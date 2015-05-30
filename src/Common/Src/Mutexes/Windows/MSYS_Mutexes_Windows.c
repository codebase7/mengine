/*!
    Multiverse Engine Project 29/5/2015 Common MSYS_Mutexes_Windows.c

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

/* Check for _WIN32 */
#ifdef _WIN32

/* Internal includes. */
#include "..\MSYS_Mutexes.h"

/* External includes (Platform specific) */
#include <intrin.h>
#include <Windows.h>
/* Change 0 to 1 below if on Windows 8 or newer. */
#if 0
#include <Processthreadsapi.h>
#endif /* 0 */

/* Define extern C */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Define the needed function calls. */
long MSYS_Get_Thread_ID()
{
	/* Init vars. */
	long ret = 0;		/* The result of this function. */

	/* Call the system call GetCurrentThreadId(). */
	ret = GetCurrentThreadId();

	/* Check for success. */
	if (ret == 0)
	{
		/* Unsuccessful. */
		ret = MSYS_INVALID_TID;
	}

	/* Return the result. */
	return ret;
}

void MSYS_Sync_Memory()
{
/* Compiler / System specific memory sync calls go here.... */
#ifdef _MSC_FULL_VER
	_ReadWriteBarrier();
#endif	/* _MSC_FULL_VER */

	/* Exit function. */
	return;
}

bool MSYS_Compare_And_Swap(bool * address, const bool oldValToCheckFor, const bool newValToWrite)
{
	/* Init vars. */
	bool ret = false;		/* The result of this function. */

/* Compiler specific calls go here. */
#ifndef _MSC_FULL_VER
	/* MSVC can not use the bool impelmentation.
	   Not only is C99's _Bool not supported until MSVC 2013, but
	   the _InterlockedCompareExchange() compiler intrinsic requires
	   at least a long data type. Hence the bool impelmenetation is 
	   not required.
	*/
#error "MSVC Does not require the bool implementation for internal mutexes support. You should make sure that MSYS_INSUFFIENCT_BITS_LONG_LOCK is undefined."
#endif	/* _MSC_FULL_VER */

	/* Return the result. */
	return ret;
}

bool MSYS_Compare_And_Swap_Long(long * address, const long oldValToCheckFor, const long newValToWrite)
{
	/* Init vars. */
	bool ret = false;		/* The result of this function. */

#ifdef _MSC_FULL_VER
	/* _InterlockedCompareExchange(long volatile * DESTIONATION, long EXCHANGE, long COMPERAND) */
	if (_InterlockedCompareExchange(address, newValToWrite, oldValToCheckFor) == oldValToCheckFor)
	{
			ret = true;
	}
#endif	/* _MSC_FULL_VER */

	/* Return the result. */
	return ret;
}

/* Define extern C */
#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */

#endif	// _WIN32

// End of MSYS_Mutexes_Windows.c
