/*!
    Multiverse Engine Project 18/5/2013 Common Thread_Utils_Functions.h
    
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

#ifndef THREAD_UTILS_FUNCTIONS_H
#define THREAD_UTILS_FUNCTIONS_H

namespace Common
{
        namespace Thread_Utils
        {
                /*!
                        Common::Thread_Utils::Thread * Common::Thread_Utils::Create_Thread(const Common::Thread_Utils::supportedThreadLibs & lib)

                        This function creates a thread class object for use with the given thread library.
                        Note: This function uses new to allocate the new object.
                        When you are done with it you must use delete to release it's memory.

                        Returns a pointer to the created thread class object if successfull.
                        Otherwise returns NULL.
                */
                Thread * Create_Thread(const supportedThreadLibs & lib);

                /*!
                        Common::Thread_Utils::Mutex * Common::Thread_Utils::Create_Mutex(const Common::Thread_Utils::supportedThreadLibs & lib)

                        This function creates a mutex class object for use with the given thread library.
                        Note: This function uses new to allocate the new object.
                        When you are done with it you must use delete to release it's memory.

                        Returns a pointer to the created mutex class object if successfull.
                        Otherwise returns NULL.
                */
                Mutex * Create_Mutex(const supportedThreadLibs & lib);
        };
};

#endif

// End of Thread_Utils_Functions.h
