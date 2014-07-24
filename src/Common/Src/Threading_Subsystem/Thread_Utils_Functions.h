/*!
    Multiverse Engine Project 18/5/2013 Common Thread_Utils_Functions.h

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
#ifndef THREAD_UTILS_FUNCTIONS_H
#define THREAD_UTILS_FUNCTIONS_H

// Check for THREAD_UTILS_H.
#ifndef THREAD_UTILS_H
#error "This header is included by Thread_Utils.h, do not include it directly."
#endif

namespace Common
{
	namespace Thread_Utils
	{
                /*!
                        size_t TU_Get_Number_of_Supported_Thread_Libraries()

                        This function is used to get the total number of supported threading libraries at runtime.
                */
                size_t Get_Number_of_Supported_Thread_Libraries();

                /*!
                        Common::Thread_Utils::Thread * Common::Thread_Utils::Create_Thread(const Common_LibraryID & lib)

                        This function creates a thread class object for use with the given thread library.
                        Note: This function uses new to allocate the new object.
                        When you are done with it you must use delete to release it's memory.
                        (Call Common::Thread_Utils::Destroy_Thread() to release it.)

                        Returns a pointer to the created thread class object if successfull.
                        Otherwise returns NULL.
                */
                TU_Thread * Create_Thread(const Common_LibraryID & lib);

                /*!
                        Common::Thread_Utils::Mutex * Common::Thread_Utils::Create_Mutex(const Common_LibraryID & lib)

                        This function creates a mutex class object for use with the given thread library.
                        Note: This function uses new to allocate the new object.
                        When you are done with it you must use delete to release it's memory.
                        (Call Common::Thread_Utils::Destroy_Mutex() to release it.)

                        Returns a pointer to the created mutex class object if successfull.
                        Otherwise returns NULL.
                */
                TU_Mutex * Create_Mutex(const Common_LibraryID & lib);

                /*!
                        Common::Thread_Utils::Condition * Common::Thread_Utils::Create_Condition(const Common_LibraryID & lib)

                        This function creates a condition class object for use with the given thread library.
                        Note: This function uses new to allocate the new object.
                        When you are done with it you must use delete to release it's memory.
                        (Call Common::Thread_Utils::Destroy_Condition() to release it.)

                        Returns a pointer to the created condition class object if successfull.
                        Otherwise returns NULL.
                */
                TU_Condition * Create_Condition(const Common_LibraryID & lib);

		/*!
                        bool Common::Thread_Utils::Destroy_Thread(TU_Thread ** thread)

                        This function destroys a thread class object using it's thread library.

                        Returns true if successful, (given pointer will be NULL.)
                        Otherwise returns false.
                */
                bool Destroy_Thread(TU_Thread ** thread);

                /*!
                        bool Common::Thread_Utils::Destroy_Mutex(TU_Mutex ** mu)

                        This function destroys a mutex class object using it's thread library.

                        Returns true if successful, (given pointer will be NULL.)
                        Otherwise returns false.
                */
                bool Destroy_Mutex(TU_Mutex ** mu);

                /*!
                        bool Common::Thread_Utils::Destroy_Condition(TU_Condition ** cond)

                        This function destroys a condition class object using it's thread library.

                        Returns true if successful, (given pointer will be NULL.)
                        Otherwise returns false.
                */
                bool Destroy_Condition(TU_Condition ** cond);

                /*!
                        void TU_Init_Library_Support_Status(TU_Library_Support_Status * str)

                        This function initilizes a Library_Support_Status structure.

                        You should use this to initilize any structure you create at runtime. (It's the equilvant to the Class Constructor.)

                        Note To Library Maintainers: No staticly defined Library_Support_Status structure should need this function and should
                        be properly initilized at compile-time. (I.e bools and lib set. If there is no lib to set, you must set lib to NULL.)

                        This function is to be used by users of the library only. (Mainly for creating structures to pass to Select_Library().)
                */
                void Init_Library_Support_Status(TU_Library_Support_Status * str);

                /*!
                        const TU_Library_Support_Status * TU_Get_Library_Stats(const Common_LibraryID & lib)

                        This function returns the support status of a given library.
                        (I.e What functions are supported by Thread_Utils.)
                */
                const TU_Library_Support_Status * Get_Library_Stats(const Common_LibraryID & lib);

                /*!
                        const Common_LibraryID & TU_Select_Library(const TU_Library_Support_Status & required_stats,
                                                                   const Common_LibraryID & skip_past_this_lib)

                        This function accepts a library support status structure created by the user, plus an optional library ID to skip past (see below),
                        and returns the ID for a supported library that best matches that structure.

                        In this function the given Library_Support_Status structure is treated as a set of required abilities that the chosen library (the one that is returned)
                        must have. I.e If the Try Lock Mutex boolean is set to true then the chosen library must support that capibility for it to be returned by this function.

                        If a boolean is set to false then it is NOT considered in the selection process. The returned library may or may not support that capibility.
                        (I.e You can't select a library based on features it does NOT have with this function.)

                        If the LibraryID variable in required_stats is NOT set to "None / Unsupported", then it is treated as the caller's perferred library. I.e if LibraryID
                        (in required_stats) is set to pthreads then the pthread library ID will be returned if it is avaible, and it fulfills the given requirements.
                        (I.e This function may still return a different library if the perferred library is not avaible or lacks a required capiblility.)

                        Note: skip_past_this_lib is the ID of a Library. This function iterates through the supportedThreadLibs array starting at zero. Specifiying a library ID
                        here will cause the function to skip past all of the libraries in the supportedThreadLibs array that came before it, as well as the given library.
                        If the given library does not exist, or there are no remaining libraries after it in the supportedThreadLibs array, then the function will return
                        "None / Unsupported". Also if the given library to skip, is past the perferred library set in the given required_stats structure, the perferred library
                        will NOT be taken into account during library selection. By default skip_pass_this_lib has no effect.

                        Return:
                        In the event no supported library has the required capibilites, all of the libraries were skipped,
                        all of the libraries after the skipped library do not support the requested requirements, or an error occurs,
                        this function returns "None / Unsupported".

                        If a perferred library is given and it supports all of the given requirements it will be returned. (Perferred library is checked first.)

                        Otherwise the first library (after any skipped libraries) that supports all of the requested requirements is returned.
                */
                const Common_LibraryID & Select_Library(const TU_Library_Support_Status & required_stats, const Common_LibraryID & skip_past_this_lib = TU_LibID_none); // TU_LibID_none = {false, "None / Unsupported"}

#ifdef MSYS_PLUGIN_SUPPORT
		// Only define the plugin loader function if plugin support is enabled.
		/*
		 * 	Note: A plugin cannot have the same LibraryID data structure as another loaded plugin.
		 * 	If we attempt to load a plugin with the same LibraryID data structure as another plugin,
		 * 	the first plugin will be kept and all remaining plugins will be unloaded from memory.
		 * 
		 * 	This function can only be run once. (It's called in Select_Library() if it's the first
		 * 	time that function has been called. For that reason, this function is considered internal
		 * 	to the engine and should not be called externally.)
		 */
		bool Load_Plugins(const char * pluginPath);
#endif	// MSYS_PLUGIN_SUPPORT
	}
}
#endif	// THREAD_UTILS_FUNCTIONS_H

// End of Thread_Utils_Functions.h
