/*!
    Multiverse Engine Project 10/4/2015 Common MSYS_Mutexes_Linux.h

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
#ifndef MSYS_MUTEXES_LINUX_H
#define MSYS_MUTEXES_LINUX_H

/* Check for defined MSYS_MUTEXES_H. */
#ifndef MSYS_MUTEXES_H
#error "You should not inlcude MSYS_Mutexes_Linux.h directly. Use MSYS_Mutexes.h instead. Aborting build."
#endif	/* MSYS_MUTEXES_H */

/* Check for linux declaration. */
#ifdef __linux__

/* Define extern C */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Check which C standard is supported by the compiler. */
#if __STDC_VERSION__ < 199901L
/* We need to include our fake stdbool.h header file. */
#include "../../../../stdbool.h"
#else
/* Use the compiler's version of stdbool.h. */
#include <stdbool.h>

/* We need to include aliases for TRUE and FALSE. */
#ifndef TRUE
#define TRUE true
#endif /* TRUE */

#ifndef FALSE
#define FALSE false
#endif /* FALSE */
#endif  /* __STDC_VERSION__ < 199901L */

/* Define the invalid thread ID to use. */
#define MSYS_INVALID_TID 0

/* Define the needed function calls. */
long MSYS_Get_Thread_ID();

void MSYS_Sync_Memory();

#ifdef __cplusplus
}	/* extern C */
#endif	/* __cplusplus */

#endif	/* __linux__ */

#endif	/* MSYS_MUTEXES_LINUX_H */

/* End of MSYS_Mutexes_Linux.h */
