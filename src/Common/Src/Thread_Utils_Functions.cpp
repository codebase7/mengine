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

Common::Thread_Utils::Thread * Common::Thread_Utils::Create_Thread(const Common::Thread_Utils::supportedThreadLibs & lib)
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
                if (lib == pthreads)
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

Common::Thread_Utils::Mutex * Common::Thread_Utils::Create_Mutex(const Common::Thread_Utils::supportedThreadLibs & lib)
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
                if (lib == pthreads)
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
