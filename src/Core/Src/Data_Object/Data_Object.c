/*
	Multiverse Engine Project	Core Data_Object.c	02/4/2016

	Copyright (C) 2016 Multiverse Engine Project

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
#include "../DataProcess.h"
#include "../../../Common/Src/Error_Handler/Common_Error_Handler_Error_Codes.h"

/* External includes. */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 *
 *		Private data structures and functions are defined below.
 *		(Should not be used outside this source file, subject to change without warning.)
 */

/* Define the real MSYS_DataObject_T object. */
typedef struct MSYS_DataObject_Private {
	char * data;        /* Pointer to data. */
    size_t length;      /* Length of data. */
    size_t capacity;    /* Length of data we can store. */
} MSYS_DataObject_T_Private;

/*!
		void MSYS_Blank_DataObject_Private(MSYS_DataObject_T_Private * buffer)

		Blanks out a newly allocated MSYS_DataObject_T_Private object.

		If the given pointer is invalid, this function will silently fail.

		This function has no return code.
 */
void MSYS_Blank_DataObject_Private(MSYS_DataObject_T_Private * buffer)
{
	/* Check for valid pointer. */
	if (buffer != NULL)
	{
		buffer->data = NULL;
		buffer->length = 0;
		buffer->capacity = 0;
	}

	/* Exit function. */
	return;
}

/*!
		void MSYS_Clear_DataObject_Private(MSYS_DataObject_T_Private * obj)

		Resets the given MSYS_DataObject_T_Private object to it's default state.
		(I.e. No allocated memory buffer, length and capacity are both set to zero.)

		If the given pointer is invalid this function will silently fail.

		This function has no return.
 */
void MSYS_Clear_DataObject_Private(MSYS_DataObject_T_Private * obj)
{
	/* Check for valid pointer. */
	if (obj != NULL)
	{
		/* Check and see if we need to deallocate the buffer. */
		if (obj->data != NULL)
		{
			DataProcess_Deallocate_CString((&(obj->data)));
		}

		/* Reset the length and capacity. */
		obj->capacity = 0;
		obj->length = 0;
	}

	/* Exit function. */
	return;
}

/*!
		void MSYS_Reset_DataObject_Private(MSYS_DataObject_T_Private * obj)

		This function erases all data in the data object's buffer, (Sets all bytes to NULL)
		and sets it's length to zero (0). The capacity is left unchanged.

		If the given pointer / object is invalid, or there is no allocated buffer,
		this function will silently fail.

		This function has no return.
 */
void MSYS_Reset_DataObject_Private(MSYS_DataObject_T_Private * obj)
{
	/* Init vars. */
	size_t x = 0;		/* Counter for erase loop. */

	/* Check for valid pointer, and object. */
	if ((obj != NULL) && (obj->data != NULL) && (obj->capacity > 0))
	{
		/* NULL out the buffer. (erase loop.) */
		for (x = 0; (x < (obj->capacity)); x++)
		{
			obj->data[x] = '\0';
		}

		/* Reset the length. */
		obj->length = 0;
	}

	/* Exit function. */
	return;
}

/*!
		int MSYS_Check_DataObject_Consistency_Private(const MSYS_DataObject_T_Private * obj)

		Checks the given MSYS_DataObject_T_Private object for consistency.

		Returns COMMON_ERROR_COMPARISON_PASSED if the given object is consistant.
		Returns COMMON_ERROR_COMPARISON_FAILED if the given object is NOT consistant.
		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is invalid.
 */
int MSYS_Check_DataObject_Consistency_Private(const MSYS_DataObject_T_Private * obj)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;

	/* Check for valid pointer. */
	if (obj != NULL)
	{
		/* Check for allocated buffer. */
		if (obj->data != NULL)
		{
			/* Check for valid capacity. */
			if (obj->capacity > 0)
			{
				/* Check for valid length. */
				if (obj->length <= obj->capacity)
				{
					/* Valid object. */
					ret = COMMON_ERROR_COMPARISON_PASSED;
				}
				else
				{
					/* Invalid object. */
					ret = COMMON_ERROR_COMPARISON_FAILED;
				}
			}
			else
			{
				/* Invalid object. */
				ret = COMMON_ERROR_COMPARISON_FAILED;
			}
		}
		else
		{
			/* No allocated buffer, check length and capacity. */
			if ((obj->capacity == 0) && (obj->length == 0))
			{
				/* Valid object. */
				ret = COMMON_ERROR_COMPARISON_PASSED;
			}
			else
			{
				/* Invalid object. */
				ret = COMMON_ERROR_COMPARISON_FAILED;
			}
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

/*!
		void MSYS_Destroy_DataObject_Private(MSYS_DataObject_T_Private ** buffer)

		Deallocates the given MSYS_DataObject_T_Private object.

		This function has no return.
 */
void MSYS_Destroy_DataObject_Private(MSYS_DataObject_T_Private ** buffer)
{
	/* Check for valid pointer. */
	if ((buffer != NULL) && (*(buffer) != NULL))
	{
		/* Clear the structure. */
		MSYS_Clear_DataObject_Private(*buffer);

		/* Deallocate the private structure. */
		DataProcess_Deallocate_CString((char**)(buffer));
	}

	/* Exit function. */
	return;
}

/*
 *
 *		Public functions are defined below.
 *
 */

int MSYS_Create_DataObject(MSYS_DataObject_T ** buffer)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of the call to another engine function. */
	MSYS_DataObject_T * tempPtr = NULL;					/* Used to create the MSYS_DataObject_T object. */
	MSYS_DataObject_T_Private * realStrPtr = NULL;		/* Used to create the MSYS_DataObject_T_Private object. */
	char * newPtP = NULL;								/* Used to allocate pointer to pointer for the public object. */

	/* Check vars. */
	if (buffer != NULL)
	{
		/* Allocate memory for the public object. */
		retFromCall = DataProcess_Reallocate_C_String(((char**)(&tempPtr)), 0, sizeof(MSYS_DataObject_T));
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPtr != NULL))
		{
			/* Set the internal pointer to NULL. */
			tempPtr->ppObject = NULL;

			/* Create new pointer to pointer for the public object's ppObject variable. */
			retFromCall = DataProcess_Reallocate_C_String(&newPtP, 0, sizeof(char**));
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (newPtP != NULL))
			{
				/* Allocate memory for the private object. */
				retFromCall = DataProcess_Reallocate_C_String(((char**)(&realStrPtr)), 0, sizeof(MSYS_DataObject_T_Private));
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (realStrPtr != NULL))
				{
					/* Blank the private structure. */
					MSYS_Blank_DataObject_Private(realStrPtr);

					/* Copy the pointer for the private structure into the pointer to pointer variable. */
					newPtP = ((char*)(realStrPtr));

					/* Copy the pointer to pointer into the public structure. */
					*(tempPtr->ppObject) = newPtP;

					/* Copy the pointer to the public structure into the buffer argument. */
					(*buffer) = tempPtr;

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Could not allocate memory for the private object. */
					ret = COMMON_ERROR_MEMORY_ERROR;

					/* Deallocate memory for the pointer to pointer variable. */
					DataProcess_Deallocate_CString(((char**)(&newPtP)));

					/* Deallocate memory for the public structure. */
					DataProcess_Deallocate_CString(((char**)(&tempPtr)));
				}
			}
			else
			{
				/* Could not allocate memory for the public object's ppObject variable. */
				ret = COMMON_ERROR_MEMORY_ERROR;

				/* Deallocate memory for the public structure. */
				DataProcess_Deallocate_CString(((char**)(&tempPtr)));
			}
		}
		else
		{
			/* Could not allocate memory for the public object. */
			ret = COMMON_ERROR_MEMORY_ERROR;
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

void MSYS_Destroy_DataObject(MSYS_DataObject_T ** buffer)
{
	/* Check for valid pointer. */
	if ((buffer != NULL) && ((*buffer) != NULL) && (((*buffer)->ppObject) != NULL) && (*((*buffer)->ppObject)) != NULL)
	{
		/* Deallocate the private structure. */
		MSYS_Destroy_DataObject_Private(((MSYS_DataObject_T_Private **)((*buffer)->ppObject)));

		/* Deallocate the pointer to pointer object. (ppObject itself.) */
		DataProcess_Deallocate_CString((char**)(&((*buffer)->ppObject)));

		/* Deallocate the public structure. */
		DataProcess_Deallocate_CString(((char**)(buffer)));
	}

	/* Exit function. */
	return;
}

int MSYS_Check_DataObject_Consistency(const MSYS_DataObject_T * obj)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;
	const MSYS_DataObject_T_Private * realPtr = NULL;

	/* Check args. */
	if ((obj != NULL) && ((obj->ppObject) != NULL) && (*(obj->ppObject) != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (const MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Call the real function. */
		ret = (MSYS_Check_DataObject_Consistency_Private(realPtr));
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Get_Capacity(const MSYS_DataObject_T * obj, size_t * retPtr)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;
	const MSYS_DataObject_T_Private * realPtr = NULL;

	/* Check args. */
	if ((obj != NULL) && ((obj->ppObject) != NULL) && (*(obj->ppObject) != NULL) && (retPtr != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (const MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Copy the capacity. */
		(*retPtr) = realPtr->capacity;

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

int MSYS_DataObject_Get_Length(const MSYS_DataObject_T * obj, size_t * retPtr)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;
	const MSYS_DataObject_T_Private * realPtr = NULL;

	/* Check args. */
	if ((obj != NULL) && ((obj->ppObject) != NULL) && (*(obj->ppObject) != NULL) && (retPtr != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (const MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Copy the length. */
		(*retPtr) = realPtr->length;

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

int MSYS_DataObject_Get_Pointer(const MSYS_DataObject_T * buffer, const char ** retPtr)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;
	const MSYS_DataObject_T_Private * realPtr = NULL;

	/* Check args. */
	if ((buffer != NULL) && ((buffer->ppObject) != NULL) && (*(buffer->ppObject) != NULL) && (retPtr != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (const MSYS_DataObject_T_Private *)(*(buffer->ppObject));

		/* Return the internal data pointer. */
		(*retPtr) = realPtr->data;

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

int MSYS_DataObject_Get_Copy(const MSYS_DataObject_T * buffer, char ** retPtr)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
	const MSYS_DataObject_T_Private * realPtr = NULL;
	char * tempCopy = NULL;

	/* Check args. */
	if ((buffer != NULL) && ((buffer->ppObject) != NULL) && (*(buffer->ppObject) != NULL) && (retPtr != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (const MSYS_DataObject_T_Private *)(*(buffer->ppObject));

		/* Check for a valid pointer. */
		if ((realPtr->data != NULL) && (realPtr->length > 0) && (realPtr->capacity > 0))
		{
			/* Copy the internal string. */
			retFromCall = DataProcess_Copy_C_String(realPtr->data, realPtr->length, &tempCopy);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempCopy != NULL))
			{
				/* Copy the new pointer to retPtr. */
				(*retPtr) = tempCopy;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Could not copy the string. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		else
		{
			/* No buffer is allocated in the private structure. */
			ret = COMMON_ERROR_NO_DATA;
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

void MSYS_Clear_DataObject(MSYS_DataObject_T * obj)
{
	/* Init vars.  */
	MSYS_DataObject_T_Private * realPtr = NULL;

	/* Check args. */
	if ((obj != NULL) && ((obj->ppObject) != NULL) && (*(obj->ppObject) != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Call the private function. */
		MSYS_Clear_DataObject_Private(realPtr);
	}

	/* Exit function. */
	return;
}

void MSYS_Reset_DataObject(MSYS_DataObject_T * obj)
{
	/* Init vars.  */
	MSYS_DataObject_T_Private * realPtr = NULL;

	/* Check args. */
	if ((obj != NULL) && ((obj->ppObject) != NULL) && (*(obj->ppObject) != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Call the private function. */
		MSYS_Reset_DataObject_Private(realPtr);
	}

	/* Exit function. */
	return;
}

int MSYS_DataObject_Create_From_Existing_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T ** retObj)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of calls to other engine functions. */
	MSYS_DataObject_T * newObj = NULL;					/* The object we will create. */

	/* Check vars. */
	/* Yes, we are explictly checking that retObj does not hold the same memory address as source,
		or the source pointer.
	*/
	if ((source != NULL) && (retObj != NULL) && (((void *)retObj) != ((void *)(source))) &&
		(source->ppObject != NULL) && (*(source->ppObject) != NULL) &&
		(((void*)(retObj)) != *(source->ppObject)))
	{
		/* Create the new object. */
		retFromCall = MSYS_Create_DataObject(&newObj);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (newObj != NULL) && (newObj->ppObject != NULL) && (*(newObj->ppObject) != NULL))
		{
			/* Deep copy the source structure. */
			retFromCall = MSYS_Deep_Copy_DataObject(source, newObj);
			if (retFromCall == COMMON_ERROR_SUCCESS)
			{
				/* Copy newObj pointer to retObj. */
				(*retObj) = newObj;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Check error code. */
				ret = ((retFromCall == COMMON_ERROR_DATA_CORRUPTION) ? (COMMON_ERROR_DATA_CORRUPTION) :
					(COMMON_ERROR_MEMORY_ERROR));

				/* Deallocate the newObj. */
				MSYS_Destroy_DataObject(&newObj);
			}
		}
		else
		{
			/* Could not create new DataObject. */
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

int MSYS_Shallow_Copy_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T * dest)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */

	/* Check args. */
	if ((source != NULL) && (dest != NULL) && (source != dest) && (source->ppObject != NULL) && (*(source->ppObject) != NULL) &&
		(dest->ppObject != NULL) && (source->ppObject != dest->ppObject) && (*(source->ppObject) != *(dest->ppObject)))
	{
		/* Deallocate the dest private structure if needed. */
		if (*(dest->ppObject) != NULL)
		{
			MSYS_Destroy_DataObject_Private(((MSYS_DataObject_T_Private **)(dest->ppObject)));
		}

		/* Copy the source pointer to the dest pointer. */
		*(dest->ppObject) = *(source->ppObject);

		/* Done. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_Deep_Copy_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T * dest)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of calls to other engine functions. */
	char * copyBuffer = NULL;								/* The copied data buffer. */
	const MSYS_DataObject_T_Private * srcPrivStr = NULL;	/* The internal structure of the source data object. */
	MSYS_DataObject_T_Private * destPrivStr = NULL;			/* The internal structure of the dest data object. */

	/* Check args. */
	if ((source != NULL) && (dest != NULL) && (source != dest) && (source->ppObject != NULL) && (*(source->ppObject) != NULL) &&
		(dest->ppObject != NULL) && (*(dest->ppObject) != NULL) && (*(source->ppObject) != *(dest->ppObject)))
	{
		/* Get the internal pointers. */
		srcPrivStr = (const MSYS_DataObject_T_Private *)(*(source->ppObject));
		destPrivStr = (MSYS_DataObject_T_Private *)(*(dest->ppObject));

		/* Check for valid data pointer in the source object. */
		if (srcPrivStr->data != NULL)
		{
			/* Check for valid capacity and length. */
			if ((srcPrivStr->length >= 0) && (srcPrivStr->capacity >= srcPrivStr->length))
			{
				/* Clear the internal structure for the dest object. */
				MSYS_Clear_DataObject_Private(destPrivStr);

				/* Deep copy the values from the source object to the dest object. */
				retFromCall = DataProcess_Copy_C_String(srcPrivStr->data, srcPrivStr->capacity, &copyBuffer);
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (copyBuffer != NULL))
				{
					/* Copy the new pointer into the dest object. */
					destPrivStr->data = copyBuffer;

					/* Copy remaining values. */
					destPrivStr->capacity = srcPrivStr->capacity;
					destPrivStr->length = srcPrivStr->length;

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Could not copy source buffer. */
					ret = COMMON_ERROR_MEMORY_ERROR;
				}
			}
			else
			{
				/* OK, the source object is invalid. */
				ret = COMMON_ERROR_DATA_CORRUPTION;
			}
		}
		else
		{
			/* Check and see if the source object's length and capacity are both equal to zero. */
			if ((srcPrivStr->capacity == 0) && (srcPrivStr->length == 0))
			{
				/* Clear the internal structure for the dest object. */
				MSYS_Clear_DataObject_Private(destPrivStr);

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* OK, the source object is invalid. */
				ret = COMMON_ERROR_DATA_CORRUPTION;
			}
		}
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Set_Data_From_CString(MSYS_DataObject_T * obj, const char * data, const size_t dataLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of calls to other engine functions. */
	MSYS_DataObject_T_Private * realPtr = NULL;			/* Pointer to private data structure. */
	char * copyStr = NULL;								/* Pointer to the copied data. */

	/* Check args. */
	if ((obj != NULL) && (obj->ppObject != NULL) && (*(obj->ppObject) != NULL) &&
		(data != NULL) && (dataLength > 0))
	{
		/* Get back the real pointer. */
		realPtr = (MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Copy the string data. */
		retFromCall = DataProcess_Copy_C_String(data, dataLength, &copyStr);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (copyStr != NULL))
		{
			/* Clear the internal structure. */
			MSYS_Clear_DataObject_Private(realPtr);

			/* Copy dataLength to the private structure's length and capacity vars. */
			realPtr->length = dataLength;
			realPtr->capacity = dataLength;

			/* Copy copyStr's pointer to the private structure. */
			realPtr->data = copyStr;

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not copy the data. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Set_Data_From_Char(MSYS_DataObject_T * obj, const char data)
{
	/* Call the real function. */
	return MSYS_DataObject_Set_Data_From_CString(obj, &data, sizeof(char));
}

int MSYS_DataObject_Append_CString(MSYS_DataObject_T * obj, const char * data, const size_t dataLength)
{
	/* Call insert function. */
	return (MSYS_DataObject_Insert_CString(obj, SIZE_MAX, data, dataLength));
}

int MSYS_DataObject_Append_Char(MSYS_DataObject_T * obj, const char data)
{
	/* Call insert function. */
	return (MSYS_DataObject_Insert_CString(obj, SIZE_MAX, &data, sizeof(char)));
}

int MSYS_DataObject_Append_DataObject(MSYS_DataObject_T * obj, const MSYS_DataObject_T * src)
{
	/* Call insert function. */
	return (MSYS_DataObject_Insert_From_DataObject(obj, SIZE_MAX, src));
}

int MSYS_DataObject_Substr(const MSYS_DataObject_T * obj, const size_t offset, const size_t endpoint, char ** substr)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of calls to other engine functions. */
	const MSYS_DataObject_T_Private * srcPrivStr = NULL;	/* The internal structure of the source data object. */
	char * newSubstr = NULL;								/* The substring to be created. */
	size_t newSubstrLength = 0;								/* Length of the new substring. */

	/* Check args. */
	if ((obj != NULL) && (obj->ppObject != NULL) && (*(obj->ppObject) != NULL) &&
		(offset >= 0) && (offset < endpoint) && (substr != NULL))
	{
		/* Get the internal pointers. */
		srcPrivStr = (const MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Check for valid data pointer in the source object. */
		if (srcPrivStr->data != NULL)
		{
			/* Check for valid length and capacity in the source object. */
			if ((srcPrivStr->length >= 0) && (srcPrivStr->capacity >= srcPrivStr->length))
			{
				/* Check for valid offset and endpoint range. */
				if (srcPrivStr->length > endpoint)
				{
					/* Check for safe length. */
					if ((SIZE_MAX - endpoint) > offset)
					{
						/* Recalculate the substring length. */
						newSubstrLength = (endpoint - offset);

						/* Allocate memory for the new substring. */
						retFromCall = DataProcess_Reallocate_C_String(&newSubstr, 0, newSubstrLength);
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (newSubstr != NULL))
						{
							/* Copy the data. */
							memcpy(newSubstr, (srcPrivStr->data + offset), newSubstrLength);

							/* Copy the pointer to the substr arg. */
							(*substr) = newSubstr;

							/* Done. */
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* Could not allocate memory for the new substring. */
							ret = COMMON_ERROR_MEMORY_ERROR;
						}
					}
					else
					{
						/* Cannot represent that value. */
						ret = COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED;
					}
				}
				else
				{
					/* Invalid substring range. */
					ret = COMMON_ERROR_RANGE_ERROR;
				}
			}
			else
			{
				/* OK, the source object is invalid. */
				ret = COMMON_ERROR_DATA_CORRUPTION;
			}
		}
		else
		{
			/* Check for valid object. */
			if ((srcPrivStr->length == 0) && (offset == 0))
			{
				/* No data to create substring from. */
				ret = COMMON_ERROR_NO_DATA;
			}
			else
			{
				/* OK, the source object is invalid. */
				ret = COMMON_ERROR_DATA_CORRUPTION;
			}
		}
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Buffer_Copy(MSYS_DataObject_T * dest, const MSYS_DataObject_T * source, const size_t copy_offset, const size_t copy_length)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of calls to other engine functions. */
	const MSYS_DataObject_T_Private * srcPrivStr = NULL;	/* The internal structure of the source data object. */
	MSYS_DataObject_T_Private * destPrivStr = NULL;			/* The internal structure of the dest data object. */

	/* Check args. */
	if ((source != NULL) && (dest != NULL) && (source != dest) && (source->ppObject != NULL) && (*(source->ppObject) != NULL) &&
		(dest->ppObject != NULL) && (*(dest->ppObject) != NULL) && (*(source->ppObject) != *(dest->ppObject)) &&
		(copy_offset >= 0) && (copy_length > 0))
	{
		/* Get the internal pointers. */
		srcPrivStr = (const MSYS_DataObject_T_Private *)(*(source->ppObject));
		destPrivStr = (MSYS_DataObject_T_Private *)(*(dest->ppObject));

		/* Check for valid data pointer in the source object. */
		retFromCall = MSYS_Check_DataObject_Consistency_Private(srcPrivStr);
		if (retFromCall == COMMON_ERROR_SUCCESS)
		{
			/* Check for data in the source structure. */
			if ((srcPrivStr->data != NULL) && (srcPrivStr->length > 0))
			{
				/* Check for valid dest object. */
				retFromCall = MSYS_Check_DataObject_Consistency_Private(destPrivStr);
				if (retFromCall == COMMON_ERROR_SUCCESS)
				{
					/* Check and see if we can get the correct range. */
					if ((SIZE_MAX - (SIZE_MAX - copy_offset)) > copy_length)
					{
						/* Check and see if the given offset and length is within the source buffer. */
						if ((copy_offset < srcPrivStr->length) && ((copy_offset + copy_length) < srcPrivStr->length))
						{
							/* Check and see if the requested length of data will fit in the given dest buffer. */
							if ((destPrivStr->data != NULL) && (copy_length < destPrivStr->capacity))
							{
								/* Reset the internal buffer for dest. */
								MSYS_Reset_DataObject_Private(destPrivStr);

								/* Copy the data. */
								memcpy(destPrivStr->data, (srcPrivStr->data + copy_offset), copy_length);

								/* Set the length of the dest object. */
								destPrivStr->length = copy_length;

								/* Done. */
								ret = COMMON_ERROR_SUCCESS;
							}
							else
							{
								/* Not enough space in the dest buffer to copy the data into it. */
								ret = COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL;
							}
						}
						else
						{
							/* Invalid source data range. */
							ret = COMMON_ERROR_RANGE_ERROR;
						}
					}
					else
					{
						/* OK, can't represent this value. */
						ret = COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED;
					}
				}
				else
				{
					/* OK, the dest object is invalid. */
					ret = COMMON_ERROR_DATA_CORRUPTION;
				}
			}
			else
			{
				/* No data in source object to create substring from. */
				ret = COMMON_ERROR_NO_DATA;
			}
		}
		else
		{
			/* OK, the source object is invalid. */
			ret = COMMON_ERROR_DATA_CORRUPTION;
		}
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Compare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */
	const MSYS_DataObject_T_Private * obj1PrivStr = NULL;	/* The internal structure of the obj1 data object. */
	const MSYS_DataObject_T_Private * obj2PrivStr = NULL;	/* The internal structure of the obj2 data object. */

	/* Check args. */
	if (obj1 != obj2)
	{
		/* Check and see if we got a NULL.... */
		if ((obj1 != NULL) && (obj2 != NULL))
		{
			/* Check internal pointer to pointers. */
			if (obj1->ppObject != obj2->ppObject)
			{
				/* Check for a NULL pointer to pointer object. */
				if ((obj1->ppObject != NULL) && (obj2->ppObject != NULL))
				{
					/* Check the private object pointers. */
					if (*(obj1->ppObject) != *(obj2->ppObject))
					{
						/* Check and see if a private object is NULL. */
						if ((*(obj1->ppObject) != NULL) && (*(obj2->ppObject) != NULL))
						{
							/* Get the internal pointers. */
							obj1PrivStr = ((const MSYS_DataObject_T_Private *)(*(obj1->ppObject)));
							obj2PrivStr = ((const MSYS_DataObject_T_Private *)(*(obj2->ppObject)));

							/* Check the capacity. */
							if (obj1PrivStr->capacity == obj2PrivStr->capacity)
							{
								/* Check the length. */
								if (obj1PrivStr->length == obj2PrivStr->length)
								{
									/* Check the buffer memory addresses. */
									if (obj1PrivStr->data == obj2PrivStr->data)
									{
										/* Objects are identical. */
										ret = COMMON_ERROR_COMPARISON_PASSED;
									}
									else
									{
										/* Objects have different buffers. */
										ret = COMMON_ERROR_COMPARISON_FAILED;
									}
								}
								else
								{
									/* Objects have different lengths. */
									ret = COMMON_ERROR_COMPARISON_FAILED;
								}
							}
							else
							{
								/* Objects have different capacities. */
								ret = COMMON_ERROR_COMPARISON_FAILED;
							}
						}
						else
						{
							/* Comparing a valid private object against a NULL object. */
							ret = COMMON_ERROR_COMPARISON_FAILED;
						}
					}
					else
					{
						/* Objects have the same private object memory address. */
						ret = COMMON_ERROR_COMPARISON_PASSED;
					}
				}
				else
				{
					/* Comparing a valid pointer to pointer object against a NULL object.
					
						This is the result of user manipulation of the public structures,
						the library will only free the public structure's pointer to pointer
						variable when that public structure itself is deallocated.
					 */
					ret = COMMON_ERROR_COMPARISON_FAILED;
				}
			}
			else
			{
				/* Objects have the same pointer to pointer memory address.

					This is the result of user manipulation of the public structures,
					the library will never create two different objects with the
					same pointer to pointer variable. (As it would break
					the Shallow Copy support and cause a double free.)
				 */
				ret = COMMON_ERROR_COMPARISON_PASSED;
			}
		}
		else
		{
			/* Comparing a valid public object against a NULL object. */
			ret = COMMON_ERROR_COMPARISON_FAILED;
		}
	}
	else
	{
		/* Objects have the same memory address. */
		ret = COMMON_ERROR_COMPARISON_PASSED;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_NCompare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)
{
	/* Call the compare function and inverse the result. */
	return (!(MSYS_DataObject_Compare(obj1, obj2)));
}

int MSYS_DataObject_Data_Compare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */
	const MSYS_DataObject_T_Private * obj1PrivStr = NULL;	/* The internal structure of the obj1 data object. */
	const MSYS_DataObject_T_Private * obj2PrivStr = NULL;	/* The internal structure of the obj2 data object. */

	/* Check args. */
	if (obj1 != obj2)
	{
		/* Check and see if we got a NULL.... */
		if ((obj1 != NULL) && (obj2 != NULL))
		{
			/* Check internal pointer to pointers. */
			if (obj1->ppObject != obj2->ppObject)
			{
				/* Check for a NULL pointer to pointer object. */
				if ((obj1->ppObject != NULL) && (obj2->ppObject != NULL))
				{
					/* Check the private object pointers. */
					if (*(obj1->ppObject) != *(obj2->ppObject))
					{
						/* Check and see if a private object is NULL. */
						if ((*(obj1->ppObject) != NULL) && (*(obj2->ppObject) != NULL))
						{
							/* Get the internal pointers. */
							obj1PrivStr = ((const MSYS_DataObject_T_Private *)(*(obj1->ppObject)));
							obj2PrivStr = ((const MSYS_DataObject_T_Private *)(*(obj2->ppObject)));

							/* Check the length. */
							if (obj1PrivStr->length == obj2PrivStr->length)
							{
								/* Check the buffer memory addresses. */
								if (obj1PrivStr->data != obj2PrivStr->data)
								{
									/* Check for NULL data buffers. */
									if ((obj1PrivStr->data != NULL) && (obj2PrivStr->data != NULL))
									{
										/* Check the data. */
										if (memcmp(obj1PrivStr->data, obj2PrivStr->data, obj1PrivStr->length) == 0)
										{
											/* Objects have the same data. */
											ret = COMMON_ERROR_COMPARISON_PASSED;
										}
										else
										{
											/* Objects have different data. */
											ret = COMMON_ERROR_COMPARISON_FAILED;
										}
									}
									else
									{
										/* Comparing a valid private buffer against a NULL buffer. */
										ret = COMMON_ERROR_COMPARISON_FAILED;
									}
								}
								else
								{
									/* Objects are identical. */
									ret = COMMON_ERROR_COMPARISON_PASSED;
								}
							}
							else
							{
								/* Objects have different lengths. */
								ret = COMMON_ERROR_COMPARISON_FAILED;
							}
						}
						else
						{
							/* Comparing a valid private object against a NULL object. */
							ret = COMMON_ERROR_COMPARISON_FAILED;
						}
					}
					else
					{
						/* Objects have the same private object memory address. */
						ret = COMMON_ERROR_COMPARISON_PASSED;
					}
				}
				else
				{
					/* Comparing a valid pointer to pointer object against a NULL object.
					
						This is the result of user manipulation of the public structures,
						the library will only free the public structure's pointer to pointer
						variable when that public structure itself is deallocated.
					 */
					ret = COMMON_ERROR_COMPARISON_FAILED;
				}
			}
			else
			{
				/* Objects have the same pointer to pointer memory address.

					This is the result of user manipulation of the public structures,
					the library will never create two different objects with the
					same pointer to pointer variable. (As it would break
					the Shallow Copy support and cause a double free.)
				 */
				ret = COMMON_ERROR_COMPARISON_PASSED;
			}
		}
		else
		{
			/* Comparing a valid public object against a NULL object. */
			ret = COMMON_ERROR_COMPARISON_FAILED;
		}
	}
	else
	{
		/* Objects have the same memory address. */
		ret = COMMON_ERROR_COMPARISON_PASSED;
	}			

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Data_NCompare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)
{
	/* Call the data compare function and inverse the result. */
	return (!(MSYS_DataObject_Data_Compare(obj1, obj2)));
}

int MSYS_DataObject_Reserve_Memory(MSYS_DataObject_T * obj, const size_t memoryLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of calls to other engine functions. */
	MSYS_DataObject_T_Private * realPtr = NULL;			/* Pointer to private data structure. */
	char * expandedBuffer = NULL;						/* Pointer to the expanded buffer. */

	/* Check args. */
	if ((obj != NULL) && (obj->ppObject != NULL) && (*(obj->ppObject) != NULL))
	{
		/* Get back the real pointer. */
		realPtr = (MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Check the private data structure. */
		retFromCall = MSYS_Check_DataObject_Consistency_Private(realPtr);
		if (retFromCall == COMMON_ERROR_COMPARISON_PASSED)
		{
			/* Check the memoryLength, and see if it's less than the current capacity, or equal to zero. */
			if ((memoryLength > 0) && (memoryLength > realPtr->capacity))
			{
				/* OK, we need to allocate a new buffer. */
				retFromCall = DataProcess_Reallocate_C_String(&expandedBuffer, 0, memoryLength);
				if ((retFromCall == COMMON_ERROR_SUCCESS) && (expandedBuffer != NULL))
				{
					/* Check for old data. */
					if ((realPtr->data != NULL) && (realPtr->capacity > 0))
					{
						/* Copy the original data. */
						memcpy(expandedBuffer, realPtr->data, realPtr->capacity);

						/* Deallocate the original buffer. */
						DataProcess_Deallocate_CString(&(realPtr->data));
						realPtr->capacity = 0;
					}

					/* Copy the expandedBuffer pointer to the object. */
					realPtr->data = expandedBuffer;
					realPtr->capacity = memoryLength;

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Could not copy the buffer. */
					ret = COMMON_ERROR_MEMORY_ERROR;
				}
			}
			else
			{
				/* Invalid memoryLength. (This function reserves absolute amounts memory, we won't deallocate it.) */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
			}
		}
		else
		{
			/* The data object is corrupt. */
			ret = COMMON_ERROR_DATA_CORRUPTION;
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

int MSYS_DataObject_Insert_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of calls to other engine functions. */
	MSYS_DataObject_T_Private * realPtr = NULL;			/* Pointer to private data structure. */
	char * expandedBuffer = NULL;						/* Pointer to the expanded buffer. */
	size_t newCapacity = 0;								/* The resulting capacity. */
	size_t newLength = 0;								/* The resulting length. */
	size_t realOffset = 0;								/* The offset used in the memcpy() calls. */

	/* Check args. */
	if ((obj != NULL) && (obj->ppObject != NULL) && (*(obj->ppObject) != NULL) && (data != NULL) && (dataLength > 0))
	{
		/* Get back the real pointer. */
		realPtr = (MSYS_DataObject_T_Private *)(*(obj->ppObject));

		/* Check for data object consistancy. */
		retFromCall = MSYS_Check_DataObject_Consistency_Private(realPtr);
		if (retFromCall == COMMON_ERROR_COMPARISON_PASSED)
		{
			/* If the given offset is bigger than the content length of the buffer, use the end of the buffer for the offset. */
			realOffset = ((offset < realPtr->length) ? (offset) : (realPtr->length));

			/* Check for valid offset. (I.e. Check for an UINT underflow attempt.) */
			if ((SIZE_MAX - (SIZE_MAX - realPtr->length)) >= realOffset)
			{
				/* Check and see if the given data will fit in the remaining capacity of the buffer. */
				if (dataLength > (realPtr->capacity - realPtr->length))
				{
					/* Buffer is not big enough. Check and see if the given dataLength will result in a UINT overflow. */
					if ((SIZE_MAX - realPtr->capacity) >= (dataLength))
					{
						/* Recalculate the needed capacity. */
						newCapacity = (realPtr->capacity + (dataLength - (realPtr->capacity - realPtr->length)));
						newLength = newCapacity;

						/* We must reallocate the buffer with enough space to store the data. */
						retFromCall = DataProcess_Reallocate_C_String(&expandedBuffer, 0, newCapacity);
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (expandedBuffer != NULL))
						{
							/* Copy the data. */
							memcpy(expandedBuffer, realPtr->data, realPtr->capacity);
						}
						else
						{
							/* Could not copy the buffer. */
							ret = COMMON_ERROR_MEMORY_ERROR;
						}
					}
					else
					{
						/* OK, the resulting data length is too big to be represented by a size_t variable on this system. */
						ret = COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED;
					}
				}
				else
				{
					/* Reuse the existing buffer. */
					expandedBuffer = realPtr->data;
					newCapacity = realPtr->capacity;
					newLength = (realPtr->length + dataLength);
				}

				/* Check that we are ok to continue. */
				if (expandedBuffer != NULL)
				{
					/* Check for data after the offset. */
					if (realOffset < realPtr->length)
					{
						/* Copy the data at the end of the buffer up to the end of the given data. */
						memcpy((expandedBuffer + realOffset + dataLength), (expandedBuffer + realOffset), (realPtr->length - realOffset));
					}

					/* Copy the given data into the buffer at the given offset. */
					memcpy((expandedBuffer + realOffset), data, dataLength);

					/* Update the private structure's length and capacity. */
					realPtr->capacity = newCapacity;
					realPtr->length = newLength;

					/* Check and see if we need to deallocate the original buffer. */
					if (realPtr->data != expandedBuffer)
					{
						/* Deallocate the original buffer. */
						DataProcess_Deallocate_CString((&(realPtr->data)));

						/* Copy in the new pointer. */
						realPtr->data = expandedBuffer;
					}

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
			}
			else
			{
				/* OK, the resulting offset is too big to be represented by a size_t variable on this system. */
				ret = COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED;
			}
		}
		else
		{
			/* Given data object is inconsistant. */
			ret = COMMON_ERROR_DATA_CORRUPTION;
		}
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int MSYS_DataObject_Insert_Char(MSYS_DataObject_T * obj, const size_t offset, const char data)
{
	/* Call real function. */
	return (MSYS_DataObject_Insert_CString(obj, offset, &data, sizeof(char)));
}

int MSYS_DataObject_Insert_From_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;					/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of calls to other engine functions. */
	const MSYS_DataObject_T_Private * srcPrivStr = NULL;	/* The internal structure of the source data object. */

	/* Check args. */
	if ((src != NULL) && (obj != NULL) && (src != obj) && (src->ppObject != NULL) && (*(src->ppObject) != NULL) &&
		(obj->ppObject != NULL) && (*(obj->ppObject) != NULL) && (*(src->ppObject) != *(obj->ppObject)))
	{
		/* Get the internal pointer for the source object. */
		srcPrivStr = (const MSYS_DataObject_T_Private *)(*(src->ppObject));

		/* Check for valid source object. */
		retFromCall = MSYS_Check_DataObject_Consistency_Private(srcPrivStr);
		if (retFromCall == COMMON_ERROR_COMPARISON_PASSED)
		{
			/* Check for valid data buffer and length. */
			if ((srcPrivStr->data != NULL) && (srcPrivStr->length > 0))
			{
				/* Call the insert C-String function. */
				retFromCall = MSYS_DataObject_Insert_CString(obj, offset, srcPrivStr->data, srcPrivStr->length);
				if (retFromCall == COMMON_ERROR_SUCCESS)
				{
					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Check error code. */
					ret = ((retFromCall != COMMON_ERROR_INVALID_ARGUMENT) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
				}
			}
			else
			{
				/* OK, the source object is empty. */
				ret = COMMON_ERROR_NO_DATA;
			}
		}
		else
		{
			/* OK, the source object is invalid. */
			ret = COMMON_ERROR_DATA_CORRUPTION;
		}
	}
	else
	{
		/* Invalid args. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}
