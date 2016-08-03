/*!
    Multiverse Engine Project 29/7/2016 Unit Tests Unit_Test_Data_Object_Insert_Replace_Overwrite_Data_Object.cpp

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

/* Internal includes. */
#include "Unit_Tests.h"

/* Special include for manually creating invalid MSYS_DataObject structures. (DON'T DO THIS AT HOME KIDS. Use the factories and public functions instead!)*/
#include "../Core/Src/Data_Object/Data_Object_Private_Structure.c"

/* Define test structure for Data_Object function variants. */
typedef struct Unit_Test_Data_Object_From_Data_Object_Funct_Test {
	int (*fp)(MSYS_DataObject_T * obj, const size_t offset, const MSYS_DataObject_T * src);	/* Function pointer to Data_Object function to test. */
	char * functName;		/* Human readable name of the function to test. */
	bool isInsert;			/* Whether or not the function to test inserts data into the given data object, or if it changes existing data. */
	bool canReallocate;		/* Whether or not the function can reallocate the given dest Data Object's memory buffer. */
} Unit_Test_Data_Object_From_Data_Object_Funct_Test_T;

/* Define functions to test for Data_Object function variants. */
const Unit_Test_Data_Object_From_Data_Object_Funct_Test_T Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[] = {
	{MSYS_DataObject_Insert_From_DataObject, "MSYS_DataObject_Insert_From_DataObject", true, true},
	{MSYS_DataObject_Insert_From_DataObject_No_Allocaton, "MSYS_DataObject_Insert_From_DataObject_No_Allocaton", true, false},
	{MSYS_DataObject_Replace_With_DataObject, "MSYS_DataObject_Replace_With_DataObject", false, false},
	{MSYS_DataObject_Overwrite_With_DataObject, "MSYS_DataObject_Overwrite_With_DataObject", false, true}
};

int Unit_Test_Data_Object_Insert_Replace_Overwrite_Data_Object()
{
		/* Init retFromCall */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

        /* Init objects to test. */
		DataProcess::Data_Object test_object_1;
		DataProcess::Data_Object test_object_2;
		MSYS_DataObject * test_object_1_c_ptr = NULL;
		MSYS_DataObject * test_object_2_c_ptr = NULL;
		void * pbadPrivPtr = NULL;	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject badPrivPtr = { &pbadPrivPtr };	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject_Private badDataPriv = { NULL, 1, 1, 0};	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject_Private badLengthPriv = { "Bad_STR", SIZE_MAX, 7, 0};	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject_Private badCapacityPriv = { "Bad_STR", 7, 3, 0};	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		void * pbadData = &badDataPriv;	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		void * pbadLength = &badLengthPriv;	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		void * pbadCapacity = &badCapacityPriv;	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject badData = { &pbadData };	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject badLength = { &pbadLength };	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */
		MSYS_DataObject badCapacity = { &pbadCapacity };	/* <---- DON'T DO THIS AT HOME KIDS. This is for testing purposes only. */

        /* Hard coded test vars. */
        const std::string s1 = "Junk_Data";
        const std::string s2 = "Is_Not";
        const std::string s3 = "Why_is_it";
        const char c1 = 'P';

        const char * p1 = NULL;
        const char * p2 = NULL;
		const char * p3 = NULL;	/* Used for comparing data from both data objects. */
		int y = 0;

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
		for (y = 0; y < (sizeof(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test) / sizeof(Unit_Test_Data_Object_From_Data_Object_Funct_Test_T)); y++)
		{
			/* Output name of function we are testing. */
			std::cout << Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].functName << "() Tests: ";
			std::cout.flush();

			/*
					Data_Object Test 1

					This test checks a char function for MSYS_DataObjects. (Reallocate)

					This test attempts to set test_object_1 to s1, test_object_2 to s2, and then run the test function with an offset of 0 and
					the data of test_object_2.

					The result for a non insert function should be that test_object_1 will have the data from test_object_2 at offset 0,
					and the remaining data will be equal to s1 NOT including the first test_object_2 number of bytes from s1.
					(Size and capacity should be: s1.size().)

					The result for an insert function should be that test_object_1 will have the data from test_object_2 at offset 0,
					and the remaining data will be equal to s1. (Size and capacity should be: s1.size() + s2.size().)
			*/

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 is empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Set test_object_1 to s1. */
			test_object_1 = s1;

			/* Set test_object_2 to s2. */
			test_object_2 = s2;

			/*
				Make sure that test_object_1's size and capacity are equal to s1.
				Also make sure that test_object_2's size and capacity are equal to s2.
			*/
			if ((test_object_1.size() != s1.size()) || (test_object_2.size() != s2.size()))
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if ((test_object_1.get_Capacity() != s1.size()) || (test_object_2.get_Capacity() != s2.size()))
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

			/* Get pointer for test_object_2. */
			p1 = NULL;
			if ((p1 = test_object_2.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_2 actually contains the correct data. */
			for (size_t x = 0; x < test_object_2.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Run test function. */
			if (Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, test_object_2_c_ptr) !=
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ?
					/* Insert No Allocation function should return buffer too small here. All other functions should return success. */
					((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? (COMMON_ERROR_SUCCESS) : (COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL)) :
					(COMMON_ERROR_SUCCESS)))
			{
					/* Test function failed. */
					return -1020;
			}

			/* Make sure that test_object_1's size and capacity are equal to (s1.size() + s2.size() insert and reallocate) OR
				(s1.size() Non-insert or non-reallocation). */
			if (test_object_1.size() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? (s1.size() + s2.size()) : (s1.size())) :
				(s1.size())))
			{
					/* Invalid size after call to test function. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? (s1.size() + s2.size()) : (s1.size())) :
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

			/* Get pointer to strings s1 and s2. */
			p2 = NULL;
			if ((p2 = s1.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}
			p3 = NULL;
			if ((p3 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ?
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? (s1.size() + s2.size()) : (s1.size())) :
				(s1.size())); x++)
			{
					/* If the current function we are testing is Insert No Allocate, then the data will be identical to s1. */
					if ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) &&
						(!(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate)))
					{
							if (p1[x] != p2[x])
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}
					/* All other functions. */
					else
					{
						/* Check for data from s2, if we are within it's length. */
						if (x < s2.size())
						{
								if (p1[x] != p3[x])
								{
										/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
										return -1004;
								}
						}

						/* Check for s1 otherwise. */
						else
						{
								if (p1[x] != p2[((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ?
									((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? (x - (s2.size())) : (x)) :
									(x))])
								{
										/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
										return -1004;
								}
						}
					}
			}

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
					Data_Object Test 2

					This test checks a char function for MSYS_DataObjects. (Reallocate)

					This test attempts to store s3 in test_object_1, s2 in test_object_2, then run the test function with an offset of
					position 4 and the data of test_object_2.

					The result for a non allocation function should be that it returns COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL, as the
					resulting string, if the non allocation function were to continue anyway, would have a capacity and size equaling
					(s3.size() + s2.size() - (offset + 1)) which is beyond the allocated length of the buffer.

					The result for the insert() or overwrite() function should be that test_object_1 contains s3's data up to position 4, at
					which point it contains s2's data followed by the data from s3 at position 4 onward.
					Capacity and size equaling (s3.size() + s2.size()).
			*/

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Set test_object_1 to s3 and test_object_2 to s2. */
			test_object_1 = s3;
			test_object_2 = s2;

			/*
				Make sure that test_object_1's size and capacity are equal to s3.
				Also make sure that test_object_2's size and capacity are equal to s2.
			*/
			if ((test_object_1.size() != s3.size()) || (test_object_2.size() != s2.size()))
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if ((test_object_1.get_Capacity() != s3.size()) || (test_object_2.get_Capacity() != s2.size()))
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

			/* Get pointer for test_object_2. */
			p1 = NULL;
			if ((p1 = test_object_2.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_2 actually contains the correct data. */
			for (size_t x = 0; x < test_object_2.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Run test function. */
			if (Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 4, test_object_2_c_ptr) !=
				/* Reallocation functions should succeed here, Non-allocation functions should return COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL. */
					((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? (COMMON_ERROR_SUCCESS) : (COMMON_ERROR_MEMORY_BUFFER_TOO_SMALL)))
			{
					/* Test function failed. */
					return -1020;
			}

			/*
				Make sure that test_object_1's size and capacity are equal to ((s3.size() + s2.size()) for Insert()),
				((s3.size() + s2.size() - (offset + 1)) for Overwrite()) or (s3.size() for everything else.).
			*/
			if (test_object_1.size() !=
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ?
					((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) :
						(s3.size() + s2.size() - (4 + 1))) :
					(s3.size())))
			{
					/* Invalid size after call to test function. */
					return -1014;
			}
			if (test_object_1.get_Capacity() !=
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ?
					((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) :
						(s3.size() + s2.size() - (4 + 1))) :
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

			/* Get pointer to strings s3 and s2. */
			p2 = NULL;
			if ((p2 = s3.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}
			p3 = NULL;
			if ((p3 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/* Unless this is the Insert() or Overwrite() function, the data will be identical to s3. */
					if (p1[x] !=
				((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].canReallocate) ? ((x < 4) ? (p2[x]) : ((x < (4 + s2.size())) ? (p3[(x - 4)]) : (p2[(x - s2.size())]))) :
				(p2[x])))
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
					Data_Object Test 3

					This test checks a Data_Object function for MSYS_DataObjects. (Non-Reallocate)

					This test attempts to reserve memory with the length of s3 + s2, then store
					(concat) s3 in test_object_1, and then run the test function with an offset of 0 and the data of s2.

					The result for a non insert function should be that test_object_1 will have the data from s2 at offset 0
					and the remaining data will be equal to s3 starting at offset s2.size().
					(Size should be: s3.size(), capacity should be (s3.size() + s2.size()).)

					The result for an insert function should be that test_object_1 will have the data from s2 at offset 0
					and the remaining data will be equal to s3. (Size and capacity should be: (s3.size() + s2.size()).)
			*/

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Reserve memory for s3.size() (Non-insert functions) OR (s3.size() + s2.size()) (Insert Functions). */
			test_object_1.reserve(((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) : (s3.size())));

			/* Check for reserved memory. */
			if (test_object_1.size() != 0)
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to reserve(). */
						return -1008;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) : (s3.size())))
			{
					/* DataProcess::Data_Object::reserve() Invalid capacity after call to reserve(). */
					return -1007;
			}

			/* Concat s3 into test_object_1, and concat s2 into test_object_2. */
			test_object_1 += s3;
			test_object_2 += s2;

			/*
				Make sure that test_object_1's size and capacity are equal to s3.
				Also make sure that test_object_2's size and capacity are equal to s2.
			*/
			if ((test_object_1.size() != s3.size()) || (test_object_2.size() != s2.size()))
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string. */
						return -1010;
			}
			if ((test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) : (s3.size()))) ||
				(test_object_2.get_Capacity() != s2.size()))
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

			/* Get pointer for test_object_2. */
			p1 = NULL;
			if ((p1 = test_object_2.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_2 actually contains the correct data. */
			for (size_t x = 0; x < test_object_2.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Run test function. */
			if (Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, test_object_2_c_ptr) != COMMON_ERROR_SUCCESS)
			{
					/* Test function failed. */
					return -1020;
			}

			/* Make sure that test_object_1's size and capacity are equal to s3.size() (Non-insert function) OR
			   (s3.size() + s2.size()) (Insert function). */
			if (test_object_1.size() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) : (s3.size())))
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s3.size() + s2.size()) : (s3.size())))
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

			/* Get pointer to strings s3 and s2. */
			p2 = NULL;
			if ((p2 = s3.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}
			p3 = NULL;
			if ((p3 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/* Check for s2's data if the current offset value is less than s2.size(). */
					if (x < s2.size())
					{
						if (p1[x] != p3[x])
						{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
						}
					}
					/* Check for s3's data otherwise. */
					else
					{
							if (p1[x] != p2[((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (x - s2.size()) : (x))])
							{
									/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
									return -1004;
							}
					}
			}

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
					Data_Object test 4

					This test checks a Data_Object function for MSYS_DataObjects. (Non-Reallocate)

					This test attempts to reserve memory with the length of s1 + s2, then store
					(concat) s1 in test_object_1, then run the test function with an offset of position 3 and data of s2.

					The result should be for a non insert function, that test_object_1 contains s1's data up to position 3,
					at which it contains s2's data, and the remaining data is s1's remaining data after position 3.
					Capacity and size equaling s1.size().

					The result should be for a insert function, that test_object_1 contains s1's data up to position 3,
					at which it contains s2's data, and the remaining data is s1's remaining data including position 3.
					Capacity and size equaling (s1.size() + s2.size()).
			*/

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/* Reserve memory for s1.size() (Non-Insert function) OR (s1.size() + s2.size()) (Insert function). */
			test_object_1.reserve(((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s1.size() + s2.size()) : (s1.size())));

			/* Check for reserved memory. */
			if (test_object_1.size() != 0)
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to reserve(). */
						return -1008;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s1.size() + s2.size()) : (s1.size())))
			{
					/* DataProcess::Data_Object::reserve() Invalid capacity after call to reserve(). */
					return -1007;
			}

			/* Concat s1 into test_object_1, and concat s2 into test_object_2. */
			test_object_1 += s1;
			test_object_2 += s2;

			/*
				Make sure that test_object_1's size and capacity are equal to s1.
				Also make sure that test_object_2's size and capacity are equal to s2.
			*/
			if ((test_object_1.size() != s1.size()) || (test_object_2.size() != s2.size()))
			{
						/* DataProcess::Data_Object::reserve() Invalid size after call to operator+= std::string. */
						return -1010;
			}
			if ((test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s1.size() + s2.size()) : (s1.size())))
				|| (test_object_2.get_Capacity() != s2.size()))
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

			/* Get pointer for test_object_2. */
			p1 = NULL;
			if ((p1 = test_object_2.get_Pointer()) == NULL)
			{
					/* DataProcess::Data_Object::get_Pointer() Could not get pointer to test_object's data. */
					return -1003;
			}

			/* Get pointer to string. */
			p2 = NULL;
			if ((p2 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_2 actually contains the correct data. */
			for (size_t x = 0; x < test_object_2.size(); x++)
			{
					if (p1[x] != p2[x])
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Run test function. */
			if (Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 3, test_object_2_c_ptr) != COMMON_ERROR_SUCCESS)
			{
					/* Test function failed. */
					return -1020;
			}

			/*
				Make sure that test_object_1's size and capacity are equal to s1.size() (Non-insert function) OR
				(s1.size() + s2.size()) (Insert function).
			 */
			if (test_object_1.size() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s1.size() + s2.size()) : (s1.size())))
			{
					/* DataProcess::Data_Object::operator= Invalid size after call to DataProcess::Data_Object::operator= std::string. */
					return -1014;
			}
			if (test_object_1.get_Capacity() != ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (s1.size() + s2.size()) : (s1.size())))
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

			/* Get pointer to strings s1 and s2. */
			p2 = NULL;
			if ((p2 = s1.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}
			p3 = NULL;
			if ((p3 = s2.c_str()) == NULL)
			{
					/* Could not get pointer to string object. */
					return -9001;
			}

			/* Make sure that test_object_1 actually contains the correct data. */
			for (size_t x = 0; x < test_object_1.size(); x++)
			{
					/*
						Check for s1 if the current offset is less than 3.

						Check for s2 if the current offset is greater than or equal to 3 but less than
						s2's length.

						If the current offset is greater than 3 + s2's length, then:
							- If the function we are testing is a non-insert function, check for the remaining s1 data at offset (x).
							- Otherwise check for the remaining data from s1 at offset (x - s2.size()).
					*/
					if (p1[x] != ((x < 3) ? (p2[x]) :
						((x < (3 + s2.size())) ? (p3[(x - 3)]) :
						 ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].isInsert) ? (p2[(x - s2.size())]) :
						  (p2[x])))))
					{
							/* DataProcess::Data_Object (Manual compare) Invalid data in the data_object. */
							return -1004;
					}
			}

			/* Clear test_object_1 and test_object_2. */
			test_object_1.clear();
			test_object_2.clear();

			/* Make sure that test_object_1 and test_object_2 are empty. */
			if ((test_object_1.size() != 0) || (test_object_2.size() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid size after clear(). */
					return -1005;
			}
			if ((test_object_1.get_Capacity() != 0) || (test_object_2.get_Capacity() != 0))
			{
					/* DataProcess::Data_Object::clear() Invalid capacity after clear(). */
					return -1006;
			}

			/*
				Invalid Data_Object pointer check.

				Should return COMMON_ERROR_INVALID_ARGUMENT.
			 */
			if ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(NULL, 3, test_object_1_c_ptr) != COMMON_ERROR_INVALID_ARGUMENT) ||
				(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 3, NULL) != COMMON_ERROR_INVALID_ARGUMENT))
			{
					/* Test function failure. Should have returned COMMON_ERROR_INVALID_ARGUMENT. */
					return -1020;
			}

			/*
				Invalid private object pointer check.

				Should return COMMON_ERROR_INVALID_ARGUMENT.
			 */
			if ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(&badPrivPtr, 3, test_object_1_c_ptr) != COMMON_ERROR_INVALID_ARGUMENT) ||
				(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 3, &badPrivPtr) != COMMON_ERROR_INVALID_ARGUMENT))
			{
					/* Test function failure. Should have returned COMMON_ERROR_INVALID_ARGUMENT. */
					return -1020;
			}

			/*
				Invalid Data Object tests.

				All of the following tests should return COMMON_ERROR_DATA_CORRUPTION.
				Note: The tests where test_object_1 is the source should return COMMON_ERROR_NO_DATA, as it was (should have been) cleared.
			 */
			if ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(&badData, 0, test_object_1_c_ptr) != COMMON_ERROR_NO_DATA) ||
				(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, &badData) != COMMON_ERROR_DATA_CORRUPTION))
			{
					/* Test function failure. Should have returned COMMON_ERROR_DATA_CORRUPTION. */
					return -1020;
			}
			if ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(&badLength, 0, test_object_1_c_ptr) != COMMON_ERROR_NO_DATA) ||
				(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, &badLength) != COMMON_ERROR_DATA_CORRUPTION))
			{
					/* Test function failure. Should have returned COMMON_ERROR_DATA_CORRUPTION. */
					return -1020;
			}
			if ((Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(&badCapacity, 0, test_object_1_c_ptr) != COMMON_ERROR_NO_DATA) ||
				(Unit_Test_Data_Object_From_Data_Object_Functions_To_Test[y].fp(test_object_1_c_ptr, 0, &badCapacity) != COMMON_ERROR_DATA_CORRUPTION))
			{
					/* Test function failure. Should have returned COMMON_ERROR_DATA_CORRUPTION. */
					return -1020;
			}

			/* Output result of tests. */
			std::cout << "PASS\n";
			std::cout.flush();

		}	/* End test loop. */

        /* Exit function. */
        return 0;
}
