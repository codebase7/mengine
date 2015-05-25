/*!
    Multiverse Engine Project 04/8/2014 FileUtills FileUtills_Private_API_Posix_Syscall.cpp

    Copyright (C) 2014 Multiverse Engine Project

    This program is free software;
    you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
    either version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with this program;
    if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    Official source repository and project information can be found at
    https://github.com/codebase7/mengine
*/

#include "FileUtills.h"
#include "FileUtills_Private_API.h"
#include "FileUtills_Private_API_Posix_Syscall.h"

int FileUtills::ResolveSystemSymoblicLink_Syscall(char ** path, size_t * pathSize)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// The result of this function.
	int errcpy = 0;						// Used to copy errno for translation if needed.
	char * readLinkBuf = NULL;				// Pointer to a buffer for readlink().
	char * checkBuffer = NULL;				// A second buffer for readlink() that is used to verifiy the contents of readLinkBuf during the "devil's loop".
	ssize_t firstBufferLength = 0;				// Signed return value of the number of bytes written to the buffer by readlink(). (Just so they could return that -1 error code....)
	ssize_t secondBufferLength = 0;				// Signed return value of the number of bytes written to the checkBuffer by readlink(). (Just so they could return that -1 error code....)
	size_t realBufferLength = 0;				// Unsigned value of how big the buffer is. (Used for accessing and allocating the buffer.)
	const size_t MAX_GET_EXE_PATH_REALLOC = 4;		// Maximum number of times to run the memory reallocation loop.
	const size_t BASE_SIZE = 1000;				// Inital number of bytes to allocate. (This number is multiplied by the loop iteration value (x) after each loop iteration.)
	struct stat st;						// POSIX Stat structure for retriving the status of the given path. (Whether or not it's a symlink and it's length.)

	// Make sure we got a valid path.
	if ((path != NULL) && ((*path) != NULL) && (pathSize != NULL) && ((*pathSize) > 0))
	{ 
		// Call lstat.
		if (lstat((*path), &st) == 0)
		{
			// Check and see if the given path is a symbolic link.
			if (S_ISLNK((st.st_mode)))
			{
				// Check the size of the given link. (Just in case we get a non-conforming system that actually fills in st_size for the proc fs. (See below rant.))
				if (st.st_size > 0)
				{
					// OK, allocate a buffer for the given length. (Plus one so we can add a NULL character to it as readlink() does not.)
					readLinkBuf = malloc((st.st_size + 1));
					if (readLinkBuf != NULL)
					{
						// Call readlink.
						firstBufferLength = readlink((*path), readLinkBuf, st.st_size);

						// Check and see if the result from readlink is not -1 and if it equals st.st_size.
						if (firstBufferLength != -1)
						{
							if (firstBufferLength == st.st_size)
							{
								// Insert a NULL character after the end of the string.
								readLinkBuf[st.st_size] = '\0';

								// Copy the result to the path buffer.
								(*path) = readLinkBuf;

								// Set success.
								ret = COMMON_ERROR_SUCCESS;
							}
							else
							{
								// OK, we got screwed with. The result should be the same size as the original lstat() call returned.
								ret = COMMON_ERROR_INTERNAL_ERROR;

								// Log the error.
								COMMON_LOG_VERBOSE("FileUtills_ResolveSystemSymoblicLink(): Size of the read symbolic link is not the same as the size returned from the OS.");
							}
						}
						else
						{
							// Copy the error code.
							errcpy = errno;

							// Translate the error code.
							ret = Common_Translate_Posix_Errno_To_Common_Error_Code(errcpy);

							// Log the error.
							COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): An error was returned while reading the symbolic link: ");
							COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
						}
					}
					else
					{
						// Could not allocate buffer.
						ret = COMMON_ERROR_MEMORY_ERROR;

						// Log the error.
						COMMON_LOG_INFO("FileUtills_ResolveSystemSymoblicLink(): ");
						COMMON_LOG_INFO(Common_Get_Error_Message(ret));
					}
				}
				else
				{
					/*
					 * 	OK, run the hard limited implemetation.
					 * 	(Copied from the original FileUtills::GetExecDirectory_Syscall() implemetation for POSIX.)
					 *
					 * 	We do this to avoid a runaway reallocation loop which could be considered a resource starvation
					 * 	issue. (See below for the original rant, just ignore the /proc file system issues for symlinks
					 * 	in general. (Only issues 1 and 3 apply to ALL symlinks.))
					 *
					 * 	(Begin original rant.)
					 *
					 * 	Short version:
					 * 	This is a cluster<explisitive>.
					 * 
					 * 	Long version:
					 * 	The only reliable (guarrenteed to work) method for getting the executable
					 * 	path in linux, is by using readlink() on /proc/self/exe.
					 *
					 * 	However, this has several issues. 
					 *
					 * 	First issue: readlink() expects a preallocated buffer to store the result.
					 * 	If the preallocated buffer is too small for the full path, then readlink()
					 * 	will silently truncate the remaining data and not tell us how much was
					 * 	left over.
					 * 
					 * 	Second issue: The proc filesystem misbehaves and does not fill in the
					 * 	st_size field of the stat structure. So as a result we can't easilly
					 * 	tell how much memory to allocate for our buffer.
					 * 
					 * 	Third issue: Because some filesystems allow paths of unlimited size,
					 * 	(i.e. the only restriction is having the space to store the path),
					 * 	we can't use PATH_MAX (as it's possibly wrong), and we can't set a
					 * 	limit on our memory allocation.
					 * 
					 * 	Because of these issues, the glibc MANUAL actually gives an indefinite
					 * 	loop of memory allocation->readlink()->if(!got entire link)->Deallocate memory->Allocate memory.
					 * 	for reading a symlink from the filesystem.
					 * 
					 * 	This loop is reimplimented here, but with three differences.
					 * 	
					 * 		- The loop will end once a certian amount of reallocations (defined by MAX_GET_EXE_PATH_REALLOC)
					 * 		  is reached. (This is to prevent some of the above issues.)
					 * 
					 * 		- The loop will also check to make sure that the returned string has not been altered. 
					 * 		  (via memcmp). (Attempt to prevent a compromised system from mallissously changing the
					 * 		   symlink's destionation as a result of our multiple accesses to the link itself.)
					 *
					 * 		- The loop will reallocate the buffer after the link is fully read so that ONLY the
					 * 		  needed memory to store it is allocated for it. (Prevent unnessacarry memory usage.)
					 * 
					 * 	(End of original rant.)
					 */
					// Begin the devil's loop.
					for (size_t x = 0; ((x < MAX_GET_EXE_PATH_REALLOC) &&
							    ((readLinkBuf == NULL) && (checkBuffer == NULL)) &&
							    (ret == COMMON_ERROR_UNKNOWN_ERROR)); x++)
					{
						// Recalculate bufferLength.
						realBufferLength = (BASE_SIZE * (x + 1));

						// Allocate the memory.
						readLinkBuf = (char*)malloc(realBufferLength);
						checkBuffer = (char*)malloc(realBufferLength);

						// Make sure it was allocated.
						if ((readLinkBuf != NULL) && (checkBuffer != NULL))
						{
							// Blank out the allocated memory.
							memset(readLinkBuf, '\0', realBufferLength);
							memset(checkBuffer, '\0', realBufferLength);

							// Call readlink() for the first buffer.
							firstBufferLength = readlink((*path), readLinkBuf, realBufferLength);

							// Check bufferLength.
							if (firstBufferLength >= 0)
							{
								// Check to see if we got the entire path.
								if (firstBufferLength < realBufferLength)
								{
									// Call readlink() for the second buffer.
									secondBufferLength = readlink((*path), checkBuffer, realBufferLength);

									// Check secondBufferLength.
									if (secondBufferLength >= 0)
									{
										// Check to see if we got the entire path.
										if (secondBufferLength == firstBufferLength)
										{
											// Call memcmp().
											if (memcmp(readLinkBuf, checkBuffer, realBufferLength) == 0)
											{
												// Paths match, deallocate the second buffer.
												if (checkBuffer != NULL)
												{
													memset(checkBuffer, '\0', realBufferLength);
													free(checkBuffer);
													checkBuffer = NULL;
												}

												// Reallocate the buffer. (Free unneeded memory.)
												ret = FileUtills_Reallocate_CString_Buffer(readLinkBuf, realBufferLength, firstBufferLength);
												if (ret == COMMON_ERROR_SUCCESS)
												{
													// Copy the first buffer pointer to the path buffer pointer.
													(*path) = readLinkBuf;
												}
												else
												{
													// Could not free the unneeded memory.
													COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): Call to FileUtills_Reallocate_CString_Buffer() failed: ");
													COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
												}
											}
											else
											{
												// Something is screwing with us...abort.
												ret = COMMON_ERROR_INTERNAL_ERROR;
												COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): ");
												COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
											}
										}
										else
										{
											// Something is screwing with us...abort.
											ret = COMMON_ERROR_INTERNAL_ERROR;
											COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): ");
											COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
										}
									}
									else
									{
										// Error.
										errcpy = errno;
										ret = Common_Translate_Posix_Errno_To_Common_Error_Code(errcpy);
										COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): readlink() system call returned: ");
										COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
									}
								}
								else
								{
									// We did not get the entire link, so we need to deallocate it for the next loop.
									if (readLinkBuf != NULL)
									{
										memset(readLinkBuf, '\0', realBufferLength);
										free(readLinkBuf);
										readLinkBuf = NULL;
									}
									if (checkBuffer != NULL)
									{
										memset(checkBuffer, '\0', realBufferLength);
										free(checkBuffer);
										checkBuffer = NULL;
									}
								}
							}
							else
							{
								// Error.
								errcpy = errno;
								ret = Common_Translate_Posix_Errno_To_Common_Error_Code(errcpy);
								COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): readlink() system call returned: ");
								COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
							}
						}
					}

					/*
					 * 	If we reach here, and ret == COMMON_ERROR_UNKNOWN_ERROR,
					 * 	then we have failed. (Most likely we ran out of reallocation attempts...)
					 */
					if (ret == COMMON_ERROR_UNKNOWN_ERROR)
					{
						/*
						 * Set COMMON_INTERNAL_ERROR.
						 * 
						 * (The system most likely can fetch the link,
						 *  but we need to limit the reallocation attempts
						 *  to prevent issues. So it's not appropriate to use
						 *  FILEUTILLS_PATH_LENGTH_INVALID.)
						 */
						ret = COMMON_ERROR_INTERNAL_ERROR;
						COMMON_LOG_INFO("FileUtills_ResolveSystemSymoblicLink(): ");
						COMMON_LOG_INFO(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
						COMMON_LOG_INFO(" Unable to resolve the symbolic link due to engine limitation. (Length of the resolved path is too long.)");
					}

					// If unsuccessful, make sure both buffers are deallocated.
					if (ret != COMMON_ERROR_SUCCESS)
					{
						if (readLinkBuf != NULL)
						{
							memset(readLinkBuf, '\0', realBufferLength);
							free(readLinkBuf);
							readLinkBuf = NULL;
						}
						if (checkBuffer != NULL)
						{
							memset(checkBuffer, '\0', realBufferLength);
							free(checkBuffer);
							checkBuffer = NULL;
						}
					}
				}
			}
			else
			{
				// This is not a symbolic link.
				ret = COMMON_ERROR_INVALID_ARGUMENT;

				// Log the error.
				COMMON_LOG_INFO("FileUtills_ResolveSystemSymoblicLink(): The given path ( ");
				COMMON_LOG_INFO(path);
				COMMON_LOG_INFO(" ) is not a symbolic link created by the system.");
			}
		}
		else
		{
			// Copy errno.
			errcpy = errno;

			// Translate the error.
			ret = Common_Translate_Posix_Errno_To_Common_Error_Code(errcpy);

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): An error was returned while accessing the given path: ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
		}
	}
	else
	{
		// Invalid path.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path argument is invalid.");
	}

	// Return the result.
	return ret;
}

int FileUtills::GetUserProfileDirectoryPath_Syscall(std::string & path)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.
#ifdef __linux__
	// Init vars.
	int errorg = 0;						// Used to hold the original state of errno so it can be restored after we finish.
	int errcpy = 0;						// Used to store errno if needed.
	char * pHD = NULL;					// Used to fetch the path from the system.

	// Backup and clear errno.
	errorg = errno;
	errno = 0;

	// Blank out the path value.
	path.clear();

	// Get the path to the user's profile directory.
	try {
		pHD = getenv("HOME");
		if ((errno == 0) && (pHD != NULL))
		{
			// Copy the variable to the path.
			path = pHD;

			// Set success code.
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			// Could not get user profile directory path variable.
			errcpy = errno;
			ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
			COMMON_LOG_VERBOSE("FileUtills::GetUserProfileDirectoryPath(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
			COMMON_LOG_VERBOSE(" Could not get user profile directory path from enviorment.\n");

			// Reset path.
			path.clear();
		}
	}
	catch (exception &ex)
	{
		// Exception thown.
		ret = COMMON_ERROR_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("FileUtills::GetUserProfileDirectoryPath(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE(" ");
		COMMON_LOG_VERBOSE(ex.what());
		COMMON_LOG_VERBOSE("\n");

		// Reset path.
		path.clear();
	}

	// Check for an allocated buffer.
	if (pHD != NULL)
	{
		// Release the buffer.
		free(pHD);
		pHD = NULL;
	}

	// Restore errno.
	errno = errorg;
#endif	// __linux__

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::GetCurrentWorkingDirectoryPath_Syscall(std::string & path)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.
#ifdef __linux__
	int errorg = 0;						// Used to hold the original state of errno so it can be restored after we finish.
	int errcpy = 0;						// Used to store errno if needed.
	char * pCWD = NULL;					// Used to fetch path from system.

	// Backup and clear errno.
	errorg = errno;
	errno = 0;

	// Blank out the path value.
	path.clear();

	// Get current directory.
	try {
		/*
		 * 	NOTE: The call below is linux (libc5, libc6, and glibc) specific.
		 * 	(The standard requires a preallocated buffer.)
		 * 
		 * 	I dislike the idea of a preallocated buffer as we cannot reliably
		 * 	determine the needed length. (Plus it could change between calls.)
		 * 
		 * 	This really should be checked for and an error thrown if the OS /
		 * 	libc in use does not support this usage.
		 */
		pCWD = getcwd(NULL, 0);
		if ((errno == 0) && (pCWD != NULL))
		{
			// Copy the path.
			path = pCWD;

			// Set ret.
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			// Could not get current working directory path variable.
			errcpy = errno;
			ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
			COMMON_LOG_VERBOSE("FileUtills::GetCurrentWorkingDirectoryPath(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
			COMMON_LOG_VERBOSE(" Could not get current working directory path from enviorment.\n");

			// Reset path.
			path.clear();
		}
	}
	catch(exception &ex)
	{
		// Exception thown.
		ret = COMMON_ERROR_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("FileUtills::GetCurrentWorkingDirectoryPath(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE(" ");
		COMMON_LOG_VERBOSE(ex.what());
		COMMON_LOG_VERBOSE("\n");

		// Reset path.
		path.clear();
	}

	// Check for an allocated buffer.
	if (pCWD != NULL)
	{
		// Release the buffer.
		free(pCWD);
		pCWD = NULL;
	}

	// Restore errno.
	errno = errorg;
#endif	// __linux__

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::GetExecDirectory_Syscall(std::string & retStr)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;	// The result code returned from this function.
	std::string result = "";		// The string returned from this function.
#ifdef __linux__

	// Call FileUtills::ResolveSystemSymoblicLink_Syscall(). (Make sure it's the real path not a symlink. (PROC_PATH is a symlink, and a weird one at that.))
	ret = FileUtills::ResolveSystemSymoblicLink_Syscall(PROC_PATH, result);
	if (ret == COMMON_ERROR_SUCCESS)
	{
		// Copy the result string to retStr.
		retStr = result;
	}
	else
	{
		// Check for an invalid argument error.
		if (ret == COMMON_ERROR_INVALID_ARGUMENT)
		{
			// This is an internal engine error.
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Report it.
			COMMON_LOG_WARNING("FileUtills::GetExecDirectory(): ");
			COMMON_LOG_WARNING(Common::Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
			COMMON_LOG_WARNING(" Getting the executable path failed. (Call to an internal engine function failed.) Please report this bug.\n");
		}
	}

#endif
	// Clear the result string.
	result.clear();

	// Return result.
	return ret;
}

FileUtills::dirlist * FileUtills::getDirectory_Syscall(const std::string & absPath, const bool & cleanList)
{
	// Init vars.
	int errcpy = 0;					// Used to fetch the error code.
	FileUtills::dirlist * ret = NULL;		// The FileUtills directory structure.
	struct dirent * dir = NULL;			// The OS (POSIX) directory structure.
	DIR * dp = NULL;				// Directory stream to hold directory name..... (Why can't it just take a c string?)
	std::string tempname = "";			// Used to store the filename / subdirectory name for the addToArray function.

	// Dumb check.
	if (absPath.size() > 0)
	{
#ifdef POSIX_COMMON_H
		// Allocate the dirlist.
		try{
			ret = new FileUtills::dirlist;
			if (ret != NULL)
			{
				// Set the path.
				ret->path = absPath;

				// Dump the path as a c string into the Directory stream object......(Overly complicated POS......)

				// Check and make sure we can open the directory first.
				if ((dp = (opendir(absPath.c_str()))) == NULL)
				{
					// Copy the error code, and translate it.
					errcpy = errno;
					errcpy = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);

					// An error occured.
					if (ret != NULL)
					{
						delete ret;
						ret = NULL;
					}

					// Log the error.
					COMMON_LOG_INFO("FileUtills::getDirectory(): Unable to get directory contents for ( ");
					COMMON_LOG_INFO(absPath.c_str());
					COMMON_LOG_INFO(" ) The system returned ");
					COMMON_LOG_INFO(Common::Get_Error_Message(errcpy));
					COMMON_LOG_INFO("\n");

					// Copy the translated error code to Common::commonLastErrorCode.
					Common::commonLastErrorCode = errcpy;
				}

				// Start filesystem fetch loop.
				while ((dir = readdir(dp))) // Call Host OS function.
				{
					// Check and see if the cleanList flag is set.
					if (cleanList)
					{
						// Check to see if d_name is a POSIX directory shortcut.
						if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0))
						{
							// d_name is a directory shortcut, do not add it to the list.
							continue;
						}
					}

					// Cast d_name to a string.
					tempname = dir->d_name;

					// Add the data to the array.
					ret->list.push_back(tempname);
				}

				// Close the directory stream and reset it.
				closedir(dp);

				// Set the number of entries.
				ret->numOfEntries = ret->list.size();

				// Set Common::commonLastErrorCode.
				Common::commonLastErrorCode = COMMON_ERROR_SUCCESS;
			}
			else
			{
				// Could not allocate memory.
				Common::commonLastErrorCode = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		catch(exception &ex)
		{
			// Free memory if needed.
			if (ret != NULL)
			{
				delete ret;
				ret = NULL;
			}

			// Could not allocate struct.
			Common::commonLastErrorCode = COMMON_ERROR_EXCEPTION_THROWN;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::getDirectory(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_EXCEPTION_THROWN));
			COMMON_LOG_DEBUG(" ");
			COMMON_LOG_DEBUG(ex.what());
			COMMON_LOG_DEBUG("\n");
		}
#endif
	}
	else
	{
		// Invalid path.
		Common::commonLastErrorCode = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::getDirectory(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Return the result.
	return ret;
}

int FileUtills::GetByteFreespace_Syscall(const std::string & absPath, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.

#ifdef POSIX_COMMON_H
	struct statvfs * buffer = NULL;				// Buffer used to get filesystem info from the OS.

	// Reset result.
	result = 0;

	// Check for invalid absPath.
	if (absPath.size() > 0)
	{
		// Begin try block.
		try {
			// Create buffer.
			buffer = new struct statvfs;
			if (buffer != NULL)
			{
				// Call host's function, and check for error.
				if (statvfs(absPath.c_str(), buffer) == 0)
				{
					// Determine number of free bytes. (Number of avaiable blocks * block size)
					result = (buffer->f_bavail * buffer->f_bsize);

					// Set success.
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					// Figure out what the error we got back was.
					ret = errno;
					ret = Common::Translate_Posix_Errno_To_Common_Error_Code(ret);

					// Log the error.
					COMMON_LOG_DEBUG("FileUtills::GetByteFreespace(): ");
					COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
					COMMON_LOG_DEBUG("\n");
				}

				// Delete the buffer
				delete buffer;
				buffer = NULL;
			}
			else
			{
				// Could not allocate memory.
				ret = COMMON_ERROR_MEMORY_ERROR;

				// Log the error.
				COMMON_LOG_DEBUG("FileUtills::GetByteFreespace(): ");
				COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
				COMMON_LOG_DEBUG("\n");
			}
		}
		catch (exception &ex)
		{
			// Exception thrown.
			ret = COMMON_ERROR_EXCEPTION_THROWN;

			// Check for allocated buffer.
			if (buffer != NULL)
			{
				delete buffer;
				buffer = NULL;
			}

			// Log the error.
			COMMON_LOG_VERBOSE("FileUtills::GetByteFreespace(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
			COMMON_LOG_VERBOSE(" ");
			COMMON_LOG_VERBOSE(ex.what());
			COMMON_LOG_VERBOSE("\n");
		}
	}
	else
	{
		// Invalid absPath.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::GetByteFreespace(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}
#endif

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::CreateDirectory_Syscall(const char * absPath)
{
	// Init errcpy.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.
	int errcpy = 0;						// Used to copy errno for translation if needed.

	// Check for NULL pointer.
	if (absPath != NULL)
	{
		// Attempt to create the given directory.
		if (mkdir(absPath, S_IRWXU) != 0)
		{
			// Copy errno, and convert it.
			errcpy = errno;
			ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
		}
		else
		{
			// Directory created successfully.
			ret = COMMON_ERROR_SUCCESS;
		}
	}
	else
	{
		// Invalid argument.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::CreateDirectory(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::CheckPermissions_Syscall(const std::string & absPath, const bool & read, const bool & write, const bool & exec)
{
	// Init vars.
	int errcpy = 0;						// Used to hold the errno value to translate it if needed.
	int mode = 0;						// Used to construct the mode bitmask.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.

	// Make sure that absPath is valid.
	if (absPath.size() > 0)
	{
		// Double check and make sure we have something to do.
		if ((read != false) || (write != false) || (exec != false))
		{
			// Set the mode.
			mode = F_OK;

			// Check for read permission check.
			if (read == true)
			{
				mode = mode | R_OK;
			}

			// Check for write permission check.
			if (write == true)
			{
				mode = mode | W_OK;
			}

			// Check for execute permission check.
			if (exec == true)
			{
				mode = mode | X_OK;
			}

			// Issue syscall.
			ret = access(absPath.c_str(), mode);
			if (ret == 0)
			{
				// File or directory is readable & writable set ret to: COMMON_ERROR_SUCCESS.
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				// Translate the errorcode.
				errcpy = errno;
				ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);

				// Log the error.
				COMMON_LOG_VERBOSE("FileUtills::CheckPermissions(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
				COMMON_LOG_VERBOSE("\n");
			}
		}
		else
		{
			// No check to make.
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::CheckPermissions(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG(" No check to perform, aborting.\n");
		}
	}
	else
	{
		// Invalid absPath.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::CheckPermissions(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Default return.
	return ret;
}

int FileUtills::DoesExist_Syscall(const std::string & absPath)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.

	// Check for valid arg.
	if (absPath.size() > 0)
	{
#ifdef POSIX_COMMON_H
		int errcpy = 0;						// Used to copy errno if needed.

		// Check and see if the file exists.
		ret = access(absPath.c_str(), F_OK);
		if (ret == 0)
		{
			// Path exists.
			ret = FILEUTILLS_ERROR_EXISTANT;
		}
		else
		{
			// Copy the error code.
			errcpy = errno;

			// Translate the error code.
			ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
		}
#endif	// POSIX_COMMON_H
	}
	else
	{
		// Invalid absPath.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::DoesExist(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Set Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::IsFileOrDirectory_Syscall(const char * absPath, const size_t absPathSize)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// Result of this function. (Defaults to function not implemetated.)
	int errcpy = 0;						// Used to copy errno if needed.

#ifdef POSIX_COMMON_H
	struct stat * buf = NULL;				// Linux stat structure, used with syscall.

	// Check for invalid absPath.
	if ((absPath != NULL) && (absPathSize() > 0))
	{
		// Init stat buffer.
		buf = new struct stat;
		if (buf != NULL)
		{
			// Ask the OS to stat() the path.
			ret = lstat(absPath, buf);

			// Check the result.
			if (ret == 0)
			{
				// Log result.
				COMMON_LOG_VERBOSE("FileUtills::IsFileOrDirectory(): The given path ( ");
				COMMON_LOG_VERBOSE(absPath);

				// Check the stat structure.
				if (S_ISREG((buf->st_mode)))
				{
					// Path is a regular file.
					ret = FILEUTILLS_ERROR_PATH_IS_A_FILE;

					// Log result.
					COMMON_LOG_VERBOSE(" ) is a regular file.");
				}
				else
				{
					if (S_ISDIR((buf->st_mode)))
					{
						// Path is a directory.
						ret = FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY;

						// Log result.
						COMMON_LOG_VERBOSE(" ) is a directory.");
					}
					else
					{
						// Check for a symlink.
						if (S_ISLNK((buf->st_mode)))
						{
							// Symlink.
							ret = FILEUTILLS_ERROR_PATH_IS_A_SYMLINK;

							// Log result.
							COMMON_LOG_VERBOSE(" ) is a symbolic link.");
						}
						else
						{
							// Special file.
							ret = COMMON_ERROR_SUCCESS;

							// Log result.
							COMMON_LOG_VERBOSE(" ) is a special file.");
						}
					}
				}
			}
			else
			{
				// Error, translate it and log it.
				errcpy = errno;
				ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);

				// Check for non-existance.
				if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
				{
					COMMON_LOG_VERBOSE("FileUtills::IsFileOrDirectory(): The given path ( ");
					COMMON_LOG_VERBOSE(absPath);
					COMMON_LOG_VERBOSE(" ) or a componet of it does not exist.");
				}
				else
				{
					COMMON_LOG_DEBUG("FileUtills::IsFileOrDirectory(): ");
					COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
					COMMON_LOG_DEBUG(" Was returned while checking path ( ");
					COMMON_LOG_DEBUG(absPath);
					COMMON_LOG_DEBUG(" ).");
				}
			}

			// Delete stat buffer.
			delete buf;
			buf = NULL;
		}
		else
		{
			// Coul not allocate stat structure.
			ret = COMMON_ERROR_MEMORY_ERROR;

			// Log the error if needed.
			COMMON_LOG_DEBUG("FileUtills::IsFileOrDirectory(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		}
	}
	else
	{
		// Invalid absPath.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::IsFileOrDirectory(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given path is invalid.");
	}
#endif	// POSIX_COMMON_H

	// Return the result.
	return ret;
}

int FileUtills::DeletePath_Syscall(const std::string & absPath)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.
	int errcpy = 0;						// Used to copy the error code if needed.

	// Begin try block.
	try {
		// Check for invalid absPath.
		if (absPath.size() > 0)
		{
#ifdef POSIX_COMMON_H
			// Issue syscall.
			if (remove(absPath.c_str()) == 0)
			{
				// Success.
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				// Copy errno.
				errcpy = errno;

				// Translate the error.
				ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
			}
#endif	// POSIX_COMMON_H
		}
		else
		{
			// Invalid absPath.
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::DeletePath(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG(" Given path is invalid.\n");
		}
	}
	catch (exception &ex)
	{
		// Exception thrown.
		ret = COMMON_ERROR_EXCEPTION_THROWN;

		// Log the error.
		COMMON_LOG_VERBOSE("FileUtills::DeletePath(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE(" ");
		COMMON_LOG_VERBOSE(ex.what());
		COMMON_LOG_VERBOSE("\n");
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;
  
	// Return the result.
	return ret;
}

int FileUtills::RenamePath_Syscall(const std::string & absPathSrc, const std::string & absPathDest, const bool & dereferenceSymLinks)
{
	// Init vars.
	bool srcIsASymLink = false;			// Used to tell if the source is a symlink.
	bool destIsASymLink = false;			// Used to tell if the destionation is a symlink.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		// The result of this function.
	int errcpy = 0;					// Used to copy errno for translation if needed.
	char * resultFromRealPath = NULL;		// Used to check the result from realpath().
	char * srcLinkedPath = NULL;			// Used to hold the dereferenced source path if needed.
	char * destLinkedPath = NULL;			// Used to hold the dereferenced destionation path if needed.

	// Begin try block.
	try {
		// Check for valid source path.
		if (absPathSrc.capacity() > 0)
		{
			// Check for valid destionation path.
			if (absPathDest.capacity() > 0)
			{
				// Disable the symlink check if dereferenceSymLinks is set to false.
				if (!dereferenceSymLinks)
				{
					// Check and see if the source is a symlink.
					ret = FileUtills::IsFileOrDirectory_Syscall(absPathSrc);
					if (ret == FILEUTILLS_ERROR_PATH_IS_A_SYMLINK)
					{
						// Clear resultFromRealPath.
						resultFromRealPath = NULL;

						// Source is a symlink, so we need to dereference it.
						srcIsASymLink = true;
						resultFromRealPath = realpath(absPathSrc.c_str(), srcLinkedPath);
						if (resultFromRealPath == NULL)
						{
							// We've hit an error.
							errcpy = errno;
							ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);

							// Log the error.
							COMMON_LOG_DEBUG("FileUtills::RenamePath(): Unable to dereference symlink on the source path ( ");
							COMMON_LOG_DEBUG(absPathSrc.c_str());
							COMMON_LOG_DEBUG(").\n");

							// Deallocate the srcLinkedPath if needed.
							if (srcLinkedPath != NULL)
							{
								free(srcLinkedPath);
								srcLinkedPath = NULL;
							}
						}
					}

					// Check and see if the destionation is a symlink.
					ret = FileUtills::IsFileOrDirectory_Syscall(absPathDest);
					if (ret == FILEUTILLS_ERROR_PATH_IS_A_SYMLINK)
					{
						// Clear resultFromRealPath.
						resultFromRealPath = NULL;

						// Destionation is a symlink, so we need to dereference it.
						destIsASymLink = true;
						resultFromRealPath = realpath(absPathDest.c_str(), destLinkedPath);
						if (resultFromRealPath == NULL)
						{
							// We've hit an error.
							errcpy = errno;
							ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);

							// Log the error.
							COMMON_LOG_DEBUG("FileUtills::RenamePath(): Unable to dereference symlink on the destionation path ( ");
							COMMON_LOG_DEBUG(absPathDest.c_str());
							COMMON_LOG_DEBUG(").\n");

							// Deallocate the destLinkedPath if needed.
							if (destLinkedPath != NULL)
							{
								free(destLinkedPath);
								destLinkedPath = NULL;
							}
						}
					}
				}

				// Check and see what variables must be passed to rename.
				if (srcIsASymLink && destIsASymLink)
				{
					// Check for allocated srcLinkedPath.
					if (srcLinkedPath != NULL)
					{
						// Check for allocated destLinkedPath.
						if (destLinkedPath != NULL)
						{
							// Issue syscall.
							errcpy = rename(srcLinkedPath, destLinkedPath);
						}
						else
						{
							// Success without result?
							ret = COMMON_ERROR_INTERNAL_ERROR;

							// Log the error.
							COMMON_LOG_WARNING("FileUtills::RenamePath(): Resolved symlink buffer for the destionation path ( ");
							COMMON_LOG_WARNING(absPathDest.c_str());
							COMMON_LOG_WARNING(" ) is invalid, but it should be valid. Please report this bug.\n");
						}
					}
					else
					{
						// Success without result?
						ret = COMMON_ERROR_INTERNAL_ERROR;

						// Log the error.
						COMMON_LOG_WARNING("FileUtills::RenamePath(): Resolved symlink buffer for the source path ( ");
						COMMON_LOG_WARNING(absPathSrc.c_str());
						COMMON_LOG_WARNING(" ) is invalid, but it should be valid. Please report this bug.\n");
					}
				}
				else
				{
					if (srcIsASymLink && !destIsASymLink)
					{
						// Check for allocated srcLinkedPath.
						if (srcLinkedPath != NULL)
						{
							// Issue syscall.
							errcpy = rename(srcLinkedPath, absPathDest.c_str());
						}
						else
						{
							// Success without result?
							ret = COMMON_ERROR_INTERNAL_ERROR;

							// Log the error.
							COMMON_LOG_WARNING("FileUtills::RenamePath(): Resolved symlink buffer for the source path ( ");
							COMMON_LOG_WARNING(absPathSrc.c_str());
							COMMON_LOG_WARNING(" ) is invalid, but it should be valid. Please report this bug.\n");
						}
					}
					else
					{
						if (!srcIsASymLink && destIsASymLink)
						{
							// Check for allocated destLinkedPath.
							if (destLinkedPath != NULL)
							{
								// Issue syscall.
								errcpy = rename(absPathSrc.c_str(), destLinkedPath);
							}
							else
							{
								// Success without result?
								ret = COMMON_ERROR_INTERNAL_ERROR;

								// Log the error.
								COMMON_LOG_WARNING("FileUtills::RenamePath(): Resolved symlink buffer for the destionation path ( ");
								COMMON_LOG_WARNING(absPathDest.c_str());
								COMMON_LOG_WARNING(" ) is invalid, but it should be valid. Please report this bug.\n");
							}
						}
						else
						{
							// Issue syscall.
							errcpy = rename(absPathSrc.c_str(), absPathDest.c_str());
						}
					}
				}

				// Check to see if we hit an internal error.
				if (ret != COMMON_ERROR_INTERNAL_ERROR)
				{
					// Check the result of the syscall.
					if (errcpy == 0)
					{
						// Success.
						ret = COMMON_ERROR_SUCCESS;
					}
					else
					{
						// Copy the error code.
						errcpy = errno;

						// Check for EXDEV.
						if (errcpy = EXDEV)
						{
							// The result is that the source and destionation are not on the same filesystem.
							ret = FILEUTILLS_ERROR_NOT_ON_SAME_FILESYSTEM;
						}
						else
						{
							// Translate the error code.
							ret = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
						}
					}
				}
			}
			else
			{
				// Invalid absPathDest.
				ret = COMMON_ERROR_INVALID_ARGUMENT;

				// Log the error.
				COMMON_LOG_DEBUG("FileUtills::RenamePath(): ");
				COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
				COMMON_LOG_DEBUG(" Given destionation path is invalid.\n");
			}
		}
		else
		{
			// Invalid absPathSrc.
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::RenamePath(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG(" Given source path is invalid.\n");
		}

		// Deallocate srcLinkedPath and destLinkedPath if needed.
		if (srcLinkedPath != NULL)
		{
			free(srcLinkedPath);
			srcLinkedPath = NULL;
		}
		if (destLinkedPath != NULL)
		{
			free(destLinkedPath);
			destLinkedPath = NULL;
		}
	}
	catch (exception &ex)
	{
		// Exception thrown.
		ret = COMMON_ERROR_EXCEPTION_THROWN;

		// Log the error.
		COMMON_LOG_VERBOSE("FileUtills::RenamePath(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE(" ");
		COMMON_LOG_VERBOSE(ex.what());
		COMMON_LOG_VERBOSE("\n");
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}
