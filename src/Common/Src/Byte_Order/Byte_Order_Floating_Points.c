/*!
    Multiverse Engine Project 09/6/2015 Common Byte_Order_Floating_Points.c

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

/* Include main header. */
#include "Byte_Order.h"

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

int Common_Host_To_Big_Endian_Float(float * f)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_FLOAT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (f != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)f), sizeof (float));
						}
						else
						{
								/* Invalid arguments. */
								ret = COMMON_ERROR_INVALID_ARGUMENT;
						}
				}
				else
				{
						/* Host endianness is unknown. Cannot convert unknown endianness. */
						ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;
				}
		}
		else
		{
				/*
				 * 	This value should already be in the correct byte order,
				 * 	as the host is big endian.
				 */
				ret = COMMON_ERROR_SUCCESS;
		}

		/* Exit function. */
		return ret;
}

int Common_Big_Endian_To_Host_Float(float * f)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_FLOAT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (f != NULL)
						{
								/* 
								 *	Call Common_Byte_Swap(). 
								 *
								 * 	(We could call Common_Host_To_Big_Endian_Float() here, but
								 * 	 that would just repeat the calls above. Plus we may not be able
								 * 	 to do that on all systems.)
								 */
								ret = Common_Byte_Swap(((char*)f), sizeof (float));
						}
						else
						{
								/* Invalid arguments. */
								ret = COMMON_ERROR_INVALID_ARGUMENT;
						}
				}
				else
				{
						/* Host endianness is unknown. Cannot convert unknown endianness. */
						ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;
				}
		}
		else
		{
				/*
				 * 	This value should already be in the correct byte order,
				 * 	as the host is big endian.
				 */
				ret = COMMON_ERROR_SUCCESS;
		}

		/* Exit function. */
		return ret;
}

int Common_Host_To_Big_Endian_Double(double * d)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_DOUBLE_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (d != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)d), sizeof (double));
						}
						else
						{
								/* Invalid arguments. */
								ret = COMMON_ERROR_INVALID_ARGUMENT;
						}
				}
				else
				{
						/* Host endianness is unknown. Cannot convert unknown endianness. */
						ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;
				}
		}
		else
		{
				/*
				 * 	This value should already be in the correct byte order,
				 * 	as the host is big endian.
				 */
				ret = COMMON_ERROR_SUCCESS;
		}

		/* Exit function. */
		return ret;
}

int Common_Big_Endian_To_Host_Double(double * d)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_DOUBLE_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (d != NULL)
						{
								/* 
								 *	Call Common_Byte_Swap(). 
								 *
								 * 	(We could call Common_Host_To_Big_Endian_Double() here, but
								 * 	 that would just repeat the calls above. Plus we may not be able
								 * 	 to do that on all systems.)
								 */
								ret = Common_Byte_Swap(((char*)d), sizeof (double));
						}
						else
						{
								/* Invalid arguments. */
								ret = COMMON_ERROR_INVALID_ARGUMENT;
						}
				}
				else
				{
						/* Host endianness is unknown. Cannot convert unknown endianness. */
						ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;
				}
		}
		else
		{
				/*
				 * 	This value should already be in the correct byte order,
				 * 	as the host is big endian.
				 */
				ret = COMMON_ERROR_SUCCESS;
		}

		/* Exit function. */
		return ret;
}

int Common_FLOAT_Endianness_Check()
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

int Common_DOUBLE_Endianness_Check()
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

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */
