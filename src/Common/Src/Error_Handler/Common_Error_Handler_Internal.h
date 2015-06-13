/*!
    Multiverse Engine Project 04/7/2014 Common Common_Error_Handler_Internal.h (INTERNAL ENGINE USE ONLY)

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
#ifndef COMMON_ERROR_HANDLER_INTERNAL_H
#define COMMON_ERROR_HANDLER_INTERNAL_H

// Project includes.
#ifdef __win32	// Needed for different path seperator in Windows.
#include "..\..\..\Core\Src\Panic_Error_Levels.h"	// Defines the log levels.
#else
#include "../../../Core/Src/Panic_Error_Levels.h"	// Defines the log levels.
#endif // __win32

// Check to see if we are being included directly.
//#ifndef COMMON_ERROR_HANDLER_H
//#error "This header is for internal engine use only. It should not be linked against, as it is NOT a part of the public API."
//#endif // COMMON_ERROR_HANDLER_H

/*
 * 	struct CommonErrorLogData
 *
 * 	Private data struct to contain the registered error
 * 	log callback pointer and current log level for the
 * 	Common namespace functions.
 * 
 * 	Note: We declare this here as the structure
 * 	and it's definition is supposed to be private
 * 	to the engine. DO NOT USE THIS STRUCTURE DIRECTLY!
 * 	This structure is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
struct CommonErrorLogData {
	unsigned int errorLogLevel;	// Current log level.
	void (*loggingFunct)(const unsigned int logLevel, const char * errorMsg); // Pointer to current callback function.
};

/*
 * 	static struct CommonErrorLogData commonErrorLoggingData
 * 
 * 	The actual data structure that contains the error
 * 	logging data for the Common namespace functions.
 * 
 * 	Once again, DO NOT USE THIS STRUCTURE DIRECTLY!
 * 	This structure is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
static struct CommonErrorLogData commonErrorLoggingData = {ERROR_DISABLE, NULL};

/*
 * 	void COMMON_LOG_ERROR(const unsigned int loggingLevel, const char * errorMsg)
 * 
 * 	This is the actual function that calls the current
 * 	error logging callback function for the Common
 * 	namespace functions.
 * 
 * 	DO NOT USE THIS FUNCTION DIRECTLY!
 * 	This function is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
MSYS_DLL_EXPORT void COMMON_LOG_ERROR(const unsigned int loggingLevel, const char * errorMsg);

/*
 * 	COMMON_LOG_CRITICAL(const char * errorMsg)
 * 
 * 	Internal API for calling the current callback error
 * 	logging function with a log level of ERROR_CRITICAL.
 * 
 * 	DO NOT USE THIS FUNCTION DIRECTLY!
 * 	This function is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
MSYS_DLL_EXPORT void COMMON_LOG_CRITICAL(const char * errorMsg);

/*
 * 	COMMON_LOG_WARNING(const char * errorMsg)
 * 
 * 	Internal API for calling the current callback error
 * 	logging function with a log level of ERROR_WARNING.
 * 
 * 	DO NOT USE THIS FUNCTION DIRECTLY!
 * 	This function is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
MSYS_DLL_EXPORT void COMMON_LOG_WARNING(const char * errorMsg);

/*
 * 	COMMON_LOG_INFO(const char * errorMsg)
 * 
 * 	Internal API for calling the current callback error
 * 	logging function with a log level of ERROR_INFO.
 * 
 * 	DO NOT USE THIS FUNCTION DIRECTLY!
 * 	This function is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
MSYS_DLL_EXPORT void COMMON_LOG_INFO(const char * errorMsg);

/*
 * 	COMMON_LOG_DEBUG(const char * errorMsg)
 * 
 * 	Internal API for calling the current callback error
 * 	logging function with a log level of ERROR_DEBUG.
 * 
 * 	DO NOT USE THIS FUNCTION DIRECTLY!
 * 	This function is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
MSYS_DLL_EXPORT void COMMON_LOG_DEBUG(const char * errorMsg);

/*
 * 	COMMON_LOG_VERBOSE(const char * errorMsg)
 * 
 * 	Internal API for calling the current callback error
 * 	logging function with a log level of ERROR_VERBOSE.
 * 
 * 	DO NOT USE THIS FUNCTION DIRECTLY!
 * 	This function is NOT a part of the public API, and
 * 	is subject to change at anytime.
 */
MSYS_DLL_EXPORT void COMMON_LOG_VERBOSE(const char * errorMsg);

#endif // COMMON_ERROR_HANDLER_INTERNAL_H

// End of Common_Error_Handler_Internal.h
