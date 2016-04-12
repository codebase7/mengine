/*!
    Multiverse Engine Project 23/1/2016 Dynamic_Library_Subsystem Dynamic_Library_Subsystem.c

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
#include "Dynamic_Library_Subsystem.h"
#include "Dynamic_Library_Subsystem_Syscall.h"
#include "../Error_Handler/Common_Error_Handler_Structures.h"
#include "../Error_Handler/Common_Error_Handler_Error_Codes.h"
#include "../Error_Handler/Common_Error_Handler_Log_Channel_Defs.h"
#include "../../../Core/Src/DataProcess.h"

/* External includes. */
#include <stddef.h>
#include <string.h>

/* Define the MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID macro. */
#define MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID MSYS_ERROR_LOG_CHANNEL_DYNLIB

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
		const char * tempPath = NULL;							/* Used to verifiy that the path was stored in the management structure. */
		size_t tempPathLength = 0;						/* Used to store the length of the tempPath string in bytes. */
		char * copiedPathFromStruct = NULL;				/* Used to copy the path from the management structure during a reload. */
		size_t copiedPathLengthFromStruct = 0;			/* Used to store the length of the tempPath string in bytes. */
		void * callResult = NULL;						/* The result of the call the engine's syscall function. */

		/* Check to see if the pointer to the management structure is valid. */
		if (lib != NULL)
		{
			/* Check to see if pathToLibrary is NULL. */
			if ((pathToLibrary != NULL) && (pathToLibraryLength > 0))
			{
				/* Check to see if the library is loaded. */
				retFromCall = Common_Dynamic_Library_Subsystem_Get_IsLoaded_Loaded_Dynamic_Library(lib);
				if ((retFromCall == COMMON_ERROR_FALSE) || (reloadLibrary))
				{
					/* Check and see if the library is loaded. */
					if (retFromCall == COMMON_ERROR_TRUE)
					{
						/* Get the pathToLibrary pointer from the management structure. */
						retFromCall = Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &tempPath, &tempPathLength);
						if (retFromCall == COMMON_ERROR_SUCCESS)
						{
							/* Check and see if the given pathToLibrary is from the lib structure. */
							if (tempPath == pathToLibrary)
							{
								/* Copy the length data. */
								copiedPathLengthFromStruct = tempPathLength;

								/* We need to copy the pathToLibrary data. */
								retFromCall = DataProcess_Reallocate_C_String(&copiedPathFromStruct, 0, copiedPathLengthFromStruct);
								if ((retFromCall == COMMON_ERROR_SUCCESS) && (copiedPathFromStruct != NULL))
								{
									/* Copy the path string. */
									memcpy(copiedPathFromStruct, tempPath, copiedPathLengthFromStruct);
								}
								else
								{
									/* Could not allocate memory for tempPath. */
									ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
									COMMON_LOG_DEBUG(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): Memory allocation function returned: ");
									COMMON_LOG_DEBUG(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
								}

								/* Reset tempPath and tempPathLength. */
								tempPath = NULL;
								tempPathLength = 0;
							}

							/* Call Unload_Library. */
							retFromCall = Common_Dynamic_Library_Subsystem_Unload_Library(lib);
						}
						else
						{
							/* Could not get the pathToLibrary pointer from the data structure. */
							ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
							retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): Unable to get the pathToLibrary pointer from the data structure.");
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Engine call returned: ");
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
							if (retFromCall != COMMON_ERROR_SUCCESS)
							{
								/* Log additional error. */
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
							}
						}
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
						retFromCall = Common_Dynamic_Library_Subsystem_Set_PathToLibrary_Loaded_Dynamic_Library(lib, ((copiedPathFromStruct == NULL) ? (pathToLibrary) : (copiedPathFromStruct)), ((copiedPathLengthFromStruct == 0) ? (pathToLibraryLength) : (copiedPathLengthFromStruct)));
						if (retFromCall == COMMON_ERROR_SUCCESS)
						{
							/* Get the path back. */
							retFromCall = Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &tempPath, &tempPathLength);
							if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempPath != NULL) && (tempPathLength > 0))
							{
								/* Call Syscall. */
								retFromCall = Common_Dynamic_Library_Subsystem_Load_Library_Syscall(tempPath, tempPathLength, &callResult);
								if (retFromCall == COMMON_ERROR_SUCCESS)
								{
									/* Copy returned osSpecificPointerData to the management structure. */
									retFromCall = Common_Dynamic_Library_Subsystem_Set_OsSpecificPointerData_Loaded_Dynamic_Library(lib, callResult);
									if (retFromCall == COMMON_ERROR_SUCCESS)
									{
										/* Set bIsLoaded. */
										retFromCall = Common_Dynamic_Library_Subsystem_Set_IsLoaded_Loaded_Dynamic_Library(lib, true);
										if (retFromCall == COMMON_ERROR_SUCCESS)
										{
											/* Success. */
											ret = COMMON_ERROR_SUCCESS;
											COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): <");
											COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, tempPath);
											COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> loaded.");
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
								else
								{
									/* Could not get osSpecificPointerData. Syscall failed. Set bLastCallEncounteredAnError flag in management structure. */
									ret = retFromCall;
									retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library_Syscall(): Could not load <");
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, pathToLibrary);
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> Host function returned: ");
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
									if (retFromCall != COMMON_ERROR_SUCCESS)
									{
										/* Log additional error. */
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
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
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): Unable to reload library.");
						if (retFromCall != COMMON_ERROR_SUCCESS)
						{
							/* Log additional error. */
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
						}
					}
				}
				else
				{
					/* Check and see if the library was already loaded. */
					if (retFromCall == COMMON_ERROR_TRUE)
					{
						/* Library is already loaded. */
						ret = DYNLIB_ERROR_LIBRARY_ALREADY_LOADED;
					}
					else
					{
						/* An error occured. */
						ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): Could not get loaded library flag from management structure. Engine call returned: ");
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
					}
				}
			}
			else
			{
				/* pathToLibrary is NULL. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): No path to the library was given. Unable to load a library without the path to it.");
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					/* Log additional error. */
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Management structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Load_Library(): The engine's library structure for the given library is invalid. Unable to load a library without a valid library structure.");
		}

		/* Check for an allocated copiedPathFromStruct and deallocate it if needed. */
		if (copiedPathFromStruct != NULL)
		{
			DataProcess_Deallocate_CString(&copiedPathFromStruct);
			copiedPathLengthFromStruct = 0;
		}

		/* Exit function. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Unload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		void * osData = NULL;							/* The osSpecificPointerData from the management structure. */
		char * pSym = NULL;								/* Used to log the library path to the error log. */
		size_t pSymLength = 0;							/* The length of pSym in bytes. */

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
						/* Call the syscall. */
						retFromCall = Common_Dynamic_Library_Subsystem_Unload_Library_Syscall(osData);
						if (retFromCall == COMMON_ERROR_SUCCESS)
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
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): <");

									/* Attempt to get the library path for the error log. */
									if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &pSym, &pSymLength) == COMMON_ERROR_SUCCESS) &&
										(pSym != NULL))
									{
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, pSym);
									}
									else
									{
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
									}
									pSym = NULL;	/* Clear abused pSym. */

									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> unloaded.");
								}
								else
								{
									/* Could not clear os specific pointer data in management structure. */
									ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
									retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): Could not clear os specific pointer data in management structure. Call returned: ");
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
									if (retFromCall != COMMON_ERROR_SUCCESS)
									{
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
									}
								}
							}
							else
							{
								/* Could not clear is loaded flag in management structure. */
								ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
								retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): Could not clear is loaded flag in management structure. Call returned: ");
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
								if (retFromCall != COMMON_ERROR_SUCCESS)
								{
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
								}
							}
						}
						else
						{
							/* Could not unload the library. */
							ret = retFromCall;
							retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): Could not unload <");

							/* Attempt to get the library path for the error log. */
							if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &pSym, &pSymLength) == COMMON_ERROR_SUCCESS) &&
								(pSym != NULL))
							{
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, pSym);
							}
							else
							{
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
							}
							pSym = NULL;	/* Clear abused pSym. */

							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> Host function returned: ");
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
							if (retFromCall != COMMON_ERROR_SUCCESS)
							{
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
							}
						}
					}
					else
					{
						/* Could not get osSpecificPointerData from management structure. */
						ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): Could not get os specific data pointer from management structure. Call returned: ");
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
					}
				}
				else
				{
					/* Could not reset last call incountered an error flag. */
					ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): Could not reset management structure's error flag. Call returned: ");
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
				}
			}
			else
			{
				/* Library is not loaded. */
				ret = DYNLIB_ERROR_LIBRARY_NOT_LOADED;
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): The given library <");

				/* Attempt to get the library path for the error log. */
				if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &pSym, &pSymLength) == COMMON_ERROR_SUCCESS) &&
					(pSym != NULL))
				{
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, pSym);
				}
				else
				{
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
				}
				pSym = NULL;	/* Clear abused pSym. */

				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> is not loaded.");
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Management structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Unload_Library(): The engine's library structure for the given library is invalid. Unable to unload a library without a valid library structure.");
		}

		/* Return result. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Reload_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		char * tempPath = NULL;							/* Used to verifiy that the path was stored in the management structure. */
		size_t tempPathLength = 0;						/* Used to store the length of the tempPath string in bytes. */

		/* Check for invalid arguments. */
		if (lib != NULL)
		{
			/* Get the pathToLibrary pointer from the management structure. */
			retFromCall = Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, &tempPath, &tempPathLength);
			if (retFromCall == COMMON_ERROR_SUCCESS)
			{
				/* Check for valid path data */
				if ((tempPath != NULL) && (tempPathLength > 0))
				{
					/* Call Common_Dynamic_Library_Subsystem_Load_Library(). */
					ret = Common_Dynamic_Library_Subsystem_Load_Library(tempPath, tempPathLength, true, lib);
				}
				else
				{
					/* The given library structure does not define a path. */
					ret = COMMON_ERROR_INVALID_ARGUMENT;
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Reload_Library(): The given library structure does not define a path.");
				}
			}
			else
			{
				/* Could not get the pathToLibrary pointer from the data structure. */
				ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Reload_Library(): Unable to get the pathToLibrary pointer from the data structure.");
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Engine call returned: ");
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					/* Log additional error. */
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, we could not set the error flag for the internal library structure. Engine Call returned: ");
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Library structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Reload_Library(): The engine's library structure for the given library is invalid.");
		}

		/* Exit function. */
		return ret;
	}

	int Common_Dynamic_Library_Subsystem_Get_Symbol(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library *const lib, const char * symbolName, const size_t symbolNameLength, void ** retSym)
	{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		void * pSym = NULL;								/* The returned symbol pointer. */
		size_t pSymLength = 0;							/* The length of pSym (When being abused as a path string) in bytes. */
		void * osData = NULL;							/* The osSpecificPointerData from the management structure. */

		/* Check to see if the pointer to the management structure is valid. */
		if (lib != NULL)
		{
			/* Check and see if retSym is valid. */
			if (retSym != NULL)
			{
				/* Check to see if symbolName is NULL, or symbolNameLength is less than or equal to zero. */
				if ((symbolName != NULL) && (symbolNameLength > 0))
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
								/* Call syscall. */
								retFromCall = Common_Dynamic_Library_Subsystem_Get_Symbol_Syscall(osData, symbolName, symbolNameLength, &pSym);
								if (retFromCall == COMMON_ERROR_SUCCESS)
								{
									/* Copy pSym to retSym. */
									(*retSym) = pSym;

									/* Success. */
									ret = COMMON_ERROR_SUCCESS;
								}
								else
								{
									/* An error occured fetching the symbol. */
									ret = retFromCall;
									retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not fetch symbol in <");

									/* Attempt to get the library path for the error log. */
									if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, (char**)&pSym, &pSymLength) == COMMON_ERROR_SUCCESS) &&
										(pSym != NULL))
									{
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, (char*)pSym);
									}
									else
									{
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
									}
									pSym = NULL;	/* Clear abused pSym. */

									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> Host function returned: ");
									COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(ret));
									if (retFromCall != COMMON_ERROR_SUCCESS)
									{
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
										COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
									}
								}
							}
							else
							{
								/* Could not get osSpecificPointerData from management structure. */
								ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not get os specific data pointer from management structure. Call returned: ");
								COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
							}
						}
						else
						{
							/* Could not reset last call incountered an error flag. */
							ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (retFromCall) : (COMMON_ERROR_INTERNAL_ERROR));
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): Could not reset management structure's error flag. Call returned: ");
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
						}
					}
					else
					{
						/* Library is not loaded. */
						ret = DYNLIB_ERROR_LIBRARY_NOT_LOADED;
						retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): The given library <");

						/* Attempt to get the library path for the error log. */
						if ((Common_Dynamic_Library_Subsystem_Get_PathToLibrary_Loaded_Dynamic_Library(lib, (char**)&pSym, &pSymLength) == COMMON_ERROR_SUCCESS) &&
							(pSym != NULL))
						{
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, (char*)pSym);
						}
						else
						{
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "[ERROR: COULD NOT FETCH PATH TO LIBRARY FROM MANAGEMENT STRUCTURE.]");
						}
						pSym = NULL;	/* Clear abused pSym. */

						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "> is not loaded.");
						if (retFromCall != COMMON_ERROR_SUCCESS)
						{
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
							COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
						}
					}
				}
				else
				{
					/* symbolName is NULL. */
					ret = COMMON_ERROR_INVALID_ARGUMENT;
					retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): No symbol name was given, cannot load a symbol without a name to identifiy it.");
					if (retFromCall != COMMON_ERROR_SUCCESS)
					{
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
						COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
					}
				}
			}
			else
			{
				/* retSym is NULL. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
				retFromCall = Common_Dynamic_Library_Subsystem_Set_LastCallEncounteredError_Loaded_Dynamic_Library(lib, true);
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): ");
				COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
				if (retFromCall != COMMON_ERROR_SUCCESS)
				{
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, " Additionally, could not set the error flag in the management structure. Call returned: ");
					COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, Common_Get_Error_Message(retFromCall));
				}
			}
		}
		else
		{
			/* Library structure is invalid. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;
			COMMON_LOG_VERBOSE(MSYS_SUBSYS_DEFAULT_ERROR_CHANNEL_ID, "Common_Dynamic_Library_Subsystem_Get_Symbol(): The engine's library structure for the given library is invalid. Unable to lookup function without a valid library structure.");
		}

		/* Return result. */
		return ret;
	}

#ifdef __cplusplus
}		/* End of extern C. */
#endif	/* __cplusplus */
