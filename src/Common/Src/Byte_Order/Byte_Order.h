/*!
    Multiverse Engine Project 03/6/2015 Common Byte_Order.h

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
#ifndef MSYS_BYTE_ORDER_H
#define MSYS_BYTE_ORDER_H

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Define Endianness Result Values. */
#define MSYS_BIG_ENDIAN 0
#define MSYS_LITTLE_ENDIAN 1
#define MSYS_UNKNOWN_ENDIANNESS 2

/* Pull in DLL_PORT.h */
#include "../../../DLL_PORT.h"	/* Defines MSYS_DLL_EXPORT, and MSYS_DLL_IMPORT_TEMPLATE. */

/* Internal headers. */
#include "../Error_Handler/Common_Error_Handler_Error_Codes.h"	/* Defines the error codes. */
#include "Byte_Order_Integers.h"
#include "Byte_Order_Floating_Points.h"

/* Define bool. */
#if _MSC_FULL_VER && _MSC_FULL_VER < 180031101
#include "../stdbool.h"	/* Older versions of Visual C don't support the C99 stdbool header. So we have to fake one. */
#else
#include <stdbool.h>
#endif

/* External headers. */
#include <stddef.h>	/* Defines NULL. */
#include <stdlib.h>	/* Defines malloc(), free(). */
#include <string.h>	/* Defines memset(), memcpy(). */

/*!
 *		int Byte_Order_Bit_Comparison(const char * byte, const char bitMask, const char bitValues)
 *
 *		Compares the given byte's bits to the given bitValues using bitMask to define what bits to compare.
 *
 *		I.e. This function compares bits to see if they are equal, using the bitMask to determine what
 *		bits to actually compare.
 *
 *		Example: If bitMask is 11000000, then only the first two bits are checked. So to make a truth table:
 *
 *		byte:		bitMask:	bitValues:		Result:
 *		11000000	11000000	11000000		TRUE	(The checked values in byte and bitValues are identical.)
 *		10000000	11000000	10000000		TRUE	(The checked first and second bits are identical.)
 *		01110010	00110010	10110010		TRUE	(The checked 3rd, 4th, and 7th bits are identical.)
 *		11000100	11000000	11000000		TRUE	(Extra bit in byte is not checked.)
 *		11000000	11000000	11000100		TRUE	(Extra bit in bitValues is not checked.)
 *		01000000	11000000	11000000		FALSE	(byte does not match bitValues.)
 *		11000000	11000000	10000000		FALSE	(bitValues does not match byte.)
 *		00000000	00000000	00000000		FALSE	(No bits are defined to check.)
 *		00000000	00110010	00000000		TRUE	(Third, forth, and 7th bits are identical.
 *														 (Hardcoded zero check, for consistancy with other results.))
 *		00000000	11111111	00000000		TRUE	(Checking all bits, byte and bitValues are both zero.
 *														 (Hardcoded zero check, for consistancy with other results.))
 *
 *		A note about checking for zero bits:
 *		For consistancy with the other results, in the event an all zero byte and bitValues is given
 *		to this function, a hard coded check is inserted to return COMMON_ERROR_COMPARISON_PASSED if
 *		the given bitMask is not equal to zero. Otherwise it returns COMMON_ERROR_COMPARISON_FAILED.
 *		This contradicts what would be expected from a binary AND operation and callers of this
 *		function should therefore be aware of it and check for this result.
 *		(Normally, a binary AND operation on an all zero set of operands would give a FALSE result.
 *		 The best antidote I can give to deal with this function's inconsistancy is:
 *		 It checks the given bits to see if they match, if given to a non-programmer, what would they
 *		 think the result should be?
 *		 Answer: (0 == 0) is TRUE, so the function should return TRUE.")
 *
 *		Returns COMMON_ERROR_COMPARISON_PASSED if the checked bits match.
 *		Returns COMMON_ERROR_COMPARISON_FAILED if the checked bits do NOT match.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer to char is invalid.
 *		Otherwise returns the approperite error code.
 */
MSYS_DLL_EXPORT int Byte_Order_Bit_Comparison(const char * byte, const char bitMask, const char bitValues);

/*!
 *		int Common_Byte_Swap(char * data, const size_t dataLength)
 *
 *		Swaps the given bytes by swapping each byte
 *		with it's complement on the other end of the
 *		byte string.
 *
 *		I.e. Each byte from x distance from the start of the string is swapped
 *		with the byte x distance from the end of the string.
 *
 *		Note: This function expects that the amount of data given to it
 *		is a multiple of 2. Also this function will alter the given
 *		data in-place. (I.e. If an error occurs, the data WILL be altered.)
 *
 *		Returns COMMON_ERROR_SUCCESS if swapping was successful.
 *
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is
 *		NULL, or if the data length is not a multiple of 2.
 *
 *		Otherwise returns the appropriate error code.
 */
MSYS_DLL_EXPORT int Common_Byte_Swap(char * data, const size_t dataLength);

/*!
 * 		int Common_Print_Bytes_To_CString(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const size_t base,
 * 										const size_t width, const char fillValue, const bool spaceBetweenBytes)
 *
 * 		Converts a given byte string to a printable (NULL-terminated) and human-readable string in the given base.
 *
 * 		@pram data: the byte string to convert.
 * 		@pram dataLength: the length of the byte string.
 * 		@pram retStr: a double pointer that will point to the converted string.
 * 		@pram retStrSize: the size of the generated string.
 * 		@pram base: the numerical base to convert each byte to.
 *
 * 		@pram width: the minimal number of values to print for each byte. (Note the minimal keyword. The value will not be truncated if it
 * 		requires more than width characters to represent it. This is solely to make smaller values take up more space for more uniform value
 * 		representation.)
 *
 * 		@pram fillValue: the value printed in the converted string to take up the extra space, when a byte's value representation is smaller
 * 		than the given width. (E.x. the byte value is 0, width is 3, and fillValue is '.': "..0" would be the result.)
 *
 * 		@pram spaceBetweenBytes: Whether or not to insert a space character after each of the converted byte values. (Readability.)
 *
 * 		WARNING: If retStr is non-NULL when this function is called, and this function returns COMMON_ERROR_SUCCESS, then the pointer will
 * 		be overwritten without being deallocated. If you need that pointer to deallocate it later, you should copy it elsewhere before calling
 * 		this function.
 *
 * 		Note: To deallocate the returned string from this function, pass the returned string to Common_Deallocate_Print_Bytes_CString().
 *
 * 		Returns COMMON_ERROR_SUCCESS if the conversion is successful.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL, or if the given base is not a value between 2 and 16.
 * 		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation fails.
 *
 * 		In case of error, (the returned error code is not COMMON_ERROR_SUCCESS, then the given arguments will NOT be altered by this function.
 */
MSYS_DLL_EXPORT int Common_Print_Bytes_To_CString(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const size_t base, const size_t width, const char fillValue, const bool spaceBetweenBytes);

/*!
 * 		void Common_Deallocate_Print_Bytes_CString(char ** str)
 *
 * 		Deallocates the given c-string and sets the given pointer to char to NULL.
 *
 * 		Note: This function is a destructor function for strings made by Common_Print_Bytes_To_CString() and
 * 		should ONLY be used for that purpose. The behaviour for using this function to deallocate other allocations is undefined.
 *
 * 		This function has no return. If a given pointer is NULL, this function will silently fail.
 */
MSYS_DLL_EXPORT void Common_Deallocate_Print_Bytes_CString(char ** str);

/*!
 * 		int Common_Print_Bytes_In_Hex(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes)
 *
 * 		Wrapper function around Common_Print_Bytes_To_CString() for converting a byte string to a human-readable hexadecimal string.
 * 		Example output: ("001FAC" if spacing is disabled, "00 1F AC" if spacing is enabled.)
 *
 * 		Note: This function is to make calls shorter, if you want more control over the output, call Common_Print_Bytes_To_CString() directly.
 *
 * 		All arguments and return values are identical to their Common_Print_Bytes_To_CString() counterparts. See Common_Print_Bytes_To_CString()
 * 		for their descriptions.
 */
MSYS_DLL_EXPORT int Common_Print_Bytes_In_Hex(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes);

/*!
 * 		int Common_Print_Bytes_In_Binary(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize,
 * 										const bool spaceBetweenBytes)
 *
 * 		Wrapper function around Common_Print_Bytes_To_CString() for converting a byte string to a human-readable binary string.
 * 		Example output: ("00000101000001010000010100000101" if spacing is disabled, "00000101 00000101 00000101 00000101" if spacing is enabled.)
 *
 * 		Note: This function is to make calls shorter, if you want more control over the output, call Common_Print_Bytes_To_CString() directly.
 *
 * 		All arguments and return values are identical to their Common_Print_Bytes_To_CString() counterparts. See Common_Print_Bytes_To_CString()
 * 		for their descriptions.
 */
MSYS_DLL_EXPORT int Common_Print_Bytes_In_Binary(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes);

/*!
* 		int Common_Print_Bytes_In_Decimal(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize,
* 										const bool spaceBetweenBytes)
*
* 		Wrapper function around Common_Print_Bytes_To_CString() for converting a byte string to a human-readable decimal string.
* 		Example output: ("10012" if spacing is disabled, "10 0 12" if spacing is enabled.)
*
* 		Note: This function is to make calls shorter, if you want more control over the output, call Common_Print_Bytes_To_CString() directly.
*
* 		All arguments and return values are identical to their Common_Print_Bytes_To_CString() counterparts. See Common_Print_Bytes_To_CString()
* 		for their descriptions.
*/
MSYS_DLL_EXPORT int Common_Print_Bytes_In_Decimal(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes);

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* MSYS_BYTE_ORDER_H */

/* End of Byte_Order.h */
