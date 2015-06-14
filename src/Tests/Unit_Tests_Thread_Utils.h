/*!
    Multiverse Engine Project 13/6/2015 Unit Tests Unit_Tests_Thread_Utils.h

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
#ifndef UNIT_TESTS_THREAD_UTILS_H
#define UNIT_TESTS_THREAD_UTILS_H

/* Internal includes. */
#include "../Common/Src/Threading_Subsystem/Thread_Utils.h"

/* Define thread_utils test structs. */
struct return_me
{
        bool cont;
        void * object;
        short rc;
};

/* Define thread_utils test functions. */
void Hacky_Delay();
void *Test_Function_1(void * dummy);
void *Test_Function_Mutex_Lock(void * dummy);
void *Test_Function_Condition_Lock(void * dummy);
void *Test_Function_Condition_Wait_Lock(void * dummy);
TU_Thread * Create_NONE_UNSUPPORTED_Thread_Class();
void Output_All_Supported_Threading_Libraries();
void Basic_Thread_Test();
void Test_Select_Library_Perferred_Library_Setting();
bool Test_Thread_Support(TU_Library_Support_Status & our_requirements,
			 const TU_Library_Support_Status * lib_status);
bool Test_Mutex_Support(TU_Library_Support_Status & our_requirements,
			const TU_Library_Support_Status * lib_status);
bool Test_Condition_Variable_Support(TU_Library_Support_Status & our_requirements,
				     const TU_Library_Support_Status * lib_status);
void Library_Test(const Common_LibraryID & lib);
int unit_test_thread_utils_main();

#endif	/* UNIT_TESTS_THREAD_UTILS_H */

/* End of Unit_Tests_Thread_Utils.h */
