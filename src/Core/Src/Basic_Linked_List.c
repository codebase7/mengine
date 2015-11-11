/*!
    Multiverse Engine Project 05/7/2015 Basic_Linked_List.c

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

/* Begin extern C if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Internal includes. */
#include "Basic_Linked_List.h"

/* External includes. */
#include <stdlib.h>	/* Define malloc() & free(). */
#include <string.h>	/* Define memset(). */

void Blank_MSYS_Linked_List_Object(MSYS_Linked_List_T * list)
{
	/* Check for valid arguments. */
	if (list != NULL)
	{
		/* Check to see if we should have allocated memory. */
		if (list->allocated)
		{
			/* Check for allocated memory. */
			if (list->data != NULL)
			{
				/* Deallocate memory. */
				DataProcess_Deallocate_CString((&(list->data)));
			}
		}

		/* Blank out the list object. */
		list->allocated = 0;
		list->data = NULL;
		list->dataLength = 0;
		list->nextObject = NULL;
		list->prevObject = NULL;
	}

	/* Exit function. */
	return;
}

int MSYS_Linked_List_Allocate_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code for this function. */
	MSYS_Linked_List_T * pList = NULL;		/* Temporary pointer used to create the list object. */

	/* Check for valid args. */
	if (ppAllocatedList != NULL)
	{
		/* Allocating new object. */
		pList = (MSYS_Linked_List_T *)malloc(sizeof(MSYS_Linked_List_T));
		if (pList != NULL)
		{
			/* Blank out the list. */
			Blank_MSYS_Linked_List_Object(pList);

			/* Determine if we are creating a new list or appending to an existing one. */
			if ((*ppAllocatedList) != NULL)
			{
				/* Appending to an existing list, determine if we are at the end of the list. */
				if ((*ppAllocatedList)->nextObject != NULL)
				{
					/* Only update the next object's prevObject pointer if it points to the current object. */
					if ((*ppAllocatedList)->nextObject->prevObject == (*ppAllocatedList))
					{
						(*ppAllocatedList)->nextObject->prevObject = pList;
					}

					/* Somewhere within the list, need to update the pointers. */
					pList->prevObject = (*ppAllocatedList);
					pList->nextObject = (*ppAllocatedList)->nextObject;
				}

				/* Set the next pointer. */
				(*ppAllocatedList)->nextObject = pList;
			}
			else
			{
				/* Creating a new list. */
				(*ppAllocatedList) = pList;
			}

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

void MSYS_Linked_List_Deallocate_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList)
{
	/* Init vars. */
	MSYS_Linked_List_T * pList = NULL;		/* Temporary pointer used to deallocate the given object.
							 * (Just in case we get called with an object's nextObject or prevObject
							 *  pointer as the current object.)
							 */

	/* Check for valid args. */
	if ((ppAllocatedList != NULL) && ((*ppAllocatedList) != NULL))
	{
		/* Copy the pointer. */
		pList = (*ppAllocatedList);

		/* Check for other objects to update. */
		if ((pList->prevObject != NULL) || (pList->nextObject != NULL))
		{
			/* Check and see if both the previous object and the next object are defined. */
			if ((pList->prevObject != NULL) && (pList->nextObject != NULL))
			{
				/* Simple stiching, but make sure that the next and previous objects actually point to the current one before altering them. */
				if (pList->prevObject->nextObject == pList)
				{
					pList->prevObject->nextObject = pList->nextObject;
				}
				if (pList->nextObject->prevObject == pList)
				{
					pList->nextObject->prevObject = pList->prevObject;
				}
			}
			else
			{
				/* OK, figure out what object needs to be updated. */
				if (pList->prevObject != NULL)
				{
					/* Set the previous object's next object pointer to NULL,
					 * but make sure that the previous object actually points
					 * to the current one before altering it.
					 */
					if (pList->prevObject->nextObject == pList)
					{
						pList->prevObject->nextObject = NULL;
					}
				}
				if (pList->nextObject != NULL)
				{
					/* Set the next object's previous object pointer to NULL,
					 * but make sure that the next object actually points
					 * to the current one before altering it.
					 */
					if (pList->nextObject->prevObject == pList)
					{
						pList->nextObject->prevObject = NULL;
					}
				}
			}
		}

		/* Blank and deallocate the current object. */
		Blank_MSYS_Linked_List_Object((*ppAllocatedList));
		free((*ppAllocatedList));
		(*ppAllocatedList) = NULL;
	}

	/* Exit function. */
	return;
}

void MSYS_Linked_List_Deallocate_Entire_List(MSYS_Linked_List_T ** ppAllocatedList)
{
	/* Init vars. */
	int retFromFunct = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code from MSYS_Linked_List_*() functions. */
	MSYS_Linked_List_T * nextObject = NULL;		/* The next object in the list, after the current one. */
	MSYS_Linked_List_T * currentObject = NULL;	/* The current object we are looking at in the list. */
	MSYS_Linked_List_T * lastObject = NULL;		/* The last object in the list. */

	/* Check for invalid arguments. */
	if ((ppAllocatedList != NULL) && ((*ppAllocatedList) != NULL))
	{
		/* Get the first object in the list. */
		retFromFunct = MSYS_Linked_List_Get_First_Object((*ppAllocatedList), &currentObject);
		if (retFromFunct == COMMON_ERROR_SUCCESS)
		{
			/* Get the last object in the list. */
			retFromFunct = MSYS_Linked_List_Get_Last_Object((*ppAllocatedList), &lastObject);
			if (retFromFunct == COMMON_ERROR_SUCCESS)
			{
				/* Begin deallocation loop. */
				while ((retFromFunct == COMMON_ERROR_SUCCESS) && (currentObject != lastObject))
				{
					/* Get the next object. */
					retFromFunct = MSYS_Linked_List_Get_Next_Object(currentObject, &nextObject);
					if (retFromFunct == COMMON_ERROR_SUCCESS)
					{
						/* Deallocate the current object. */
						MSYS_Linked_List_Deallocate_Linked_List_Object(&currentObject);

						/* Copy the pointer for the next object to the current one. */
						currentObject = nextObject;
					}
				}
			}
		}
	}

	/* Exit function. */
	return;
}

int MSYS_Linked_List_Get_First_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppFirstObject)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code for this function. */
	const MSYS_Linked_List_T * currentObject = NULL;	/* The current object we are looking at in the list. */

	/* Check for valid args. */
	if ((pAllocatedList != NULL) && (ppFirstObject != NULL))
	{
		/* Copy the pointer. */
		currentObject = pAllocatedList;

		/* Set ret to COMMON_ERROR_INTERNAL_ERROR. */
		ret = COMMON_ERROR_INTERNAL_ERROR;

		/* Search for the first object.
		 * (The first object in the list has it's prevObject pointer set to NULL.)
		 * Also the extra check is to prevent jumping out of our chain.
		 */
		while ((ret == COMMON_ERROR_INTERNAL_ERROR) &&
			(currentObject->prevObject != NULL) &&
			(currentObject->prevObject->nextObject == currentObject) &&
			(currentObject->prevObject->prevObject != currentObject))
		{
			/* Check and see if the next object is going to end the loop. */
			if (currentObject->prevObject->prevObject == NULL)
			{
				/* Copy the pointer for the first object. */
				(*ppFirstObject) = currentObject->prevObject;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}

			/* Switch to previous object. */
			currentObject = currentObject->prevObject;
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Linked_List_Get_Last_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppLastObject)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code for this function. */
	const MSYS_Linked_List_T * currentObject = NULL;	/* The current object we are looking at in the list. */

	/* Check for valid args. */
	if ((pAllocatedList != NULL) && (ppLastObject != NULL))
	{
		/* Copy the pointer. */
		currentObject = pAllocatedList;

		/* Set ret to COMMON_ERROR_INTERNAL_ERROR. */
		ret = COMMON_ERROR_INTERNAL_ERROR;

		/* Search for the last object.
		 * (The last object in the list has it's nextObject pointer set to NULL.)
		 * Also the extra check is to prevent jumping out of our chain.
		 */
		while ((ret == COMMON_ERROR_INTERNAL_ERROR) &&
			(currentObject->nextObject != NULL) &&
			(currentObject->nextObject->prevObject == currentObject) &&
			(currentObject->nextObject->nextObject != currentObject))
		{
			/* Check and see if the next object is going to end the loop. */
			if (currentObject->nextObject->nextObject == NULL)
			{
				/* Copy the pointer for the last object. */
				(*ppLastObject) = currentObject->nextObject;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}

			/* Switch to next object. */
			currentObject = currentObject->nextObject;
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Linked_List_Get_Next_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppNextObject)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code for this function. */

	/* Check for valid args. */
	if ((pAllocatedList != NULL) && (ppNextObject != NULL))
	{
		/* Copy the pointer to the next object. */
		(*ppNextObject) = pAllocatedList->nextObject;

		/* Success. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Linked_List_Get_Previous_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppPrevObject)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code for this function. */

	/* Check for valid args. */
	if ((pAllocatedList != NULL) && (ppPrevObject != NULL))
	{
		/* Copy the pointer to the previous object. */
		(*ppPrevObject) = pAllocatedList->prevObject;

		/* Success. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Linked_List_Get_Current_Object_Contents(const MSYS_Linked_List_T * pAllocatedList, void ** ppData, size_t * dataLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code for this function. */

	/* Check for valid args. */
	if ((pAllocatedList != NULL) && (ppData != NULL) && (dataLength != NULL))
	{
		/* Copy the pointer and length. */
		(*ppData) = pAllocatedList->data;
		(*dataLength) = pAllocatedList->dataLength;

		/* Success. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Linked_List_Set_Current_Object_Contents(MSYS_Linked_List_T * pAllocatedList, void * pData, const size_t dataLength, const int copyData)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code for this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code from an engine function. */
	char * tempData = NULL;							/* Temporary pointer used to allocate memory. */

	/* Check for valid args. */
	if (pAllocatedList != NULL)
	{
		/* Blank the existing list. */
		Blank_MSYS_Linked_List_Object(pAllocatedList);

		/* Check and see if we need to copy the data instead of the pointer. */
		if (copyData)
		{
			/* Allocate memory. */
			retFromCall = DataProcess_Reallocate_C_String(&tempData, 0, dataLength);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempData != NULL))
			{
				/* Copy the data. */
				memcpy(tempData, pData, dataLength);

				/* Copy the allocated pointer, and data length. */
				pAllocatedList->data = tempData;
				pAllocatedList->dataLength = dataLength;

				/* Make sure allocated is true. */
				pAllocatedList->allocated = 1;

				/* Success. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Could not allocate memory. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		else
		{
			/* Copy the pointer and length. */
			pAllocatedList->data = pData;
			pAllocatedList->dataLength = dataLength;

			/* Make sure allocated is false. */
			pAllocatedList->allocated = 0;

			/* Success. */
			ret = COMMON_ERROR_SUCCESS;
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Linked_List_Swap_Objects(MSYS_Linked_List_T * pFirstObject, MSYS_Linked_List_T * pSecondObject)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code of this function. */
	void * pData = NULL;						/* Temporary pointer used to swap the data pointers. */
	size_t dataLength = 0;						/* Temporary pointer used to swap the data lengths. */
	
	/* Check for invalid arguments. */
	if ((pFirstObject != NULL) && (pSecondObject != NULL))
	{
		/* Copy the pointers. */
		pData = pFirstObject->data;
		pFirstObject->data = pSecondObject->data;
		pSecondObject->data = pData;
		pData = NULL;

		/* Copy the data lengths. */
		dataLength = pFirstObject->dataLength;
		pFirstObject->dataLength = pSecondObject->dataLength;
		pSecondObject->dataLength = dataLength;
		dataLength = 0;

		/* Done. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}
	
	/* Exit function. */
	return ret;
}
