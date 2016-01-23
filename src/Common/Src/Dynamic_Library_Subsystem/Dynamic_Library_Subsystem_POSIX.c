/*!
    Multiverse Engine Project 01/4/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_POSIX.c

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

/* Check for linux. */
#ifdef __linux__

/* Internal includes */
#include "Dynamic_Library_Subsystem.h"
#include "../Error_Handler/Common_Error_Handler_Structures.h"

/* External includes. */
#include <dlfcn.h>	/* dlopen, dlclose, dlsym, dlerror. */

/* Check for C++ Compiler. */
#ifdef __cplusplus
/* Define extern C. */
extern "C" {
#endif	/* __cplusplus */
	int Common_Dynamic_Library_Subsystem_Load_Library(const char * pathToLibrary, const size_t pathToLibraryLength, const bool reloadLibrary, Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		void * callResult = NULL;						/* The result of the call to dlopen(). */
		char * hostErr = NULL;							/* The result returned from dlerror(). */
		char * tempPath = NULL;							/* Used to load the library. */

		/* Check to see if the pointer to the management structure is valid. */
		if (lib != NULL)
		{
			/* Check to see if pathToLibrary is NULL. */
			if (pathToLibrary != NULL)
			{
				/* Check to see if the library is loaded. */
				retFromCall = Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(lib);
				if ((retFromCall == COMMON_ERROR_FALSE) || (retFromCall == COMMON_ERROR_INVALID_ARGUMENT) || (reloadLibrary))
				{
					/* Check and see if the library is loaded. */
					if (retFromCall == COMMON_ERROR_TRUE)
					{
						/* Call Unload_Library. */
						retFromCall = Common_Dynamic_Library_Subsystem_Unload_Library(lib);
					}
					else
					{
						/* Reset retFromCall. */
						retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
					}
		
					/* Only continue if the library was unloaded, or if we did not need to unload the library. */
					if ((retFromCall == COMMON_ERROR_UNKNOWN_ERROR) || (retFromCall == COMMON_ERROR_SUCCESS))
					{
						/* Blank the values in lib. */
						Common_Dynamic_Library_Subsystem_Blank_Loaded_Dynamic_Library(lib);

						/* Copy the path string into lib. */
						retFromCall = Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library(lib, pathToLibrary, pathToLibraryLength);
						if (retFromCall == COMMON_ERROR_SUCCESS)
						{
							/* Get the path back. */
							retFromCall = Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &tempPath);
							if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPath != NULL))
							{
								/* Call dlopen(). */
								callResult = dlopen(tempPath, RTLD_LAZY | RTLD_LOCAL);

								/* Check the callResult. */
								if (callResult == NULL)
								{
									/* An error occured.
										There is no clean way to check the error given here, as dlerror() returns a human-readable string.
										In addition, dlopen() does not have any defined error codes in the POSIX standard.
										As such we have no way of returning the specific error encountered to the caller,
										so we must return COMMON_ERROR_SYSTEM_SPECIFIC.
									 */
									ret = COMMON_ERROR_SYSTEM_SPECIFIC;

									/* Could not load the library. */
									hostErr = dlerror();
									retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
									COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): Could not load <");
									COMMON_LOG_VERBOSE(tempPath);
									COMMON_LOG_VERBOSE("> Host function returned: ");
									COMMON_LOG_VERBOSE(hostErr);
									if (retFromCall != COMMON_ERROR_SUCCESS)
									{
										/* Log additional error. */
										COMMON_LOG_VERBOSE(" Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
										COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
									}
								}
								else
								{
									/* Cast the OS specific data structure pointer to void*.  */
									retFromCall = Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library(lib, ((void*)callResult));
									if (retFromCall == COMMON_ERROR_SUCCESS)
									{
										/* Set bIsLoaded. */
										retFromCall = Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library(lib, true);
										if (retFromCall == COMMON_ERROR_SUCCESS)
										{
											/* Success. */
											ret = COMMON_ERROR_SUCCESS;
											COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): <");
											COMMON_LOG_VERBOSE(tempPath);
											COMMON_LOG_VERBOSE("> loaded.");
										}
										else
										{
											/* Could not set is loaded flag. */
											ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
										}
									}
									else
									{
										/* Could not set os specific pointer data. */
										ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
									}
								}
							}
							else
							{
								/* Could not retrive path from lib structure. */
								ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
							}
						}
						else
						{
							/* Could not copy path data. */
							ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
						}
					}
					else
					{
						/* Encountered an error during the unload. */
						ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
						retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
						COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): Unable to reload library.");
						if (retFromCall != COMMON_ERROR_SUCCESS)
						{
							/* Log additional error. */
							COMMON_LOG_VERBOSE(" Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
							COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
						}
					}
				}
				else
				{
					/* Library is already loaded. */
					ret = DYNLIB_ERROR_LIBRARY_ALREADY_LOADED;
				}
			}
			else
			{
				/* pathToLibrary is NULL. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): No path to the library was given. Unable to load a library without the path to it.");
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					/* Log additional error. */
					COMMON_LOG_VERBOSE(" Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
					COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Management structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): The engine's library structure for the given library is invalid. Unable to load a library without a valid library structure.");
		}

		/* Exit function. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Unload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		char * hostErr = NULL;							/* The result returned from dlerror(). */
		void * osData = NULL;							/* The osSpecificPointerData from the management structure. */
		char * pSym = NULL;								/* Used to log the library path to the error log. */

		/* Check to see if the pointer to the management structure is valid. */
		if (lib != NULL)
		{
			/* Check for a loaded library. */
			retFromCall = Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(lib);
			if (retFromCall == COMMON_ERROR_TRUE)
			{
				/* Reset bLastCallEncounteredAnError. */
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, false);
				if (retFromCall == COMMON_ERROR_SUCCESS)
				{
					/* Get the osSpecificPointerData from the management structure. */
					retFromCall = Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library(lib, &osData);
					if ((retFromCall == COMMON_ERROR_SUCCESS) && (osData != NULL))
					{
						/* Call dlclose(). */
						retFromCall = dlclose(lib->osSpecificPointerData);
						if (retFromCall == 0)
						{
							/* The library was unloaded successfully. */
							retFromCall = Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library(lib, false);
							if (retFromCall == COMMON_ERROR_SUCCESS)
							{
								retFromCall = Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library(lib, NULL);
								if (retFromCall == COMMON_ERROR_SUCCESS)
								{
									/* Success. */
									ret = COMMON_ERROR_SUCCESS;
									COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): <");

									/* Attempt to get the library path for the error log. */
									if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &pSym) == COMMON_ERROR_SUCCESS) &&
										(pSym != NULL))
									{
										COMMON_LOG_VERBOSE(pSym);
									}
									else
									{
										COMMON_LOG_VERBOSE("[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
									}
									pSym = NULL;	/* Clear abused pSym. */

									COMMON_LOG_VERBOSE("> unloaded.");
								}
								else
								{
									/* Could not clear os specific pointer data in management structure. */
									ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
									retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
									COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not clear os specific pointer data in management structure. Call returned: ");
									COMMON_LOG_VERBOSE(Common_Get_Error_Message(ret));
									if (retFromCall != COMMON_ERROR_SUCCESS)
									{
										COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
										COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
									}
								}
							}
							else
							{
								/* Could not clear is loaded flag in management structure. */
								ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
								retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not clear is loaded flag in management structure. Call returned: ");
								COMMON_LOG_VERBOSE(Common_Get_Error_Message(ret));
								if (retFromCall != COMMON_ERROR_SUCCESS)
								{
									COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
									COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
								}
							}
						}
						else
						{
							/* An error occured.
								There is no clean way to check the error given here, as dlerror() returns a human-readable string.
								In addition, dlclose() does not have any defined error codes in the POSIX standard.
								As such we have no way of returning the specific error encountered to the caller,
								so we must return COMMON_ERROR_SYSTEM_SPECIFIC.
							 */
							ret = COMMON_ERROR_SYSTEM_SPECIFIC;

							/* Could not load the library. */
							hostErr = dlerror();
							retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
							COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not unload <");

							/* Attempt to get the library path for the error log. */
							if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &pSym) == COMMON_ERROR_SUCCESS) &&
								(pSym != NULL))
							{
								COMMON_LOG_VERBOSE(pSym);
							}
							else
							{
								COMMON_LOG_VERBOSE("[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
							}
							pSym = NULL;	/* Clear abused pSym. */

							COMMON_LOG_VERBOSE("> Host function returned: ");
							COMMON_LOG_VERBOSE(hostErr);
							if (retFromCall != COMMON_ERROR_SUCCESS)
							{
								COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
								COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
							}
						}
					}
					else
					{
						/* Could not get osSpecificPointerData from management structure. */
						ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
						COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not get os specific data pointer from management structure. Call returned: ");
						COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
					}
				}
				else
				{
					/* Could not reset last call incountered an error flag. */
					ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
					COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not reset management structure's error flag. Call returned: ");
					COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
				}
			}
			else
			{
				/* Library is not loaded. */
				ret = DYNLIB_ERROR_LIBRARY_NOT_LOADED;
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): The given library <");

				/* Attempt to get the library path for the error log. */
				if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &pSym) == COMMON_ERROR_SUCCESS) &&
					(pSym != NULL))
				{
					COMMON_LOG_VERBOSE(pSym);
				}
				else
				{
					COMMON_LOG_VERBOSE("[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
				}
				pSym = NULL;	/* Clear abused pSym. */

				COMMON_LOG_VERBOSE("> is not loaded.");
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
					COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Management structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): The engine's library structure for the given library is invalid. Unable to unload a library without a valid library structure.");
		}

		/* Return result. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Get_Symbol(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib, const char * symbolName, void ** retSym)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		void * pSym = NULL;								/* The returned symbol pointer. */
		void * osData = NULL;							/* The osSpecificPointerData from the management structure. */
		char * hostErr = NULL;							/* The result returned from dlerror(). */

		/* Check to see if the pointer to the management structure is valid. */
		if (lib != NULL)
		{
			/* Check and see if retSym is valid. */
			if (retSym != NULL)
			{
				/* Check to see if symbolName is NULL. */
				if (symbolName != NULL)
				{
					/* Check for a loaded library. */
					retFromCall = Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(lib);
					if (retFromCall == COMMON_ERROR_TRUE)
					{
						/* Reset bLastCallEncounteredAnError. */
						retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, false);
						if (retFromCall == COMMON_ERROR_SUCCESS)
						{
							/* Get the osSpecificPointerData from the management structure. */
							retFromCall = Common_Dynamic_Library_Subsystem_Get_OsSpecificPointerData_Loaded_Dynamic_Library(lib, &osData);
							if ((retFromCall == COMMON_ERROR_SUCCESS) && (osData != NULL))
							{
								/* Call dlerror to clear the error state. */
								dlerror();

								/* Call dlsym. */
								pSym = dlsym(osData, symbolName);
								
								/* Call dlerror again to check for an error. */
								hostErr = dlerror();
								if (hostErr != NULL)
								{
									/* An error occured.
										There is no clean way to check the error given here, as dlerror() returns a human-readable string.
										In addition, dlsym() does not have any defined error codes in the POSIX standard.
										As such we have no way of returning the specific error encountered to the caller,
										so we must return COMMON_ERROR_SYSTEM_SPECIFIC.
									 */
									ret = COMMON_ERROR_SYSTEM_SPECIFIC;
									
									/* An error occured fetching the symbol. */
									retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
									COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not fetch symbol in <");

									/* Attempt to get the library path for the error log. */
									if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, (char**)&pSym) == COMMON_ERROR_SUCCESS) &&
										(pSym != NULL))
									{
										COMMON_LOG_VERBOSE((char*)pSym);
									}
									else
									{
										COMMON_LOG_VERBOSE("[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
									}
									pSym = NULL;	/* Clear abused pSym. */

									COMMON_LOG_VERBOSE("> Host function returned: ");
									COMMON_LOG_VERBOSE(hostErr);
									if (retFromCall != COMMON_ERROR_SUCCESS)
									{
										COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
										COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
									}
								}
								else
								{
									/* Copy pSym to retSym. */
									(*retSym) = pSym;

									/* Success. */
									ret = COMMON_ERROR_SUCCESS;
								}
							}
							else
							{
								/* Could not get osSpecificPointerData from management structure. */
								ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not get os specific data pointer from management structure. Call returned: ");
								COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
							}
						}
						else
						{
							/* Could not reset last call incountered an error flag. */
							ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
							COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not reset management structure's error flag. Call returned: ");
							COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
						}
					}
					else
					{
						/* Library is not loaded. */
						ret = DYNLIB_ERROR_LIBRARY_NOT_LOADED;
						retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
						COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): The given library <");

						/* Attempt to get the library path for the error log. */
						if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, (char**)&pSym) == COMMON_ERROR_SUCCESS) &&
							(pSym != NULL))
						{
							COMMON_LOG_VERBOSE((char*)pSym);
						}
						else
						{
							COMMON_LOG_VERBOSE("[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
						}
						pSym = NULL;	/* Clear abused pSym. */

						COMMON_LOG_VERBOSE("> is not loaded.");
						if (retFromCall != COMMON_ERROR_SUCCESS)
						{
							COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
							COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
						}
					}
				}
				else
				{
					/* symbolName is NULL. */
					ret = COMMON_ERROR_INVALID_ARGUMENT;
					retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
					COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): No symbol name was given, cannot load a symbol without a name to identifiy it.");
					if (retFromCall != COMMON_ERROR_SUCCESS)
					{
						COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
						COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
					}
				}
			}
			else
			{
				/* retSym is NULL. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): ");
				COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					COMMON_LOG_VERBOSE(" Additionally, could not set the error flag in the management structure. Call returned: ");
					COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Library structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): The engine's library structure for the given library is invalid. Unable to lookup function without a valid library structure.");
		}

		/* Return result. */
		return ret;
	}

#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus */
#endif	/* __linux__ */
