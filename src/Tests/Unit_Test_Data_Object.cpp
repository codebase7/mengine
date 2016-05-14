/*!
    Multiverse Engine Project 21/8/2012 Unit Tests Unit_Test_Data_Object.cpp

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

int Unit_Test_Data_Object()
{
        /*!
                NOTE: This function is designed to check all DataProcess::Data_Object functions to see if they work correctly.
                If any error is incountered it must be returned.

                For errors that are boolean 0 true, -1 false.

                If an error occurs that has no return code, (function returns void), add the error to the list below.

                Void Error Codes:
                    -1001   DataProcess::Data_Object::set() did not correctly set data.
                    -1002   DataProcess::Data_Object::set() invalid capacity after set.
                    -1003   DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                    -1004   DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                    -1005   DataProcess::Data_Object::clear() Invalid size after clear().
                    -1006   DataProcess::Data_Object::clear() Invalid capacity after clear().
                    -1007   DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                    -1008   DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                    -1009   DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string.
                    -1010   DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                    -1011   DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= char.
                    -1012   DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= char.
                    -1013   DataProcess::Data_Object::operator= char invalid char data after call to operator= char.
                    -1014   DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                    -1015   DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                    -1016   DataProcess::Data_Object::Data_Compare() Comparasion failed should have passed.
                    -1017   DataProcess::Data_Object::Data_NCompare() Comparasion passed should have failed.
                    -1018   DataProcess::Data_Object::Data_Compare() Comparasion passed should have failed.
                    -1019   DataProcess::Data_Object::Data_NCompare() Comparasion failed should have passed.
					-1020   DataProcess::Data_Object::Compare() Comparasion failed should have passed.
                    -1021   DataProcess::Data_Object::NCompare() Comparasion passed should have failed.
                    -1022   DataProcess::Data_Object::Compare() Comparasion passed should have failed.
                    -1023   DataProcess::Data_Object::NCompare() Comparasion failed should have passed.
                    -1024   DataProcess::Data_Object::insert() Could not insert data (returned 0).
					-1025	DataProcess::Data_Object::Shallow_Copy() failed.
					-1026	DataProcess::Data_Object::Shallow_Copy() made a deep copy of the source object.

                    -9001   Could not get pointer to string object.


                    Currently Implimented tests:
                        set()
                        clear()
                        size()
                        get_Pointer()
                        get_Capacity()
                        operator= (char)
                        operator= (std::string)
                        operator= (DataProcess::Data_Object)
						Compare()
						NCompare()
                        Data_Compare()
                        Data_NCompare()
                        reserve()
                        operator+= (char)
                        operator+= (std::string)
                        insert (char)

                    Need to be added.
                        operator+= (DataProcess::Data_Object)
                        Buffer_Copy()
                        get_Copy()
                        get_length()
                        reset()
                        substr()
                        insert (std::string)
                        insert (DataProcess::Data_Object)
						replace (char)
						replace (std::string)
						replace (DataProcess::Data_Object)
        */

        // Test data objects.
        DataProcess::Data_Object test_object_1;
        DataProcess::Data_Object test_object_2;

        // Hard coded test vars.
        const std::string s1 = "Junk_Data";
        const std::string s2 = "Is_Not";
        const std::string s3 = "Why_is_it";
        const char c1 = 'P';

        const char * p1 = NULL;
        const char * p2 = NULL;

		/* Result from Insert_Char test. */
		int ret_Insert_Char = 0;

        // First test DataProcess::Data_Object.

        /*
                DataProcess::Data_Object::set() Test

                This test checks the DataProcess::Data_Object::set() function.
                The result should be that test_object_1's length, capacity and actual data
                equals s1.
        */

        // Test Data_Object::set.
        test_object_1.set(s1.c_str(), s1.size());

        // Check the data length.
        if (test_object_1.size() != s1.size())
        {
                // DataProcess::Data_Object::set() did not correctly set data.
                return -1001;
        }

        // Check capacity.
        if (test_object_1.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::set() invalid capacity after set.
                return -1002;
        }

        // Check data.
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Reset pointers.
        p1 = NULL;
        p2 = NULL;

        // Test Data_Object::clear().
        test_object_1.clear();

        // Check size and capacity.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        /*
            OK DataProcess::Data_Object::set() works, as well as DataProcess::Data_Object::size()
            DataProcess::Data_Object::get_Pointer(), DataProcess::Data_Object::get_Capacity() and
            DataProcess::Data_Object::clear().
        */

        /*
                DataProcess::Data_Object::reserve() Test 1

                This test checks the DataProcess::Data_Object::reserve() function. Allocating memory when no
                other data is present in the data object.

                The result should be that the capacity is equal to s2, and the size equal to zero (0).
        */

        // Check the reserve function test 1, result should be that the capacity is equal to s2, and the size equal to zero (0).
        test_object_1.reserve(s2.size());

        // Check the capacity.
        if (test_object_1.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Check the size.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                return -1008;
        }

        // Clear the data_object.
        test_object_1.clear();

        /*
                DataProcess::Data_Object::reserve() Test 2

                This test checks the DataProcess::Data_Object::reserve() function.

                This test will try using reserve() to reserve memory for s2 in test_object_2,
                then attempt to += (concat) s2 into it.

                The result should be that test_object_2 will have a capacity and size (length) equal
                to s2's size, and that test_object_2 will have the same data as s2 in it.
        */

        // Reserve enough memory to add s2.
        test_object_2.reserve(s2.size());

        // Make sure the memory was allocated.
        if (test_object_2.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Check the size of test_object_2 should be zero (0).
        if (test_object_2.size() != 0)
        {
                // DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                return -1008;
        }

        // Now attempt to concat ( += ) s2.
        test_object_2 += s2;

        // Check for a changed capacity.
        if (test_object_2.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string.
                return -1009;
        }

        // Check the size of test_object_2 should be equal to s2.
        if (test_object_2.size() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                return -1010;
        }

        // Clear test_object_2.
        test_object_2.clear();

        /*
                DataProcess::Data_Object::reserve() Test 3

                This test checks the DataProcess::Data_Object::reserve() function.

                This test will try using reserve() to reserve memory for s2 in test_object_2,
                then attempt to += (concat) s2 into it, then the test will attempt to allocate
                more memory to store s1 in it.

                The result should be that test_object_2 should have the capacity of s1 + s2.
                while having the length and actual data of s2.
        */

        // Clear test_object_2.
        test_object_2.clear();

        // Make sure that test_object_2 is empty.
        if (test_object_2.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_2.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Reserve enough memory to add s2.
        test_object_2.reserve(s2.size());

        // Make sure the memory was allocated.
        if (test_object_2.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Check the size of test_object_2 should be zero (0).
        if (test_object_2.size() != 0)
        {
                // DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                return -1008;
        }

        // Now attempt to concat ( += ) s2.
        test_object_2 += s2;

        // Check for a changed capacity.
        if (test_object_2.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string.
                return -1009;
        }

        // Check the size of test_object_2 should be equal to s2.
        if (test_object_2.size() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                return -1010;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s2.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < test_object_2.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Reserve enough memory to add s1.
        test_object_2.reserve((s1.size()) + (s2.size()));

        // Make sure the memory was allocated.
        if (test_object_2.get_Capacity() != ((s1.size()) + (s2.size())))
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Check the size of test_object_2 should be equal to s2.
        if (test_object_2.size() != s2.size())
        {
                // DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                return -1010;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s2.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < s2.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Clear test_object_2.
        test_object_2.clear();

        // Make sure that test_object_2 is empty.
        if (test_object_2.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_2.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        /*
                Operator= char Test

                This test checks the DataProcess::Data_Object::operator= char function.

                The result should be that test_object_1 should have a size and capacity of 1.
                With test_object_1's actual data as P.
        */

        // Clear the test object.
        test_object_1.clear();

        // Make sure that test_object_1 is empty.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set the char.
        test_object_1 = c1;

        // Make sure that test_object_1's size and capacity are equal to s1.
        if (test_object_1.size() != 1)
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= char.
                return -1011;
        }
        if (test_object_1.get_Capacity() != 1)
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= char.
                return -1012;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Check and see if the char is equal to c1.
        if (p1[0] != c1)
        {
                // DataProcess::Data_Object::operator= char invalid char data after call to operator= char.
                return -1013;
        }

        // Clear test_object_1.
        test_object_1.clear();

        // Make sure that test_object_1 is empty.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        /*
                Operator= std::string Test

                This test checks the DataProcess::Data_Object::operator= std::string function.

                The result should be that test_object_1 should have the same size, capacity and actual data as s3.
        */

        // Clear test_object_1.
        test_object_1.clear();

        // Make sure that test_object_1 is empty.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set test_object_1 to s1.
        test_object_1 = s1;

        // Make sure that test_object_1's size and capacity are equal to s1.
        if (test_object_1.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Clear test_object_1.
        test_object_1.clear();

        // Make sure that test_object_1 is empty.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        /*
                Operator= Data_Object Test.

                This test checks the DataProcess::Data_Object::operator= Data_Object function.

                The result should be that test_object_1 should have the same size, capacity and actual data as test_object_2
                which has the same size, capacity and actual data as s2.
        */

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set test_object_2 to s2.
        test_object_2 = s2;

        // Make sure that test_object_2's size and capacity are equal to s2.
        if (test_object_2.size() != s2.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_2.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s2.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < test_object_2.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Now set test_object_1 equal to test_object_2.
        test_object_1 = test_object_2;

        // Make sure that test_object_1's size and capacity are equal to test_object_2.
        if (test_object_1.size() != test_object_2.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != test_object_2.get_Capacity())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer for test_object_2.
        p2 = NULL;
        if ((p2 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        /*
                Operator+= char Test

                This test checks the DataProcess::Data_Object::operator+= (char) function.

                This test sets test_object_1 to equal s1. Then the test attempts to add c1 to it.

                The result should be test_object_1 has the size and capacity of s1 + c1, and has the
                data contents of s1 + c1 in that order.
        */

        // Clear test_object_1.
        test_object_1.clear();

        // Make sure that test_object_1 is empty.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set test_object_1 to s1.
        test_object_1 = s1;

        // Make sure that test_object_1's size and capacity are equal to s1.
        if (test_object_1.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Attempt to add c1 to test_object_1.
        test_object_1 += c1;

        // Make sure that test_object_1's size and capacity are equal to s1 + 1.
        if (test_object_1.size() != ((s1.size()) + 1))
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != ((s1.size()) + 1))
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if ((x + 1) == test_object_1.size())
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }
                else
                {
                        if (p1[x] != p2[x])
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }
        }

        // Clear test_object_1.
        test_object_1.clear();

        // Make sure that test_object_1 is empty.
        if (test_object_1.size() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if (test_object_1.get_Capacity() != 0)
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        /*
                Data Compare test 1

                This test checks the DataProcess::Data_Object::Data_Compare() and DataProcess::Data_Object::Data_NCompare() functions
                to see if they return correct values for equal DataProcess::Data_Objects.

                This test uses s1.

                The result should be Data_Compare() = true,
                                     Data_NCompare() = false.
        */

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set both test_objects to s1.
        test_object_1 = s1;
        test_object_2 = s1;

        // Make sure that test_object_1's size and capacity are equal to s1.
        if (test_object_1.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Make sure that test_object_2's size and capacity are equal to s1.
        if (test_object_2.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_2.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Now run the Data Compare function.
        if (!(test_object_1.Data_Compare(test_object_2)))
        {
                // DataProcess::Data_Object::Data_Compare() Comparasion failed should have passed.
                return -1016;
        }

        // Now run the Data NCompare function.
        if (test_object_1.Data_NCompare(test_object_2))
        {
                // DataProcess::Data_Object::Data_NCompare() Comparasion passed should have failed.
                return -1017;
        }

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }


        /*
                Data Compare test 2

                This test checks the DataProcess::Data_Object::Data_Compare() and DataProcess::Data_Object::Data_NCompare() functions
                to see if they return correct values for non-equal DataProcess::Data_Objects.

                This test uses s2 and s3.

                The result should be Data_Compare() = false,
                                     Data_NCompare() = true.
        */

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set test_object_1 to s2 and test_object_2 to s3.
        test_object_1 = s2;
        test_object_2 = s3;

        // Make sure that test_object_1's size and capacity are equal to s2.
        if (test_object_1.size() != s2.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s2.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s2.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Make sure that test_object_2's size and capacity are equal to s3.
        if (test_object_2.size() != s3.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_2.get_Capacity() != s3.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s3.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Now run the Data Compare function.
        if (test_object_1.Data_Compare(test_object_2))
        {
                // DataProcess::Data_Object::Data_Compare() Comparasion passed should have failed.
                return -1018;
        }

        // Now run the Data NCompare function.
        if (!(test_object_1.Data_NCompare(test_object_2)))
        {
                // DataProcess::Data_Object::Data_NCompare() Comparasion failed should have passed.
                return -1019;
        }

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

		  /*
                Compare test 1

                This test checks the DataProcess::Data_Object::Compare() and DataProcess::Data_Object::NCompare() functions
                to see if they return correct values for deep copied DataProcess::Data_Objects.

                This test uses s1.

				(The assignment operator creates a deep copy. So the Compare() and NCompare() functions should fail.)

                The result should be Compare() = false,
                                     NCompare() = true.
        */

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set both test_objects to s1.
        test_object_1 = s1;
        test_object_2 = s1;

        // Make sure that test_object_1's size and capacity are equal to s1.
        if (test_object_1.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Make sure that test_object_2's size and capacity are equal to s1.
        if (test_object_2.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_2.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Now run the Compare function.
        if (test_object_1.Compare(test_object_2))
        {
                // DataProcess::Data_Object::Compare() Comparasion passed and should have failed.
                return -1022;
        }

        // Now run the NCompare function.
        if (!(test_object_1.NCompare(test_object_2)))
        {
                // DataProcess::Data_Object::NCompare() Comparasion failed and should have passed.
                return -1023;
        }

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

		/*
                Compare test 2

                This test checks the DataProcess::Data_Object::Compare() and DataProcess::Data_Object::NCompare() functions
                to see if they return correct values for shallow copied DataProcess::Data_Objects.

                This test uses s1.

                The result should be Compare() = true,
                                     NCompare() = false.
        */

        // Clear both test objects.
        test_object_1.clear();
        test_object_2.clear();

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Set test_object_1 to s1.
        test_object_1 = s1;

		// Shallow copy test_object_1 to test_object_2
        if (test_object_2.Shallow_Copy(test_object_1) != COMMON_ERROR_SUCCESS)
		{
			/* Shallow copy attempt failed. */
			return -1025;
		}

        // Make sure that test_object_1's size and capacity are equal to s1.
        if (test_object_1.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

        // Make sure that test_object_2's size and capacity are equal to s1.
        if (test_object_2.size() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_2.get_Capacity() != s1.size())
        {
                // DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string.
                return -1015;
        }

        // Get pointer for test_object_2.
        p1 = NULL;
        if ((p1 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

        // Get pointer to string.
        p2 = NULL;
        if ((p2 = s1.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_2 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                if (p1[x] != p2[x])
                {
                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                        return -1004;
                }
        }

		// Get pointer for test_object_1.
        p1 = NULL;
        if ((p1 = test_object_1.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

		// Get pointer for test_object_2.
        p2 = NULL;
        if ((p2 = test_object_2.get_Pointer()) == NULL)
        {
                // DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data.
                return -1003;
        }

		/* Make sure that test_object_1 & test_object_2 have the same pointer. */
		if (p1 != p2)
		{
			/* The objects have different pointers. */
			return -1026;
		}

        // Now run the Compare function.
        if (!(test_object_1.Compare(test_object_2)))
        {
                // DataProcess::Data_Object::Compare() Comparasion failed should have passed.
                return -1020;
        }

        // Now run the NCompare function.
        if (test_object_1.NCompare(test_object_2))
        {
                // DataProcess::Data_Object::NCompare() Comparasion passed should have failed.
                return -1021;
        }

        // Clear test_object_1 test objects.
        test_object_1.clear();
        test_object_2.clear();	/* ERROR: Shallow Copied data object cannot be cleared. */

        // Make sure that both test_object_1 and test_object_2 are empty.
        if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid size after clear().
                return -1005;
        }
        if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
        {
                // DataProcess::Data_Object::clear() Invalid capacity after clear().
                return -1006;
        }

        // Tell User we are starting the insert test for (char).
        std::cout << "DataProcess::Data_Object::insert() (char):        ";
		ret_Insert_Char = Unit_Test_Data_Object_Insert_char();
        if (ret_Insert_Char == 0)
        {
                std::cout << "PASS\n";
        }
        else
        {
                std::cout << "FAIL Error Code: " << ret_Insert_Char << '\n';
                return -1;
        }

        // Default return.
        return 0;
}

