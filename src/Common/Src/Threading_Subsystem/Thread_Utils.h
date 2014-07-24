/*!
    Multiverse Engine Project 06/5/2013 Common Thread_Utils.h

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
#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

/*
 * These lines determine what libraries to build wappers for. 
 * (These are commented out, as they are for documentation purposes only.)
 * 
 * #define MSYS_PLUGIN_SUPPORT		// Define whether or not to enable plugin support in this subsystem.
 * 					// Note: This does not control the building of plugins, it only enables
 * 					// building the code needed to load a plugin into this specific subsystem
 * 					// at runtime.
 * 
 * #define MSYS_PLUGIN_BUILD		// Define whether or not we are building a plugin.
 * 					// Note: This must be defined when actually building a plugin.
 * 					// Any other time it should be undefined. (It's used internally
 * 					// to disable building plugin specific code that is not needed for
 * 					// internally supported wrapper libraries.)
 * 
 * The #defines below determine what external libraries to build support wrappers for.
 * 
 * Note 1: These #defines only control what support wrappers will be built at compile time.
 * If support for loading plugins is included in the engine, (MSYS_PLUGIN_SUPPORT is defined),
 * then the support wrappers for the libraries below can still be loaded at runtime even if
 * they are not built here. (I.e. Not being built at compile time does not prevent a support
 * wrapper from loading at runtime as a plugin.)
 * 
 * #define TW_PTHREADS_SUPPORT		// Define whether or not to build the support wrapper for using pthreads. 
 */

// Define Threading_Subsystem plugin API version.
#define TW_PLUGIN_ABI_VERSION 1

// Define the DEFAULT_PLUGIN_PATH if needed.
#ifdef MSYS_PLUGIN_SUPPORT
/*
 * Define default path to plugin installation directory.
 * 
 * Path is absolute.
 */
#ifndef TW_DEFAULT_INSTALL_PLUGIN_PATH

#ifdef __win32
#define TW_DEFAULT_INSTALL_PLUGIN_PATH ".\\"
#else
#define TW_DEFAULT_INSTALL_PLUGIN_PATH "/usr/lib/mengine"
#endif	// __win32

#endif	// TW_DEFAULT_INSTALL_PLUGIN_PATH

#endif	// MSYS_PLUGIN_SUPPORT


/*
 * Define the path of the plugins subdirectory within the executable path.
 * 
 * This path is rooted at the location of the executable. (I.e. path is relative to the executable.)
 * 
 * I.e. if the executable is stored in "/usr/local/bin",
 * and TW_EXEC_PLUGIN_DIR_PATH is "lib/plugins",
 * then the full path to the plugins subdirectory would be "/usr/local/bin/lib/plugins".
 * 
 * (This is used in non-system wide installs (for example if some user installs the engine
 *  in their home directory.) or debug builds. It is also used on Windows systems as a typical
 *  Windows program installs all of it's program data (executable, dynamic libraries, asset
 *  data, etc.) in the same folder.)
 */
#ifndef TW_EXEC_PLUGIN_DIR_PATH
#ifdef __win32
#define TW_EXEC_PLUGIN_DIR_PATH ".\\lib\\plugins"
#else
#define TW_EXEC_PLUGIN_DIR_PATH "/lib/plugins"
#endif	// __win32

#endif	// TW_EXEC_PLUGIN_DIR_PATH


// External includes.
#include <stddef.h>     // For errno.
#include <time.h>       // For timespec and clock_gettime().
#include <cstring>      // For strcmp().

// Internal includes.
#ifdef __win32	// Need this for different path seperator in Windows....
#include "..\Error_Handler\Common_Error_Handler.h"		// Error logging.

#ifdef MSYS_PLUGIN_SUPPORT
#include "..\Dynamic_Library_Subsystem\Dynamic_Library_Subsystem.h"	// Dynamic Library subsystem.
#include "..\File_Management_Subsystem\FileUtills.h"			// FileUtills::getDirectory() (used by PluginLoader().)
#endif // MSYS_PLUGIN_SUPPORT

#else
#include "../Error_Handler/Common_Error_Handler.h"		// Error logging.

#ifdef MSYS_PLUGIN_SUPPORT
#include "../Dynamic_Library_Subsystem/Dynamic_Library_Subsystem.h"	// Dynamic Library subsystem.
#include "../File_Management_Subsystem/FileUtills.h"			// FileUtills::getDirectory() (used by PluginLoader().)
#endif // MSYS_PLUGIN_SUPPORT

#endif	// __win32


// Thread_Utils Includes.
#include "Thread_Utils_Structures.h"	/*
                                                Includes Generic_Wrapper.h, LibraryID_Struct.h, and SymbolTable_Struct.h.
                                                Defines the plugin symbol names, and Thread_Utils::Library_Support_Status.
                                        */
#include "Thread_Utils_Base.h"		/*
						Defines the base template class objects used by Thread_Utils.
						(E.g. TU_Thread, TU_Mutex, and TU_Condition.)
					*/
#include "Thread_Utils_Library_Pointer_Structures.h"		/*
									Defines the TU_Library, and
									TU_Loaded_Plugin data structures,
									also includes the Dynamic Library
									Subsystem headers if plugin support
									is enabled.

									Must be included after Thread_Utils_Base.h as
									TU_Library and TU_Loaded_Plugin
									contain pointer(s)-to-function
									that return pointers to the base template
									objects defined in Thread_Utils_Base.h.
								*/
#include "Thread_Utils_Functions.h"				/*
									Defines the public API functions for
									the threading subsystem. (A.K.A. Thread_Utils)
								*/

/*
        Below are includes for the different library wrappers if they are enabled.
        NOTE: The actual includes for the external libraries should be put in the wrapper include NOT HERE!
*/
#ifdef TW_PTHREADS_SUPPORT
#include "Thread_Utils_pthread.h"
#endif // TW_PTHREADS_SUPPORT

#endif // THREAD_UTILS_H

// End of Thread_Utils.h
