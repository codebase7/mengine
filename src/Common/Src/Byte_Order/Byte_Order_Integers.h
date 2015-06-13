/*!
    Multiverse Engine Project 09/6/2015 Common Byte_Order_Integers.h

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
#ifndef MSYS_BYTE_ORDER_INTEGERS_H
#define MSYS_BYTE_ORDER_INTEGERS_H

/* Make sure we are not included directly. */
#ifndef MSYS_BYTE_ORDER_H
#error "You should not include __FILE__ directly, it is included automaticly by Byte_Order.h, remove this include. Aborting build."
#endif

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
 * 		int Common_Host_To_Big_Endian_UChar(unsigned char * uc)
 *
 * 		Converts a given unsigned CHAR value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_UChar(unsigned char * uc);

/*!
 * 		int Common_Big_Endian_To_Host_UChar(unsigned char * uc)
 *
 * 		Converts a given unsigned CHAR value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_UChar(unsigned char * uc);

/*!
 * 		int Common_Host_To_Big_Endian_Char(char * c)
 *
 * 		Converts a given CHAR value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Char(char * c);

/*!
 * 		int Common_Big_Endian_To_Host_Char(char * c)
 *
 * 		Converts a given CHAR value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Char(char * c);

/*!
 * 		int Common_Host_To_Big_Endian_UShort(unsigned short * us)
 *
 * 		Converts a given unsigned SHORT value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_UShort(unsigned short * us);

/*!
 * 		int Common_Big_Endian_To_Host_UShort(unsigned short * us)
 *
 * 		Converts a given unsigned SHORT value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_UShort(unsigned short * us);

/*!
 * 		int Common_Host_To_Big_Endian_Short(short * s)
 *
 * 		Converts a given SHORT value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Short(short * s);

/*!
 * 		int Common_Big_Endian_To_Host_Short(short * s)
 *
 * 		Converts a given SHORT value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Short(short * s);

/*!
 * 		int Common_Host_To_Big_Endian_UInt(unsigned int * ui)
 *
 * 		Converts a given unsigned INT value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_UInt(unsigned int * ui);

/*!
 * 		int Common_Big_Endian_To_Host_UInt(unsigned int * ui)
 *
 * 		Converts a given unsigned INT value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_UInt(unsigned int * ui);

/*!
 * 		int Common_Host_To_Big_Endian_Int(int * i)
 *
 * 		Converts a given INT value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Int(int * i);

/*!
 * 		int Common_Big_Endian_To_Host_Int(int * i)
 *
 * 		Converts a given INT value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Int(int * i);

/*!
 * 		int Common_Host_To_Big_Endian_ULong(unsigned long * ul)
 *
 * 		Converts a given unsigned LONG value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_ULong(unsigned long * ul);

/*!
 * 		int Common_Big_Endian_To_Host_ULong(unsigned long * ul)
 *
 * 		Converts a given unsigned LONG value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_ULong(unsigned long * ul);

/*!
 * 		int Common_Host_To_Big_Endian_Long(long * l)
 *
 * 		Converts a given LONG value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Long(long * l);

/*!
 * 		int Common_Big_Endian_To_Host_Long(long * l)
 *
 * 		Converts a given LONG value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Long(long * l);

/*!
 * 		int Common_Host_To_Big_Endian_ULong_Long(unsigned long long * ull)
 *
 * 		Converts a given unsigned LONG LONG value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_ULong_Long(unsigned long long * ull);

/*!
 * 		int Common_Big_Endian_To_Host_ULong_Long(unsigned long long * ull)
 *
 * 		Converts a given unsigned LONG LONG value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_ULong_Long(unsigned long long * ull);

/*!
 * 		int Common_Host_To_Big_Endian_Long_Long(long long * ull)
 *
 * 		Converts a given LONG LONG value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Long_Long(long long * ll);

/*!
 * 		int Common_Big_Endian_To_Host_Long_Long(long long * ll)
 *
 * 		Converts a given LONG LONG value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Long_Long(long long * ll);

/*!
 * 		int Common_Host_To_Big_Endian_Size_T(size_t * st)
 *
 * 		Converts a given SIZE_T value from the host's endianness
 * 		to Big Endian format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Size_T(size_t * st);

/*!
 * 		int Common_Big_Endian_To_Host_Size_T(size_t * st)
 *
 * 		Converts a given SIZE_T value from the Big Endian format
 * 		to the host's endianness format.
 *
 * 		Returns COMMON_ERROR_SUCCESS, if the conversion is successful,
 * 		(data will be converted after call returns),
 * 		or if the host is a Big Endian host. (In such case no data alteration 
 * 		is performed.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
 *
 *		Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given data type's 
 * 		byte ordering is unknown for the given host.
 *
 * 		In case of error, (returned error code is not COMMON_ERROR_SUCCESS),
 * 		all arguments will be left unaltered.
 */
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Size_T(size_t * st);

/*!
 * 		General Definitions for the Common_*_Endianness_Check() functions:
 *
 * 		The functions below all contain the same returns,
 * 		and purpose.
 */

/*!
 *		int Common_UCHAR_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a unsigned CHAR argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_UCHAR_Endianness_Check();

/*!
 *		int Common_CHAR_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a CHAR argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_CHAR_Endianness_Check();

/*!
 *		int Common_USHORT_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a unsigned SHORT argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_USHORT_Endianness_Check();

/*!
 *		int Common_SHORT_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a SHORT argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_SHORT_Endianness_Check();

/*!
 *		int Common_UINT_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a unsigned INT argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_UINT_Endianness_Check();

/*!
 *		int Common_INT_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a INT argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_INT_Endianness_Check();

/*!
 *		int Common_ULONG_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a unsigned LONG argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_ULONG_Endianness_Check();

/*!
 *		int Common_LONG_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a LONG argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_LONG_Endianness_Check();

/*!
 *		int Common_ULONG_LONG_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a unsigned LONG LONG argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_ULONG_LONG_Endianness_Check();

/*!
 *		int Common_LONG_LONG_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a LONG LONG argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_LONG_LONG_Endianness_Check();

/*!
 *		int Common_SIZE_T_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		UCHAR data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a SIZE_T argument.
 * 		This function is here for the purpose of making it easier
 * 		to use C code.
 *
 *		Returns MSYS_BIG_ENDIAN if the given data type is stored as big 
 *		endian on the host machine.
 *
 *		Returns MSYS_LITTLE_ENDIAN if the given data type stored as little
 *		endian on the host machine.
 *
 *		Returns MSYS_UNKNOWN_ENDIANNESS if the given data type's byte ordering
 *		is unknown for the given host.
 */
MSYS_DLL_EXPORT int Common_SIZE_T_Endianness_Check();

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* MSYS_BYTE_ORDER_INTEGERS_H */

/* End of Byte_Order_Integers.h */
