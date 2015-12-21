/*!
    Multiverse Engine Project 08/8/2015 FileUtills FileUtills_Private_API.c

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
#include "../../../Core/Src/DataProcess.h"	/* For DataProcess Allocators. (DataProcess_Deallocate_C_String(), DataProcess_Reallocate_CString().) */

int FileUtills_Create_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV_T ** obj)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	MSYS_FileUtills_dirList_PRIV_T * tempObj = NULL;	/* The object we are creating. */

	/* Check for invalid pointer argument. */
	if (obj != NULL)
	{
		/* Allocate object. */
		tempObj = (MSYS_FileUtills_dirList_PRIV_T *)malloc((sizeof(MSYS_FileUtills_dirList_PRIV_T)));
		if (tempObj != NULL)
		{
			/* NULL out object. */
			memset(obj, '\0', (sizeof(MSYS_FileUtills_dirList_PRIV_T)));

			/* Copy pointer. */
			(*obj) = tempObj;

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for object. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid pointer. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

void FileUtills_Destroy_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV_T ** obj)
{
	/* Check for valid pointer. */
	if ((obj != NULL) && ((*obj) != NULL))
	{
		/* Deallocate the entry list. */
		MSYS_Linked_List_Deallocate_Entire_List((&((*obj)->list)));

		/* Release the memory. */
		free((*obj));
		(*obj) = NULL;
	}

	/* Exit function. */
	return;
}

int FileUtills_dirList_PRIV_Add_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv,
										const char * entry, const size_t entryLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to another engine function. */
	int allocatedInitialListMemory = 0;				/* Whether or not we allocated the first entry in the list. */
	MSYS_Linked_List_T * allocatedObject = NULL;	/* Pointer to the allocated list entry. */

	/* Check for invalid arguments. */
	if ((dirListPriv != NULL) && (entry != NULL) && (entryLength > 0))
	{
		/* Allocate the linked list object. */
		retFromCall = MSYS_Linked_List_Allocate_And_Return_Linked_List_Object(&(dirListPriv->list), &allocatedObject);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (dirListPriv->list != NULL) && (allocatedObject != NULL))
		{
			/* Increment the number of entries. */
			dirListPriv->numOfEntries++;

			/* Copy the data into the list. */
			retFromCall = MSYS_Linked_List_Set_Current_Object_Contents(allocatedObject, (void *)entry, entryLength, 1);
			if (retFromCall == COMMON_ERROR_SUCCESS)
			{
				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Could not create a copy of the entry data. */
				ret = ((retFromCall != COMMON_ERROR_MEMORY_ERROR) ? (COMMON_ERROR_INTERNAL_ERROR) :
				(COMMON_ERROR_MEMORY_ERROR));

				/* Decrement the number of entries. */
				dirListPriv->numOfEntries--;

				/* Deallocate the allocated list object. */
				MSYS_Linked_List_Deallocate_Linked_List_Object(&allocatedObject);

				/* Log error. */
				if (ret != COMMON_ERROR_MEMORY_ERROR)
				{
					COMMON_LOG_VERBOSE("FileUtills_dirList_PRIV_Add_Entry(): Could not create a copy of the entry data.");
				}
			}
		}
		else
		{
			/* Could not allocate memory for the linked list object. */
			ret = ((retFromCall != COMMON_ERROR_MEMORY_ERROR) ? (COMMON_ERROR_INTERNAL_ERROR) :
					(COMMON_ERROR_MEMORY_ERROR));

			/* Log error. */
			if (ret != COMMON_ERROR_MEMORY_ERROR)
			{
				COMMON_LOG_VERBOSE("FileUtills_dirList_PRIV_Add_Entry(): Could not allocate memory for the linked list object.");
			}
		}
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int FileUtills_dirList_PRIV_Get_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv, const size_t entryOffset,
										char ** entry, size_t * entryLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to another engine function. */
	MSYS_Linked_List_T * iterator = NULL;			/* Iterator used to iterate through the linked list. */
	char * fetchedEntry = NULL;						/* Pointer to data in linked list object. */
	size_t fetchedEntryLength = 0;					/* Length of fetchedEntry. */
	char * returnedEntry = NULL;					/* Pointer to copy of the entry data that is returned to the caller. */
	size_t x = 0;									/* Loop counter. */

	/* Check for invalid arguments. */
	if ((dirListPriv != NULL) && (dirListPriv->list != NULL) && (entry != NULL) && (entryLength != NULL))
	{
		/* Get the first iterator pointer. */
		retFromCall = MSYS_Linked_List_Get_First_Object(dirListPriv->list, &iterator);
		if (retFromCall == COMMON_ERROR_SUCCESS)
		{
			/* Begin iteration loop. (Start at index one as we already have the first entry.) */
			for (x = 1; ((x < entryOffset) && (retFromCall == COMMON_ERROR_SUCCESS) && (iterator != NULL)); x++)
			{
				/* Get the next object. */
				retFromCall = MSYS_Linked_List_Get_Next_Object(iterator, &iterator);
			}

			/* Check for valid iterator. */
			if (iterator != NULL)
			{
				/* Get the contents of the correct entry. */
				retFromCall = MSYS_Linked_List_Get_Current_Object_Contents(iterator, ((void**)(&fetchedEntry)), &fetchedEntryLength, 1);
				if (retFromCall == COMMON_ERROR_SUCCESS)
				{
					/* Check and see if there is entry data at all.... */
					if ((fetchedEntry != NULL) && (fetchedEntryLength > 0))
					{
						/* Copy the new pointer to the caller. */
						(*entry) = fetchedEntry;
						(*entryLength) = fetchedEntryLength;

						/* Done. */
						ret = COMMON_ERROR_SUCCESS;
					}
					else
					{
						/* No entry data. */
						(*entry) = NULL;
						(*entryLength) = 0;

						/* Done. */
						ret = COMMON_ERROR_SUCCESS;
					}
				}
				else
				{
					/* Unable to get object's data contents. */
					ret = COMMON_ERROR_INTERNAL_ERROR;
					COMMON_LOG_VERBOSE("FileUtills_dirList_PRIV_Get_Entry(): Unable to get object's data contents.");
				}
			}
			else
			{
				/* Invalid index. */
				ret = COMMON_ERROR_RANGE_ERROR;
			}
		}
		else
		{
			/* Could not get initial iterator pointer. */
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_VERBOSE("FileUtills_dirList_PRIV_Get_Entry(): Could not get initial iterator pointer.");
		}
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int FileUtills_dirList_PRIV_Remove_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv, const size_t entryOffset)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to another engine function. */
	MSYS_Linked_List_T * iterator = NULL;			/* Iterator used to iterate through the linked list. */
	char * entry = NULL;							/* Pointer to the entry data. */
	size_t entryLength = 0;							/* Length of the entry data. */
	size_t x = 0;									/* Loop counter. */

	/* Check for invalid arguments. */
	if ((dirListPriv != NULL) && (dirListPriv->list != NULL))
	{
		/* Get the first iterator pointer. */
		retFromCall = MSYS_Linked_List_Get_First_Object(dirListPriv->list, &iterator);
		if (retFromCall == COMMON_ERROR_SUCCESS)
		{
			/* Begin iteration loop. (Start at index one as we already have the first entry.) */
			for (x = 1; ((x < entryOffset) && (retFromCall == COMMON_ERROR_SUCCESS) && (iterator != NULL)); x++)
			{
				/* Get the next object. */
				retFromCall = MSYS_Linked_List_Get_Next_Object(iterator, &iterator);
			}

			/* Check for valid iterator. */
			if (iterator != NULL)
			{
				/* Deallocate the entry's linked list object. */
				MSYS_Linked_List_Deallocate_Linked_List_Object(&iterator);

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Non-existant entry. */
				ret = COMMON_ERROR_RANGE_ERROR;
			}
		}
		else
		{
			/* Could not get initial iterator pointer. */
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_VERBOSE("FileUtills_dirList_PRIV_Remove_Entry(): Could not get initial iterator pointer.");
		}
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

void FileUtills_dirList_PRIV_Deallocate_Entry_Data_Copy(char ** data)
{
	/* Check for valid pointer. */
	if ((data != NULL) && ((*data) != NULL))
	{
		/* Deallocate the data. */
		MSYS_Linked_List_Deallocate_Copied_Data(data);
	}

	/* Exit function. */
	return;
}

int FileUtills_IsAbsolutePathReference(const char * path, const size_t pathSize)
{
	/* Call FileUtills_IsAbsolutePathReference_absRef(). */
	return (FileUtills_IsAbsolutePathReference_absRef(path, pathSize, NULL, NULL));
}

int FileUtills_IsAbsolutePathReference_absRef(const char * path, const size_t pathSize, char ** absRef, size_t * absRefLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* Result of this function. */
	char * tempAbsRef = NULL;					/* Temporary variable for construction of absRef. */

	/* Check for a valid arguments. */
	if ((path != NULL) && (pathSize > 0))
	{
		/* Check for a valid string. */
		if (path[0] == '/')	/* Posix style path. */
		{
			/* Valid Posix style path. */
			ret = FILEUTILLS_ERROR_PATH_IS_ABSOLUTE;

			/* OPTIONAL: If absRef and absRefLength are non-NULL attempt to copy the absolute path reference. */
			if ((absRef != NULL) && (absRefLength != NULL))
			{
				/* Allocate memory for absRef. */
				tempAbsRef = (char*)malloc((sizeof(char) * 2));
				if (tempAbsRef != NULL)
				{
					/* Write the data. */
					tempAbsRef[0] = '/';
					tempAbsRef[1] = '\0';

					/* Copy the pointer. */
					(*absRef) = tempAbsRef;

					/* Update the absRefLength. */
					(*absRefLength) = (sizeof(char) * 2);
				}
				else
				{
					/* Could not allocate memory. */
					ret = COMMON_ERROR_MEMORY_ERROR;

					/* Log error. */
					COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
					COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
					COMMON_LOG_VERBOSE(" Unable to allocate memory for absRef buffer.");
				}
			}
		}
		else
		{
			/* Check for a Windows / DOS style path. */
			if ((pathSize > 2) && (path[0] != '\0') && (path[1] == ':') && (path[2] == '\\'))
			{
				/* Valid Windows / DOS style path. */
				ret = FILEUTILLS_ERROR_PATH_IS_ABSOLUTE;

				/* OPTIONAL: If absRef and absRefLength are non-NULL attempt to copy the absolute path reference. */
				if ((absRef != NULL) && (absRefLength != NULL))
				{
					/* Allocate memory for absRef. */
					tempAbsRef = (char*)malloc((sizeof(char) * 4));
					if (tempAbsRef != NULL)
					{
						/* Write the data. */
						tempAbsRef[0] = path[0];
						tempAbsRef[1] = path[1];
						tempAbsRef[2] = path[2];
						tempAbsRef[3] = '\0';

						/* Copy the pointer. */
						(*absRef) = tempAbsRef;

						/* Update the absRefLength. */
						(*absRefLength) = (sizeof(char) * 4);
					}
					else
					{
						/* Could not allocate memory. */
						ret = COMMON_ERROR_MEMORY_ERROR;

						/* Log error. */
						COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
						COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
						COMMON_LOG_VERBOSE(" Unable to allocate memory for absRef buffer.");
					}
				}
			}
			else
			{
				/* Path is not absolute. */
				ret = FILEUTILLS_ERROR_PATH_IS_RELATIVE;
			}
		}
	}
	else
	{
		/* Invalid pointer. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
		COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	/* Return the result. */
	return ret;
}

int FileUtills_ResolvePath_Helper(char ** retStr, size_t * retStrSize)
{
    /* Init vars. */
	bool eraseLoopDone = false;						/* Used to tell when the loop for erasing the current directory segment from the output is done. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code from this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code from another engine function. */
	const char * pCurrentPos = NULL;				/* Used to access the path string. */
	size_t x = 0;									/* Counter used in parsing loop. */
	size_t initalOffset = 0;						/* Used to start parsing at the correct offset if the given path starts with a resolveable identifier. */
	size_t currentOutputPos = 0;					/* Used to store the current position in the output string.
													 * (Reasoning for this is that I can't determine if any of
													 * the insertion operators consider NULL characters to not
													 * be a valid part of the string's value.
													 * (E.x. for the given string: "some\0\0\0" is the current
													 * insertion point 4 or is it 7? Also does the C++ standard
													 * define this, or is the result implimentation defined, or
													 * is this possibly undefined behavour?))
													 */
	char * output = NULL;							/* Result of this function. */
	size_t outputLength = 0;						/* Length of the output string. */
	char * homeDir = NULL;							/* Used if we need to get the home (User profile) directory. */
	size_t homeDirLength = 0;						/* Length of the homeDir string. */
	char * currentDir = NULL;						/* Used if we need to get the current working directory. */
	size_t currentDirLength = 0;					/* Length of the currentDir string. */

	/* Check for invalid args. */
	if ((retStr != NULL) && ((*retStr) != NULL) && (retStrSize != NULL) && ((*retStrSize) > 0))
	{
		/* Results:
		 *
		 * 	Does nothing but copy the path string to the output
		 * 	string if the path is already absolute.
		 *
		 * 	If the path is not absolute, then the path is made
		 * 	absolute before being returned.
		 *
		 * 	Default is to assume the path is Relative.
		 *
		 * 	This function does NOT filter invalid characters in
		 * 	the given path. (Valid characters are filesystem
		 * 	specific. The OS in use may not allow the user to
		 * 	access that information without special privileges.
		 * 	In addition it's not practical for us to maintain a
		 * 	list of valid characters for each filesystem type in
		 * 	existance. (Some OSes may not have an easy mechinism
		 * 	for determining what characters are valid vs. invalid
		 * 	short of attempting to actually use them.)) As such
		 * 	any given invalid character will be retained in the
		 * 	output string if this function succeeds.
		 *
		 * 	Notes: About linux behavior.
		 * 	/foo/bar/../fee translates to /foo/fee. (../ nulls out bar.)
		 * 	/foo/./bar translates to /foo/bar. (./ is ignored or translates to the current path without it.)
		 * 	/foo/./bar/../ translates to /foo. (./ is ignored like above, ../ nulls out bar.)
		 * 	/foo/./bar/../.././ translates to /. (the first ./ is ignored like above, the first ../ nulls out bar, the second ../ nulls out foo, and the last ./ is ignored like above.)
		 * 	/foo/./bar/../../~ results in a no such file or directory error. (Apperently ~ only has a special meaning if it is located at the beginning of the given path string. Also not all shells resolve it.)
		 * 	/foo/./bar/../../$HOME translates to $HOME. (./ is ignored like above, the first ../ nulls out bar, the second ../ nulls out foo, and $ is treated as the start of an enviorment variable. the enviorment variable's name is HOME (the space is the delimiter.))
		 * 	./foo translates to <current working directory>/foo.
		 * 	../foo translates to <parent of the current working directory>/foo.
		 * 	foo translates to <current working directory>/foo.
		 */

		/* Get a pointer to the path string. */
		pCurrentPos = (*retStr);

		/* Make sure we got the pointer. */
		if (pCurrentPos != NULL)
		{
			/* First allocate enough memory for the current path string. */
			retFromCall = DataProcess_Reallocate_C_String(&output, 0, (*retStrSize));
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (output != NULL))
			{
				/* Set the outputLength. */
				outputLength = (*retStrSize);

				/*
				 * 	Check to see if the path is a user profile directory path.
				 *
				 * 	This only has a special meaning if there is a DIR_SEP as the next character,
				 * 	or if it is the only character in the given path string.
				 *
				 * 	If this is not the case, then the HOME_DIR_SYMBOL looses it's special meaning,
				 * 	and is assumed to be a part of the current path segment.
				 */
				if ((pCurrentPos[0] == HOME_DIR_SYMBOL) && ((outputLength == 1) || ((outputLength > 1) && (pCurrentPos[1] == DIR_SEP))))
				{
					/* Get the user profile directory path. */
					ret = FileUtills_GetUserProfileDirectoryPath(&homeDir, &homeDirLength);
					if ((ret == COMMON_ERROR_SUCCESS) && (homeDir != NULL) && (homeDirLength > 0))
					{
						/* Allocate memory for the output string to hold the home dir path. */
						retFromCall = DataProcess_Reallocate_C_String(&output, 0, (outputLength + (homeDirLength)));
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (output != NULL))
						{
							/* Set the length of the output string. */
							outputLength += homeDirLength;

							/* Set the user profile directory. */
							memcpy(output, homeDir, homeDirLength);

							/* Update currentOutputPos. */
							currentOutputPos = homeDirLength;

							/* Set the initial offset. */
							initalOffset = 1;
						}
						else
						{
							/* Unable to reallocate memory for the output string. */
							ret = COMMON_ERROR_MEMORY_ERROR;
						}
					}
					else
					{
						/* Unable to get user profile directory. */
						ret = COMMON_ERROR_INTERNAL_ERROR;
						COMMON_LOG_VERBOSE("FileUtills_ResolvePath(): Unable to get needed user profile directory path, aborting.\n");

						/* Deallocate output. */
						DataProcess_Deallocate_CString(&output);
						outputLength = 0;
					}
				}
				else
				{
					/* Check for an absolute path reference. */
					/* We need to check for a abosolute reference here. (If it is an absolute reference we do nothing.) */
					retFromCall = FileUtills_IsAbsolutePathReference((*retStr), (*retStrSize));
					if (retFromCall == FILEUTILLS_ERROR_PATH_IS_RELATIVE)
					{
						/* The default is to assume that the path is relative to the current working directory. */
						/* Get the current working directory. */
						retFromCall = FileUtills_GetCurrentWorkingDirectoryPath(&currentDir, &currentDirLength);
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (currentDir != NULL) && (currentDirLength > 0))
						{
							/* Allocate memory for the output string to hold the current dir path. */
							retFromCall = DataProcess_Reallocate_C_String(&output, 0, (outputLength + currentDirLength));
							if ((retFromCall == COMMON_ERROR_SUCCESS) && (output != NULL))
							{
								/* Set the length of the output string. */
								outputLength += currentDirLength;

								/* Copy the current working directory. */
								memcpy(output, currentDir, currentDirLength);

								/* Update currentOutputPos. */
								currentOutputPos = currentDirLength;

								/*
								 * 	Continue parsing looking for another dot as we may not be done yet.
								 *
								 * 	If this is not the case, then we assume that the given path is a path
								 * 	segment that starts in the given working directory.
								 */
								if (pCurrentPos[0] == '.')
								{
									/* Check and see if there is something else to parse after the dot. */
									if ((*retStrSize) > 1)
									{
										/* Check for another dot. */
										if (pCurrentPos[1] == '.') /* ".." (Parent directory of the current working directory.) */
										{
											/*
											 * 	Check for the end of the path or that there is another directory seperator present.
											 *
											 * 	If this is not the case then the first two dots loose their special meaning, and we
											 * 	assume that the first two dots are part of the current path segment.
											 * 	(That or the caller made a typo....)
											 */
											if (((*retStrSize) == 2) || (((*retStrSize) > 2) && (pCurrentPos[2] == DIR_SEP)) || (((*retStrSize) == 3) && (pCurrentPos[2] == '\0')))
											{
												/* Erase the last directory segment from the output. */
												retFromCall = FileUtills_RemoveLastPathSegment(&output, &outputLength);
												if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputLength > 0))
												{
													/* Skip the first two dots. */
													initalOffset = 2;
												}
												else
												{
													/* FileUtills_RemoveLastPathSegment() failed. */
													ret = COMMON_ERROR_INTERNAL_ERROR;
													COMMON_LOG_VERBOSE("FileUtills_ResolvePath(): Call to FileUtills_RemoveLastPathSegment() failed, unable to get needed parent directory. Aborting.\n");

													/* Deallocate output. */
													DataProcess_Deallocate_CString(&output);
													outputLength = 0;
												}
											}
										}
									}
									else
									{
										/*
										 * 	The dot is by itself, assumed to be a reference to the
										 * 	current working directory.
										 *
										 * 	(Rather than a reference to a file in the current working
										 * 	directory whose filename is a dot.)
										 */
										initalOffset = 1;
									}
								}
								else
								{
									/* This is the start of a directory entry, so add a DIR_SEP to output and increment currentOutputPos. */
									output[currentOutputPos] = DIR_SEP;
									currentOutputPos++;
								}
							}
							else
							{
								/* Could not allocate memory to hold the currentDir in the output string. */
								ret = COMMON_ERROR_MEMORY_ERROR;
							}
						}
						else
						{
							/* Could not get current working directory. */
							ret = COMMON_ERROR_INTERNAL_ERROR;
							COMMON_LOG_VERBOSE("FileUtills_ResolvePath(): Unable to get needed current working directory path, aborting.\n");

							/* Deallocate output. */
							DataProcess_Deallocate_CString(&output);
							outputLength = 0;
						}
					}
					else
					{
						/* Check for FILEUTILLS_ERROR_PATH_IS_ABSOLUTE. */
						if (retFromCall != FILEUTILLS_ERROR_PATH_IS_ABSOLUTE)
						{
							/* Call to FileUtills_IsAbsolutePathReference() failed. */
							ret = COMMON_ERROR_INTERNAL_ERROR;

							/* Log the error. */
							COMMON_LOG_DEBUG("FileUtills_ResolvePath(): Could not determing if the given path was an absolute path reference, aborting.\n");

							/* Deallocate output. */
							DataProcess_Deallocate_CString(&output);
							outputLength = 0;
						}
					}
				}

				/* Start processing loop. */
				for (x = initalOffset; ((x < (*retStrSize)) && (ret == COMMON_ERROR_UNKNOWN_ERROR)); x++)
				{
					/* Selection switch. */
					switch (pCurrentPos[x])
					{
						case '.':		/* Dot ('.') character. Normally used for indicating
									   the current or parent directory.

									   For the dot character to have a special meaning,
									   one of the following conditions must be true:

										- There must be a DIR_SEP at either the
										(x + 1) or (x + 2) position (but not both) in
										the given path string. (In the case of the
										latter, position (x + 1) must have another
										dot character for (x + 2) to have a meaning.)

										- The dot characters (either "." or "..") must
										be at the end of the given path string, and
										have nothing after them. (The terminating NULL
										byte for c-style strings is permitted however.)

									   If both of these conditions are false, then the
									   dot character is assumed to be part of the
									   current path segment, and therefore loses it's
									   special meaning.
									*/

						/* Check and see if we have at least one character left after the current position. */
						if ((x + 1) < (*retStrSize))
						{
							/* Check for ".<DIR_SEP>" current working directory variant. */
							if (pCurrentPos[(x + 1)] == DIR_SEP)
							{
								/* Increment x to skip checking the directory seperator on the next loop iteration. */
								x++;
							}
							else
							{
									/* Check for ".." variant. (Parent directory.) */
									if (pCurrentPos[(x + 1)] == '.')
									{
										/*
										 *	Determine if we can continue.
										 *
										 * 	/foo/bar/..<NON DIR_SEP> is a valid path.
										 * 	(Yes, ".." only has a special meaning if it's at the end of a path.
										 * 	Otherwise it's considered part of a filesystem entry.
										 * 	Ex. "/foo/bar/..my_filename_begins_with_two_dots" is a valid filename.)
										 */
										if (((x + 2) >= (*retStrSize)) ||
										    (((x + 2) < (*retStrSize)) && ((pCurrentPos[(x + 2)] == DIR_SEP) || (((x + 3) >= (*retStrSize)) && (pCurrentPos[(x + 2)] == '\0')))))
										{
											/* Referening the parent directory. Check to see if we are at the root directory. (No parent path reference can pass beyond the filesystem's root directory.) */
											if (currentOutputPos > MINIMAL_VALID_ABSOLUTE_PATH_LENGTH)
											{
												/* Reset eraseLoopDone. */
												eraseLoopDone = false;

												/* Remove last path segment from output. (Search from the end of the output string.) */
												ret = FileUtills_RemoveLastPathSegment(&output, &outputLength);
												if ((ret == COMMON_ERROR_SUCCESS) && (output != NULL) && (outputLength > 0))
												{
													/* Set eraseLoopDone. */
													eraseLoopDone = true;
												}
												else
												{
													/* FileUtills_RemoveLastPathSegment() failed. */
													ret = COMMON_ERROR_INTERNAL_ERROR;
													COMMON_LOG_VERBOSE("FileUtills_ResolvePath(): Call to FileUtills_RemoveLastPathSegment() failed. Unable to remove current path segment. Aborting.\n");

													/* Deallocate output. */
													DataProcess_Deallocate_CString(&output);
													outputLength = 0;
												}
											}

											/* Check to see if there are at least two characters after the current position. */
											if (((x + 2) < (*retStrSize)) && (pCurrentPos[(x + 2)] == DIR_SEP))
											{
												/* Increment x by 2 to skip the dots and the directory seperator. */
												x += 2;
											}
											else
											{
												/* Increment x to skip the dots. */
												x++;
											}
										}
										else
										{
											/* Allocate memory for adding dot to output string. */
											retFromCall = DataProcess_Reallocate_C_String(&output, outputLength, (outputLength + (sizeof(char))));
											if ((retFromCall == COMMON_ERROR_SUCCESS) && (output != NULL))
											{
												/* Copy the dot. */
												memcpy((output + outputLength), (pCurrentPos + x), (sizeof(char)));

												/* Update outputLength. */
												outputLength += (sizeof(char));

												/* Increment currentOutputPos. */
												currentOutputPos++;
											}
											else
											{
												/* Could not reallocate memory for output string addition. */
												ret = COMMON_ERROR_MEMORY_ERROR;

												/* Deallocate output. */
												DataProcess_Deallocate_CString(&output);
												outputLength = 0;
											}
										}
									}
									else
									{
										/* Allocate memory for adding dot to output string. */
										retFromCall = DataProcess_Reallocate_C_String(&output, outputLength, (outputLength + (sizeof(char))));
										if ((retFromCall == COMMON_ERROR_SUCCESS) && (output != NULL))
										{
											/* Copy the dot. */
											memcpy((output + outputLength), (pCurrentPos + x), (sizeof(char)));

											/* Update outputLength. */
											outputLength += (sizeof(char));

											/* Increment currentOutputPos. */
											currentOutputPos++;
										}
										else
										{
											/* Could not reallocate memory for output string addition. */
											ret = COMMON_ERROR_MEMORY_ERROR;

											/* Deallocate output. */
											DataProcess_Deallocate_CString(&output);
											outputLength = 0;
										}
									}
							}
						}
						break;
						default:
							/* Check and see if the current character is a DIR_SEP and it is the last character in the string. */
							if (((x + 1) < (*retStrSize)) || (((x + 1) == (*retStrSize)) && (pCurrentPos[x] != DIR_SEP)))
							{
								/* We don't do anything here, except copy the data to the output buffer. */
								retFromCall = DataProcess_Reallocate_C_String(&output, outputLength, (outputLength + (sizeof(char))));
								if ((retFromCall == COMMON_ERROR_SUCCESS) && (output != NULL) && (outputLength > 0))
								{
									/* Copy the data. */
									memcpy((output + outputLength), (pCurrentPos + x), (sizeof(char)));

									/* Update outputLength. */
									outputLength += (sizeof(char));

									/* Increment currentOutputPos. */
									currentOutputPos++;
								}
								else
								{
									/* Could not reallocate memory for output string addition. */
									ret = COMMON_ERROR_MEMORY_ERROR;

									/* Deallocate output. */
									DataProcess_Deallocate_CString(&output);
									outputLength = 0;
								}
							}
							break;
					};
				}

				/* Set ret. */
				ret = COMMON_ERROR_SUCCESS;

				/* Copy output to retStr. */
				(*retStr) = output;
				(*retStrSize) = outputLength;

				/* Log result. */
				COMMON_LOG_VERBOSE("FileUtills_ResolvePath(): Path ( ");
				COMMON_LOG_VERBOSE((*retStr));
				COMMON_LOG_VERBOSE(" ) resolved to ( ");
				COMMON_LOG_VERBOSE(output);
				COMMON_LOG_VERBOSE(").\n");
			}
			else
			{
				/* Could not allocate memory for output. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		else
		{
			/* Could not get pointer for given path. */
			ret = COMMON_ERROR_INTERNAL_ERROR;
			COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
			COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
			COMMON_LOG_WARNING(" Unable to get pointer to given path argument.\n");
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills_ResolvePath(): ");
		COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_VERBOSE(" No path given.\n");
	}

	/* Check for allocated strings, and deallocate them if needed. */
	if (homeDir != NULL)
	{
		DataProcess_Deallocate_CString(&homeDir);
		homeDirLength = 0;
	}
	if (currentDir != NULL)
	{
		DataProcess_Deallocate_CString(&currentDir);
		currentDirLength = 0;
	}
	if ((ret != COMMON_ERROR_SUCCESS) && (output != NULL))
	{
		DataProcess_Deallocate_CString(&output);
		outputLength = 0;
	}

	/* Return the result. */
	return ret;
}

int FileUtills_RemoveLastPathSegmentAtPosition(char ** path, size_t * pathSize, size_t * currentPathPos)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* Result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* Result code of other engine functions. */
	size_t tempPathSize = 0;						/* The temporary variable used to store the new path's size. */
	size_t y = 0;									/* Loop counter. */
	char * tempPath = NULL;							/* Temporary pointer to construct the result string. */

	/* Check for valid path. */
	if ((pathSize != NULL) && ((*pathSize) > 0) && (path != NULL) && ((*path) != NULL))
	{
		/* Check for a valid path position. */
		if ((currentPathPos != NULL) && ((*currentPathPos) > 0))
		{
			/* Make sure the path position is within the path buffer. */
			if ((*currentPathPos) < (*pathSize))
			{
				/* Remove last path segment from output. (Search from the end of the output string.) */
				for (y = 0; (((y < (*pathSize))) && (ret == COMMON_ERROR_UNKNOWN_ERROR)); y++)
				{
					/* Look for the DIR_SEP. */
					if ((*path)[((*currentPathPos) - y)] == DIR_SEP)
					{
						/* Check to see if we have hit the first directory seperator. */
						if (((*currentPathPos) - y) == MINIMAL_VALID_ABSOLUTE_PATH_LENGTH)
						{
							/* Decrement y, as we need this directory seperator. */
							y--;
						}

						/* Calculate the new string's length. */
						tempPathSize = ((sizeof(char)) * ((*currentPathPos) - y));

						/* Reallocate the new path string. */
						retFromCall = DataProcess_Reallocate_C_String(&tempPath, 0, tempPathSize);
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPath != NULL))
						{
							/* Memcopy the data to the new buffer. */
							memcpy(tempPath, path, tempPathSize);

							/* Reset the current path position. */
							(*currentPathPos) = ((*currentPathPos) - y);

							/* Reset the pathSize. */
							(*pathSize) = tempPathSize;

							/* Copy the temp pointer. */
							(*path) = tempPath;

							/* Success. */
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* Call to DataProcess_Reallocate_C_String() failed. */
							if (retFromCall == COMMON_ERROR_MEMORY_ERROR)
							{
								ret = COMMON_ERROR_MEMORY_ERROR;
							}
							else
							{
								ret = COMMON_ERROR_INTERNAL_ERROR;
							}

							/* Log the error. */
							COMMON_LOG_DEBUG("FileUtills_RemoveLastPathSegmentAtPosition(): Call to DataProcess_Reallocate_C_String() failed with error code: ");
							COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
						}
					}
				}

				/* If we get here and result is still COMMON_UNKNOWN_ERROR, then the path did not have a directory seperator in it. */
				if (ret == COMMON_ERROR_UNKNOWN_ERROR)
				{
					ret = COMMON_ERROR_SUCCESS;
				}
			}
			else
			{
				/* currentPathPos is beyond the end of the path buffer. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				COMMON_LOG_VERBOSE("FileUtills_RemoveLastPathSegmentAtPosition(): ");
				COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
				COMMON_LOG_VERBOSE(" current path position is beyond the end of the path buffer. (Nice try.)");
			}
		}
		else
		{
			/* Invalid currentPathPos. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE("FileUtills_RemoveLastPathSegmentAtPosition(): ");
			COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			COMMON_LOG_VERBOSE(" current path position is invalid.");
		}
	}
	else
	{
		/* No path given. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills_RemoveLastPathSegmentAtPosition(): ");
		COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_VERBOSE(" No valid path given.");
	}

	/* Check for success. */
	if (ret != COMMON_ERROR_SUCCESS)
	{
		/* Deallocate the tempPath string if needed. */
		if (tempPath != NULL)
		{
			DataProcess_Deallocate_CString(&tempPath);
		}
	}

	/* Return the result. */
	return ret;
}
