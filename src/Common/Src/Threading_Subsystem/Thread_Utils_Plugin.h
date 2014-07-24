/*!
    Multiverse Engine Project 14/5/2014 Common Thread_Utils_Plugin.h

    This file contains the prototypes for a plugin to the Thread_Utils
    subsystem.
    
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

#ifndef THREAD_UTILS_PLUGIN_H
#define THREAD_UTILS_PLUGIN_H

// Check for THREAD_UTILS_H.
#ifndef THREAD_UTILS_H
#error "This header should be included AFTER Thread_Utils.h."
#endif

#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

/*!
 * 	int TU_Get_Plugin_ABI_Version(const int & hostABIVersion)
 *
 * 	Returns the ABI version of the loaded plugin, by default or if the given
 * 	ABI version argument is equal to zero (0).
 *
 * 	If given a version number argument, it will return the given version
 * 	number if the plugin supports that ABI version. Otherwise the plugin will
 * 	return it's own version number, to indicate the plugin does NOT support
 * 	that ABI version.
 * 
 * 	Note: You should probably check this first to see if the plugin
 * 	ABI version is newer than the ABI version of the program using it.
 * 	(If the plugin's ABI version is greater than the program's
 * 	ABI version, there is no guarentee that the plugin will work.)
 *
 * 	Pram: const int & hostABIVersion, the ABI version number of the
 * 	program using the plugin. (Defaults to zero (0).)
 * 
 * 	Returns the plugin's ABI version if the given ABI version
 * 	is equal to zero (0). (Default)
 * 
 * 	Returns the plugin's ABI version if the given ABI version
 * 	is unsupported by the plugin.
 *
 * 	Returns the given ABI version if the plugin supports the
 * 	given ABI version.
 */
int TU_Get_Plugin_ABI_Version(const int & hostABIVersion = 0);

/*!
 * 	TU_Thread * TU_Create_Thread_Object()
 * 
 * 	Has the plugin create a thread object of it's own type in memory and passes it back
 * 	to the caller as a base pointer of type TU_Thread.
 * 
 * 	Note: It's the caller's job to delete the thread object out of memory when done with it.
 * 	(Call TU_Destroy_Thread_Object() when you are done with it.)
 * 
 * 	Returns a valid pointer on success, otherwise returns NULL.
 */
TU_Thread * TU_Create_Thread_Object();

/*!
 * 	TU_Mutex * TU_Create_Mutex_Object()
 * 
 * 	Has the plugin create a mutex object of it's own type in memory and passes it back
 * 	to the caller as a base pointer of type TU_Mutex.
 * 
 * 	Note: It's the caller's job to delete the mutex object out of memory when done with it.
 * 	(Call TU_Destroy_Mutex_Object() when you are done with it.)
 * 
 * 	Returns a valid pointer on success, otherwise returns NULL.
 */
TU_Mutex * TU_Create_Mutex_Object();

/*!
 * 	TU_Condition * TU_Create_Condition_Object()
 * 
 * 	Has the plugin create a condition object of it's own type in memory and passes it back
 * 	to the caller as a base pointer of type TU_Condition.
 * 
 * 	Note: It's the caller's job to delete the condition object out of memory when done with it.
 * 	(Call TU_Destroy_Condition_Object() when you are done with it.)
 *
 * 	Returns a valid pointer on success, otherwise returns NULL.
 */
TU_Condition * TU_Create_Condition_Object();

/*!
	const TU_Library_Support_Status TU_Get_Library_Support_Status_Object()

	Has the plugin return a copy of it's TU_Library_Support_Status object.
*/
const TU_Library_Support_Status TU_Get_Library_Support_Status_Object();

/*!
 * 	void TU_Destroy_Thread_Object(TU_Thread ** thread)
 * 
 * 	Has the plugin destroy the given thread object.
 */
void TU_Destroy_Thread_Object(TU_Thread ** thread);

/*!
 * 	void TU_Destroy_Mutex_Object(TU_Mutex ** mu)
 * 
 * 	Has the plugin destroy the given mutex object.
 */
void TU_Destroy_Mutex_Object(TU_Mutex ** mu);

/*!
 * 	void TU_Destroy_Condition_Object(TU_Condition ** cond)
 * 
 * 	Has the plugin destroy the given condition variable.
 */
void TU_Destroy_Condition_Object(TU_Condition ** cond);

#ifdef __cplusplus
}		// End of extern C.
#endif	// __cplusplus

#endif // THREAD_UTILS_PLUGIN_H

// End of Thread_Utils_Plugin.h
