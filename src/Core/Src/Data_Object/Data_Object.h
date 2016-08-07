/*
	Multiverse Engine Project	Core Data_Object.h	02/4/2016

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

/* Include guard. */
#ifndef MSYS_DATAOBJECT_H
#define MSYS_DATAOBJECT_H

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Internal include for library symbol export. */
#include "../../../DLL_PORT.h"

/*!
		 typedef struct MSYS_DataObject {} MSYS_DataObject_T

		 This structure is a basic RAW data storage structure.

		 It supports preallocating memory in addition to reallocating
		 memory when needed to store data. It also supports Shallow Copies
		 by using reference counts, and Deep Copies where needed.

		 It is NOT synchronized, and therefore NOT thread safe. If it is to be
		 used in a threaded environment, care should be taken to ensure that no
		 data race conditions occur, either by wraping it in another thread-safe
		 container (best option), or by ensuring it is NOT shared between threads.
 */
MSYS_DLL_EXPORT typedef struct MSYS_DataObject {
	void ** ppObject;			/* The object itself. */
} MSYS_DataObject_T;

/*!
		int MSYS_Create_DataObject(MSYS_DataObject_T ** buffer)

		Creates a MSYS_DataObject_T object and sets the pointer pointed to by buffer to the
		newly created object.

		The created data structure should be deallocated with MSYS_Destroy_DataObject().

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer to pointer argument is invalid.
		Returns COMMON_ERROR_MEMORY_ERROR if an error occurs while allocating memory for the structure.
 */
MSYS_DLL_EXPORT int MSYS_Create_DataObject(MSYS_DataObject_T ** buffer);

/*!
		void MSYS_Destroy_DataObject(MSYS_DataObject_T ** buffer)

		Destroys (Deallocates) the given MSYS_DataObject_T object, created by
		MSYS_Create_DataObject() or MSYS_DataObject_Create_From_Existing_DataObject().

		This function has no return.
 */
MSYS_DLL_EXPORT void MSYS_Destroy_DataObject(MSYS_DataObject_T ** buffer);

/*!
		int MSYS_Check_DataObject_Consistency(const MSYS_DataObject_T * obj)

		Checks the given MSYS_DataObject_T object for consistency.

		Returns COMMON_ERROR_COMPARISON_PASSED if the given object is consistant.
		Returns COMMON_ERROR_COMPARISON_FAILED if the given object is NOT consistant.
		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is invalid.
 */
MSYS_DLL_EXPORT int MSYS_Check_DataObject_Consistency(const MSYS_DataObject_T * obj);

/*!
		int MSYS_DataObject_Get_Capacity(const MSYS_DataObject_T * obj, size_t * retPtr)

		Returns the currently allocated buffer's total memory capacity,
		by copying the value to retPtr.

		WARNING: The returned value is only valid so long as no other calls are made with
		the given object that will change the allocated buffer.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Get_Capacity(const MSYS_DataObject_T * obj, size_t * retPtr);

/*!
		int MSYS_DataObject_Get_Length(const MSYS_DataObject_T * obj, size_t * retPtr)

		Returns the currently allocated buffer's content length, (i.e. the length of the actual data
		in the given object), by copying the value to retPtr.

		WARNING: The returned value is only valid so long as no other calls are made with
		the given object that will change the allocated buffer OR it's content.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Get_Length(const MSYS_DataObject_T * obj, size_t * retPtr);

/*!
		int MSYS_DataObject_Get_Pointer(const MSYS_DataObject_T * buffer, const char ** retPtr)

		Returns the internal pointer that points to the currently allocated data buffer,
		by copying the internal pointer to retPtr.

		WARNING: The returned pointer should not be modified or deallocated. Also this pointer
		should only be accessed when NO other thread / process will access the given
		MSYS_Data_Object_T structure. FAILURE TO ABIDE BY THIS WARNING MAY CAUSE
		UNDEFINED BEHAVIOR.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Get_Pointer(const MSYS_DataObject_T * buffer, const char ** retPtr);

/*!
		int MSYS_DataObject_Get_Data_Copy(const MSYS_DataObject_T * buffer, char ** retPtr)

		Copies the given object's data to a C-String, and copies the resulting pointer to retPtr.

		The returned pointer should be deallocated with MSYS_Destroy_DataObject_Data_Copy() when it is
		no longer needed.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
		Returns COMMON_ERROR_MEMORY_ERROR if memory could not be allocated for the copied data.
		Returns COMMON_ERROR_NO_DATA if the given MSYS_DataObject_T has no data in it. (I.e. Length is zero.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Get_Data_Copy(const MSYS_DataObject_T * buffer, char ** retPtr);

/*!
		int MSYS_DataObject_Get_Byte(const MSYS_DataObject_T * buffer, char * retPtr, const size_t offset)

		Returns the value of the byte in the given MSYS_DataObject_T's allocated memory buffer at the given offset.

		Note: This function DOES NOT consider the current length (as returned by MSYS_DataObject_Get_Length())
		when checking the given offset. This is because it allows accessing any value in the allocated memory
		buffer for the object.

		Returns COMMON_ERROR_SUCCESS if successful. The desired byte will be stored in retPtr.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
		Returns COMMON_ERROR_NO_DATA if the given MSYS_DataObject_T lacks an allocated buffer. (I.e. Capacity is zero.)
		Returns COMMON_ERROR_DATA_CORRUPTION if the source MSYS_DataObject_T object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
		Returns COMMON_ERROR_RANGE_ERROR if the given offset argument is outside the given object's allocated memory buffer. (I.e. An offset that
		would point to data from before or after the end of the given data object's allocated memory buffer.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Get_Byte(const MSYS_DataObject_T * buffer, char * retPtr, const size_t offset);

/*!
		int MSYS_DataObject_Set_Byte(MSYS_DataObject_T * buffer, const char byte, const size_t offset)

		Sets the value of the byte in the given MSYS_DataObject_T's allocated memory buffer at the given offset.

		Note 1: This function DOES NOT consider the current length (as returned by MSYS_DataObject_Get_Length())
		when checking the given offset. This is because it allows accessing any value in the allocated memory
		buffer for the object.

		Note 2: This function DOES NOT allocate memory. If the given MSYS_DataObject_T lacks an allocated
		memory buffer when this function is called, or if the given offset is outside of the allocated
		memory buffer, an error will be returned. See below.

		Note 3: This function will set the length of the given MSYS_DataObject_T to include the set byte
		if the given offset is greater than the MSYS_DataObject_T's length at the time of the call.
		(I.e. length = ((length < offset) ? (offset) : (length)))

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
		Returns COMMON_ERROR_NO_DATA if the given MSYS_DataObject_T lacks an allocated buffer. (I.e. Capacity is zero.)
		Returns COMMON_ERROR_DATA_CORRUPTION if the source MSYS_DataObject_T object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
		Returns COMMON_ERROR_RANGE_ERROR if the given offset argument is outside the given object's allocated memory buffer. (I.e. An offset that
		would point to data from before or after the end of the given data object's allocated memory buffer.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Set_Byte(MSYS_DataObject_T * buffer, const char byte, const size_t offset);

/*!
		void MSYS_Destroy_DataObject_Data_Copy(char ** obj)

		Destroys (Deallocates) the copied object data, created by
		MSYS_DataObject_Get_Data_Copy().

		WARNING: DO NOT ATTEMPT to deallocate MSYS_DataObject_T objects with this function.
		Use MSYS_Destroy_DataObject() instead. Failure to do so, will result in
		UNDEFINED BEHAVIOR.

		This function has no return.
 */
MSYS_DLL_EXPORT void MSYS_Destroy_DataObject_Data_Copy(char ** obj);

/*!
		void MSYS_Clear_DataObject(MSYS_DataObject_T * obj)

		Clears the given MSYS_DataObject_T object to it's default state.
		(I.e. No allocated memory buffer, length and capacity are both set to zero.)

		If the given pointer is invalid this function will silently fail.

		This function has no return.
 */
MSYS_DLL_EXPORT void MSYS_Clear_DataObject(MSYS_DataObject_T * obj);

/*!
		void MSYS_Reset_DataObject(MSYS_DataObject_T * obj)

		This function erases all data in the given MSYS_DataObject_T object's buffer,
		(Sets all bytes to NULL) and sets it's length to zero (0). The capacity is left unchanged.

		If the given pointer / object is invalid, or there is no allocated buffer,
		this function will silently fail.

		This function has no return.
 */
MSYS_DLL_EXPORT void MSYS_Reset_DataObject(MSYS_DataObject_T * obj);

/*!
		int MSYS_DataObject_Create_From_Existing_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T ** retObj)

		Creates a new MSYS_DataObject_T structure from a pre-existing MSYS_DataObject_T structure,
		by creating a new structure, deep copying the original data, and copying the new structure's pointer
		to retObj.

		The created data structure should be deallocated with MSYS_Destroy_DataObject().

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
		Returns COMMON_ERROR_DATA_CORRUPTION if the source MSYS_DataObject_T object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Create_From_Existing_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T ** retObj);

/*!
		int MSYS_Shallow_Copy_DataObject(MSYS_DataObject_T * source, MSYS_DataObject_T * dest)

		Copies the data values from the source MSYS_DataObject_T object to the dest MSYS_DataObject_T object, without
		performing memory allocations. The source object has it's reference count incremented upon success.

		Note: Only the values are copied, the actual data is not. If either the source object or the dest object gets
		modified, the data for the other object will be as well. If either the source object or the dest object
		gets deallocated, the data will only be deallocated if the object being deallocated is the last reference
		to it.

		The maximum number of references to an object are defined by the system's SIZE_MAX. An object cannot have
		more references than that amount. Attempts to create more than the maximum allowed references, will result in
		an error.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if there are too many pre-existing references to the given object.
 */
MSYS_DLL_EXPORT int MSYS_Shallow_Copy_DataObject(MSYS_DataObject_T * source, MSYS_DataObject_T * dest);

/*!
		int MSYS_Deep_Copy_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T * dest)

		Copies the data from the source MSYS_DataObject_T object to the dest MSYS_DataObject_T object.

		Note: This function copies both the values for the struct and the actual data. (A deep copy.)
		Unlike MSYS_Shallow_Copy_DataObject(), the resulting dest object that this function produces
		is completely independant of the source object, and may be deallocated / modified without
		changing the source object at all.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
		Returns COMMON_ERROR_DATA_CORRUPTION if the source MSYS_DataObject_T object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
 */
MSYS_DLL_EXPORT int MSYS_Deep_Copy_DataObject(const MSYS_DataObject_T * source, MSYS_DataObject_T * dest);

/*!
		int MSYS_DataObject_Set_Data_From_CString(MSYS_DataObject_T * obj, const char * data, const size_t dataLength)

		Copies the given data into the given data object, deallocating any previous data held by that data object.
		(The result is the given data object only contains a copy of the given data.)

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, or the given dataLength is less than or equal to zero.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Set_Data_From_CString(MSYS_DataObject_T * obj, const char * data, const size_t dataLength);

/*!
		int MSYS_DataObject_Set_Data_From_Char(MSYS_DataObject_T * obj, const char data)

		Copies the given char into the given data object, deallocating any previous data held by that data object.
		(The result is the given data object only contains a copy of the given char.)

		Note: This function is just a wrapper for MSYS_DataObject_Set_Data_From_CString(),
		and is the equivalent to calling it like: MSYS_DataObject_Set_Data_From_CString(obj, &data, sizeof(char)).
		(That's what this function does....)

		As such this function's return codes are identical to MSYS_DataObject_Set_Data_From_CString().
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Set_Data_From_Char(MSYS_DataObject_T * obj, const char data);

/*!
		int MSYS_DataObject_Append_CString(MSYS_DataObject_T * obj, const char * data, const size_t dataLength)

		Appends the given C-Style string to the given data object's buffer.

		Note: This function is just a wrapper for MSYS_DataObject_Insert_CString(), with the given
		offset set to SIZE_MAX.

		See MSYS_DataObject_Insert_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Append_CString(MSYS_DataObject_T * obj, const char * data, const size_t dataLength);

/*!
		int MSYS_DataObject_Append_Char(MSYS_DataObject_T * obj, const char data)

		Appends the given char to the given data object's buffer.

		Note: This function is just a wrapper for MSYS_DataObject_Insert_CString(), with the given
		offset set to SIZE_MAX, and dataLength set to sizeof(char).

		See MSYS_DataObject_Insert_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Append_Char(MSYS_DataObject_T * obj, const char data);

/*!
		int MSYS_DataObject_Append_DataObject(MSYS_DataObject_T * obj, const MSYS_DataObject_T * src)

		Appends the given MSYS_DataObject_T object (src) to the given data object's (obj) buffer.

		Note: This function is just a wrapper for MSYS_DataObject_Insert_From_DataObject(), with the given
		offset set to SIZE_MAX.

		See MSYS_DataObject_Insert_From_DataObject() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Append_DataObject(MSYS_DataObject_T * obj, const MSYS_DataObject_T * src);

/*!
		int MSYS_DataObject_Substr(const MSYS_DataObject_T * obj, const size_t offset, const size_t endpoint, char ** substr)

		Creates a new substring from the given data object's current contents, using the given offset and endpoint (in bytes).
		The pointer for the new substring is then copied to substr.

		The resulting substring should be deallocated with DataProcess_Deallocate_CString() when no longer needed.

		Note: Both the offset and endpoint arguments are considered to be relative to the start of the data object's current buffer,
		and must be within that buffer. The resulting substring is always (endpoint - offset) bytes long. Also only the actual content
		of the buffer is considered, not the capacity of the buffer.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, the given offset is less than zero,
		or the given endpoint is less than or equal to the given offset.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if the resulting length / capacity of the substring would be
		bigger than the SIZE_MAX that the system supports.
		Returns COMMON_ERROR_DATA_CORRUPTION if the source MSYS_DataObject_T object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
		Returns COMMON_ERROR_NO_DATA if the given MSYS_DataObject_T has no data in it. (I.e. Length is zero.)
		Returns COMMON_ERROR_RANGE_ERROR if the given offset and / or endpoint arguments would result in a substring with contents outside of the
		given data object's current contents. (I.e. A substring that would contain data from before or after the end of the data object's contents.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Substr(const MSYS_DataObject_T * obj, const size_t offset, const size_t endpoint, char ** substr);

/*!
		int MSYS_DataObject_Buffer_Copy(MSYS_DataObject_T * dest, const MSYS_DataObject_T * source, const size_t copy_offset, const size_t copy_length)

		This function is designed to copy data from one data object to another, without performing a memory re/allocation of any kind.

		If the requested amount of data to be copied from the source object is too big to fit in the dest object,
		then an error will be returned.

		Note: This function will erase the contents of the dest buffer before copying the data from the source object if it succeeds.
		(I.e. The result is only the requested data from the source object will be in the dest object's memory buffer (starting at offset 0)
		if the function succeeds.) No changes to the dest object's capacity will be made, the dest object will have the same capacity as before
		the call to this function.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, the given copy_offset is less than zero,
		or the given copy_length is less than or equal to zero.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if the result of adding the given copy_offset and copy_length would be
		bigger than the SIZE_MAX that the system supports.
		Returns COMMON_ERROR_DATA_CORRUPTION if the source / dest MSYS_DataObject_T object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
		Returns COMMON_ERROR_NO_DATA if the given source MSYS_DataObject_T has no data in it. (I.e. Length is zero.).
		Returns COMMON_ERROR_RANGE_ERROR if the given copy_offset and / or copy_length arguments would result in a buffer with contents outside of the
		given source data object's current contents. (I.e. A buffer that would contain data from before or after the end of the source data object's contents.)
		Returns COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL if the given dest object's memory buffer is too small to contain the data to be copied from the source
		object.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Buffer_Copy(MSYS_DataObject_T * dest, const MSYS_DataObject_T * source, const size_t copy_offset, const size_t copy_length);

/*!
		int MSYS_DataObject_Compare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)

		This function checks the given MSYS_DataObject_T against another MSYS_DataObject_T object to
        see if they equal each other.

		Note: This function is looking for EXACT matches. Which means either the structures must have identical memory
		addresses or the buffer memory addresses, length, and capacities much match. (I.e. A shallow copy will match the object it was created
		from, but a deep copy will not. (The deep copy has a different internal buffer memory address.))

		Additional note: Passing a NULL object as a comparison will fail against a valid object.
		Passing two NULL objects will pass.

        Returns COMMON_ERROR_COMPARISON_PASSED if both MSYS_DataObject_T objects are equal. (Or both are NULL objects.)
        Returns COMMON_ERROR_COMPARISON_FAILED if MSYS_DataObject_T objects are NOT equal. (Or one object is NULL and the other is a VALID object.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Compare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2);

/*!
		int MSYS_DataObject_NCompare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)

		This function checks the given MSYS_DataObject_T against another MSYS_DataObject_T object to
        see if they equal each other, but inverses the result. (Via a NOT operation on the result.)

		Note: This function is a wrapper for MSYS_DataObject_Compare(), the only difference is that it inverses the result
		from MSYS_DataObject_Compare(). As such it's the equivalent to calling !(MSYS_DataObject_Compare(obj1, obj2)).

        Returns COMMON_ERROR_COMPARISON_FAILED if both MSYS_DataObject_T objects are equal. (Or both are NULL objects.)
        Returns COMMON_ERROR_COMPARISON_PASSED if MSYS_DataObject_T objects are NOT equal. (Or one object is NULL and the other is a VALID object.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_NCompare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2);

/*!
		MSYS_DLL_EXPORT int MSYS_DataObject_Data_Compare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)

		This function checks the data and lengths of the given MSYS_DataObject_T against another MSYS_DataObject_T object to
        see if they equal each other.

		Note: Unlike MSYS_DataObject_Compare(), this function does not check capacity, only the length and actual data is
		checked. In other words a shallow copy, AND a deep copy, will match the object it was created from. BUT, the allocated
		memory capacities MAY differ from each other.

		Additional note: Passing a NULL object as a comparison will fail against a valid object.
		Passing two NULL objects will pass.

        Returns COMMON_ERROR_COMPARISON_PASSED if both MSYS_DataObject_T objects are equal. (Or both are NULL objects.)
        Returns COMMON_ERROR_COMPARISON_FAILED if MSYS_DataObject_T objects are NOT equal. (Or one object is NULL and the other is a VALID object.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Data_Compare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2);

/*!
		int MSYS_DataObject_Data_NCompare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2)

		This function checks the data and lengths of the given MSYS_DataObject_T against another MSYS_DataObject_T object to
        see if they equal each other, but inverses the result. (Via a NOT operation on the result.)

		Note: This function is a wrapper for MSYS_DataObject_Data_Compare(), the only difference is that it inverses the result
		from MSYS_DataObject_Data_Compare(). As such it's the equivalent to calling !(MSYS_DataObject_Data_Compare(obj1, obj2)).

        Returns COMMON_ERROR_COMPARISON_FAILED if both MSYS_DataObject_T objects are equal. (Or both are NULL objects.)
        Returns COMMON_ERROR_COMPARISON_PASSED if MSYS_DataObject_T objects are NOT equal. (Or one object is NULL and the other is a VALID object.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Data_NCompare(const MSYS_DataObject_T * obj1, const MSYS_DataObject_T * obj2);

/*!
		int MSYS_DataObject_Reserve_Memory(MSYS_DataObject_T * obj, const size_t memoryLength)

		This function reserves memory (preallocates) for a data object. If this function reallocates
		memory, then any pre-existing data will be retained after the reallocation.

		Note: This function expects that the given length is the total amount
		of memory to allocate for the data object, not the amount added.

		I.e if you have allocated 6 bytes, and then call this function with the amount
		of 7 bytes you will get a total size of 7 bytes not 13 bytes.

		If given a length that is equal to zero or less than the given object's current
		capacity, this function will return an error.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, the given memoryLength is equal to zero,
		or the given memoryLength is less than or equal to the given object's current capacity.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
		Returns COMMON_ERROR_DATA_CORRUPTION if the given data object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Reserve_Memory(MSYS_DataObject_T * obj, const size_t memoryLength);

/*!
		int MSYS_DataObject_Insert_CString_No_Allocaton(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength)

		Inserts the given C-Style string to the given data object's buffer at the given offset. (No memory allocation version.)

		Note: If the given data object's remaining capacity is not big enough to hold the pre-existing data and the given string,
		then an error will be returned, and the data object will not be modified. (Use MSYS_DataObject_Insert_CString() if you want memory to be
		reallocated automatically. This function is intended to be used when memory is preallocated for the data.)

		If this function is given an offset greater than the length of the given object's pre-existing content, (as returned by MSYS_DataObject_Get_Length()),
		then this function will append the given data to the end of the given object's pre-existing content. (Pre-allocated capacity is ignored when considering
		the position of the offset.)

		I.E.
			Pre-existing content: "Cat" (Length: 3)
				--> Actual buffer: "Cat     " (Total Capacity: 8)
			Given Data: " Stop" (Length: 5)
			Given offset: 5.
			Result: "Cat Stop" (Length: 8)
				--> Actual buffer: "Cat Stop" (Total Capacity: 8)

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, or the given dataLength is less than or equal to zero.
		Returns COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL if the given data object lacks a big enough buffer to store the given data and it's original data.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if the resulting calculations on offset / length / capacity would be bigger than the SIZE_MAX
		that the system supports.
		Returns COMMON_ERROR_DATA_CORRUPTION if the given data object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Insert_CString_No_Allocaton(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength);

/*!
		int MSYS_DataObject_Insert_Char_No_Allocaton(MSYS_DataObject_T * obj, const size_t offset, const char data)

		Inserts the given char into the given data object, at the given offset. (No memory allocation version.)

		Note: This function is just a wrapper for MSYS_DataObject_Insert_CString_No_Allocaton(), and is the equivalent to calling
		MSYS_DataObject_Insert_CString_No_Allocaton(obj, offset, data, sizeof(char)).

		See MSYS_DataObject_Insert_CString_No_Allocaton() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Insert_Char_No_Allocaton(MSYS_DataObject_T * obj, const size_t offset, const char data);

/*!
		int MSYS_DataObject_Insert_From_DataObject_No_Allocaton(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src)

		Inserts the given source (src) data object's content, into the given dest data object (obj), at the given offset. (No memory allocation version.)

		Note: This function is just a wrapper for MSYS_DataObject_Insert_CString_No_Allocaton().

		See MSYS_DataObject_Insert_CString_No_Allocaton() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Insert_From_DataObject_No_Allocaton(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src);

/*!
		int MSYS_DataObject_Insert_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength)

		Inserts the given C-Style string to the given data object's buffer at the given offset.

		Note: This function performs memory (re)allocations. If you DO NOT want the buffer to be reallocated automatically,
		(due to memory constraints / design considerations / etc.) call MSYS_DataObject_Insert_CString_No_Allocaton() instead.

		Note 2: If the given data object's remaining capacity is not big enough to hold the pre-existing data and the given string,
		then the object's buffer will be reallocated to be big enough to contain both. The resulting buffer will be
		have a length and capacity that are equal to the length of the pre-existing data and the given string.
		I.E.
			 newCapacity = (obj->capacity + (dataLength - (obj->capacity - obj->length)))
			 newLength = newCapacity

		If this function is given an offset greater than the length of the given object's pre-existing content, (as returned by MSYS_DataObject_Get_Length()),
		then this function will append the given data to the end of the given object's pre-existing content. (Pre-allocated capacity is ignored when considering
		the position of the offset.)

		Example without remaining data:
			Pre-existing content: "Dog" (Length: 3)
				--> Actual buffer: "Dog     " (Total Capacity: 8)
			Given Data: " Eats." (Length: 6)
			Given offset: 5.
			Result: "Dog Eats." (Length: 9)
				--> Actual buffer: "Dog Eats." (Total Capacity: 9)

		Example with remaining data:
		Pre-existing content: "Suzie walked to the park." (Length: 25)
				--> Actual buffer: "Suzie walked to the park. " (Total Capacity: 26)
			Given Data: "ran" (Length: 3)
			Given offset: 6.
			Result: "Suzie ranwalked to the park. " (Length: 29)
				--> Actual buffer: "Suzie ranwalked to the park. " (Total Capacity: 29)

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, or the given dataLength is less than or equal to zero.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if the resulting calculations on offset / length / capacity would be bigger than the SIZE_MAX
		that the system supports.
		Returns COMMON_ERROR_DATA_CORRUPTION if the given data object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Insert_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength);

/*!
		int MSYS_DataObject_Insert_Char(MSYS_DataObject_T * obj, const size_t offset, const char data)

		Inserts the given char into the given data object, at the given offset.

		Note: This function is just a wrapper for MSYS_DataObject_Insert_CString(), and is the equivalent to calling
		MSYS_DataObject_Insert_CString(obj, offset, data, sizeof(char)).

		See MSYS_DataObject_Insert_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Insert_Char(MSYS_DataObject_T * obj, const size_t offset, const char data);

/*!
		int MSYS_DataObject_Insert_From_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src)

		Inserts the given source (src) data object's content, into the given dest data object (obj), at the given offset.

		Note: This function is just a wrapper for MSYS_DataObject_Insert_CString().

		See MSYS_DataObject_Insert_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Insert_From_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src);

/*!
		int MSYS_DataObject_Replace_With_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength)

		Takes the given C-Style string and replaces the given data object's buffer at the given offset with it, and updates the data object's
		length if needed.

		Note: If any data past the given offset is not replaced it will be retained.

		Example with remaining data:
		Pre-existing content: "Suzie walked to the park." (Length: 25)
				--> Actual buffer: "Suzie walked to the park. " (Total Capacity: 26)
			Given Data: "ran" (Length: 3)
			Given offset: 6.
			Result: "Suzie ranked to the park. " (Length: 26)
				--> Actual buffer: "Suzie ranked to the park. " (Total Capacity: 26)

		Note 2: This function does NOT perform memory (re)allocations. In cases where a memory (re)allocation is required, an error will be returned,
		and the given data object will NOT be altered. If you want the buffer to be reallocated automatically, call
		MSYS_DataObject_Overwrite_With_CString() instead.

		Note 3: This function is only for replacing existing data. The given offset must be within the given data object's length, (A special case
		is permitted for when length is zero. See note 4.) and the given data must fit within the remaining space in memory buffer, or an error
		will be returned.

		Note 4: In the event the given data object's length is zero, then the given offset must be zero. (Pre-allocated capacity is ignored when
		considering the position of the offset.) The given data must still fit within the capacity of the existing memory buffer.

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, or the given dataLength is less than or equal to zero.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if the resulting calculations on offset / length / capacity would be bigger than the SIZE_MAX
		that the system supports.
		Returns COMMON_ERROR_DATA_CORRUPTION if the given data object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
		Returns COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL if the given offset and / or dataLength would require a memory reallocation to fit within the
		given data object's memory buffer.
		Returns COMMON_ERROR_RANGE_ERROR if the given offset is beyond the current length of the buffer. (As returned by MSYS_DataObject_Get_Length().)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Replace_With_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength);

/*!
		int MSYS_DataObject_Replace_With_Char(MSYS_DataObject_T * obj, const size_t offset, const char data)

		Replaces the given data object's data, at the given offset, with the given char.

		Note: This function is just a wrapper for MSYS_DataObject_Replace_With_CString(), and is the equivalent to calling
		MSYS_DataObject_Replace_With_CString(obj, offset, data, sizeof(char)).

		See MSYS_DataObject_Replace_With_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Replace_With_Char(MSYS_DataObject_T * obj, const size_t offset, const char data);

/*!
		int MSYS_DataObject_Replace_With_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src)

		Replaces the given dest data object (obj)'s content, with the given source (src) data object's content, at the given offset.

		Note: This function is just a wrapper for MSYS_DataObject_Replace_With_CString().

		See MSYS_DataObject_Replace_With_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Replace_With_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src);

/*!
		int MSYS_DataObject_Overwrite_With_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength)

		Takes the given C-Style string and overwrites the given data object's buffer at the given offset with it, and updates the data object's
		length if needed.

		If the buffer is not big enough to contain the entireity of the given data after the given offset, the buffer will be automaticly reallocated
		to be able to contain the data.
			I.e.
				newCapacity = (offset + dataLength)
				newLength = newCapacity

		Note: If any data past the given offset is not overwritten it will be retained.

		Example without remaining data:
		Pre-existing content: "Dog bark" (Length: 8)
				--> Actual buffer: "Dog bark " (Total Capacity: 9)
			Given Data: "ug Eats." (Length: 8)
			Given offset: 2.
			Result: "Doug Eats." (Length: 10)
				--> Actual buffer: "Doug Eats." (Total Capacity: 10)

		Example with remaining data:
		Pre-existing content: "Suzie walked to the park." (Length: 25)
				--> Actual buffer: "Suzie walked to the park. " (Total Capacity: 26)
			Given Data: "ran" (Length: 3)
			Given offset: 6.
			Result: "Suzie ranked to the park. " (Length: 26)
				--> Actual buffer: "Suzie ranked to the park. " (Total Capacity: 26)

		Note 2: This function performs memory (re)allocations. If you DO NOT want the buffer to be reallocated automatically,
		(due to memory constraints / design considerations / etc.) call MSYS_DataObject_Replace_With_CString() instead.

		Note 3: This function is only for overwriting existing data. The given offset must be within the given data object's length, (A special case
		is permitted for when length is zero. See note 4.)

		Note 4: In the event the given data object's length is zero, then the given offset must be zero. (Pre-allocated capacity is ignored when
		considering the position of the offset.)

		Returns COMMON_ERROR_SUCCESS if successful.
		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is invalid, or the given dataLength is less than or equal to zero.
		Returns COMMON_ERROR_SYSTEM_LIMIT_EXCEEDED if the resulting calculations on offset / length / capacity would be bigger than the SIZE_MAX
		that the system supports.
		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
		Returns COMMON_ERROR_DATA_CORRUPTION if the given data object is inconsistant. (E.x. No allocated buffer, but size or capacity > 0.)
		Returns COMMON_ERROR_RANGE_ERROR if the given offset is beyond the current length of the buffer. (As returned by MSYS_DataObject_Get_Length().)
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Overwrite_With_CString(MSYS_DataObject_T * obj, const size_t offset, const char * data, const size_t dataLength);

/*!
		int MSYS_DataObject_Overwrite_With_Char(MSYS_DataObject_T * obj, const size_t offset, const char data)

		Overwrites the given data object's data, at the given offset, with the given char.

		Note: This function is just a wrapper for MSYS_DataObject_Overwrite_With_CString(), and is the equivalent to calling
		MSYS_DataObject_Overwrite_With_CString(obj, offset, data, sizeof(char)).

		See MSYS_DataObject_Overwrite_With_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Overwrite_With_Char(MSYS_DataObject_T * obj, const size_t offset, const char data);

/*!
		int MSYS_DataObject_Overwrite_With_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src)

		Overwrites the given dest data object (obj)'s content, with the given source (src) data object's content, at the given offset.

		Note: This function is just a wrapper for MSYS_DataObject_Overwrite_With_CString().

		See MSYS_DataObject_Overwrite_With_CString() for the list of possible return codes / expected behavior.
 */
MSYS_DLL_EXPORT int MSYS_DataObject_Overwrite_With_DataObject(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src);

/* Check for C++ compiler. */
#ifdef __cplusplus
}	/* End of extern "C" */
#endif	/* __cplusplus */

#endif	/* MSYS_DATAOBJECT_H */

/* End of Data_Object.h. */
