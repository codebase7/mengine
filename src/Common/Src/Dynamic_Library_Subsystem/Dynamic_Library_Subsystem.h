/*!
    Multiverse Engine Project 21/3/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem.h

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

/* Include guard. */
#ifndef MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_H
#define MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_H

/* Internal includes. */
#include "../../../DLL_PORT.h"	/* Defines MSYS_DLL_EXPORT, and MSYS_DLL_IMPORT_TEMPLATE. */

/* Check for MSVC. */
#ifdef _MSC_FULL_VER
#include "..\..\..\stdbool.h"	/* bool. (MSVC is special.) */
#else
#include <stdbool.h>	/* bool. */
#endif	/* _MSC_FULL_VER */
#include <stddef.h>	/* NULL. */
#include <stdlib.h>	/* Malloc. */

/* Internal includes. */
#include "Dynamic_Library_Subsystem_Data_Structures.h"		/* Contains data structures used internally. */

#ifdef __win32
#include "..\Error_Handler\Common_Error_Handler_Internal.h"			/* Contains the function defintions for calling the common error handler. */
#else
#include "../Error_Handler/Common_Error_Handler_Internal.h"			/* Contains the function defintions for calling the common error handler. */
#endif /* __win32 */

/* Defines for the default library extension. */
#ifdef __win32
#define DL_EXTENSION ".dll"
#elif __linux__
#define DL_EXTENSION ".so"
#endif

#ifdef __cplusplus
/* Define extern C. */
extern "C" {
#endif
		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Load_Library(const char * pathToLibrary, const size_t pathToLibraryLength, const bool reloadLibrary,
		 * 							    Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
		 *
		 * 	This function calls the system specific dynamic library handler and attempts to load the requested library.
		 *
		 * 	Pram: const char * pathToLibrary, a pointer to the c-string that contains the path to the library on disk.
		 *	Pram: const size_t pathToLibraryLength, length of the pathToLibrary c-string in bytes.
		 * 	Pram: const bool reloadLibrary, whether or not to reload the library if it is already loaded.
		 * 	Pram: Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib, A pointer to a properly constructed
		 * 	management data structure used internally.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the library was successfully loaded. (The value of lib.bLastCallEncounteredAnError will be false in this case as well.)
		 * 	Returns Translated host system error code if the library could not be loaded. (The value of lib.bLastCallEncounteredAnError will be true in this case as well.)
		 * 	Returns All errors returned by Common_Dynamic_Library_Subsystem_Unload_Library() if the attempt to unload the library failed. (Only possible if reloadLibrary is true.) (The value of lib.bLastCallEncounteredAnError will be true in this case as well.)
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the pathToLibrary pointer was NULL. (The value of lib.bLastCallEncounteredAnError will be true in this case as well.)
		 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library pointer was NULL.
		 *	Returns DYNLIB_ERROR_LIBRARY_ALREADY_LOADED if the library was already loaded. (Only possible if reloadLibrary is false.) (The value of lib.bLastCallEncounteredAnError will be false in this case as well.)
		 */
		MSYS_DLL_EXPORT int Common_Dynamic_Library_Subsystem_Load_Library(const char * pathToLibrary, const size_t pathToLibraryLength, const bool reloadLibrary,
																		 Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Unload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
		 *
		 * 	This function calls the system specific dynamic library handler and attempts to unload the requested library.
		 *
		 * 	Note: Due to the underlying system, even if this call is successful, the library may still be loaded in memory.
		 * 	Internally, the Dynamic_Library_Subsystem blocks attempts to load the library multiple times via calls to Common_Dynamic_Library_Subsystem_Load_Library().
		 * 	(I.e. Load a library that is already loaded.) This is to try and prevent specific systems that use reference counts
		 * 	to manage whether or not a library is still in use from keeping the library in memory after a call to Unload_Library().
		 * 	However we cannot prevent a program that uses the Dynamic_Library_Subsystem from interacting with the underlying system
		 * 	directly, nor can we forceably unload a library even if the underlying system has a method to do so. (This is because any other
		 * 	section of the program could still be using it, and a forced removal from memory could cause undefined behavior in those sections.)
		 * 	As such this call can only be expected to decrease the reference count that was incremented by a call to Common_Dynamic_Library_Subsystem_Load_Library()
		 * 	on such systems.
		 *
		 * 	Pram: Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib, A pointer to a properly constructed
		 * 	management data structure used internally.
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the library unload call returned successful.
		 * 	Returns DYNLIB_ERROR_LIBRARY_NOT_LOADED if the library was not loaded according to the given management data structure.
		 * 	Returns Translated host system error code if the library unload call returned unsuccessful.
		 *	Returns COMMON_ERROR_INVALID_ARGUMENT if the given Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library pointer was NULL.
		 */
		MSYS_DLL_EXPORT int Common_Dynamic_Library_Subsystem_Unload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib);

		/*!
		 * 	int Common_Dynamic_Library_Subsystem_Get_Symbol(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib,
		 * 							     const char * symbolName, void ** retSym)
		 *
		 * 	This function calls the system specific dynamic library handler and attempts to fetch a pointer to the first byte
		 * 	of the given symbol.
		 *
		 * 	Note: To check for an error result from this function, check the value of lib.bLastCallEncounteredAnError.
		 * 	If lib.bLastCallEncounteredAnError is false, no error occured during this function. Otherwise an error occured.
		 *
		 * 	Pram: Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, A pointer to a properly constructed
		 * 	management data structure used internally.
		 * 	Pram: const char * symbolName, A pointer to a c-string that contains the name of the requested symbol to
		 * 	search for.
		 *	Pram: void ** retSym, A double pointer that will hold the address to the first byte of the requested symbol if the function succeeds.
		 *	(retSym will NOT be modified if this function returns an error.)
		 *
		 * 	Returns COMMON_ERROR_SUCCESS if the resulting lookup returned a valid pointer. (The value of lib.bLastCallEncounteredAnError will be false in this case.)
		 * 	Returns a NULL pointer if the resulting lookup returned a NULL pointer. (The value of lib.bLastCallEncounteredAnError will be false in this case as well.)
		 *		(Note: Some systems may not support NULL symbols, in this case the result is the same as if the lookup failed, see below.)
		 * 	Returns Translated host system error code if the lookup failed for some reason. (The value of lib.bLastCallEncounteredAnError will be true in this case.)
		 *	Returns COMMON_ERROR_INVALID_ARGUMENT if the given Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library, symbolName, or retSym pointer(s) was / were set to NULL.
		 *	Returns DYNLIB_ERROR_LIBRARY_NOT_LOADED if the library was not loaded according to the given management data structure.
		 */
		MSYS_DLL_EXPORT int Common_Dynamic_Library_Subsystem_Get_Symbol(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib, const char * symbolName, void ** retSym);
#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus */

#endif	/* MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_H */

/* End of Dynamic_Library_Subsystem.h */
