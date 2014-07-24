/*!
    Multiverse Engine Project 16/5/2013 Common Thread_Utils_Functions.cpp

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

// Include main header.
#include "Thread_Utils.h"

// Include the private API header.
#include "Thread_Utils_Private_API.h"

// The loadedPlugins vector is only needed if plugin support is enabled.
#ifdef MSYS_PLUGIN_SUPPORT
/*!
 * 	static std::vector<TU_Loaded_Plugin> TU_loadedPlugins
 * 
 * 	A global vector to contain the data structures and function pointers
 * 	for loaded Thread_Utils plugins.
 * 
 * 	Only built into the library if plugin support is enabled at compile time.
 * 	(i.e. MSYS_PLUGIN_SUPPORT is defined at compile time.)
 */
static std::vector<TU_Loaded_Plugin> TU_loadedPlugins;
#endif // MSYS_PLUGIN_SUPPORT

size_t Common::Thread_Utils::Get_Number_of_Supported_Thread_Libraries()
{
        /*
            Calculate size of internal support array. (sizeof entire array / sizeof single element in array.)
            (Note: This works as the array is global to the namespace and therefore does not need to be passed to us.)
        */
        size_t ret = sizeof(TU_supportedThreadLibs) / sizeof(TU_Library);

#ifdef MSYS_PLUGIN_SUPPORT
	// Add the number of loaded plugins if plugin support is enabled.
	ret += TU_loadedPlugins.size();
#endif // MSYS_PLUGIN_SUPPORT

        // Return result.
        return ret;
}

const size_t Get_Number_of_Internal_Thread_Libraries()
{
        /*
            Calculate size of internal support array. (sizeof entire array / sizeof single element in array.)
            (Note: This works as the array is global to the namespace and therefore does not need to be passed to us.)
        */
        return (sizeof(TU_supportedThreadLibs) / sizeof(TU_Library));
}

TU_Thread * Common::Thread_Utils::Create_Thread(const Common_LibraryID & lib)
{
        // Init vars.
        TU_Thread * ret = NULL;
        #ifdef MSYS_PLUGIN_SUPPORT
        static bool pluginsLoaded = false;
        #endif // MSYS_PLUGIN_SUPPORT

	// Reset Common::commonErrorCode.
	Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

        // Begin try block.
        try{
                // Plugin loader code.
                #ifdef MSYS_PLUGIN_SUPPORT
                // Check to see if the plugins are loaded.
		if ((!pluginsLoaded) && (TU_loadedPlugins.size() == 0))
                {
                        // Load the plugins.
			pluginsLoaded = Common::Thread_Utils::Load_Plugins(NULL);
                }

                // Iterate through the plugins and find one we can use.
		for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (ret == NULL)); x++)
		{
			// Check for a match from the plugins.
			if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
			    (lib.Name != NULL) &&
			    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0) &&
			    (TU_loadedPlugins[x].libSupportStatus->bThreadsSupport) &&
			    (TU_loadedPlugins[x].createThreadObjFunct != NULL))
			{
				// Match found.
				ret = TU_loadedPlugins[x].createThreadObjFunct();
				if ((ret != NULL) && (Common::commonLastErrorCode == THREAD_UTILS_INVALID_LIBRARY_ID))
				{
					// We were successfull.
					Common::commonLastErrorCode = Common::COMMON_SUCCESS;
				}
			}
		}

                /*
		 * Plugins override internal support.
		 * This is to allow the use of updated / fixed libraries.
		 * Only use internally supported libraries
		 * if a plugin has not already claimed support for a given library.
		 *
		 * (ret will be NULL if no plugin has created an object, or if
		 * plugin support is disabled at compile time.)
		 */
		if (ret == NULL)
		{
		#endif
			/*
				Below is a check for each supported thread library type.
				If a thread library is requested that is disabled or not supported, we return NULL.
			*/
			for (size_t x = 0;
			    ((x < Get_Number_of_Internal_Thread_Libraries()) &&
			    (ret == NULL)); x++)
			{
				// Check for library match.
				if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
				    (lib.Name != NULL) &&
				    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.bThreadsSupport) &&
				    (TU_supportedThreadLibs[x].createThreadObjFunct() != NULL))
				{
					ret = TU_supportedThreadLibs[x].createThreadObjFunct();
					if ((ret != NULL) && (Common::commonLastErrorCode == THREAD_UTILS_INVALID_LIBRARY_ID))
					{
						// We were successfull.
						Common::commonLastErrorCode = Common::COMMON_SUCCESS;
					}
				}
			}
		#ifdef MSYS_PLUGIN_SUPPORT
		}	/*
				Prevent the compiler from seeing the if (ret == NULL),
				if plugin support is disabled to prevent bad optizations.
			*/
		#endif // MSYS_PLUGIN_SUPPORT
        }
        catch(...)
        {
                // An error occured.
                if (ret != NULL)
                {
                        delete ret;
                }
                ret = NULL;

		// Set THREAD_UTILS_EXCEPTION_THROWN error code.
		Common::commonLastErrorCode = Common::THREAD_UTILS_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("Thread_Utils::Create_Thread(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_VERBOSE("\n");
        }
        
        // Exit function.
        return ret;
}

TU_Mutex * Common::Thread_Utils::Create_Mutex(const Common_LibraryID & lib)
{
        // Init return var.
        TU_Mutex * ret = NULL;
	#ifdef MSYS_PLUGIN_SUPPORT
	static bool pluginsLoaded = false;
	#endif // MSYS_PLUGIN_SUPPORT

	// Reset Common::commonErrorCode.
	Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

        // Begin try block.
        try{
		// Plugin loader code.
                #ifdef MSYS_PLUGIN_SUPPORT
                // Check to see if the plugins are loaded.
		if ((!pluginsLoaded) && (TU_loadedPlugins.size() == 0))
                {
                        // Load the plugins.
			pluginsLoaded = Common::Thread_Utils::Load_Plugins(NULL);
                }

                // Iterate through the plugins and find one we can use.
		for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (ret == NULL)); x++)
		{
			// Check for a match from the plugins.
			if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
			    (lib.Name != NULL) &&
			    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0) &&
			    (TU_loadedPlugins[x].libSupportStatus->bMutexesSupport) &&
			    (TU_loadedPlugins[x].createMutexObjFunct != NULL))
			{
				// Match found.
				ret = TU_loadedPlugins[x].createMutexObjFunct();
				if ((ret != NULL) && (Common::commonLastErrorCode == THREAD_UTILS_INVALID_LIBRARY_ID))
				{
					// We were successfull.
					Common::commonLastErrorCode = Common::COMMON_SUCCESS;
				}
			}
		}

                /*
		 * Plugins override internal support.
		 * This is to allow the use of updated / fixed libraries.
		 * Only use internally supported libraries
		 * if a plugin has not already claimed support for a given library.
		 *
		 * (ret will be NULL if no plugin has created an object, or if
		 * plugin support is disabled at compile time.)
		 */
		if (ret == NULL)
		{
		#endif
			/*
				Below is a check for each supported thread library type.
				If a thread library is requested that is disabled or not supported, we return NULL.
			*/
			for (size_t x = 0;
			    ((x < Get_Number_of_Internal_Thread_Libraries()) &&
			    (ret == NULL)); x++)
			{
				// Check for library match.
				if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
				    (lib.Name != NULL) &&
				    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.bMutexesSupport) &&
				    (TU_supportedThreadLibs[x].createMutexObjFunct() != NULL))
				{
					ret = TU_supportedThreadLibs[x].createMutexObjFunct();
					if ((ret != NULL) && (Common::commonLastErrorCode == THREAD_UTILS_INVALID_LIBRARY_ID))
					{
						// We were successfull.
						Common::commonLastErrorCode = Common::COMMON_SUCCESS;
					}
				}
			}
		#ifdef MSYS_PLUGIN_SUPPORT
		}	/*
				Prevent the compiler from seeing the if (ret == NULL),
				if plugin support is disabled to prevent bad optizations.
			*/
		#endif // MSYS_PLUGIN_SUPPORT
        }
        catch(...)
        {
                // An error occured.
                if (ret != NULL)
                {
                        delete ret;
                }
                ret = NULL;

		// Set THREAD_UTILS_EXCEPTION_THROWN error code.
		Common::commonLastErrorCode = Common::THREAD_UTILS_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("Thread_Utils::Create_Mutex(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_VERBOSE("\n");
        }

        // Exit function.
        return ret;
}

TU_Condition * Common::Thread_Utils::Create_Condition(const Common_LibraryID & lib)
{
        // Init return var.
        TU_Condition * ret = NULL;
	#ifdef MSYS_PLUGIN_SUPPORT
	static bool pluginsLoaded = false;
	#endif // MSYS_PLUGIN_SUPPORT

	// Reset Common::commonErrorCode.
	Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

        // Begin try block.
        try{
		// Plugin loader code.
                #ifdef MSYS_PLUGIN_SUPPORT
                // Check to see if the plugins are loaded.
		if ((!pluginsLoaded) && (TU_loadedPlugins.size() == 0))
                {
                        // Load the plugins.
			pluginsLoaded = Common::Thread_Utils::Load_Plugins(NULL);
                }

                // Iterate through the plugins and find one we can use.
		for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (ret == NULL)); x++)
		{
			// Check for a match from the plugins.
			if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
			    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
			    (lib.Name != NULL) &&
			    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0) &&
			    (TU_loadedPlugins[x].libSupportStatus->bConditionVariableSupport) &&
			    (TU_loadedPlugins[x].createConditionObjFunct != NULL))
			{
				// Match found.
				ret = TU_loadedPlugins[x].createConditionObjFunct();
				if ((ret != NULL) && (Common::commonLastErrorCode == THREAD_UTILS_INVALID_LIBRARY_ID))
				{
					// We were successfull.
					Common::commonLastErrorCode = Common::COMMON_SUCCESS;
				}
			}
		}

                /*
		 * Plugins override internal support.
		 * This is to allow the use of updated / fixed libraries.
		 * Only use internally supported libraries
		 * if a plugin has not already claimed support for a given library.
		 *
		 * (ret will be NULL if no plugin has created an object, or if
		 * plugin support is disabled at compile time.)
		 */
		if (ret == NULL)
		{
		#endif
			/*
				Below is a check for each supported thread library type.
				If a thread library is requested that is disabled or not supported, we return NULL.
			*/
			for (size_t x = 0;
			    ((x < Get_Number_of_Internal_Thread_Libraries()) &&
			    (ret == NULL)); x++)
			{
				// Check for library match.
				if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
				    (lib.Name != NULL) &&
				    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.bConditionVariableSupport) &&
				    (TU_supportedThreadLibs[x].createConditionObjFunct() != NULL))
				{
					ret = TU_supportedThreadLibs[x].createConditionObjFunct();
					if ((ret != NULL) && (Common::commonLastErrorCode == THREAD_UTILS_INVALID_LIBRARY_ID))
					{
						// We were successfull.
						Common::commonLastErrorCode = Common::COMMON_SUCCESS;
					}
				}
			}
		#ifdef MSYS_PLUGIN_SUPPORT
		}	/*
				Prevent the compiler from seeing the if (ret == NULL),
				if plugin support is disabled to prevent bad optizations.
			*/
		#endif // MSYS_PLUGIN_SUPPORT
        }
        catch(...)
        {
                // An error occured.
                if (ret != NULL)
                {
                        delete ret;
                }
                ret = NULL;

		// Set THREAD_UTILS_EXCEPTION_THROWN error code.
		Common::commonLastErrorCode = Common::THREAD_UTILS_EXCEPTION_THROWN;
		COMMON_LOG_VERBOSE("Thread_Utils::Create_Condition(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_VERBOSE("\n");
        }

        // Exit function.
        return ret;
}

bool Common::Thread_Utils::Destroy_Thread(TU_Thread ** thread)
{
        // Init vars.
        bool ret = false;		// Return from this function.
	Common_LibraryID lib;

        // Check for invalid pointer.
        if (thread != NULL)
	{
		// Fetch Library_ID from the object.
		lib = (*thread)->Get_Thread_Library();

		// Reset Common::commonErrorCode.
		Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

		// Begin try block.
		try{
			// Plugin loader code.
			#ifdef MSYS_PLUGIN_SUPPORT
			// Iterate through the plugins and find one we can use.
			for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (!ret)); x++)
			{
				// Check for a match from the plugins.
				if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
				    (lib.Name != NULL) &&
				    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0) &&
				    (TU_loadedPlugins[x].libSupportStatus->bThreadsSupport) &&
				    (TU_loadedPlugins[x].destroyThreadObjFunct != NULL))
				{
					// Match found.
					TU_loadedPlugins[x].destroyThreadObjFunct(thread);

					// We were successful.
					Common::commonLastErrorCode = Common::COMMON_SUCCESS;
					ret = true;
				}
			}

			/*
			 * 	Plugins override internal support.
			 * 	This is to allow the use of updated / fixed libraries.
			 * 	Only use internally supported libraries
			 * 	if a plugin has not already claimed support for a given library.
			 *
			 * 	(ret will be false if no plugin has destroyed an object, or if
			 * 	plugin support is disabled at compile time.)
			 */
			if (!ret)
			{
			#endif
				/*
				 * 	Below is a check for each supported thread library type.
				 * 	If a thread library is requested that is disabled or not supported, we return NULL.
				 */
				for (size_t x = 0;
				    ((x < Get_Number_of_Internal_Thread_Libraries()) &&
				    (!ret)); x++)
				{
					// Check for library match.
					if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
					    (lib.Name != NULL) &&
					    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.bThreadsSupport) &&
					    (TU_supportedThreadLibs[x].destroyThreadObjFunct != NULL))
					{
						TU_supportedThreadLibs[x].destroyThreadObjFunct(thread);

						// We were successful.
						Common::commonLastErrorCode = Common::COMMON_SUCCESS;
						ret = true;
					}
				}
			#ifdef MSYS_PLUGIN_SUPPORT
			}	/*
					Prevent the compiler from seeing the if (ret == NULL),
					if plugin support is disabled to prevent bad optizations.
				*/
			#endif // MSYS_PLUGIN_SUPPORT
		}
		catch(...)
		{
			// An error occured, Set THREAD_UTILS_EXCEPTION_THROWN error code.
			Common::commonLastErrorCode = Common::THREAD_UTILS_EXCEPTION_THROWN;
			COMMON_LOG_VERBOSE("Thread_Utils::Destroy_Thread(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_VERBOSE("\n");
		}
	}
	else
	{
		// Invalid pointer.
		Common::commonLastErrorCode = Common::COMMON_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("Thread_Utils::Destroy_Thread(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_VERBOSE(" Invalid thread pointer.\n");
	}

	// If we get here, and the Library_ID was unknown we have a problem.
	if ((!ret) && (Common::commonLastErrorCode == Common::THREAD_UTILS_INVALID_LIBRARY_ID))
	{
		COMMON_LOG_CRITICAL("Thread_Utils::Destroy_Thread(): ");
		COMMON_LOG_CRITICAL(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_CRITICAL(" Unable to release memory for thread object (no library claimed the thread object), may cause a memory leak. You should kill the engine NOW!\n");
	}
	else
	{
		// See if that thing was destroyed.
		if (*thread != NULL)
		{
			// Internal error.
			Common::commonLastErrorCode = Common::COMMON_INTERNAL_ERROR;
			COMMON_LOG_CRITICAL("Thread_Utils::Destroy_Thread(): ");
			COMMON_LOG_CRITICAL(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_CRITICAL(" Unable to release memory for thread object (internal engine issue with destructor), may cause a memory leak. You should kill the engine NOW!\n");
		}
	}

        // Exit function.
        return ret;
}

bool Common::Thread_Utils::Destroy_Mutex(TU_Mutex ** mu)
{
        // Init return var.
        bool ret = false;
        Common_LibraryID lib;

	// Check for invalid pointer.
	if (mu != NULL)
	{
		// Fetch Library_ID from the object.
		lib = (*mu)->Get_Thread_Library();

		// Reset Common::commonErrorCode.
		Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

		// Begin try block.
		try{
			// Plugin loader code.
			#ifdef MSYS_PLUGIN_SUPPORT
			// Iterate through the plugins and find one we can use.
			for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (!ret)); x++)
			{
				// Check for a match from the plugins.
				if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
				    (lib.Name != NULL) &&
				    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0) &&
				    (TU_loadedPlugins[x].libSupportStatus->bMutexesSupport) &&
				    (TU_loadedPlugins[x].destroyMutexObjFunct != NULL))
				{
					// Match found.
					TU_loadedPlugins[x].destroyMutexObjFunct(mu);

					// We were successful.
					Common::commonLastErrorCode = Common::COMMON_SUCCESS;
					ret = true;
				}
			}

			/*
			 * 	Plugins override internal support.
			 * 	This is to allow the use of updated / fixed libraries.
			 * 	Only use internally supported libraries
			 * 	if a plugin has not already claimed support for a given library.
			 *
			 * 	(ret will be false if no plugin has destroyed an object, or if
			 * 	plugin support is disabled at compile time.)
			 */
			if (!ret)
			{
			#endif
				/*
				 * 	Below is a check for each supported thread library type.
				 * 	If a thread library is requested that is disabled or not supported, we return NULL.
				 */
				for (size_t x = 0;
				    ((x < Get_Number_of_Internal_Thread_Libraries()) &&
				    (!ret)); x++)
				{
					// Check for library match.
					if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
					    (lib.Name != NULL) &&
					    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.bMutexesSupport) &&
					    (TU_supportedThreadLibs[x].destroyMutexObjFunct != NULL))
					{
						TU_supportedThreadLibs[x].destroyMutexObjFunct(mu);

						// We were successful.
						Common::commonLastErrorCode = Common::COMMON_SUCCESS;
						ret = true;
					}
				}
			#ifdef MSYS_PLUGIN_SUPPORT
			}	/*
					Prevent the compiler from seeing the if (ret == NULL),
					if plugin support is disabled to prevent bad optizations.
				*/
			#endif // MSYS_PLUGIN_SUPPORT
		}
		catch(...)
		{
			// An error occured, Set THREAD_UTILS_EXCEPTION_THROWN error code.
			Common::commonLastErrorCode = Common::THREAD_UTILS_EXCEPTION_THROWN;
			COMMON_LOG_VERBOSE("Thread_Utils::Destroy_Mutex(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_VERBOSE("\n");
		}
	}
	else
	{
		// Invalid pointer.
		Common::commonLastErrorCode = Common::COMMON_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("Thread_Utils::Destroy_Mutex(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_VERBOSE(" Invalid mutex pointer.\n");
	}

	// If we get here, and the Library_ID was unknown we have a problem.
	if ((!ret) && (Common::commonLastErrorCode == Common::THREAD_UTILS_INVALID_LIBRARY_ID))
	{
		COMMON_LOG_CRITICAL("Thread_Utils::Destroy_Mutex(): ");
		COMMON_LOG_CRITICAL(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_CRITICAL(" Unable to release memory for mutex object (no library claimed the mutex object), may cause a memory leak. You should kill the engine NOW!\n");
	}
	else
	{
		// See if that thing was destroyed.
		if (*mu != NULL)
		{
			// Internal error.
			Common::commonLastErrorCode = Common::COMMON_INTERNAL_ERROR;
			COMMON_LOG_CRITICAL("Thread_Utils::Destroy_Mutex(): ");
			COMMON_LOG_CRITICAL(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_CRITICAL(" Unable to release memory for mutex object (internal engine issue with destructor), may cause a memory leak. You should kill the engine NOW!\n");
		}
	}

        // Exit function.
        return ret;
}

bool Common::Thread_Utils::Destroy_Condition(TU_Condition ** cond)
{
        // Init return var.
        bool ret = false;
	Common_LibraryID lib;

	// Check for invalid pointer.
	if (cond != NULL)
	{
		// Fetch Library_ID from the object.
		lib = (*cond)->Get_Thread_Library();

		// Reset Common::commonErrorCode.
		Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

		// Begin try block.
		try{
			// Plugin loader code.
			#ifdef MSYS_PLUGIN_SUPPORT

			// Iterate through the plugins and find one we can use.
			for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (!ret)); x++)
			{
				// Check for a match from the plugins.
				if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
				    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
				    (lib.Name != NULL) &&
				    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0) &&
				    (TU_loadedPlugins[x].libSupportStatus->bConditionVariableSupport) &&
				    (TU_loadedPlugins[x].destroyConditionObjFunct != NULL))
				{
					// Match found.
					TU_loadedPlugins[x].destroyConditionObjFunct(cond);

					// We were successful.
					Common::commonLastErrorCode = Common::COMMON_SUCCESS;
					ret = true;
				}
			}

			/*
			 * 	Plugins override internal support.
			 * 	This is to allow the use of updated / fixed libraries.
			 * 	Only use internally supported libraries
			 * 	if a plugin has not already claimed support for a given library.
			 *
			 * 	(ret will be false if no plugin has destroyed an object, or if
			 * 	plugin support is disabled at compile time.)
			 */
			if (!ret)
			{
			#endif
				/*
				 * 	Below is a check for each supported thread library type.
				 * 	If a thread library is requested that is disabled or not supported, we return NULL.
				 */
				for (size_t x = 0;
				    ((x < Get_Number_of_Internal_Thread_Libraries()) &&
				    (!ret)); x++)
				{
					// Check for library match.
					if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
					    (lib.Name != NULL) &&
					    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin) &&
					    (TU_supportedThreadLibs[x].libSupportStatus.bConditionVariableSupport) &&
					    (TU_supportedThreadLibs[x].destroyConditionObjFunct != NULL))
					{
						TU_supportedThreadLibs[x].destroyConditionObjFunct(cond);

						// We were successful.
						Common::commonLastErrorCode = Common::COMMON_SUCCESS;
						ret = true;
					}
				}
			#ifdef MSYS_PLUGIN_SUPPORT
			}	/*
					Prevent the compiler from seeing the if (ret == NULL),
					if plugin support is disabled to prevent bad optizations.
				*/
			#endif // MSYS_PLUGIN_SUPPORT
		}
		catch(...)
		{
			// An error occured, Set THREAD_UTILS_EXCEPTION_THROWN error code.
			Common::commonLastErrorCode = Common::THREAD_UTILS_EXCEPTION_THROWN;
			COMMON_LOG_VERBOSE("Thread_Utils::Destroy_Condition(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_VERBOSE("\n");
		}
	}
	else
	{
		// Invalid pointer.
		Common::commonLastErrorCode = Common::COMMON_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("Thread_Utils::Destroy_Condition(): ");
		COMMON_LOG_VERBOSE(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_VERBOSE(" Invalid condition variable pointer.\n");
	}

	// If we get here, and the Library_ID was unknown we have a problem.
	if ((!ret) && (Common::commonLastErrorCode == Common::THREAD_UTILS_INVALID_LIBRARY_ID))
	{
		COMMON_LOG_CRITICAL("Thread_Utils::Destroy_Condition(): ");
		COMMON_LOG_CRITICAL(Common::Get_Error_Message(Common::commonLastErrorCode));
		COMMON_LOG_CRITICAL(" Unable to release memory for condition variable object (no library claimed the condition variable object), may cause a memory leak. You should kill the engine NOW!\n");
	}
	else
	{
		// See if that thing was destroyed.
		if (*cond != NULL)
		{
			// Internal error.
			Common::commonLastErrorCode = Common::COMMON_INTERNAL_ERROR;
			COMMON_LOG_CRITICAL("Thread_Utils::Destroy_Condition(): ");
			COMMON_LOG_CRITICAL(Common::Get_Error_Message(Common::commonLastErrorCode));
			COMMON_LOG_CRITICAL(" Unable to release memory for condition variable object (internal engine issue with destructor), may cause a memory leak. You should kill the engine NOW!\n");
		}
	}

        // Exit function.
        return ret;
}

void Common::Thread_Utils::Init_Library_Support_Status(TU_Library_Support_Status * str)
{
        // Check for NULL.
        if (str != NULL)
        {
		// Reset the structure.
                str->lib = &TU_LibID_none;         // {false, "None / Unsupported"}
                str->bThreadsSupport = false;
                str->bJoinThreadSupport = false;
                str->bDetachThreadSupport = false;
                str->bLibraryRequiresSpecificFunctionSig = false;
                str->bMutexesSupport = false;
                str->bTryLockSupport = false;
                str->bConditionVariableSupport = false;
                str->bConditionWaitTimeoutSupport = false;

		// Clear Common::commonLastErrorCode.
		Common::commonLastErrorCode = Common::COMMON_SUCCESS;
        }
        else
	{
		// Invalid argument.
		Common::commonLastErrorCode = Common::COMMON_INVALID_ARGUMENT;
	}

        // Exit function.
        return;
}

const TU_Library_Support_Status * Common::Thread_Utils::Get_Library_Stats(const Common_LibraryID & lib)
{
        // Init return var.
        const TU_Library_Support_Status * ret = &TU_LibSupport_none;

	// Reset Common::commonLastErrorCode.
	Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

	#ifdef MSYS_PLUGIN_SUPPORT
	for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (ret == &TU_LibSupport_none)); x++)
	{
		// Check for a match from the plugins.
		if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
		    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
		    (TU_loadedPlugins[x].libSupportStatus->lib->bIsPlugin == lib.bIsPlugin) &&
		    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
		    (lib.Name != NULL) &&
		    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, lib.Name) == 0))
		{
			// Match found, return the Library_Support_Status structure.
			ret = TU_loadedPlugins[x].libSupportStatus;

			// Clear Common::commonLastErrorCode.
			Common::commonLastErrorCode = Common::COMMON_SUCCESS;
		}
	}

	/*
	 * Plugins override internal support.
	 * This is to allow the use of updated / fixed libraries.
	 * Only use internally supported libraries
	 * if a plugin has not already claimed support for a given library.
	 *
	 * (ret will be equal to the address of TU_LibSupport_none if no plugin has claimed support, 
	 * or if plugin support is disabled at compile time.)
	 */
	if (ret == &TU_LibSupport_none)
	{
	#endif
		/*
			Below is a check for each supported thread library type.
			If a thread library is requested that is disabled or not supported, we return the none / unsupported struct.
		*/
		for (size_t x = 0;
		     ((x < Get_Number_of_Internal_Thread_Libraries()) &&
		     (ret == NULL)); x++)
		{
			// Check for library match.
			if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
			    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL) &&
			    (lib.Name != NULL) &&
			    (strcmp(TU_supportedThreadLibs[x].libSupportStatus.lib->Name, lib.Name) == 0) &&
			    (TU_supportedThreadLibs[x].libSupportStatus.lib->bIsPlugin == lib.bIsPlugin))
			{
				// Return the Library_Support_Status structure.
				ret = &TU_supportedThreadLibs[x].libSupportStatus;

				// Clear Common::commonLastErrorCode.
				Common::commonLastErrorCode = Common::COMMON_SUCCESS;
			}
		}
	#ifdef MSYS_PLUGIN_SUPPORT
	}	/*
			Prevent the compiler from seeing the if (ret == &TU_LibSupport_none),
			if plugin support is disabled to prevent bad optizations.
		*/
	#endif // MSYS_PLUGIN_SUPPORT

        // Exit function.
        return ret;
}

/*
 * 	bool Check_Library(const TU_Library_Support_Status & required_stats,
 * 			   const TU_Library_Support_Status & libToCheck)
 * 
 * 	Performs the actual check of the library / plugin against the requirements,
 * 	for Common::Thread_Utils::Select_Library().
 * 
 * 	Note: This function does not check to see if the given library / plugin
 * 	matches the perferred library / plugin. Nor does it check to see if the
 * 	given library / plugin should be skipped. Those tasks must be done by
 * 	Common::Thread_Utils::Select_Library().
 * 	This is due to this function not checking the validity of the LibraryID
 * 	data structures.
 * 
 * 	Returns true if the library fulfills the requirements.
 * 	Returns false otherwise.
 */
bool Check_Library(const TU_Library_Support_Status & required_stats,
		   const TU_Library_Support_Status & libToCheck)
{
	// Init the result.
	bool ret = false;	// The result of the check.

	// Clear Common::commonLastErrorCode.
	Common::commonLastErrorCode = Common::COMMON_SUCCESS;

	/*
	 * OK, for each library check and see if it provides a requirement.
	 * Check for no requirement first as that is more likely.
	 */
	if ((!required_stats.bThreadsSupport) ||
	    (required_stats.bThreadsSupport && libToCheck.bThreadsSupport))
	{
		// bJoinThreadSupport.
		if ((!required_stats.bJoinThreadSupport) ||
		    (required_stats.bJoinThreadSupport && libToCheck.bJoinThreadSupport))
		{
			// bDetachThreadSupport.
			if ((!required_stats.bDetachThreadSupport) ||
			    (required_stats.bDetachThreadSupport && libToCheck.bDetachThreadSupport))
			{
				// bLibraryRequiresSpecificFunctionSig.
				if ((!required_stats.bLibraryRequiresSpecificFunctionSig) ||
				    (required_stats.bLibraryRequiresSpecificFunctionSig && libToCheck.bLibraryRequiresSpecificFunctionSig))
				{
					// bMutexesSupport.
					if ((!required_stats.bMutexesSupport) ||
					    (required_stats.bMutexesSupport && libToCheck.bMutexesSupport))
					{
						// bTryLockSupport.
						if ((!required_stats.bTryLockSupport) ||
						    (required_stats.bTryLockSupport && libToCheck.bTryLockSupport))
						{
							// bConditionVariableSupport.
							if ((!required_stats.bConditionVariableSupport) ||
							    (required_stats.bConditionVariableSupport && libToCheck.bConditionVariableSupport))
							{
								// bConditionWaitTimeoutSupport.
								if ((!required_stats.bConditionWaitTimeoutSupport) ||
								    (required_stats.bConditionWaitTimeoutSupport && libToCheck.bConditionWaitTimeoutSupport))
								{
									// Library fulfills given requirements.
									ret = true;
								}
							}
						}
					}
				}
			}
		}
	}

	// Return the result.
	return ret;
}

const Common_LibraryID & Common::Thread_Utils::Select_Library(const TU_Library_Support_Status & required_stats, const Common_LibraryID & skip_past_this_lib)
{
        // Init result.
        const Common_LibraryID * ret = &TU_LibID_none;        // None / Unsupported.

        // Init other vars.
#ifdef MSYS_PLUGIN_SUPPORT
        static bool loadedPlugins = false;	// Used to tell if we have loaded the plugins before.
        bool skipPlugins = false;		// Used to skip past the plugins if we need to due to the given skip_past_this_lib.
#endif // MSYS_PLUGIN_SUPPORT

        bool checkedPerferredlib = false;   	// Used to tell if we have checked the perferred library.
        bool passedSkipLib = false;		// Used to tell if we have passed the library to skip.
      
	// Reset Common::commonLastErrorCode.
	Common::commonLastErrorCode = Common::THREAD_UTILS_INVALID_LIBRARY_ID;

	/*
	 * 	Check to see if the skip_past_this_lib and required_stats LibraryID structures are valid.
	 * 
	 * 	Short requirement list:
	 * 		If a LibraryID structure pointer is valid it's Name pointer must also be valid.
	 * 
	 * 	Long requirement list:
	 * 		skip_past_this_lib.Name is always a valid pointer, required_stats.lib may be NULL.
	 * 		If required_stats.lib is a valid pointer, then required_stats.lib->Name MUST also
	 * 		be a valid pointer.
	 */
	if (skip_past_this_lib.Name != NULL)
	{
		if ((required_stats.lib == NULL) ||
		    ((required_stats.lib != NULL) && (required_stats.lib->Name != NULL)))
		{
			// Check for perferred library.
			if ((required_stats.lib == NULL) || (strcmp(TU_LibID_none.Name, required_stats.lib->Name) == 0))
			{
				// No perferred library to check.
				checkedPerferredlib = true;
			}
			
			// Check for a library to skip past.
			if (strcmp(TU_LibID_none.Name, skip_past_this_lib.Name) == 0)
			{
				// There is no library for us to skip to.
				passedSkipLib = true;
			}

#ifdef MSYS_PLUGIN_SUPPORT
			else	// This else statement only has relavence if plugin support is enabled.
			{
				// Check and see if it is a plugin we must skip.
				if (skip_past_this_lib.bIsPlugin)
				{
					// Set the flag to skip the plugins.
					skipPlugins = true;
				}
			}

			// Make sure the plugins are loaded, but only do it if we have not already done so.
			if ((!loadedPlugins) && (TU_loadedPlugins.size() <= 0))
			{
				// Load the plugins.
				loadedPlugins = Load_Plugins(NULL);
			}

			// Check the plugins. (If we are not skipping them.)
			if (!skipPlugins)
			{
				// Begin check loop.
				for (size_t x = 0; ((x < TU_loadedPlugins.size()) && (ret == &TU_LibID_none)); ++x)
				{
					// Check the current library for a valid TU_Library_Support_Status structure.
					if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
					    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
					    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL))
					{
						/*
						 * If we have a library to skip check it,
						 * otherwise skip_past_this_lib.Name should be the same as TU_LibID_none.Name.
						 */
						if (passedSkipLib) // There is no given library to skip. / We've already skipped past that library.
						{
							/*
							 * Check to see if we need to check the prefered library.
							 * 
							 * checkedPerferredlib will be true if we have already checked the prefered library,
							 * and it does not meet the given requirements. OR if there was no prefered library
							 * given by the caller.
							 * 
							 * If checkedPerferredlib is false, we must check the current LibraryID structure
							 * to see if it matches the given prefered library. If the current library does
							 * not match the prefered library, then we must skip the current library.
							 */
							if ((checkedPerferredlib) ||
							    ((!checkedPerferredlib) &&
							    (strcmp(required_stats.lib->Name, TU_loadedPlugins[x].libSupportStatus->lib->Name) == 0)))
							{
								// Check the library if the above is ok.
								if (Check_Library(required_stats, *(TU_loadedPlugins[x].libSupportStatus)) == true)
								{
									// Select the plugin.
									ret = TU_loadedPlugins[x].libSupportStatus->lib;

									// Clear Common::commonLastErrorCode.
									Common::commonLastErrorCode = Common::COMMON_SUCCESS;
								}
								else
								{
									// Check to see if the current library is the prefered library.
									if ((!checkedPerferredlib) &&
									    (strcmp(required_stats.lib->Name, TU_loadedPlugins[x].libSupportStatus->lib->Name) == 0))
									{
										/* 
										 * OK the prefered library does not meet the given requirements,
										 * so, we must set the checkedPerferredlib flag, and restart the loop.
										 */
										checkedPerferredlib = true;
		//#error "// This may prevent checking the first library."
										x = 0;
									}
								}
							}
						}
						else
						{
							// Check to see if the current library is the library to skip past.
							if (strcmp(skip_past_this_lib.Name, TU_loadedPlugins[x].libSupportStatus->lib->Name) == 0)
							{
								/* 
								 * The current library is the one we should skip past in the list,
								 * so set the passedSkipLib flag so we can start checking for a
								 * library that meets the given requirements.
								 */
								passedSkipLib = true;
							}
						}
					}
				}
			}
#endif // MSYS_PLUGIN_SUPPORT

			// Check the internally supported libraries only if a plugin was not selected.
			for (size_t x = 0; ((x < Get_Number_of_Internal_Thread_Libraries()) && (ret == &TU_LibID_none)); ++x)
			{
				// Check the current library for a valid LibraryID structure.
				if ((TU_supportedThreadLibs[x].libSupportStatus.lib != NULL) &&
				    (TU_supportedThreadLibs[x].libSupportStatus.lib->Name != NULL))
				{
					/*
					 * If we have a library to skip check it,
					 * otherwise skip_past_this_lib.Name should be the same as TU_LibID_none.Name.
					 */
					if (passedSkipLib) // There is no given library to skip. / We've already skipped past that library.
					{
						/*
						 * Check to see if we need to check the prefered library.
						 * 
						 * checkedPerferredlib will be true if we have already checked the prefered library,
						 * and it does not meet the given requirements. OR if there was no prefered library
						 * given by the caller.
						 * 
						 * If checkedPerferredlib is false, we must check the current LibraryID structure
						 * to see if it matches the given prefered library. If the current library does
						 * not match the prefered library, then we must skip the current library.
						 */
						if ((checkedPerferredlib) ||
						    ((!checkedPerferredlib) &&
						    (strcmp(required_stats.lib->Name, TU_supportedThreadLibs[x].libSupportStatus.lib->Name) == 0)))
						{
							// Check the library if the above is ok.
							if (Check_Library(required_stats, TU_supportedThreadLibs[x].libSupportStatus) == true)
							{
								// Select the library.
								ret = TU_supportedThreadLibs[x].libSupportStatus.lib;

								// Clear Common::commonLastErrorCode.
								Common::commonLastErrorCode = Common::COMMON_SUCCESS;
							}
							else
							{
								// Check to see if the current library is the prefered library.
								if ((!checkedPerferredlib) &&
								    (strcmp(required_stats.lib->Name, TU_supportedThreadLibs[x].libSupportStatus.lib->Name) == 0))
								{
									/* 
									 * OK the prefered library does not meet the given requirements,
									 * so, we must set the checkedPerferredlib flag, and restart the loop.
									 */
									checkedPerferredlib = true;
		//#error "// This may prevent checking the first library."
									x = 0;
								}
							}
						}
					}
					else
					{
						// Check to see if the current library is the library to skip past.
						if (strcmp(skip_past_this_lib.Name, TU_supportedThreadLibs[x].libSupportStatus.lib->Name) == 0)
						{
							/* 
							 * The current library is the one we should skip past in the list,
							 * so set the passedSkipLib flag so we can start checking for a
							 * library that meets the given requirements.
							 */
							passedSkipLib = true;
						}
					}
				}
			}
		}
		else
		{
			// Invalid argument.
			Common::commonLastErrorCode = Common::COMMON_INVALID_ARGUMENT;
		}
	}
	else
	{
		// Invalid argument.
		Common::commonLastErrorCode = Common::COMMON_INVALID_ARGUMENT;
	}

	// Exit function.
	return *ret;
}

#ifdef MSYS_PLUGIN_SUPPORT
/*!
 * 	bool PluginLoader(const char * pluginPath)
 * 
 * 	This is the function that actually loads plugins for Thread_Utils.
 * 	(It's an internal function called by the public Common::Thread_Utils::Load_Plugins() function.
 * 	 This function should NOT be called directly.)
 */
bool PluginLoader(const char * pluginPath = NULL)
{
	// Init vars.
	bool result = false;						// Result of this function.
	bool bDupePlugin = false;					// Used to tell if we are attempting to load a plugin that has the same LibraryID as another plugin.
	int libLoadResult = 0;						// Used to hold return code from Common_Dynamic_Library_Subsystem_Load_Library().
	size_t locationCheck = 0;					// Used to hold the result from std::string::find().
	FileUtills::dirlist * pluginDirContents = NULL;			// Used to hold a pointer to the dirlist created by FileUtills::getDirectory().
	int (*pluginABICheck)(const int &) = NULL;			// Used to hold the returned function pointer for the ABI Check function from the Dynamic Loader Subsystem.
	const TU_Library_Support_Status * (*libSupportFunct)() = NULL;	// Used to hold the returned function pointer for the Library_Support_Status function from the Dynamic Loader Subsystem.
	TU_Loaded_Plugin pluginData;					// Used to store data about the plugin being loaded.
	std::string errorMsg = "";					// Used to construct error messages for the error logger.

	// Clear the pluginData structure.
	pluginData.libSupportStatus = NULL;
	pluginData.createThreadObjFunct = NULL;
	pluginData.createMutexObjFunct = NULL;
	pluginData.createConditionObjFunct = NULL;
	pluginData.destroyThreadObjFunct = NULL;
	pluginData.destroyMutexObjFunct = NULL;
	pluginData.destroyConditionObjFunct = NULL;
	pluginData.lib.bIsLoaded = false;
	pluginData.lib.bLastCallEncounteredAnError = false;
	pluginData.lib.osSpecificPointerData = NULL;
	pluginData.lib.pathToLibrary = NULL;

	// Get the file listing.
	if (pluginPath != NULL)
	{
		// Load from the given path.
		pluginDirContents = FileUtills::getDirectory(pluginPath, true);

		// Check and see if the returned list is valid.
		if ((pluginDirContents != NULL) && (pluginDirContents->list.size() > 0))
		{
			// Now, iterate through the filelist.
			for (size_t x = 0; x < pluginDirContents->list.size(); x++)
			{ 
				/* 
				 * Check for the dynamic library extension.
				 * 
				 * DL_EXTENSION should always have at least a NULL termination character in it.
				 * sizeof(DL_EXTENSION) includes the NULL termination character, but std::string::find()
				 * omits checking for it.
				 * 
				 * So we add 1 to pluginDirContents->list[x].size() to allow the check for the
				 * library extension to succeed.
				 */
				locationCheck = pluginDirContents->list[x].find(DL_EXTENSION);
				if ((locationCheck != std::string::npos) && (locationCheck == ((pluginDirContents->list[x].size() + 1) - sizeof(DL_EXTENSION))))
				{
					// Call the dynamic loader subsystem.
					libLoadResult = Common_Dynamic_Library_Subsystem_Load_Library(((pluginDirContents->path + DIR_SEP + pluginDirContents->list[x]).c_str()), false, &(pluginData.lib));

					// Check and see if the call failed.
					if ((libLoadResult == 0) && (!pluginData.lib.bLastCallEncounteredAnError) && (pluginData.lib.bIsLoaded))
					{
						// OK, attempt to get the pointer for the ABI Version Check function.
						pluginABICheck = (int (*)(const int &))Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Get_Plugin_ABI_Version");

						// Check to see if the symbol was found.
						if (pluginABICheck != NULL)
						{
							// Call the function.
							pluginABICheck(0);

							// Get the pointer for the Library_Support_Status function.
							libSupportFunct = (const TU_Library_Support_Status * (*)())Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Get_Library_Support_Status_Plugin");

							// Check to see if the function pointer is valid.
							if (libSupportFunct != NULL)
							{
								// Get the plugin's TU_Library_Support_Status data structure.
								pluginData.libSupportStatus = libSupportFunct();

								// Check to see what is supported.
								if (pluginData.libSupportStatus != NULL)
								{
									// Check to see if the LibraryID structure is valid.
									if ((pluginData.libSupportStatus->lib != NULL) &&
									    (pluginData.libSupportStatus->lib->Name != NULL) &&
									    (pluginData.libSupportStatus->lib->bIsPlugin))
									{
										// Check to see if the plugin defines the same libraryID as another plugin.
										for (size_t x = 0; ((x < TU_loadedPlugins.size()) && !bDupePlugin); x++)
										{
											if ((TU_loadedPlugins[x].libSupportStatus != NULL) &&
											    (TU_loadedPlugins[x].libSupportStatus->lib != NULL) &&
											    (TU_loadedPlugins[x].libSupportStatus->lib->Name != NULL) &&
											    (strcmp(TU_loadedPlugins[x].libSupportStatus->lib->Name, pluginData.libSupportStatus->lib->Name) == 0))
											{
												// Match found, cannot have two plugins with the same LibraryID.
												bDupePlugin = true;
											}
										}

										// Check to see if bDupePlugin is false.
										if (!bDupePlugin)
										{
											// Check for Thread support.
											if (pluginData.libSupportStatus->bThreadsSupport)
											{
												// Get the plugin's create thread function pointer.
												pluginData.createThreadObjFunct = (TU_Thread * (*)())Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Create_Thread_Object");

												// Check for failure.
												if (pluginData.lib.bLastCallEncounteredAnError)
												{
													// Log error.
													errorMsg = "PluginLoader(): Plugin (";
													errorMsg += pluginData.libSupportStatus->lib->Name;
													errorMsg += ") unable to retrive function pointer for thread creation. (Plugin's Library Support Status data structure says it should exist.) Unloading unsafe plugin.\n";
													COMMON_LOG_VERBOSE(errorMsg.c_str());

													// Clear data from structure.
													pluginData.createThreadObjFunct = NULL;

													// Close the library.
													libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
												}
												else
												{
													// Get the plugin's destroy thread function pointer.
													pluginData.destroyThreadObjFunct = (void (*)(TU_Thread **))Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Destroy_Thread_Object");

													// Check for failure.
													if (pluginData.lib.bLastCallEncounteredAnError)
													{
														// Log error.
														errorMsg = "PluginLoader(): Plugin (";
														errorMsg += pluginData.libSupportStatus->lib->Name;
														errorMsg += ") unable to retrive function pointer for thread destruction. (Plugin's Library Support Status data structure says it should exist.) Unloading unsafe plugin.\n";
														COMMON_LOG_VERBOSE(errorMsg.c_str());

														// Clear data from structure.
														pluginData.createThreadObjFunct = NULL;
														pluginData.destroyThreadObjFunct = NULL;

														// Close the library.
														libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
													}
												}
											}
											else
											{
												// Plugin does not support thread creation.
												pluginData.createThreadObjFunct = NULL;
												pluginData.destroyThreadObjFunct = NULL;
											}

											// Make sure that the plugin is still loaded.
											if ((!pluginData.lib.bLastCallEncounteredAnError) && (pluginData.lib.bIsLoaded))
											{
												// Check for Mutex support.
												if (pluginData.libSupportStatus->bMutexesSupport)
												{
													// Get the plugin's create mutex function pointer.
													pluginData.createMutexObjFunct = (TU_Mutex * (*)())Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Create_Mutex_Object");

													// Check for failure.
													if (pluginData.lib.bLastCallEncounteredAnError)
													{
														// Invalid Create Mutex function pointer.
														errorMsg = "PluginLoader(): Plugin (";
														errorMsg += pluginData.libSupportStatus->lib->Name;
														errorMsg += ") unable to retrive function pointer for mutex creation. (Plugin's Library Support Status data structure says it should exist.) Unloading unsafe plugin.\n";
														COMMON_LOG_VERBOSE(errorMsg.c_str());

														// Clear data from structure.
														pluginData.createThreadObjFunct = NULL;
														pluginData.destroyThreadObjFunct = NULL;
														pluginData.createMutexObjFunct = NULL;

														// Close the library.
														libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
													}
													else
													{
														// Get the plugin's destroy mutex function pointer.
														pluginData.destroyMutexObjFunct = (void (*)(TU_Mutex **))Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Destroy_Mutex_Object");

														// Check for failure.
														if (pluginData.lib.bLastCallEncounteredAnError)
														{
															// Invalid Destroy Mutex function pointer.
															errorMsg = "PluginLoader(): Plugin (";
															errorMsg += pluginData.libSupportStatus->lib->Name;
															errorMsg += ") unable to retrive function pointer for mutex destruction. (Plugin's Library Support Status data structure says it should exist.) Unloading unsafe plugin.\n";
															COMMON_LOG_VERBOSE(errorMsg.c_str());

															// Clear data from structure.
															pluginData.createThreadObjFunct = NULL;
															pluginData.destroyThreadObjFunct = NULL;
															pluginData.createMutexObjFunct = NULL;
															pluginData.destroyMutexObjFunct = NULL;

															// Close the library.
															libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
														}
													}
												}
												else
												{
													// Plugin does not support mutex creation.
													pluginData.createMutexObjFunct = NULL;
													pluginData.destroyMutexObjFunct = NULL;
												}

												// Make sure that the plugin is still loaded.
												if ((!pluginData.lib.bLastCallEncounteredAnError) && (pluginData.lib.bIsLoaded))
												{
													// Check for Condition variable support.
													if (pluginData.libSupportStatus->bConditionVariableSupport)
													{
														// Get the plugin's create condition variable function pointer.
														pluginData.createConditionObjFunct = (TU_Condition * (*)())Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Create_Condition_Object");

														// Check for failure.
														if (pluginData.lib.bLastCallEncounteredAnError)
														{
															// Invalid Create Condition Variable function pointer.
															errorMsg = "PluginLoader(): Plugin (";
															errorMsg += pluginData.libSupportStatus->lib->Name;
															errorMsg += ") unable to retrive function pointer for condition variable creation. (Plugin's Library Support Status data structure says it should exist.) Unloading unsafe plugin.\n";
															COMMON_LOG_VERBOSE(errorMsg.c_str());

															// Clear data from structure.
															pluginData.createThreadObjFunct = NULL;
															pluginData.destroyThreadObjFunct = NULL;
															pluginData.createMutexObjFunct = NULL;
															pluginData.destroyMutexObjFunct = NULL;
															pluginData.createConditionObjFunct = NULL;

															// Close the library.
															libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
														}
														else
														{
															// Get the plugin's destroy condition variable function pointer.
															pluginData.destroyConditionObjFunct = (void (*)(TU_Condition **))Common_Dynamic_Library_Subsystem_Get_Symbol(&(pluginData.lib), "TU_Destroy_Condition_Object");

															// Check for failure.
															if (pluginData.lib.bLastCallEncounteredAnError)
															{
																// Invalid Destroy Condition Variable function pointer.
																errorMsg = "PluginLoader(): Plugin (";
																errorMsg += pluginData.libSupportStatus->lib->Name;
																errorMsg += ") unable to retrive function pointer for condition variable destruction. (Plugin's Library Support Status data structure says it should exist.) Unloading unsafe plugin.\n";
																COMMON_LOG_VERBOSE(errorMsg.c_str());

																// Clear data from structure.
																pluginData.createThreadObjFunct = NULL;
																pluginData.destroyThreadObjFunct = NULL;
																pluginData.createMutexObjFunct = NULL;
																pluginData.destroyMutexObjFunct = NULL;
																pluginData.createConditionObjFunct = NULL;
																pluginData.destroyConditionObjFunct = NULL;

																// Close the library.
																libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
															}
														}
													}
													else
													{
														// Plugin does not support condition variable creation.
														pluginData.createConditionObjFunct = NULL;
														pluginData.destroyConditionObjFunct = NULL;
													}

													// Make sure that the plugin is still loaded.
													if ((!pluginData.lib.bLastCallEncounteredAnError) && (pluginData.lib.bIsLoaded))
													{
														// Make sure data is valid.
														if ((!(pluginData.libSupportStatus->bThreadsSupport)) ||
														    ((pluginData.libSupportStatus->bThreadsSupport) && (pluginData.createThreadObjFunct != NULL) &&
														     (pluginData.destroyThreadObjFunct != NULL)))
														{
															if ((!(pluginData.libSupportStatus->bMutexesSupport)) ||
															    ((pluginData.libSupportStatus->bMutexesSupport) && (pluginData.createMutexObjFunct != NULL) &&
															      (pluginData.destroyMutexObjFunct != NULL)))
															{
																if ((!(pluginData.libSupportStatus->bConditionVariableSupport)) ||
																    ((pluginData.libSupportStatus->bConditionVariableSupport) && (pluginData.createConditionObjFunct != NULL) &&
																      (pluginData.destroyConditionObjFunct != NULL)))
																{
																	// Add data to TU_loadedPlugins vector.
																	TU_loadedPlugins.push_back(pluginData);
																	errorMsg = "PluginLoader(): Loaded threading subsystem plugin: (";
																	errorMsg += pluginData.libSupportStatus->lib->Name;
																	errorMsg += ").\n";
																	COMMON_LOG_DEBUG(errorMsg.c_str());
																}
																else
																{
																	// Invalid Create Condition Variable function pointer.
																	errorMsg = "PluginLoader(): Plugin (";
																	errorMsg += pluginData.libSupportStatus->lib->Name;
																	errorMsg += ") Verification of Condition Variable function pointers failed. Unloading unsafe plugin.\n";
																	COMMON_LOG_VERBOSE(errorMsg.c_str());

																	// Unload unsafe plugin.
																	libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
																}
															}
															else
															{
																// Invalid Create Mutex function pointer.
																errorMsg = "PluginLoader(): Plugin (";
																errorMsg += pluginData.libSupportStatus->lib->Name;
																errorMsg += ") Verification of Mutex function pointers failed. Unloading unsafe plugin.\n";
																COMMON_LOG_VERBOSE(errorMsg.c_str());

																// Unload unsafe plugin.
																libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
															}
														}
														else
														{
															// Invalid Create Thread function pointer.
															errorMsg = "PluginLoader(): Plugin (";
															errorMsg += pluginData.libSupportStatus->lib->Name;
															errorMsg += ") Verification of Thread function pointers failed. Unloading unsafe plugin.\n";
															COMMON_LOG_VERBOSE(errorMsg.c_str());

															// Unload unsafe plugin.
															libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
														}
													}
												}
											}
										}
										else
										{
											// Attempted to load a second plugin that has the same LibraryID as an already loaded plugin.
											errorMsg = "PluginLoader(): threading subsystem Plugin (";
											errorMsg += pluginData.libSupportStatus->lib->Name;
											errorMsg += ") is already loaded. Ignoring.\n";
											COMMON_LOG_DEBUG(errorMsg.c_str());

											// Unload already loaded plugin.
											libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
										}
									}
									else
									{
										// Invalid plugin LibraryID data structure. (Improper library.)
										errorMsg = "PluginLoader(): Threading subsystem plugin library file (";
										errorMsg += pluginDirContents->path + DIR_SEP + pluginDirContents->list[x];
										errorMsg += ") has an invalid LibraryID structure, skipping.\n";
										COMMON_LOG_WARNING(errorMsg.c_str());

										// Unload unsafe plugin.
										libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
									}
								}
								else
								{
									// Could not get library support status structure.
									errorMsg = "PluginLoader(): Could not get Library Support Status data structure for threading subsystem library file (";
									errorMsg += pluginDirContents->path + DIR_SEP + pluginDirContents->list[x];
									errorMsg += "), skipping.\n";
									COMMON_LOG_VERBOSE(errorMsg.c_str());

									// Unload unsafe plugin.
									libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
								}
							}
							else
							{
								// The function does not exist so close the library. (Improper library.)
								errorMsg = "PluginLoader(): Threading subsystem plugin library file (";
								errorMsg += pluginDirContents->path + DIR_SEP + pluginDirContents->list[x];
								errorMsg += ") has a valid TU_Get_Plugin_ABI_Version() function, but lacks a TU_Get_Library_Support_Status_Plugin() function. Skipping.\n";
								COMMON_LOG_WARNING(errorMsg.c_str());

								// Unload unsafe plugin.
								libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
							}

							// Clear the pluginData structure.
							pluginData.libSupportStatus = NULL;
							pluginData.createThreadObjFunct = NULL;
							pluginData.createMutexObjFunct = NULL;
							pluginData.createConditionObjFunct = NULL;
							pluginData.destroyThreadObjFunct = NULL;
							pluginData.destroyMutexObjFunct = NULL;
							pluginData.destroyConditionObjFunct = NULL;
							pluginData.lib.bIsLoaded = false;
							pluginData.lib.bLastCallEncounteredAnError = false;
							pluginData.lib.osSpecificPointerData = NULL;
							pluginData.lib.pathToLibrary = NULL;
						}
						else
						{
							// The function does not exist so close the library. (Not a plugin.)
							errorMsg = "PluginLoader(): Library file (";
							errorMsg += pluginDirContents->path + DIR_SEP + pluginDirContents->list[x];
							errorMsg += ") is not a threading subsystem plugin, skipping.\n";
							COMMON_LOG_VERBOSE(errorMsg.c_str());
							libLoadResult = Common_Dynamic_Library_Subsystem_Unload_Library(&(pluginData.lib));
						}
 
						// Clear the pointer.
						libSupportFunct = NULL;
					}
					else
					{
						errorMsg = "PluginLoader(): Call to Common_Dynamic_Library_Subsystem_Load_Library() failed for library file: (";
						errorMsg += (pluginDirContents->path + DIR_SEP + pluginDirContents->list[x]);
						errorMsg += ").\n";
						COMMON_LOG_VERBOSE(errorMsg.c_str());
					}
				}
				else
				{
					// Failed to find DL_EXTENSION.
					errorMsg = "PluginLoader(): File (";
					errorMsg += (pluginDirContents->path + DIR_SEP + pluginDirContents->list[x]);
					errorMsg += ") is not a library file.\n";
					COMMON_LOG_VERBOSE(errorMsg.c_str());
				}
			}

			/*
			 * We return true even if we did not load any plugins.
			 * (Return value indicates any avaiable plugins from the given
			 *  directory were loaded. (Not including already loaded plugins,
			 *  as we only permit one plugin to be loaded for any given LibraryID.
			 *  E.g. no duplicates.))
			 */
			result = true;
		}
		else
		{
			// Returned directory list is invalid.
			errorMsg = "PluginLoader(): Unable to retrive directory listing for ";
			errorMsg += pluginPath;
			errorMsg += ".\n";
			COMMON_LOG_WARNING(errorMsg.c_str());
		}
	}
	else
	{
		// Plugin path invalid.
		COMMON_LOG_VERBOSE("PluginLoader: Given plugin path is NULL.\n");
	}

	// Return result.
	return result;
}

bool Common::Thread_Utils::Load_Plugins(const char * pluginPath)
{
	// Init vars.
	static bool done = false;			// Used to prevent multiple loads of the plugins.
	bool resultOfCallToPluginLoader = false;	// Used to store the return code from PluginLoader().
	std::string execDir = "";			// Used to store the executable path returned from FileUtills::GetExecDirectory().

	// Clear Common::commonLastErrorCode.
	Common::commonLastErrorCode = Common::COMMON_SUCCESS;

	// Only load the plugins once.
	if (!done)
	{
		// Log attempt...
		COMMON_LOG_VERBOSE("Thread_Utils::Load_Plugins(): Attempting to load plugins.\n");

		// Check to see if we were given a path to load from.
		if (pluginPath != NULL)
		{
			// Attempt to load the plugins from the given path first.
			resultOfCallToPluginLoader = PluginLoader(pluginPath);
		}

		// Get the current executable directory.
		execDir = FileUtills::GetExecDirectory();

		// Check to see if we got a valid directory.
		if (execDir.size() > 0)
		{
			// Add the path to the plugin subdirectory.
			execDir += TW_EXEC_PLUGIN_DIR_PATH;

			// Load the plugins from the plugins directory. (It's a subdirectory of the executable's directory.)
			resultOfCallToPluginLoader = PluginLoader(execDir.c_str());
		}
		else
		{
			// We can't get the path to the executable's installation directory, so log the error, and continue.
			COMMON_LOG_VERBOSE("Thread_Utils::Load_Plugins(): Unable to get the path to the executable's installation directory, ignoring.\n");
		}

		// Attempt to load from the default installation path.
		resultOfCallToPluginLoader = PluginLoader(TW_DEFAULT_INSTALL_PLUGIN_PATH);

		// Check to see if we could not load plugins from a directory.
		if (TU_loadedPlugins.size() > 0)
		{
			// We only need to do this once.
			COMMON_LOG_DEBUG("Thread_Utils::Load_Plugins(): Plugin load successful.\n");
			done = true;
		}
		else
		{
			// Log failure.
			COMMON_LOG_DEBUG("Thread_Utils::Load_Plugins(): No plugins loaded.\n");
		}
	}

	// Exit function.
	return done;
}
#endif // MSYS_PLUGIN_SUPPORT
