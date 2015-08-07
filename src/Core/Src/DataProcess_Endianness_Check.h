/*!
    Multiverse Engine Project 11/7/2015 DataProcess DataProcess_Endianness_Check.h

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
#ifndef DATAPROCESS_ENDIANNESS_CHECK_H
#define DATAPROCESS_ENDIANNESS_CHECK_H

/* Define Endianness Result Values. */
#define MSYS_BIG_ENDIAN 0
#define MSYS_LITTLE_ENDIAN 1
#define MSYS_UNKNOWN_ENDIANNESS 2

/* Define namespace. */
namespace DataProcess {

/*!
 *		template<typename T>
 *		int DataProcess_Endianness_Check(T & a)
 *
 *		Template function which checks the host's endianness for the
 *		given argument's data type.
 *
 *		Note: The given argument is not altered or used by the function.
 *		It's only used to exploit the C++ template generator.
 *
 * 		The specializations for float and double are required as floating
 * 		point data types must be detected differently from integers.
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
template<typename T>
int DataProcess_Endianness_Check(const T & a);

template<>
int DataProcess_Endianness_Check<float>(const float & a);

template<>
int DataProcess_Endianness_Check<double>(const double & a);

}	/* namespace DataProcess */

#endif	/* DATAPROCESS_ENDIANNESS_CHECK_H */

/* End of DataProcess_Endianness_Check.h */
