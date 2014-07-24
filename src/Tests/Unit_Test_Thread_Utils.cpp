/*!
    Basic Test for thread_utils. 22/5/2013

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

#include "Unit_Tests.h"

void Hacky_Delay()
{
        // Init delay.
        const int delay = 5;

        // Yeah this is a hack......
        sleep(delay);

        // Exit function.
        return;
}

void *Test_Function_1(void * dummy)
{
        // Keep us busy so we don't exit right way.
        Hacky_Delay();

        // Exit function.
        return NULL;
}

void *Test_Function_Mutex_Lock(void * dummy)
{
        // Init counter.
        size_t counter = 0;

        // Init pointers.
        TU_Mutex * mu = NULL;
        return_me * rm = NULL;

        // Get rc.
        rm = (return_me*)dummy;

        // Check for NULL.
        if (rm == NULL)
        {
                // ERROR.
                return NULL;
        }

        // Dereference the pointer.
        mu = (TU_Mutex*)rm->object;

        // Check for NULL.
        if (mu == NULL)
        {
                // ERROR.
                rm->rc = -9;
                return NULL;
        }

        // Lock the mutex.
        counter = mu->Try_Lock_Mutex();

        // Set cont.
        rm->cont = true;

        // Check for return success.
        if (counter != 0)
        {
                // ERROR.
                rm->rc = counter;
                return NULL;
        }

        // Set success.
        rm->rc = 1;

        // Exit function.
        return NULL;
}

void *Test_Function_Condition_Lock(void * dummy)
{
        // Init ret.
        short ret = 0;

        // Init pointers.
        TU_Condition * cond = NULL;
        return_me * rm = NULL;

        // Get rc.
        rm = (return_me*)dummy;

        // Check for NULL.
        if (rm == NULL)
        {
                // ERROR.
                return NULL;
        }

        // Dereference the pointer.
        cond = (TU_Condition*)rm->object;

        // Check for NULL.
        if (cond == NULL)
        {
                // ERROR.
                rm->rc = -9;
                return NULL;
        }

        // Set cont.
        rm->cont = true;

        // Wait on thread.
        ret = cond->Wait();

        // Check for error.
        if (!ret)
        {
                // Set success.
                rm->rc = 1;
                return NULL;
        }

        // Exit function.
        rm->rc = ret;
        return NULL;
}

void *Test_Function_Condition_Wait_Lock(void * dummy)
{
        // Init ret.
        short ret = 0;

        // Init pointers.
        TU_Condition * cond = NULL;
        return_me * rm = NULL;

        // Get rc.
        rm = (return_me*)dummy;

        // Check for NULL.
        if (rm == NULL)
        {
                // ERROR.
                return NULL;
        }

        // Dereference the pointer.
        cond = (TU_Condition*)rm->object;

        // Check for NULL.
        if (cond == NULL)
        {
                // ERROR.
                rm->rc = -9;
                return NULL;
        }

        // Set cont.
        rm->cont = true;

        // Wait on thread. (Wait three seconds.)
        ret = cond->Timed_Wait(3);

        // Check for error.
        if (ret)
        {
                // Check that we aborted on timeout.
                if (ret == 1)
                {
                        // Set success.
                        rm->rc = 1;
                        return NULL;
                }
        }

        // Exit function.
        rm->rc = ret;
        return NULL;
}

TU_Thread * Create_NONE_UNSUPPORTED_Thread_Class()
{
        // Init vars.
        TU_Thread * th = NULL;
        Common_LibraryID Library_ID_Test = TU_LibID_none;

        // Tell user we are attempting to create a thread with the given library.
        std::cout << "Attempting to create thread using LibraryID (Should fail): ";

        // Create new thread.
        th = Common::Thread_Utils::Create_Thread(Library_ID_Test);

        // Check for NULL.
        if (th == NULL)
        {
                std::cout << "PASS\n";
        }
        else
        {
                // Error.
                std::cout << "FAILED\n";
                std::cout << "Create_Thread() created an object and should not have, aborting.\n";

                // Make sure th is really NULL.
                if (th != NULL)
                {
			std::cout << "Destroying thread object: ";
			std::cout.flush();
			if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
			{
				// Success.
				std::cout << "PASS\n";
			}
			else
			{
				std::cout << "FAIL\n";
			}
                }

                // Exit function.
                return th;
        }

        // Make sure th is really NULL.
        if (th != NULL)
        {
		std::cout << "Destroying thread object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }

        // Because Thread_Utils::Create_Thread() will NOT create a None / Unsupported class, we must do it manually.
        std::cout << "Manually creating thread object for None / Unsupported. NEVER DO THIS IN A PRODUCTION PROGRAM!\n";

        // Just another reiteration, DO NOT CREATE THIS CLASS YOURSELF! It's only being done here for testing purposes.
        try{
                th = new TU_Thread;
        }
        catch(...)
        {
                std::cout << "Exception occured, aborting.\n";

                // Exit function.
                return th;
        }

        // Exit function.
        return th;
}

void Output_All_Supported_Threading_Libraries()
{
        // Init vars.
        short count = 0;
	TU_Library_Support_Status noRequires;
	Common_LibraryID previousLib = TU_LibID_none;
	Common_LibraryID currentLib = TU_LibID_none;

        // Get total number of supported threading libraries.
        count = Common::Thread_Utils::Get_Number_of_Supported_Thread_Libraries();

	// Make sure we actually have a real library and not just the dummy library.
	if (count > 1)
	{
		// Init the noRequires structure.
		Common::Thread_Utils::Init_Library_Support_Status(&noRequires);

		// Output table headers.
		std::cout << "Library Name\t\t\tType\t\n";

		// Output each supported library.
		for (size_t x = 0; x < count; x++)
		{
			// Get the next library.
			previousLib = currentLib;
			currentLib = Common::Thread_Utils::Select_Library(noRequires, previousLib);

			// Check to see if we are trying to output the dummy library. (Skip it if we are.)
			if ((strcmp(currentLib.Name, TU_LibID_none.Name) != 0) && (currentLib.bIsPlugin != TU_LibID_none.bIsPlugin))
			{
				// Output library name.
				if (currentLib.Name != NULL)
				{
					// Output library name.
					std::cout << currentLib.Name << "\t\t\t";

					// Output whether or not the library is a loaded plugin or not.
					if (currentLib.bIsPlugin)
					{
						std::cout << "(Plugin)";
					}
					else
					{
						std::cout << "(Internal)";
					}
					std::cout << '\n';
				}
			}
		}

		// Output total number of supported threading libraries.
		std::cout << '\n';
		std::cout << "Total number of supported threading libraries: " << (count - 1) << ".\n\n";
	}

        // Exit function.
        return;
}

void Basic_Thread_Test()
{
        // Init vars.
        short ret = 0;
        unsigned long int pid = 0;
        void * ret_from_thread = NULL;

        // Init Library_Support_Status Structure.
        TU_Library_Support_Status our_requirements;
        Common::Thread_Utils::Init_Library_Support_Status(&our_requirements);

        // Set threading support flag.
        our_requirements.bThreadsSupport = true;

        // Output START OF TEST SECTION.
        std::cout << START_TEST_SECTION;

        // Tell user we are selecting a threading library.
        std::cout << "Selecting a threading library for basic thread test, and creating the thread.\n";

        // Init thread object.
        TU_Thread * th = NULL;

        th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::Select_Library(our_requirements));

        // Check for NULL.
        if (th == NULL)
        {
                // Error.
                std::cout << "An error occured while initing the thread, aborting.\n";

                // Output END OF TEST SECTION.
                std::cout << END_TEST_SECTION;

                // Exit function.
                return;
        }

        // Output the chosen thread.
        std::cout << "The threading library chosen was: " << (th->Get_Thread_Library()).Name << ".\n\n";

        // Tell user we are initing the thread.
        std::cout << "Initing thread.\n";

        // Init the thread.
        ret = th->Create_Thread(Test_Function_1, NULL, &pid);

        // Check for error.
        if (ret != 0)
        {
                // Output error code.
                std::cout << "Error occured while initing the thread, thread library was: " << (th->Get_Thread_Library()).Name << ".\n";
                std::cout << "Return code from Thread_Utils function was: " << ret << ".\n";
                std::cout << "Return code from library was: " << th->Get_Return_Code() << ".\n";
                std::cout << "Aborting.\n";

                // Destroy object.
                if (th != NULL)
                {
			std::cout << "Destroying thread object: ";
			std::cout.flush();
			if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
			{
				// Success.
				std::cout << "PASS\n";
			}
			else
			{
				std::cout << "FAIL\n";
			}
                }

                // Output END OF TEST SECTION.
                std::cout << END_TEST_SECTION;

                // Exit function.
                return;
        }

        // Tell the user the pid.
        std::cout << "PID for new thread is: " << pid << ".\n";

        // Tell user we are waiting on the thread to finish.
        std::cout << "Waiting on all threads to finish.\n";

        // Join the thread.
        ret = th->Join_Thread(&ret_from_thread);

        // Tell user return code from thread_utils.
        std::cout << "Return code from Join_Thread() for PID: " << pid << " was: ";
        std::cout << ret << ".\n";

        // Tell user the pointer address for the return value from the thread.
        std::cout << "Return value pointer address from thread is: " << ret_from_thread << ".\n";

        // Destroy objects.
        if (th != NULL)
        {
		std::cout << "Destroying thread object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }

        // Output END OF TEST SECTION.
        std::cout << END_TEST_SECTION;
        
        // Exit function.
        return;
}

void Test_Select_Library_Perferred_Library_Setting()
{
	// Init vars.
	Common_LibraryID firstLib = TU_LibID_none;
	Common_LibraryID secondLib = TU_LibID_none;
	const Common_LibraryID Library_ID_Fake = {true, "Non-existant Library"};
	TU_Library_Support_Status our_requirements;
	const TU_Library_Support_Status * checkSupport;

	// Init Library_Support_Status Structures.
	Common::Thread_Utils::Init_Library_Support_Status(&our_requirements);

	// Output START OF TEST SECTION.
	std::cout << START_TEST_SECTION;

	// Tell user that we are testing the perferred library options.
	std::cout << "Testing perferred library support in Thread_Utils::Select_Library():\n";

	// Get an inital library.
	firstLib = Common::Thread_Utils::Select_Library(our_requirements);
	std::cout << "Attempting to get Library ID: " << firstLib.Name << ' ';
	if (firstLib.bIsPlugin)
	{
		std::cout << "(Plugin)";
	}
	else
	{
		std::cout << "(Internal)";
	}
	std::cout << " via perferred library setting: ";

	// Set perferred library.
	our_requirements.lib = &firstLib;

	// Get ID.
	secondLib = Common::Thread_Utils::Select_Library(our_requirements);

	// Check result.
	if ((secondLib.bIsPlugin == our_requirements.lib->bIsPlugin) || (strcmp(secondLib.Name, our_requirements.lib->Name) == 0))
	{
		std::cout << "PASS\n";
	}
	else
	{
		std::cout << "FAILED\n";
	}

	// Output result data from Select_Library().
	std::cout << "Select_Library() returned Library ID: " << secondLib.Name << ' ';
	if (secondLib.bIsPlugin)
	{
		std::cout << "(Plugin)";
	}
	else
	{
		std::cout << "(Internal)";
	}
	std::cout << '\n';

	// Attempt to test a skipped library.
	std::cout << "Attempting to get library after skipping it. (Should fail.): ";

	// Select new library, skipping the library we are trying to retrive.
	secondLib = Common::Thread_Utils::Select_Library(our_requirements, *our_requirements.lib);

	// Check result.
	if ((secondLib.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(secondLib.Name, our_requirements.lib->Name) == 0))
	{
		std::cout << "PASS\n";
	}
	else
	{
		std::cout << "FAILED\n";
	}

	// Output result data from Select_Library().
	std::cout << "Select_Library() returned Library ID: " << secondLib.Name << ' ';
	if (secondLib.bIsPlugin)
	{
		std::cout << "(Plugin)";
	}
	else
	{
		std::cout << "(Internal)";
	}
	std::cout << '\n';

	// Tell user we are testing a non existant library.
	std::cout << "Attempting to perfer a library that does not exist (Should Fail): ";

	// Reset requirements, and set perferred library.
	Common::Thread_Utils::Init_Library_Support_Status(&our_requirements);
	our_requirements.lib = &Library_ID_Fake;

	// Select new library.
	secondLib = Common::Thread_Utils::Select_Library(our_requirements);

	// Check result.
	if ((secondLib.bIsPlugin != Library_ID_Fake.bIsPlugin) || (strcmp(secondLib.Name, Library_ID_Fake.Name) != 0))
	{
		std::cout << "PASS\n";
	}
	else
	{
		std::cout << "FAILED\n";
	}

	// Output result data from Select_Library().
	std::cout << "Select_Library() returned Library ID: " << secondLib.Name << ' ';
	if (secondLib.bIsPlugin)
	{
		std::cout << "(Plugin)";
	}
	else
	{
		std::cout << "(Internal)";
	}
	std::cout << '\n';

	// Tell user we are trying to get a library that exists but does not support our requirements.
	std::cout << "Attempting to get a perferred library that exists but does not meet our requirements. (Should fail, and return a different library.): ";

	// Reset requirements, and get first library.
	Common::Thread_Utils::Init_Library_Support_Status(&our_requirements);
	firstLib = Common::Thread_Utils::Select_Library(our_requirements);

	/*
	 * Break the requirements. 
	 * 
	 * First find out what it supports then break it, by requesting
	 * something it does not support. 
	 * 
	 * Note: This test will fail if we can't find a library that 
	 * does not support something.
	 */
	// For each supported library run tests on them.
	for (short x = 0; ((x < Common::Thread_Utils::Get_Number_of_Supported_Thread_Libraries()) &&
	     ((our_requirements.lib->bIsPlugin == TU_LibID_none.bIsPlugin) &&
	      (strcmp(TU_LibID_none.Name, our_requirements.lib->Name) == 0))); x++)
	{
		// Get a new library.
		if ((secondLib.bIsPlugin != TU_LibID_none.bIsPlugin) || (strcmp(secondLib.Name, TU_LibID_none.Name) != 0))
		{
			secondLib = firstLib;
			firstLib = Common::Thread_Utils::Select_Library(our_requirements, secondLib);
		}

		// Get the library's TU_Library_Support_Status structure.
		checkSupport = Common::Thread_Utils::Get_Library_Stats(firstLib);

		// Check to see if the library does not support something.
		if (checkSupport != NULL)
		{
			if (checkSupport->bThreadsSupport)
			{
				if (checkSupport->bJoinThreadSupport)
				{
					if (checkSupport->bDetachThreadSupport)
					{
						if (checkSupport->bLibraryRequiresSpecificFunctionSig)
						{
							if (checkSupport->bMutexesSupport)
							{
								if (checkSupport->bTryLockSupport)
								{
									if (checkSupport->bConditionVariableSupport)
									{
										if (!checkSupport->bConditionWaitTimeoutSupport)
										{
											// The library does not support Wait timeouts on condition variables.
											our_requirements.lib = &firstLib;
											our_requirements.bConditionWaitTimeoutSupport = true;
										}
									}
									else
									{
										// The library does not support condition variables.
										our_requirements.lib = &firstLib;
										our_requirements.bConditionVariableSupport = true;
									}
								}
								else
								{
									// The library does not support Non-Blocking mutex lock attempts.
									our_requirements.lib = &firstLib;
									our_requirements.bTryLockSupport = true;
								}
							}
							else
							{
								// The library does not support mutexes.
								our_requirements.lib = &firstLib;
								our_requirements.bMutexesSupport = true;
							}
						}
						else
						{
							// The library does not require specific thread function signatures.
							our_requirements.lib = &firstLib;
							our_requirements.bLibraryRequiresSpecificFunctionSig = true;
						}
					}
					else
					{
						// The library does not support detaching threads.
						our_requirements.lib = &firstLib;
						our_requirements.bDetachThreadSupport = true;
					}
				}
				else
				{
					// The library does not support joining threads.
					our_requirements.lib = &firstLib;
					our_requirements.bJoinThreadSupport = true;
				}
			}
			else
			{
				// The library does not support threads.
				our_requirements.lib = &firstLib;
				our_requirements.bThreadsSupport = true;
			}
		}
	}

	// Check and see if our_requirements.lib is not TU_LibID_none.
	if ((TU_LibID_none.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(TU_LibID_none.Name, our_requirements.lib->Name) != 0))
	{
		// Select new library.
		secondLib = Common::Thread_Utils::Select_Library(our_requirements);

		// Check result.
		if ((secondLib.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(secondLib.Name, our_requirements.lib->Name) != 0))
		{
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAILED\n";
		}

		// Output result data from Select_Library().
		std::cout << "Select_Library() returned Library ID: " << secondLib.Name << ' ';
		if (secondLib.bIsPlugin)
		{
			std::cout << "(Plugin)";
		}
		else
		{
			std::cout << "(Internal)";
		}
		std::cout << '\n';
	}
	else
	{
		std::cout << "N/A\n";
		std::cout << "This test cannot be performed, as all of the supported libraries support everything.\n\n";
	}

	// Output END OF TEST SECTION.
	std::cout << END_TEST_SECTION;

	// Exit function.
	return;
}

bool Test_Thread_Support(TU_Library_Support_Status & our_requirements, const TU_Library_Support_Status * lib_status)
{
        // Init vars.
        bool bNoneUnsupportedlibrary = false;       // Whether or not we are testing the None / Unsupported library.
        short ret = 0;
        unsigned long int pid = 0;
        void * ret_from_thread = NULL;
        Common_LibraryID Library_ID_Test;

        // Init thread object.
        TU_Thread * th = NULL;

        // Check and see if we are testing the None / unsupported library.
        if ((our_requirements.lib->bIsPlugin == TU_LibID_none.bIsPlugin) && (strcmp(our_requirements.lib->Name, TU_LibID_none.Name) == 0))
        {
                bNoneUnsupportedlibrary = true;
        }

        // Check to see if we lack a lib_status struct.
        if ((!bNoneUnsupportedlibrary) && (lib_status == NULL))
        {
		// We cannot test this library.
		std::cout << "Error: Test_Mutex_Support() called without a TU_Library_Support_Status structure, for Library ID: ";
		std::cout << our_requirements.lib->Name << ' ';
		if (our_requirements.lib->bIsPlugin)
		{
			std::cout << "(Plugin)";
		}
		else
		{
			std::cout << "(Internal)";
		}
		std::cout << "\nWe need a TU_Library_Support_Status structure to test the library, Skipping test.\n";
        }
        else
        {
                // Tell user we are testing thread support.
                std::cout << "Testing thread support.\n";

                // Tell user we are attempting to create the class.
                std::cout << "Creating thread class: ";

                // Check for None / Unsupported.
                if (bNoneUnsupportedlibrary)
                {
                        // Call class creation function.
                        th = Create_NONE_UNSUPPORTED_Thread_Class();
                }
                else
                {
                        // Create thread.
                        th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::Select_Library(our_requirements));
                }

                // Check for NULL.
                if (th == NULL)
                {
                        // Error.
                        std::cout << "FAILED\n";
                        std::cout << "An error occured while initing the thread, aborting.\n";

                        // Output END OF TEST SECTION.
                        std::cout << END_TEST_SECTION;

                        // Exit function.
                        return false;
                }

                /*
                        Note: th should be the given library.
                        Verify that the correct library was chosen.
                */
                Library_ID_Test = th->Get_Thread_Library();
                if ((Library_ID_Test.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(Library_ID_Test.Name, our_requirements.lib->Name) != 0))
                {
                        std::cout << "FAILED\n";
			std::cout << "ERROR, could not select library: " << our_requirements.lib->Name << ' ';
			if (our_requirements.lib->bIsPlugin)
			{
				std::cout << "(Plugin)";
			}
			else
			{
				std::cout << "(Internal)";
			}
			std::cout << ".\n";
			std::cout << "Skipping library.\n\n";
                }
                else
                {
                        // Previous test passed, report it.
                        std::cout << "PASS\n";

                        // Test each function. (Note: For None / Unsupported they should all fail.)
                        std::cout << "Testing thread creation: ";
                        ret = th->Create_Thread(Test_Function_1, NULL, &pid);

                        // Check and see if we are testing the None / Unsupported library.
                        if (bNoneUnsupportedlibrary)
                        {
                                // Check for unimplimented.
                                if (ret == -3)
                                {
                                        std::cout << "PASS\n";
                                }
                                else
                                {
                                        // Error this function should be unimplimented for None / Unsupported.
                                        std::cout << "FAILED\n";
                                        std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                        std::cout << "Return code was: " << ret << '\n';
                                }
                        }
                        else
                        {
                                // Check for return OK.
                                if (ret == 0)
                                {
                                        std::cout << "PASS\n";

                                        // Tell the user the pid.
                                        std::cout << "PID for new thread is: " << pid << ".\n";
                                }
                                else
                                {
                                        // Error.
                                        std::cout << "FAILED\n";
                                        std::cout << "Return code was: " << ret << '\n';
                                }
                        }

                        // Check and see if the library supports thread joining.
                        if ((bNoneUnsupportedlibrary) || (lib_status->bJoinThreadSupport))
                        {
                                // Test Join_Thread().
                                std::cout << "Testing thread joining. (Note: This could take a minute.): ";
                                std::cout.flush();
                                ret = th->Join_Thread(&ret_from_thread);

                                // Check and see if we are testing the None / Unsupported library.
                                if (bNoneUnsupportedlibrary)
                                {
                                        // Check for unimplimented.
                                        if (ret == -3)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error this function should be unimplimented for None / Unsupported.
                                                std::cout << "FAILED\n";
                                                std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                                else
                                {
                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";

                                                // Tell user return code from thread_utils.
                                                std::cout << "Return code from Join_Thread() for PID: " << pid << " was: ";
                                                std::cout << ret << ".\n";

                                                // Tell user the pointer address for the return value from the thread.
                                                std::cout << "Return value pointer address from thread is: " << ret_from_thread << ".\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                        }
                        else
                        {
                                // Library does NOT support joining threads.
                                std::cout << "Library does NOT support joining threads, skipping test.\n";
                        }

                        // Check and see if the library supports thread detachment.
                        if ((bNoneUnsupportedlibrary) || (lib_status->bDetachThreadSupport))
                        {
                                // Check for None / Unsupported.
                                if (!bNoneUnsupportedlibrary)
                                {
					// Destroy objects.
                                        if (th != NULL)
                                        {
						std::cout << "Destroying thread object: ";
						std::cout.flush();
						if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
						{
							// Success.
							std::cout << "PASS\n";
						}
						else
						{
							std::cout << "FAIL\n";
						}
                                        }
				  
                                        // Tell user we are creating a new thread for detachment.
                                        std::cout << "Creating new thread for detachment test: ";

                                        // Create new object.
                                        th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::Select_Library(our_requirements));

                                        // Check for NULL.
                                        if (th == NULL)
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "An error occured while initing the thread, aborting.\n";

                                                // Output END OF TEST SECTION.
                                                std::cout << END_TEST_SECTION;

                                                // Exit function.
                                                return false;
                                        }

                                        /*
                                                Note: th should be the given library.
                                                Verify that the correct library was chosen.
                                        */
                                        Library_ID_Test = th->Get_Thread_Library();
                                        if ((Library_ID_Test.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(Library_ID_Test.Name, our_requirements.lib->Name) != 0))
                                        {
                                                std::cout << "FAILED\n";
						std::cout << "ERROR, could not select library: " << our_requirements.lib->Name << ' ';
						if (our_requirements.lib->bIsPlugin)
						{
							std::cout << "(Plugin)";
						}
						else
						{
							std::cout << "(Internal)";
						}
						std::cout << ".\n";
                                                std::cout << "Test will most likely fail.\n\n";
                                        }

                                        // Previous test passed, report it.
                                        std::cout << "PASS\n";

                                        // Tell user we are dispatching a new thread.
                                        std::cout << "Initing new thread for detachment test: ";

                                        // Create thread.
                                        ret = th->Create_Thread(Test_Function_1, NULL, &pid);

                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";

                                                // Tell the user the pid.
                                                std::cout << "PID for new thread is: " << pid << ".\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }

                                // Test Detach_Thread().
                                std::cout << "Testing thread detachment: ";
                                ret = th->Detach_Thread();

                                // Check and see if we are testing the None / Unsupported library.
                                if (bNoneUnsupportedlibrary)
                                {
                                        // Check for unimplimented.
                                        if (ret == -3)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error this function should be unimplimented for None / Unsupported.
                                                std::cout << "FAILED\n";
                                                std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                                else
                                {
                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                        }
                        else
                        {
                                // Library does not support detaching threads.
                                std::cout << "Library does NOT support detaching threads, skipping test.\n";
                        }

                        // Test get return code.
                        std::cout << "Testing retrival of last return code from the Thread_Utils library: ";
                        ret = th->Get_Return_Code();

                        // Check and see if we are testing the None / Unsupported library.
                        if (bNoneUnsupportedlibrary)
                        {
                                // Check for unimplimented.
                                if (ret == -3)
                                {
                                        std::cout << "PASS\n";
                                }
                                else
                                {
                                        // Error this function should be unimplimented for None / Unsupported.
                                        std::cout << "FAILED\n";
                                        std::cout << "This function should return unimplimented as that was the last return code.\n";
                                        std::cout << "Return code was: " << ret << '\n';
                                }
                        }
                        else
                        {
                                // Check for return OK.
                                if (ret == 0)
                                {
                                        std::cout << "PASS\n";
                                }
                                else
                                {
                                        // Error.
                                        std::cout << "FAILED\n";
                                        std::cout << "Return code was: " << ret << '\n';
                                }
                        }
                }
        }

        // Destroy object.
        if (th != NULL)
        {
		std::cout << "Destroying thread object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }

        // Exit function.
        return true;
}

bool Test_Mutex_Support(TU_Library_Support_Status & our_requirements, const TU_Library_Support_Status * lib_status)
{
        // Init vars.
        bool bNoneUnsupportedlibrary = false;       // Whether or not we are testing the None / Unsupported library.
        short ret = 0;
        short hack_delay_count = 0;                 // Used to tell how long we have waited.
        unsigned long int pid = 0;
        Common_LibraryID Library_ID_Test;
        return_me rm;
        rm.cont = false;
        rm.object = NULL;
        rm.rc = 0;

        // Init thread object.
        TU_Thread * th = NULL;

        // Init mutex object.
        TU_Mutex * mu = NULL;

        // Check and see if we are testing the None / unsupported library.
        if ((our_requirements.lib->bIsPlugin == TU_LibID_none.bIsPlugin) && (strcmp(our_requirements.lib->Name, TU_LibID_none.Name) == 0))
        {
		// We cannot test this library.
		std::cout << "Error: Test_Mutex_Support() called with the dummy library. " << our_requirements.lib->Name << ' ';
		if (our_requirements.lib->bIsPlugin)
		{
			std::cout << "(Plugin)";
		}
		else
		{
			std::cout << "(Internal)";
		}
		std::cout << '\n';
		std::cout << "We cannot test this library as the base class for TU_Mutex is virtual. Skipping test.\n";
        }
        else
        {
                // Check to see if we lack a lib_status struct.
                if (lib_status == NULL)
                {
			// We cannot test this library.
			std::cout << "Error: Test_Mutex_Support() called without a TU_Library_Support_Status structure, for Library ID: " << our_requirements.lib->Name << ' ';
			if (our_requirements.lib->bIsPlugin)
			{
				std::cout << "(Plugin)";
			}
			else
			{
				std::cout << "(Internal)";
			}
			std::cout << '\n';
			std::cout << "We need a TU_Library_Support_Status structure to test the library, Skipping test.\n";
                }
                else
                {
                        // Tell user we are testing mutex support.
                        std::cout << "Testing mutex support.\n";

                        // Tell user we are attempting to create the class.
                        std::cout << "Creating mutex class: ";

                        // Create mutex object.
                        mu = Common::Thread_Utils::Create_Mutex(Common::Thread_Utils::Select_Library(our_requirements));

                        // Check for NULL.
                        if (mu == NULL)
                        {
                                // Error.
                                std::cout << "FAILED\n";
                                std::cout << "ERROR\nAn error occured while initing the mutex, aborting.\n";

                                // Destroy Object.
                                if (th != NULL)
                                {
					std::cout << "Destroying thread object: ";
					std::cout.flush();
					if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
					{
						// Success.
						std::cout << "PASS\n";
					}
					else
					{
						std::cout << "FAIL\n";
					}
                                }
                                
                                // Output END OF TEST SECTION.
                                std::cout << END_TEST_SECTION;
                                return false;
                        }

                        // Set rm's object pointer to mu.
                        rm.object = mu;

                        /*
                                Note: mu should be the given library.
                                Verify that the correct library was chosen.
                        */
                        Library_ID_Test = mu->Get_Thread_Library();
                        if ((Library_ID_Test.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(Library_ID_Test.Name, our_requirements.lib->Name) != 0))
                        {
				std::cout << "FAILED\n";
				std::cout << "ERROR, could not select library: " << our_requirements.lib->Name << ' ';
				if (our_requirements.lib->bIsPlugin)
				{
					std::cout << "(Plugin)";
				}
				else
				{
					std::cout << "(Internal)";
				}
				std::cout << ".\n";
                                std::cout << "Returned library was: " << Library_ID_Test.Name << ' ';
				if (Library_ID_Test.bIsPlugin)
				{
					std::cout << "(Plugin)";
				}
				else
				{
					std::cout << "(Internal)";
				}
				std::cout << ".\n";
				std::cout << "Skipping library.\n\n";
                        }
                        else
                        {
                                // Previous test passed, report it.
                                std::cout << "PASS\n";

                                // Test mutex creation.
                                std::cout << "Testing mutex creation: ";
                                ret = mu->Init_Mutex();

                                // Check and see if we are testing the None / Unsupported library.
                                if (bNoneUnsupportedlibrary)
                                {
                                        // Check for unimplimented.
                                        if (ret == -3)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error this function should be unimplimented for None / Unsupported.
                                                std::cout << "FAILED\n";
                                                std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                                else
                                {
                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }

                                // Test mutex locking.
                                std::cout << "Testing mutex locking: ";
                                ret = mu->Lock_Mutex();

                                // Check and see if we are testing the None / Unsupported library.
                                if (bNoneUnsupportedlibrary)
                                {
                                        // Check for unimplimented.
                                        if (ret == -3)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error this function should be unimplimented for None / Unsupported.
                                                std::cout << "FAILED\n";
                                                std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                                else
                                {
                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }

                                // Test mutex unlocking.
                                std::cout << "Testing mutex unlocking: ";
                                ret = mu->Unlock_Mutex();

                                // Check and see if we are testing the None / Unsupported library.
                                if (bNoneUnsupportedlibrary)
                                {
                                        // Check for unimplimented.
                                        if (ret == -3)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error this function should be unimplimented for None / Unsupported.
                                                std::cout << "FAILED\n";
                                                std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                                else
                                {
                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }

                                // Check and see if the library supports try lock.
                                if ((bNoneUnsupportedlibrary) || (lib_status->bTryLockSupport))
                                {
                                        // Test mutex try lock.
                                        std::cout << "Testing mutex locking (Non-Blocking): ";
                                        ret = mu->Try_Lock_Mutex();

                                        // Check and see if we are testing the None / Unsupported library.
                                        if (bNoneUnsupportedlibrary)
                                        {
                                                // Check for unimplimented.
                                                if (ret == -3)
                                                {
                                                        std::cout << "PASS\n";
                                                }
                                                else
                                                {
                                                        // Error this function should be unimplimented for None / Unsupported.
                                                        std::cout << "FAILED\n";
                                                        std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                        std::cout << "Return code was: " << ret << '\n';
                                                }
                                        }
                                        else
                                        {
                                                // Check for return OK.
                                                if (ret == 0)
                                                {
                                                        std::cout << "PASS\n";

                                                        // Unlock the mutex.
                                                        std::cout << "Unlocking mutex for next test: ";
                                                        ret = mu->Unlock_Mutex();
                                                        if (!ret)
                                                        {
                                                                std::cout << "PASS\n";
                                                        }
                                                        else
                                                        {
                                                                std::cout << "FAILED\n";
                                                                std::cout << "Return code was: " << ret << '\n';
                                                        }
                                                }
                                                else
                                                {
                                                        // Error.
                                                        std::cout << "FAILED\n";
                                                        std::cout << "Return code was: " << ret << '\n';
                                                }
                                        }
                                }
                                else
                                {
                                        // Library does not support non-blocking mutex lock attempts.
                                        std::cout << "Library does not support non-blocking mutex lock attempts, Skipping test.\n";
                                }

                                // Check to see if threads are supported.
                                if ((lib_status != NULL) && (lib_status->bThreadsSupport))
                                {
                                        // Check for Try_Lock_Support.
                                        if ((lib_status != NULL) && (lib_status->bTryLockSupport))
                                        {
                                                // Test mutex locking.
                                                std::cout << "Creating thread to test mutex locking while mutex is already locked: ";

                                                // Check to see if the thread exists.
                                                if (th != NULL)
                                                {
							std::cout << "Destroying thread object: ";
							std::cout.flush();
							if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
							{
								// Success.
								std::cout << "PASS\n";
							}
							else
							{
								std::cout << "FAIL\n";
							}
                                                }

                                                // Create new thread.
                                                th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::Select_Library(our_requirements));

                                                // Check for NULL.
                                                if (th == NULL)
                                                {
                                                        // Could not create thread.
                                                        std::cout << "FAILED\n";
                                                        std::cout << "Could not create thread to run locking thread.\n";
                                                }
                                                else
                                                {
                                                        // Run thread to lock the mutex.
                                                        ret = th->Create_Thread(Test_Function_Mutex_Lock, &rm, &pid);

                                                        // Check for success.
                                                        if (ret != 0)
                                                        {
                                                                // Could not run thread.
                                                                std::cout << "FAILED\n";
                                                                std::cout << "Could not run locking thread.\n";
                                                        }
                                                        else
                                                        {
                                                                // Tell the user the thread was created.
                                                                std::cout << "PASS\n";
                                                                std::cout << "Testing mutex locking when already locked by another thread (Should fail): ";
                                                                std::cout.flush();

                                                                // Wait a second so we don't try to lock the mutex before the other thread.
                                                                while (!rm.cont)
                                                                {
                                                                        Hacky_Delay();
                                                                        hack_delay_count++;

                                                                        // Output counter.
                                                                        std::cout << (6 - hack_delay_count) << "...";

                                                                        // Check for going over 5.
                                                                        if (hack_delay_count > 5)
                                                                        {
                                                                                // Error.
                                                                                break;
                                                                        }
                                                                }

                                                                // Reset hack_delay count.
                                                                hack_delay_count = 0;

                                                                // Check one last time.
                                                                if (!rm.cont)
                                                                {
                                                                        std::cout << "FAILED\n";
                                                                        std::cout << "Time for test to complete has expired.\n";
                                                                }
                                                                else
                                                                {
                                                                        // Attempt to lock the thread.
                                                                        ret = mu->Try_Lock_Mutex();

                                                                        // Check and see if we are testing the None / Unsupported library.
                                                                        if (bNoneUnsupportedlibrary)
                                                                        {
                                                                                // Error this function should be unimplimented for None / Unsupported.
                                                                                std::cout << "FAILED\n";
                                                                                std::cout << "This function should not be implimented for the default None / Unsupported library.\n";
                                                                                std::cout << "Return code was: " << ret << '\n';
                                                                        }
                                                                        else
                                                                        {
                                                                                // Check for return OK.
                                                                                if (ret == 1)
                                                                                {
                                                                                        // Check to see if the rc was set.
                                                                                        if (rm.rc == 1)
                                                                                        {
                                                                                                std::cout << "PASS\n";

                                                                                                /*
                                                                                                        Destroy the mutex. (Note: We are doing this to clear the library error code.
                                                                                                        (It should have returned that the try lock attempt above failed. If it returns that.))
                                                                                                */
                                                                                                std::cout << "Destroying mutex: ";
                                                                                                ret = mu->Destroy_Mutex();

                                                                                                // Check for error.
                                                                                                if (ret == 0)
                                                                                                {
                                                                                                        std::cout << "PASS\n";
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        // Error.
                                                                                                        std::cout << "FAILED\n";
                                                                                                        std::cout << "Return code was: " << ret << '\n';
                                                                                                }
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                // Error in thread.
                                                                                                std::cout << "FAILED\n";
                                                                                                std::cout << "Error occured in thread.\n";
                                                                                                std::cout << "Return code from thread was: " << rm.rc << '\n';
                                                                                        }
                                                                                }
                                                                                else
                                                                                {
                                                                                        // Error.
                                                                                        std::cout << "FAILED\n";
                                                                                        std::cout << "Return code was: " << ret << '\n';
                                                                                }
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                // Library does not support non-blocking mutex lock attempts.
                                                std::cout << "Library does NOT support non-blocking mutex lock attempts, cannot test for lock attempts while already locked. Skipping test.\n";
                                        }
                                }
                                else
                                {
                                        // Threads are NOT supported by this library, so we are unable to test Mutex locking when another thread holds the lock.
                                        std::cout << "Threads are NOT supported by this library, so we are unable to test mutex locking when another thread holds the lock. Skipping test.\n";
                                }

                                // Test get return code.
                                std::cout << "Testing retrival of last return code from the Thread_Utils library: ";
                                ret = mu->Get_Return_Code();

                                // Check and see if we are testing the None / Unsupported library.
                                if (bNoneUnsupportedlibrary)
                                {
                                        // Check for unimplimented.
                                        if (ret == -3)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error this function should be unimplimented for None / Unsupported.
                                                std::cout << "FAILED\n";
                                                std::cout << "This function should return unimplimented as that was the last return code.\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                                else
                                {
                                        // Check for return OK.
                                        if (ret == 0)
                                        {
                                                std::cout << "PASS\n";
                                        }
                                        else
                                        {
                                                // Error.
                                                std::cout << "FAILED\n";
                                                std::cout << "Return code was: " << ret << '\n';
                                        }
                                }
                        }
                }
        }

        // Destroy objects.
        if (th != NULL)
        {
		std::cout << "Destroying thread object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }
        if (mu != NULL)
        {
		std::cout << "Destroying mutex object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Mutex(&mu) == true) && (mu == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }

        // Exit function.
        return true;
}

bool Test_Condition_Variable_Support(TU_Library_Support_Status & our_requirements, const TU_Library_Support_Status * lib_status)
{
        // Init vars.
        short ret = 0;
        short hack_delay_count = 0;
        unsigned long int pid = 0;
        void * ret_from_thread = NULL;
        Common_LibraryID Library_ID_Test;
        return_me rm;
        rm.cont = false;
        rm.object = NULL;
        rm.rc = 0;

        // Init thread object.
        TU_Thread * th = NULL;

        // Init condition variable object.
        TU_Condition * cond = NULL;

        // Check and see if we are testing the None / unsupported library.
        if ((our_requirements.lib->bIsPlugin == TU_LibID_none.bIsPlugin) && (strcmp(our_requirements.lib->Name, TU_LibID_none.Name) == 0))
        {
		// We cannot test this library.
		std::cout << "Error: Test_Condition_Variable_Support() called with the dummy library. " << our_requirements.lib->Name << ' ';
		if (our_requirements.lib->bIsPlugin)
		{
			std::cout << "(Plugin)";
		}
		else
		{
			std::cout << "(Internal)";
		}
		std::cout << '\n';
		std::cout << "We cannot test this library as the base class for TU_Condition is virtual. Skipping test.\n";
        }
        else
        {
                // Check to see if we lack a lib_status struct.
                if (lib_status == NULL)
                {
			// We cannot test this library.
			std::cout << "Error: Test_Condition_Variable_Support() called without a TU_Library_Support_Status structure, for Library ID Number: " << our_requirements.lib->Name << ' ';
			if (our_requirements.lib->bIsPlugin)
			{
				std::cout << "(Plugin)";
			}
			else
			{
				std::cout << "(Internal)";
			}
			std::cout << '\n';
			std::cout << "We need a TU_Library_Support_Status structure to test the library, Skipping test.\n";
                }
                else
                {
                        // Tell user we are testing condition variable support.
                        std::cout << "Testing condition variable support.\n";

                        // Tell user we are attempting to create the class.
                        std::cout << "Creating condition variable class: ";

                        // Create condition variable object.
                        cond = Common::Thread_Utils::Create_Condition(Common::Thread_Utils::Select_Library(our_requirements));

                        // Check for NULL.
                        if (cond == NULL)
                        {
                                // Error.
                                std::cout << "FAILED\n";
                                std::cout << "ERROR\nAn error occured while initing the condition variable, aborting.\n";

                                // Output END OF TEST SECTION.
                                std::cout << END_TEST_SECTION;

                                // Exit function.
                                return false;
                        }

                        // Set rm's object pointer to cond.
                        rm.object = cond;

                        /*
                                Note: cond should be the given library.
                                Verify that the correct library was chosen.
                        */
                        Library_ID_Test = cond->Get_Thread_Library();
                        if ((Library_ID_Test.bIsPlugin != our_requirements.lib->bIsPlugin) || (strcmp(Library_ID_Test.Name, our_requirements.lib->Name) != 0))
                        {
				std::cout << "FAILED\n";
				std::cout << "ERROR, could not select library: " << our_requirements.lib->Name << ' ';
				if (our_requirements.lib->bIsPlugin)
				{
					std::cout << "(Plugin)";
				}
				else
				{
					std::cout << "(Internal)";
				}
				std::cout << '\n';
				std::cout << "Returned library was: " << Library_ID_Test.Name << ' ';
				if (Library_ID_Test.bIsPlugin)
				{
					std::cout << "(Plugin)";
				}
				else
				{
					std::cout << "(Internal)";
				}
				std::cout << '\n';
				std::cout << "Skipping library.\n\n";
                        }
                        else
                        {
                                // Previous test passed, report it.
                                std::cout << "PASS\n";

                                // Test initing the condition variable.
                                std::cout << "Initing condition variable: ";
                                ret = cond->Init_Condition();

                                // Check for return OK.
                                if (ret == 0)
                                {
                                        std::cout << "PASS\n";
                                }
                                else
                                {
                                        // Error.
                                        std::cout << "FAILED\n";
                                        std::cout << "Return code was: " << ret << '\n';
                                }

                                // Check to see if threads are supported.
                                if ((lib_status != NULL) && (lib_status->bThreadsSupport))
                                {
                                        // Check for Try_Lock_Support.
                                        if ((lib_status != NULL) && (lib_status->bTryLockSupport))
                                        {
                                                // Check to see if the thread exists.
                                                if (th != NULL)
                                                {
							std::cout << "Destroying thread object: ";
							std::cout.flush();
							if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
							{
								// Success.
								std::cout << "PASS\n";
							}
							else
							{
								std::cout << "FAIL\n";
							}
                                                }

                                                // Tell user we are creating a thread to test the condition variable.
                                                std::cout << "Creating new thread to test condition variable: ";

                                                // Create new thread.
                                                th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::Select_Library(our_requirements));

                                                // Check for NULL.
                                                if (th == NULL)
                                                {
                                                        // Could not create thread.
                                                        std::cout << "FAILED\n";
                                                        std::cout << "Could not create thread to run condition test.\n";
                                                }
                                                else
                                                {
                                                        // Run thread to test the condition variable.
                                                        ret = th->Create_Thread(Test_Function_Condition_Lock, &rm, &pid);

                                                        // Check for success.
                                                        if (ret != 0)
                                                        {
                                                                // Could not run thread.
                                                                std::cout << "FAILED\n";
                                                                std::cout << "Could not run condition thread.\n";
                                                        }
                                                        else
                                                        {
                                                                // Tell user we were successfull.
                                                                std::cout << "PASS\n";

                                                                // Wait a second before continuing to allow the new thread to catch up.
                                                                while (!rm.cont)
                                                                {
                                                                        Hacky_Delay();
                                                                        hack_delay_count++;

                                                                        // Print the count.
                                                                        std::cout << (6 - hack_delay_count) << "...";

                                                                        // If we get above 5.
                                                                        if (hack_delay_count > 5)
                                                                        {
                                                                                // Error.
                                                                                break;
                                                                        }
                                                                }

                                                                // Reset hack delay count.
                                                                hack_delay_count = 0;

                                                                // Final check.
                                                                if (!rm.cont)
                                                                {
                                                                        std::cout << "ERROR: Thread is non responsive. Test failed.\n";
                                                                }
                                                                else
                                                                {
                                                                        // Tell the user we are sending a signal.
                                                                        std::cout << "Signaling thread to continue: ";

                                                                        // Tell thread we are ready.
                                                                        ret = cond->Signal();
                                                                        if (!ret)
                                                                        {
                                                                                // Tell user we passed.
                                                                                std::cout << "PASS\n";
                                                                                std::cout << "Checking result from thread: ";
                                                                                std::cout.flush();

                                                                                // Join the thread.
                                                                                ret = th->Join_Thread(&ret_from_thread);
                                                                                if (!ret)
                                                                                {
                                                                                        // Check return.
                                                                                        if (rm.rc == 1)
                                                                                        {
                                                                                                std::cout << "PASS\n";
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                // Error.
                                                                                                std::cout << "FAILED\n";
                                                                                                std::cout << "Error occured in thread\n";
                                                                                                std::cout << "Return code from library is: " << cond->Get_Return_Code() << '\n';
                                                                                                std::cout << "Return code from thread is: " << rm.rc << '\n';
                                                                                        }
                                                                                }
                                                                                else
                                                                                {
                                                                                        // Error.
                                                                                        std::cout << "ERROR: Could not join thread.\n";
                                                                                        std::cout << "Return code from Thread_Utils is: " << ret << '\n';
                                                                                }
                                                                        }
                                                                        else
                                                                        {
                                                                                // Error.
                                                                                std::cout << "FAILED\n";
                                                                                std::cout << "Return code was: " << ret << '\n';
                                                                        }
                                                                }
                                                        }

                                                        // Reset rm.cont and rm.rc.
                                                        rm.cont = false;
                                                        rm.rc = 0;
                                                }

                                                // Check and see if the library supports wait timeouts.
                                                if (lib_status->bConditionWaitTimeoutSupport)
                                                {
                                                        // Check to see if the thread exists.
                                                        if (th != NULL)
                                                        {
								std::cout << "Destroying thread object: ";
								std::cout.flush();
								if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
								{
									// Success.
									std::cout << "PASS\n";
								}
								else
								{
									std::cout << "FAIL\n";
								}
                                                        }

                                                        // Tell user we are creating a thread to test the wait timeout condition variable.
                                                        std::cout << "Creating new thread to test wait timeouts on condition variables: ";

                                                        // Create new thread.
                                                        th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::Select_Library(our_requirements));

                                                        // Check for NULL.
                                                        if (th == NULL)
                                                        {
                                                                // Could not create thread.
                                                                std::cout << "FAILED\n";
                                                                std::cout << "Could not create thread to run condition test.\n";
                                                        }
                                                        else
                                                        {
                                                                // Run thread to test the wait timeout on the condition variable.
                                                                ret = th->Create_Thread(Test_Function_Condition_Wait_Lock, &rm, &pid);

                                                                // Check for success.
                                                                if (ret != 0)
                                                                {
                                                                        // Could not run thread.
                                                                        std::cout << "FAILED\n";
                                                                        std::cout << "Could not run condition wait thread.\n";
                                                                }
                                                                else
                                                                {
                                                                        // Tell user we were successfull.
                                                                        std::cout << "PASS\n";
                                                                        std::cout << "Waiting a few seconds to make the condition variable's wait period timeout.\n";

                                                                        // Wait a second before continuing to allow the new thread to catch up.
                                                                        while (!rm.cont)
                                                                        {
                                                                                Hacky_Delay();
                                                                                hack_delay_count++;

                                                                                // Print the count.
                                                                                std::cout << (6 - hack_delay_count) << "...";

                                                                                // If we get above 5.
                                                                                if (hack_delay_count > 5)
                                                                                {
                                                                                        // Error.
                                                                                        break;
                                                                                }
                                                                        }

                                                                        // Reset hack delay count.
                                                                        hack_delay_count = 0;

                                                                        // Final check.
                                                                        if (!rm.cont)
                                                                        {
                                                                                std::cout << "ERROR: Thread is non responsive. Test failed.\n";
                                                                        }
                                                                        else
                                                                        {
                                                                                // Tell user we are checking the result from the thread.
                                                                                std::cout << "Checking result from thread: ";
                                                                                std::cout.flush();

                                                                                // Join the thread.
                                                                                ret = th->Join_Thread(NULL);
                                                                                if (!ret)
                                                                                {
                                                                                        // Check return. (It will point to the condition variable's memory address if successfull.)
                                                                                        if (rm.rc == 1)
                                                                                        {
                                                                                                std::cout << "PASS\n";
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                // Error.
                                                                                                std::cout << "FAILED\n";
                                                                                                std::cout << "Error occured in thread.\n";
                                                                                                std::cout << "Return code from library is: " << cond->Get_Return_Code() << '\n';
                                                                                                std::cout << "Return code from thread is: " << rm.rc << '\n';
                                                                                        }
                                                                                }
                                                                                else
                                                                                {
                                                                                        // Error.
                                                                                        std::cout << "ERROR: Could not join thread.\n";
                                                                                        std::cout << "Return code from Thread_Utils is: " << ret << '\n';
                                                                                }
                                                                        }
                                                                }
                                                        }

                                                        // Reset rm.cont and rm.rc.
                                                        rm.cont = false;
                                                        rm.rc = 0;
                                                }
                                                else
                                                {
                                                        // Library does not support wait timeouts.
                                                        std::cout << "Library does NOT support wait timeouts on condition variables. Skipping Test.\n";
                                                }
                                        }
                                        else
                                        {
                                                // Library does not support non-blocking mutex lock attempts.
                                                std::cout << "Library does NOT support non-blocking mutex lock attempts, cannot test for lock attempts while already locked. Skipping test.\n";
                                        }
                                }
                                else
                                {
                                        // Threads are NOT supported by this library, so we are unable to test Mutex locking when another thread holds the lock.
                                        std::cout << "Threads are NOT supported by this library, so we are unable to test mutex locking when another thread holds the lock. Skipping test.\n";
                                }
                        }
                }
        }

        // Destroy objects.
        if (th != NULL)
        {
		std::cout << "Destroying thread object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Thread(&th) == true) && (th == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }
        if (cond != NULL)
        {
		std::cout << "Destroying condition variable object: ";
		std::cout.flush();
		if ((Common::Thread_Utils::Destroy_Condition(&cond) == true) && (cond == NULL))
		{
			// Success.
			std::cout << "PASS\n";
		}
		else
		{
			std::cout << "FAIL\n";
		}
        }

        // Exit function.
        return true;
}

void Library_Test(const Common_LibraryID & lib)
{
        // Init vars.
        bool bNoneUnsupportedlibrary = false;       // Whether or not we are testing the None / Unsupported library.

        // Check and see if we are testing the None / unsupported library.
        if ((lib.bIsPlugin == TU_LibID_none.bIsPlugin) && (strcmp(lib.Name, TU_LibID_none.Name) == 0))
        {
                bNoneUnsupportedlibrary = true;
        }

        // Init TU_Library_Support_Status Structures.
        TU_Library_Support_Status our_requirements;
        Common::Thread_Utils::Init_Library_Support_Status(&our_requirements);
        const TU_Library_Support_Status * lib_status = NULL;

        // Output START OF TEST SECTION.
        std::cout << START_TEST_SECTION;

        // Tell user what library we are testing.
	std::cout << "Testing Library ID: " << lib.Name << ' ';
	if (lib.bIsPlugin)
	{
		std::cout << "(Plugin)";
	}
	else
	{
		std::cout << "(Internal)";
	}
	std::cout << ".\n";

        // Tell user that we are getting the TU_Library_Support_Status object for the given library.
        std::cout << "Retriving TU_Library_Support_Status structure: ";

        // Check and see if we are testing None / Unsupported.
        if (bNoneUnsupportedlibrary)
        {
		std::cout << "N/A\n";
		std::cout << "Library " << lib.Name << ' ';
		if (lib.bIsPlugin)
		{
			std::cout << "(Plugin)";
		}
		else
		{
			std::cout << "(Internal)";
		}
		std::cout << " is a fake library so the support status structure is not needed.\n";
        }
        else
        {
                // Get TU_Library_Support_Status structure for this library.
                lib_status = Common::Thread_Utils::Get_Library_Stats(lib);

                // Make sure the support structure matches the library.
                if (lib_status != NULL)
                {
                        if (lib_status->lib != NULL)
                        {
                                // Check ID number and name.
                                if ((lib_status->lib->bIsPlugin == lib.bIsPlugin) && (strcmp(lib_status->lib->Name, lib.Name) == 0))
                                {
                                        std::cout << "PASS\n";
                                }
                                else
                                {
					// Error library IDs should match.
					std::cout << "FAILED\n";
					std::cout << "Incorrect TU_Library_Support_Status structure was returned.\n";
					std::cout << "Returned Library ID was: " << lib_status->lib->Name << ' ';
					if (our_requirements.lib->bIsPlugin)
					{
						std::cout << "(Plugin)";
					}
					else
					{
						std::cout << "(Internal)";
					}
					std::cout << ".\nSkipping Library.\n";

					// Output END OF TEST SECTION.
					std::cout << END_TEST_SECTION;

					// Exit function.
					return;
                                }
                        }
                        else
                        {
                                // Invalid TU_Library_Support_Status structure, LibraryID variable is not defined.
                                std::cout << "FAILED\n";
                                std::cout << "Invalid TU_Library_Support_Status structure, LibraryID variable is not defined.\n";
                                std::cout << "Skipping Library.\n";

                                // Output END OF TEST SECTION.
                                std::cout << END_TEST_SECTION;

                                // Exit function.
                                return;
                        }
                }
                else
                {
                        // Error, No TU_Library_Support_Status structure was returned by TU_Get_Library_Stats().
                        std::cout << "FAILED\n";
                        std::cout << "No TU_Library_Support_Status structure was returned by TU_Get_Library_Stats().\n";
                        std::cout << "Skipping Library.\n";

                        // Output END OF TEST SECTION.
                        std::cout << END_TEST_SECTION;

                        // Exit function.
                        return;
                }
        }

        // Set perferred library.
        our_requirements.lib = &lib;

        // Begin thread support test.
        if ((bNoneUnsupportedlibrary) || (lib_status->bThreadsSupport))
        {
                // Call test function.
                if (!Test_Thread_Support(our_requirements, lib_status))
                {
                        // Error.
                        return;
                }
        }
        else
        {
                // Library does not support threads.
                std::cout << "Library does not support threads, skipping thread tests.\n";
        }

        // Begin Mutex support test.
        if ((!bNoneUnsupportedlibrary) && (lib_status->bMutexesSupport))
        {
                // Call test function.
                if (!Test_Mutex_Support(our_requirements, lib_status))
                {
                        // Error.
                        return;
                }
        }
        else
        {
                // Library does not support mutexes.
                std::cout << "Library does not support mutexes, skipping mutex tests.\n";
        }

        // Begin condition variabale support test.
        if ((!bNoneUnsupportedlibrary) && (lib_status->bConditionVariableSupport))  // There is no way to create a base class for Condition, so None / Unsupported can not be tested.
        {
                // Call test function.
                if (!Test_Condition_Variable_Support(our_requirements, lib_status))
                {
                        // Error.
                        return;
                }
        }
        else
        {
                // Library does not support condition variables.
                std::cout << "Library does not support condition variables, skipping condition variables tests.\n";
        }

        // Output END OF TEST SECTION.
        std::cout << END_TEST_SECTION;

        // Exit function.
        return;
}

int unit_test_thread_utils_main()
{
	// Init vars.
	size_t ret = 0;
	Common_LibraryID previousLib = TU_LibID_none;
	Common_LibraryID currentLib;
	TU_Library_Support_Status noRequires;

	// Register the error log callback.
	Common::Register_Error_Log_Callback(Common_Error_Log_Callback);

	// Set the log level.
	Common::Set_Error_Log_Level(ERROR_VERBOSE);

	// Init the noRequires structure.
	Common::Thread_Utils::Init_Library_Support_Status(&noRequires);

	/*
	 * Select first library.
	 * 
	 * Will also load the plugins if any are avaiable.
	 * Do this first so that if only plugins are supported on this build,
	 * the check for a library to test will succeed.
	 * 
	 * (Get_Number_of_Supported_Thread_Libraries() will only return the
	 *  number of internaly supported libraries until the plugins are
	 *  actually loaded by Select_Library().)
	 */
	currentLib = Common::Thread_Utils::Select_Library(noRequires);

	// Get number of supported libraries.
	ret = Common::Thread_Utils::Get_Number_of_Supported_Thread_Libraries();

	// Check to see if we have any libraries to actually test with.
	if (ret > 1)
	{
		// Output all supported threading libraries. (Will also output the plugins if applicable.)
		Output_All_Supported_Threading_Libraries();

		// Call tests for perferred library setting in Thread_Utils::Select_Library().
		Test_Select_Library_Perferred_Library_Setting();

		// Run basic thread test.
		Basic_Thread_Test();

		// For each supported library run tests on them.
		for (size_t x = 0; (x < ret); x++)
		{
			// Run library test.
			Library_Test(currentLib);

			// Get a new library.
			previousLib = currentLib;
			currentLib = Common::Thread_Utils::Select_Library(noRequires, previousLib);
		}
	}
	else
	{
		// There are no libraries to test with, so we cannot run tests on Thread_Utils.
		std::cout << "Subsystem Test N/A: Unable to run tests on the Threading Subsystem as we do not have any libraries to test with.\n\n";
	}

	// Clear the error log callback.
	Common::Register_Error_Log_Callback(NULL);

	// Exit test.
	return 0;
}
