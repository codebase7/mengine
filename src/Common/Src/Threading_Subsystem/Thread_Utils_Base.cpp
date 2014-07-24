/*!
    Multiverse Engine Project 20/5/2013 Common Thread_Utils_Base.cpp

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

#include "Thread_Utils.h"

const Common_LibraryID & TU_Thread::Get_Thread_Library() const
{
        // Return thread library ID.
        return this->lib;
}

int TU_Thread::Get_Return_Code() const
{
        // Return last library return code.
        return this->rc_from_prevOP;
}

short TU_Thread::Create_Thread(void *(*real_funct_ptr)(void*), void * function_args, unsigned long int * thread_id)
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a thread object.)
        return -3;
}

short TU_Thread::Detach_Thread()
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a thread object.)
        return -3;
}

short TU_Thread::Join_Thread(void ** ret_from_thread)
{
        // Return not implimented. (This function is NOT implimented here as it's only a placeholder. The base class does not have a thread object.)
        return -3;
}
