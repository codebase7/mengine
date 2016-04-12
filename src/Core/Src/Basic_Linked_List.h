/*!
    Multiverse Engine Project 25/6/2015 Basic_Linked_List.h

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

/* Include guard. */
#ifndef MSYS_BASIC_LINKED_LIST_H
#define MSYS_BASIC_LINKED_LIST_H

/* Begin extern C if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Internal includes. */
#include "../../DLL_PORT.h"	/* Defines MSYS_DLL_EXPORT, and MSYS_DLL_IMPORT_TEMPLATE. */
#include "../../Common/Src/Error_Handler/Common_Error_Handler_Error_Codes.h" /* Defines Common error codes used for return codes. */

/* External includes. */
#include <stddef.h>	/* Define NULL, size_t. */

/* Define basic linked list object. */
typedef struct MSYS_Linked_List {
	int allocated;				/* Whether or not we have used our allocator for the data we point to. */
	void * data;				/* Data structure for this object in the chain. */
	size_t dataLength;			/* Optional Length of the given data structure if data is non-NULL. */
	struct MSYS_Linked_List * nextObject;	/* The next object in the chain, should be NULL if the current object is the last one in the chain. */
	struct MSYS_Linked_List * prevObject;	/* The previous object in the chain, should be NULL if the current object is the first one in the chain. */
} MSYS_Linked_List_T;

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Allocate_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList)
 *
 * 	Allocates a new MSYS_Linked_List object. 
 * 
 * 	If the given pointer to object is non-NULL, the newly allocated object will be pointed
 * 	to by the given object's nextObject pointer. If given object's nextObject pointer is
 * 	non-NULL, then the newly allocated object will be inserted between the given object and
 * 	the object that came after it prior to the call to this function.
 * 
 * 	Ex.
 * 	ppAllocatedList		nextObject pointer	result:
 * 	NULL			N / A			(*ppAllocatedList) points to allocated object.
 * 
 * 	non-NULL		NULL			(*ppAllocatedList)->nextObject points to allocated object.
 * 
 * 	non-NULL		non-NULL		(*ppAllocatedList)->nextObject points to allocated object,
 * 							allocated object->nextObject points to nextObject.
 * 							allocated object->prevObject points to (*ppAllocatedList).
 * 							nextObject->prevObject points to allocated object. (ONLY TRUE IF nextObject->prevObject == (*ppAllocatedList))
 *
 * 	Returns COMMON_ERROR_SUCCESS if allocation was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if given pointer to pointer was NULL.
 * 	Returns COMMON_ERROR_MEMORY_ERROR if memory allocation for new object failed.
 * 	Otherwise returns the appropriate error.
 * 
 * 	If an error is returned, then the list will not be altered.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Allocate_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList);

/*!
 *	MSYS_DLL_EXPORT int MSYS_Linked_List_Allocate_And_Return_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList, MSYS_Linked_List_T ** ppAllocatedObject)
 *
 *	This function is a wrapper around MSYS_Linked_List_Allocate_Linked_List_Object()
 *	that returns the allocated object's pointer via the function's ppAllocatedObject pointer.
 *
 *  If ppAllocatedObject is NULL, then this function's behavior is identical to calling:
 *		MSYS_Linked_List_Allocate_Linked_List_Object(ppAllocatedList).
 *
 *  See MSYS_Linked_List_Allocate_Linked_List_Object() for error code descriptions.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Allocate_And_Return_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList, MSYS_Linked_List_T ** ppAllocatedObject);

/*!
 * 	MSYS_DLL_EXPORT void MSYS_Linked_List_Deallocate_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList)
 *
 * 	Deallocates the given MSYS_Linked_List object, and sets it's pointer to NULL.
 *
 * 	If the given object points to any other MSYS_Linked_List object, then they will be modified to
 * 	reflect the removal of the given object.
 * 	I.e. The pointed to objects will have their nextObject and prevObject pointers updated.
 *
 * 	This function has no return, and will silently fail if the given pointer to pointer is NULL.
 * 	Otherwise upon return, the given pointer to object will be set to NULL.
 */
MSYS_DLL_EXPORT void MSYS_Linked_List_Deallocate_Linked_List_Object(MSYS_Linked_List_T ** ppAllocatedList);

/*!
 * 	MSYS_DLL_EXPORT void MSYS_Linked_List_Deallocate_Entire_List(MSYS_Linked_List_T ** ppAllocatedList)
 *
 * 	Deallocates the given MSYS_Linked_List object and all other objects in it's list. Then sets the given
 * 	argument to NULL.
 *
 * 	If the given object points to any other MSYS_Linked_List object, then they will deallocated as well.
 *
 * 	This function has no return, and will silently fail if the given pointer to pointer is NULL.
 * 	Otherwise upon return, the given pointer to object will be set to NULL.
 */
MSYS_DLL_EXPORT void MSYS_Linked_List_Deallocate_Entire_List(MSYS_Linked_List_T ** ppAllocatedList);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Get_First_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppFirstObject)
 *
 * 	Copies the pointer to the first object in the list to the given ppFirstObject argument.
 *
 * 	Returns COMMON_ERROR_SUCCESS if copying the pointer to the first object was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to pointer or pointer to object was NULL.
 * 	Returns COMMON_ERROR_INTERNAL_ERROR if the given linked list is broken. (I.e. recursive.)
 * 	Otherwise returns the appropriate error.
 *
 * 	If an error occurs, ppFirstObject will not be modified.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Get_First_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppFirstObject);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Last_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppLastObject)
 *
 * 	Copies the pointer to the last object in the list to the given ppLastObject argument.
 *
 * 	Returns COMMON_ERROR_SUCCESS if copying the pointer to the last object was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to pointer or pointer to object was NULL.
 * 	Returns COMMON_ERROR_INTERNAL_ERROR if the given linked list is broken. (I.e. recursive.)
 * 	Otherwise returns the appropriate error.
 *
 * 	If an error occurs, ppLastObject will not be modified.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Last_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppLastObject);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Next_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppNextObject)
 *
 * 	Copies the pointer to the next object in the list to the given ppNextObject argument.
 *
 * 	Returns COMMON_ERROR_SUCCESS if copying the pointer to the next object was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to pointer or pointer to object was NULL.
 * 	Otherwise returns the appropriate error.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Next_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppNextObject);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Previous_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppPrevObject)
 *
 * 	Copies the pointer to the previous object in the list to the given ppPrevObject argument.
 *
 * 	Returns COMMON_ERROR_SUCCESS if copying the pointer to the previous object was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to pointer or pointer to object was NULL.
 * 	Otherwise returns the appropriate error.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Previous_Object(const MSYS_Linked_List_T * pAllocatedList, MSYS_Linked_List_T ** ppPrevObject);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Current_Object_Contents(const MSYS_Linked_List_T * pAllocatedList, void ** ppData, size_t * dataLength, const int copyData)
 *
 * 	Copies the contents of the given object in the list to the given pointers.
 *
 *	@Pram: copyData, whether or not to copy the data the MSYS_LINKED_LIST_T object points to.
 *	(If applicable see below.)
 *
 *	If copyData is non-zero, the given MSYS_LINKED_LIST_T object allocated (copied) the data it points to,
 *	and the given length of the data was greater than zero, then this function will copy the data from the
 *	given MSYS_LINKED_LIST_T object and return a pointer to the copy.
 *	This pointer should be deallocated by calling MSYS_Linked_List_Deallocate_Copied_Data().
 *
 *	If copyData is zero, the given MSYS_LINKED_LIST_T object did not allocate the data it points to, or
 *	the given length of the data was 0, then this function will only copy the MSYS_LINKED_LIST_T object's
 *	internal data pointer and dataLength.
 *
 * 	Returns COMMON_ERROR_SUCCESS if copying the contents was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to pointer or pointer to data was NULL.
 *	Returns COMMON_ERROR_MEMORY_ERROR if memory allocation for coping data failed.
 * 	Otherwise returns the appropriate error.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Current_Object_Contents(const MSYS_Linked_List_T * pAllocatedList, void ** ppData, size_t * dataLength, const int copyData);

/*!
 *	MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Allocated(const MSYS_Linked_List_T * pAllocatedList, int * isAllocated)
 *
 *	This function returns whether or not the given MSYS_LINKED_LIST_T object has allocated
 *	the data it points to or not via it's isAllocated argument.
 *
 *	Returns COMMON_ERROR_SUCCESS if successful.
 *	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to pointer or pointer to data was NULL.
 * 	Otherwise returns the appropriate error code.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Get_Allocated(const MSYS_Linked_List_T * pAllocatedList, int * isAllocated);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Set_Current_Object_Contents(MSYS_Linked_List_T * pAllocatedList, void * pData, const size_t dataLength, const int copyData)
 *
 * 	Copies the given contents to the given object in the list.
 *
 *	Pram: copyData, If non-zero the data pointed to by pData will be copied using the
 *	linked list library's internal allocator.
 *	If copyData is zero, then only the given pointer will be copied.
 *
 * 	Returns COMMON_ERROR_SUCCESS if copying the contents was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to object was NULL.
 *	Returns COMMON_ERROR_MEMORY_ERROR if memory allocation for coping data failed.
 * 	Otherwise returns the appropriate error.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Set_Current_Object_Contents(MSYS_Linked_List_T * pAllocatedList, void * pData, const size_t dataLength, const int copyData);

/*!
 * 	MSYS_DLL_EXPORT int MSYS_Linked_List_Swap_Objects(MSYS_Linked_List_T * pFirstObject, MSYS_Linked_List_T * pSecondObject)
 *
 * 	Swaps the given contents of the two given objects in the list.
 *
 * 	Returns COMMON_ERROR_SUCCESS if swapping the contents of the two objects was successful.
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer to object was NULL.
 * 	Otherwise returns the appropriate error.
 */
MSYS_DLL_EXPORT int MSYS_Linked_List_Swap_Objects(MSYS_Linked_List_T * pFirstObject, MSYS_Linked_List_T * pSecondObject);

/*!
 *	MSYS_DLL_EXPORT void MSYS_Linked_List_Deallocate_Copied_Data(void ** ppData)
 *
 *	This function deallocates data that was copied out of a MSYS_LINKED_LIST_T object
 *	by a call to MSYS_Linked_List_Get_Current_Object_Contents().
 *
 *	This function should ALWAYS be used to deallocate data that was copied out of a
 *	MSYS_LINKED_LIST_T object by a call to MSYS_Linked_List_Get_Current_Object_Contents().
 *
 *	If the given pointer is invalid this function will silently fail.
 *
 *	This function has no return.
 */
MSYS_DLL_EXPORT void MSYS_Linked_List_Deallocate_Copied_Data(void ** ppData);

/* End extern C if needed. */
#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* MSYS_BASIC_LINKED_LIST_H */

/* End of Basic_Linked_List.h. */