/*!
    Multiverse Engine Project DataProcess DataProcess.h

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

/* Include guard. */
#ifndef DATAPROCESS_H
#define DATAPROCESS_H

/* Internal includes. */
#include "Panic.h"
#if _MSC_FULL_VER && _MSC_FULL_VER < 180031101
/* Visual C++ 2013 introduced support for C99's _Bool. Anything lower than that has to use our fake bool header. */
#include "../../stdbool.h"
#else
/* Use the built in bool data type. */
#include <stdbool.h>
#endif	/* _MSC_FULL_VER 180021005 */

/* Define extern "C". */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* External includes. */
#include <stddef.h>

/* Include data object C header. */
#include "Data_Object/Data_Object.h"

/* Include DLL_PORT.h */
#include "../../DLL_PORT.h"

/* We need to include stdint.h for SIZE_MAX. (MSVC includes it automaticly with the above headers.) */
#ifdef __GNUC__
#include <stdint.h>
#endif  /* __GNUC__ */

/* Define C functions. */
/*!
	size_t DataProcess_Trivial_Random_Number_Generator(const size_t min_value, const size_t max_value, const bool reset_rand)

	This function generates psudo-random numbers based on the given max_value.

	@pram min_value, the minimum value that is acceptable for the function to return.
	@pram max_value, the maximum value that is acceptable for the function to return.

	E.x. If you want a range of 1 to 100 set min_value to 1 and max_value to 100.

	@pram reset_rand, if this is set to true, the RNG will be re-seeded with the current time value returned by time().
	Otherwise the next psudo-random number from the current seed will be returned.

	Returns the generated psudo-random number if successful.
	If the current system time cannot be used to set the random seed, then this function will consistantly return zero (0)
	regardless of the range defined by min_value and max_value.
*/
MSYS_DLL_EXPORT size_t DataProcess_Trivial_Random_Number_Generator(const size_t min_value, const size_t max_value, const bool reset_rand);

/*!
 *		int DataProcess_Reallocate_C_String(char ** str, const size_t strLength, const size_t newLength)
 *
 *		Reallocates the given string to be the new length.
 *
 *		Optionally it may do the following:
 *			- If newLength is 0, it will only deallocate the given string.
 *			- If newLength is greater than zero, but str is NULL or strLength is zero then,
 *			  this function will only allocate a string of newLength bytes.
 *			  (The string will be NULL filled.)
 *			- If newLength and strLength is greater than zero, and str is non-NULL,
 *			  then the data from str will be copied into the reallocated string as follows:
 *				- If the newLength is less than the original length, then the data from str
 *				  will be copied, but any bytes after newLength will be truncated.
 *				- If the newLength is greater than or equal to the original length then,
 *				  the entire original string will be copied.
 *			In any instance, the reallocated string may NOT be NULL terminated. This occurs if
 *			data is copied from the original string and either the original string is not NULL
 *			terminated, or if the data to be copied from the original string did not include the
 *			NULL terminator. In addition, the resulting string is always newLength in size if
 *			this function is successful.
 *
 *		Returns COMMON_ERROR_SUCCESS if successful.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer to pointer is NULL.
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *		Otherwise returns the appropriate error code.
 *
 *		In case of error, the given arguments will NOT be altered.
 */
MSYS_DLL_EXPORT int DataProcess_Reallocate_C_String(char ** str, const size_t strLength, const size_t newLength);

/*!
 *		int DataProcess_Reallocate_C_String_With_NULL_Terminator(char ** str, const size_t strLength, size_t * newLength)
 *
 *		Reallocates the given string to be the new length and adds a NULL byte terminator if needed.
 *		The resulting string is guaranteed to ALWAYS be NULL byte terminated if this function returns COMMON_ERROR_SUCCESS.
 *
 *		Note: This function WILL change the given string to make it NULL byte terminated if the NULL byte
 *		could not be added during reallocation (this happens if the additional byte would result in a length greater than SIZE_MAX),
 *		but only if the function returns COMMON_ERROR_SUCCESS.
 *
 *		(This function is a wrapper around DataProcess_Reallocate_C_String(), see that function for more information.)
 *
 *		In case of error, the given arguments will NOT be altered.
 */
MSYS_DLL_EXPORT int DataProcess_Reallocate_C_String_With_NULL_Terminator(char ** str, const size_t strLength, size_t * newLength);

/*!
 *		void DataProcess_Deallocate_CString(char ** str)
 *
 *		Destructor function for C-Strings allocated by DataProcess.
 *
 *		WARNING: Giving an object or a C-String not allocated by DataProcess will cause
 *		undefined behaviour.
 *
 *		If a given pointer is NULL, this function will silently fail.
 *
 *		This function has no return.
 */
MSYS_DLL_EXPORT void DataProcess_Deallocate_CString(char ** str);

/*!
	int DataProcess_Copy_C_String(const char * source, const size_t sourceLength, char ** dest)

	Internal function for coping a const string for later modification.
	(Copied string if the function succeeds will be pointed to by dest, copied string is always
	 the same length as it's source.)

	Note: This function will overwrite dest without deallocating it. If you need whatever
	dest points to after this function returns, copy the pointer elsewhere before calling
	this function.

	When this string is no longer needed it should be deallocated by
	DataProcess_Deallocate_CString().

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is NULL, or if sourceLength <= 0.
	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
*/
MSYS_DLL_EXPORT int DataProcess_Copy_C_String(const char * source, const size_t sourceLength, char ** dest);

/*!
 *		int DataProcess_getCStringFromSizeT(const size_t number, char ** str, size_t * strLength)
 *
 *		Takes given size_t and outputs the equivalent human-readable string as a C-String.
 *
 *		The generated string should be freed using DataProcess_Deallocate_CString() when it is no longer needed.
 *
 *		WARNING: This function will NOT deallocate the given string if it is already allocated.
 *		The pointer WILL be overwritten if this function returns success!
 *		If you need to keep the pointer for later deallocation, copy it elsewhere before calling this function.
 *
 *		Returns COMMON_ERROR_SUCCESS if successful. str will point to a C-String with string equivalent to number in this case.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if a given argument is invalid.
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *		Otherwise returns the appropriate error code.
 *
 *		No alteration clause:
 *		In case of error, this function will not alter any given argument.
 */
MSYS_DLL_EXPORT int DataProcess_getCStringFromSizeT(const size_t number, char ** str, size_t * strLength);

/*!
 *		int DataProcess_Get_SubString_Using_Delimiter(const char * src, const size_t srcLength, const char * delim, const size_t delimLength,
 *													char ** subStr, size_t * subStrLength, const int searchFromEnd, const int getPriorData)
 *
 *		Basic delimiter based sub-string generation function.
 *
 *		Takes the given source string and looks for the first occurrence of the given delimiter string within it.
 *		If the delimiter string is found, this function will produce a sub-string with either the remaining bytes in the
 *		source string that come after the delimiter, or the bytes from the source string that came before the delimiter.
 *
 *		The generated sub-string should be freed using DataProcess_Deallocate_CString() when it is no longer needed.
 *
 *		Optionally if searchFromEnd is non-zero, the search will start from the end of the source string instead of the beginning.
 *
 *		Notes about resulting substring:
 *		If getPriorData is true, the length of the substring is sourceLength - <delimiter offset>, otherwise
 *		the length of the substring is <delimiter offset> - <delimiter length>.
 *
 *		If getPriorData is true the start of the substring is the start of the source string, otherwise it depends
 *		on the value of searchFromEnd. If searchFromEnd is true, then the start of the substring is
 *		(<end of the string> - <delimiter offset>), otherwise the start of the string is the <delimiter offset>.
 *
 *		Truth Table:
 *
 *		--------------------------------------------------------------------------------------------------------------------------------------------------
 *		|	getPriorData:	|	searchFromEnd: 	| Start of substring:								| Length of substring: 								|
 *		--------------------------------------------------------------------------------------------------------------------------------------------------
 *		|	true			|		N / A		|	Start of source	string							|	(<end of source string> - <delimiter offset>)	|
 *		--------------------------------------------------------------------------------------------------------------------------------------------------
 *		|	false			|		true		|	(<end of source string> - <delimiter offset>)	|	(<delimiter offset> - <delimiter length>)		|
 *		--------------------------------------------------------------------------------------------------------------------------------------------------
 *		|	false			|		false		|	Delimiter offset								|	(<delimiter offset> - <delimiter length>)		|
 *		--------------------------------------------------------------------------------------------------------------------------------------------------
 *
 *		@pram getPriorData, Chooses the bytes that came before the delimiter or after the delimiter for generating the sub-string from.
 *				If getPriorData is non-zero then the sub-string will contain the bytes before the delimiter, otherwise the sub-string will
 *				contain the bytes after the delimiter.
 *
 *		Returns COMMON_ERROR_SUCCESS if the delimiter was found and a sub-string was created.
 *		Returns COMMON_ERROR_RANGE_ERROR if the delimiter string was not found in the source string.
 *		Returns COMMON_ERROR_END_OF_DATA if the delimiter string was found at the end of source string
 *				with no data remaining to create the sub-string with. (subStr and subStrLength will NOT be altered in this case.)
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if a given argument is invalid.
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *		Otherwise returns the appropriate error code.
 *
 *		No alteration clause:
 *		In case of error, this function will not alter any given argument.
 *		(For the purposes of this no-alteration clause, the error codes COMMON_ERROR_RANGE_ERROR and COMMON_ERROR_END_OF_DATA
 *		 are considered errors.)
 */
MSYS_DLL_EXPORT int DataProcess_Get_SubString_Using_Delimiter(const char * src, const size_t srcLength, const char * delim, const size_t delimLength,
																char ** subStr, size_t * subStrLength, const int searchFromEnd, const int getPriorData);

/*!
 *		int DataProcess_Get_SubString_Using_Offset(const char * src, const size_t srcLength, const size_t offset,
 *												char ** subStr, size_t * subStrLength, const int searchFromEnd, const int getPriorData)
 *
 *		Takes the given source data string and offset and generates a substring from it. The generated sub-string should be freed using
 *		DataProcess_Deallocate_CString() when it is no longer needed.
 *
 *		Note: The generated substring is not NULL terminated. This is to allow the function to be used with unformatted data.
 *
 *		The substring is generated based on the given offset, searchFromEnd, and getPriorData arguments using the following truth table:
 *
 *		---------------------------------------------------------------------------------------------------------
 *		|	searchFromEnd:	|	getPriorData:	|	substring contents:	(Starting and ending offset ranges.)	|
 *		---------------------------------------------------------------------------------------------------------
 *		|	FALSE			|	FALSE			|	offset <--> end of string									|
 *		|	TRUE			|	FALSE			|	(end of string - offset) <--> end of string					|
 *		|	FALSE			|	TRUE			|	start of string <--> offset									|
 *		|	TRUE			|	TRUE			|	start of string <--> (end of string - offset)				|
 *		---------------------------------------------------------------------------------------------------------
 *
 *		Note:	searchFromEnd only controls the offset's point of origin. (I.e. which end of the given
 *				string the offset is based at.) searchFromEnd does NOT control what substring is selected
 *				based on the given offset; the selection is made based on getPriorData.
 *
 *		@pram src (const char *), the source string that the substring is generated from.
 *
 *		@pram srcLength (const size_t), the length of the source string. (Function may fail if given length is invalid / incorrect.)
 *
 *		@pram offset (const size_t), the starting offset within the source string to start copying data from.
 *
 *		@pram subStr (char **), a pointer that points to the pointer for the generated sub-string. WARNING: The pointer value will be overwritten
 *		if this call returns COMMON_ERROR_SUCCESS. This pointer should be released by calling DataProcess_Deallocate_CString().
 *
 *		@pram subStrLength (size_t *), a pointer to a size_t value that contains the length of the generated substring.
 *
 *		@pram searchFromEnd (integer treated as boolean), Which end of the given source string the given offset is is based at.
 *		(Start of given string = 0, end of given string = any non-zero value.)
 *
 *		@pram getPriorData (integer treated as boolean), Whether or not to use the segment of data that comes before the given offset as the
 *		generated substring. (False = zero, True = any non-zero value.)
 *
 *		Returns COMMON_ERROR_SUCCESS if successfull. In this case the values of subStr and subStrLength will change to contain a pointer to the generated
 *		substring and the length of the generated substring respectively.
 *
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is NULL, the length of the source string is 0, the given offset is less than zero or
 *		greater than or equal to the length of the string.
 *
 *		Returns COMMON_ERROR_MEMORY_ERROR if memory allocation for the substring fails.
 *
 *		Returns COMMON_ERROR_END_OF_DATA if the given arguments would generate a substring that contains no data.
 *		(I.e. The generated substring's length would be zero.)
 *
 *		Returns COMMON_ERROR_RANGE_ERROR if an internal calculation fails.
 *
 *		Otherwise returns the approperite error code.
 *
 *		No alteration clause:
 *		In case of error, this function will not alter any given argument.
 *		(For the purposes of this no-alteration clause, the error codes COMMON_ERROR_RANGE_ERROR and COMMON_ERROR_END_OF_DATA
 *		 are considered errors.)
 */
MSYS_DLL_EXPORT int DataProcess_Get_SubString_Using_Offset(const char * src, const size_t srcLength, const size_t offset,
															char ** subStr, size_t * subStrLength, const int searchFromEnd, const int getPriorData);
#ifdef __cplusplus
}	/* End of extern "C". */
#endif	/* __cplusplus */

/* Only define the below with a CPP compiler. */
#ifdef __cplusplus

/* Internal includes. */
#include "DataProcess_Endianness_Check.h"

/* External includes. */
#include <vector>

/* Define DataProcess namespace. */
namespace DataProcess{

class Data_Object{
    private:
        MSYS_DataObject_T * obj;	/* The actual C object. */

    public:
        MSYS_DLL_EXPORT Data_Object();

        MSYS_DLL_EXPORT ~Data_Object()
        {
            if (obj != NULL)
            {
				MSYS_Destroy_DataObject(&(this->obj));
            }
        }
        MSYS_DLL_EXPORT Data_Object(const Data_Object & source);
        MSYS_DLL_EXPORT Data_Object(const std::string & source);
        MSYS_DLL_EXPORT Data_Object(const char * source, size_t str_length);
        MSYS_DLL_EXPORT Data_Object(const char & source);
        MSYS_DLL_EXPORT Data_Object & operator= (const Data_Object &source);
        MSYS_DLL_EXPORT Data_Object & operator= (const std::string &source);
        MSYS_DLL_EXPORT Data_Object & operator= (const char &source);
        MSYS_DLL_EXPORT Data_Object & operator+= (const char &source);
        MSYS_DLL_EXPORT Data_Object & operator+= (const std::string & source);
        MSYS_DLL_EXPORT Data_Object & operator+= (const Data_Object & source);
        MSYS_DLL_EXPORT char * substr(size_t offset, size_t endpoint) const;

        /*!
            int DataProcess::Data_Object::Buffer_Copy(const DataProcess::Data_Object & source, size_t copy_offset, size_t copy_length)

            This function is designed to copy data from one data_object, to another without performing a memory reallocation.

            By default this function assumes to try and copy all data in the source data_object.

            Returns 0 on success.
            Returns -1 if the destionation buffer ran out of space before all of the requested data was copied.
            Returns -3 if the function reaches a default return.
            Returns -5 if the one or more of the following is true:
                        The source buffer has nothing in it.
                        The source buffer's data length is less than the requested amount of data to be copied.
                        The source buffer's data length is less than the requested offset.
                        The source buffer's data length is less than the requested offset plus the requested length.
            Returns -9 on a memory error, (Note You may need to re check the buffer to make sure that the data_object was not reallocated.)
        */
        MSYS_DLL_EXPORT int Buffer_Copy(const DataProcess::Data_Object & source, size_t copy_offset = 0, size_t copy_length = 0);

        /*!
                const char * DataProcess::Data_Object::get_Pointer() const

                This function returns a constant pointer to the Data_Object's data pointer.

                If the Data_Object has no allocated memory, capacity equals zero (0), this function returns NULL.
        */
        MSYS_DLL_EXPORT const char * get_Pointer() const;

        /*!
                char * DataProcess::Data_Object::get_Data_Copy() const

                This function creates a copy of the data in the Data_Object and then returns a non-const pointer to that copy.

                Note: The copy that is created will not be freed after the Data_Object goes out of scope. (I.e is destroyed.)
                The caller must free the copy's memory using DataProcess::Data_Object::destroy_Data_Copy().

				Note: The resulting copy (if the function succeeds) will have a memory buffer length identical to the value
				returned by Data_Object::size() at the time this function was called.

                If this function fails to allocate memory, it will return NULL.
        */
        MSYS_DLL_EXPORT char * get_Data_Copy() const;

		/*!
				void DataProcess::Data_Object::destroy_Data_Copy(char ** obj) const

				Destroys (Deallocates) the copied object data, created by
				DataProcess::Data_Object::get_Data_Copy().

				WARNING: DO NOT ATTEMPT to deallocate DataProcess::Data_Object objects with this function.
				Use ~DataProcess::Data_Object() instead. Failure to do so, will result in
				UNDEFINED BEHAVIOR.

				This function has no return.
		 */
		MSYS_DLL_EXPORT void destroy_Data_Copy(char ** obj) const;

        MSYS_DLL_EXPORT size_t get_length() const;

        /*!
                size_t DataProcess::Data_Object::get_Capacity() const

                This function returns the capacity (total allocated memory)
                of the Data_Object.

                If no memory has been allocated this function returns zero (0).
        */
        MSYS_DLL_EXPORT size_t get_Capacity() const;

        /*!
                size_t DataProcess::Data_Object::size() const

                This function returns the current length (size) of actual data in
                the Data_Object.

                If no data is present zero (0) is returned.
        */
        MSYS_DLL_EXPORT size_t size() const;

		/*!
				int DataProcess::Data_Object::Shallow_Copy(const DataProcess::Data_Object & source)

				Makes the object that this function is called on a shallow copy of the given DataProcess::Data_Object.
				(Variable only copy.)

				Note: If this function succeeds, then ANY changes made to either the source object or the object
				that this function is called on will desync the other object. Care should be taken to not
				cause a desync between a shallow copied object and it's source object. Failure to prevent
				a desync, will result in UNDEFINED BEHAVIOR.

				Returns COMMON_ERROR_SUCCESS if the shallow copy is successful.
		 */
		MSYS_DLL_EXPORT int Shallow_Copy(const DataProcess::Data_Object & source);

		/*!
			void DataProcess::Data_Object::set(const char * source, const size_t & source_length)

			This function clears the Data_Object's buffer, and then copies
			source_length amount of data from source to the Data_Object's buffer.

			If this function encounters an error, (i.e. NULL source, bad source_length,
			an exception, etc.) then this function will silently fail and the Data_Object
			will be cleared.
		*/
		MSYS_DLL_EXPORT void set(const char * source, const size_t & source_length);

        /*!
                void DataProcess::Data_Object::clear()

                This function deallocates (frees) the Data_Object's memory, and resets
                length and capacity to zero (0).
        */
        MSYS_DLL_EXPORT void clear();

        /*!
                void DataProcess::Data_Object::reset()

                This function erases all data in the Data_Object, (Sets all bytes to NULL)
                and sets length to zero (0). The capacity is left unchanged.
        */
        MSYS_DLL_EXPORT void reset();

        /*!
                void DataProcess::Data_Object::reserve(size_t new_length)

                This function reserves memory (preallocates) for a Data_Object.

                Note: This function expects that the given length is the total amount
                of memory to allocate for the Data_Object, not the amount added.

                i.e if you have allocated 6 bytes, and then call this function with the amount
                of 7 bytes you will get a total size of 7 bytes not 13 bytes.

                This function tries to be non destructive. If a smaller length than what is
                already allocated is requested, this function will silently fail.

                This function can fail to allocate memory, if this occurs no modifications will
                be made to the Data_Object.

                This function can also fail to copy data to the new memory buffer, in this case
                the Data_Object will contain the data that was successfully copied prior to the failure.
                All other data will be lost.
        */
        MSYS_DLL_EXPORT void reserve(size_t new_length);
        MSYS_DLL_EXPORT bool Compare(const Data_Object &source) const;
        MSYS_DLL_EXPORT bool NCompare(const Data_Object &source) const;

        /*!
                bool DataProcess::Data_Object::Data_Compare(const DataProcess::Data_Object & source) const

                This function checks the data section of the Data_Object against another Data_Object to
                see if they equal each other.

                Note: Unlike DataProcess::Data_Object::Compare(), this function does not check capacity
                only length and actual data is checked.

                Returns true if both the length and data of the two Data_Objects are equal.
                Returns false if etheir the length or data does not match.
        */
        MSYS_DLL_EXPORT bool Data_Compare(const DataProcess::Data_Object & source) const;

        /*!
                bool DataProcess::Data_Object::Data_NCompare(const DataProcess::Data_Object & source) const

                This function checks the data section of the Data_Object against another Data_Object to
                see if they are not equal each other.

                Note: Unlike DataProcess::Data_Object::NCompare(), this function does not check capacity
                only length and actual data is checked.

                Returns false if both the length and data of the two Data_Objects are equal.
                Returns true if etheir the length or data does not match.
        */
        MSYS_DLL_EXPORT bool Data_NCompare(const DataProcess::Data_Object & source) const;

        /*!
                size_t DataProcess::Data_Object::insert(size_t offset, const char source)

                This function inserts a single char into the Data_Object at the given offset.

                Note: This function will reallocate the buffer if needed.

                Returns amount of inserted data if successfull. (In this case one (1).)
                Returns zero (0) if an error occurs or if no data was copied.
        */
        MSYS_DLL_EXPORT size_t insert(size_t offset, const char source);

        /*!
                size_t DataProcess::Data_Object::insert(size_t offset, const std::string & source)

                This function inserts a string into the Data_Object at the given offset.

                Note: This function will reallocate the buffer if needed.

                This function will copy all of the contents of the given string.

                Returns amount of inserted data if successfull.
                Returns zero (0) if an error occurs or if no data was copied.
        */
        MSYS_DLL_EXPORT size_t insert(size_t offset, const std::string & source);

        /*!
                size_t DataProcess::Data_Object::insert(size_t offset, const Data_Object & source)

                This function inserts a DataProcess::Data_Object's contents into the Data_Object at the given offset.

                Note: This function will reallocate the buffer if needed.

                This function will copy all of the contents of the given Data_Object.

                Returns amount of inserted data if successfull.
                Returns zero (0) if an error occurs or if no data was copied.
        */
        MSYS_DLL_EXPORT size_t insert(size_t offset, const Data_Object & source);
};

/*!
	int DataProcess::CopyCStringToStdString(const char * source, const size_t & sourceLength, std::string & dest)

	This function takes a given C style string and copies it to a std::string by copying the amount of bytes given by
	sourceLength.
	The resulting string if this function succeeds will be the same length as the given sourceLength.

	NOTE: This function will NOT deallocate a pre-existing string, but it WILL OVERWRITE IT.
	(So if you need to use or deallocate it later, make sure to copy the string before calling
	 this function.)

	WARNING: This function will copy the given amount of bytes (as defined by sourceLength) from the given source pointer.
	If the source string's buffer is NOT at least sourceLength bytes long, then the result of this function is UNDEFINED.
	(Depending on the system, a memory access violation may occur, or the function may copy data from beyond the end of
	 the source string's buffer, but neither of these behaviours can be guaranteed by this function. It is up to the caller
	 to ensure that the given amount of bytes to copy is within the given source string's allocated memory buffer.)

	Returns COMMON_ERROR_SUCCESS if the function succeeds. (Result string will be stored in dest.)
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given source string pointer is NULL, or the given length is less than or equal to zero.

	No alteration clause:
		In case of error, this function will not alter any given argument.
*/
MSYS_DLL_EXPORT int CopyCStringToStdString(const char * source, const size_t & sourceLength, std::string & dest);

/*!
	int DataProcess::CopyStdStringToCString(const std::string & source, char ** dest)

	This function takes a given std::string and copies it to a C style string.
	The resulting string if this function succeeds will be the same length as the source string.

	NOTE: This function will NOT deallocate a pre-existing pointer, but it WILL OVERWRITE IT.
	(So if you need to use or deallocate it later, make sure to copy the pointer before calling
	 this function.)

	When the result string of this function is no longer needed, it should be deallocated by calling
	DataProcess_Deallocate_CString().

	Returns COMMON_ERROR_SUCCESS if the function succeeds. (Result string will be pointed to by dest.)
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given source string is empty, or it's data could not be accessed.
	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.

	No alteration clause:
		In case of error, this function will not alter any given argument.
*/
MSYS_DLL_EXPORT int CopyStdStringToCString(const std::string & source, char ** dest);

/*!
	size_t DataProcess::Trivial_Random_Number_Generator(const size_t & min_value, const size_t & max_value, const bool & reset_rand)

	A wrapper around the DataProcess_Trivial_Random_Number_Generator() C function. (For compatibility.)

	See DataProcess_Trivial_Random_Number_Generator()'s description for documentation.

	Note: Default values for arguments are: min_value 0, max_value 255, reset_rand false.
*/
MSYS_DLL_EXPORT size_t Trivial_Random_Number_Generator(const size_t & min_value = 0, const size_t & max_value = 255, const bool & reset_rand = false);

/*!
        short DataProcess::IncrementingSort(std::vector<std::string> & sort)

        This function sorts strings by incrementing value.
        ( I.e The entire string is parsed, and the strings with
         characters that are larger in value than the previous string
         are moved up the list. I.e Have their positions swapped
         in the list.)

         Returns 0 on success.
         Returns -9 if an exception is thrown.
*/
MSYS_DLL_EXPORT short IncrementingSort(std::vector<std::string> & sort);

/*!
        short DataProcess::DecrementingSort(std::vector<std::string> & sort)

        This function sorts strings by decrementing value.
        ( I.e The entire string is parsed, and the strings with
         characters that are larger in value than the previous string
         are moved down the list. I.e Have their positions swapped
         in the list.)

         Returns 0 on success.
         Returns -9 if an exception is thrown.
*/
MSYS_DLL_EXPORT short DecrementingSort(std::vector<std::string> & sort);

/*!
    bool DataProcess::CheckForEOF(std::fstream & source)

    Checks the given file stream for eof (End of File) status and returns the result.

    Note: This function ignores the EOF (End of File) flag on the fstream. Instead it checks by checking the current get pointer's position
    against the end of the file.

    Returns true if the fstream is at EOF. (End of File)
    Returns false otherwise. (Note: This function will return false if the fstream has failed. (i.e source.fail() == true).)
*/
MSYS_DLL_EXPORT bool CheckForEOF(std::fstream & source);

/*!
    GenerateUID(long int length)

    Generates an pseduo-random alphanumeric string of given length. Default length is 25 charaters.
    WARNING: The longer the length the longer it will take to create the UID.

    Returns string of given length.
*/
MSYS_DLL_EXPORT std::string GenerateUID(long int length = 25);

/*!
        getnumberFromString(std::string source, std::string varName, std::string limiter , bool isdecimal, Panic::Panic_ERROR & error)

        Gets number(s) from a string.

        Returns number if successful.
        Otherwise returns 0.
*/
MSYS_DLL_EXPORT double getnumberFromString(std::string source, std::string varName, std::string limiter , bool isdecimal, Panic::Panic_ERROR & error);

/*!
        getIntFromInput()

        Gets an Integer from console, clears the Newline from the buffer, and then
        Returns the integer.

        Returns integer from console if successful,
        Otherwise returns 0.
*/
MSYS_DLL_EXPORT int getIntFromInput();

/*!
        bool DataProcess::yesNoConsolePrompt()

        Prompts the user via the console to answer a YES or NO question.

        Returns true if the user said YES.
        Otherwise returns false. (Defaults to NO.)
*/
MSYS_DLL_EXPORT bool yesNoConsolePrompt();

MSYS_DLL_EXPORT bool getboolFromstring(std::string source, std::string varName, char delimiter, Panic::Panic_ERROR & error);
// Reads input string for a true or false statement then returns the result.
// if no varible statement is found it returns the following string "ERROR: NO VAR."

// Takes a pointer to an integer and converts the integer back to a binary number.
// Return value is the binary equilvent to the given integer. Which is wrote back into the pointer.
MSYS_DLL_EXPORT long ConvertToBinary(int input);

/*!
        getnumberFromString(const char * string, size_t string_size)

        Extracts a number from the given string.

        Will skip any data before an actual number is found. After a number is found it will be extracted
        along with any number following it until etheir a non number is found (including end of stream), or
        the number of extracted numbers = sizeof(long int).

        Note: Will extract a negative number if number is proceeded by a '-'.

        Returns the extracted number on success.
        Returns zero (0) otherwise.
*/
MSYS_DLL_EXPORT long int getnumberFromString(const char * string, size_t string_size);

/*!
        size_t DataProcess::getSize_TFromString(const char * string, size_t string_size)

        Extracts an unsigned int from the given string.

        Will skip any data before an actual number is found. After a number is found it will be extracted
        along with any number following it until etheir a non number is found (including end of stream), or
        the number of extracted numbers = sizeof(long int).

        Note: Will extract a negative number if number is proceeded by a '-'.

        Returns the extracted number on success.
        Returns zero (0) otherwise.
*/
MSYS_DLL_EXPORT size_t getSize_TFromString(const char * string, size_t string_size);

/*!
        getnumberFromString(char input)

        Converts a single character to the number it repesents. Much like atoi().

        If the character given is not a number, then zero (0) is returned.
        Otherwise the number is returned.
*/
MSYS_DLL_EXPORT short getnumberFromString(char input);

/*!
        dumpDataToConsole(const char * data, size_t length, size_t offset, bool print_bad_chars, bool memory_format)

        Writes length amount of data in given pointer starting at offset to the console (std out).
        If data can't be printed on the console (i.e non char data) then one of the
        following takes place.

        If print_bad_chars is false (Default) then the char is
        replaced with a period (.)

        If print_bad_chars is true then the char code (char converted to int) is
        printed.

        memory_format is a method to print out the data with each character
        clearly numbered as an offset from the addess given. (This is off by
                                                              default.)
*/
MSYS_DLL_EXPORT void dumpDataToConsole(const char * data, size_t length, size_t offset = 0, bool print_bad_chars = false, bool memory_format = false);

/*!
        DataProcess::Data_Object DataProcess::getStringFromSizeT(const size_t & number)

        Takes given size_t and outputs the equilvent string in a DataProcess::Data_Object.

        Returns: DataProcess::Data_Object with string equilvent to number if successful.
        Returns: empty DataProcess::Data_Object if this function fails.
*/
MSYS_DLL_EXPORT DataProcess::Data_Object getStringFromSizeT(const size_t & number);

/*!
        std::string DataProcess::getStdStringFromSizeT(const size_t & number)

        Takes given size_t and outputs the equilvent string in a std::string.

        Returns: std::string with string equilvent to number if successful.
        Returns: empty std::string if this function fails.
*/
MSYS_DLL_EXPORT std::string getStdStringFromSizeT(const size_t & number);

/*!
        DataProcess::Data_Object DataProcess::getStringFromInt(long int number)

        Takes the given integer, and outputs the equilvent string in a DataProcess::Data_Object.

        Note: This function operates on base-10 only.

        Returns: DataProcess::Data_Object with string equilvent to number if successful.
        Returns: empty DataProcess::Data_Object if this function fails.
*/
MSYS_DLL_EXPORT DataProcess::Data_Object getStringFromInt(long int number);

/*!
 * 	template<typename T>
 * 	void DataProcess::removeFromVector(std::vector<T> & container, const size_t & offset)
 *
 * 	This is a template function that takes the given vector and offset and erases the
 * 	element at that offset.
 *
 * 	If the given offset is outside of the vector, (I.e. the offset lacks that many elements),
 * 	then this function will silently fail.
 *
 * 	This function uses std::advance(), to avoid issues in the event a non-random-access iterator
 * 	is used by the given container.
 *
 * 	(Why the std::vector template does not include the ability to call erase() with an offset
 * 	I have no idea.....)
 *
 * 	It has no return.
 */
template<typename T>
void removeFromVector(std::vector<T> & container, const size_t & offset)
{
	// Init iter.
	typename std::vector<T>::iterator iter = container.begin();

	// Check and make sure that the offset is valid.
	if (offset < container.size())
	{
		// Move to correct position.
		std::advance(iter, offset);

		// Erase the element.
		container.erase(iter);
	}

	// Exit function.
	return;
}

/*!
        short DataProcess::RegularExpressionParser(const std::string & expression, const std::string & input, Panic::Panic_ERROR * error)

        This function takes a input string and an expression string, compares them, then returns the result.
        This is the std::string version.

        This function can also be debugged by giving an error handler with the error level set to at least ERROR_VERBOSE or higher. By default no error handler is expected.

        Note: The documatation for the expression rules and syntax is in the docs subdirectory of the top level source directory. (Look for Regular_Expression_Rules.txt)

        Returns 0 if the expression matches the input string.
        Returns -2 if the expression does NOT match the input string.
        Returns -5 on an argument error. (Lack of string(s), or a syntax error in the expression string.)
        Returns -9 on control loop out of bounds, or a memory error.
*/
MSYS_DLL_EXPORT short RegularExpressionParser(const std::string & expression, const std::string & input, Panic::Panic_ERROR * error = NULL);

/*!
        short DataProcess::RegularExpressionParser(const DataProcess::Data_Object & expression, const DataProcess::Data_Object & input, Panic::Panic_ERROR * error)

        This function takes a input string and an expression string, compares them, then returns the result.
        This is the DataProcess::Data_Object version.

        This function can also be debugged by giving an error handler with the error level set to at least ERROR_VERBOSE or higher. By default no error handler is expected.

        Note: The documatation for the expression rules and syntax is in the docs subdirectory of the top level source directory. (Look for Regular_Expression_Rules.txt)

        Returns 0 if the expression matches the input string.
        Returns -2 if the expression does NOT match the input string.
        Returns -5 on an argument error. (Lack of string(s), or a syntax error in the expression string.)
        Returns -9 on control loop out of bounds, or a memory error.
*/
MSYS_DLL_EXPORT short RegularExpressionParser(const DataProcess::Data_Object & expression, const DataProcess::Data_Object & input, Panic::Panic_ERROR * error = NULL);
}

#endif	/* __cplusplus */

#endif	/* DATAPROCESS_H */

/* End of DataProcess.h */
