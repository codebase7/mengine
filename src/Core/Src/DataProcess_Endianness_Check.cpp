/*!
    Multiverse Engine Project 11/7/2015 DataProcess DataProcess_Endianness_Check.cpp

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

/* Include internal header. */
#include "DataProcess_Endianness_Check.h"

template<typename T>
int DataProcess_Endianness_Check(const T & a)
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		T t = 1;							/* Variable to check. */

		/* Cast t to a char string and see if the result is 1. */
		if (((char*)&t)[0])
		{
				/* The first byte is 1 so it's little endian. */
				ret = MSYS_LITTLE_ENDIAN;
		}
		else
		{
				/*
				 *	The first byte is 0 so, check and see if the last byte is non-zero.
				 *	If it is, then the host is big endian.
				 *
				 *	Otherwise the host is using something like middle-endian to store
				 *	the value, but we would need more checks to determine what exact
				 *	kind of endianness the host is using.
				 */
				if (((char*)&t)[((sizeof(t)) - 1)])
				{
						/* It's big endian. */
						ret = MSYS_BIG_ENDIAN;
				}
		}

		/* Return the result. */
		return ret;
}

template<>
int DataProcess_Endianness_Check<float>(const float & a)
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		float t = 1.0;						/* Variable to check. */

		/* Cast t to a char string and see if the first 2 values are 0x3F80. */
		if ((((char*)&t)[0] == 0x3F) && ((((char*)&t)[1] == 0x80)))
		{
				/* The first 2 bytes are 0x3F80 so it's big endian. */
				ret = MSYS_BIG_ENDIAN;
		}
		else
		{
				/*
				 *	The first check did not pass, so check and see if the last 2 bytes are 0x803F.
				 *	If they are, then the host is little endian.
				 *
				 *	Otherwise the host is using something like middle-endian to store
				 *	the value, but we would need more checks to determine what exact
				 *	kind of endianness the host is using.
				 */
				if ((((char*)&t)[(sizeof (float) - 1)] == 0x80) && ((((char*)&t)[(sizeof (float) - 2)] == 0x3F)))
				{
						/* It's little endian. */
						ret = MSYS_LITTLE_ENDIAN;
				}
		}

		/* Return the result. */
		return ret;
}

template<>
int DataProcess_Endianness_Check<double>(const double & a)
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		double t = 1.0;						/* Variable to check. */

		/* Cast t to a char string and see if the first 2 values are 0x3FF0. */
		if ((((char*)&t)[0] == 0x3F) && ((((char*)&t)[1] == 0xF0)))
		{
				/* The first 2 bytes are 0x3F80 so it's big endian. */
				ret = MSYS_BIG_ENDIAN;
		}
		else
		{
				/*
				 *	The first check did not pass, so check and see if the last 2 bytes are 0xF03F.
				 *	If they are, then the host is little endian.
				 *
				 *	Otherwise the host is using something like middle-endian to store
				 *	the value, but we would need more checks to determine what exact
				 *	kind of endianness the host is using.
				 */
				if ((((char*)&t)[(sizeof (double) - 1)] == 0xF0) && ((((char*)&t)[(sizeof (double) - 2)] == 0x3F)))
				{
						/* It's little endian. */
						ret = MSYS_LITTLE_ENDIAN;
				}
		}

		/* Return the result. */
		return ret;
}

/* End of DataProcess_Endianness_Check.cpp */
