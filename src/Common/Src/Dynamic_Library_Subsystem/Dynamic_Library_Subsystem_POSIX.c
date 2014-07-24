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

#ifdef __linux__
#include "Dynamic_Library_Subsystem.h"
#include <dlfcn.h>	// dlopen, dlclose, dlsym, dlerror.

#ifdef __cplusplus
// Define extern C.
extern "C" {
#endif
		int Common_Dynamic_Library_Subsystem_Load_Library(const char * pathToLibrary, const bool reloadLibrary, Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
		{
				// Init vars.
				int result = 0;				// The result of this function.
				void * callResult = NULL;		// The result of the call to dlopen().

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

												// Call dlopen().
												callResult = dlopen(lib->pathToLibrary, RTLD_LAZY | RTLD_LOCAL);

												// Check the callResult.
												if (callResult == NULL)
												{
														// Could not load the library.
														result = -1;
														lib->bLastCallEncounteredAnError = true;
												}
												else
												{
														// Cast the OS specific data structure pointer to void*.
														lib->osSpecificPointerData = callResult;

														// Set bIsLoaded.
														lib->bIsLoaded = true;
												}
										}
										else
										{
												// Encountered an error during the unload.
												result = -2;
												lib->bLastCallEncounteredAnError = true;
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
						}
				}
				else
				{
						// Management structure is invalid.
						result = -4;
				}

				// Return result.
				return result;
		}

		int Common_Dynamic_Library_Subsystem_Unload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
		{
				// Init vars.
				int result = 0;				// The result of this function.

				// Check to see if the pointer to the management structure is valid.
				if (lib != NULL)
				{
						// Reset bLastCallEncounteredAnError.
						lib->bLastCallEncounteredAnError = false;

						// Check for a valid handle.
						if ((lib->bIsLoaded) && (lib->osSpecificPointerData != NULL))
						{
								// Call dlclose().
								result = dlclose(lib->osSpecificPointerData);

								// Check result.
								if (result != 0)
								{
									// An error occured.
									result = -2;
									lib->bLastCallEncounteredAnError = true;
								}
								else
								{
									// Library unloaded successfully.
									lib->osSpecificPointerData = NULL;
									lib->bIsLoaded = false;
								}
						}
						else
						{
								// Library is not loaded.
								result = -1;
								lib->bLastCallEncounteredAnError = true;
						}
				}
				else
				{
						// Management structure is invalid.
						result = -4;
				}

				// Return result.
				return result;
		}

		void * Common_Dynamic_Library_Subsystem_Get_Symbol(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib, const char * symbolName)
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
								// Check to see if we have a valid handle.
								if ((lib->bIsLoaded) && (lib->osSpecificPointerData != NULL))
								{
										// Call dlerror to clear the error state.
										dlerror();

										// Call dlsym.
										result = dlsym(lib->osSpecificPointerData, symbolName);

										// Call dlerror again to check for an error.
										if (dlerror() != NULL)
										{
											// An error occured.
											result = NULL;
											lib->bLastCallEncounteredAnError = true;
										}
								}
						}
						else
						{
								// symbolName is NULL.
								lib->bLastCallEncounteredAnError = true;
						}
				}

				// Return result.
				return result;
		}
#ifdef __cplusplus
}		// End of extern C.
#endif
#endif
