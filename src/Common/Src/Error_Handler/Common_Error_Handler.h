/*!
    Multiverse Engine Project 23/6/2014 Common Common_Error_Handler.h

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
#ifndef COMMON_ERROR_HANDLER_H
#define COMMON_ERROR_HANDLER_H

/* Pull in DLL_PORT.h */
#include "../../../DLL_PORT.h"	/* Defines MSYS_DLL_EXPORT, and MSYS_DLL_IMPORT_TEMPLATE. */

/* External includes. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

	#include <stddef.h>		/* Defines NULL. */

#ifdef __cplusplus
}	/* End of extern C. */
#endif	/* __cplusplus */

#ifndef __cplusplus
#if _MSC_FULL_VER && _MSC_FULL_VER < 180031101	/* Visual C versions less than 2013 are special. (They lack support for C99's bool type.) */
#include "..\..\..\stdbool.h"		/* Defines bool data type. (For C compilers.) */
#else
#include <stdbool.h>
#endif	/* _MSC_FULL_VER && _MSC_FULL_VER < 180031101 */
#endif	/* __cplusplus */

/* Project includes. */
#ifdef _WIN32	/* Needed for different path seperator in Windows. */
#include "..\..\..\Core\Src\Panic_Error_Levels.h"	/* Defines the log levels. */
#else
#include "../../../Core/Src/Panic_Error_Levels.h"	/* Defines the log levels. */
#include "Posix_Error_Translation_Table.h"		/* Defines the POSIX errno to Common namespace error translation table and functions. */
#endif /* _WIN32 */

#include "Common_Error_Handler_Log_Channel_Defs.h"	/* Defines the error log channels and their related functions. */
#include "Common_Error_Handler_Error_Codes.h"		/* Defines error codes. */
#include "Common_Error_Handler_Structures.h"		/* Defines the error codes, error lookup table error lookup table version number, and Common::commonLastErrorCode. */

/* Define the supported API version numbers. */
#define MSYS_COMMON_ERROR_HANDLER_API_MAJOR_VER 1
#define MSYS_COMMON_ERROR_HANDLER_API_MINOR_VER 0
#define MSYS_COMMON_ERROR_HANDLER_API_REVISION_VER 0

/* Enable C linkage if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Define the C bindings for the error handler. */

/*!
	int Common_Error_Handler_Get_API_Major_Version_Number()

	Returns the API major version number for the Common Error Handler.
 */
MSYS_DLL_EXPORT int Common_Error_Handler_Get_API_Major_Version_Number();

/*!
	int Common_Error_Handler_Get_API_Minor_Version_Number()

	Returns the API minor version number for the Common Error Handler.
 */
MSYS_DLL_EXPORT int Common_Error_Handler_Get_API_Minor_Version_Number();

/*!
	int Common_Error_Handler_Get_API_Revision_Version_Number()

	Returns the API revision version number for the Common Error Handler.
 */
MSYS_DLL_EXPORT int Common_Error_Handler_Get_API_Revision_Version_Number();

/*!
 * 	void Common_Set_Error_Log_Level(const unsigned int & logLevel)
 * 
 * 	Sets the error logging level for the Common namespace functions.
 * 
 * 	By default it sets the error logging level to ERROR_DISABLE.
 * 	(Disables all logging. See Core/Src/Panic.h for a list of
 * 	 valid logging levels.)
 */
MSYS_DLL_EXPORT void Common_Set_Error_Log_Level(const unsigned int logLevel);

/*!
 * 	unsigned int Common_Get_Error_Log_Level()
 * 
 * 	Returns the current error logging level for the Common namespace functions.
 * 
 * 	See Core/Src/Panic.h for a list of valid logging levels.
 */
MSYS_DLL_EXPORT unsigned int Common_Get_Error_Log_Level();

/*!
 * 	void Common_Register_Error_Log_Callback(void (*loggingFunction)(const int channelID, const unsigned int logLevel, const char * errorMsg))
 *
 * 	WARNING: The callback function MUST return control back to
 * 	the caller, as the caller will be blocked until the callback
 * 	function returns.
 * 
 * 	Sets the logging function to call when an error is generated
 * 	by a Common namespace function.
 * 
 * 	For example, this function can be used to send the generated
 * 	errors to the console in a multi-threaded enviroment.
 * 
 * 	Passing a NULL pointer to this function (the default) will
 * 	disable calling another function when an error is generated.
 * 	In addition the logging level will be reset to ERROR_DISABLE.
 */
MSYS_DLL_EXPORT void Common_Register_Error_Log_Callback(void (*loggingFunction)(const int channelID, const unsigned int logLevel, const char * errorMsg));
#ifdef MSYS_BUILD_FATAL_ERROR_SUPPORT

/*!
 * 	typedef void(*Common_pErrorCallBackFunction)(void)
 *
 * 	Defines the function pointer type for use as arguments by the Common fatal error handler functions.
 */
typedef void(*Common_pErrorCallBackFunction)(void);

/*!
 * 	bool Common_Register_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
 *
 * 	WARNING: The callback function MUST return control back to
 * 	the caller, as the caller will be blocked until the callback
 * 	function returns. This means any other registered callbacks
 * 	will not be triggered, which may lead to data loss. The only exception
 * 	to this is if the host system will kill the engine's process after a set
 * 	amount of time. In this one specific instance, nothing can be done to
 * 	prevent the host system from killing the engine. As such the function
 * 	registered with this call should attempt to clean up and return as
 * 	fast as possible.
 *
 * 	Registers a callback function for notification of an engine subsystem
 * 	triggering the host system to kill the engine's process.
 * 	
 * 	Note: The registered callback is not guaranteed to be called at all prior to
 * 	the engine process being terminated. (The host system reserves the right to
 * 	kill the engine without warning it of the impending termination.)
 * 	As such this should be considered an informal notification and not something
 * 	to be relied on if data preservation / security or proper cleanup is required
 * 	prior to engine shutdown.
 *
 * 	Returns true if the regisration completed successfully.
 * 	Returns false otherwise.
 */
MSYS_DLL_EXPORT bool Common_Register_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction);

/*!
 * 	bool Common_Unregister_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
 *
 * 	Unregisters the given fatal error callback function from the list of fatal error
 * 	callback functions to be triggered in the event of a fatal error being generated.
 *
 * 	(I.e. If unregistered, a given callback function will not be called if a fatal
 * 	 error occurs.)
 *
 * 	The callback function pointer given to this function must match a function pointer
 * 	given to Common_Register_Fatal_Error_Callback() (Or Common::Register_Fatal_Error_Callback()) previously,
 * 	otherwise this function will fail.
 *
 * 	Returns true if the unregisration completed successfully.
 * 	Returns false otherwise.
 */
MSYS_DLL_EXPORT bool Common_Unregister_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction);

/*!
 * 	void Common_Fatal_Error_Notify()
 *
 * 	This function triggers the registered fatal error callback functions
 * 	registered with Common_Register_Fatal_Error_Callback() (Or Common::Register_Fatal_Error_Callback()),
 * 	in an attempt to notify all need to know sections of the engine, and application, that the engine is
 * 	about to be terminated.
 *
 * 	When this function returns to it's caller, it is expected that the caller
 * 	will terminate the engine's process if it does not happen automaticly.
 *
 * 	This function does not return any data to it's caller.
 */
MSYS_DLL_EXPORT void Common_Fatal_Error_Notify();
#endif	/* MSYS_BUILD_FATAL_ERROR_SUPPORT */

/* End C Linkage if needed. */
#ifdef __cplusplus
}
#endif	/* __cplusplus */

/* Define C++ Bindings. */
#ifdef __cplusplus
/* Define namespaces. */
namespace Common
{
	/*!
	 * 	void Common::Set_Error_Log_Level(const unsigned int & logLevel)
	 *
	 * 	(C++ Binding)
	 *
	 * 	Sets the error logging level for the Common namespace functions.
	 * 
	 * 	By default it sets the error logging level to ERROR_DISABLE.
	 * 	(Disables all logging. See Core/Src/Panic.h for a list of
	 * 	 valid logging levels.)
	 */
	MSYS_DLL_EXPORT void Set_Error_Log_Level(const unsigned int & logLevel = ERROR_DISABLE);

	/*!
	 * 	unsigned int Common::Get_Error_Log_Level()
	 *
	 * 	(C++ Binding)
	 *
	 * 	Returns the current error logging level for the Common namespace functions.
	 * 
	 * 	See Core/Src/Panic.h for a list of valid logging levels.
	 */
	MSYS_DLL_EXPORT unsigned int Get_Error_Log_Level();

	/*!
	 * 	void Common::Register_Error_Log_Callback(void (*loggingFunction)(const int channelID, const unsigned int logLevel, const char * errorMsg))
	 *
	 * 	(C++ Binding)
	 *
	 * 	WARNING: The callback function MUST return control back to
	 * 	the caller, as the caller will be blocked until the callback
	 * 	function returns.
	 * 
	 * 	Sets the logging function to call when an error is generated
	 * 	by a Common namespace function.
	 * 
	 * 	For example, this function can be used to send the generated
	 * 	errors to the console in a multi-threaded enviroment.
	 * 
	 * 	Passing a NULL pointer to this function (the default) will
	 * 	disable calling another function when an error is generated.
	 * 	In addition the logging level will be reset to ERROR_DISABLE.
	 */
	MSYS_DLL_EXPORT void Register_Error_Log_Callback(void (*loggingFunction)(const int channelID, const unsigned int logLevel, const char * errorMsg) = NULL);

#ifdef MSYS_BUILD_FATAL_ERROR_SUPPORT
	/*!
	 * 	bool Common::Register_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
	 *
	 * 	(C++ Binding)
	 *
	 * 	WARNING: The callback function MUST return control back to
	 * 	the caller, as the caller will be blocked until the callback
	 * 	function returns. This means any other registered callbacks
	 * 	will not be triggered, which may lead to data loss. The only exception
	 * 	to this is if the host system will kill the engine's process after a set
	 * 	amount of time. In this one specific instance, nothing can be done to
	 * 	prevent the host system from killing the engine. As such the function
	 * 	registered with this call should attempt to clean up and return as
	 * 	fast as possible.
	 *
	 * 	Registers a callback function for notification of an engine subsystem
	 * 	triggering the host system to kill the engine's process.
	 * 	
	 * 	Note: The registered callback is not guaranteed to be called at all prior to
	 * 	the engine process being terminated. (The host system reserves the right to
	 * 	kill the engine without warning it of the impending termination.)
	 * 	As such this should be considered an informal notification and not something
	 * 	to be relied on if data preservation / security or proper cleanup is required
	 * 	prior to engine shutdown.
	 *
	 * 	Returns true if the regisration completed successfully.
	 * 	Returns false otherwise.
	 */
	MSYS_DLL_EXPORT bool Register_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction);

	/*!
	 * 	bool Common::Unregister_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction)
	 *
	 * 	(C++ Binding)
	 *
	 * 	Unregisters the given fatal error callback function from the list of fatal error
	 * 	callback functions to be triggered in the event of a fatal error being generated.
	 *
	 * 	(I.e. If unregistered, a given callback function will not be called if a fatal
	 * 	 error occurs.)
	 *
	 * 	The callback function pointer given to this function must match a function pointer
	 * 	given to Common_Register_Fatal_Error_Callback() (Or Common::Register_Fatal_Error_Callback()) previously,
	 * 	otherwise this function will fail.
	 *
	 * 	Returns true if the unregisration completed successfully.
	 * 	Returns false otherwise.
	 */
	MSYS_DLL_EXPORT bool Unregister_Fatal_Error_Callback(const Common_pErrorCallBackFunction fatalErrorNotifyFunction);

	/*!
	 * 	void Common::Fatal_Error_Notify()
	 *
	 * 	(C++ Binding)
	 *
	 * 	This function triggers the registered fatal error callback functions
	 * 	registered with Or Common_Register_Fatal_Error_Callback() (Common::Register_Fatal_Error_Callback()),
	 * 	in an attempt to notify all need to know sections of the engine, and application, that the engine is
	 * 	about to be terminated.
	 *
	 * 	When this function returns to it's caller, it is expected that the caller
	 * 	will terminate the engine's process if it does not happen automaticly.
	 *
	 * 	This function does not return any data to it's caller.
	 */
	MSYS_DLL_EXPORT void Fatal_Error_Notify();
#endif	/* MSYS_BUILD_FATAL_ERROR_SUPPORT */
};
#endif	/* __cplusplus */

#endif /* COMMON_ERROR_HANDLER_H */

/* End of Common_Error_Handler.h */
