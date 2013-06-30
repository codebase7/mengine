/*!
    Multiverse Engine Project 16/5/2013 Common Thread_Utils_pthread.cpp
    
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

// Only define things if pthread support is enabled.
#ifdef TW_PTHREADS_SUPPORT

short Common::Thread_Utils::Mutex_pthread::Init_Mutex(pthread_mutexattr_t * attr)
{
        // Check for pthreads.
        if (this->thread_lib != pthreads)
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Check and see if the mutex is already inited.
        if (this->mutex_init)
        {
                // Error, mutex must not be inited.
                return -4;
        }
        else
        {
                // Check and see if the attribs object is inited.
                if (this->attrib_init)
                {
                        // We need to destroy the attribs object first.
                        this->rc_from_prevOP = pthread_mutexattr_destroy(&attribs);

                        // Check for error.
                        if (this->rc_from_prevOP)
                        {
                                // An error occured.
                                return -5;
                        }

                        // Set attrib_init to false.
                        this->attrib_init = false;
                }

                // Init the attribs object.
                if (attr != NULL)
                {
                        // Copy the attributes object.
                        this->attribs = *attr;
                }
                else
                {
                        // Init attribs.
                        this->rc_from_prevOP = pthread_mutexattr_init(&attribs);

                        // Check for error.
                        if (this->rc_from_prevOP)
                        {
                                // An error occured.
                                return -5;
                        }
                }

                // Set attrib init.
                this->attrib_init = true;

                // Init the actual mutex.
                this->rc_from_prevOP = pthread_mutex_init(&mutex, &attribs);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set mutex init.
                this->mutex_init = true;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Mutex_pthread::Destroy_Mutex()
{
        // Check for pthreads.
        if (this->thread_lib != pthreads)
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Check and see if the mutex has been inited.
        if (this->mutex_init)
        {
                // Unlock the mutex.
                this->rc_from_prevOP = pthread_mutex_unlock(&mutex);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured starting the thread.
                        return -5;
                }

                // Destroy mutex.
                this->rc_from_prevOP = pthread_mutex_destroy(&mutex);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set mutex_init to false.
                this->mutex_init = false;
        }

        // Check and see if the attribs object has been inited.
        if (this->attrib_init)
        {
                // Destroy the attribs object.
                this->rc_from_prevOP = pthread_mutexattr_destroy(&attribs);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set attrib_init to false.
                this->attrib_init = false;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Mutex_pthread::Lock_Mutex()
{
        // Check for pthreads.
        if (this->thread_lib != pthreads)
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Lock the mutex.
        this->rc_from_prevOP = pthread_mutex_lock(&mutex);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // An error occured.
                return -5;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Mutex_pthread::Try_Lock_Mutex()
{
        // Check for pthreads.
        if (this->thread_lib != pthreads)
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Try to lock the mutex.
        this->rc_from_prevOP = pthread_mutex_trylock(&mutex);

        // Check to see if the mutex is busy.
        if (this->rc_from_prevOP == EBUSY)
        {
                // OK, the thing is busy, return OK.
                return 1;
        }
        else
        {
                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured starting the thread.
                        return -5;
                }
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Mutex_pthread::Unlock_Mutex()
{
        // Check for pthreads.
        if (this->thread_lib != pthreads)
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Unlock the mutex.
        this->rc_from_prevOP = pthread_mutex_unlock(&mutex);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // An error occured starting the thread.
                return -5;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Thread_pthread::Create_Thread(void *(*real_funct_ptr)(void*), void * function_args, unsigned long int * thread_id)
{
        // Check for pthreads in the thread struct.
        if (this->thread_lib != pthreads)
        {
                // This has not been inited by the user, or is already being used. Abort.
                return -1;
        }

        // Check and see if the thread is already inited.
        if (this->thread_init)
        {
                // Thread already inited, abort.
                return -4;
        }
        else
        {
                // Check and see if the attribs object is already inited.
                if (this->attrib_init)
                {
                        // Check and see if the attribs object was specified by the user.
                        if (!this->user_attrib)
                        {
                                // We need to destroy the attribs object first.
                                this->rc_from_prevOP = pthread_attr_destroy(&attribs);

                                // Check for error.
                                if (this->rc_from_prevOP)
                                {
                                        // An error occured.
                                        return -5;
                                }

                                // Set attrib_init to false.
                                this->attrib_init = false;
                        }
                }

                // Note: if statement used due to the above if statement possibly destroying the attribs object.
                if (!this->attrib_init)
                {
                        // Init the attribs object.
                        this->rc_from_prevOP = pthread_attr_init(&attribs);

                        // Check for error.
                        if (this->rc_from_prevOP)
                        {
                                // An error occured starting the thread.
                                return -5;
                        }

                        // Set attrib_init.
                        this->attrib_init = true;
                }

                // Check for a valid functionn pointer.
                if (real_funct_ptr == NULL)
                {
                        // Need a valid pointer.
                        return -2;
                }

                // Call pthread_create. (Here we use the thread.thread_attr as the pthread thread attributes object.)
                this->rc_from_prevOP = pthread_create(&pid, &attribs, real_funct_ptr, function_args);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured starting the thread.
                        return -5;
                }

                // Set thread_init.
                this->thread_init = true;

                // If thread_pid is not NULL.
                if (thread_id != NULL)
                {
                        // Set thread_id to the new pid.
                        *thread_id = this->pid;
                }
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Thread_pthread::Destroy_Thread()
{
        // Check and see if the thread object is inited.
        if (this->thread_init)
        {
                // Delete the pid.
                this->pid = 0;

                // Set thread_init to false.
                this->thread_init = false;
        }

        // Check and see if the attribs object is inited.
        if (this->attrib_init)
        {
                // Destroy the attribs object.
                this->rc_from_prevOP = pthread_attr_destroy(&attribs);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set attrib_init to false.
                this->attrib_init = false;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Thread_pthread::Detach_Thread()
{
        // Check and see if the thread_lib used is ours.
        if (this->thread_lib != pthreads)
        {
                // This thread was not created by our library. Abort.
                return -1;
        }

        // Call detech.
        this->rc_from_prevOP = pthread_detach(pid);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // An error occured.
                return -5;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Thread_pthread::Join_Thread(void * ret_from_thread)
{
        // Check and see if the thread_lib used is ours.
        if (this->thread_lib != pthreads)
        {
                // This thread was not created by our library. Abort.
                return -1;
        }

        // Call pthread_join().
        this->rc_from_prevOP = pthread_join(pid, &ret_from_thread);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // An error occured.
                return -5;
        }

        // Exit function.
        return 0;
}

short Common::Thread_Utils::Thread_pthread::Set_Attribs(pthread_attr_t * attr)
{
        // Check and see if the thread_lib used is ours.
        if (this->thread_lib != pthreads)
        {
                // This thread was not created by our library. Abort.
                return -1;
        }

        // Set the attribs object.
        if (attr != NULL)
        {
                // Copy the attrib object.
                this->attribs = *attr;

                // Set the flags.
                this->user_attrib = true;
                this->attrib_init = true;
        }
        else
        {
                // Set the flags.
                this->user_attrib = false;
                this->attrib_init = true;
        }

        // Exit function.
        return 0;
}

#endif
