/*!
    Multiverse Engine Project 07/7/2016 Unit Tests Unit_Test_Data_Object_Insert_Replace_Overwrite.cpp

    Copyright (C) 2016 Multiverse Engine Project

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

typedef struct Unit_Test_Data_Object_Char_Funct_Test {
	int (*fp)(MSYS_DataObject_T * obj, const size_t offset, const char data);	/* Function pointer to char function to test. */
	char * functName;		/* Human readable name of the function to test. */
	bool isInsert;			/* Whether or not the function to test inserts data into the given data object, or if it changes existing data. */
	bool canReallocate;		/* Whether or not the function can reallocate the given Data Object's memory buffer. */
} Unit_Test_Data_Object_Char_Funct_Test_T;

/* Define functions to test. */
const Unit_Test_Data_Object_Char_Funct_Test_T Unit_Test_Data_Process_Char_Functions_To_Test[] = {
	{MSYS_DataObject_Insert_Char, "MSYS_DataObject_Insert_Char", true, true},
	{MSYS_DataObject_Insert_Char_No_Allocaton, "MSYS_DataObject_Insert_Char_No_Allocaton", true, false},
	{MSYS_DataObject_Replace_With_Char, "MSYS_DataObject_Replace_With_Char", false, false},
	{MSYS_DataObject_Overwrite_With_Char, "MSYS_DataObject_Overwrite_With_Char", false, true}
};

int Unit_Test_Data_Object_Insert_Replace_Overwrite_Char()
{
		/* Init retFromCall */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

        /* Init objects to test. */
		DataProcess::Data_Object test_object_1;
		DataProcess::Data_Object test_object_2;
		MSYS_DataObject * test_object_1_c_ptr = NULL;
		MSYS_DataObject * test_object_2_c_ptr = NULL;

        /* Hard coded test vars. */
        const std::string s1 = "Junk_Data";
        const std::string s2 = "Is_Not";
        const std::string s3 = "Why_is_it";
        const char c1 = 'P';

        const char * p1 = NULL;
        const char * p2 = NULL;
		int y = 2;

		/* Get the pointers for the C objects. */
		retFromCall = test_object_1.get_C_Struct(&test_object_1_c_ptr);
		if (retFromCall != COMMON_ERROR_SUCCESS)
		{
			/* Could not get test_object C struct pointer. */
			return -1;
		}
		retFromCall = test_object_2.get_C_Struct(&test_object_2_c_ptr);
		if (retFromCall != COMMON_ERROR_SUCCESS)
		{
			/* Could not get test_object C struct pointer. */
			return -1;
		}

		/* Send newline to output. */
		std::cout << '\n';
		std::cout.flush();

		/* Begin test loop. */
		for (y = 0; y < (sizeof(Unit_Test_Data_Process_Char_Functions_To_Test) / sizeof(Unit_Test_Data_Object_Char_Funct_Test_T)); y++)
		{
			/* Output name of function we are testing. */
			std::cout << Unit_Test_Data_Process_Char_Functions_To_Test[y].functName << "() Tests: ";
			std::cout.flush();

			/*
					Char Test 1

					This test checks a char function for MSYS_DataObjects. (Reallocate)

					This test attempts to set test_object_1 to s1, and then run the test function with an offset of 0 and
					the data of c1.

					The result for a non insert function should be that test_object_1 will have the first char equal to c1
					and the remaining data will be equal to s1 NOT including the first char of s1. (Size and capacity should be: s1.size().)

					The result for an insert function should be that test_object_1 will have the first char equal to c1
					and the remaining data will be equal to s1 including the first char of s1. (Size and capacity should be: s1.size() + 1.)
			*/

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Set test_object_1 to s1. */
			test_object_1 = s1;

			/* Make sure that test_object_1's size and capacity are equal to s1. */
			if (test_object_1.size() != s1.size())
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != s1.size())
			{
					/* DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string. */
					return -1015;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s1.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Attempt to replace data. */
			if (Unit_Test_Data_Process_Char_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, c1) !=
				((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
					/* Insert No Allocation function should return buffer too small here. All other functions should return success. */
					((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (COMMON_ERROR_SUCCESS) : (COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL)) :
					(COMMON_ERROR_SUCCESS)))
			{
					/* Test function failed. */
					return -1020;
			}

			/* Make sure that test_object_1's size and capacity are equal to s1.size() + 1. */
			if (test_object_1.size() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (s1.size() + 1) : (s1.size())) :
				(s1.size())))
			{
					/* Invalid size after call to test function. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (s1.size() + 1) : (s1.size())) :
				(s1.size())))
			{
					/* Invalid capacity after call to test function. */
					return -1015;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s1.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/* Check for c1 if x = 0. */
					if (x == 0)
					{
							if (p1[x] != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
									/* Only Insert No Allocation should check for the data from p2 here, all other functions should check for c1. */
									((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (c1) : (p2[x])) :
									(c1)))
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}

					/* Check for s1 otherwise. */
					else
					{
							if (p1[x] != p2[((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
								((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (x - 1) : (x)) :
								(x))])
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}
			}

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
					Replace() char Test 2

					This test checks a char function for MSYS_DataObjects. (Reallocate)

					This test attempts to store s3 in test_object_1, then run the test function with an offset of
					position 4 and the data of c1.

					The result for a non insert function should be that test_object_1 contains s3's data up to position 4, at
					which point it contains c1 followed by the data from s3 at position 5 onward.
					Capacity and size equaling s3.size().

					The result for an insert function should be that test_object_1 contains s3's data up to position 4, at
					which point it contains c1 followed by the data from s3 at position 4 onward.
					Capacity and size equaling s3.size() + 1.
			*/

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Set test_object_1 to s3. */
			test_object_1 = s3;

			/* Make sure that test_object_1's size and capacity are equal to s3. */
			if (test_object_1.size() != s3.size())
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != s3.size())
			{
					/* DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string. */
					return -1015;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s3.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Attempt to replace data. */
			if (Unit_Test_Data_Process_Char_Functions_To_Test[y].fp(test_object_1_c_ptr, 4, c1) !=
				((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
				/* Insert No Allocation function should return buffer too small here. All other functions should return success. */
					((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (COMMON_ERROR_SUCCESS) : (COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL)) :
					(COMMON_ERROR_SUCCESS)))
			{
					/* Test function failed. */
					return -1020;
			}

			/* Make sure that test_object_1's size and capacity are equal to s3.size(). */
			if (test_object_1.size() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (s3.size() + 1) : (s3.size())) :
				(s3.size())))
			{
					/* Invalid size after call to test function. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (s3.size() + 1) : (s3.size())) :
				(s3.size())))
			{
					/* Invalid capacity after call to test function. */
					return -1015;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s3.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/* Check for c1 if x = 4. */
					if (x == 4)
					{
							if (p1[x] != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
								/* Only Insert No Allocation should check for the data from p2 here, all other functions should check for c1. */
									((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (c1) : (p2[x])) :
									(c1)))
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}

					/* Check for s3 otherwise.

						Fix this, the multiple IFs are not needed. use a conditional.
					*/
					else
					{
							if (x < 4)
							{
									if (p1[x] != p2[x])
									{
											/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
											return -1004;
									}
							}
							if (x > 4)
							{
									if (p1[x] != p2[((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ?
										((Unit_Test_Data_Process_Char_Functions_To_Test[y].canReallocate) ? (x - 1) : (x)) :
										(x))])
									{
											/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
											return -1004;
									}
							}
					}
			}

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
					Char Test 3

					This test checks a char function for MSYS_DataObjects. (Non-Reallocate)

					This test attempts to reserve memory with the length of s3, then store
					(concat) s3 in test_object_1, and then run the test function with an offset of 0 and the data of c1.

					The result for a non insert function should be that test_object_1 will have the first char equal to c1 and the remaining data will be
					equal to s3 not including the first char of s3. (Size and capacity should be: s3.size().)

					The result for an insert function should be that test_object_1 will have the first char equal to c1 and the remaining data will be
					equal to s3 including the first char. (Size and capacity should be: s3.size() + 1.)
			*/

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Reserve memory for s3.size(). */
			test_object_1.reserve(((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s3.size() + 1) : (s3.size())));

			/* Check for reserved memory. */
			if (test_object_1.size() != 0)
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to reserve(). */
						return -1008;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s3.size() + 1) : (s3.size())))
			{
					/* DataProcess::Data_Object::reserve() Invalid capacity after call to reserve(). */
					return -1007;
			}

			/* Concat s3 into test_object_1. */
			test_object_1 += s3;

			/* Make sure that test_object_1's size and capacity are equal to s3. */
			if (test_object_1.size() != s3.size())
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string. */
						return -1010;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s3.size() + 1) : (s3.size())))
			{
						/* DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string. */
						return -1009;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s3.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Attempt to replace data. */
			if (Unit_Test_Data_Process_Char_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, c1) != COMMON_ERROR_SUCCESS)
			{
					/* DataProcess::Data_Object::Replace() Could not replace data. */
					return -1020;
			}

			/* Make sure that test_object_1's size and capacity are equal to s3.size(). */
			if (test_object_1.size() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s3.size() + 1) : (s3.size())))
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s3.size() + 1) : (s3.size())))
			{
					/* DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string. */
					return -1015;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s3.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/* Check for c1 if x = 0. */
					if (x == 0)
					{
							if (p1[x] != c1)
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}

					/* Check for s3 otherwise. */
					else
					{
							if (p1[x] != p2[((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (x - 1) : (x))])
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}
			}

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
					Char test 4

					This test checks a char function for MSYS_DataObjects. (Non-Reallocate)

					This test attempts to reserve memory with the length of s1, then store
					(concat) s1 in test_object_1, then run the test function with an offset of position 3 and data of c1.

					The result should be for a non insert function, that test_object_1 contains s1's data up to position 3,
					at which it contains c1, and the remaining data is s1's remaining data after position 3.
					Capacity and size equaling s1.size().

					The result should be for a insert function, that test_object_1 contains s1's data up to position 3,
					at which it contains c1, and the remaining data is s1's remaining data including position 3.
					Capacity and size equaling s1.size() + 1.
			*/

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Reserve memory for s1.size(). */
			test_object_1.reserve(((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s1.size() + 1) : (s1.size())));

			/* Check for reserved memory. */
			if (test_object_1.size() != 0)
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to reserve(). */
						return -1008;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s1.size() + 1) : (s1.size())))
			{
					/* DataProcess::Data_Object::reserve() Invalid capacity after call to reserve(). */
					return -1007;
			}

			/* Concat s1 into test_object_1. */
			test_object_1 += s1;

			/* Make sure that test_object_1's size and capacity are equal to s1. */
			if (test_object_1.size() != s1.size())
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string. */
						return -1010;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s1.size() + 1) : (s1.size())))
			{
						/* DataProcess::Data_Object::reserve() Invalid capacity after call to operator+= std::string. */
						return -1009;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s1.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Attempt to replace data. */
			if (Unit_Test_Data_Process_Char_Functions_To_Test[y].fp(test_object_1_c_ptr, 3, c1) != COMMON_ERROR_SUCCESS)
			{
					/* DataProcess::Data_Object::Replace() Could not replace data. */
					return -1020;
			}

			/* Make sure that test_object_1's size and capacity are equal to s1.size(). */
			if (test_object_1.size() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s1.size() + 1) : (s1.size())))
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (s1.size() + 1) : (s1.size())))
			{
					/* DataProcess::Data_Object::operator= Invalid capacity after call to DataProcess::Data_Object::operator= std::string. */
					return -1015;
			}

			/* Get pointer for test_object_1. */
			p1 = NULL;
			if ((p1 = test_object_1.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s1.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/* Check for c1 if x = 3. */
					if (x == 3)
					{
							if (p1[x] != c1)
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}

					/* Check for s1 otherwise. */
					else
					{
							if (x < 3)
							{
									if (p1[x] != p2[x])
									{
											/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
											return -1004;
									}
							}
							if (x > 3)
							{
									if (p1[x] != p2[((Unit_Test_Data_Process_Char_Functions_To_Test[y].isInsert) ? (x - 1) : (x))])
									{
											/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
											return -1004;
									}
							}
					}
			}

			/* Clear test_object_1. */
			test_object_1.clear();

			/* Make sure that test_object_1 is empty. */
			if (test_object_1.size() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if (test_object_1.get_Capacity() != 0)
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Output result of tests. */
			std::cout << "PASS\n";
			std::cout.flush();

		}	/* End test loop. */

        /* Exit function. */
        return 0;
}
