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

int FileUtills_Create_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV ** obj)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	MSYS_FileUtills_dirList_PRIV * tempObj = NULL;	/* The object we are creating. */

	/* Check for invalid pointer argument. */
	if (obj != NULL)
	{
		/* Allocate object. */
		tempObj = (MSYS_FileUtills_dirList_PRIV *)malloc((sizeof MSYS_FileUtills_dirList_PRIV));
		if (tempObj != NULL)
		{
			/* NULL out object. */
			memset(obj, '\0', (sizeof MSYS_FileUtills_dirList_PRIV));

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

void FileUtills_Destroy_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV ** obj)
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

int FileUtills_dirList_PRIV_Add_Entry(MSYS_FileUtills_dirList_PRIV * dirListPriv,
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

int FileUtills_dirList_PRIV_Get_Entry(MSYS_FileUtills_dirList_PRIV * dirListPriv, const size_t entryOffset,
										char ** entry, size_t * entryLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to another engine function. */
	MSYS_Linked_List_T * iterator = NULL;			/* Iterator used to iterate through the linked list. */
	char * fetchedEntry = NULL;						/* Pointer to data in linked list object. */
	size_t fetchedEntryLength = 0;					/* Length of fetchedEntry. */
	char * returnedEntry = NULL;					/* Pointer to copy of the entry data that is returned to the caller. */

	/* Check for invalid arguments. */
	if ((dirListPriv != NULL) && (dirListPriv->list != NULL) && (entry != NULL) && (entryLength != NULL))
	{
		/* Get the first iterator pointer. */
		retFromCall = MSYS_Linked_List_Get_First_Object(dirListPriv->list, &iterator);
		if (retFromCall == COMMON_ERROR_SUCCESS)
		{
			/* Begin iteration loop. (Start at index one as we already have the first entry.) */
			for (size_t x = 1; ((x < entryOffset) && (retFromCall == COMMON_ERROR_SUCCESS) && (iterator != NULL)); x++)
			{
				/* Get the next object. */
				retFromCall = MSYS_Linked_List_Get_Next_Object(iterator, &iterator);
			}

			/* Check for valid iterator. */
			if (iterator != NULL)
			{
				/* Get the contents of the correct entry. */
				retFromCall = MSYS_Linked_List_Get_Current_Object_Contents(iterator, ((void**)(&fetchedEntry)), &fetchedEntryLength);
				if (retFromCall == COMMON_ERROR_SUCCESS)
				{
					/* Check and see if there is entry data at all.... */
					if ((fetchedEntry != NULL) && (fetchedEntryLength > 0))
					{
						/* Allocate memory to copy the entry data prior to returning it to the caller. */
						retFromCall = DataProcess_Reallocate_C_String(&returnedEntry, 0, fetchedEntryLength);
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (returnedEntry != NULL))
						{
							/* Copy the entry data. */
							memcpy(returnedEntry, fetchedEntry, fetchedEntryLength);

							/* Copy the new pointer to the caller. */
							(*entry) = returnedEntry;
							(*entryLength) = fetchedEntryLength;

							/* Done. */
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* Could not allocate memory for data copy. */
							ret = ((retFromCall != COMMON_ERROR_MEMORY_ERROR) ? (COMMON_ERROR_INTERNAL_ERROR) :
							(COMMON_ERROR_MEMORY_ERROR));

							/* Log error. */
							if (ret != COMMON_ERROR_MEMORY_ERROR)
							{
								COMMON_LOG_VERBOSE("FileUtills_dirList_PRIV_Get_Entry(): Could not create a copy of the entry data.");
							}
						}
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

int FileUtills_dirList_PRIV_Remove_Entry(MSYS_FileUtills_dirList_PRIV * dirListPriv, const size_t entryOffset)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to another engine function. */
	MSYS_Linked_List_T * iterator = NULL;			/* Iterator used to iterate through the linked list. */
	char * entry = NULL;							/* Pointer to the entry data. */
	size_t entryLength = 0;							/* Length of the entry data. */

	/* Check for invalid arguments. */
	if ((dirListPriv != NULL) && (dirListPriv->list != NULL))
	{
		/* Get the first iterator pointer. */
		retFromCall = MSYS_Linked_List_Get_First_Object(dirListPriv->list, &iterator);
		if (retFromCall == COMMON_ERROR_SUCCESS)
		{
			/* Begin iteration loop. (Start at index one as we already have the first entry.) */
			for (size_t x = 1; ((x < entryOffset) && (retFromCall == COMMON_ERROR_SUCCESS) && (iterator != NULL)); x++)
			{
				/* Get the next object. */
				retFromCall = MSYS_Linked_List_Get_Next_Object(iterator, &iterator);
			}

			/* Check for valid iterator. */
			if (iterator != NULL)
			{
				/* Get the contents of the correct entry. */
				retFromCall = MSYS_Linked_List_Get_Current_Object_Contents(iterator, ((void**)(&entry)), &entryLength);
				if (retFromCall == COMMON_ERROR_SUCCESS)
				{
					/* Deallocate the entry data. */
					DataProcess_Deallocate_CString(&entry);

					/* Deallocate the entry's linked list object. */
					MSYS_Linked_List_Deallocate_Linked_List_Object(&iterator);

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
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
		DataProcess_Deallocate_CString(data);
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
