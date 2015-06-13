/*!
    Multiverse Engine Project 09/6/2015 Common Byte_Order_Integers.c

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

/* Internal includes. */
#include "Byte_Order.h"

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

int Common_Host_To_Big_Endian_UChar(unsigned char * uc)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_UCHAR_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (uc != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)uc), sizeof (unsigned char));
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

int Common_Big_Endian_To_Host_UChar(unsigned char * uc)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_UCHAR_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (uc != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)uc), sizeof (unsigned char));
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

int Common_Host_To_Big_Endian_Char(char * c)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_CHAR_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (c != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)c), sizeof (char));
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

int Common_Big_Endian_To_Host_Char(char * c)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_CHAR_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (c != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)c), sizeof (char));
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

int Common_Host_To_Big_Endian_UShort(unsigned short * us)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_USHORT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (us != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)us), sizeof (unsigned short));
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

int Common_Big_Endian_To_Host_UShort(unsigned short * us)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_USHORT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (us != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)us), sizeof (unsigned short));
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

int Common_Host_To_Big_Endian_Short(short * s)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_SHORT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (s != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)s), sizeof (short));
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

int Common_Big_Endian_To_Host_Short(short * s)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_SHORT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (s != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)s), sizeof (short));
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

int Common_Host_To_Big_Endian_UInt(unsigned int * ui)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_UINT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ui != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ui), sizeof (unsigned int));
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

int Common_Big_Endian_To_Host_UInt(unsigned int * ui)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_UINT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ui != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ui), sizeof (unsigned int));
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

int Common_Host_To_Big_Endian_Int(int * i)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_INT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (i != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)i), sizeof (int));
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

int Common_Big_Endian_To_Host_Int(int * i)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_INT_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (i != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)i), sizeof (int));
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

int Common_Host_To_Big_Endian_ULong(unsigned long * ul)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_ULONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ul != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ul), sizeof (unsigned long));
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

int Common_Big_Endian_To_Host_ULong(unsigned long * ul)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_ULONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ul != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ul), sizeof (unsigned long));
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

int Common_Host_To_Big_Endian_Long(long * l)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_LONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (l != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)l), sizeof (long));
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

int Common_Big_Endian_To_Host_Long(long * l)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_LONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (l != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)l), sizeof (long));
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

int Common_Host_To_Big_Endian_ULong_Long(unsigned long long * ull)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_ULONG_LONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ull != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ull), sizeof (unsigned long long));
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

int Common_Big_Endian_To_Host_ULong_Long(unsigned long long * ull)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_ULONG_LONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ull != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ull), sizeof (unsigned long long));
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

int Common_Host_To_Big_Endian_Long_Long(long long * ll)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_LONG_LONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ll != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ll), sizeof (long long));
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

int Common_Big_Endian_To_Host_Long_Long(long long * ll)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_LONG_LONG_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (ll != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)ll), sizeof (long long));
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

int Common_Host_To_Big_Endian_Size_T(size_t * st)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_SIZE_T_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (st != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)st), sizeof (size_t));
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

int Common_Big_Endian_To_Host_Size_T(size_t * st)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */

		/* Check host's endianness. */
		ret = Common_SIZE_T_Endianness_Check();
		if (ret != MSYS_BIG_ENDIAN)
		{
				/* Check for valid endianness. */
				if (ret == MSYS_LITTLE_ENDIAN)
				{
						/* Check for invalid arguments. */
						if (st != NULL)
						{
								/* Call Common_Byte_Swap(). */
								ret = Common_Byte_Swap(((char*)st), sizeof (size_t));
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

int Common_UCHAR_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		unsigned char t = '\1';				/* Variable to check. */

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

int Common_CHAR_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		char t = '\1';						/* Variable to check. */

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

int Common_USHORT_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		unsigned short t = 1;				/* Variable to check. */

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

int Common_SHORT_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		short t = 1;						/* Variable to check. */

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

int Common_UINT_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		unsigned int t = 1;					/* Variable to check. */

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

int Common_INT_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		int t = 1;							/* Variable to check. */

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

int Common_ULONG_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		unsigned long t = 1;				/* Variable to check. */

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

int Common_LONG_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		long t = 1;							/* Variable to check. */

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

int Common_ULONG_LONG_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		unsigned long long t = 1;			/* Variable to check. */

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

int Common_LONG_LONG_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		long long t = 1;					/* Variable to check. */

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

int Common_SIZE_T_Endianness_Check()
{
		/* Init vars. */
		int ret = MSYS_UNKNOWN_ENDIANNESS;	/* The result of this function. */
		size_t t = 1;						/* Variable to check. */

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

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */
