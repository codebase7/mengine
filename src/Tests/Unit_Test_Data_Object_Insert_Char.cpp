/*!
    Multiverse Engine Project 22/8/2012 Unit Tests Unit_Test_Data_Object_Insert.cpp
    
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

int Unit_Test_Data_Object_Insert_char()
{
        // Init objects to test.
        DataProcess::Data_Object test_object_1;
        DataProcess::Data_Object test_object_2;

        // Hard coded test vars.
        const std::string s1 = "Junk_Data";
        const std::string s2 = "Is_Not";
        const std::string s3 = "Why_is_it";
        const char c1 = 'P';

        const char * p1 = NULL;
        const char * p2 = NULL;

        /*
                insert() char Test 1

                This test checks DataProcess::Data_Object::insert() char. (Reallocate)

                This test attempts to set test_object_1 to s1, and then insert c1 into test_object_1 at the begining.

                The result should be that test_object_1 will have the first char equal to c1 and the remaining data will be
                equal to s1. (Size and capacity should be: s1.size() + 1)
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

        // Attempt to insert data.
        if (test_object_1.insert(0, c1) != 1)
        {
                // DataProcess::Data_Object::insert() Could not insert data (returned 0).
                return -1020;
        }

        // Make sure that test_object_1's size and capacity are equal to s1.size() + 1.
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
                // Check for c1 if x = 0.
                if (x == 0)
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }

                // Check for s1 otherwise.
                else
                {
                        if (p1[x] != p2[(x - 1)])
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
                insert() char Test 2

                This test checks DataProcess::Data_Object::insert() char. (Reallocate)

                This test attempts to store s3 in test_object_1, then insert c1 at position 4.

                The result should be that test_object_1 contains s3's data up to position 4, at
                which it contains c1 and the remaining data being the remaining data from s3.
                Capacity and size equaling s3.size() + 1.
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

        // Set test_object_1 to s3.
        test_object_1 = s3;

        // Make sure that test_object_1's size and capacity are equal to s3.
        if (test_object_1.size() != s3.size())
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != s3.size())
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
        if ((p2 = s3.c_str()) == NULL)
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

        // Attempt to insert data.
        if (test_object_1.insert(4, c1) != 1)
        {
                // DataProcess::Data_Object::insert() Could not insert data (returned 0).
                return -1020;
        }

        // Make sure that test_object_1's size and capacity are equal to s3.size() + 1.
        if (test_object_1.size() != ((s3.size()) + 1))
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != ((s3.size()) + 1))
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
        if ((p2 = s3.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                // Check for c1 if x = 4.
                if (x == 4)
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }

                // Check for s3 otherwise.
                else
                {
                        if (x < 4)
                        {
                                if (p1[x] != p2[x])
                                {
                                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                        return -1004;
                                }
                        }
                        if (x > 4)
                        {
                                if (p1[x] != p2[(x - 1)])
                                {
                                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                        return -1004;
                                }
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
                insert() char Test 3

                This test checks DataProcess::Data_Object::insert() char. (Reallocate)

                This test attempts to store s2 in test_object_1, then insert c1 at the end.

                The result should be that test_object_1 contains s2's data and at the end it
                contains c1. Capacity and size equaling s2.size() + 1.
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

        // Set test_object_1 to s2.
        test_object_1 = s2;

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

        // Attempt to insert data.
        if (test_object_1.insert((s2.size()), c1) != 1)
        {
                // DataProcess::Data_Object::insert() Could not insert data (returned 0).
                return -1020;
        }

        // Make sure that test_object_1's size and capacity are equal to s2.size() + 1.
        if (test_object_1.size() != ((s2.size()) + 1))
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != ((s2.size()) + 1))
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
                // Check for c1 if x = s2.size().
                if (x == s2.size())
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }

                // Check for s2 otherwise.
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
                insert() char Test 4

                This test checks DataProcess::Data_Object::insert() char. (Non-Reallocate)

                This test attempts to reserve memory with the length of s3 + 1, then store
                (concat) s3 in test_object_1, and then insert c1 into test_object_1 at the beginning.

                The result should be that test_object_1 will have the first char equal to c1 and the remaining data will be
                equal to s3. (Size and capacity should be: s3.size() + 1)
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

        // Reserve memory for s3.size() + 1.
        test_object_1.reserve((s3.size() + 1));

        // Check for reserved memory.
        if (test_object_1.size() != 0)
        {
                    //  DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                    return -1008;
        }
        if (test_object_1.get_Capacity() != (s3.size() + 1))
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Concat s3 into test_object_1.
        test_object_1 += s3;

        // Make sure that test_object_1's size is equal to s3, and capacity are equal to s3.size() + 1.
        if (test_object_1.size() != s3.size())
        {
                    // DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                    return -1010;
        }
        if (test_object_1.get_Capacity() != (s3.size() + 1))
        {
                    // DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string.
                    return -1009;
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
        if ((p2 = s3.c_str()) == NULL)
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

        // Attempt to insert data.
        if (test_object_1.insert(0, c1) != 1)
        {
                // DataProcess::Data_Object::insert() Could not insert data (returned 0).
                return -1020;
        }

        // Make sure that test_object_1's size and capacity are equal to s3.size() + 1.
        if (test_object_1.size() != ((s3.size()) + 1))
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != ((s3.size()) + 1))
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
        if ((p2 = s3.c_str()) == NULL)
        {
                // Could not get pointer to string object.
                return -9001;
        }

        // Make sure that test_object_1 actually contains the correct data.
        for (size_t x = 0; x < test_object_1.size(); x++)
        {
                // Check for c1 if x = 0.
                if (x == 0)
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }

                // Check for s3 otherwise.
                else
                {
                        if (p1[x] != p2[(x - 1)])
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
                insert() char test 5

                This test checks DataProcess::Data_Object::insert() char. (Non-Reallocate)

                This test attempts to reserve memory with the length of s1 + 1, then store
                (concat) s1 in test_object_1, then insert c1 at position 3.

                The result should be that test_object_1 contains s1's data up to position 3,
                at which it contains c1 and the remaining data is s1's remaining data.
                Capacity and size equaling s1.size() + 1.
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

        // Reserve memory for s1.size() + 1.
        test_object_1.reserve((s1.size() + 1));

        // Check for reserved memory.
        if (test_object_1.size() != 0)
        {
                    //  DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                    return -1008;
        }
        if (test_object_1.get_Capacity() != (s1.size() + 1))
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Concat s1 into test_object_1.
        test_object_1 += s1;

        // Make sure that test_object_1's size is equal to s1, and capacity are equal to s1.size() + 1.
        if (test_object_1.size() != s1.size())
        {
                    // DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                    return -1010;
        }
        if (test_object_1.get_Capacity() != (s1.size() + 1))
        {
                    // DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string.
                    return -1009;
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

        // Attempt to insert data.
        if (test_object_1.insert(3, c1) != 1)
        {
                // DataProcess::Data_Object::insert() Could not insert data (returned 0).
                return -1020;
        }

        // Make sure that test_object_1's size and capacity are equal to s1.size() + 1.
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
                // Check for c1 if x = 3.
                if (x == 3)
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }

                // Check for s1 otherwise.
                else
                {
                        if (x < 3)
                        {
                                if (p1[x] != p2[x])
                                {
                                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                        return -1004;
                                }
                        }
                        if (x > 3)
                        {
                                if (p1[x] != p2[(x - 1)])
                                {
                                        // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                        return -1004;
                                }
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
                insert() char Test 6

                This test checks DataProcess::Data_Object::insert() char. (Non-Reallocate)

                This test attempts to reserve memory with the length of s2 + 1, then store
                (concat) s2 in test_object_1, then insert c1 at the end.

                The result should be that test_object_1 contains s2's data and at the end it
                contains c1. Capacity and size equaling s2.size() + 1.
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

        // Reserve memory for s2.size() + 1.
        test_object_1.reserve((s2.size() + 1));

        // Check for reserved memory.
        if (test_object_1.size() != 0)
        {
                    //  DataProcess::Data_Object::reserve() Invalid size after call to reserve().
                    return -1008;
        }
        if (test_object_1.get_Capacity() != (s2.size() + 1))
        {
                // DataProcess::Data_Object::reserve() Invalid capacity after call to reserve().
                return -1007;
        }

        // Concat s2 into test_object_1.
        test_object_1 += s2;

        // Make sure that test_object_1's size is equal to s2, and capacity are equal to s2.size() + 1.
        if (test_object_1.size() != s2.size())
        {
                    // DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string.
                    return -1010;
        }
        if (test_object_1.get_Capacity() != (s2.size() + 1))
        {
                    // DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string.
                    return -1009;
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

        // Attempt to insert data.
        if (test_object_1.insert((s2.size()), c1) != 1)
        {
                // DataProcess::Data_Object::insert() Could not insert data (returned 0).
                return -1020;
        }

        // Make sure that test_object_1's size and capacity are equal to s2.size() + 1.
        if (test_object_1.size() != ((s2.size()) + 1))
        {
                // DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string.
                return -1014;
        }
        if (test_object_1.get_Capacity() != ((s2.size()) + 1))
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
                // Check for c1 if x = s2.size().
                if (x == s2.size())
                {
                        if (p1[x] != c1)
                        {
                                // DataProcess::Data_Object (Manual compare) Invalid data in the data_object.
                                return -1004;
                        }
                }

                // Check for s2 otherwise.
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

        // Exit function.
        return 0;
}
