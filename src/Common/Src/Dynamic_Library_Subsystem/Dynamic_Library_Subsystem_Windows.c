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

#include "Dynamic_Library_Subsystem.h"
#include <windows.h>

#ifdef __cplusplus
// Define extern C.
extern "C" {
#endif
		int Common_Dynamic_Library_Subsystem_Load_Library(const char * pathToLibrary, const bool reloadLibrary, Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		{
				// Init vars.
				int result = 0;				// The result of this function.
				HMODULE callResult = NULL;	// The result of the call to LoadLibraryEx().

				// Check to see if the pointer to the management structure is valid.
				if (lib != NULL)
				{
						// Check to see if pathToLibrary is NULL.
						if (pathToLibrary != NULL)
						{
								// Check to see if the library is loaded.
								if ((!lib->bIsLoaded) || (reloadLibrary))
								{
										// Check and see if the library is loaded.
										if (lib->bIsLoaded)
										{
												// Call Unload_Library.
												result = Common_Dynamic_Library_Subsystem_Unload_Library(lib);
										}
		
										// Only continue if the library was unloaded, or if we did not need to unload the library.
										if (result == 0)
										{
												// Set the values in lib.
												lib->bIsLoaded = false;
												lib->bLastCallEncounteredAnError = false;
												lib->osSpecificPointerData = NULL;
												lib->pathToLibrary = pathToLibrary;
		
												// Call LoadLibraryEx().
												callResult = LoadLibraryEx(lib->pathToLibrary, NULL, 0);
		
												// Check the callResult.
												if (callResult == NULL)
												{
														// Could not load the library.
														result = -1;
														lib->bLastCallEncounteredAnError = true;
														COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): Could not load the library.\n");
												}
												else
												{
														// Cast the OS specific data structure pointer to void*. 
														lib->osSpecificPointerData = (void*)callResult;
		
														// Set bIsLoaded.
														lib->bIsLoaded = true;
												}
										}
										else
										{
												// Encountered an error during the unload.
												result = -2;
												lib->bLastCallEncounteredAnError = true;
												COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): Unable to reload library.\n");
										}
								}
								else
								{
										// Library is already loaded.
										result = 1;
								}
						}
						else
						{
								// pathToLibrary is NULL.
								result = -3;
								lib->bLastCallEncounteredAnError = true;
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): No path to the library was given. Unable to load a library without the path to it.\n");
						}
				}
				else
				{
						// Management structure is invalid.
						result = -4;
						COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Load_Library(): The engine's library structure for the given library is invalid. Unable to load a library without a valid library structure.\n");
				}

				// Return result.
				return result;
		}

		int Common_Dynamic_Library_Subsystem_Unload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		{
				// Init vars.
				int result = 0;				// The result of this function.

				// Check to see if the pointer to the management structure is valid.
				if (lib != NULL)
				{
						// Reset bLastCallEncounteredAnError.
						lib->bLastCallEncounteredAnError = false;
		
						// Check and see if the OS specific data structure pointer is valid.
						if ((lib->bIsLoaded) && (lib->osSpecificPointerData != NULL))
						{
								// Call FreeLibrary.
								if (FreeLibrary((HMODULE)lib->osSpecificPointerData))
								{
										// The library was unloaded successfully.
										lib->bIsLoaded = false;
										lib->osSpecificPointerData = NULL;
								}
								else
								{
										// Could not unload the library.
										result = -2;
										lib->bLastCallEncounteredAnError = true;
										COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): Could not unload the library.\n");
								}
						}
						else
						{
								// Library is not loaded.
								result = -1;
								lib->bLastCallEncounteredAnError = true;
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): The library is not loaded.\n");
						}
				}
				else
				{
						// Management structure is invalid.
						result = -4;
						COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Unload_Library(): The engine's library structure for the given library is invalid. Unable to unload a library without a valid library structure.\n");
				}

				// Return result.
				return result;
		}

		void * Common_Dynamic_Library_Subsystem_Get_Symbol(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib, const char * symbolName)
		{
				// Init vars.
				void * result = NULL;				// The result of this function.

				// Check to see if the pointer to the management structure is valid.
				if (lib != NULL)
				{
						// Reset bLastCallEncounteredAnError.
						lib->bLastCallEncounteredAnError = false;
		
						// Check to see if symbolName is NULL.
						if (symbolName != NULL)
						{
								// Check for a loaded library.
								if (((lib->bIsLoaded) && (lib->osSpecificPointerData != NULL)))
								{
									// Get the address.
									result = (void*)GetProcAddress((HMODULE)lib->osSpecificPointerData, symbolName);
									if (result == NULL)
									{
										// An error occured fetching the symbol.
										lib->bLastCallEncounteredAnError = true;
										COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): Unable to retrive symbol.\n");
									}
								}
								else
								{
									// Library is not loaded.
									lib->bLastCallEncounteredAnError = true;
									COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): The library is not loaded.\n");
								}
						}
						else
						{
								// symbolName is NULL.
								lib->bLastCallEncounteredAnError = true;
								COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): No symbol name was given, cannot load a symbol without a name to identifiy it.\n");
						}
				}
				else
				{
					// Library structure is invalid.
					COMMON_LOG_VERBOSE("Common_Dynamic_Library_Subsystem_Get_Symbol(): The engine's library structure for the given library is invalid. Unable to lookup function without a valid library structure.\n");
				}

				// Return result.
				return result;
		}
#ifdef __cplusplus
}		// End of extern C.
#endif

