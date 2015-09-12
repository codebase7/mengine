/*!
    Multiverse Engine Project 02/6/2013 Unit Tests Test_Base_Header.h
    
    Copyright (C) 2013 Multiverse Engine Project

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

#ifndef TEST_BASE_HEADER_H
#define TEST_BASE_HEADER_H

// External Includes.

/* C++ specific includes. */
#ifdef __cplusplus
#include <iostream>     // For std::cout / NULL macro.
#else
/* C specific includes. */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#endif	/* __cplusplus */

#include <string.h>     // For strcmp.
#ifdef _WIN32
#include <Windows.h>	/* For SleepEx(). */
#else	/* _WIN32 */
#include <unistd.h>     /* For sleep. */
#endif	/* _WIN32 */
#include <time.h>	// For time().
#include <stdlib.h>	// For rand() / srand().

// Define compile date time stamp.
#ifndef TESTCOMPILEDATE
#define TESTCOMPILEDATE __DATE__
#endif

#ifndef TESTCOMPILETIME
#define TESTCOMPILETIME __TIME__
#endif

// Define section deviders.
#ifndef START_TEST_SECTION
#define START_TEST_SECTION "\n\n=============== START OF TEST SECTION ================\n\n"
#endif

#ifndef END_TEST_SECTION
#define END_TEST_SECTION "\n\n=============== END OF TEST SECTION ================\n\n"
#endif

// Define max failures.
#ifndef MAX_FAILURES
#define MAX_FAILURES 3
#endif

// Define Unknown Error message.
const char UNKNOWN_ERROR[] = "Unknown Error.";

// Define Error_Messages struct.
struct Error_Messages{
	short error_code;
	const char * message;
};

/*!
 * 		void Msys_Sleep(const unsigned int secondsToSleep)
 *
 *		Sleeps the thread for the given number of seconds, unless a system defined
 *		condition forces an early wake up.
 *
 * 		This function does not have a return.
 */
void Msys_Sleep(const unsigned int secondsToSleep);

#endif

// End of Test_Base_Header.h
