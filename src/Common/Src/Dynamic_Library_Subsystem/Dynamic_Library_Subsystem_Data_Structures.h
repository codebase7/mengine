/*!
    Multiverse Engine Project 21/3/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Data_Structures.h

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

// Include guard.
#ifndef MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_H
#error "You must include the Dynamic_Library_Subsystem.h header file. It will include all of the other needed headers."
#else
#ifndef MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_DATA_STRUCTURES_H
#define MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_DATA_STRUCTURES_H

// Define the supported API level.
#define MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_API_LEVEL 0

#ifdef __cplusplus
// Define extern C.
extern "C" {
#endif
		// Define Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library.
		struct Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library
		{
			bool bIsLoaded;				// Whether or not this library is loaded.
			bool bLastCallEncounteredAnError;	/*
								    Whether or not this library has encountered an error in the last call.
								    (Should reset to false when a new call is made and no error occurs.)
								*/

			void * osSpecificPointerData;		/*
								    Pointer to an OS specific data structure.
								    (For example, Windows defines loaded libraries with an HMODULE pointer,
								    which is needed to unload the library or to search it.)
								*/
			const char * pathToLibrary;			// Path to the dynamic library file on disk.
		};

		typedef struct Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library;

		/*!
		 * 	Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library()
		 *
		 * 	Creates a Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library data structure in a neutral state.
		 *
		 * 	This function should be called when constructing a Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library object.
		 * 	As it will correctly setup said object.
		 *
		 * 	WARNING: The caller is responsible for calling free() or
		 * 	Destroy_Loaded_Dynamic_Library() on the successfully created structure.
		 *
		 * 	Returns a pointer to a Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library data structure if successful.
		 * 	Otherwise returns NULL.
		 */
		MSYS_DLL_EXPORT Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library();

		/*!
		 * 	void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		 *
		 * 	Destroys (frees) a created Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library data structure.
		 *
		 * 	Pram: Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, a pointer to
		 * 	a successfully created Loaded_Dynamic_Library data structure.
		 *
		 * 	This function has no return.
		 */
		MSYS_DLL_EXPORT void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib);
#ifdef __cplusplus
}		// End of extern C.
#endif

#endif
#endif

// End of Dynamic_Library_Subsystem_Data_Structures.h
