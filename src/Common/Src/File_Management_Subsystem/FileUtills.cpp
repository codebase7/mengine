/*!
    Multiverse Engine Project 04/12/2011 FileUtills FileUtills.cpp

    Copyright (C) 2013 Multiverse Engine Project

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

/*!
    std::string RemoveTrailingSlash(const std::string & path)

    Removes a DIR_SEP on the end of the given path string (if it exists)
    Will not do anything and return the original string if there is only 1 charater in the given path string.
    Will also return the original string if a memory error occurs.
*/
std::string RemoveTrailingSlash(const std::string & path)
{
	 //init vars
	size_t size = 0;
	std::string buffer = "";

	// Get size of the Directory string.
	size = path.size();

	// Check the length of the string see if it is only 1 charater
	if (size == 1)
	{
	    // We can't remove anything, if we do the return would be empty.
	    return path;
	}

	// Copy the directory string to buffer
	buffer = path;

	// Check and see if a directory seperator is on the end of the string.
	if ((path.find_last_of(DIR_SEP)) == (size-1))
	{
		 // Remove the trailing Directory seperator so we don't screw up the next check.
		 // Note substr CAN throw an exception so we must put it in a try catch block
		 try{
            buffer = path.substr(0, (size-1));
		 }
		 catch(exception ex)
		 {
		     // We can't return an error so we will silently fail.
		     return path;
		 }
	}

	// Return new path.
	return buffer;
}

int FileUtills::GetUserProfileDirectoryPath(std::string & path)
{
	// Reset Common::commonLastErrorCode.
	Common::commonLastErrorCode = Common::COMMON_FUNCTION_NOT_IMPLEMENTED;
#ifdef __linux__
	// Init vars.
	int errorg = 0;			// Used to hold the original state of errno so it can be restored after we finish.
	int errcpy = 0;			// Used to store errno if needed.
	char * pHD = NULL;		// Used to fetch the path from the system.

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
			Common::commonLastErrorCode = Common::COMMON_SUCCESS;
		}
		else
		{
			// Could not get user profile directory path variable.
			errcpy = errno;
			Common::commonLastErrorCode = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
			COMMON_LOG_VERBOSE("GetUserProfileDirectoryPath(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_VERBOSE(" Could not get user profile directory path from enviorment.\n");

			// Reset path.
			path.clear();
		}
	}
	catch (exception &ex)
	{
		// Exception thown.
		Common::commonLastErrorCode = Common::COMMON_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("GetUserProfileDirectoryPath(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
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

	// Exit function.
	return Common::commonLastErrorCode;
}

int FileUtills::GetCurrentWorkingDirectoryPath(std::string & path)
{
	// Reset Common::commonLastErrorCode.
	Common::commonLastErrorCode = Common::COMMON_FUNCTION_NOT_IMPLEMENTED;
#ifdef __linux__
	// Init vars.
	int errorg = 0;			// Used to hold the original state of errno so it can be restored after we finish.
	int errcpy = 0;			// Used to store errno if needed.
	char * pCWD = NULL;		// Used to fetch path from system.

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

			// Set commonLastErrorCode.
			Common::commonLastErrorCode = Common::COMMON_SUCCESS;
		}
		else
		{
			// Could not get current working directory path variable.
			errcpy = errno;
			Common::commonLastErrorCode = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
			COMMON_LOG_VERBOSE("GetCurrentWorkingDirectoryPath(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_VERBOSE(" Could not get current working directory path from enviorment.\n");

			// Reset path.
			path.clear();
		}
	}
	catch(exception &ex)
	{
		// Exception thown.
		Common::commonLastErrorCode = Common::COMMON_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("GetCurrentWorkingDirectoryPath(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
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

	// Exit function.
	return Common::commonLastErrorCode;
}

std::string FileUtills::GetExecDirectory()
{
	// Init vars.
	std::string result = "";		// The string returned from this function.
#ifdef __linux__
	/*
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
	 * 	This loop is reimplimented here, but with two differences.
	 * 	
	 * 		- The loop will end once a certian amount of relocations (defined by GET_EXE_PATH_REALLOC)
	 * 		  is reached. (This is to prevent some of the above issues.)
	 * 
	 * 		- The loop will also check to make sure that the returned string has not been altered. 
	 * 		  (via memcmp).
	 */

	// Init vars.
	int errcpy = 0;					// Used to copy errno if needed.
	const size_t MAX_GET_EXE_PATH_REALLOC = 4;	// Maximum number of times to run the memory reallocation loop.
	const size_t BASE_SIZE = 1000;			// Inital number of bytes to allocate. (This number is multiplied by the loop iteration value (x) after each loop iteration.)
	size_t realBufferLength = 0;			// Unsigned value of how big the buffer is. (Used for accessing and allocating the buffer.)
	ssize_t firstBufferLength = 0;			// Signed return value of the number of bytes written to the buffer by readlink(). (Just so they could return that -1 error code....)
	ssize_t secondBufferLength = 0;			// Signed return value of the number of bytes written to the checkBuffer by readlink(). (Just so they could return that -1 error code....)
	char * buffer = NULL;				// First buffer.
	char * checkBuffer = NULL;			// Second buffer. (Both buffers must match exactly (memcmp) for this function to return a valid path.)
	struct stat st;					// Used to make sure that PROC_PATH is actually a symlink.
	const char * const PROC_PATH = "/proc/self/exe";// The actual path to the symlink that represents the executable in the /proc filesystem.

	// Set Common::commonLastErrorCode to COMMON_UNKNOWN_ERROR.
	Common::commonLastErrorCode = Common::COMMON_UNKNOWN_ERROR;

	// OK this is dumb, but check it anyway....
	errcpy = lstat(PROC_PATH, &st);
	if (errcpy == 0)
	{
		// Make sure that PROC_PATH is a symlink.
		if ((st.st_mode & S_IFMT) == S_IFLNK)	// S_IFMT is a bit mask for extracting the file type from st_mode. S_IFLNK is the file type for a symlink.
		{
			// Begin the devil's loop.
			try {
				for (size_t x = 0; ((x < MAX_GET_EXE_PATH_REALLOC) &&
						    ((buffer == NULL) && (checkBuffer == NULL)) &&
						    (Common::commonLastErrorCode == Common::COMMON_UNKNOWN_ERROR)); x++)
				{
					// Recalculate bufferLength.
					realBufferLength = (BASE_SIZE * (x + 1));

					// Allocate the memory.
					buffer = (char*)malloc(realBufferLength);
					checkBuffer = (char*)malloc(realBufferLength);

					// Make sure it was allocated.
					if ((buffer != NULL) && (checkBuffer != NULL))
					{
						// Blank out the allocated memory.
						memset(buffer, '\0', realBufferLength);
						memset(checkBuffer, '\0', realBufferLength);

						// Call readlink() for the first buffer.
						firstBufferLength = readlink(PROC_PATH, buffer, realBufferLength);

						// Check bufferLength.
						if (firstBufferLength >= 0)
						{
							// Check to see if we got the entire path.
							if (firstBufferLength < realBufferLength)
							{
								// Call readlink() for the second buffer.
								secondBufferLength = readlink(PROC_PATH, checkBuffer, realBufferLength);

								// Check secondBufferLength.
								if (secondBufferLength >= 0)
								{
									// Check to see if we got the entire path.
									if (secondBufferLength == firstBufferLength)
									{
										// Call memcmp().
										if (memcmp(buffer, checkBuffer, realBufferLength) == 0)
										{
											// Paths match, deallocate the second buffer.
											if (checkBuffer != NULL)
											{
												free(checkBuffer);
												checkBuffer = NULL;
											}

											// Copy the first buffer to the result.
											result = buffer;

											// Because the returned link is the actual executable, call GetParent().
											result = FileUtills::GetParent(result);
											if (result.size() > 0)
											{
												// Clear Common::commonLastErrorCode.
												Common::commonLastErrorCode = Common::COMMON_SUCCESS;
											}
											else
											{
												// GetParent() failed.
												Common::commonLastErrorCode = Common::COMMON_INTERNAL_ERROR;
												COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): ");
												COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
												COMMON_LOG_DEBUG(" Call to GetParent() failed.\n");
												result = "";
											}
										}
									}
								}
								else
								{
									// Error.
									errcpy = errno;
									Common::commonLastErrorCode = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
									COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): readlink() system call returned: ");
									COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
									COMMON_LOG_DEBUG("\n");
									result = "";
								}
							}
						}
						else
						{
							// Error.
							errcpy = errno;
							Common::commonLastErrorCode = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
							COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): readlink() system call returned: ");
							COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
							COMMON_LOG_DEBUG("\n");
							result = "";
						}
					}

					// Deallocate any remaining buffers.
					if (buffer != NULL)
					{
						free(buffer);
						buffer = NULL;
					}
					if (checkBuffer != NULL)
					{
						free(checkBuffer);
						checkBuffer = NULL;
					}
				}

				/*
				 * 	If we reach here, and Common::commonLastErrorCode == Common::COMMON_UNKNOWN_ERROR,
				 * 	then we have failed. (Most likely we ran out of reallocation attempts...)
				 */
				if (Common::commonLastErrorCode == Common::COMMON_UNKNOWN_ERROR)
				{
					/*
					 * Set COMMON_INTERNAL_ERROR.
					 * 
					 * (The system most likely can fetch the link,
					 *  but we need to limit the reallocation attempts
					 *  to prevent issues. So it's not appropriate to use
					 *  FILEUTILLS_PATH_LENGTH_INVALID.)
					 */
					Common::commonLastErrorCode = Common::COMMON_INTERNAL_ERROR;
					COMMON_LOG_INFO("FileUtills::GetExecDirectory(): ");
					COMMON_LOG_INFO(Common::Get_Error_Message(Common::commonLastErrorCode));
					COMMON_LOG_INFO(" executable path is too long to retrive due to engine limitation.\n");
					result = "";
				}
			}
			catch(...)
			{
				// Exception thrown.
				Common::commonLastErrorCode = Common::COMMON_EXCEPTION_THROWN;
				COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): ");
				COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
				COMMON_LOG_DEBUG("\n");
				result = "";
			}
		}
		else
		{
			// Internal error. (PROC_PATH is NOT a symbolic link.)
			Common::commonLastErrorCode = Common::COMMON_INTERNAL_ERROR;
			COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_DEBUG(" PROC_PATH is NOT a symbolic link.\n");
		}
	}
	else
	{
		// lstat() Error.
		errcpy = errno;
		Common::commonLastErrorCode = Common::Translate_Posix_Errno_To_Common_Error_Code(errcpy);
		COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): lstat() system call returned: ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_DEBUG("\n");
	}
#endif
	// Return result.
	return result;
}

std::string FileUtills::CheckPathType(const std::string & path)
{
        // Init vars.
        std::string output = "";
        char charArray[1000];			// Used for the cwd function.
        char * pCWD;				// Used to store result of the getCWD function.
        long int size = 0;          // Size of path string.

        // Set size.
        size = path.size();

        // Check and see if a directory seperator is in the path.
        if (path.find(DIR_SEP) == string::npos)
        {
                // Going with realtive path.
                pCWD = getcwd(charArray, sizeof(charArray));
                output = pCWD;
                output += DIR_SEP;
                output += path;
                return output;
        }

        // Look for home '~'.
        if (path.find_first_of('~') == 0)
        {
                // Get the home path.
                pCWD = getenv("HOME");
                output = pCWD;
                output += path.substr(1, size);

                // Remove the slash if it was added back.
                output = RemoveTrailingSlash(output);

                // Return output.
                return output;
        }

        // Look for "./" (Relative)
        if(path.find("./") == 0)
        {
                // Get current directory.
                pCWD = getcwd(charArray, sizeof(charArray));
                output = pCWD;

                // Add a DIR_SEP to the string or we will mess up the directory name.
                output += DIR_SEP;

                // Add data from the Directory string.
                output += path.substr(2, size);

                // Remove the slash if it was added back.
                output = RemoveTrailingSlash(output);

                // Return the output.
                return output;
        }

        // Look for absolute path.
        if (path.find(DIR_SEP) == 0)
        {
                // Path is absolute.
                return path;
        }
        else // If all else fails it must be relative.
        {
                // Assuming relative path.
                pCWD = getcwd(charArray, sizeof(charArray));
                output = pCWD;
                output += DIR_SEP;
                output += path;
                return output;
        }

        // Default return
        return "";
}

FileUtills::dirlist * FileUtills::getDirectory(const std::string & path, const bool & cleanList)
{
#ifdef POSIX_COMMON_H
	// Dumb check.
	if (path.size() <= 0)
	{
		// Invalid path.
		return NULL;
	}

	// Init vars.
	FileUtills::dirlist * buffer;
	struct dirent * dir;				// ''
	DIR * dp;					// Directory stream to hold directory name..... (Why can't it just take a c string?)
	std::string tempname = "";			// Used to store the filename / subdirectory name for the addToArray function.

	// Allocate the dirlist.
	try{
		buffer = new FileUtills::dirlist;
	}
	catch(bad_alloc)
	{
		// Could not allocate struct.
		return NULL;
	}

	// Set the path.
	buffer->path = path;

	// Dump the path as a c string into the Directory stream object......(Overly complicated POS......)

	// Check and make sure we can open the directory first.
	if ((dp = (opendir(path.c_str()))) == NULL)
	{
		// An error occured.
		if (buffer != NULL)
		{
			delete buffer;
			buffer = NULL;
		}

		// Exit function.
		return NULL;
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
		buffer->list.push_back(tempname);
	}

	// Close the directory stream and reset it.
	closedir(dp);

	// If we are cleaning the list, call DataProcess::DecrementingSort().
	if (DataProcess::DecrementingSort(buffer->list) != 0)
	{
		// An exception was thrown in the DecrementingSort() function, bail out.
		if (buffer != NULL)
		{
			delete buffer;
			buffer = NULL;
		}

		// Exit function.
		return NULL;
	}

	// Set the number of entries.
	buffer->numOfEntries = buffer->list.size();

	// Return the buffer.
	return buffer;
#endif
	// Default return for unimplemted function.
	return NULL;
}

short FileUtills::GetGigaFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		}
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine gigabyte conversion.
	result = (free_blocks * block_size) / ((double)1000000000);

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif

	// Default return for unimplemented function.
	return -3;
}

short FileUtills::GetFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		}
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine megabyte conversion.
	result = (free_blocks * block_size) / ((double)(1000000));

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif
	// Default return for unimplemented function.
	return -3;
}

short FileUtills::GetKiloFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		}
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine byte conversion.
	result = ((free_blocks * block_size) / ((double)(1000)));

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif
	// Default return for unimplemented function.
	return -3;
}

short FileUtills::GetByteFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		};
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine byte conversion.
	result = (free_blocks * block_size);

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif
	// Default return for unimplemented function.
	return -3;
}

short FileUtills::CreateDirectory(const std::string & directory, Panic::ERROR & error, const bool & createRecursive)
{
#ifdef POSIX_COMMON_H
	// Init vars.
	std::string buffer = ""; 		// Used to store the current directory path.
	std::string parentbuffer = "";	// Used to store the parent directory's path.
	std::string realpath = "";		// Used to store the real directory path if a relative path or a user path is given instead of an absolute path.
	int errorcode = 0;			    // Used to store return error codes.
	size_t position = 0;			// Used to store current search position in buffer.
	size_t size = 0;			    // Used to store the size of the path string
	int permission = 0;			    // Used to store return code from FileUtills::CheckPermissions().
	bool skiploop = false;			// Used to control the recursive directory creation loop.
	bool isrelative = false;		// Used to tell if the path is relative or abosulute.
	bool isHome = false;			// Used to tell if the path is in a user's home directory.
	char charArray[1000];			// Used for the cwd function.
	char * pCWD;				    // Used to store result of the getCWD function.

    	// Check to see if the full directory path already exists.
	if (FileUtills::DoesExist(directory, error) == true)
	{
	    // Directory already exists thus return true.
	    return -3;
	}

	// Check for a directory seperator on the end of the path and remove it if it is found.
	buffer = RemoveTrailingSlash(directory);

	// Get the size of the buffer string.
	size = buffer.size();

	// Determine if we have a relative path or a absolute one.
	if (buffer.find_first_of(DIR_SEP) == 0)
	{
		isrelative = false;
	}

	if (buffer.find("./") == 0) // BUG: this should not be called when string != "./"<some path>.
	{
		// Ok relative path get the full path
		isrelative = true;
		pCWD = getcwd(charArray, sizeof(charArray));
		buffer = pCWD;

		buffer += directory.substr(1, size);

		// Remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the realpath.
		realpath = buffer;

	}

	// Also check if it's in a user's home subdirectory.
	if (buffer.find_first_of('~') == 0)
	{
		// Ok user path, get the full path.
		isHome = true;
		pCWD = getenv("HOME");
		buffer = pCWD;
		buffer += directory.substr(1, size);

		// remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the real path.
		realpath = buffer;
	}

	// Assume relative if we have something else here.
	if (buffer.find_first_of(DIR_SEP) != 0 && isHome == false && isrelative == false) // BUG: This does not get called.
	{
		// Set isrelative to true and retrive the current working directory.
		isrelative = true;
		pCWD = getcwd(charArray, sizeof(charArray));
		buffer = pCWD;

		// Add a DIR_SEP to the string or we will mess up the directory name.
		buffer += DIR_SEP;

		// Add all data from the Directory string because the string does not have a DIR_SEP at position zero.
		buffer += directory.substr(0, size);

		// Remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the realpath.
		realpath = buffer;
	}

	// Get the parent directory out of the buffer and store it for later.
	position = buffer.find_last_of(DIR_SEP);
	parentbuffer = buffer.substr(0, position);

	 // Check and see if the parent directory exists.
	errorcode = FileUtills::CheckParent(directory);	// Switch

	switch (errorcode) {
      case -1:  // Can't write to the parent directory exit the function.
        error.PanicHandler("FileUtills::CreateDirectory : Parent Directory not writable. will not create directory.");
		return -1;
		permission = 0;
        break;
	  case -2:  // Parent Directory does not exist,
	    if (createRecursive == false)
	    {
                // Don't create the directory structure.
                error.PanicHandler("FileUtills::CreateDirectory : Parent Directory does not exist. createRecursive is false, will not create directory.");
                return -2;
	    }
	    break;

	  case 0:  // Parent Directory does exist and is writeable.
        // since we can write to the directory skip the loop.
		skiploop = true;
		break;
      default: // Ether there was an unknown error or this Arch / OS is not supported. ether way return -4.
	    return -4;
	    errorcode = 0;
	    break;
	}

	// Clear the vars for the recursive directory creation loop.
	permission = 0;
	position = 0;
	errorcode = 0;

	// Set buffer so we can check the path correctly.
	// If we have a relative or user path use the real path.
	if (isHome == true || isrelative == true)
	{
		buffer = realpath.substr(0, (realpath.find_first_of( DIR_SEP , 1)));

		// Also set the size of the string correctly.
		size = realpath.size();
	}
	else
	{
		// Otherwise use the directory string.
		buffer = directory.substr(0, (directory.find_first_of( DIR_SEP, 1)));

		// Also set the size of the string correctly.
		size = directory.size();
	}

	// If the parent directory does not exist and createRecursive is true then begin main loop.
	while (skiploop != true)
	{
		// If we are at position 0 and there is a DIR_SEP there incremnt position by one.
		if (position == 0 && buffer.find_first_of(DIR_SEP) == 0)
		{
			// Incremnt the position by one.
			position++;
		}

		// Start with root directory and run though the following until we reach the requested directory.

		if (isHome == true || isrelative == true)	// If true use realpath
		{
			if ((position = realpath.find_first_of(DIR_SEP, position)) == string::npos)
			{
				// This is the requested directory so exit the loop.
				skiploop = true;
				break;
			}
		}
		else 		// Otherwise use directory.
		{
			if ((position = directory.find_first_of(DIR_SEP, position)) == string::npos)
			{
				// This is the requested directory so exit the loop.
				skiploop = true;
				break;
			}
		}

		// Do a sanity check for the size of the string.
		if (position < 0 || position > size)
		{
			// Ok something went wrong.
			return -4;
		}

		// Dump the last buffer into the parentdirectory buffer.
		parentbuffer = buffer;

		// Cut up the directory string so we can check for it.

		if (isHome == true || isrelative == true)
		{
			buffer = realpath.substr(0, position);
		}
		else
		{
			buffer = directory.substr(0, position);
		}

		// Do Check.
		errorcode = FileUtills::DoesExist(buffer, error);

		switch (errorcode){
		  case -1:		// Directory does not exist on system.
		    // Check and see if we can create it.
		    permission = FileUtills::CheckPermissions(parentbuffer, error);

		    switch (permission){
		      case -1:
			// Permission Check Failed.
			return false;
			break;

		      case 0:
			// Ok try and create the directory.
			if ((errorcode = (mkdir(buffer.c_str(), S_IRWXU))) != 0)
			{
				// An error ocurred find out what.

				switch (errno) {
				  case EACCES:		// Permission error.
				    return -1;
				    break;
				  case EEXIST:		// Path exists on system.
				    return -3;
				    break;
				  case ENOSPC:		// Out of disk space.
				    return -2;
				    break;
				  default:		// We really don't care about the other errors.
				    return -4;
				    break;
				}
			}

			// Update the position counter.
			position++;

			// Check and see if that was the last directory to create.
			if (isHome == true || isrelative == true)
			{
				// Check realpath.
				if (buffer == realpath)
				{
				  skiploop = true;
				  return 0;
				}
			}
			// Otherwise check the directory buffer.
			if (buffer == directory)
			{
				skiploop = true;
				return 0;
			}
			break;

		      default:
			// Bad errorcode exit function.
			return -4;
			break;
		    }
		    permission = 0;
		    errorcode = 0;
		    break;

		  case 0:		// Ok directory does exist.
		    position++;
		    break;

		  default:
		    // Bad error code exit function.
		    return -4;
		}



		// If the next directory does exist then skip the remaining portion of the checks and restart with the next directory.

		// If the next directory does not exist the check the permissions of this one.

			// If we can write to this directory then create the directory.

				// If the directory creation was successful then check and see what to do next.

					// If we have created the requested directory exit the function
					//return true.

					// If we have not created the requested directory contiune loop with the next
					// directory.

				// If we encountered a fatal error exit the function return false.

			// If we can't write to this directory exit the function, return false.

			// If the permission check fails with a fatal error exit the function return false.

		// If the existance check fails exit the function, return false.
	}



	//If we have a relative or user path use realpath.
	if (isHome == true || isrelative == true)
	{
		buffer = realpath;
	}
	else // Otherwise use the directory string.
	{

		buffer = directory;
	}

	// Ok try and create the directory.
	if ((errorcode = (mkdir(buffer.c_str(), S_IRWXU))) != 0)
	{
		// An error ocurred find out what.

		switch (errno) {
		  case EACCES:		// Permission error.
		    return -1;
		    break;
		  case EEXIST:		// Path exists on system.
		    return -5;
		    break;
		  case ENOSPC:		// Out of disk space.
		    return -4;
		    break;
		  default:		// We really don't care about the other errors.
		    return -6;
		    break;
		}
	}
	if (errorcode == 0)
	{
		return 0;
	}
#endif
	// If an implemetation does not exist for this platform then exit the function, return false.
	return -3;
}

short FileUtills::CreateDirectory(const std::string & directory, const bool & createRecursive)
{
#ifdef POSIX_COMMON_H
	// Init vars.
	std::string buffer = ""; 		// Used to store the current directory path.
	std::string parentbuffer = "";	// Used to store the parent directory's path.
	std::string realpath = "";		// Used to store the real directory path if a relative path or a user path is given instead of an absolute path.
	int errorcode = 0;			    // Used to store return error codes.
	size_t position = 0;			// Used to store current search position in buffer.
	size_t size = 0;			    // Used to store the size of the path string
	int permission = 0;			    // Used to store return code from FileUtills::CheckPermissions().
	bool skiploop = false;			// Used to control the recursive directory creation loop.
	bool isrelative = false;		// Used to tell if the path is relative or abosulute.
	bool isHome = false;			// Used to tell if the path is in a user's home directory.
	char charArray[1000];			// Used for the cwd function.
	char * pCWD;				    // Used to store result of the getCWD function.

    	// Check to see if the full directory path already exists.
	if (FileUtills::DoesExist(directory) == true)
	{
	    // Directory already exists thus return true.
	    return -3;
	}

	// Check for a directory seperator on the end of the path and remove it if it is found.
	buffer = RemoveTrailingSlash(directory);

	// Get the size of the buffer string.
	size = buffer.size();

	// Determine if we have a relative path or a absolute one.
	if (buffer.find_first_of(DIR_SEP) == 0)
	{
		isrelative = false;
	}

	if (buffer.find("./") == 0) // BUG: this should not be called when string != "./"<some path>.
	{
		// Ok relative path get the full path
		isrelative = true;
		pCWD = getcwd(charArray, sizeof(charArray));
		buffer = pCWD;

		buffer += directory.substr(1, size);

		// Remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the realpath.
		realpath = buffer;

	}

	// Also check if it's in a user's home subdirectory.
	if (buffer.find_first_of('~') == 0)
	{
		// Ok user path, get the full path.
		isHome = true;
		pCWD = getenv("HOME");
		buffer = pCWD;
		buffer += directory.substr(1, size);

		// remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the real path.
		realpath = buffer;
	}

	// Assume relative if we have something else here.
	if (buffer.find_first_of(DIR_SEP) != 0 && isHome == false && isrelative == false) // BUG: This does not get called.
	{
		// Set isrelative to true and retrive the current working directory.
		isrelative = true;
		pCWD = getcwd(charArray, sizeof(charArray));
		buffer = pCWD;

		// Add a DIR_SEP to the string or we will mess up the directory name.
		buffer += DIR_SEP;

		// Add all data from the Directory string because the string does not have a DIR_SEP at position zero.
		buffer += directory.substr(0, size);

		// Remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the realpath.
		realpath = buffer;
	}

	// Get the parent directory out of the buffer and store it for later.
	position = buffer.find_last_of(DIR_SEP);
	parentbuffer = buffer.substr(0, position);

	 // Check and see if the parent directory exists.
	errorcode = FileUtills::CheckParent(directory);	// Switch

	switch (errorcode) {
      case -1:  // Can't write to the parent directory exit the function.
		return -1;
		permission = 0;
        break;
	  case -2:  // Parent Directory does not exist,
	    if (createRecursive == false)
	    {
                // Don't create the directory structure.
                return -2;
	    }
	    break;

	  case 0:  // Parent Directory does exist and is writeable.
        // since we can write to the directory skip the loop.
		skiploop = true;
		break;
      default: // Ether there was an unknown error or this Arch / OS is not supported. ether way return -4.
	    return -4;
	    errorcode = 0;
	    break;
	}

	// Clear the vars for the recursive directory creation loop.
	permission = 0;
	position = 0;
	errorcode = 0;

	// Set buffer so we can check the path correctly.
	// If we have a relative or user path use the real path.
	if (isHome == true || isrelative == true)
	{
		buffer = realpath.substr(0, (realpath.find_first_of( DIR_SEP , 1)));

		// Also set the size of the string correctly.
		size = realpath.size();
	}
	else
	{
		// Otherwise use the directory string.
		buffer = directory.substr(0, (directory.find_first_of( DIR_SEP, 1)));

		// Also set the size of the string correctly.
		size = directory.size();
	}

	// If the parent directory does not exist and createRecursive is true then begin main loop.
	while (skiploop != true)
	{
		// If we are at position 0 and there is a DIR_SEP there incremnt position by one.
		if (position == 0 && buffer.find_first_of(DIR_SEP) == 0)
		{
			// Incremnt the position by one.
			position++;
		}

		// Start with root directory and run though the following until we reach the requested directory.

		if (isHome == true || isrelative == true)	// If true use realpath
		{
			if ((position = realpath.find_first_of(DIR_SEP, position)) == string::npos)
			{
				// This is the requested directory so exit the loop.
				skiploop = true;
				break;
			}
		}
		else 		// Otherwise use directory.
		{
			if ((position = directory.find_first_of(DIR_SEP, position)) == string::npos)
			{
				// This is the requested directory so exit the loop.
				skiploop = true;
				break;
			}
		}

		// Do a sanity check for the size of the string.
		if (position < 0 || position > size)
		{
			// Ok something went wrong.
			return -4;
		}

		// Dump the last buffer into the parentdirectory buffer.
		parentbuffer = buffer;

		// Cut up the directory string so we can check for it.

		if (isHome == true || isrelative == true)
		{
			buffer = realpath.substr(0, position);
		}
		else
		{
			buffer = directory.substr(0, position);
		}

		// Do Check.
		errorcode = FileUtills::DoesExist(buffer);

		switch (errorcode){
		  case -1:		// Directory does not exist on system.
		    // Check and see if we can create it.
		    permission = FileUtills::CheckPermissions(parentbuffer);

		    switch (permission){
		      case -1:
			// Permission Check Failed.
			return false;
			break;

		      case 0:
			// Ok try and create the directory.
			if ((errorcode = (mkdir(buffer.c_str(), S_IRWXU))) != 0)
			{
				// An error ocurred find out what.

				switch (errno) {
				  case EACCES:		// Permission error.
				    return -1;
				    break;
				  case EEXIST:		// Path exists on system.
				    return -3;
				    break;
				  case ENOSPC:		// Out of disk space.
				    return -2;
				    break;
				  default:		// We really don't care about the other errors.
				    return -4;
				    break;
				}
			}

			// Update the position counter.
			position++;

			// Check and see if that was the last directory to create.
			if (isHome == true || isrelative == true)
			{
				// Check realpath.
				if (buffer == realpath)
				{
				  skiploop = true;
				  return 0;
				}
			}
			// Otherwise check the directory buffer.
			if (buffer == directory)
			{
				skiploop = true;
				return 0;
			}
			break;

		      default:
			// Bad errorcode exit function.
			return -4;
			break;
		    }
		    permission = 0;
		    errorcode = 0;
		    break;

		  case 0:		// Ok directory does exist.
		    position++;
		    break;

		  default:
		    // Bad error code exit function.
		    return -4;
		}



		// If the next directory does exist then skip the remaining portion of the checks and restart with the next directory.

		// If the next directory does not exist the check the permissions of this one.

			// If we can write to this directory then create the directory.

				// If the directory creation was successful then check and see what to do next.

					// If we have created the requested directory exit the function
					//return true.

					// If we have not created the requested directory contiune loop with the next
					// directory.

				// If we encountered a fatal error exit the function return false.

			// If we can't write to this directory exit the function, return false.

			// If the permission check fails with a fatal error exit the function return false.

		// If the existance check fails exit the function, return false.
	}



	//If we have a relative or user path use realpath.
	if (isHome == true || isrelative == true)
	{
		buffer = realpath;
	}
	else // Otherwise use the directory string.
	{

		buffer = directory;
	}

	// Ok try and create the directory.
	if ((errorcode = (mkdir(buffer.c_str(), S_IRWXU))) != 0)
	{
		// An error ocurred find out what.

		switch (errno) {
		  case EACCES:		// Permission error.
		    return -1;
		    break;
		  case EEXIST:		// Path exists on system.
		    return -5;
		    break;
		  case ENOSPC:		// Out of disk space.
		    return -4;
		    break;
		  default:		// We really don't care about the other errors.
		    return -6;
		    break;
		}
	}
	if (errorcode == 0)
	{
		return 0;
	}
#endif
	// If an implemetation does not exist for this platform then exit the function, return false.
	return -3;
}

int FileUtills::CheckPermissions(const std::string & Filename, Panic::ERROR & error, bool read, bool write)
{
	// Double check and make sure we have something to do.
	if (read == false && write == false)
	{
		// Ok what? Call PanicHandler.
		error.PanicHandler("FileUtills::CheckPermissions : CheckPermissions called but no permissions to check due to args. Returning -3");

		// Return -3
		return -3;
	}

#ifdef POSIX_COMMON_H
	//init vars
	int errorcode = 0;

	// Find out if file or directory exists
	if ((errorcode = DoesExist(Filename, error)) == -1)
	{
		// File does not exist return -2.
		return -2;
	}

	// Also check and make sure no other error occured.
	if (errorcode == -2)
	{
		// Something went wrong with DoesExist return -3.
		return -3;
	}

	// Reset errorcode
	errorcode = 0;

	// DoesExist returned ok, Begin check
	if (read == true && write == false)
	{
		// Check for read only permission.
		errorcode = access(Filename.c_str(), R_OK);
		if (errorcode != 0)
		{
			// File or Directory is not readable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable return 0.
			return 0;
		}

		// Unknown error call Panic Handler
		error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during read permission check. Returning -3");
		return -3;
	}

	if (read == false && write == true)
	{
		// Check for write only permission. (odd but for rundundantcy.)
		errorcode = access(Filename.c_str(), W_OK);

		if (errorcode != 0)
		{
			// File or Directory is not writeable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is writeable return 0.
			return 0;
		}

		// Unknown error call Panic Handler
		error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during write permission check. Returning -3");
		return -3;
	}

	if (read == true && write == true)
	{
		// Check for read and write permissions.
		errorcode = access(Filename.c_str(), R_OK);
		if (errorcode != 0)
		{
		    // File or directory is not readable. it has failed one critera for check, return -1.
		    return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable check for write permission.
			errorcode = access(Filename.c_str(), W_OK);

			if (errorcode != 0)
			{
				// File or Directory is not writeable return -1
				return -1;
			}
			if (errorcode == 0)
			{
				// File or directory is writeable return 0.
				return 0;
			}
			else
			{
				// Unknown error call panic handler.
				error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during write permission check. Returning -3");
				return -3;
			}
		}
		else
		{
			// Unknown error call panic handler.
			error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during read permission check. Returning -3");
			return -3;
		}
	}

#endif
  // Call Panic Handler there is no OS / arch impilmentation.
  error.PanicHandler("FileUtills::CheckPermissions : OS / arch not supported. No Implementation found. Returning -3.");

  // Default Return
  return -3;
}


int FileUtills::CheckPermissions(const std::string & path, bool read, bool write)
{
	// Double check and make sure we have something to do.
	if (read == false && write == false)
	{
		// Return -3
		return -3;
	}

#ifdef POSIX_COMMON_H
	//init vars
	int errorcode = 0;

	// Find out if file or directory exists
	if ((errorcode = DoesExist(path)) == -1)
	{
		// File does not exist return -2.
		return -2;
	}

	// Also check and make sure no other error occured.
	if (errorcode == -2)
	{
		// Something went wrong with DoesExist return -3.
		return -3;
	}

	// Reset errorcode
	errorcode = 0;

	// DoesExist returned ok, Begin check
	if (read == true && write == false)
	{
		// Check for read only permission.
		errorcode = access(path.c_str(), R_OK);
		if (errorcode != 0)
		{
			// File or Directory is not readable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable return 0.
			return 0;
		}
        // Unknown error
		return -3;
	}

	if (read == false && write == true)
	{
		// Check for write only permission. (odd but for rundundantcy.)
		errorcode = access(path.c_str(), W_OK);

		if (errorcode != 0)
		{
			// File or Directory is not writeable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is writeable return 0.
			return 0;
		}

		// Unknown error
		return -3;
	}

	if (read == true && write == true)
	{
		// Check for read and write permissions.
		errorcode = access(path.c_str(), R_OK);
		if (errorcode != 0)
		{
		    // File or directory is not readable. it has failed one critera for check, return -1.
		    return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable check for write permission.
			errorcode = access(path.c_str(), W_OK);

			if (errorcode != 0)
			{
				// File or Directory is not writeable return -1
				return -1;
			}
			if (errorcode == 0)
			{
				// File or directory is writeable return 0.
				return 0;
			}
			else
			{
				// Unknown error
				return -3;
			}
		}
		else
		{
			// Unknown error
			return -3;
		}
	}

#endif
  // there is no OS / arch impilmentation return default.
  // Default Return
  return -3;
}


int FileUtills::DoesExist(const std::string & Filename, Panic::ERROR & error)
{
#ifdef POSIX_COMMON_H

    // Declare some vars.
    int errorcode = 0; // Holds error number.

    // Check and see if the file exists.
    errorcode = access(Filename.c_str(), F_OK);

    // Get error code.
    if (errorcode == 0)
    {
	// File exists return ok
	return 0;
    }
    if (errorcode == -1)
    {
	// File does not exist return false.
	return -1;
    }
    else
    {
	// Ok What happened? Call PanicHandler
	error.PanicHandler("FileUtills::DoesExist : Unknown Error, returning false on file exist check.");
    }
#endif
  // Call Panic Handler arch / OS not supported.
  error.PanicHandler("FileUtils::DoesExist : OS / arch not supported. No Implementation found. Returning -2.");

  // Default return.
  return -2;
}

int FileUtills::DoesExist(const std::string & Filename)
{
#ifdef POSIX_COMMON_H

    // Declare some vars.
    int errorcode = 0; // Holds error number.

    // Check and see if the file exists.
    errorcode = access(Filename.c_str(), F_OK);

    // Get error code.
    if (errorcode == 0)
    {
	// File exists return ok
	return 0;
    }
    if (errorcode == -1)
    {
	// File does not exist return false.
	return -1;
    }
    else
    {
        // Unknown error return false.
        return -1;
    }
#endif
  // arch / OS not supported.

  // Default return.
  return -2;
}

int FileUtills::IsFileOrDirectory(const std::string & path)
{
        // Make sure that the path is not empty.
        if (path.size() <= 0)
        {
                // Empty path.
                return -5;
        }

#ifdef POSIX_COMMON_H
        // Init vars.
        int result = 0;
        int call_result = 0;
        struct stat * buf = NULL;

        // Init stat buffer.
        buf = new struct stat;

        // Ask the OS to stat() the path.
        call_result = stat(path.c_str(), buf);

        // Check the result.
        if (call_result == 0)
        {
                // Check the stat structure.
                if (S_ISREG((buf->st_mode)))
                {
                        // Path is a regular file.
                        result = 1;
                }
                else
		{
			if (S_ISDIR((buf->st_mode)))
			{
				// Path is a directory.
				result = 2;
			}
		}
        }
        else
	{
		// Error, see if it was a permissions error.
		switch (errno)
		{
			case EACCES:
			    // Permissions error.
			    result = -4;
			    break;
			case ENOENT:
			    // A path componet does not exist.
			    result = -6;
			    break;
			case ENOTDIR:
			    // Path has a file in it, and is not the final componet.
			    result = -7;
			    break;
			default:
			    // Some other error.
			    result = -9;
			    break;
		};
	}

        // Delete stat buffer.
        delete buf;
        buf = NULL;

        // Exit function.
        return result;
#endif

        // System unsupported, why not add support for it? :)
        return -3;
}

int FileUtills::CheckParent(const std::string & path, bool read, bool write)
{
#ifdef POSIX_COMMON_H
    // Init vars
    std::string parentbuffer = "";
    long int length = 0;
    long int location = 0;
    int result = 0;

    // Remove the trailing slash if present.
    parentbuffer = RemoveTrailingSlash(path);

    // Check the Path for absolute path.
    parentbuffer = FileUtills::CheckPathType(parentbuffer);

    // Check the length of the path.
    length = parentbuffer.length();

    // Check and see if the length is zero.
    if (length == 0)
    {
        // Nothing to do so return that the path does not exist. (It clearly does not exist.)
        return -2;
    }

    // Locate the path seperator before the last directory / file name.
    location = parentbuffer.find_last_of(DIR_SEP);

    // Check and make sure that the location of the dir sep is inside the string
    if (location > length || length < 0 ||  location < 0)
    {
        // Memory error or someone is fucking with us.
        // Either way kill the function
        return -5;
    }

    // Check and see if the parentbuffer is a root directory
    if (length > 1)
    {

        // Get the parent directory path.
        // Note substr CAN throw an exception. so we need to put this in a try catch block.
        try{
            parentbuffer = parentbuffer.substr(0, location);
        }
        catch(exception &ex)
        {
            // If we end up here we're in trouble.
            // Kill the function to be safe.
            return -5;
        }

        // Now rerun the check for a dir sep on the end.
        parentbuffer = RemoveTrailingSlash(parentbuffer);
    }

    // Call the other functions
    result = FileUtills::CheckPermissions(parentbuffer, read, write);

    // Check the result
    switch (result)
    {
        // Successful
        case 0:
            return 0;
            break;
        // Permission error
        case -1:
            return -1;
            break;
        // Parent Does not exist
        case -2:
            return -2;
            break;
        // Unknown error (Probabliy a memory error)
        default:
            return -5;
            break;
    };
#endif
  // arch / OS not supported.
  return -3;
}

std::string FileUtills::GetParent(const std::string & path)
{
    // Init vars.
    std::string parentbuffer = "";
    long int length = 0;
    long int location = 0;

#ifdef POSIX_COMMON_H
    // Remove the trailing slash if present.
    parentbuffer = RemoveTrailingSlash(path);

    // Check the Path for absolute path.
    parentbuffer = FileUtills::CheckPathType(parentbuffer);

    // Check the length of the path.
    length = parentbuffer.length();

    // Check and see if the length is zero.
    if (length == 0)
    {
        // Nothing to do so return that the path does not exist. (It clearly does not exist.)
        parentbuffer = "";
        return parentbuffer;
    }

    // Locate the path seperator before the last directory / file name.
    location = parentbuffer.find_last_of(DIR_SEP);

    // Check and make sure that the location of the dir sep is inside the string
    if (location > length || length < 0 ||  location < 0)
    {
        // Memory error or someone is fucking with us.
        // Either way kill the function
        parentbuffer = "";
        return parentbuffer;
    }

    // Check and see if the parentbuffer is a root directory
    if (length > 1)
    {
        // Get the parent directory path.
        // Note substr CAN throw an exception. so we need to put this in a try catch block.
        try{
            parentbuffer = parentbuffer.substr(0, location);
        }
        catch(exception &ex)
        {
            // If we end up here we're in trouble.
            // Kill the function to be safe.
            parentbuffer = "";
            return parentbuffer;
        }

        // Now rerun the check for a dir sep on the end.
        parentbuffer = RemoveTrailingSlash(parentbuffer);

        // Exit function.
        return parentbuffer;

    }
#endif
  // arch / OS not supported.
  parentbuffer = "";
  return parentbuffer;

}

short FileUtills::DeletePath(const std::string & path, const bool & recursive)
{
#ifdef POSIX_COMMON_H
        // Init vars.
        bool done = false;                              // Used to know when to exit the recursive iterator loop.
        bool resetIterLoop = false;                     // Used to control resetting the recursive iterator loop.
        bool unableToDeleteAll = false;                 // Used to tell if we could not delete something while deleting recursively.
        int result = 0;                                 // Used to store results from calls to other functions.
        size_t x = 0;                                   // Used by the recursion loop, for accessing the directory list.
        std::string currentabspath = "";                // Used to contain the current absolute path.
        std::string dummy = "";                         // Used to construct temporary paths.
        FileUtills::dirlist * plist = NULL;             // Used to store paths for recursive deletions.
        std::vector<std::string>::iterator iter;        // plist->list (Directory Listing).
        std::vector<size_t> directory_offsets;          // Used to store the offsets in the directory listings.

        // Check and see if the file can be erased.
        result = FileUtills::CheckPermissions(path);

        // Attempt to delete the path if the OS permissions allow it.
        if (result == 0)
        {
                // Call removal function.
                if (remove(path.c_str()) != 0)
                {
                        // Check the error.
                        if (errno == EACCES)
                        {
                                // Permissions error.
                                return -1;
                        }
                        if (errno == EPERM)
                        {
                                // Permissions error.
                                return -1;
                        }
                        if (errno == ENOTEMPTY) // Path is a non empty directory.
                        {
                                // If we have recursive set to true we can delete the path, else return an error.
                                if (recursive)
                                {
                                        // Copy the src path to the currentabspath var.
                                        currentabspath = path;

                                        // Begin recursion loop.
                                        do
                                        {
                                                // OK we need to get the paths of every file in the directory and any other directories.
                                                plist = NULL;
                                                plist = FileUtills::getDirectory(currentabspath, true);
                                                if (plist == NULL)
                                                {
                                                        // Could not get directory list.
                                                        if (plist != NULL)
                                                        {
                                                                delete plist;
                                                                plist = NULL;
                                                        }
                                                        return -4;
                                                }

                                                // Reset the iter just to be safe.
                                                iter = plist->list.begin();

                                                // Check and see if the directory offset list has anything in it.
                                                if ((!resetIterLoop) && (directory_offsets.size() > 0))
                                                {
                                                        // We have an offset, so init x to that offset.
                                                        x = directory_offsets[(directory_offsets.size() - 1)];      // size() returns the number of valid elements in the vector.

                                                        // Fix the iterator.
                                                        iter = iter + x;

                                                        // Erase the offset from the vector.
                                                        directory_offsets.erase((directory_offsets.end() - 1));     // end() returns the position after the last valid element in the vector.
                                                }
                                                else
                                                {
                                                        // We don't have any offsets, (or we just switched to a subdirectory) so init x to zero.
                                                        x = 0;

                                                        // Unset resetIterLoop.
                                                        resetIterLoop = false;
                                                }

                                                // Begin loop to check for more subdirectories.
                                                for (; x < plist->list.size(); x++)
                                                {
                                                        // Create temp path.
                                                        dummy.clear();
                                                        dummy = currentabspath + DIR_SEP + (plist->list[x]);
                                                        dummy = RemoveTrailingSlash(dummy);     // If we got a DIR_SEP at the end of the string get rid of it.

                                                        // Check to see if the current entry in the list is a directory.
                                                        switch (FileUtills::IsFileOrDirectory(dummy))
                                                        {
                                                                case 0:         // Not a file or directory. (Try to remove anyway.)
                                                                case 1:         // File.
                                                                    // Attempt to delete file.
                                                                    if (remove(dummy.c_str()) != 0)
                                                                    {
                                                                            // Set unableToDeleteAll.
                                                                            unableToDeleteAll = true;

                                                                            /*
                                                                                Note: We need someway of keeping track of what
                                                                                files we've already attempted to delete,
                                                                                Otherwise we'll end up in an indefinte loop.

                                                                                The easist way to to have the list generated the same
                                                                                way each time and store the offsets. (I.e each call to
                                                                                FileUtills::getDirectory() returns the same list. As
                                                                                opposed to just the way the OS spits out the directory
                                                                                listing.)

                                                                                Then when the subdirectory is removed, (or after the failed removal
                                                                                attempt) find where that subdirectory was in the list and continue.
                                                                            */
                                                                    }
                                                                    break;
                                                                case 2:         // Directory.
                                                                    // Set currentabspath to this path.
                                                                    currentabspath = dummy;

                                                                    // Set the current directory list offset (x) in to the vector.
                                                                    directory_offsets.push_back(x);

                                                                    // Set reset flag.
                                                                    resetIterLoop = true;

                                                                    // Get out of this loop.
                                                                    break;
                                                                case -3:        // OS not supported.
                                                                    if (plist != NULL)
                                                                    {
                                                                            delete plist;
                                                                            plist = NULL;
                                                                    }
                                                                    return -3;
                                                                case -4:        // Permission error.
                                                                case -5:        // Arg error.
                                                                case -6:        // Path componet does not exist.
                                                                case -7:        // Part of path is a file.
                                                                case -9:        // Memory error.
                                                                default:
                                                                    // Set unableToDeleteAll.
                                                                    unableToDeleteAll = true;
                                                                    break;
                                                        };

                                                        // Check to see if reset flag is set.
                                                        if (resetIterLoop)
                                                        {
                                                                // Get out of this loop.
                                                                break;
                                                        }
                                                }

                                                // Check to see how the previous loop exited.
                                                if (!resetIterLoop)
                                                {
                                                        // Remove the directory.
                                                        if (remove(currentabspath.c_str()) != 0)
                                                        {
                                                                // Check and see if unableToDeleteAll was set. If it was set, we ignore this error.
                                                                if (!unableToDeleteAll)
                                                                {
                                                                        // Check the error.
                                                                        if (errno == EACCES)
                                                                        {
                                                                                // Permissions error.
                                                                                if (plist != NULL)
                                                                                {
                                                                                        delete plist;
                                                                                        plist = NULL;
                                                                                }
                                                                                return -1;
                                                                        }
                                                                        else
                                                                        {
                                                                                if (errno == EPERM)
                                                                                {
                                                                                        // Permissions error.
                                                                                        if (plist != NULL)
                                                                                        {
                                                                                                delete plist;
                                                                                                plist = NULL;
                                                                                        }
                                                                                        return -1;
                                                                                }
                                                                                else
                                                                                {
                                                                                        // Some other error.
                                                                                        if (plist != NULL)
                                                                                        {
                                                                                                delete plist;
                                                                                                plist = NULL;
                                                                                        }
                                                                                        return -5;
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
                                                                        // Increment the offset in the vector. (We have dealt with this subdirectory.)
                                                                        if (directory_offsets.size() > 0)
                                                                        {
                                                                                directory_offsets[(directory_offsets.size() - 1)] = (directory_offsets[(directory_offsets.size() - 1)] + 1);
                                                                        }
                                                                }
                                                        }

                                                        // Check to see if we removed the source dir.
                                                        if (currentabspath != path)
                                                        {
                                                                // Get the parent directory of currentabspath.
                                                                currentabspath = FileUtills::GetParent(currentabspath);
                                                                if (currentabspath.size() <= 0)
                                                                {
                                                                        // Could not get parent directory.
                                                                        if (plist != NULL)
                                                                        {
                                                                                delete plist;
                                                                                plist = NULL;
                                                                        }
                                                                        return -7;
                                                                }

                                                                // Delete the old plist.
                                                                if (plist != NULL)
                                                                {
                                                                        delete plist;
                                                                        plist = NULL;
                                                                }
                                                        }
                                                        else
                                                        {
                                                                // Delete the old plist.
                                                                if (plist != NULL)
                                                                {
                                                                        delete plist;
                                                                        plist = NULL;
                                                                }

                                                                // All directories have been deleted.
                                                                done = true;
                                                        }
                                                }
                                                else
                                                {
                                                        // Delete the old plist.
                                                        if (plist != NULL)
                                                        {
                                                                delete plist;
                                                                plist = NULL;
                                                        }
                                                }
                                        }while (!done);

                                        // Delete the plist.
                                        if (plist != NULL)
                                        {
                                                delete plist;
                                                plist = NULL;
                                        }

                                        // Clear dummy and currentabspath.
                                        dummy.clear();
                                        currentabspath.clear();

                                        // Flush the directory_offsets vector.
                                        directory_offsets.clear();

                                        // Check and see if the unableToDeleteAll flag is set.
                                        if (unableToDeleteAll)
                                        {
                                                // We can't delete some things so return an error.
                                                return -8;
                                        }
                                }
                                else
                                {
                                        // Path is not empty and we are not deleting recursively.
                                        return -6;
                                }
                        }
                        else
                        {
                                // Some other error.
                                return -5;
                        }
                }
        }
        else
        {
                // Determine the error.
                switch (result)
                {
                        // Permission BAD
                        case -1:
                            return -1;
                            break;
                        // Path does not exist
                        case -2:
                            return -2;
                            break;
                        // Either an unknown error or function is not supported
                        case -3:
                            return -3;
                            break;
                        // Possible memory error
                        default:
                            return -4;
                            break;
                };
        }

        // Exit function.
        return 0;
#endif
        // System not supported.
        return -3;
}

short FileUtills::CopyFile(const std::string & src, const std::string & dest, const bool & append, const streamsize & begOffset, const streamsize & endOffset)
{
        // Init vars.
        const short buffer_size = 512;                  // Constant used to determine the size of the file copy buffer.
        streamsize result = 0;                          // Used to hold the returned result of this function to the caller.
        streamsize count = 0;                           // Used while copying data to count the number of copied bytes.
        streamsize total_bytes_copied = 0;              // Holds the total amount of copied bytes.
        streamsize input_size = 0;                      // Holds the size of the input file.
        streamsize bytes_to_copy = 0;                   // Holds the total amount of bytes to copy from the input file.
        char * pBuffer = NULL;                          // Used as a buffer for copying data.
        fstream input;                                  // File stream for input file.
        fstream output;                                 // File stream for output file.

        // Check for invalid offsets.
        if ((begOffset < 0) || (endOffset < 0))
        {
                // Error, An offset is negative.
                result = -1;
        }
        else
        {
                // Check and make sure that the beginning offset is smaller than the ending offset.
                if (begOffset > endOffset)
                {
                        // Offsets are out of order.
                        result = -5;
                }
                else
                {
                        // Check the source file name length.
                        if (src.size() <= 0)
                        {
                                // Invalid source file name.
                                result = -10;
                        }
                        else
                        {
                                // Check to see if src is a directory.
                                result = FileUtills::IsFileOrDirectory(src);
                                if (result == 2)
                                {
                                        // Src is a directory, do not continue.
                                        result = -17;
                                }
                                else
                                {
                                        // Check for negative return code.
                                        if (result < 0)
                                        {
                                                // IsFileOrDirectory() returned an error.
                                                switch (result)
                                                {
                                                        case -3:
                                                            // IsFileOrDirectory() is not supported on this system.
                                                            result = -33;
                                                            break;
                                                        case -4:
                                                            // A permissions error occured.
                                                            result = -34;
                                                            break;
                                                        case -5:
                                                            // The given path is empty.
                                                            result = -35;
                                                            break;
                                                        case -6:
                                                            // A path componet does not exist.
                                                            result = -36;
                                                            break;
                                                        case -7:
                                                            // The path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
                                                            result = -37;
                                                            break;
                                                        default:
                                                            // All other errors.
                                                            result = -39;
                                                            break;
                                                };
                                        }
                                        else
                                        {
                                                // Attempt to open the file.
                                                input.open(src.c_str(), ios::in | ios::binary);
                                                if (!input.is_open())
                                                {
                                                        // Could not open file.
                                                        result = -11;
                                                }
                                                else
                                                {
                                                        // Get file size.
                                                        input.seekg(0, ios::end);
                                                        input_size = input.tellg();
                                                        input.seekg(0, ios::beg);

                                                        // Determine if the input file has the needed amount of bytes to copy.
                                                        if (input_size < begOffset)
                                                        {
                                                                // Input file is smaller than the beginning offset.
                                                                result = -12;
                                                        }
                                                        else
                                                        {
                                                                if (input_size < endOffset)
                                                                {
                                                                        // Input file is smaller than the ending offset.
                                                                        result = -13;
                                                                }
                                                                else
                                                                {
                                                                        // Check to see if we are copying the entire file.
                                                                        if ((begOffset == 0) && (endOffset == 0))   // Shortcut so the caller does not need to know the size of the file.
                                                                        {
                                                                                // We are copying the entire file.
                                                                                bytes_to_copy = input_size;
                                                                        }
                                                                        else
                                                                        {
                                                                                // Calculate the total amount of bytes to copy.
                                                                                bytes_to_copy = endOffset - begOffset;

                                                                                // Seek to the beginning offset in the source file.
                                                                                input.seekg(begOffset, ios::beg);
                                                                        }

                                                                        // Check the length of the dest.
                                                                        if (dest.size() <= 0)
                                                                        {
                                                                                // Invalid dest path.
                                                                                result = -20;
                                                                        }
                                                                        else
                                                                        {
                                                                                // Check and see if dest is a directory.
                                                                                result = FileUtills::IsFileOrDirectory(dest);
                                                                                if (result == 2)
                                                                                {
                                                                                        // Dest is a directory, abort.
                                                                                        result = -27;
                                                                                }
                                                                                else
                                                                                {
                                                                                        // Check for negative return code. (That is NOT the non existant file error.)
                                                                                        if ((result != -6) && (result < 0))
                                                                                        {
                                                                                                // IsFileOrDirectory() returned an error.
                                                                                                switch (result)
                                                                                                {
                                                                                                        case -3:
                                                                                                            // IsFileOrDirectory() is not supported on this system.
                                                                                                            result = -33;
                                                                                                            break;
                                                                                                        case -4:
                                                                                                            // A permissions error occured.
                                                                                                            result = -34;
                                                                                                            break;
                                                                                                        case -5:
                                                                                                            // The given path is empty.
                                                                                                            result = -35;
                                                                                                            break;
                                                                                                        case -6:
                                                                                                            // A path componet does not exist.
                                                                                                            result = -36;
                                                                                                            break;
                                                                                                        case -7:
                                                                                                            // The path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
                                                                                                            result = -37;
                                                                                                            break;
                                                                                                        default:
                                                                                                            // All other errors.
                                                                                                            result = -39;
                                                                                                            break;
                                                                                                };
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                // Check and see if we got the non existant file error from IsFileOrDirectory().
                                                                                                if (result == -6)
                                                                                                {
                                                                                                        // Reset result.
                                                                                                        result = 0;
                                                                                                }

                                                                                                // Open output file.
                                                                                                if (append)
                                                                                                {
                                                                                                        output.open(dest.c_str(), ios::in | ios::out | ios::binary | ios::app);
                                                                                                        output.seekg(0, ios::end);
                                                                                                        output.seekp(0, ios::end);
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        output.open(dest.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
                                                                                                }

                                                                                                // Check to see if the file is open.
                                                                                                if (!output.is_open())
                                                                                                {
                                                                                                        // Could not open output file.
                                                                                                        result = -21;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        // Begin try block.
                                                                                                        try{
                                                                                                                // Allocate memory buffer.
                                                                                                                pBuffer = (char*)malloc(buffer_size);
                                                                                                                if (pBuffer == NULL)
                                                                                                                {
                                                                                                                        // Could not allocate memory buffer.
                                                                                                                        result = -9;
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                        // Blank the buffer.
                                                                                                                        memset(pBuffer, '\0', buffer_size);

                                                                                                                        // Start copy loop.
                                                                                                                        while (total_bytes_copied < bytes_to_copy)
                                                                                                                        {
                                                                                                                                // Check the state of the file streams.
                                                                                                                                if (input.fail())
                                                                                                                                {
                                                                                                                                        // Input file stream error.
                                                                                                                                        if (input.bad())
                                                                                                                                        {
                                                                                                                                                // Read IO error.
                                                                                                                                                result = -14;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                                // Logical IO error.
                                                                                                                                                result = -15;
                                                                                                                                        }

                                                                                                                                        // Get out of the loop.
                                                                                                                                        break;
                                                                                                                                }
                                                                                                                                if (input.eof())
                                                                                                                                {
                                                                                                                                        // ??? We should not have hit eof....
                                                                                                                                        result = -16;

                                                                                                                                        // Get out of the loop.
                                                                                                                                        break;
                                                                                                                                }
                                                                                                                                if (output.fail())
                                                                                                                                {
                                                                                                                                        // Output file stream error.
                                                                                                                                        if (output.bad())
                                                                                                                                        {
                                                                                                                                                // Write IO error.
                                                                                                                                                result = -24;
                                                                                                                                        }
                                                                                                                                        else
                                                                                                                                        {
                                                                                                                                                // Logical IO error.
                                                                                                                                                result = -25;
                                                                                                                                        }

                                                                                                                                        // Get out of the loop.
                                                                                                                                        break;
                                                                                                                                }

                                                                                                                                // Check and see if the data remaining to copy is less than the buffer size.
                                                                                                                                if ((bytes_to_copy - total_bytes_copied) < buffer_size)
                                                                                                                                {
                                                                                                                                        // OK we only need to copy the remaining data.
                                                                                                                                        input.read(pBuffer, (bytes_to_copy - total_bytes_copied));
                                                                                                                                }
                                                                                                                                else
                                                                                                                                {
                                                                                                                                        // Fill up the buffer.
                                                                                                                                        input.read(pBuffer, buffer_size);
                                                                                                                                }

                                                                                                                                // Get the number of read bytes.
                                                                                                                                count = input.gcount();

                                                                                                                                // Write out the bytes to the output file.
                                                                                                                                output.write(pBuffer, count);

                                                                                                                                // Add the bytes copied to the total.
                                                                                                                                total_bytes_copied += count;
                                                                                                                        }

                                                                                                                        // Deallocate memory buffer.
                                                                                                                        memset(pBuffer, '\0', buffer_size);
                                                                                                                        if (pBuffer != NULL)
                                                                                                                        {
                                                                                                                                free(pBuffer);
                                                                                                                                pBuffer = NULL;
                                                                                                                        }
                                                                                                                }
                                                                                                        }
                                                                                                        catch(...)
                                                                                                        {
                                                                                                                // Exception thrown during copy loop.
                                                                                                                result = -99;
                                                                                                        }

                                                                                                        // Close output file.
                                                                                                        if (output.is_open())
                                                                                                        {
                                                                                                                output.close();
                                                                                                        }
                                                                                                }
                                                                                        }
                                                                                }
                                                                        }
                                                                }
                                                        }

                                                        // Close input file.
                                                        if (input.is_open())
                                                        {
                                                                input.close();
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }

        // Exit function.
        return result;
}

short FileUtills::CopyPath(const std::string & src, const std::string & dest, const bool & recursive,
						   const bool & rename, const bool & abort_on_failure,
						   const bool & append, const streamsize & begOffset, const streamsize & endOffset)
{
		// Init vars.
		bool done = false;				// Used to know when to exit the recursive iterator loop.
		bool resetIterLoop = false;			// Used to control resetting the recursive iterator loop.
		bool unableToCopyAll = false;			// Used to know if a file copy failed while recursively copying files.
		short result = 0;				// Used to store results from calls to other functions.
		std::string currentabspath_src = "";		// Used to contain the current absolute source path.
		std::string currentabspath_dest = "";		// Used to contain the current absolute destionation path.
		std::string src_path = "";			// Used to construct temporary source paths.
		std::string dest_path = "";			// Used to construct temporary destionation paths.
		size_t x = 0;					// Used by the recursion loop, for accessing the directory list.
		FileUtills::dirlist * plist = NULL;		// Used to store paths for recursive copying.
		std::vector<std::string>::iterator iter;	// plist->list (Directory Listing).
		std::vector<size_t> directory_offsets;		// Used to store the offsets in the directory listings.

		// Check and see if the src is a file or a directory.
		result = FileUtills::IsFileOrDirectory(src);
		if (result == 2)	// Directory.
		{
				// Copy the src path to the currentabspath_src and the dest path to the currentabspath_dest var.
				currentabspath_src = src;
				currentabspath_dest = dest;

				// OK, check and see if the dest directory exists.
				result = FileUtills::IsFileOrDirectory(currentabspath_dest);
				if (result == -6) // Directory does not exist.
				{
						// Create the dest directory.
						result = FileUtills::CreateDirectory(currentabspath_dest);
						if (result != 0)
						{
								// OK, we can't create the dest directory.
								result = -1;
						}
				}
				else
				{
						if (result == 2)		// Dest Directory exists.
						{
								// Set result to zero. (0)
								result = 0;
						}
						else
						{
								if (result >= 0)
								{
										// OK, dest is some file or other filesystem entry, so we can't copy a directory to it.
										result = -2;
								}
								else
								{
										// IsFileOrDirectory() returned an error.
										switch (result)
										{
                                                case -3:
                                                    // IsFileOrDirectory() is not supported on this system.
                                                    result = -13;
                                                    break;
                                                case -4:
                                                    // A permissions error occured.
                                                    result = -14;
                                                    break;
                                                case -5:
                                                    // The given path is empty.
                                                    result = -15;
                                                    break;
                                                case -6:
                                                    // A path componet does not exist.
                                                    result = -16;
                                                    break;
                                                case -7:
                                                    // The path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
                                                    result = -17;
                                                    break;
                                                default:
                                                    // All other errors.
                                                    result = -19;
                                                    break;
										};
								}
						}
				}

				// Make sure that result == 0. (I.e. that we can continue.)
				if (result == 0)
				{
						// Begin recursion loop.
						do
						{
								// OK we need to get the paths of every file in the directory and any other directories.
								plist = NULL;
								plist = FileUtills::getDirectory(currentabspath_src, true);
								if (plist == NULL)
								{
										// Could not get directory list.
										if (plist != NULL)
										{
												delete plist;
												plist = NULL;
										}
										result = -4;

										// Exit loop.
										done = true;
										break;
								}

								// Reset the iter just to be safe.
								iter = plist->list.begin();

								// Check and see if the directory offset list has anything in it.
								if ((!resetIterLoop) && (directory_offsets.size() > 0))
								{
										// We have an offset, so init x to that offset.
										x = directory_offsets[(directory_offsets.size() - 1)];      // size() returns the number of valid elements in the vector.

										// Fix the iterator.
										iter = iter + x;

										// Erase the offset from the vector.
										directory_offsets.erase((directory_offsets.end() - 1));     // end() returns the position after the last valid element in the vector.
								}
								else
								{
										// We don't have any offsets, (or we just switched to a subdirectory) so init x to zero.
										x = 0;

										// Unset resetIterLoop.
										resetIterLoop = false;
								}

								// Begin loop to check for more subdirectories.
								for (; x < plist->list.size(); x++)
								{
										// Create temp paths.
										src_path.clear();
										src_path = currentabspath_src + DIR_SEP + (plist->list[x]);
										src_path = RemoveTrailingSlash(src_path);     // If we got a DIR_SEP at the end of the string get rid of it.
										dest_path.clear();
										dest_path = currentabspath_dest + DIR_SEP + (plist->list[x]);
										dest_path = RemoveTrailingSlash(dest_path);     // If we got a DIR_SEP at the end of the string get rid of it.

										// Check to see if the current entry in the list is a directory.
										switch (FileUtills::IsFileOrDirectory(src_path))
										{
												case 0:         // Not a file or directory. (Try to copy anyway.)
												case 1:         // File.
													// Attempt to copy file.
													result = FileUtills::CopyFile(src_path, dest_path, false, 0, 0);
													if (result != 0)
													{
															if ((result != -3) || (result == -33))	// If result does = -3 (CopyFile), or -33 (IsFileOrDirectory) it means the OS / Arch is unsupported by CopyFile().
															{
																	// Set unableToCopyAll.
																	unableToCopyAll = true;

																	/*
																			Note: We need someway of keeping track of what
																			files we've already attempted to copy,
																			Otherwise we'll end up in an indefinte loop.

																			The easist way to to have the list generated the same
																			way each time and store the offsets. (I.e each call to
																			FileUtills::getDirectory() returns the same list. As
																			opposed to just the way the OS spits out the directory
																			listing.)

																			Then when we return from a subdirectory,
																			we find where that subdirectory was in the list and continue.
																	*/
															}
													}
													break;
												case 2:         // Directory.
													// Check recursive flag.
													if (recursive)
													{
															// Set currentabspath_src and currentabspath_dest to this path.
															currentabspath_src = src_path;
															currentabspath_dest = dest_path;

															// Set the current directory list offset (x) in to the vector.
															directory_offsets.push_back(x);

															// Set reset flag.
															resetIterLoop = true;

															// Get out of this loop.
													}	// Ignore otherwise.
													break;
												case -3:        // OS not supported.
													if (plist != NULL)
													{
															delete plist;
															plist = NULL;
													}
													result = -3;
													break;
												case -4:        // Permission error.
												case -5:        // Arg error.
												case -6:        // Path componet does not exist.
												case -7:        // Part of path is a file.
												case -9:        // Memory error.
												default:
													// Set unableToCopyAll.
													unableToCopyAll = true;
													break;
										};

										// Check to see if reset flag is set, if we hit OS / Arch unsupported, or if we failed and the user requested abort on failure.
										if ((resetIterLoop) || (result == -3) || ((unableToCopyAll) && (abort_on_failure)))
										{
												// Get out of this loop.
												break;
										}
								}

								// Check to see how the previous loop exited.
								if ((result == -3) || (result == -33) || ((abort_on_failure) && (unableToCopyAll)))
								{
										/* OS / Arch not supported, or
										 * we failed to copy something and the user requested abort on failure.
										 * No point in trying to continue.
										 */
										done = true;
								}
								else
								{
										if (resetIterLoop)	// Entering subdirectory.
										{
												// Delete the old plist.
												if (plist != NULL)
												{
														delete plist;
														plist = NULL;
												}

												// Check and see if the dest directory exists.
												result = FileUtills::IsFileOrDirectory(currentabspath_dest);
												if (result == -6)	// Directory does NOT exist.
												{
														// Create subdirectory.
														result = FileUtills::CreateDirectory(currentabspath_dest);
														if (result != 0)
														{
																if (result == -3)	// -3 means OS / Arch not supported.
																{
																		// Exit loop.
																		done = true;
																}
																else
																{
																		// Could not create subdirectory.
																		unableToCopyAll = true;

																		// Set resetIterLoop, so that the loop will continue from the parent directory.
																		resetIterLoop = false;
																}
														}
												}
												else
												{
														// Check to see if currentabspath_dest is a some sort of filesystem entry.
														if (result >= 0)
														{
																// OK, we can't create a directory where a file (or some other filesystem entry) exists.
																unableToCopyAll = true;
														}
														else
														{
																if (result == -3)	// OS / Arch not supported.
																{
																		// Exit loop.
																		done = true;
																}
																else
																{
																		// An error occured.
																		unableToCopyAll = true;
																}
														}
												}
										}
										if ((abort_on_failure) && (unableToCopyAll))	// Check for abort on fail. (We do this here due to the above if statement possibly triggering it.)
										{
                                                // Recheck failure due to subdirectory.
                                                done = true;
                                                break;
										}
										if (!resetIterLoop)	// Leaving the subdirectory.
										{
												/* (Note: We do a recheck here, because the above if
												* statement may set this to false. It prevents us from duping
												* this section in the above if statement.)
												*/

												// Check to see if we reached the top level source dir.
												if (currentabspath_src != src)
												{
														// Get the parent directory of currentabspath_src and currentabspath_dest.
														currentabspath_src = FileUtills::GetParent(currentabspath_src);
														if (currentabspath_src.size() <= 0)
														{
																// Could not get parent directory.
																result = -5;
																done = true;
														}
														currentabspath_dest = FileUtills::GetParent(currentabspath_dest);
														if (currentabspath_dest.size() <= 0)
														{
																// Could not get parent directory.
																result = -5;
																done = true;
														}

														// Delete the old plist.
														if (plist != NULL)
														{
																delete plist;
																plist = NULL;
														}
												}
												else
												{
														// Delete the old plist.
														if (plist != NULL)
														{
																delete plist;
																plist = NULL;
														}

														// All directories have been copied.
														done = true;
												}
										}
								}
						}while (!done);

						// Delete the plist.
						if (plist != NULL)
						{
								delete plist;
								plist = NULL;
						}

						// Clear src_path, dest_path, currentabspath_src, and currentabspath_dest.
						src_path.clear();
						dest_path.clear();
						currentabspath_src.clear();
						currentabspath_dest.clear();

						// Flush the directory_offsets vector.
						directory_offsets.clear();

						// Check and see if the unableToCopyAll flag is set.
						if (((result == 0) && (unableToCopyAll)) || ((abort_on_failure) && (unableToCopyAll)))
						{
								// We can't copy some things so return an error.
								result = -6;
						}

						// Check and see if IsFileOrDirectory() returned -3.
						if (result == -33)
						{
                                // IsFileOrDirectory() is not supported.
                                result = -13;
						}
				}
		}
		else	// Treat as single file.
		{
				if ((result == 0) || (result == 1))
				{
                        // Call CopyFile.
                        result = FileUtills::CopyFile(src, dest, append, begOffset, endOffset);
				}
				else
				{
                        // IsFileOrDirectory() returned an error.
                        switch (result)
                        {
                                case -3:
                                    // IsFileOrDirectory() is not supported on this system.
                                    result = -13;
                                    break;
                                case -4:
                                    // A permissions error occured.
                                    result = -14;
                                    break;
                                case -5:
                                    // The given path is empty.
                                    result = -15;
                                    break;
                                case -6:
                                    // A path componet does not exist.
                                    result = -16;
                                    break;
                                case -7:
                                    // The path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
                                    result = -17;
                                    break;
                                default:
                                    // All other errors.
                                    result = -19;
                                    break;
                        };
				}
		}

		// Return result.
		return result;
}

short FileUtills::MovePath(const std::string & src, const std::string & dest, const bool & overwrite)
{
        // Dumb check.
        if ((src.size() <= 0) || (dest.size() <= 0))
        {
                // Bad src or dest.
                return -5;
        }

        // Init vars.
        short result = 0;         // Used for return codes.

        // Check and see if dest already exists.
        result = FileUtills::DoesExist(dest);
        switch (result)
        {
                case 0:     // Path exists.
                    if (overwrite == true)
                    {
                            // Attempt to delete dest path.
                            result = FileUtills::DeletePath(dest, true);
                            switch (result)
                            {
                                    case 0:     // Delete OK.
                                        break;
                                    default:    // Unable to delete path.
                                        result = -21;
                                        break;
                            };
                    }
                    else
                    {
                            // Can't delete existing path bail out.
                            result = -20;
                            break;
                    }
                    break;
                case -1:    // Path does not exist.
                    break;
                default:    // Some error.
                    result = -22;
                    break;
        };

        // Check to see if we can continue.
        if ((result == -1) || (result == 0))
        {
                // Copy entire path to the dest.
                result = FileUtills::CopyPath(src, dest);
                switch (result)
                {
                        case 0:     // Copy ok.
                            break;
                        case -1:    // Source Permission error.
                            result = -10;
                        case -2:    // Source Does not exist.
                            result = -10;
                        default:    // Some error.
                            result = -4;
                            break;
                };

                // Check to see if the copy was successful.
                if (result == 0)
                {
                        // Delete original path.
                        result = FileUtills::DeletePath(src, true);
                        switch (result)
                        {
                                case 0:     // Delete ok.
                                    break;
                                default:    // Some error.
                                    result = -4;
                                    break;
                        };
                }
        }

        // Default return.
        return result;
}
