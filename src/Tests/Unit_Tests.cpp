/*!
    Multiverse Engine Project 21/8/2012 Unit Tests Unit_Tests.cpp

    Copyright (C) 2014 Multiverse Engine Project

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
#include "Unit_Tests.h"

int main()
{
	// Delcare vars.
	short error_code_data_object = 0;
	short error_code_fileutills = 0;
	short error_code_thread_utils = 0;

    // Starting Unit tests.
    std::cout << "Multiverse_Engine_Project_Public Unit Tests Compiled on: " << TESTCOMPILEDATE << " " << TESTCOMPILETIME << "\n";
    std::cout << "Starting Unit tests for DataProcess::Data_Object. Please be pacent this can take some time.\n";
    error_code_data_object = Unit_Test_Data_Object();

/* Only call FileUtills tests if FileUtills was built. */
#ifdef MSYS_HAVE_FILEUTILLS
	std::cout << "Starting FileUtills Tests.\n";
	error_code_fileutills = unit_test_fileutills_main();
#else
	std::cout << "FileUtills was disabled at build time. Skipping FileUtills tests.\n";
#endif	/* MSYS_HAVE_FILEUTILLS */

/* Only call Thread_Utils tests if Thread_Utils was built. */
#ifdef MSYS_HAVE_THREAD_UTILS
	std::cout << "Starting Thread_Utils Tests.\n";
	error_code_thread_utils = unit_test_thread_utils_main();
#else
	std::cout << "Thread_Utils was disabled at build time. Skipping Thread_Utils tests.\n";
#endif	/* MSYS_HAVE_THREAD_UTILS */

	// Output overall test results.
	std::cout << "Overall Test Results:\n\n";
	
	// Check to see if a test failed.
	std::cout << "DataProcess::Data_Object Tests: ";
	if (error_code_data_object != 0)
	{
		std::cout << "FAIL\n";
		std::cout << "Returned error code was: " << error_code_data_object << ".\n";
	}
	else
	{
		std::cout << "PASS\n";
	}

	/* Only output a result if we ran the tests. */
#ifdef MSYS_HAVE_FILEUTILLS
	std::cout << "FileUtills Tests: ";
	if (error_code_fileutills != 0)
	{
		std::cout << "FAIL\n";
		std::cout << "Returned error code was: " << error_code_fileutills << ".\n";
	}
	else
	{
		std::cout << "PASS\n";
	}
#endif	/* MSYS_HAVE_FILEUTILLS */

#ifdef MSYS_HAVE_THREAD_UTILS
	std::cout << "Thread_Utils Tests: ";
	if (error_code_thread_utils != 0)
	{
		std::cout << "FAIL\n";
		std::cout << "Returned error code was: " << error_code_thread_utils << ".\n";
	}
	else
	{
		std::cout << "PASS\n";
	}
#endif	/* MSYS_HAVE_THREAD_UTILS */

	/* Exit test program. */
	return 0;
}
