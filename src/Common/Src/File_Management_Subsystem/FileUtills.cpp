/*!
    Multiverse Engine Project 04/12/2011 FileUtills FileUtills.cpp

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

// Internal includes.
#include "FileUtills.h"
#include "FileUtills_Private_API.h"

/*!
    std::string RemoveTrailingSlash(const std::string & path)

    Removes a DIR_SEP on the end of the given path string (if it exists)
    Will not do anything and return the original string if there is only 1 charater in the given path string.
    Will also return the original string if a memory error occurs.
*/
std::string RemoveTrailingSlash(const std::string & path)
{
	// Init vars.
	size_t size = 0;
	std::string buffer = "";

	// Get size of the Directory string.
	size = path.size();

	// Check the length of the string see if it is only 1 charater.
	if (size <= 1)
	{
		// We can't remove anything, if we do the return would be empty.
		return path;
	}

	// Copy the directory string to buffer
	buffer = path;

	// Check and see if a directory seperator is on the end of the string.
	if ((path.find_last_of(DIR_SEP)) == (size - 1))
	{
		// Remove the trailing Directory seperator so we don't screw up the next check.
		// Note: substr CAN throw an exception so we must put it in a try catch block.
		try{
			buffer = path.substr(0, (size - 1));
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

int CheckPathType(const std::string & path, bool & bIsDosStylePath)
{
	// Init vars.
	short ret = COMMON_ERROR_INTERNAL_ERROR;		// Result of this function.

	// Check for valid path string.
	if (path.size() > 0)
	{
		// Check for a DOS style absolute path reference.
		if ((path.size() > 3) && (path[1] == ':') && (path[2] == '\\')) 
		{
			// This is DOS style absolute path.
			bIsDosStylePath = true;
		}
		else
		{
			// Set bIsDosStylePath.
			bIsDosStylePath = true;

			/*
			* 	We are assuming that if a '/' character is found
			* 	in the path, it is a POSIX style path.
			*
			* 	(Probably a dangerous assumption, but there is not
			* 	much of a way to determine the path type short of
			* 	determining the OS in use. (And even then it's a
			* 	problem if the target is different than the host.))
			*
			* 	Hopefully the target OS will complain if it gets an
			* 	invalid path......
			*/
			for (size_t x = 0; ((x < path.size()) && (bIsDosStylePath)); x++)
			{
				// Check for a '/' character.
				if (path[x] == '/')
				{
					// OK this is a reserved character on windows, so assume the path is a POSIX style path.
					bIsDosStylePath = false;
				}
			}
		}

		// Done.
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		// Invalid path.
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	// Return the result.
	return ret;
}

int FileUtills::GetUserProfileDirectoryPath(std::string & path)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;

	// Call the syscall.
	ret = FileUtills::GetUserProfileDirectoryPath_Syscall(path);
	if (ret != COMMON_ERROR_SUCCESS)
	{
		// Blank path.
		path.clear();

		// Check for a INVALID_ARGUMENT.
		if (ret == COMMON_ERROR_INVALID_ARGUMENT)
		{
			// This is an internal error.
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Log this error.
			COMMON_LOG_WARNING("FileUtills::GetUserProfileDirectoryPath(): Syscall returned an invalid argument error. Please report this bug.\n");
		}
		else
		{
			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::GetUserProfileDirectoryPath(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG("\n");
		}
	}
	else
	{
		// Check for success without result.
		if (path.size() <= 0)
		{
			// Internal error.
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::GetUserProfileDirectoryPath(): Syscall returned an invalid path, but indicated success. Please report this bug.\n");
		}
	}

	// Return the result.
	return ret;
}

int FileUtills::GetCurrentWorkingDirectoryPath(std::string & path)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;

	// Call the syscall.
	ret = FileUtills::GetCurrentWorkingDirectoryPath_Syscall(path);
	if (ret != COMMON_ERROR_SUCCESS)
	{
		// Blank path.
		path.clear();

		// Check for a INVALID_ARGUMENT.
		if (ret == COMMON_ERROR_INVALID_ARGUMENT)
		{
			// This is an internal error.
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Log this error.
			COMMON_LOG_WARNING("FileUtills::GetCurrentWorkingDirectoryPath(): Syscall returned an invalid argument error. Please report this bug.\n");
		}
		else
		{
			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::GetCurrentWorkingDirectoryPath(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG("\n");
		}
	}
	else
	{
		// Check for success without result.
		if (path.size() <= 0)
		{
			// Internal error.
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::GetCurrentWorkingDirectoryPath(): Syscall returned an invalid path, but indicated success. Please report this bug.\n");
		}
	}

	// Return the result.
	return ret;
}

int FileUtills::GetExecDirectory(std::string & retStr)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;	// The result code of this function.
	std::string result = "";		// The result string from GetExecDirectory_Syscall().

	// Call the syscall.
	ret = FileUtills::GetExecDirectory_Syscall(result);
	if (ret == COMMON_ERROR_SUCCESS)
	{
		// Copy result to retStr.
		retStr = result;
	}
	else
	{
		// Check for a INVALID_ARGUMENT.
		if (ret == COMMON_ERROR_INVALID_ARGUMENT)
		{
			// This is an internal error.
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Log this error.
			COMMON_LOG_WARNING("FileUtills::GetExecDirectory(): Syscall returned an invalid argument error. Please report this bug.\n");
		}
		else
		{
			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::GetExecDirectory(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG("\n");
		}
	}

	// Blank result.
	result.clear();

	// Return ret.
	return ret;
}

/*!
 * 	int FileUtills_Reallocate_CString_Buffer(char ** buf, const size_t bufSize, const size_t newSize)
 *
 * 	Allocates a new C-String buffer of newSize length, Reallocates a given buffer
 * 	to be the given newSize length, or deallocates the given buffer if it is
 * 	allocated and newSize is equal to zero.
 *
 * 	WARNING: If this function returns COMMON_ERROR_SUCCESS, then the original
 * 	pointer will be deallocated (free()'d) prior to the function's return.
 * 	DO NOT ATTEMPT TO REUSE THE ORIGINAL POINTER AFTERWARDS.
 *
 * 	Note about buffer reallocations:
 * 	If the original buffer is allocated and a valid size is provided,
 * 	(bufSize must be greater than zero), then X amount of data from the original
 * 	buffer will be sequentially copied to the new buffer. Where X is the amount of
 * 	data that will fit within the new buffer. Any remaining space will be filled
 * 	with NULL characters. Any data that does not fit will be truncated.
 *
 * 	Examples of buffer reallocations:
 * 		Original Buffer (bufSize)		Reallocated buffer(newSize):
 * 		"Foo"(3)				"Foo"(3)
 * 		"Foo"(3)				"Foo\0\0\0"(6)
 * 		"Foo"(3)				"F"(1)
 *
 * 	Returns COMMON_ERROR_SUCCESS if successful. The original pointer will have
 * 	been deallocated and replaced with the newly allocated buffer. The newly
 * 	allocated buffer will be of newSize length.
 *
 * 	Otherwise returns the appropriate error. In this case the original buffer is
 * 	guaranteed to be left intact and unaltered.
 */
int FileUtills_Reallocate_CString_Buffer(char ** buf, const size_t bufSize, const size_t newSize)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		// The result of this function.
	char * tempBuf = NULL;				// A temp pointer used to copy data.

	// Check for a zero new size.
	if (newSize > 0)
	{
		// Allocate the buffer.
		tempBuf = (char*)malloc(newSize);
		if (tempBuf != NULL)
		{
			// Fill the buffer with NULL characters.
			for (size_t x = 0; (x < newSize); x++)
			{
				tempBuf[x] = '\0';
			}

			// Check and see if the original buffer size is greater than zero, and if that buffer is allocated.
			if ((bufSize > 0) && (buf != NULL))
			{
				// OK, copy as much of the original data from the original buffer as possible.
				for (size_t x = 0; ((x < bufSize) && (x < newSize)); x++)
				{
					tempBuf[x] = (*buf)[x];
				}
			}

			// Deallocate the original buffer if it is allocated.
			if ((*buf) != NULL)
			{
				free((*buf));
				(*buf) = NULL;
			}

			// Copy the tempBuf pointer to buf.
			(*buf) = tempBuf;

			// Done.
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			// Could not allocate memory.
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		// Deallocate the original buffer if it is allocated.
		if ((*buf) != NULL)
		{
			free((*buf));
			(*buf) = NULL;
		}

		// Done.
		ret = COMMON_ERROR_SUCCESS;
	}

	// Return the result.
	return ret;
}

int FileUtills::ResolvePath(const char * path, const size_t pathSize, char * retStr, size_t * retStrSize, const bool disableSymLinkResolution)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				// The result of this function.
	size_t numOfResolveAttempts = 0;				// The number of times we have attempted to resolve a symbolic link.
	size_t outputStrSize = 0;					// The current size of the output string.
	size_t tempLinkBufSize = 0;					// The current size of the tempLinkBuf.
	char * outputStr = NULL;					// The resolved path.
	char * tempLinkBuf = NULL;					// Used to hold the result of FileUtills::ResolveSystemSymoblicLink_Syscall().

	// Check for valid path.
	if ((path != NULL) && (pathSize > 0))
	{
			// Allocate buffer for outputStr.
			outputStr = (char*)malloc(pathSize);
			if (outputStr != NULL)
			{
				// Copy path to outputStr.
				for (outputStrSize = 0; ((ret == COMMON_ERROR_UNKNOWN_ERROR) && (outputStrSize < pathSize)); outputStrSize++)
				{
					// Check for a NULL that's before the end of the buffer.
					if ((path[outputStrSize] == '\0') && ((outputStrSize + 1) != pathSize))
					{
						// Invalid path string. (NULL should be at the end of the buffer.)
						ret = COMMON_ERROR_INVALID_ARGUMENT;
						COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
						COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
						COMMON_LOG_DEBUG(" given path argument has a NULL character before the end of the buffer.");
					}
					else
					{
						// Copy the data.
						outputStr[outputStrSize] = path[outputStrSize];
					}
				}

				// Check for success.
				if ((pathSize == outputStrSize) && (ret == COMMON_ERROR_UNKNOWN_ERROR))
				{
					// Begin resolution loop.
					for (numOfResolveAttempts = 0; ((ret == FILEUTILLS_ERROR_PATH_IS_A_SYMLINK) && (numOfResolveAttempts < (FileUtills::Get_Max_Symlink_Depth()))); numOfResolveAttempts++)
					{
						// Resolve the given path.
						ret = FileUtills::ResolvePath_Helper(outputStr, &outputStrSize);

						// Check for error.
						if (ret == COMMON_ERROR_SUCCESS)
						{
							// Check for valid result.
							if ((outputStr != NULL) && (outputStrSize > 0))
							{
								// Check to see if the path is a symbolic link.
								ret = FileUtills::IsFileOrDirectory_Helper(outputStr, outputStrSize);

								// Check the result.
								switch (ret)
								{
									case COMMON_ERROR_SUCCESS:		// System specific (unchecked) filesystem entry type.
									case FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY:
									case FILEUTILLS_ERROR_PATH_IS_A_FILE:
										// Success.
										ret = COMMON_ERROR_SUCCESS;
										break;
									case FILEUTILLS_ERROR_PATH_IS_A_SYMLINK:
										// Check and see if we are resolving symbolic links.
										if (!disableSymLinkResolution)
										{
											// OK, Resolve the symbolic link.
											ret = FileUtills::ResolveSystemSymoblicLink_Syscall(outputStr, outputStrSize, &tempLinkBuf, &tempLinkBufSize);
											if (ret == COMMON_ERROR_SUCCESS)
											{
												// Check for success without result.
												if ((tempLinkBuf != NULL) && (tempLinkBufSize > 0))
												{
													// OK, we need to determine if the resolved symbolic link is a relative path or an absolute path.
													ret = FileUtills::IsAbsolutePathReference(tempLinkBuf, tempLinkBufSize);

													// Check for absolute path result.
													if (ret == FILEUTILLS_ERROR_PATH_IS_ABSOLUTE)
													{
														// Replace the result with the absolute path.
														free(outputStr);
														outputStr = tempLinkBuf;
														outputStrSize = tempLinkBufSize;
													}
													else
													{
														// Check for relative path.
														if (ret == FILEUTILLS_ERROR_PATH_IS_RELATIVE)
														{
															// Remove the symlink from the outputStr.
															ret = FileUtills::RemoveLastPathSegment(&outputStr, &outputStrSize);
															if (ret == COMMON_ERROR_SUCCESS)
															{
																// Reallocate the buffer to store the relative path.
																ret = FileUtills_Reallocate_CString_Buffer(outputStr, outputStrSize, (outputStrSize + tempLinkBufSize));
																if (ret == COMMON_ERROR_SUCCESS)
																{
																	// Reset ret.
																	ret = COMMON_ERROR_UNKNOWN_ERROR;

																	// Append the relative path to the result.
																	for (size_t x = outputStrSize; ((x < (outputStrSize + tempLinkBufSize)) && (ret == COMMON_ERROR_UNKNOWN_ERROR)); x++)
																	{
																		// Check for NULL.
																		if ((tempLinkBuf[x] == '\0') && ((x + 1) != (outputStrSize + tempLinkBufSize)))
																		{
																			// Alright, the tempLinkBuf should NOT have a NULL character in the middle of the buffer.
																			ret = COMMON_ERROR_INTERNAL_ERROR;
																			COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																			COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
																			COMMON_LOG_DEBUG(" invalid NULL character found in the middle of a resolved symbolic link's buffer.");
																		}
																		else
																		{
																			// Copy the data.
																			outputStr[x] = tempLinkBuf[x];
																		}
																	}
																}
																else
																{
																	// An error occured while reallocating the buffer.
																	if (ret == COMMON_ERROR_MEMORY_ERROR)
																	{
																		// Unable to allocate memory for buffer reallocation.
																		COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
																		COMMON_LOG_DEBUG(" out of usable memory. Cannot reallocate buffer for addition of relative path.");
																	}
																	else
																	{
																		// All other errors.
																		COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																		COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
																		COMMON_LOG_DEBUG(" unable to reallocate output buffer for addition of relative path. Please report this bug.");
																		ret = COMMON_ERROR_INTERNAL_ERROR;
																	}
																}
															}
															else
															{
																// Unable to remove the last path segment.
																COMMON_LOG_DEBUG("FileUtills::ResolvePath(): ");
																COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
																COMMON_LOG_DEBUG(" Call to path segment removal function failed. Please report this bug.");
																ret = COMMON_ERROR_INTERNAL_ERROR;
															}
														}
														else
														{
															// This is any other error.
															COMMON_LOG_DEBUG("FileUtills::ResolvePath(): ");
															COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
															COMMON_LOG_DEBUG(" Unable to resolve the given path ( ");
															COMMON_LOG_DEBUG(path);
															COMMON_LOG_DEBUG(" ) Unable to determine the type of the symbolic link.");
															ret = COMMON_ERROR_INTERNAL_ERROR;
														}
													}
												}
												else
												{
													// Success without result.
													ret = COMMON_ERROR_INTERNAL_ERROR;

													// Log the error.
													COMMON_LOG_WARNING("FileUtills::ResolvePath(): ");
													COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
													COMMON_LOG_WARNING(" Call to system symbolic link resolution function indicated success but did not give a result. Please report this bug.");
												}
											}
											else
											{
												// OK an error occured report and log it.
												if (ret == COMMON_ERROR_INVALID_ARGUMENT)
												{
													// This is an internal engine error.
													ret = COMMON_ERROR_INTERNAL_ERROR;
													COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
													COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
													COMMON_LOG_WARNING(" Call to system symbolic link resolution function failed with the given path ( ");
													COMMON_LOG_WARNING(outputStr);
													COMMON_LOG_WARNING(" ) Please report this bug.");
												}
												else
												{
													// This is any other error.
													COMMON_LOG_DEBUG("FileUtills_ResolvePath(): Unable to resolve the given path ( ");
													COMMON_LOG_DEBUG(outputStr);
													COMMON_LOG_DEBUG(" ) Unable to resolve system defined symbolic link.");
												}
											}
										}
										break;
									default:
										// OK an error occured report and log it.
										if (ret == COMMON_ERROR_INVALID_ARGUMENT)
										{
											// This is an internal engine error.
											ret = COMMON_ERROR_INTERNAL_ERROR;
											COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
											COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
											COMMON_LOG_WARNING(" Call to FileUtills_IsFileOrDirectory() failed with the given path ( ");
											COMMON_LOG_WARNING(path);
											COMMON_LOG_WARNING(" ) Please report this bug.\n");
										}
										else
										{
											// This is any other error.
											COMMON_LOG_DEBUG("FileUtills_ResolvePath(): Unable to resolve the given path ( ");
											COMMON_LOG_DEBUG(path);
											COMMON_LOG_DEBUG(" ) Unable to determine final path type.\n");
										}
										break;
								};
							}
							else
							{
								// Success without result.
								ret = COMMON_ERROR_INTERNAL_ERROR;

								// Log the error.
								COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
								COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
								COMMON_LOG_WARNING(" Call to helper function indicated success but did not give a result. Please report this bug.\n");
							}
						}
					}
					
					// Check and see if the loop exited because we hit the resolution attempt limit.
					if (numOfResolveAttempts >= FileUtills::Get_Max_Symlink_Depth())
					{
						// Resolve attempt limit reached.
						ret = FILEUTILLS_ERROR_SYMLINK_CHAIN_TOO_DEEP;

						// Log the error.
						COMMON_LOG_INFO("FileUtills_ResolvePath(): Unable to resolve the given path ( ");
						COMMON_LOG_INFO(path);
						COMMON_LOG_INFO(" ) ");
						COMMON_LOG_INFO(Common_Get_Error_Message(FILEUTILLS_ERROR_SYMLINK_CHAIN_TOO_DEEP));
						COMMON_LOG_INFO("\n");
					}
				}
			}
	}
	else
	{
		// Given path is invalid.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::ResolvePath(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// If we do not have success, we need to deallocate the outputStr buffer.
	if (ret != COMMON_ERROR_SUCCESS)
	{
		if (outputStr != NULL)
		{
			free(outputStr);
			outputStr = NULL;
		}
	}

	// Return the result.
	return ret;
}

FileUtills::dirlist * FileUtills::getDirectory(const std::string & path, const bool & cleanList)
{
	// Init vars.
	FileUtills::dirlist * ret = NULL;					// Result of this function.
	std::string absPath = "";						// Absolute version of the given path.

	// Resolve the given path.
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper.
		ret = FileUtills::getDirectory_Helper(absPath, cleanList);
		if (Common_commonLastErrorCode != COMMON_ERROR_SUCCESS)
		{
			// Check for a list.
			if (ret != NULL)
			{
				delete ret;
				ret = NULL;
			}

			// Check for a INVALID_ARGUMENT error.
			if (Common_commonLastErrorCode == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				Common_commonLastErrorCode = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
		else
		{
			// Check for a success without result.
			if (ret == NULL)
			{
				// Set this to internal error. (The caller does not need to see the success without result error.)
				Common_commonLastErrorCode = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Log the error if needed.
		COMMON_LOG_VERBOSE("FileUtills::getDirectory(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common_commonLastErrorCode));
		COMMON_LOG_VERBOSE("Unable to resolve the given path, aborting.\n");

		/*
		 *	Just in case for some reason Common_commonLastErrorCode
		 * 	was COMMON_ERROR_SUCCESS, and we got here because absPath.size()
		 *	was less than or equal to (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1),
		 *	make sure we set the correct error code.
		 */
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= 0))
		{
			// The error is an internal error.
			Common_commonLastErrorCode = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::getDirectory(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Return the result.
	return ret;
}

int FileUtills::GetGigaFreespace(const std::string & path, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;			// Result of this function.
	std::string absPath = "";						// Absolute version of the given path.

	// Resolve the given path.
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper.
		ret = FileUtills::GetGigaFreespace_Helper(absPath, result);
		if (ret != COMMON_ERROR_SUCCESS)
		{
			// Check for a INVALID_ARGUMENT error.
			if (ret == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Log the error if needed.
		COMMON_LOG_VERBOSE("FileUtills::GetGigaFreespace(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE("Unable to resolve the given path, aborting.\n");

		/*
		 *	Just in case for some reason result
		 * 	was COMMON_SUCCESS, and we got here because absPath.size()
		 *	was less than or equal to (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1),
		 *	make sure we set the correct error code.
		 */
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= 0))
		{
			// The error is an internal error.
			result = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::GetGigaFreespace(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return ret.
	return ret;
}

int FileUtills::GetFreespace(const std::string & path, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;			// Result of this function.
	std::string absPath = "";						// Absolute version of the given path.

	// Resolve the given path.
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper.
		ret = FileUtills::GetFreespace_Helper(absPath, result);
		if (ret != COMMON_ERROR_SUCCESS)
		{
			// Check for a INVALID_ARGUMENT error.
			if (ret == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Log the error if needed.
		COMMON_LOG_VERBOSE("FileUtills::GetFreespace(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE("Unable to resolve the given path, aborting.\n");

		/*
		 *	Just in case for some reason result
		 * 	was COMMON_SUCCESS, and we got here because absPath.size()
		 *	was less than or equal to (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1),
		 *	make sure we set the correct error code.
		 */
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= 0))
		{
			// The error is an internal error.
			result = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::GetFreespace(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return ret.
	return ret;
}

int FileUtills::GetKiloFreespace(const std::string & path, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;			// Result of this function.
	std::string absPath = "";						// Absolute version of the given path.

	// Resolve the given path.
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper.
		ret = FileUtills::GetKiloFreespace_Helper(absPath, result);
		if (ret != COMMON_ERROR_SUCCESS)
		{
			// Check for a INVALID_ARGUMENT error.
			if (ret == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Log the error if needed.
		COMMON_LOG_VERBOSE("FileUtills::GetKiloFreespace(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE("Unable to resolve the given path, aborting.\n");

		/*
		 *	Just in case for some reason result
		 * 	was COMMON_SUCCESS, and we got here because absPath.size()
		 *	was less than or equal to (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1),
		 *	make sure we set the correct error code.
		 */
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= 0))
		{
			// The error is an internal error.
			result = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::GetKiloFreespace(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return ret.
	return ret;
}

int FileUtills::GetByteFreespace(const std::string & path, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;			// Result of this function.
	std::string absPath = "";						// Absolute version of the given path.

	// Resolve the given path.
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper.
		ret = FileUtills::GetByteFreespace_Helper(absPath, result);
		if (ret != COMMON_ERROR_SUCCESS)
		{
			// Check for a INVALID_ARGUMENT error.
			if (ret == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Log the error if needed.
		COMMON_LOG_VERBOSE("FileUtills::GetByteFreespace(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
		COMMON_LOG_VERBOSE("Unable to resolve the given path, aborting.\n");

		/*
		 *	Just in case for some reason result
		 * 	was COMMON_SUCCESS, and we got here because absPath.size()
		 *	was less than or equal to (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1),
		 *	make sure we set the correct error code.
		 */
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= 0))
		{
			// The error is an internal error.
			result = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::GetByteFreespace(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return ret.
	return ret;
}

int FileUtills::CreateDirectory(const std::string & directory, const bool & createRecursive)
{
	// Init vars.
	int result = COMMON_ERROR_UNKNOWN_ERROR;	// Used to hold the result of this function.
	std::string absPath = ""; 			// Used to store the current directory path.

	// Check to see if the full directory path already exists.
	if (FileUtills::DoesExist(directory) != true)
	{
		// Check for a directory seperator on the end of the path and remove it if it is found.
		absPath = RemoveTrailingSlash(directory);

		// Get the absolute version of the path to create.
		absPath = FileUtills::ResolvePath(absPath);

		// Check the result.
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1)))
		{
			// Call helper.
			result = FileUtills::CreateDirectory_Helper(absPath, createRecursive);
			if (result != COMMON_ERROR_SUCCESS)
			{
				// Check for a INVALID_ARGUMENT error.
				if (result == COMMON_ERROR_INVALID_ARGUMENT)
				{
					// Set this to internal error. (The caller does not need to see the invalid argument error.)
					result = COMMON_ERROR_INTERNAL_ERROR;
				}
			}
		}
		else
		{
			// Could not get absolute path to create.
			COMMON_LOG_VERBOSE("FileUtills::CreateDirectory(): Could not get absolute path to create, aborting.\n");

			/*
			 *	Just in case for some reason result
			 * 	was COMMON_SUCCESS, and we got here because absPath.size()
			 *	was less than or equal to (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1),
			 *	make sure we set the correct error code.
			 */
			if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1)))
			{
				// The error is an internal error.
				result = COMMON_ERROR_INTERNAL_ERROR;
				COMMON_LOG_WARNING("FileUtills::CreateDirectory(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
			}
		}
	}
	else
	{
		// Directory already exists thus return true.
		result = FILEUTILLS_ERROR_EXISTANT;
	}

	// Copy result to commonLastErrorCode.
	Common_commonLastErrorCode = result;

	// Return the result.
	return result;
}

int FileUtills::CheckPermissions(const std::string & path, const bool & read, const bool & write, const bool & exec)
{
	// Init vars.
	int ret = COMMON_ERROR_SUCCESS;		// The result of this function.
	std::string absPath = "";			// The absolute path of the given path.

	// Call ResolvePath().
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper function.
		ret = FileUtills::CheckPermissions_Helper(absPath, read, write, exec);
		if (ret != COMMON_ERROR_SUCCESS)
		{
			// Check for a INVALID_ARGUMENT error.
			if (ret == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Call to ResolvePath() failed.
		COMMON_LOG_VERBOSE("FileUtils::CheckPermissions(): Unable to resolve the given path, aborting.\n");

		// Make sure Common_commonLastErrorCode is set to something.
		if (absPath.size() <= 0)
		{
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::CheckPermissions(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::DoesExist(const std::string & path)
{
	// Declare some vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;	// Holds common namepspace error code.
	std::string absPath = "";				// Holds the abosolute value of the given path.

	// Call ResolvePath().
	absPath = FileUtills::ResolvePath(path);
	if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
	{
		// Call helper function.
		ret = FileUtills::DoesExist_Helper(absPath);
		if (ret != COMMON_ERROR_SUCCESS)
		{
			// Check for a INVALID_ARGUMENT error.
			if (ret == COMMON_ERROR_INVALID_ARGUMENT)
			{
				// Set this to internal error. (The caller does not need to see the invalid argument error.)
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}
		}
	}
	else
	{
		// Call to ResolvePath() failed.
		COMMON_LOG_VERBOSE("FileUtils::DoesExist(): Call to FileUtills::ResolvePath() failed, aborting.\n");

		// Make sure Common_commonLastErrorCode is set to something.
		if (absPath.size() <= 0)
		{
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills::DoesExist(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
		}
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Default return.
	return ret;
}

int FileUtills::IsFileOrDirectory(const std::string & path)
{
	// Init result.
	int result = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;			// Result of this function. (Defaults to function not implemetated.)
	std::string absPath = "";						// The absolute path of the given path argument.

	// Make sure that the path is not empty.
	if (path.size() > 0)
	{
		// Get the absolute path of the given path argument.
		absPath = FileUtills::ResolvePath(path);

		// Check for success.
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
		{
			// Call Helper function.
			result = FileUtills::IsFileOrDirectory_Helper(absPath);
			if (result != COMMON_ERROR_SUCCESS)
			{
				// Check for a INVALID_ARGUMENT error.
				if (result == COMMON_ERROR_INVALID_ARGUMENT)
				{
					// Set this to internal error. (The caller does not need to see the invalid argument error.)
					result = COMMON_ERROR_INTERNAL_ERROR;
				}
			}
		}
		else
		{
			// Unable to generate absolute path.
			COMMON_LOG_DEBUG("FileUtills::IsFileOrDirectory(): Unable to get absolute path, aborting.\n");

			// Make sure Common_commonLastErrorCode is set to a valid error code.
			if (absPath.size() <= 0)
			{
				result = COMMON_ERROR_INTERNAL_ERROR;
				COMMON_LOG_WARNING("FileUtills::IsFileOrDirectory(): ResolvePath() returned an invalid path string, but indicated success. Please report this bug.\n");
			}
		}
	}
	else
	{
		// Empty path.
		result = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::IsFileOrDirectory(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
		COMMON_LOG_DEBUG(" given path argument is invalid.");
	}

	// Copy result to commonLastErrorCode.
	Common_commonLastErrorCode = result;

	// Exit function.
	return result;
}

int FileUtills::CheckParent(const std::string & path, const bool & read, const bool & write, const bool & exec)
{
	// Init vars.
	int result = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;			// Result of this function.
	std::string absPath = path;						// Absolute version of the given path.

	// Check and see if the length is zero.
	if (absPath.size() > 0)
	{
		// Get the absolute path.
		absPath = FileUtills::ResolvePath(absPath);
		if (Common_commonLastErrorCode == COMMON_ERROR_SUCCESS)
		{
			// Call helper.
			result = FileUtills::CheckParent_Helper(absPath, read, write, exec);
			if (result != COMMON_ERROR_SUCCESS)
			{
				// Check for a INVALID_ARGUMENT error.
				if (result == COMMON_ERROR_INVALID_ARGUMENT)
				{
					// Set this to internal error. (The caller does not need to see the invalid argument error.)
					result = COMMON_ERROR_INTERNAL_ERROR;
				}
			}
		}
		else
		{
			// Call to ResolvePath() failed.
			COMMON_LOG_VERBOSE("FileUtills::CheckParent(): Could not resolve the parent path. Unable to check parent's existance / permissions.\n");
		}
	}
	else
	{
		// Invalid path.
		result = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills::CheckParent(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(result));
		COMMON_LOG_VERBOSE(" Given path is invalid, aborting.\n");
	}

	// Copy result to commonLastErrorCode.
	Common_commonLastErrorCode = result;

	// Return the result.
	return result;
}

std::string FileUtills::GetParent(const std::string & path)
{
    // Init vars.
    std::string parentbuffer = "";
    size_t length = 0;
    size_t location = 0;

#ifdef POSIX_COMMON_H
    // Remove the trailing slash if present.
    parentbuffer = RemoveTrailingSlash(path);

    // Check the Path for absolute path.
    parentbuffer = FileUtills::ResolvePath(parentbuffer);

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

int FileUtills::DeletePath(const std::string & path, const bool & recursive)
{
        // Init vars.
	int result = COMMON_ERROR_UNKNOWN_ERROR;	// Used to store results from calls to other functions.
	std::string absPath = "";			// Used to contain the top level absolute path.

	// Avoid running ResolvePath() if the given path argument is empty.
	if (path.size() > 0)
	{
		// Get the absolute path.
		absPath = FileUtills::ResolvePath(path);

		// Make sure we got the path.
		if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() > 0))
		{
			// Call helper.
			result = FileUtills::DeletePath_Helper(path, recursive);
			if (result != COMMON_ERROR_SUCCESS)
			{
				// Check for a INVALID_ARGUMENT error.
				if (result == COMMON_ERROR_INVALID_ARGUMENT)
				{
					// Set this to internal error. (The caller does not need to see the invalid argument error.)
					result = COMMON_ERROR_INTERNAL_ERROR;
				}
			}
		}
		else
		{
			// Log the error.
			COMMON_LOG_INFO("FileUtills::DeletePath(): Unable to delete ( ");
			COMMON_LOG_INFO(absPath.c_str());
			COMMON_LOG_INFO(" ) Path resolution failed with error: ");
			if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPath.size() <= 0))
			{
				// Internal error.
				result = COMMON_ERROR_INTERNAL_ERROR;
				COMMON_LOG_INFO(Common::Get_Error_Message(result));
				COMMON_LOG_INFO("\n");
				COMMON_LOG_WARNING("FileUtills::DeletePath(): ResolvePath() returned an empty / invalid absolute path while indicating success, Please report this bug.");
			}
			else
			{
				// Preserve the error code from ResolvePath().
				result = Common_commonLastErrorCode;
				COMMON_LOG_INFO(Common::Get_Error_Message(result));
			}
			COMMON_LOG_INFO("\n");
		}
	}
	else
	{
		// Invalid path argument.
		result = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills::DeletePath(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
		COMMON_LOG_DEBUG(" Given path argument is empty.\n");
	}

	// Copy result to Common_commonLastErrorCode.
	Common_commonLastErrorCode = result;

	// Return the result.
	return result;
}

int FileUtills::CopyFile(const std::string & src, const std::string & dest, const bool & append, const streamsize & begOffset, const streamsize & endOffset)
{
	// Init vars.
	int result = COMMON_ERROR_UNKNOWN_ERROR;			// The result of this function.
	size_t amountOfBytesToCopy = 0;					// Used to hold the amount of bytes to copy from the source file.
	size_t x = 0;							// Used to control the outer copy loop.
	size_t y = 0;							// Used to control the inner input copy loop.
	size_t z = 0;							// Used to control the inner output copy loop.
	const size_t bufferSize = 512;					// Size of the buffer to allocate.
	char * ioBuffer = NULL;						// Used to hold data in a buffer while it is being copied.
	std::string absPathSrc = "";					// Used to fetch the absolute path of src.
	std::string absPathDest = "";					// Used to fetch the absolute path of dest.
	std::fstream input;						// File stream for the input (source) file.
	std::fstream output;						// File stream for the output (destionation) file.

	// Check Arguments.
	if (src.size() > 0)
	{
		if (dest.size() > 0)
		{
			if (begOffset >= 0)
			{
			  	if (endOffset >= 0)
				{
					// Check and see if the offsets are valid.
					if (((begOffset == 0) && (endOffset == 0)) ||
					    ((begOffset == 0) && (endOffset > 0)) ||
					    ((begOffset > 0) && (endOffset == 0)) ||
					    ((begOffset > 0) && (endOffset > 0) && (endOffset > begOffset)))
					{
						// Set the amountOfBytesToCopy if we know the total amount.
						if ((begOffset == 0) && (endOffset > 0))
						{
							amountOfBytesToCopy = endOffset;
						}
						else
						{
							if ((begOffset > 0) && (endOffset > 0) && (endOffset > begOffset))
							{
								amountOfBytesToCopy = (endOffset - begOffset);
							}
						}

						// Get absolute path for src.
						absPathSrc = FileUtills::ResolvePath(src);

						// Check for error.
						if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPathSrc.size() > 0))
						{
							// Get absolute path for dest.
							absPathDest = FileUtills::ResolvePath(dest);

							// Check for error.
							if ((Common_commonLastErrorCode == COMMON_ERROR_SUCCESS) && (absPathDest.size() > 0))
							{
								// Check and see if src is a regular file.
								if (FileUtills::IsFileOrDirectory(absPathSrc) == FILEUTILLS_ERROR_PATH_IS_A_FILE)
								{
									// Check and see if dest exists.
									FileUtills::IsFileOrDirectory(absPathDest);
									if ((Common_commonLastErrorCode == FILEUTILLS_ERROR_NON_EXISTANT) ||
									    (Common_commonLastErrorCode == FILEUTILLS_ERROR_PATH_IS_A_FILE))
									{
										// Check to see if the parent directory exists.
										result = FileUtills::CheckParent(absPathDest);
										if (result == COMMON_ERROR_SUCCESS)
										{
											// Open the dest file first.
											if ((Common_commonLastErrorCode == FILEUTILLS_ERROR_PATH_IS_A_FILE) &&
											    (append))
											{
												// Open in append mode.
												output.open(absPathDest.c_str(), std::ios::out | std::ios::binary | std::ios::app);
											}
											else
											{
												// Open in truncate mode.
												output.open(absPathDest.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
											}

											// Check and see if the dest file opened.
											if (output.is_open())
											{
												// If we are appending data jump to the end.
												if (append)
												{
													output.seekp(0, std::ios::end);
												}

												// Open the input file.
												input.open(absPathSrc.c_str(), std::ios::in | std::ios::binary);

												// Check and see if the input file opened.
												if (input.is_open())
												{
													// Calculate the size of the input file, and determine if we need to take into account an offset. (amountOfBytesToCopy will be greater than zero if we do.)
													input.seekg(0, std::ios::end);
													if (amountOfBytesToCopy > 0)
													{
														// Check and see if we have a file big enough to have that many bytes.
														if (input.tellg() >= (begOffset + amountOfBytesToCopy))
														{
															// Jump to the correct beginning offset in the input file.
															input.seekg(begOffset, std::ios::beg);
														}
														else
														{
															// File is not big enough to copy the requested byte range.
															result = COMMON_ERROR_RANGE_ERROR;

															// Log the error.
															COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
															COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
															COMMON_LOG_DEBUG(" The given source file ( ");
															COMMON_LOG_DEBUG(absPathSrc.c_str());
															COMMON_LOG_DEBUG(" ) is too small. Either the beginning offset itself, or the beginning offset plus the range of bytes to copy, is beyond the end of the source file. Aborting.\n");

															// Reset amountOfBytesToCopy.
															amountOfBytesToCopy = 0;
														}
													}
													else
													{
														// Copy the entire file. (Only if both offsets are equal to zero.)
														amountOfBytesToCopy = input.tellg();

														// Seek back to the beginning og the source file.
														input.seekg(0, std::ios::beg);
													}

													// Allocate our memory buffer.
													try {
														ioBuffer = (char*)malloc(bufferSize);
														
														// Check for an allocated buffer.
														if (ioBuffer != NULL)
														{
															// Begin copy loop.
															for (x = 0; ((x < amountOfBytesToCopy) && (result == COMMON_ERROR_SUCCESS));)
															{
																// Start internal buffer loop.
																for (y = 0; ((y < bufferSize) && ((x + y) < amountOfBytesToCopy) && (result == COMMON_ERROR_SUCCESS)); y++)
																{
																	// Copy the data.
																	ioBuffer[(x + y)] = input.get();

																	// Check the input stream.
																	if (!input.good())
																	{
																		// I/O error.
																		result = COMMON_ERROR_IO_ERROR;

																		// Log the error.
																		COMMON_LOG_VERBOSE("FileUtills::CopyFile(): ");
																		COMMON_LOG_VERBOSE(Common::Get_Error_Message(result));
																		COMMON_LOG_VERBOSE(" Input file stream failed.");
																		COMMON_LOG_VERBOSE("\n");
																	}
																}

																// Output the data.
																for (z = 0; ((z < y) && (result == COMMON_ERROR_SUCCESS)); z++)
																{
																	output.put(ioBuffer[z]);

																	// Check the output stream.
																	if (!output.good())
																	{
																		// I/O error.
																		result = COMMON_ERROR_IO_ERROR;

																		// Log the error.
																		COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
																		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
																		COMMON_LOG_VERBOSE(" Output file stream failed.");
																		COMMON_LOG_DEBUG("\n");
																	}
																}

																// Flush the output buffer.
																if (output.good())
																{
																	output.flush();
																}
																
																// Increment x.
																x += y;
															}
														}
														else
														{
															// Could not allocate memory buffer.
															result = COMMON_ERROR_MEMORY_ERROR;

															// Log the error.
															COMMON_LOG_VERBOSE("FileUtills::CopyFile(): ");
															COMMON_LOG_VERBOSE(Common::Get_Error_Message(result));
															COMMON_LOG_VERBOSE("\n");
														}
													}
													catch(exception &ex)
													{
														// Exception thrown.
														result = COMMON_ERROR_EXCEPTION_THROWN;

														// Log the error.
														COMMON_LOG_VERBOSE("FileUtills::CopyFile(): ");
														COMMON_LOG_VERBOSE(Common::Get_Error_Message(result));
														COMMON_LOG_VERBOSE(" ");
														COMMON_LOG_VERBOSE(ex.what());
														COMMON_LOG_VERBOSE("\n");
													}

													// Free the buffer if needed.
													if (ioBuffer != NULL)
													{
														free(ioBuffer);
														ioBuffer = NULL;
													}

													// Close the input and output files.
													if (input.is_open())
													{
														input.close();
													}
													if (output.is_open())
													{
														output.close();
													}

													// Log file creation.
													if (result == COMMON_ERROR_SUCCESS)
													{
														COMMON_LOG_INFO("FileUtills::CopyFile(): Copied file ( ");
														COMMON_LOG_INFO(absPathDest.c_str());
														COMMON_LOG_INFO(" ) successfully.\n");
													}
													else
													{
														COMMON_LOG_INFO("FileUtills::CopyFile(): File ( ");
														COMMON_LOG_INFO(absPathDest.c_str());
														COMMON_LOG_INFO(" ) created, but coping was unsuccessful.\n");
													}
												}
												else
												{
													// Could not open the source file for reading.
													result = COMMON_ERROR_IO_ERROR;

													// Log error.
													COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
													COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
													COMMON_LOG_DEBUG(" Unable to open ( ");
													COMMON_LOG_DEBUG(absPathSrc.c_str());
													COMMON_LOG_DEBUG(" ) for reading.\n");

													// Close the output file.
													output.close();
												}
											}
											else
											{
												// Could not open the destionation file for writing.
												result = COMMON_ERROR_IO_ERROR;

												// Log error.
												COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
												COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
												COMMON_LOG_DEBUG(" Unable to open ( ");
												COMMON_LOG_DEBUG(absPathDest.c_str());
												COMMON_LOG_DEBUG(" ) for writing.\n");
											}
										}
										else
										{
											// Check for non-existant parent directory.
											if (result == FILEUTILLS_ERROR_NON_EXISTANT)
											{
												COMMON_LOG_INFO("FileUtills::CopyFile(): Destionation directory (or a path componet leading up to it) does not exist, CopyFile() does not create non-existant directories, call CopyPath() instead. Aborting.\n");
											}
											else
											{
												COMMON_LOG_INFO("FileUtills::CopyFile(): Error while checking destionation parent directory, aborting.\n");
											}
										}
									}
									else
									{
										// Check for a directory.
										if (Common_commonLastErrorCode == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
										{
											// Cannot overwrite a directory with a file.
											COMMON_LOG_INFO("FileUtills::CopyFile(): Cannot overwrite a directory with a file, aborting.\n");
										}
										else
										{
											// Other error, abort.
											COMMON_LOG_INFO("FileUtills::CopyFile(): Unable to determine the destionation path's type / existance, aborting.\n");
										}
									}
								}
								else
								{
									// Check error.
									if ((Common_commonLastErrorCode == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY) ||
									  (Common_commonLastErrorCode == COMMON_ERROR_SUCCESS))
									{
										// Unable to copy a directory or special file. (COMMON_ERROR_SUCCESS is used to indicate path existance when it is not a regular file or directory.)
										COMMON_LOG_DEBUG("FileUtills::CopyFile(): Unable to copy non-regular files or directories, aborting.\n");
									}
									else
									{
										// Got an error, abort.
										COMMON_LOG_VERBOSE("FileUtills::CopyFile(): Unable to determine the source path's type / existance, aborting.\n");
									}
								}
							}
							else
							{
								// Unable to get destionation absolute path.
								COMMON_LOG_VERBOSE("Unable to get destionation absolute path, aborting.\n");

								// Make sure Common_commonLastErrorCode is set to something.
								if (absPathDest.size() <= 0)
								{
									result = COMMON_ERROR_INTERNAL_ERROR;
								}
							}
						}
						else
						{
							// Unable to get source absolute path.
							COMMON_LOG_VERBOSE("Unable to get source absolute path, aborting.\n");

							// Make sure Common_commonLastErrorCode is set to something.
							if (absPathSrc.size() <= 0)
							{
								result = COMMON_ERROR_INTERNAL_ERROR;
							}
						}
					}
					else
					{
						// Offsets are switched.
						result = COMMON_ERROR_INVALID_ARGUMENT;

						// Log error.
						COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
						COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
						COMMON_LOG_DEBUG(" Your offsets are invalid. (Really the only way this is possible is if you either reverse the beginning and ending offsets, or if you have an offset that is less than zero.) Aborting.\n");
					}
				}
				else
				{
					// endOffset is invalid.
					result = COMMON_ERROR_INVALID_ARGUMENT;

					// Log error.
					COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
					COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
					COMMON_LOG_DEBUG(" ending offset argument is invalid.\n");
				}
			}
			else
			{
				// begOffset is invalid.
				result = COMMON_ERROR_INVALID_ARGUMENT;

				// Log error.
				COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
				COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
				COMMON_LOG_DEBUG(" beginning offset argument is invalid.\n");
			}
		}
		else
		{
			// dest is invalid.
			result = COMMON_ERROR_INVALID_ARGUMENT;

			// Log error.
			COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
			COMMON_LOG_DEBUG(" destionation path argument is invalid.\n");
		}
	}
	else
	{
		// Src is invalid.
		result = COMMON_ERROR_INVALID_ARGUMENT;

		// Log error.
		COMMON_LOG_DEBUG("FileUtills::CopyFile(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
		COMMON_LOG_DEBUG(" source path argument is invalid.\n");
	}

	// Copy result to Common_commonLastErrorCode.
	Common_commonLastErrorCode = result;

	// Return the result.
	return result;
}

int FileUtills::CopyPathData(const std::string & src, const std::string & dest, const bool & recursive,
			   const bool & rename, const bool & abort_on_failure,
			   const bool & append, const streamsize & begOffset, const streamsize & endOffset)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;

	// LOG INCOMPLETE FUNCTION.
	COMMON_LOG_WARNING("FileUtills::CopyPathData(): ");
	COMMON_LOG_WARNING(Common::Get_Error_Message(ret));
	COMMON_LOG_WARNING("\n");

	// Copy result to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::CopyPath(const std::string & src, const std::string & dest, const bool & recursive,
			   const bool & useSyscall, const bool & useRename)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// The result of this function.
	std::string absPathSrc = "";				// The absolute version of the given source path.
	std::string absPathDest = "";				// The absolute version of the given destionation path.

	// Call FileUtills::ResolvePath() for the source path.
	absPathSrc = FileUtills::ResolvePath(src);
	if (Common_commonLastErrorCode == COMMON_ERROR_SUCCESS)
	{
		// Check for valid result.
		if (absPathSrc.size() > 0)
		{
			// Resolve the destionation path.
			absPathDest = FileUtills::ResolvePath(dest);
			if (Common_commonLastErrorCode == COMMON_ERROR_SUCCESS)
			{
				// Check for valid result.
				if (absPathDest.size() > 0)
				{
					// Call helper function.
					ret = FileUtills::CopyPath_Helper(absPathSrc, absPathDest, recursive, useSyscall, useRename);
					if (ret == COMMON_ERROR_SUCCESS)
					{
						// Log success.
						COMMON_LOG_INFO("FileUtills::CopyPath(): Copied ( ");
						COMMON_LOG_INFO(absPathSrc.c_str());
						COMMON_LOG_INFO(" ) to ( ");
						COMMON_LOG_INFO(absPathDest.c_str());
						COMMON_LOG_INFO(" ) successfully.\n");
					}
					else
					{
						// Check for invalid argument.
						if (ret == COMMON_ERROR_INVALID_ARGUMENT)
						{
							// Set this to internal error. (The caller does not need to see the invalid argument error.)
							ret = COMMON_ERROR_INTERNAL_ERROR;
						}

						// Log the error.
						COMMON_LOG_INFO("FileUtills::CopyPath(): Unable to copy ( ");
						COMMON_LOG_INFO(absPathSrc.c_str());
						COMMON_LOG_INFO(" ) to ( ");
						COMMON_LOG_INFO(absPathDest.c_str());
						COMMON_LOG_INFO(" ) successfully. Some files / directories may have been copied. Please double check manually.\n");
					}
				}
				else
				{
					// Could not resolve the destionation path. (Success without result.)
					ret = COMMON_ERROR_INTERNAL_ERROR;

					// Log the error.
					COMMON_LOG_WARNING("FileUtills::CopyPath(): ");
					COMMON_LOG_WARNING(Common::Get_Error_Message(ret));
					COMMON_LOG_WARNING(" Could not resolve the destionation path, FileUtills::ResolvePath() returned an invalid path but indicated success, Please report this bug.\n");
				}
			}
			else
			{
				// Log the error.
				COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
				COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
				COMMON_LOG_DEBUG(" Could not resolve the destionation path, aborting.\n");
			}
		}
		else
		{
			// Could not resolve the source path. (Success without result.)
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Log the error.
			COMMON_LOG_WARNING("FileUtills::CopyPath(): ");
			COMMON_LOG_WARNING(Common::Get_Error_Message(ret));
			COMMON_LOG_WARNING(" Could not resolve the source path, FileUtills::ResolvePath() returned an invalid path but indicated success, Please report this bug.\n");
		}
	}
	else
	{
		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Could not resolve the destionation path, aborting.\n");
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return the result.
	return ret;
} 
  // Below is the Helper function for CopyPath().
  
  rewrite directory parser loop with the one from DeletePath().
  
int FileUtills::CopyPath_Helper(const std::string & absPathSrc, const std::string & absPathDest, const bool & recursive, const bool & useSyscall, const bool & useRename)
{
	// Init vars.
	int ret = COMMON_ERROR_SUCCESS;		// Used to hold the result of this function.
	char * pCurrentPathSegment = NULL;		// Used to allocate memory for a substring that contains the current path segment.
	std::string absPathDestFixedFileName = "";	// Used to copy a source path with a different destionation name.

	// Check for valid absPathSrc.
	if (absPathSrc.size() > 0)
	{
		// Check for valid absPathDest.
		if (absPathDest.size() > 0)
		{
			// Determine the type of source. (File or directory.)
			ret = FileUtills::IsFileOrDirectory_Helper(absPathSrc);
			if ((ret == FILEUTILLS_ERROR_PATH_IS_A_FILE) || (ret == COMMON_ERROR_SUCCESS))
			{ 
				// Check and see if the source is a non-regular file, and if the copy syscall use is disabled.
				if ((ret == COMMON_ERROR_SUCCESS) && (!useSyscall))
				{
					// We cannot copy a non-regular file, without using a syscall.
					COMMON_LOG_INFO("FileUtills::CopyPath(): Cannot copy source ( ");
					COMMON_LOG_INFO(absPathSrc.c_str());
					COMMON_LOG_INFO(" ) to destionation ( ");
					COMMON_LOG_INFO(absPathDest.c_str());
					COMMON_LOG_INFO(" ) Cannot copy a non-regular file without using a host's syscall. Caller has disabled use of a host's syscall. Aborting.\n");
				}
				else
				{
					// Check and see if the destionation path exists.
					ret = FileUtills::IsFileOrDirectory_Helper(absPathDest);
					if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
					{
						// Destionation path does not exist. Assume the last path segment in the destionation path is the file name of the copied file.
						// OK, check and see if the parent exists.
						ret = FileUtills::CheckParent_Helper(absPathDest, true, true, true);
						if (ret == COMMON_ERROR_SUCCESS)
						{
							// OK Copy the source file to the destionation directory.
							// Using the given last path segment in the destionation path as the copied file's name.
							if (useSyscall && useRename)
							{
								// Use the rename syscall.
								ret = FileUtills::RenameFile_Syscall(absPathSrc, absPathDest);
								if (ret == COMMON_ERROR_SUCCESS)
								{
									// Log the copied file.
									COMMON_LOG_INFO("FileUtills::CopyPath(): Copied ( ");
									COMMON_LOG_INFO(absPathSrc.c_str());
									COMMON_LOG_INFO(" ) to destionation ( ");
									COMMON_LOG_INFO(absPathDest.c_str());
									COMMON_LOG_INFO(" ) successfully.\n");
								}
								else
								{
									// An error occured.
									COMMON_LOG_DEBUG("FileUtills::CopyPath(): Error ( ");
									COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
									COMMON_LOG_DEBUG(" ) was returned from the RenameFile syscall. Unable to copy ( ");
									COMMON_LOG_DEBUG(absPathSrc.c_str());
									COMMON_LOG_DEBUG(" ) to destionation ( ");
									COMMON_LOG_DEBUG(absPathDest.c_str());
									COMMON_LOG_DEBUG(" ).\n");

									// If ret was invalid argument change it to internal error.
									if (ret == COMMON_ERROR_INVALID_ARGUMENT)
									{
										ret = COMMON_ERROR_INTERNAL_ERROR;
									}
								}
							}
							else
							{
								// Check to see if we are using the syscall.
								if (useSyscall)
								{
									// Copy using the host's copy syscall.
									ret = FileUtills::CopyPath_Syscall(absPathSrc, absPathDest);
									if (ret == COMMON_ERROR_SUCCESS)
									{
										// Log the copied file.
										COMMON_LOG_INFO("FileUtills::CopyPath(): Copied ( ");
										COMMON_LOG_INFO(absPathSrc.c_str());
										COMMON_LOG_INFO(" ) to destionation ( ");
										COMMON_LOG_INFO(absPathDest.c_str());
										COMMON_LOG_INFO(" ) successfully.\n");
									}
									else
									{
										// An error occured.
										COMMON_LOG_DEBUG("FileUtills::CopyPath(): Error ( ");
										COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
										COMMON_LOG_DEBUG(" ) was returned from the CopyFile syscall. Unable to copy ( ");
										COMMON_LOG_DEBUG(absPathSrc.c_str());
										COMMON_LOG_DEBUG(" ) to destionation ( ");
										COMMON_LOG_DEBUG(absPathDest.c_str());
										COMMON_LOG_DEBUG(" ).\n");

										// If ret was invalid argument change it to internal error.
										if (ret == COMMON_ERROR_INVALID_ARGUMENT)
										{
											ret = COMMON_ERROR_INTERNAL_ERROR;
										}
									}
								}
								else
								{
									// Copy using the CopyPathData() function.
								}
							}
						}
						else
						{
							// An error occured.
						}
					}
					else
					{
						// Check and see if the destionation path is a directory.
						if (ret == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
						{
							// The last path segment in the destionation path is a directory,
							// assume the copied file's name is the same as the source file.

							// Copy absPathDest to absPathDestFixedFileName and add a DIR_SEP.
							absPathDestFixedFileName = absPathDest;
							absPathDestFixedFileName += DIR_SEP;

							// We need to copy the last path segment of the source to the destionation.
							// (So the copied file will have the same name as the source file.)
							ret = FileUtills::GetLastPathSegment(absPathSrc, absPathDestFixedFileName, false);
							if (ret == COMMON_ERROR_SUCCESS)
							{
								// Check for success without result.
								if (absPathDestFixedFileName.size() > (absPathDest.size() + sizeof(DIR_SEP)))
								{
									// Check and see if we are using the syscalls.
									if (useSyscall && useRename)
									{
										// Use the rename syscall.
										ret = FileUtills::RenameFile_Syscall(absPathSrc, absPathDestFixedFileName);
										if (ret == COMMON_ERROR_SUCCESS)
										{
											// Log the copied file.
											COMMON_LOG_INFO("FileUtills::CopyPath(): Copied ( ");
											COMMON_LOG_INFO(absPathSrc.c_str());
											COMMON_LOG_INFO(" ) to destionation ( ");
											COMMON_LOG_INFO(absPathDestFixedFileName.c_str());
											COMMON_LOG_INFO(" ) successfully.\n");
										}
										else
										{
											// An error occured.
											COMMON_LOG_DEBUG("FileUtills::CopyPath(): Error ( ");
											COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
											COMMON_LOG_DEBUG(" ) was returned from the CopyFile syscall. Unable to copy ( ");
											COMMON_LOG_DEBUG(absPathSrc.c_str());
											COMMON_LOG_DEBUG(" ) to destionation ( ");
											COMMON_LOG_DEBUG(absPathDestFixedFileName.c_str());
											COMMON_LOG_DEBUG(" ).\n");

											// If ret was invalid argument change it to internal error.
											if (ret == COMMON_ERROR_INVALID_ARGUMENT)
											{
												ret = COMMON_ERROR_INTERNAL_ERROR;
											}
										}
									}
									else
									{
										// Check and see if we are using the host's copy syscall.
										if (useSyscall)
										{
											// OK, copy the source file to the destionation directory, using the syscall.
											ret = FileUtills::CopyPath_Syscall(absPathSrc, absPathDestFixedFileName);
											if (ret == COMMON_ERROR_SUCCESS)
											{
												// Log the copied file.
												COMMON_LOG_INFO("FileUtills::CopyPath(): Copied ( ");
												COMMON_LOG_INFO(absPathSrc.c_str());
												COMMON_LOG_INFO(" ) to destionation ( ");
												COMMON_LOG_INFO(absPathDestFixedFileName.c_str());
												COMMON_LOG_INFO(" ) successfully.\n");
											}
											else
											{
												// An error occured.
												COMMON_LOG_DEBUG("FileUtills::CopyPath(): Error ( ");
												COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
												COMMON_LOG_DEBUG(" ) was returned from the CopyFile syscall. Unable to copy ( ");
												COMMON_LOG_DEBUG(absPathSrc.c_str());
												COMMON_LOG_DEBUG(" ) to destionation ( ");
												COMMON_LOG_DEBUG(absPathDestFixedFileName.c_str());
												COMMON_LOG_DEBUG(" ).\n");

												// If ret was invalid argument change it to internal error.
												if (ret == COMMON_ERROR_INVALID_ARGUMENT)
												{
													ret = COMMON_ERROR_INTERNAL_ERROR;
												}
											}
										}
										else
										{
											// Copy using the CopyPathData() function.
										}
								}
								else
								{
									// We got success without a result.
									ret = COMMON_ERROR_INTERNAL_ERROR;
									COMMON_LOG_WARNING("FileUtills::CopyPath(): ");
									COMMON_LOG_WARNING(Common::Get_Error_Message(ret));
									COMMON_LOG_WARNING(" FileUtills::GetLastPathSegment() returned an invalid path while indicating success. Please report this bug.\n");
								}
							}
							else
							{
								// Log the error.
								

								// Could not copy the file name.
								if (ret == COMMON_ERROR_INVALID_ARGUMENT)
								{
									// Set this to internal error.
									ret = COMMON_ERROR_INTERNAL_ERROR;
								}
							}
						}
						else
						{
							// An error occured.
						}
					}
				}
			}
			else
			{
				// Check and see if the source is a directory.
				if (ret == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
				{
					// Check and see if copy recursive is false.
					if (recursive)
					{
						// Check and see if the destionation exists.
						ret = FileUtills::IsFileOrDirectory_Helper(absPathDest);
						if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
						{
							// Destionation path does not exist, assume that the destionation path's
							// last path segment is the name to use for the copied directory.

							// Check and see if the parent exists.
							ret = FileUtills::CheckParent_Helper(absPathDest, true, true, true);
							if (ret == COMMON_ERROR_SUCCESS)
							{
								// Ok, create the destionation path.
								ret = FileUtills::CreateDirectory_Helper(absPathDest);
								if (ret != COMMON_ERROR_SUCCESS)
								{
									// We cannot create the destionation directory.
									COMMON_LOG_INFO("FileUtills::CopyPath(): Cannot copy source ( ");
									COMMON_LOG_INFO(absPathSrc.c_str());
									COMMON_LOG_INFO(" ) to destionation ( ");
									COMMON_LOG_INFO(absPathDest.c_str());
									COMMON_LOG_INFO(" ) unable to create destionation directory. Aborting.\n");
								}
							}
							else
							{
								// An error occured.
							}
						}
						else
						{
							// Check and see if the destionation is a pre-existing directory.
							// If the destionation is a pre-existing directory, assume we need
							// to merge the source directory's contents with the destionation's
							// contents.
							if (ret != FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
							{
								// Check and see if the destionation path is a file.
								if ((ret == COMMON_ERROR_SUCCESS) || (ret == FILEUTILLS_ERROR_PATH_IS_A_FILE))
								{
									// Indicate failure.
									ret = FILEUTILLS_ERROR_PATH_IS_A_FILE;

									// Cannot overwrite a file with a directory.
									COMMON_LOG_INFO("FileUtills::CopyPath(): Cannot copy source ( ");
									COMMON_LOG_INFO(absPathSrc.c_str());
									COMMON_LOG_INFO(" ) to destionation ( ");
									COMMON_LOG_INFO(absPathDest.c_str());
									COMMON_LOG_INFO(" ) Cannot overwrite a pre-existing file with a directory. Aborting.\n");
								}
								else
								{
									// An error occured.
								}
							}
						}
					  
						// Check and see if we can continue. (If the destionation path was non-existant then ret would be COMMON_ERROR_SUCCESS if the directory was created.)
						if ((ret == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY) || (ret == COMMON_ERROR_SUCCESS))
						{
							// Begin try block.
							try {
								// Begin recursion loop.
							}
							catch (exception &ex)
							{
								// Exception thrown.
								ret = COMMON_ERROR_EXCEPTION_THROWN;

								// Log the error.
								COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
								COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
								COMMON_LOG_DEBUG(" ");
								COMMON_LOG_DEBUG(ex.what());
								COMMON_LOG_DEBUG("\n");
							}
						}
					}
					else
					{
						// Cannot copy a directory if recursion is disabled by the caller.
						COMMON_LOG_DEBUG("FileUtills::CopyPath(): Cannot copy source ( ");
						COMMON_LOG_DEBUG(absPathSrc.c_str());
						COMMON_LOG_DEBUG(" ) to destionation ( ");
						COMMON_LOG_DEBUG(absPathDest.c_str());
						COMMON_LOG_DEBUG(" ) because recursion is disabled by the caller. Aborting.\n");
					}
				}
				else
				{
					// An error occured.
				}
			}
		  
			
				// Run copy loop.
				for (size_t x = (MINIMAL_VALID_ABSOLUTE_PATH_LENGTH + 1); ((x < absPath.size()) && (result == COMMON_ERROR_SUCCESS)); x++)
				{
					// Search for the next DIR_SEP, or the end of the given path string.
					if ((absPath[x] == DIR_SEP) || ((x + 1) == absPath.size()))
					{
						// This is the end of the next path segment, create the needed substring and create the directory.
						try {
							// Allocate memory buffer.
							if (absPath[x] != DIR_SEP)
							{
								// Allocate an extra character only if we are before a directory seperator.
								pCurrentPathSegment = (char*)malloc((x + 1));
							}
							else
							{
								// If the current char is a directory seperator, then we need to allocate only the current x value.
								pCurrentPathSegment = (char*)malloc(x);
							}

							// Check and make sure we got the memory allocated.
							if (pCurrentPathSegment != NULL)
							{
								// Check and see if the current char is a DIR_SEP. (Controls how much of the source buffer we need to copy.)
								if (absPath[x] != DIR_SEP)
								{
									// Copy the data.
									for (size_t y = 0; (y < (x + 1)); y++)
									{
										pCurrentPathSegment[y] = absPath[y];
									}

									// Terminate the string. (Arrays start at zero, x is the last valid character in the string.)
									pCurrentPathSegment[x] = '\0';
								}
								else
								{
									// Copy the data.
									for (size_t y = 0; (y < x); y++)
									{
										pCurrentPathSegment[y] = absPath[y];
									}

									// Terminate the string. (Arrays start at zero, (x - 1) is the last valid character in the string.)
									pCurrentPathSegment[(x - 1)] = '\0';
								}

								// Now create the path. (Issue system call.)
								if ((FileUtills::CreateDirectory_Syscall(pCurrentPathSegment) != COMMON_ERROR_SUCCESS) || (Common_commonLastErrorCode != COMMON_ERROR_SUCCESS))
								{
									// Check and see if the error code is FILEUTILLS_ERROR_EXISTANT. (This is only an error if the final directory segment cannot be created.)
									if ((Common_commonLastErrorCode != FILEUTILLS_ERROR_EXISTANT) || ((Common_commonLastErrorCode == FILEUTILLS_ERROR_EXISTANT) && ((x + 1) >= absPath.size())))
									{
										// Copy the error.
										result = Common_commonLastErrorCode;

										// Log the error if needed.
										COMMON_LOG_INFO("FileUtills::CreateDirectory(): ");
										COMMON_LOG_INFO(Common::Get_Error_Message(result));
										COMMON_LOG_INFO(" Unable to create directory ( ");
										COMMON_LOG_INFO(pCurrentPathSegment);
										COMMON_LOG_INFO(" ), aborting.\n");

										// Force the loop to exit.
										x = absPath.size();
									}
								}
								else
								{
									// Report success.
									COMMON_LOG_INFO("FileUtills::CreateDirectory(): Created directory ( ");
									COMMON_LOG_INFO(pCurrentPathSegment);
									COMMON_LOG_INFO(" )\n");
								}

								// Deallocate the buffer.
								if (pCurrentPathSegment != NULL)
								{
									free(pCurrentPathSegment);
									pCurrentPathSegment = NULL;
								}
							}
							else
							{
								// Could not allocate memory.
								result = COMMON_ERROR_MEMORY_ERROR;
								COMMON_LOG_DEBUG("FileUtills::CreateDirectory(): ");
								COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
								COMMON_LOG_DEBUG("\n");

								// Force loop to exit.
								x = absPath.size();
							}
						}
						catch(exception &ex)
						{
							// Exception thrown.
							result = COMMON_ERROR_EXCEPTION_THROWN;
							COMMON_LOG_DEBUG("FileUtills::CreateDirectory(): ");
							COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
							COMMON_LOG_DEBUG(" ");
							COMMON_LOG_DEBUG(ex.what());
							COMMON_LOG_DEBUG("\n");

							// Force loop to exit.
							x = absPath.size();
						}
					}
				}
			}
		}
		else
		{
			// Invalid destionation path.
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG(" Given destionation path is invalid.\n");
		}
	}
	else
	{
		// Invalid source path.
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given source path is invalid.\n");
	}

	// Copy ret to Common_commonLastErrorCode.
	Common_commonLastErrorCode = ret;

	// Return the result.
	return ret; 
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
		// Init vars.
		bool done = false;				// Used to know when to exit the recursive iterator loop.
		bool resetIterLoop = false;			// Used to control resetting the recursive iterator loop.
		bool unableToCopyAll = false;			// Used to know if a file copy failed while recursively copying files.
		int result = COMMON_ERROR_UNKNOWN_ERROR;	// Used to store results from calls to other functions.
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
		if (result == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)	// Directory.
		{
				// Copy the src path to the currentabspath_src and the dest path to the currentabspath_dest var.
				currentabspath_src = src;
				currentabspath_dest = dest;

				// OK, check and see if the dest directory exists.
				result = FileUtills::IsFileOrDirectory(currentabspath_dest);
				if (result == FILEUTILLS_ERROR_NON_EXISTANT) // Directory does not exist.
				{
					// Create the dest directory.
					result = FileUtills::CreateDirectory(currentabspath_dest);
					if (result == COMMON_ERROR_SUCCESS)
					{
						// Set result to FILEUTILLS_ERROR_NON_EXISTANT, so that we know we can continue.
						result = FILEUTILLS_ERROR_NON_EXISTANT;
					}
					else
					{
						// OK, we can't create the dest directory.
						COMMON_LOG_DEBUG("FileUtills::CopyPath(): Could not create destionation directory, aborting.\n");
					}
				}
				else
				{
					if (result != FILEUTILLS_ERROR_EXISTANT)		// Dest Directory exists.
					{
						if (result == COMMON_ERROR_SUCCESS)
						{
							// This is some special file, so we can't overwrite it.
							COMMON_LOG_DEBUG("FileUtills::CopyPath(): Destionation is a special file, will not overwrite it, aborting.\n");
						}
						else
						{
							// Some other error.
							COMMON_LOG_DEBUG("FileUtills::CopyPath(): Unable to check destionation, returned error was: ");
							COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
							COMMON_LOG_DEBUG("\n");
						}
					}
				}

				// Make sure that result == 0. (I.e. that we can continue.)
				if ((result == FILEUTILLS_ERROR_NON_EXISTANT) || (result == FILEUTILLS_ERROR_EXISTANT))
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
										result = Common_commonLastErrorCode;

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
												case COMMON_ERROR_SUCCESS:         // Not a file or directory. (Try to copy anyway.)
												case FILEUTILLS_ERROR_PATH_IS_A_FILE:         // File.
													// Attempt to copy file.
													result = FileUtills::CopyFile(src_path, dest_path, false, 0, 0);
													if (result != COMMON_ERROR_SUCCESS)
													{
															if (result == COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED)	// If result does = -3 (CopyFile), or -33 (IsFileOrDirectory) it means the OS / Arch is unsupported by CopyFile().
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
												case FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY:         // Directory.
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
												case COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED:        // OS not supported.
													if (plist != NULL)
													{
															delete plist;
															plist = NULL;
													}
													break;
												case COMMON_ERROR_ACCESS_DENIED:        // Permission error.
												case COMMON_ERROR_INVALID_ARGUMENT:        // Arg error.
												case FILEUTILLS_ERROR_NON_EXISTANT:        // Path componet does not exist.
												case FILEUTILLS_ERROR_PATH_FILE_AS_DIRECTORY:        // Part of path is a file.
												case COMMON_ERROR_MEMORY_ERROR:        // Memory error.
												default:
													// Set unableToCopyAll.
													unableToCopyAll = true;
													break;
										};

										// Check to see if reset flag is set, if we hit OS / Arch unsupported, or if we failed and the user requested abort on failure.
										if ((resetIterLoop) || (result == COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED) || ((unableToCopyAll) && (abort_on_failure)))
										{
												// Get out of this loop.
												break;
										}
								}

								// Check to see how the previous loop exited.
								if ((result == COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED) || ((abort_on_failure) && (unableToCopyAll)))
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
												if (result == FILEUTILLS_ERROR_NON_EXISTANT)	// Directory does NOT exist.
												{
														// Create subdirectory.
														result = FileUtills::CreateDirectory(currentabspath_dest);
														if (result != COMMON_ERROR_SUCCESS)
														{
																if (result == COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED)	// -3 means OS / Arch not supported.
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
														if (result != FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
														{
																// OK, we can't create a directory where a file (or some other filesystem entry) exists.
																unableToCopyAll = true;
														}
														else
														{
																if (result == COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED)	// OS / Arch not supported.
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
																result = COMMON_ERROR_INTERNAL_ERROR;
																done = true;
														}
														currentabspath_dest = FileUtills::GetParent(currentabspath_dest);
														if (currentabspath_dest.size() <= 0)
														{
																// Could not get parent directory.
																result = COMMON_ERROR_INTERNAL_ERROR;
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
				}
		}
		else	// Treat as single file.
		{
			if ((result == COMMON_ERROR_SUCCESS) || (result == FILEUTILLS_ERROR_PATH_IS_A_FILE))
			{
				// Call CopyFile.
				result = FileUtills::CopyFile(src, dest, append, begOffset, endOffset);
			}
			else
			{
				// IsFileOrDirectory() returned an error.
				COMMON_LOG_INFO("FileUtills::CopyPath(): Unable to determine the type of the source path, aborting.\n");
			}
		}

		// Copy result to Common_commonLastErrorCode.
		Common_commonLastErrorCode = result;

		// Return result.
		return result;
}

int FileUtills::MovePath(const std::string & src, const std::string & dest, const bool & overwrite)
{
	// Init vars.
	int result = 0;	// Used for return codes.

	// Dumb check.
	if (src.size() > 0)
	{
		if (dest.size() > 0)
		{
			// Check and see if dest already exists.
			result = FileUtills::DoesExist(dest);
			switch (result)
			{
				case FILEUTILLS_ERROR_EXISTANT:     // Path exists.
				    if (overwrite == true)
				    {
					    // Attempt to delete dest path.
					    result = FileUtills::DeletePath(dest, true);
					    switch (result)
					    {
						    case COMMON_ERROR_SUCCESS:     // Delete OK.
							break;
						    default:    // Unable to delete path.
							COMMON_LOG_INFO("FileUtills::MovePath(): Unable to delete destionation path, aborting.\n");
							break;
					    };
				    }
				    else
				    {
					    // Can't delete existing path bail out.
					    COMMON_LOG_INFO("FileUtills::MovePath(): Destionation path already exists. Caller has disabled overwriting pre-existing paths, aborting.\n");
					    break;
				    }
				    break;
				case FILEUTILLS_ERROR_NON_EXISTANT:    // Path does not exist.
				    break;
				default:    // Some error.
				    COMMON_LOG_VERBOSE("FileUtills::MovePath(): Unable to determine if the destionation path already exists. Aborting.\n");
				    break;
			};

			// Check to see if we can continue.
			if ((result == FILEUTILLS_ERROR_NON_EXISTANT) || (result == COMMON_ERROR_SUCCESS))
			{
				// Copy entire path to the dest.
				result = FileUtills::CopyPath(src, dest);
				switch (result)
				{
					case COMMON_ERROR_SUCCESS:     // Copy ok.
					    break;
					default:    // Some error.
					    COMMON_LOG_INFO("FileUtills::MovePath(): Unable to copy data from source to destionation, aborting.\n");
					    break;
				};

				// Check to see if the copy was successful.
				if (result == COMMON_ERROR_SUCCESS)
				{
					// Delete original path.
					result = FileUtills::DeletePath(src, true);
					switch (result)
					{
						case COMMON_ERROR_SUCCESS:     // Delete ok.
						    COMMON_LOG_INFO("FileUtills::MovePath(): Source path moved to destionation path successfully.\n");
						    break;
						default:    // Some error.
						    COMMON_LOG_WARNING("FileUtills::MovePath(): Source path copied to destionation path successfully, but we were unable to delete the source path. Returning error: ");
						    COMMON_LOG_WARNING(Common::Get_Error_Message(result));
						    COMMON_LOG_WARNING("\n");
						    break;
					};
				}
			}
		}
		else
		{
			// Dest is invalid.
			result = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_INFO("FileUtills::MovePath(): Invalid destionation path, aborting.\n");
		}
	}
	else
	{
		// Invalid source path.
		result = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_INFO("FileUtills::MovePath(): Invalid source path, aborting.\n");
	}

	// Copy result to Common_commonLastErrorCode.
	Common_commonLastErrorCode = result;

        // Default return.
        return result;
}
