/*!
    Multiverse Engine Project 21/8/2012 Unit Tests Unit_Tests.cpp

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
        
	std::cout << "Starting FileUtills Tests.\n";
        error_code_fileutills = unit_test_fileutills_main();
	
	std::cout << "Starting Thread_Utils Tests.\n";
	error_code_thread_utils = unit_test_thread_utils_main();
	
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
	
        return 0;
}
