/*!
    Multiverse Engine Project 17/1/2016 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Data_Structures_Private_API.h

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

/* Include guard. */
#ifndef MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_H
#error "You must include the Dynamic_Library_Subsystem.h header file. It will include all of the other needed headers."
#else
#ifndef MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_DATA_STRUCTURES_PRIVATE_API_H
#define MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_DATA_STRUCTURES_PRIVATE_API_H

/* Check for C++ Compiler. */
#ifdef __cplusplus
/* Define extern C. */
extern "C" {
#endif	/* __cplusplus	*/
		/*!
			struct Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private

			This structure is an internal engine structure used to manage dynamicly
			loaded libraries that were loaded at runtime via the Dynamic Library Subsystem.

			This structure should NOT be accessed directly as it is subject to change without
			warning. You should use the Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library
			wrapper instead.
		 */
		struct Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private
		{
			bool bIsLoaded;				/* Whether or not this library is loaded. */
			bool bLastCallEncounteredAnError;	/*
								    Whether or not this library has encountered an error in the last call.
								    (Should reset to false when a new call is made and no error occurs.)
								*/

			void * osSpecificPointerData;		/*
								    Pointer to an OS specific data structure.
								    (For example, Windows defines loaded libraries with an HMODULE pointer,
								    which is needed to unload the library or to search it.)
								*/
			char * pathToLibrary;			/* Path to the dynamic library file on disk. */
		};

		/* Create user defined data type for Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private structure. */
		typedef struct Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private;

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib)
		 *
		 * 	Creates a Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private data structure in a neutral state.
		 *
		 * 	This function should be called when constructing a Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private object.
		 * 	As it will correctly setup said object.
		 *
		 * 	WARNING: The caller is responsible for calling
		 * 	Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library_Private() on the successfully created structure.
		 *
		 *	WARNING: This function will NOT deallocate a preexisting structure, and will overwrite the given pointer if it is
		 *	non-NULL if this function succeeds. Therefore if you need to keep the pointer, copy it elsewhere before calling this
		 *	function.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if successful. (The created structure will be pointed to by lib.)
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given double pointer is NULL.
		 *	Returns COMMON_ERROR_MEMORY_ERROR if the data structure could not be allocated.
		 *	Otherwise returns the appropriate error code.
		 *
		 *	No-alteration clause:
		 *		- In case of error, this function will not modify it's arguments.
		 */
		int Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib);

		/*!
		 * 	void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib)
		 *
		 * 	Destroys (frees) a created Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private data structure and set's it's pointer to NULL.
		 *
		 * 	Pram: Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib, a double pointer to
		 * 	a successfully created Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private data structure.
		 *
		 * 	This function has no return.
		 */
		void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private ** lib);

		/*!
		 *	void Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib)
		 *
		 *	Blanks the given Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private data structure's members. (Deallocating memory for them if needed.)
		 *
		 *	If given an invalid pointer this function will silently fail.
		 *
		 *	This function has no return.
		 */
		void Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib);
		
		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Returns the status of the bIsLoaded member variable.
		 *
		 * 	Returns COMMON_ERROR_TRUE if the library is loaded.
		 *	Returns COMMON_ERROR_FALSE if the library is NOT loaded.
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const bool value)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Sets the status of the bIsLoaded member variable to the given value.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the status was set to the given value successfully.
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const bool value);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Returns the status of the bLastCallEncounteredAnError member variable.
		 *
		 * 	Returns COMMON_ERROR_TRUE if the last operation on this library encountered an error.
		 *	Returns COMMON_ERROR_FALSE if the last operation on this library did NOT encounter an error.
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Get_LastCallEncounteredError_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const bool value)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Sets the status of the bLastCallEncounteredAnError member variable to the given value.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the status was set to the given value successfully.
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const bool value);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, void ** retVar)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Returns the pointer for the osSpecificPointerData member variable.
		 *
		 *	WARNING: This function will NOT deallocate a preexisting structure, and will overwrite the given pointer if it is
		 *	non-NULL if this function succeeds. Therefore if you need to keep the pointer, copy it elsewhere before calling this
		 *	function.
		 *
		 *	WARNING: The caller should NOT deallocate the returned pointer.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the data was returned successfully. (retVar will point to the pointer value in this case.)
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, void ** retVar);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, void * value)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Sets the pointer for the osSpecificPointerData member variable to the given value.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the status was set to the given value successfully.
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, void * value);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const char ** retVar)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Returns the pointer for the pathToLibrary member variable.
		 *
		 *	WARNING: This function will NOT deallocate a preexisting structure, and will overwrite the given pointer if it is
		 *	non-NULL if this function succeeds. Therefore if you need to keep the pointer, copy it elsewhere before calling this
		 *	function.
		 *
		 *	WARNING: The caller should NOT deallocate the returned pointer.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the data was returned successfully. (retVar will point to the pointer value in this case.)
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
		 *	Otherwise returns the appropriate error code.
		 */
		int Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library_Private(const Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const char ** retVar);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const char * value, const size_t valueLength)
		 *
		 * 	ACCESSOR FUNCTION.
		 *
		 *	Sets the pointer for the pathToLibrary member variable to the given value.
		 *
		 *	Note this function serves two purposes, to allocate and copy the needed path string into the structure,
		 *	and to deallocate a pre-existing path string in the structure. The mode that is chosen is dependant on the
		 *	arguments given to the function.
		 *
		 *	I.e. If value is non-NULL and valueLength is greater than zero, then the given path string will be copied.
		 *	If value is NULL, and valueLength is equal to zero, then any pre-existing path string in the structure will be
		 *	deallocated. Any other combination will generate a COMMON_ERROR_INVALID_ARGUMENT error code and the structure
		 *	will not be modified.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the status was set to the given value successfully.
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers or length is NULL.
		 *	Otherwise returns the appropriate error code.
		 *
		 *	No-alteration clause:
		 *		- In case of error, this function will not modify it's arguments.
		 */
		int Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library_Private(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library_Private * lib, const char * value, const size_t valueLength);

#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus	*/

#endif	/*	MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_DATA_STRUCTURES_PRIVATE_API_H	*/
#endif	/*	MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_H	*/

/* End of Dynamic_Library_Subsystem_Data_Structures.h */
