/*!
    Multiverse Engine Project 04/8/2014 FileUtills FileUtills_Private_API.cpp

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

int FileUtills::IsAbsolutePathReference(const char * path, const size_t pathSize)
{
	/* Call C function. */
	return (FileUtills_IsAbsolutePathReference(path, pathSize));
}

int FileUtills::IsAbsolutePathReference(const char * path, const size_t pathSize, char ** absRef, size_t * absRefSize)
{
	/* Call C function. */
	return (FileUtills_IsAbsolutePathReference_absRef(path, pathSize, absRef, absRefSize));
}

int FileUtills::GetPathSegment(const std::string & path, const size_t & currentPathPos, std::string & pathSegment, const bool & blankPathSegment)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		// The result of this function.

	// Blank pathSegment if needed.
	if (blankPathSegment)
	{
		pathSegment.clear();
	}

	// Check for valid path.
	if (path.capacity > 0)
	{
		// Check for a valid path position.
		if (currentPathPos > 0)
		{
			// Make sure the path position is within the path buffer.
			if (currentPathPos < path.capacity())
			{
				// Copy the path segment from output. (Search from the given currentPathPos offset.)
				for (size_t y = 0; ((y < path.capacity()) && (result == COMMON_ERROR_UNKNOWN_ERROR)); y++)
				{
					// Look for the DIR_SEP.
					if (path[(currentPathPos - y)] == DIR_SEP)
					{
						// Decrement y, as we don't want to copy the directory seperator.
						y--;

						// This position is the start of the directory segment.
						for (size_t z = 0; ((z < y) && (((currentPathPos - y) + z) < path.capacity())); z++)
						{
							// Blank the value.
							pathSegment += path[((currentPathPos - y) + z)];
						}

						// Set result.
						result = COMMON_ERROR_SUCCESS;
					}
				}

				// If we get here and result is still COMMON_UNKNOWN_ERROR, then the path did not have a directory seperator in it.
				if (result == COMMON_ERROR_UNKNOWN_ERROR)
				{
					result = COMMON_ERROR_SUCCESS;
				}
			}
			else
			{
				// currentPathPos is beyond the end of the path buffer.
				result = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_VERBOSE("FileUtills::GetPathSegment(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(result));
				COMMON_LOG_VERBOSE(" current path position is beyond the end of the path buffer. (Nice try.)\n");
			}
		}
		else
		{
			// Invalid currentPathPos.
			result = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE("FileUtills::GetPathSegment(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(result));
			COMMON_LOG_VERBOSE(" current path position is invalid.\n");
		}
	}
	else
	{
		// Invalid path.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::GetPathSegment(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::GetLastPathSegment(const std::string & path, std::string & pathSegment, const bool & blankPathSegment)
{
	// Init fake currentPathPos.
	size_t currentPathPos = path.size();

	// Check for valid path size. (No need to check for false here. If this is false, then the real function will return COMMON_ERROR_INVALID_ARGUMENT. (It does it's own check.))
	if (currentPathPos > 0)
	{
		// Make sure currentPathPos is less than it's size.
		currentPathPos--;
	}

	// Call the GetPathSegment() function.
	return (FileUtills::GetPathSegment(path, currentPathPos, pathSegment));
}

int FileUtills::RemoveLastPathSegment(std::string & path, size_t * currentPathPos)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* Result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* Result code of other engine functions. */
	size_t pathSize = 0;							/* The given path's size. */
	char * tempPath = NULL;							/* Temporary pointer to construct the result string. */
	std::string resultStr = "";						/* The result string of this function. */

	/* Get the path size. */
	pathSize = path.size();

	/* Copy the string to a C-style string. */
	retFromCall = DataProcess::CopyStdStringToCString(path, &tempPath);
	if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPath != NULL))
	{
		/* Call C function. */
		ret = FileUtills_RemoveLastPathSegmentAtPosition(&tempPath, &pathSize, currentPathPos);
		if ((ret == COMMON_ERROR_SUCCESS) && (tempPath != NULL) && (pathSize > 0))
		{
			/* OK, copy the result path to the path var. */
			retFromCall = DataProcess::CopyCStringToStdString(tempPath, &pathSize, &resultStr);
			if (retFromCall != NULL)
			{
				/* Deallocate the C style string. */
				DataProcess_Deallocate_CString(&tempPath);

				/* Copy the resultStr to the path variable. */
				path = resultStr;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Could not copy c string to std::string. */
				ret = retFromCall;
				COMMON_LOG_DEBUG("FileUtills::RemoveLastPathSegment(): Could not copy result string to path argument.");
			}
		}
	}
	else
	{
		/* No path given. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills_RemoveLastPathSegment(): ");
		COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_VERBOSE(" No valid path given.");
	}

	/* Deallocate the tempPath string if needed. */
	if (tempPath != NULL)
	{
		DataProcess_Deallocate_CString(&tempPath);
	}

	/* Return the result. */
	return ret;
}

int FileUtills::RemoveLastPathSegment(std::string & path)
{
	/* Init vars. */
	size_t fakeCurrentPathPos = 0;	/* Fake variable to satisfy FileUtills_RemoveLastPathSegmentAtPosition()'s arugment list. */

	/* Call FileUtills::RemoveLastPathSegment() and return it's result. */
	return (FileUtills::RemoveLastPathSegment(path, &fakeCurrentPathPos));
}

FileUtills::dirlist * FileUtills::getDirectory_Helper(const std::string & absPath, const bool & cleanList)
{
	// Init vars.
	int errcode_SortFunct = 0;			// The returned error code from DataProcess::DecrementingSort().
	FileUtills::dirlist * ret = NULL;		// The constructed directory list.

	// Dumb check.
	if (absPath.size() > 0)
	{
		// Call syscall.
		ret = FileUtills::getDirectory_Syscall(absPath, cleanList);
		if ((Common::commonLastErrorCode == COMMON_ERROR_SUCCESS) && (ret != NULL))
		{
			// If we are cleaning the list, call DataProcess::DecrementingSort().
			if (cleanList)
			{
				errcode_SortFunct = DataProcess::DecrementingSort(ret->list);
				if (errcode_SortFunct != 0)
				{
					// An exception was thrown in the DecrementingSort() function, bail out.
					if (ret != NULL)
					{
						delete ret;
						ret = NULL;
					}

					// Internal error.
					Common::commonLastErrorCode = COMMON_ERROR_INTERNAL_ERROR;

					// Log the error.
					COMMON_LOG_VERBOSE("FileUtills::getDirectory(): The call to DataProcess::DecrementingSort() failed, Aborting.\n");
				}
			}
		}
		else
		{
			// Check for SUCCESS but no list.
			if ((Common::commonLastErrorCode == COMMON_ERROR_SUCCESS) && (ret == NULL))
			{
				// Bug in the syscall.
				Common::commonLastErrorCode = COMMON_ERROR_INTERNAL_ERROR;
				COMMON_LOG_WARNING("FileUtills::getDirectory(): ");
				COMMON_LOG_WARNING(Common::Get_Error_Message(Common::commonLastErrorCode));
				COMMON_LOG_WARNING(" The syscall returned an invalid directory list, but indicated success. Please report this bug.\n");
			}
			else
			{
				// An error occured in the syscall.
				if (ret != NULL)
				{
					delete ret;
					ret = NULL;
				}

				// Check for invalid argument.
				if (Common::commonLastErrorCode == COMMON_ERROR_INVALID_ARGUMENT)
				{
					// OK the syscall is bugged.
					Common::commonLastErrorCode = COMMON_ERROR_INTERNAL_ERROR;
					COMMON_LOG_WARNING("FileUtills::getDirectory(): ");
					COMMON_LOG_WARNING(Common::Get_Error_Message(Common::commonLastErrorCode));
					COMMON_LOG_WARNING(" Syscall returned invalid argument, please report this bug.\n");
				}
			}
		}
	}
	else
	{
		// Invalid path.
		Common::commonLastErrorCode = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills::getDirectory(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Return the result.
	return ret;
}

int FileUtills::GetGigaFreespace_Helper(const std::string & absPath, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// Result of this function.

	// Issue syscall.
	ret = FileUtills::GetByteFreespace_Syscall(absPath, result);

	// Check for success.
	if (ret == COMMON_ERROR_SUCCESS)
	{
		// Byte conversion.
		result = (result / ((double)1000000000));
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::GetFreespace_Helper(const std::string & absPath, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// Result of this function.

	// Issue syscall.
	ret = FileUtills::GetByteFreespace_Syscall(absPath, result);

	// Check for success.
	if (ret == COMMON_ERROR_SUCCESS)
	{
		// Byte conversion.
		result = (result / ((double)1000000));
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::GetKiloFreespace_Helper(const std::string & absPath, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// Result of this function.

	// Issue syscall.
	ret = FileUtills::GetByteFreespace_Syscall(absPath, result);

	// Check for success.
	if (ret == COMMON_ERROR_SUCCESS)
	{
		// Byte conversion.
		result = (result / ((double)1000));
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::GetByteFreespace_Helper(const std::string & absPath, size_t & result)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// Result of this function.

	// Issue syscall.
	ret = FileUtills::GetByteFreespace_Syscall(absPath, result);

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::CreateDirectory_Helper(const std::string & absPath, const bool & createRecursive)
{
	// Init vars.
	int result = COMMON_ERROR_SUCCESS;	// Used to hold the result of this function.
	char * pCurrentPathSegment = NULL;		// Used to allocate memory for a substring that contains the current path segment.

	// Check for valid absPath.
	if (absPath.size() > 0)
	{
		// Check and see if create recursive is false.
		if (!createRecursive)
		{
			// Check and see if the parent directory exists.
			result = FileUtills::CheckParent(absPath);
			if (result == COMMON_ERROR_SUCCESS)
			{
				// Attempt to create the directory path. (Issue syscall.)
				result = FileUtills::CreateDirectory_Syscall(absPath.c_str());
				if ((result != COMMON_ERROR_SUCCESS) || (Common::commonLastErrorCode != COMMON_ERROR_SUCCESS))
				{
					// Log the error if needed.
					COMMON_LOG_INFO("FileUtills::CreateDirectory(): Error returned while attempting to create directory ( ");
					COMMON_LOG_INFO(absPath.c_str());
					COMMON_LOG_INFO(" ) ");
					COMMON_LOG_INFO(Common::Get_Error_Message(result));
					COMMON_LOG_INFO(" Aborting.\n");
				}
				else
				{
					COMMON_LOG_INFO("FileUtills::CreateDirectory(): Created directory ( ");
					COMMON_LOG_INFO(absPath.c_str());
					COMMON_LOG_INFO(" )\n");
				}
			}
			else
			{
				// Unable to create directory.
				COMMON_LOG_INFO("FileUtills::CreateDirectory(): Unable to create directory ( ");
				COMMON_LOG_INFO(absPath.c_str());
				COMMON_LOG_INFO(" ) as the parent directory does not exist or is inaccessable, and recursive directory creation is disabled by the caller. Aborting.\n");
			}
		}
		else
		{
			// Run directory creation loop.
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
							if ((FileUtills::CreateDirectory_Syscall(pCurrentPathSegment) != COMMON_ERROR_SUCCESS) || (Common::commonLastErrorCode != COMMON_ERROR_SUCCESS))
							{
								// Check and see if the error code is FILEUTILLS_ERROR_EXISTANT. (This is only an error if the final directory segment cannot be created.)
								if ((Common::commonLastErrorCode != FILEUTILLS_ERROR_EXISTANT) || ((Common::commonLastErrorCode == FILEUTILLS_ERROR_EXISTANT) && ((x + 1) >= absPath.size())))
								{
									// Copy the error.
									result = Common::commonLastErrorCode;

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
		// Invalid path.
		result = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills::CreateDirectory(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");	
	}

	// Copy result to Common::commonLastErrorCode.
	Common::commonLastErrorCode = result;

	// Return the result.
	return result;
}

int FileUtills::CheckPermissions_Helper(const std::string & absPath, const bool & read, const bool & write, const bool & exec)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// The result of this function.

	// Call syscall.
	ret = FileUtills::CheckPermissions_Syscall(absPath, read, write, exec);
	if (ret != COMMON_ERROR_SUCCESS)
	{
		// Check for INVALID_ARGUMENT.
		if (ret == COMMON_ERROR_INVALID_ARGUMENT)
		{
			// This is an internal error. (The caller does not need to see the invalid argument error.)
			ret = COMMON_ERROR_INTERNAL_ERROR;

			// Log the error.
			COMMON_LOG_WARNING("FileUtills::CheckPermissions(): ");
			COMMON_LOG_WARNING(Common::Get_Error_Message(ret));
			COMMON_LOG_WARNING(" Misbehaving syscall, returned invalid argument. Please report this bug.\n");
		}
	}

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::CheckParent_Helper(const std::string & path, const bool & read, const bool & write, const bool & exec)
{
	// Init vars.
	int result = COMMON_ERROR_UNKNOWN_ERROR;			// Result of this function.
	std::string absPath = path;						// Absolute version of the given path.

	// Check for valid path.
	if (absPath.size() > 0)
	{
		// Get the parent path.
		result = FileUtills::RemoveLastPathSegment(absPath);
		if (result == COMMON_ERROR_SUCCESS)
		{
			// Call the other functions
			result = FileUtills::CheckPermissions_Helper(absPath, read, write, exec);

			// Log the result.
			COMMON_LOG_INFO("FileUtills::CheckParent(): Path ( ");
			COMMON_LOG_INFO(absPath.c_str());
			COMMON_LOG_INFO(" ) ");

			// Check the result
			switch (result)
			{
				// Successful.
				case COMMON_ERROR_SUCCESS:
				    COMMON_LOG_INFO("exists and is accessable with the requested permissions.\n"); 
				    break;
				// Permission error.
				case COMMON_ERROR_ACCESS_DENIED:
				    COMMON_LOG_INFO("Status unknown. A permissions error was encountered while performing the needed checks.\n");
				    break;
				// Parent Does not exist.
				case FILEUTILLS_ERROR_NON_EXISTANT:
				    COMMON_LOG_INFO("does not exist.\n");
				    break;
				// Unknown error.
				default:
				    COMMON_LOG_INFO("Call to CheckPermissions() failed, unable to check parent's permissions or existance.\n");
				    break;
			};
		}
		else
		{
			// Log the error.
			COMMON_LOG_VERBOSE("FileUtills::CheckParent(): Unable to get absolute path of parent directory, aborting.\n");

			// Set result to COMMON_ERROR_INTERNAL_ERROR. (Caller should not see the invalid argument error.)
			result = COMMON_ERROR_INTERNAL_ERROR;
		}
	}
	else
	{
		// Invalid path.
		result = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_DEBUG("FileUtills::CheckParent(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Copy result to Common::commonLastErrorCode.
	Common::commonLastErrorCode = result;

	// Return the result.
	return result;
}

int FileUtills::DoesExist_Helper(const std::string & absPath)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		// The result of this function.
  
	// Check for invalid absPath.
	if (absPath.size() > 0)
	{
		// Call the syscall.
		ret = FileUtills::DoesExist_Syscall(absPath);

		// Get error code.
		switch (ret) {
			case FILEUTILLS_ERROR_EXISTANT:		// Path exists.
			    // Log existance if needed.
			    COMMON_LOG_INFO("FileUtills::DoesExist(): Path ( ");
			    COMMON_LOG_INFO(absPath.c_str());
			    COMMON_LOG_INFO(" ) exists.\n");
			    break;
			default:	// Error occured.
			    // Check for non-existing path error.
			    if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
			    {
				    // Path does not exist.
				    COMMON_LOG_INFO("FileUtills::DoesExist(): Path ( ");
				    COMMON_LOG_INFO(absPath.c_str());
				    COMMON_LOG_INFO(" ) does not exist.\n");
			    }
			    else
			    {
				    // Log the error.
				    COMMON_LOG_DEBUG("FileUtills::DoesExist(): An error occured while checking existance of path: ");
				    COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
				    COMMON_LOG_DEBUG("\n");
			    }
			    break;
		};
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

	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::DeletePath_Helper(const std::string & absPath, const bool & recursive)
{
	// Init vars.
	bool unableToDeleteAll = false;			// Used to tell if we could not delete something while deleting recursively.
	int result = COMMON_ERROR_UNKNOWN_ERROR;	// Used to store results from calls to other functions.
	size_t currentEntry = 0;			// Used by the recursion loop to indicate the current entry in the directory listing that it is working on.
	std::string currentAbsPath = "";		// Used to contain the current absolute path.
	std::string tempPath = "";			// Used to construct temporary paths.
	FileUtills::dirlist * pList = NULL;		// Used to store paths for recursive deletions.

	// Check path string.
	if (absPath.size() > 0)
	{
		// Determine the type of path given.
		result = FileUtills::IsFileOrDirectory_Helper(absPath);
		switch (result)
		{
			case COMMON_ERROR_SUCCESS:
			case FILEUTILLS_ERROR_PATH_IS_A_FILE:
				// Attempt to delete the file.
				result = FileUtills::DeletePath_Syscall(absPath);
				if (result == COMMON_ERROR_SUCCESS)
				{
					// Log the success.
					COMMON_LOG_INFO("FileUtills::DeletePath(): Deleted ( ");
					COMMON_LOG_INFO(absPath.c_str());
					COMMON_LOG_INFO(" ) from the filesystem.\n");
				}
				else
				{
					// Log the failure.
					COMMON_LOG_INFO("FileUtills::DeletePath(): Unable to delete ( ");
					COMMON_LOG_INFO(absPath.c_str());
					COMMON_LOG_INFO(" ) from the filesystem. The returned error was: ");
					COMMON_LOG_INFO(Common::Get_Error_Message(result));
					COMMON_LOG_INFO("\n");
				}
				break;
			case FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY:
				// If we have recursive set to true we can delete the path, else return an error.
				if (recursive)
				{
					// Copy the top level path.
					currentAbsPath = absPath;

					// Blank tempPath.
					tempPath.clear();

					// Begin recursive deletion loop.
					do
					{
						// Delete the current directory list.
						if (pList != NULL)
						{
							delete pList;
							pList = NULL;
						}

						// OK we need to get the paths of every file in the directory and any other directories.
						pList = FileUtills::getDirectory(currentAbsPath, true);
						if ((Common::commonLastErrorCode == COMMON_ERROR_SUCCESS) && (pList != NULL))
						{
							// Set currentEntry to zero.
							currentEntry = 0;

							// Check to see if tempPath is defined.
							if (tempPath.size() > 0)
							{
								// Ok, we just swapped out of a subdirectory, so we need to skip to it in the list and delete it.
								for (size_t x = 0; (x < pList->list.size()); x++)
								{
									// Check for the subdirectory we just finished parsing.
									if (((currentAbsPath + DIR_SEP) + pList->list[x]) == tempPath)
									{
										// Subdirectory entry found, attempt to delete it.
										result = FileUtills::DeletePath_Syscall(tempPath);
										if (result != COMMON_ERROR_SUCCESS)
										{
											// Set unableToDeleteAll.
											unableToDeleteAll = true;
										}

										// Set currentEntry to the next entry in the list. (The reason this works is because the Directory listing is sorted in desending order. Anything in the list prior to this position, we were unable to delete.)
										currentEntry = (x + 1);

										// Clear tempPath.
										tempPath.clear();
									}
								}
							}

							// Begin inner path loop. (Should exit early if we hit a subdirectory, or if we hit a critical error.)
							for (; ((pList != NULL) && (currentEntry < (pList->list.size())) && (result != FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY)); currentEntry++)
							{
								// Construct the path to be deleted.
								tempPath = ((currentAbsPath + DIR_SEP) + pList->list[currentEntry]);

								// Attempt to delete the entry.
								result = FileUtills::DeletePath_Syscall(tempPath);
								if (result != COMMON_ERROR_SUCCESS)
								{
									// Check and see if it's a directory.
									if (result == FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY)
									{
										// Update currentAbsPath to add the new subdirectory.
										currentAbsPath = ((currentAbsPath + DIR_SEP) + pList->list[currentEntry]);
									}
									else
									{
										// Skip the entry and continue.
										unableToDeleteAll = true;
									}
								}
							}

							// Blank tempPath.
							tempPath.clear();

							// Check to see if the directory list we just finished parsing is for the given path from the caller.
							if ((currentAbsPath != absPath) && (result != FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY))
							{
								// OK, copy currentAbsPath to tempPath so that the next loop will check the parent directory for currentAbsPath's entry in the list.
								tempPath = currentAbsPath;

								// Now call FileUtills::RemoveLastPathSegment() on the currentAbsPath, so we can get the parent directory's entry list on the next loop.
								if (FileUtills::RemoveLastPathSegment(currentAbsPath) != COMMON_ERROR_SUCCESS)
								{
									// Could not remove path segment.
									result = COMMON_ERROR_INTERNAL_ERROR;
									COMMON_LOG_INFO("FileUtills::DeletePath(): FileUtills::RemoveLastPathSegment() returned: ");
									COMMON_LOG_INFO(Common::Get_Error_Message(Common::commonLastErrorCode));
									COMMON_LOG_INFO(" Please report this bug, Aborting.\n");
								}
							}
						}
						else
						{
							// Unable to get directory listing, check to see if pList is NULL and Common::commonLastErrorCode is COMMON_ERROR_SUCCESS.
							if ((pList == NULL) && (Common::commonLastErrorCode == COMMON_ERROR_SUCCESS))
							{
								// Internal bug in getDirectory(). (This should never happen.)
								result = COMMON_ERROR_INTERNAL_ERROR;
								COMMON_LOG_WARNING("FileUtills::DeletePath(): ");
								COMMON_LOG_WARNING(" FileUtills::getDirectory() returned an invalid directory listing while indicating success, please report this bug.\n");
							}
							else
							{
								// Preserve the returned error code from getDirectory().
								result = Common::commonLastErrorCode;
							}
						}
					}
					while ((currentAbsPath != absPath) && ((result == COMMON_ERROR_SUCCESS) || (result == FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY)));

					// Reattempt to delete the given top level directory if unableToDeleteAll is not set.
					if (!unableToDeleteAll)
					{
						// Attempt to delete the given top level directory.
						result = FileUtills::DeletePath_Syscall(absPath);
						if (result == COMMON_ERROR_SUCCESS)
						{
							// Success.
							COMMON_LOG_INFO("FileUtills::DeletePath(): Deleted ( ");
							COMMON_LOG_INFO(absPath.c_str());
							COMMON_LOG_INFO(" ) from the filesystem.\n");
						}
						else
						{
							// Unsuccessfull.
							COMMON_LOG_INFO("FileUtills::DeletePath(): Unable to completely delete ( ");
							COMMON_LOG_INFO(absPath.c_str());
							COMMON_LOG_INFO(" ) from the filesystem. The the directory should be empty however. The returned error was: ");
							COMMON_LOG_INFO(Common::Get_Error_Message(result));
							COMMON_LOG_INFO("\n");
						}
					}
					else
					{
						// We were unable to delete the requested path.
						COMMON_LOG_INFO("FileUtills::DeletePath(): Unable to completely delete ( ");
						COMMON_LOG_INFO(absPath.c_str());
						COMMON_LOG_INFO(" ) from the filesystem.\n");
					}
				}
				else
				{
					// Unable to delete a directory if recursive is set to false.
					COMMON_LOG_INFO("FileUtills::DeletePath(): Unable to delete ( ");
					COMMON_LOG_INFO(absPath.c_str());
					COMMON_LOG_INFO(" ) as it's a directory, and recursive deletion was disabled by the caller.\n");
				}
				break;
			default:
				// Log the error.
				COMMON_LOG_INFO("FileUtills::DeletePath(): Unable to delete ( ");
				COMMON_LOG_INFO(absPath.c_str());
				COMMON_LOG_INFO(" ) from the filesystem.\n");
				break;
		};
	}
	else
	{
		// Invalid path argument.
		result = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::DeletePath(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(result));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	// Copy result to Common::commonLastErrorCode.
	Common::commonLastErrorCode = result;

	// Return the result.
	return result;
}

int FileUtills::CopyPath_Helper(const std::string & absPathSrc, const std::string & absPathDest, const bool & recursive,
				const bool & rename, const bool & abort_on_failure,
				const bool & append, const streamsize & begOffset, const streamsize & endOffset)
{
	// Init vars.
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			// The result of this function.

	// Check for valid absPathSrc.
	if (absPathSrc.size() > 0)
	{
		// Check for valid absPathDest.
		if (absPathDest.size() > 0)
		{
			// Ok, Check and see what the source path is.
			ret = FileUtills::IsFileOrDirectory_Helper(absPathSrc);
			if ((ret == FILEUTILLS_ERROR_PATH_IS_A_FILE) || (ret == COMMON_ERROR_SUCCESS))
			{
				// Path is either a regular file or a special file.
				COMMON_LOG_WARNING("FileUtills::CopyPath(): TODO: We can only copy a special file if the system's copy syscall is used. Impliment the copy syscall functions.\n");

				// Check to see if the dest is a file or a directory.
				ret = FileUtills::IsFileOrDirectory_Helper(absPathDest);
				if (ret == FILEUTILLS_ERROR_PATH_IS_A_FILE)
				{
					// Overwrite pre-existing file?
				}
				else
				{
					// Check and see if dest is a directory.
					if (ret == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
					{
						// Copy source file to pre-existing directory.
					}
					else
					{
						// Check for non-existant path.
						if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
						{
							// Check for the parent path's existance.
							ret = FileUtills::CheckParent_Helper(absPathDest);
							if (ret == COMMON_ERROR_SUCCESS)
							{
								// Copy the source file to the destionation path with the given filename instead of it's original filename.
								
							}
							else
							{
								// Check for non-existant error.
								if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
								{
									// We cannot copy something to a non-existant destionation directory.
									COMMON_LOG_DEBUG("FileUtills::CopyPath(): Cannot copy to non-existant destionation directory ( ");
									COMMON_LOG_DEBUG(absPathDest.c_str());
									COMMON_LOG_DEBUG(" ). Please create the destionation directory and try to copy the source again.\n");
								}
								else
								{
									// An error has occured.
									if ()
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
				// Check and see if the source path is a directory.
				if (ret == FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY)
				{
					// Check to see if recursion is enabled.
					if (recursive)
					{
						// OK, begin try block.
						try {
							// Begin directory recursion loop.
							
						  
						}
						catch (execption &ex)
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
					else
					{
						// Cannot copy a directory if recursion is disabled.
						ret = COMMON_ERROR_INVALID_ARGUMENT;

						// Log the error.
						COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
						COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
						COMMON_LOG_DEBUG(" Unable to copy a directory because the caller has disabled recursion, aborting.\n");
					}
				}
				else
				{
					// Log the error.
					COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
					COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
					COMMON_LOG_DEBUG(" was returned while checking the source path's filesystem type, aborting.\n");
				}
			}
		}
		else
		{
			// Invalid destionation path argument.
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
			COMMON_LOG_DEBUG(" Given destionation path is invalid.\n");
		}
	}
	else
	{
		// Invalid source path argument.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::CopyPath(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
		COMMON_LOG_DEBUG(" Given source path is invalid.\n");
	}
	
	// Copy ret to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}
