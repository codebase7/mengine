/*!
    Multiverse Engine Project 10/4/2015 Common MSYS_Mutexes_Linux.c

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
#include "MSYS_Mutexes.h"

/* Define extern C */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Define the needed function calls. */
long MSYS_Get_Thread_ID()
{
	/* Init vars. */
	long ret = 0;		/* The result of this function. */

	/* Call the system call gettid(2). (NOT pthread_self(3), that cannot be converted to a long in ANY reasonable manner. Hence the linux host preprocessor check as gettid(2) is linux specific.) */
	ret = gettid();

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
#ifdef __GNUC__
	__sync_synchronize();
#endif	/* __GNUC__ */

	/* Exit function. */
	return;
}

bool MSYS_Compare_And_Swap(bool * address, const bool oldValToCheckFor, const bool newValToWrite)
{
	/* Init vars. */
	bool ret = false;

#ifdef __GNUC__
	ret = __sync_bool_compare_and_swap(address, oldValToCheckFor, newValToWrite);
#endif	/* __GNUC__ */

	/* Return the result. */
	return ret;
}

bool MSYS_Compare_And_Swap_Long(long * address, const long oldValToCheckFor, const long newValToWrite)
{
	/* Init vars. */
	bool ret = false;

#ifdef __GNUC__
	ret = __sync_bool_compare_and_swap(address, oldValToCheckFor, newValToWrite);
#endif	/* __GNUC__ */

	/* Return the result. */
	return ret;
}

#ifdef __cplusplus
}	/* extern C */
#endif	/* __cplusplus */

/* End of MSYS_Mutexes_Linux.c */
