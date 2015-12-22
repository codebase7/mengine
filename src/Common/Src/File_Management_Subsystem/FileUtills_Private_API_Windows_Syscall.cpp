/*!
    Multiverse Engine Project 06/7/2015 FileUtills FileUtills_Private_API_Windows_Syscall.cpp (Based on FileUtills_Private_API_Posix_Syscall.cpp)
	
    Copyright (C) 2015 Multiverse Engine Project

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

/* Internal includes. */
#include "FileUtills.h"
#include "FileUtills_Private_API.h"
#include "FileUtills_Private_API_Windows_Syscall.h"

size_t FileUtills_Get_Max_Symlink_Depth_Syscall()
{
	/* Windows supports a maximum of 31 reparse points (and therefore symbolic links).
		See also: https://msdn.microsoft.com/en-us/library/windows/desktop/aa365460%28v=vs.85%29.aspx

		For some reason there does not appear to be a system constant for it....
	*/
	return (MSYS_MAX_SYMLINK_DEPTH);
}

void FileUtills_Windows_Syscall_Deallocate_CString(char ** obj)
{
	/* Deallocate the pointer. */
	DataProcess_Deallocate_CString(obj);

	/* Exit function. */
	return;
}

void FileUtils_Deallocate_CString_Syscall(char ** obj)
{
	/* Call the real syscall function. */
	FileUtills_Windows_Syscall_Deallocate_CString(obj);

	/* Exit function. */
	return;
}

/*!
	int FileUtills_Windows_Syscall_Copy_C_String(const char * source, const size_t sourceLength, char ** dest)

	Internal function for coping a const string for later modification.
	(Copied string if the function succeeds will be pointed to by dest, copied string is always
	 the same length as it's source.)

	Note: This function will overwrite dest without deallocating it. If you need whatever
	dest points to after this function returns, copy the pointer elsewhere before calling
	this function.

	When this string is no longer needed it should be deallocated by
	FileUtills_Windows_Syscall_Deallocate_CString(), BEFORE returning to the helper
	or public engine function.

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is NULL, or if sourceLength <= 0.
	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
*/
int FileUtills_Windows_Syscall_Copy_C_String(const char * source, const size_t sourceLength, char ** dest)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of other engine functions. */
	size_t x = 0;									/* Loop counter. */
	char * tempDest = NULL;							/* Temporary pointer used to copy the source string. */

	/* Check for valid arguments. */
	if ((source != NULL) && (sourceLength > 0) && (dest != NULL))
	{
		/* Allocate memory for the copy. */
		retFromCall = DataProcess_Reallocate_C_String(&tempDest, 0, sourceLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempDest != NULL))
		{
			/* Copy the string. */
			for (x = 0; (x < sourceLength); x++)
			{
				tempDest[x] = source[x];
			}

			/* Copy the pointer. */
			(*dest) = tempDest;

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for tempDest. */
			ret = COMMON_ERROR_MEMORY_ERROR;
			COMMON_LOG_DEBUG("FileUtills_Windows_Syscall_Copy_C_String(): ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills_Windows_Syscall_Copy_C_String(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	/* Check for no success. */
	if (ret != COMMON_ERROR_SUCCESS)
	{
		/* Deallocate tempDest if needed. */
		if (tempDest != NULL)
		{
			DataProcess_Deallocate_CString(&tempDest);
		}
	}

	/* Exit function. */
	return ret;
}

/*!
	int FileUtills_Windows_Syscall_Add_Extended_Length_Prefix(char ** path, size_t * pathSize)

	Modifies the given string to prepend MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX
	to the given path. (This allows the windows syscalls to use paths beyond MAX_PATH in length.)
	The resulting string pointer will overwrite the original path pointer, and pathSize will be updated
	to reflect the length of the resulting string.

	The length of the resulting string should always be:
	((*pathSize) + sizeof(MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX)).

	Note: This function will overwrite path and pathSize without deallocating them. If you need whatever
	they point to after this function returns, copy them elsewhere before calling
	this function.

	When this string is no longer needed it should be deallocated by
	FileUtills_Windows_Syscall_Deallocate_CString(), BEFORE returning to the helper
	or public engine function.

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is NULL, or if pathSize <= 0.
	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
*/
int FileUtills_Windows_Syscall_Add_Extended_Length_Prefix(char ** path, size_t * pathSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of other engine functions. */
	size_t x = 0;									/* Loop counter. */
	char * tempPath = NULL;							/* Temporary variable used to prepend MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX to the path. */

	/* Check for valid data. */
	if ((path != NULL) && ((*path) != NULL) && (pathSize != NULL) && ((*pathSize) > 0))
	{
		/* Allocate memory for a new string. */
		retFromCall = DataProcess_Reallocate_CString(&tempPath, 0, ((*pathSize) + sizeof(MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX)));
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPath != NULL))
		{
			/* Add the MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX. */
			for (x = 0; (x < sizeof(MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX)); x++)
			{
				tempPath[x] = MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX[x];
			}

			/* Copy the original string. */
			for (x = 0; (x < (*pathSize)); x++)
			{
				tempPath[x] = ((*path)[x]);
			}

			/* Copy the new pointer and size. */
			(*path) = tempPath;
			(*pathSize) = ((*pathSize) + sizeof(MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX));

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for tempPath. */
			ret = COMMON_ERROR_MEMORY_ERROR;
			COMMON_LOG_DEBUG("FileUtills_Windows_Syscall_Add_Extended_Length_Prefix(): ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
		}
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills_Windows_Syscall_Add_Extended_Length_Prefix(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	/* Check for no success. */
	if (ret != COMMON_ERROR_SUCCESS)
	{
		/* Deallocate tempPath if needed. */
		if (tempPath != NULL)
		{
			DataProcess_Deallocate_CString(&tempPath);
		}
	}

	/* Exit function. */
	return ret;
}

int FileUtills_ResolveSystemSymoblicLink_Syscall(char ** path, size_t * pathSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

	/* Make sure we got a valid path. */
	if ((path != NULL) && ((*path) != NULL) && (pathSize != NULL) && ((*pathSize) > 0))
	{
		
	}
	else
	{
		/* Invalid path. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		/* Log the error. */
		COMMON_LOG_DEBUG("FileUtills_ResolveSystemSymoblicLink(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path argument is invalid.");
	}

	/* Return the result. */
	return ret;
}

int FileUtills::GetUserProfileDirectoryPath_Syscall(char ** path, size_t * pathLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	/* The result of this function. */
	_TCHAR * tempPath = NULL;							/* Temporary pointer for constructing the path. */
	size_t tempPathLength = 0;							/* Temporary variable for storing the length of the path. */

	/* Check for invalid arguments. */
	if ((path != NULL) && (pathLength != NULL))
	{

	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Return the result. */
	return ret;
}

int FileUtills::GetCurrentWorkingDirectoryPath_Syscall(std::string & path)
{
	/* Init vars. */
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	/* The result of this function. */

	/* Return the result. */
	return ret;
}

int FileUtills::GetExecDirectory_Syscall(char ** retStr, size_t * retStrSize)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;	// The result code returned from this function.
	char * result = NULL;			// The string returned from this function.
	size_t resultSize = 0;			// The size of the result string.

	// Check for valid arguments.
	if ((retStr != NULL) && (retStrSize != NULL))
	{

		// Copy the pointer.
		result = PROC_PATH;
		resultSize = PROC_PATH_SIZE;

		// Call FileUtills::ResolveSystemSymoblicLink_Syscall(). (Make sure it's the real path not a symlink. (PROC_PATH is a symlink, and a weird one at that.))
		ret = FileUtills::ResolveSystemSymoblicLink_Syscall(&result, &resultSize);
		if (ret == COMMON_ERROR_SUCCESS)
		{
			// The resulting path is actually the exe itself, so we need to call RemoveLastPathSegment().
			ret = FileUtills::RemoveLastPathSegment(&result, &resultSize);
			if (ret == COMMON_ERROR_SUCCESS)
			{
				// Copy the result string to retStr.
				(*retStr) = result;
				(*retStrSize) = resultSize;
			}
			else
			{
				// Could not remove exe from path.
				COMMON_LOG_DEBUG("FileUtills_GetExecDirectory_Syscall(): Could not remove exe from it's path, call to FileUtills_RemoveLastPathSegment() failed: ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
			}
		}
		else
		{
			// This is an internal engine error.
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Report it.
			COMMON_LOG_WARNING("FileUtills_GetExecDirectory(): ");
			COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
			COMMON_LOG_WARNING(" Getting the executable path failed. (Call to an internal engine function failed.) Please report this bug.");
		}
#endif
	}
	else
	{
		// Invalid arguments.
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills_GetExecDirectory(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	// Return result.
	return ret;
}

FileUtills::dirlist * FileUtills::getDirectory_Syscall(const std::string & absPath, const bool & cleanList)
{
	/* Init vars. */
	int errcpy = 0;					/* Used to fetch the error code. */
	FileUtills::dirlist * ret = NULL;		/* The FileUtills directory structure. */
	std::string tempname = "";			/* Used to store the filename / subdirectory name for the addToArray function. */
	_TCHAR * tempPath = NULL;
	
	
	_tfindfirst();	/* Find first file. */
	_tfindnext();	/* Find next file. */
	_tfindclose();	/* Release directory search handles and resources. */
	
	/* Dumb check. */
	if (absPath.size() > 0)
	{

		/* Allocate the dirlist. */
		try{
			ret = new FileUtills::dirlist;
			if (ret != NULL)
			{
				/* Set the path.*/
				ret->path = absPath;

				/* Dump the path as a c string into the Directory stream object......(Overly complicated POS......) */

				/* Check and make sure we can open the directory first. */
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

	

	// Return the result.
	return ret;
}

int FileUtills::CreateDirectory_Syscall(const char * absPath)
{
	// Init errcpy.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.
	
	// Check for NULL pointer.
	if (absPath != NULL)
	{
		
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

	// Return the result.
	return ret;
}

int FileUtills::CheckPermissions_Syscall(const std::string & absPath, const bool & read, const bool & write, const bool & exec)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.

	// Make sure that absPath is valid.
	if (absPath.size() > 0)
	{
		// Double check and make sure we have something to do.
		if ((read != false) || (write != false) || (exec != false))
		{
				
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

	// Return the result.
	return ret;
}

int FileUtills_IsFileOrDirectory_Syscall(const char * absPath, const size_t absPathSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	/* Result of this function. (Defaults to function not implemented.) */
	char * tempAbsPath = NULL;							/* Temporary variable used to prepend the needed syntax for unicode use. */
	size_t tempAbsPathLength = 0;						/* Length of the tempAbsPath string. */
	DWORD retGFA = 0;									/* The result of the call to GetFileAttributes(). */
	LPWIN32_FIND_DATA fdLP = NULL;						/* Pointer to a LPWIN32_FIND_DATA structure. Used when checking for symlinks. */
	HANDLE retFFF = NULL;								/* The handle from FindFirstFile(). */

	/* Check for invalid absPath. */
	if ((absPath != NULL) && (absPathSize() > 0))
	{
		/* Copy the absPath pointer and length. */
		retFromCall = FileUtills_Windows_Syscall_Copy_C_String(absPath, absPathSize, tempAbsPath);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempAbsPath != NULL))
		{
			/* Set tempAbsPathLength. */
			tempAbsPathLength = absPathSize;

			/* Convert string to have needed prepended tag. */
			retFromCall = FileUtills_Windows_Syscall_Add_Extended_Length_Prefix(&tempAbsPath, &tempAbsPathLength);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempAbsPath != NULL) && (tempAbsPathLength > 0))
			{
				/* Call GetFileAttributes(). */
				retGFA = GetFileAttributes(tempAbsPath);
				if (retGFA != INVALID_FILE_ATTRIBUTES)
				{
					/* Check for directory. */
					if (retGFA | FILE_ATTRIBUTE_DIRECTORY)
					{
						ret = FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY;
					}
					else
					{
						/* Check for a file.

							Note: Windows does not provide a "this is a file" attribute,
							so we have to check for all other entry types, to determine if
							the given filesystem entry is a file.
						*/
						if (retGFA | FILE_ATTRIBUTE_DEVICE)
						{
							/* This is a device handle!
								The engine does not support
								accessing raw devices, so return
								COMMON_ERROR_SUCCESS.
							*/
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* It's a file. */
							ret = FILEUTILLS_ERROR_PATH_IS_A_FILE;
						}
					}

					/* Check for reparse point. */
					if (retGFA | FILE_ATTRIBUTE_REPARSE_POINT)
					{
						/* Get the entry's LPWIN32_FIND_DATA structure. */
						retFFF = FindFirstFile(tempAbsPath, fdLP);
						if ((retFFF != INVALID_HANDLE_VALUE) && (retFFF != ERROR_FILE_NOT_FOUND) && (fdLP != NULL))
						{
							/* Check for symlink. */
							if ((fdLP->dwReserved0) | IO_REPARSE_TAG_SYMLINK)
							{
								ret = FILEUTILLS_ERROR_PATH_IS_A_SYMLINK;
							}
						}
						else
						{
							/* Call failed get error info. */
							retGFA = GetLastError();

							/* Translate the error code. */
							retFromCall = Common_Error_Handler_Translate_Windows_Error_Code(retGFA);
							ret = retFromCall;

							/* Log the error. */
							COMMON_LOG_DEBUG("FileUtills_IsFileOrDirectory_Syscall(): Host function returned: ");
							COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
						}
					}
				}
				else
				{
					/* Call failed get error info. */
					retGFA = GetLastError();

					/* Translate the error code. */
					retFromCall = Common_Error_Handler_Translate_Windows_Error_Code(retGFA);
					ret = retFromCall;

					/* Log the error. */
					COMMON_LOG_DEBUG("FileUtills_IsFileOrDirectory_Syscall(): Host function returned: ");
					COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
				}
			}
			else
			{
				/* Check for memory error. */
				if (retFromCall == COMMON_ERROR_MEMORY_ERROR)
				{
					ret = COMMON_ERROR_MEMORY_ERROR;
				}
				else
				{
					/* Could not prepend the extended length prefix to the given path. */
					ret = COMMON_ERROR_INTERNAL_ERROR;
					COMMON_LOG_DEBUG("FileUtills_IsFileOrDirectory_Syscall(): Could not prepend extended length prefix to path.");
				}
			}
		}
		else
		{
			/* Could not copy path string to temp buffer. */
			ret = COMMON_ERROR_MEMORY_ERROR;
			COMMON_LOG_DEBUG("FileUtills_IsFileOrDirectory_Syscall(): ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
			COMMON_LOG_DEBUG(" Could not copy path string to temp buffer.");
		}
	}
	else
	{
		/* Invalid absPath. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		/* Log the error. */
		COMMON_LOG_DEBUG("FileUtills_IsFileOrDirectory_Syscall(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path is invalid.");
	}

	/* Check for open handle and close it if needed. */
	if (fdLP != NULL)
	{
		if (FindClose(fdLP))
		{
			fdLP = NULL;
		}
		else
		{
			/* Could not release LPWIN32_FIND_DATA structure. */
			COMMON_LOG_DEBUG("FileUtills_IsFileOrDirectory_Syscall(): Could not release LPWIN32_FIND_DATA structure.");
		}
	}

	/* Deallocate temporary string memory. */
	FileUtills_Windows_Syscall_Deallocate_CString(&tempAbsPath);

	/* Return the result. */
	return ret;
}

int FileUtills::DeletePath_Syscall(const std::string & absPath)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// The result of this function.

	// Begin try block.
	try {
		// Check for invalid absPath.
		if (absPath.size() > 0)
		{
			
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
