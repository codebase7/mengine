/*!
    Multiverse Engine Project 09/6/2015 Common Byte_Order_Floating_Points.h

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
#ifndef MSYS_BYTE_ORDER_FLAOTING_POINTS_H
#define MSYS_BYTE_ORDER_FLAOTING_POINTS_H

/* Make sure we are not included directly. */
#ifndef MSYS_BYTE_ORDER_H
#error "You should not include __FILE__ directly, it is included automatically by Byte_Order.h, remove this include. Aborting build."
#endif

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
 * 		int Common_Host_To_Big_Endian_Float(float * f)
 *
 * 		Converts a given FLOAT value from the host's endianness
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
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Float(float * f);

/*!
 * 		int Common_Big_Endian_To_Host_Float(float * f)
 *
 * 		Converts a given FLOAT value from Big Endian format
 *		to the host's endianness format.
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
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Float(float * f);

/*!
 * 		int Common_Host_To_Big_Endian_DOUBLE(double * d)
 *
 * 		Converts a given DOUBLE value from the host's endianness
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
MSYS_DLL_EXPORT int Common_Host_To_Big_Endian_Double(double * d);

/*!
 * 		int Common_Big_Endian_To_Host_Double(double * d)
 *
 * 		Converts a given DOUBLE value from Big Endian format
 *		to the host's endianness format.
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
MSYS_DLL_EXPORT int Common_Big_Endian_To_Host_Double(double * d);

/*!
 * 		General Definitions for the Common_*_Endianness_Check() functions:
 *
 * 		The functions below all contain the same returns,
 * 		and purpose.
 */

/*!
 *		int Common_FLOAT_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		FLOAT data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a signed FLOAT argument.
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
MSYS_DLL_EXPORT int Common_FLOAT_Endianness_Check();

/*!
 *		int Common_DOUBLE_Endianness_Check()
 *
 *		Template function which checks the host's endianness for the
 *		DOUBLE data type.
 *
 *		Note: This function is the equivalent of calling
 *		DataProcess_Endianness_Check() with a signed DOUBLE argument.
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
MSYS_DLL_EXPORT int Common_DOUBLE_Endianness_Check();

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	/* MSYS_BYTE_ORDER_FLAOTING_POINTS_H */

/* End of Byte_Order_Floating_Points.h */
