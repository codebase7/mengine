/*!
    Multiverse Engine Project 29/5/2015 Common MSYS_Mutexes_Windows.h

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

/* Check for defined MSYS_MUTEXES_H. */
#ifndef MSYS_MUTEXES_H
#error "You should not inlcude MSYS_Mutexes_Windows.h directly. Use MSYS_Mutexes.h instead. Aborting build."
#endif	/* MSYS_MUTEXES_H */

/* Include guard. */
#ifndef MSYS_MUTEXES_WINDOWS
#define MSYS_MUTEXES_WINDOWS

/* Check for win32 declaration. */
#ifdef _WIN32

/* Define the invalid thread ID to use. */
#define MSYS_INVALID_TID 0

/* Define true and false values for the fake boolean implementation. */
#define MSYS_LONG_TRUE 1L
#define MSYS_LONG_FALSE 0L

/* Define the needed function calls. */
long MSYS_Get_Thread_ID();

void MSYS_Sync_Memory();

#endif	/* _WIN32 */

#endif	/* MSYS_MUTEXES_WINDOWS */

/* End of MSYS_Mutexes_Windows.h */
