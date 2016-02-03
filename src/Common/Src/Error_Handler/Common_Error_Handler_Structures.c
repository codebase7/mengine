/*!
    Multiverse Engine Project 16/5/2015 Common Common_Error_Handler_Structures.c

    Copyright (C) 2015 Multiverse Engine Project

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

/* Internal Includes. */
#include "Common_Error_Handler.h"

/* Enable C linkage if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
 * 	const char * COMMON_ERROR_UNKNOWN_ERROR_MSG
 *
 * 	This is the definition for the generic unknown error
 * 	code.
 *
 * 	It is defined here to allow Common_Get_Error_Message()
 * 	to reference it without needing to use another for loop
 * 	to locate it's offset in the error message table.
 */
const char COMMON_ERROR_UNKNOWN_ERROR_MSG[] = COMMON_UNKNOWN_ERROR_MSG_DEF;

/*!
 * 	const Common_Error_Object Common_commonErrorTable[]
 * 
 * 	This array contains all of the error codes that a Common namespace
 * 	function may return, in addition to a human readable string describing
 * 	the error code's meaning. (This is a work in progress, some error codes
 * 	conflict with error codes in other functions, as such these are slowly
 * 	being corrected.)
 * 
 * 	The easiest way of fetching the human readable string from this table
 * 	is to call Common::GetErrorMessage().
 *
 * 	Do not reuse an existing error code. (If the error is generic then use a
 * 	generic error code.)
 * 
 * 	Do not change an existing error code. (This is to keep the API stable
 * 	between revisions.)
 */
const Common_Error_Object Common_commonErrorTable[] = {
	/* Define the initilizers for the lookup table. */
	{COMMON_ERROR_UNKNOWN_ERROR, COMMON_ERROR_UNKNOWN_ERROR_MSG},
	{COMMON_ERROR_SYSTEM_SPECIFIC, "System specific error code. Check log."},
	{COMMON_ERROR_SUCCESS, "Success."},
	{COMMON_ERROR_INVALID_ARGUMENT, "Invalid argument."},
	{COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED, "Function not implemented."},
	{COMMON_ERROR_ACCESS_DENIED, "Access Denied."},
	{COMMON_ERROR_EXCEPTION_THROWN, "Execption thrown."},
	{COMMON_ERROR_INTERNAL_ERROR, "Internal error."},
	{COMMON_ERROR_IO_ERROR, "Input / Output error. (Normally this is a hardware issue.)"},
	{COMMON_ERROR_RANGE_ERROR, "Given range is invalid."},
	{COMMON_ERROR_MEMORY_ERROR, "Memory error (Could not allocate memory / Control loop out of bounds.)"},
	{COMMON_ERROR_INVALID_LIBRARY_ID, "Given LibraryID does not match a supported library or a loaded plugin."},
	{COMMON_ERROR_PEBKAC_INVALID_OPERATION_ORDER, "Caller is attempting to do something that requires another call / process to be completed first. (Check the order in which you are doing things.)"},
	{COMMON_ERROR_CANNOT_GET_SYSTEM_TIME, "Could not get the system's current time."},
	{COMMON_ERROR_SUBSYSTEM_OBJECT_NOT_INITED, "Given object has not been inited yet."},
	{COMMON_ERROR_SUBSYSTEM_OBJECT_ALREADY_INITED, "Given object has already been inited."},
	{COMMON_ERROR_END_OF_DATA, "There is no remaining data to process."},
	{COMMON_ERROR_COMPARISON_PASSED, "A check passed it's requirements."},
	{COMMON_ERROR_COMPARISON_FAILED, "A check failed to pass it's requirements."},
	{COMMON_ERROR_RACE_CONDITION, "Another process or thread has altered the state of an object needed by the function while the function was using it. Because of the modification to the object, the function could not complete it's task successfully. Please make sure nothing is accessing the needed object before calling the function again."},
	{COMMON_ERROR_HOST_NOT_SUPPORTED, "The host system does not support the requested function / command / feature."},
	{COMMON_ERROR_TRUE, "The result of the previous operation returned true. (See the code documentation for what the result actually means. This is just a generic boolean response.)"},
	{COMMON_ERROR_FALSE, "The result of the previous operation returned false. (See the code documentation for what the result actually means. This is just a generic boolean response.)"},
	{COMMON_ERROR_ARGUMENT_CONVERSION_FAILURE, "A given argument to the previous engine call was not converted properly. (See the code documentation for what the result actually means.)"},
	{COMMON_ERROR_FALSE_SUCCESS, "A success code was returned without a valid result. (AKA. Some expected return value was not obtained, was invalid, corrupted, etc. This can happen when the engine interacts with poorly written / designed code. Including when interacting with itself.)"},
	/* Rendering Subsystem error codes. */
	{RENDERER_ERROR_UNABLE_TO_ALLOC_OI_BUF, "Could not allocate memory for overlay image buffer."},
	{RENDERER_ERROR_UNABLE_TO_ALLOC_TD_BUF, "Could not allocate memory for transparency data buffer."},
	{RENDERER_ERROR_MEM_BUF_ALLOC_EXCEPTION, "Exception thrown while attempting to allocate memory buffer(s)."},
	{RENDERER_ERROR_DUPE_OVERLAY_EXCEPTION, "Exception thrown while duplicating overlay, clearing dest overlay."},
	{RENDERER_ERROR_INVAL_OVERLAY_SELF_OVERWRITE, "Given overlays are the same. Cannot overwrite an overlay with itself."},
	{RENDERER_ERROR_TRANSPARENCY_DISABLED, "Transparency is disabled on given overlay."},
	/* Threading Subsystem (Thread_Utils) error codes. */
	{THREAD_UTILS_ERROR_EXCEPTION_THROWN, "Exception thrown in threading subsystem."},
	{THREAD_UTILS_ERROR_PLUGIN_LOAD_FAILURE, "Unable to load plugin(s). Internal error."},
	{THREAD_UTILS_ERROR_THREAD_COULD_NOT_START, "Could not start new thread."},
	{THREAD_UTILS_ERROR_THREAD_COULD_NOT_DETACH, "Could not detach thread."},
	{THREAD_UTILS_ERROR_THREAD_COULD_NOT_JOIN, "Could not join thread."},
	{THREAD_UTILS_ERROR_MUTEX_ALREADY_LOCKED, "The given mutex is already locked."},
	{THREAD_UTILS_ERROR_CONDITION_WAIT_TIMEOUT_REACHED, "Given timeout period was exceeded while waiting for the condition variable to signal."},
	{THREAD_UTILS_ERROR_CONDITION_CANNOT_LOCK_MUTEX, "Could not lock internal mutex in condition variable object."},
	/* FileUtills. */
	{FILEUTILLS_ERROR_EXISTANT, "The path exists."},
	{FILEUTILLS_ERROR_NON_EXISTANT, "The path (or a component of the path) does not exist."},
	{FILEUTILLS_ERROR_READ_ONLY, "The path is read only."},
	{FILEUTILLS_ERROR_PATH_LENGTH_INVALID, "The path's length is beyond the filesystem's maximum length."},
	{FILEUTILLS_ERROR_PATH_FILE_AS_DIRECTORY, "The path has a file in it that is being treated as a directory."},
	{FILEUTILLS_ERROR_PATH_IS_A_FILE, "Given path is a file."},
	{FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY, "Given path is a directory."},
	{FILEUTILLS_ERROR_PATH_IS_A_SYMLINK, "Given path is a symbolic link."},
	{FILEUTILLS_ERROR_PATH_IS_ABSOLUTE, "Given path is in absolute format (Fully resolved)."},
	{FILEUTILLS_ERROR_PATH_IS_RELATIVE, "Given path is in relative format (Needs resolving)."},
	{FILEUTILLS_ERROR_FILESYSTEM_FULL, "Given filesystem is full."},
	{FILEUTILLS_ERROR_FILESYSTEM_QUOTA_REACHED, "User's disk usage quota for the given filesystem has been reached."},
	{FILEUTILLS_ERROR_EMPTY_DIRECTORY, "The given path is an empty directory."},
	{FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY, "The given path is a non-empty directory."},
	{FILEUTILLS_ERROR_SYMLINK_CHAIN_TOO_DEEP, "While parsing a host-defined symbolic link chain, the host system indicated the link chain was longer than what it supports."},
	/* UI Subsystem */
	{UI_SUBSYSTEM_ERROR_EXCEPTION_THROWN, "An exception was thrown in the UI Subsystem."},
	/* Dynamic Library Subsystem. */
	{DYNLIB_ERROR_INVALID_LIBRARY, "The given library is not recognized by the system. (Invalid container format / not a library / data corruption / etc.)"},
	{DYNLIB_ERROR_LIBRARY_ALREADY_LOADED, "The given library is already loaded."},
	{DYNLIB_ERROR_LIBRARY_NOT_LOADED, "The given library is not currently loaded."},
	{DYNLIB_ERROR_HOST_VS_LIBRARY_MISMATCH, "The given library was built for a different system. (Different OS / Arch / etc.)"},
	{DYNLIB_ERROR_SYMBOL_NOT_FOUND, "The requested symbol was not found in the given library."},
	/* TODO: Need to add the error codes from all common namespace functions. */
};

const unsigned int Common_Get_Error_Table_API_Version()
{
	return COMMON_ERROR_TABLE_ABI_VER;
}

const unsigned int Common_Get_Error_Table_Size()
{
	return (sizeof(Common_commonErrorTable) / sizeof(Common_Error_Object));
}

const char * Common_Get_Error_Message(const int errorCode)
{
	/* Init vars. */
	const char * result = COMMON_ERROR_UNKNOWN_ERROR_MSG;			/* Result of this function. */
	const size_t errorTableSize = Common_Get_Error_Table_Size();	/* Size of the Common error lookup table. */
	size_t x = 0;													/* Counter used in for loop. */

	/* Check for COMMON_UNKNOWN_ERROR. */
	if (errorCode != COMMON_ERROR_UNKNOWN_ERROR)
	{
		/* Begin lookup loop. */
		for (x = 0; ((x < errorTableSize) && (result == COMMON_ERROR_UNKNOWN_ERROR_MSG)); x++)
		{
			/* Check for the correct error code. */
			if (Common_commonErrorTable[x].errorCode == errorCode)
			{
				/* Found the correct error code. */
				result = Common_commonErrorTable[x].error;
			}
		}
	}

	/* Return the result. */
	return result;
}

/* End C Linkage if needed. */
#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus	*/
