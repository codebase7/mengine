/*!
    Multiverse Engine Project 16/5/2013 Common Thread_Utils_Functions.cpp

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

#include "Thread_Utils.h"

short Common::Thread_Utils::Get_Number_of_Supported_Thread_Libraries()
{
        /*
            Calculate size of array. (sizeof entire array / sizeof single element in array.)
            (Note: This works as the array is global to the namespace and therefore does not need to be passed to us.)
        */
        short ret = sizeof(Common::Thread_Utils::supportedThreadLibs) / sizeof(Common::Thread_Utils::supportedThreadLibs[0]);

        // Return result.
        return ret;
}

Common::Thread_Utils::Thread * Common::Thread_Utils::Create_Thread(const Common::LibraryID & lib)
{
        // Init return var.
        Common::Thread_Utils::Thread * ret = NULL;

        // Begin try block.
        try{
                /*
                        Below is a check for each supported thread library type.
                        If a thread library is requested that is disabled or not supported, we return NULL.
                */
                #ifdef TW_PTHREADS_SUPPORT
                // Create new object.
                if (lib.IDNum == 1)     // PThreads ID {1, "Pthreads"}.
                {
                        ret = new Common::Thread_Utils::Thread_pthread;
                }
                #endif
        }
        catch(...)
        {
                // An error occured.
                if (ret != NULL)
                {
                        delete ret;
                }
                ret = NULL;
        }

        // Exit function.
        return ret;
}

Common::Thread_Utils::Mutex * Common::Thread_Utils::Create_Mutex(const Common::LibraryID & lib)
{
        // Init return var.
        Common::Thread_Utils::Mutex * ret = NULL;

        // Begin try block.
        try{
                /*
                        Below is a check for each supported thread library type.
                        If a thread library is requested that is disabled or not supported, we return NULL.
                */
                #ifdef TW_PTHREADS_SUPPORT
                // Create new object.
                if (lib.IDNum == 1)     // PThreads ID {1, "Pthreads"}.
                {
                        ret = new Common::Thread_Utils::Mutex_pthread;
                }
                #endif
        }
        catch(...)
        {
                // An error occured.
                if (ret != NULL)
                {
                        delete ret;
                }
                ret = NULL;
        }

        // Exit function.
        return ret;
}

Common::Thread_Utils::Condition * Common::Thread_Utils::Create_Condition(const Common::LibraryID & lib)
{
        // Init return var.
        Common::Thread_Utils::Condition * ret = NULL;

        // Begin try block.
        try{
                /*
                        Below is a check for each supported thread library type.
                        If a thread library is requested that is disabled or not supported, we return NULL.
                */
                #ifdef TW_PTHREADS_SUPPORT
                // Create new object.
                if (lib.IDNum == 1)     // PThreads ID {1, "Pthreads"}.
                {
                        ret = new Common::Thread_Utils::Condition_pthread;
                }
                #endif
        }
        catch(...)
        {
                // An error occured.
                if (ret != NULL)
                {
                        delete ret;
                }
                ret = NULL;
        }

        // Exit function.
        return ret;
}

void Common::Thread_Utils::Init_Library_Support_Status(Common::Thread_Utils::Library_Support_Status * str)
{
        // Check for NULL.
        if (str != NULL)
        {
                str->lib = &Common::Thread_Utils::supportedThreadLibs[0];         // {0, "None / Unsupported"}
                str->bThreadsSupport = false;
                str->bJoinThreadSupport = false;
                str->bDetachThreadSupport = false;
                str->bLibraryRequiresSpecificFunctionSig = false;
                str->bMutexesSupport = false;
                str->bTryLockSupport = false;
                str->bConditionVariableSupport = false;
                str->bConditionWaitTimeoutSupport = false;
        }

        // Exit function.
        return;
}

const Common::Thread_Utils::Library_Support_Status * Common::Thread_Utils::Get_Library_Stats(const Common::LibraryID & lib)
{
        // Init return var.
        const Common::Thread_Utils::Library_Support_Status * ret = &Common::Thread_Utils::LibSupport_none;

        /*
                Below is a check for each supported thread library type.
                If a thread library is requested that is disabled or not supported, we return the none / unsupported struct.
        */
        #ifdef TW_PTHREADS_SUPPORT
        if (lib.IDNum == 1)     // PThreads ID {1, "Pthreads"}.
        {
                ret = &Common::Thread_Utils::LibSupport_pthreads;
        }
        #endif

        // Exit function.
        return ret;
}

const Common::LibraryID & Common::Thread_Utils::Select_Library(const Common::Thread_Utils::Library_Support_Status & required_stats, const Common::LibraryID & skip_past_this_lib)
{
        // Init result.
        const Common::LibraryID * ret = &Common::Thread_Utils::supportedThreadLibs[0];        // None / Unsupported.

        // Init other vars.
        bool checkedPerferredlib = false;   // Used to tell if we have checked the perferred library.
        short skipOffset = 0;               // Used to skip past libraries.
        short numberOfLibs = Common::Thread_Utils::Get_Number_of_Supported_Thread_Libraries();
        const Common::Thread_Utils::Library_Support_Status * stat = NULL;

        // Check and see if there is a perferred lib.
        if ((required_stats.lib == NULL) || (required_stats.lib->IDNum == 0))
        {
                // No perferred lib to check.
                checkedPerferredlib = true;
        }

        // If we need to skip past some libraries.
        if (skip_past_this_lib.IDNum != 0)
        {
                // Find the library in the array.
                for (skipOffset = 0; skipOffset < numberOfLibs; skipOffset++)
                {
                        // First get the status of the current library.
                        stat = NULL;
                        stat = Common::Thread_Utils::Get_Library_Stats(Common::Thread_Utils::supportedThreadLibs[skipOffset]);
                        if (stat == NULL)
                        {
                                // Could not get a library abort.
                                skipOffset = -1;
                                break;
                        }

                        // Check the Library ID Number.
                        if ((stat->lib != NULL) && (stat->lib->IDNum == skip_past_this_lib.IDNum))
                        {
                                // Check and see if there are more libraries after this one.
                                if ((skipOffset + 1) < numberOfLibs)
                                {
                                        // OK, continue to the library selection loop.
                                        skipOffset++;
                                        break;
                                }
                                else
                                {
                                        // There are no more libraries.
                                        skipOffset = -1;
                                        break;
                                }
                        }
                        else
                        {
                                // Check and see if there are more libraries after this one.
                                if ((skipOffset + 1) >= numberOfLibs)
                                {
                                        // There are no more libraries.
                                        skipOffset = -1;
                                        break;
                                }
                        }
                }
        }

        // Check and see if there are remaining libraries to check.
        if ((skipOffset >= 0) && (skipOffset < numberOfLibs))
        {
                // Start library selection loop.
                for (short x = skipOffset; x < numberOfLibs; x++)
                {
                        // First get the status of the current library.
                        stat = NULL;
                        stat = Common::Thread_Utils::Get_Library_Stats(Common::Thread_Utils::supportedThreadLibs[x]);
                        if (stat == NULL)
                        {
                                // Could not get a library abort.
                                ret = &Common::Thread_Utils::supportedThreadLibs[0];        // None / Unsupported.
                                break;
                        }

                        // Check and see if we have a perferred library to check.
                        if (!checkedPerferredlib)
                        {
                                // We have a perferred library to check, see if the current library is that library.
                                if ((stat->lib == NULL) || (stat->lib->IDNum != required_stats.lib->IDNum))
                                {
                                        // Check and see if there are more libraries to check.
                                        if ((x + 1) < numberOfLibs)
                                        {
                                                // Skip this library.
                                                continue;
                                        }
                                        else
                                        {
                                                /*
                                                        We are out of libraries, (ether the library is non-existant or we have skipped it.),
                                                        reset x to skipOffset, and look for an alternitive library to use.
                                                */
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                                continue;
                                        }
                                }
                        }

                        /*
                            NOTE: We never get here if we have not checked the perferred library and the current library is not the perferred one.
                            (Unless the perferred library is non-existant, we've skipped it, or if the perferred library does not fulfill the
                             requested requirements.)
                        */

                        // OK, for each library check and see if it provides a required function.
                        if (required_stats.bThreadsSupport)
                        {
                                if (!stat->bThreadsSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bJoinThreadSupport)
                        {
                                if (!stat->bJoinThreadSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bDetachThreadSupport)
                        {
                                if (!stat->bDetachThreadSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bLibraryRequiresSpecificFunctionSig)
                        {
                                if (!stat->bLibraryRequiresSpecificFunctionSig)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bMutexesSupport)
                        {
                                if (!stat->bMutexesSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bTryLockSupport)
                        {
                                if (!stat->bTryLockSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bConditionVariableSupport)
                        {
                                if (!stat->bConditionVariableSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }
                        if (required_stats.bConditionWaitTimeoutSupport)
                        {
                                if (!stat->bConditionWaitTimeoutSupport)
                                {
                                        // If we are checking the perferred lib, then the perferred lib has failed. Reset to the skipOffset and check for an altertive library.
                                        if (!checkedPerferredlib)
                                        {
                                                x = skipOffset - 1;     // We subtract one from skip offset as continue will increment x by one.
                                                checkedPerferredlib = true;
                                        }

                                        // Ok this library does not support this, go to the next one.
                                        continue;
                                }
                        }

                        // OK return this library.
                        ret = stat->lib;
                        break;
                }
        }

        // Exit function.
        return *ret;
}
