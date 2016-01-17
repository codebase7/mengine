/*!
    Multiverse Engine Project 28/3/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Windows.c

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

/* Internal includes. */
#include "Dynamic_Library_Subsystem.h"
#include "../Error_Handler/Common_Error_Handler_Structures.h"
#include "../Error_Handler/Windows_Error_Translation_Table.h"

/* External includes. */
#include <windows.h>

/* Check for C++ Compiler. */
#ifdef __cplusplus
/* Define extern C. */
extern "C" {
#endif	/* __cplusplus */
		int Common_Dynamic_Library_Subsystem_Load_Library(const char * pathToLibrary, const bool reloadLibrary, Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
		{
				/* Init vars. */
				int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
				int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
				HMODULE callResult = NULL;						/* The result of the call to LoadLibraryEx(). */
				DWORD retLLEX = 0;								/* Error code from LoadLibraryEx(). */

				/* Check to see if the pointer to the management structure is valid. */
				if (lib != NULL)
				{
						/* Check to see if pathToLibrary is NULL. */
						if (pathToLibrary != NULL)
						{
								/* Check to see if the library is loaded. */
								if ((!lib->bIsLoaded) || (reloadLibrary))
								{
										/* Check and see if the library is loaded. */
										if (lib->bIsLoaded)
										{
												/* Call Unload_Library. */
												retFromCall = Common_Dynamic_Library_Subsystem_Unload_Library(lib);
										}
		
										/* Only continue if the library was unloaded, or if we did not need to unload the library. */
										if ((retFromCall == COMMON_ERROR_UNKNOWN_ERROR) || (retFromCall == COMMON_ERROR_SUCCESS))
										{
												/* Set the values in lib. */
												lib->bIsLoaded = false;
												lib->bLastCallEncounteredAnError = false;
												lib->osSpecificPointerData = NULL;
												lib->pathToLibrary = pathToLibrary;
		
												/* Call LoadLibraryEx(). */
												callResult = LoadLibraryEx(lib->pathToLibrary, NULL, 0);
		
												/* Check the callResult. */
												if (callResult == NULL)
												{
														/* Get the last error. */
														retLLEX = GetLastError();
														retFromCall = Common_Translate_Windows_Error_Code_To_Common_Error_Code(retLLEX);

														/* Could not load the library. */
														ret = retFromCall;
														lib->bLastCallEncounteredAnError = true;
														COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): Could not load <");
														COMMON_LOG_VERBOSE(lib->pathToLibrary);
														COMMON_LOG_VERBOSE("> Host function returned: ");
														COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
												}
												else
												{
														/* Cast the OS specific data structure pointer to void*.  */
														lib->osSpecificPointerData = (void*)callResult;
		
														/* Set bIsLoaded. */
														lib->bIsLoaded = true;

														/* Clear lib->bLastCallEncounteredAnError. */
														lib->bLastCallEncounteredAnError = false;

														/* Success. */
														ret = COMMON_ERROR_SUCCESS;
														COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): <");
														COMMON_LOG_VERBOSE(lib->pathToLibrary);
														COMMON_LOG_VERBOSE("> loaded.");
												}
										}
										else
										{
												/* Encountered an error during the unload. */
												ret = retFromCall;
												lib->bLastCallEncounteredAnError = true;
												COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): Unable to reload library.");
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
								lib->bLastCallEncounteredAnError = true;
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): No path to the library was given. Unable to load a library without the path to it.");
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
				DWORD retFL = 0;								/* Error code from FreeLibrary(). */

				/* Check to see if the pointer to the management structure is valid. */
				if (lib != NULL)
				{
						/* Reset bLastCallEncounteredAnError. */
						lib->bLastCallEncounteredAnError = false;
		
						/* Check and see if the OS specific data structure pointer is valid. */
						if ((lib->bIsLoaded) && (lib->osSpecificPointerData != NULL))
						{
								/* Call FreeLibrary. */
								if (FreeLibrary((HMODULE)lib->osSpecificPointerData))
								{
										/* The library was unloaded successfully. */
										lib->bIsLoaded = false;
										lib->osSpecificPointerData = NULL;
										lib->bLastCallEncounteredAnError = false;

										/* Success. */
										ret = COMMON_ERROR_SUCCESS;
										COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): <";
										COMMON_LOG_VERBOSE(lib->pathToLibrary);
										COMMON_LOG_VERBOSE("> unloaded.");
								}
								else
								{
										/* Get the last error. */
										retFL = GetLastError();
										retFromCall = Common_Translate_Windows_Error_Code_To_Common_Error_Code(retFL);

										/* Could not unload the library. */
										ret = retFromCall;
										lib->bLastCallEncounteredAnError = true;
										COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not unload <");
										COMMON_LOG_VERBOSE(lib->pathToLibrary);
										COMMON_LOG_VERBOSE("> Host function returned: ");
										COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
								}
						}
						else
						{
								/* Library is not loaded. */
								ret = DYNLIB_ERROR_LIBRARY_NOT_LOADED;
								lib->bLastCallEncounteredAnError = true;
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): The given library <");
								COMMON_LOG_VERBOSE(lib->pathToLibrary);
								COMMON_LOG_VERBOSE("> is not loaded.");
						}
				}
				else
				{
						/* Management structure is invalid. */
						ret = COMMON_ERROR_INVALID_ARGUMENT_ERROR;
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
				DWORD retGPA = 0;								/* Error code from GetProcAddress(). */

				/* Check to see if the pointer to the management structure is valid. */
				if (lib != NULL)
				{
					/* Reset bLastCallEncounteredAnError. */
					lib->bLastCallEncounteredAnError = false;
		
					/* Check and see if retSym is valid. */
					if (retSym != NULL)
					{
						/* Check to see if symbolName is NULL. */
						if (symbolName != NULL)
						{
								/* Check for a loaded library. */
								if (((lib->bIsLoaded) && (lib->osSpecificPointerData != NULL)))
								{
									/* Get the address. */
									pSym = (void*)GetProcAddress((HMODULE)lib->osSpecificPointerData, symbolName);
									if (pSym == NULL)
									{
										/* Get the last error. */
										retGPA = GetLastError();
										retFromCall = Common_Translate_Windows_Error_Code_To_Common_Error_Code(retGPA);

										/* An error occured fetching the symbol. */
										ret = retFromCall;
										lib->bLastCallEncounteredAnError = true;
										COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not fetch symbol in <");
										COMMON_LOG_VERBOSE(lib->pathToLibrary);
										COMMON_LOG_VERBOSE("> Host function returned: ");
										COMMON_LOG_VERBOSE(Common_Get_Error_Message(retFromCall));
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
									/* Library is not loaded. */
									ret = DYNLIB_ERROR_LIBRARY_NOT_LOADED;
									lib->bLastCallEncounteredAnError = true;
									COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): The given library <");
									COMMON_LOG_VERBOSE(lib->pathToLibrary);
									COMMON_LOG_VERBOSE("> is not loaded.");
								}
						}
						else
						{
							/* symbolName is NULL. */
							ret = COMMON_ERROR_INVALID_ARGUMENT;
							lib->bLastCallEncounteredAnError = true;
							COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): No symbol name was given, cannot load a symbol without a name to identifiy it.");
						}
					}
					else
					{
						/* retSym is NULL. */
						ret = COMMON_ERROR_INVALID_ARGUMENT;
						lib->bLastCallEncounteredAnError = true;
						COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): ");
						COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
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

