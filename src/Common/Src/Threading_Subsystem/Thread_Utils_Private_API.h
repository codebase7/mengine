/*!
    Multiverse Engine Project 04/7/2014 Common Thread_Utils_Private_API.h (INTERNAL ENGINE USE ONLY)

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
#ifndef THREAD_UTILS_PRIVATE_API_H
#define THREAD_UTILS_PRIVATE_API_H

// Check for THREAD_UTILS_H.
#ifndef THREAD_UTILS_H
#error "This header is not for public use, as it is a part of the engine's private internal API. DO NOT LINK TO THIS HEADER!"
#endif

// Include internal API header for Error Logging.
#ifdef __win32
#include "..\Error_Handler\Common_Error_Handler_Internal.h"
#else
#include "../Error_Handler/Common_Error_Handler_Internal.h"
#endif // __win32

// Include internal API header for Thread_Utils::supportedThreadLibs.
#include "Thread_Utils_Internally_Supported_Libraries.h"	/*
									Defines Thread_Utils::supportedThreadLibs.
									(The array that holds the list of 
									internally supported libraries.)
								*/

#endif	// THREAD_UTILS_PRIVATE_API_H

// End of Thread_Utils_Private_API.h
