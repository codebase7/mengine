/*!
    Multiverse Engine Project 31/5/2013 Common Thread_Utils_Structures.h

    Copyright (C) 2013 Multiverse Engine Project

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

#ifndef THREAD_UTILS_STRUCTURES_H
#define THREAD_UTILS_STRUCTURES_H

// Include Generic_Wrapper.
#include "../Generic_Wrapper.h"	// Includes LibraryID_Struct.h.

namespace Common
{
        namespace Thread_Utils
        {
                /*!
                        const Common::LibraryID supportedThreadLibs

                        Contains a list of supported threading libraries.

                        The actual list used by the engine is generated at compile time.

                        Below is the entire list of supported libraries that could be avaiable.

                        Note: That some of the libraries below may not be avaiable to the engine
                        at run-time due to external reasons.
                        (Ex. The library is not supported on the given platform, was disabled at compile
                         time due to user override, etc.)

                        Note: If you add support for a library, you must define a unique id number for it.
                        (This is to prevent the list from generating errors due to an id mismatch.)
                        Also you must add a string for it so Get_Library_Name() has something to return.
                        (We want to be able to have a human readable string just in case the ID numbers
                        change.)
                */
                const Common::LibraryID supportedThreadLibs[] =
                {
                        {0,"None / Unsupported"},
                        #ifdef TW_PTHREADS_SUPPORT
                        {1,"Pthreads"},
                        #endif
                };

                /*!
                        struct Library_Support_Status

                        This structure is used to aid programs in determining what threading library to use.

                        It contains varius info about what is supported by the current Thread_Utils.

                        Note To Library Maintainers: If support is added / removed for a given library you
                        must update it's Library_Support_Status structure.

                        Also if you add support for a new threading library you must create it's
                        Library_Support_Status structure. (In the actual header files for that particular
                        library.)
                */
                struct Library_Support_Status
                {
                        // Library ID.
                        const Common::LibraryID * lib;

                        // Thread support status.
                        bool    bThreadsSupport;
                        bool    bJoinThreadSupport;
                        bool    bDetachThreadSupport;
                        bool    bLibraryRequiresSpecificFunctionSig;

                        // Mutex support status.
                        bool    bMutexesSupport;
                        bool    bTryLockSupport;

                        // Condition variable support status.
                        bool    bConditionVariableSupport;
                        bool    bConditionWaitTimeoutSupport;
                };
        }
}

#endif

// End of Thread_Utils_Structures.h
