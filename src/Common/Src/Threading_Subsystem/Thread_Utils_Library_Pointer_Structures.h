/*!
    Multiverse Engine Project 02/6/2014 Common Thread_Utils_Library_Pointer_Structures.h

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
#ifndef THREAD_UTILS_LIBRARY_POINTER_STRUCTURES_H
#define THREAD_UTILS_LIBRARY_POINTER_STRUCTURES_H

// Check for THREAD_UTILS_H.
#ifndef THREAD_UTILS_H
#error "This header is included by Thread_Utils.h, do not include it directly."
#endif

// TU_Loaded_Plugin is only needed if plugin support is enabled.
#ifdef MSYS_PLUGIN_SUPPORT
/*!
 * 	struct TU_Loaded_Plugin
 * 
 * 	A data structure used to hold data and function pointers for a loaded
 * 	Thread_Utils plugin.
 * 
 * 	The primary purpose of this data structure is to prevent a need to relookup
 * 	the symbols for the plugin every time that a call to them is needed.
 * 	A.K.A to prevent us from needing to call to the Dynamic Loader Subsystem.
 */
struct TU_Loaded_Plugin
{
	const TU_Library_Support_Status * libSupportStatus;				// Pointer to the library support status structure.
	Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library lib;			// The data structure for the dynamic library subsystem.
	TU_Thread * (*createThreadObjFunct)();						// Pointer to the plugin's Create Thread function. (If applicable.)
	TU_Mutex * (*createMutexObjFunct)();						// Pointer to the plugin's Create Mutex function. (If applicable.)
	TU_Condition * (*createConditionObjFunct)();					// Pointer to the plugin's Create Condition function. (If applicable.)
	void (*destroyThreadObjFunct)(TU_Thread **);					// Pointer to the plugin's Destroy Thread function. (If applicable.)
	void (*destroyMutexObjFunct)(TU_Mutex **);					// Pointer to the plugin's Destroy Mutex function. (If applicable.)
	void (*destroyConditionObjFunct)(TU_Condition **);				// Pointer to the plugin's Destroy Condition function. (If applicable.)
};
#endif // MSYS_PLUGIN_SUPPORT

/*!
 * 	struct TU_Library
 * 
 * 	A data structure used to hold data and function pointers for a internally
 * 	supported library used by Thread_Utils.
 * 
 * 	(This is a slieghtly altered version of TU_Loaded_Plugin.)
 * 
 * 	The primary purpose of this data structure is to be able to call a library
 * 	function without needing to hard-code the function call.
 */
struct TU_Library
{
	const TU_Library_Support_Status libSupportStatus;				// Pointer to the library support status structure.
	TU_Thread * (*createThreadObjFunct)();						// Pointer to the Create Thread function. (If applicable.)
	TU_Mutex * (*createMutexObjFunct)();						// Pointer to the Create Mutex function. (If applicable.)
	TU_Condition * (*createConditionObjFunct)();					// Pointer to the Create Condition function. (If applicable.)
	void (*destroyThreadObjFunct)(TU_Thread **);					// Pointer to the Destroy Thread function. (If applicable.)
	void (*destroyMutexObjFunct)(TU_Mutex **);					// Pointer to the Destroy Mutex function. (If applicable.)
	void (*destroyConditionObjFunct)(TU_Condition **);				// Pointer to the Destroy Condition function. (If applicable.)
};

#endif // THREAD_UTILS_LIBRARY_POINTER_STRUCTURES_H

// End of Thread_Utils_Library_Pointer_Structures.h