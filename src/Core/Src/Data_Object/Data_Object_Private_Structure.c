/*
	Multiverse Engine Project	Core Data_Object_Private_Structure.c	28/7/2016

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

#ifdef __cplusplus__
extern "C" {
#endif	/* __cplusplus__ */

/*
 *
 *		Private data structure is defined below.
 *		(Subject to change without warning.)
 *
 *		DO NOT USE MSYS_DataObject_T_Private DIRECTLY. (The exception this is made for is the Unit_Tests program.)
 *		USE THE MSYS_DataObject_T object and functions instead.
 */

/* Define the real MSYS_DataObject_T object. */
typedef struct MSYS_DataObject_Private {
	char * data;        /* Pointer to data. */
    size_t length;      /* Length of data. */
    size_t capacity;    /* Length of data we can store. */
	size_t refcount;	/* Number of references (Shadow Copies) that point to the object. */
} MSYS_DataObject_T_Private;

#ifdef __cplusplus__
} /* extern "C" */
#endif	/* __cplusplus__ */
