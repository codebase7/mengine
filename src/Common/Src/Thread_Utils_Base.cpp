/*!
    Multiverse Engine Project 20/5/2013 Common Thread_Utils_Base.cpp
    
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

const char * Common::Thread_Utils::Get_Library_Name(const Common::Thread_Utils::supportedThreadLibs & lib)
{
        // Check for each library.
        #ifdef TW_PTHREADS_SUPPORT
        if (lib == pthreads)
        {
                return "Pthreads\0";
        }
        #endif

        // If we get here return none / unsupported.
        return "None / Unsupported\0";
}

Common::Thread_Utils::supportedThreadLibs Common::Thread_Utils::Thread::Get_Thread_Library() const
{
        // Return thread library ID.
        return this->thread_lib;
}

int Common::Thread_Utils::Thread::Get_Return_Code() const
{
        // Return last library return code.
        return this->rc_from_prevOP;
}

short Common::Thread_Utils::Thread::Create_Thread(void *(*real_funct_ptr)(void*), void * function_args, unsigned long int * thread_id)
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a thread object.)
        return -3;
}

short Common::Thread_Utils::Thread::Detach_Thread()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a thread object.)
        return -3;
}

short Common::Thread_Utils::Thread::Join_Thread(void * ret_from_thread)
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a thread object.)
        return -3;
}

Common::Thread_Utils::supportedThreadLibs Common::Thread_Utils::Mutex::Get_Thread_Library() const
{
        // Return thread library ID.
        return this->thread_lib;
}

int Common::Thread_Utils::Mutex::Get_Return_Code() const
{
        // Return last library return code.
        return this->rc_from_prevOP;
}

short Common::Thread_Utils::Mutex::Init_Mutex()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a mutex object.)
        return -3;
}

short Common::Thread_Utils::Mutex::Destroy_Mutex()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a mutex object.)
        return -3;
}

short Common::Thread_Utils::Mutex::Lock_Mutex()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a mutex object.)
        return -3;
}

short Common::Thread_Utils::Mutex::Try_Lock_Mutex()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a mutex object.)
        return -3;
}

short Common::Thread_Utils::Mutex::Unlock_Mutex()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a mutex object.)
        return -3;
}
