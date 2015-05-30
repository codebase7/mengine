/*!
    Multiverse Engine Project 16/5/2013 Common Thread_Utils_pthread.cpp

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

#ifdef _WIN32
#include "..\Thread_Utils.h"
#else
#include "../Thread_Utils.h"
#endif	/* _WIN32 */

// Only define things if pthread support is enabled.
#ifdef TW_PTHREADS_SUPPORT

short TU_Thread_pthread::Create_Thread(void *(*real_funct_ptr)(void*), void * function_args, unsigned long int * thread_id)
{
        // Check for pthreads in the thread struct.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
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

short TU_Thread_pthread::Destroy_Thread()
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This thread was not created by our library. Abort.
                return -1;
        }

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

                // Set user_attrib to false.
                this->user_attrib = false;
        }

        // Exit function.
        return 0;
}

short TU_Thread_pthread::Detach_Thread()
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
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

short TU_Thread_pthread::Join_Thread(void ** ret_from_thread)
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This thread was not created by our library. Abort.
                return -1;
        }

        // Call pthread_join().
        this->rc_from_prevOP = pthread_join(pid, ret_from_thread);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // An error occured.
                return -5;
        }

        // Exit function.
        return 0;
}

short TU_Thread_pthread::Set_Attribs(pthread_attr_t * attr)
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
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
                // Destroy the attribs object.
                this->rc_from_prevOP = pthread_attr_destroy(&attribs);

                // Set the flags.
                this->user_attrib = false;
                this->attrib_init = true;
        }

        // Exit function.
        return 0;
}

const Common_LibraryID & TU_Mutex_pthread::Get_Thread_Library() const
{
        // Return thread library ID.
        return this->lib;
}

int TU_Mutex_pthread::Get_Return_Code() const
{
        // Return last library return code.
        return this->rc_from_prevOP;
}

short TU_Mutex_pthread::Init_Mutex()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
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
                        // Check and see if the attribs object was specified by the user.
                        if (!this->user_attrib)
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
                }

                // Init the attribs object.
                // Note: if statement used due to the above if statement possibly destroying the attribs object.
                if (!this->attrib_init)
                {
                        // Init attribs.
                        this->rc_from_prevOP = pthread_mutexattr_init(&attribs);

                        // Check for error.
                        if (this->rc_from_prevOP)
                        {
                                // An error occured.
                                return -5;
                        }

                        // Set the type to errorcheck.
                        this->rc_from_prevOP = pthread_mutexattr_settype(&attribs, PTHREAD_MUTEX_ERRORCHECK);

                        // Check for error.
                        if (this->rc_from_prevOP)
                        {
                                // An error occured.
                                return -5;
                        }

                        // Set attrib init.
                        this->attrib_init = true;
                }

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

short TU_Mutex_pthread::Destroy_Mutex()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Call Destory_Mutex_Only.
        this->Destroy_Mutex_Only();

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

                // Set user_attrib to false.
                this->user_attrib = false;
        }

        // Exit function.
        return 0;
}

short TU_Mutex_pthread::Lock_Mutex()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Lock the mutex.
        this->rc_from_prevOP = pthread_mutex_lock(&mutex);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // Check to see if we already own the lock.
                if (this->rc_from_prevOP != EDEADLK)
                {
                        // An error occured.
                        return -5;
                }
        }

        // Exit function.
        return 0;
}

short TU_Mutex_pthread::Try_Lock_Mutex()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Try to lock the mutex.
        this->rc_from_prevOP = pthread_mutex_trylock(&mutex);

        // Check to see if the mutex is already locked.
        if (this->rc_from_prevOP == EBUSY)
        {
                // OK, the thing is already locked, return already locked. (Not sure if this is locked by us, or locked by someone else.....)
                return 1;
        }
        else
        {
                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured trying to lock the mutex.
                        return -5;
                }
        }

        // Exit function.
        return 0;
}

short TU_Mutex_pthread::Unlock_Mutex()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Unlock the mutex.
        this->rc_from_prevOP = pthread_mutex_unlock(&mutex);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // Check and see if we can't unlock it because we don't own it.
                if (this->rc_from_prevOP == EPERM)
                {
                        // We don't own this mutex.
                        return -2;
                }
                else
                {
                        // An error occured starting the thread.
                        return -5;
                }
        }

        // Exit function.
        return 0;
}

short TU_Mutex_pthread::Set_Attribs(pthread_mutexattr_t * attr)
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
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
                // Destroy the attribs object.
                this->rc_from_prevOP = pthread_mutexattr_destroy(&attribs);

                // Set the flags.
                this->user_attrib = false;
                this->attrib_init = true;
        }

        // Exit function.
        return 0;
}

short TU_Mutex_pthread::Destroy_Mutex_Only()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
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

        // Exit function.
        return 0;
}

const Common_LibraryID & TU_Condition_pthread::Get_Thread_Library() const
{
        // Return thread library ID.
        return this->lib;
}

int TU_Condition_pthread::Get_Return_Code() const
{
        // Return last library return code.
        return this->rc_from_prevOP;
}

short TU_Condition_pthread::Init_Condition()
{
        // Check for pthreads.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // Trying to use incorrect library abort.
                return -1;
        }

        // Init ret.
        short ret = 0;

        // Check and see if our mutex object is inited.
        if (this->mutex_init)
        {
                // Destroy the mutex first.
                ret = this->Destroy_Mutex_Only();

                // Check for error.
                if (ret)
                {
                        // Error could not destroy mutex.
                        return -2;
                }
        }

        // Init the mutex object.
        ret = this->Init_Mutex();

        // Check and see if our mutex init failed.
        if (ret)
        {
                // Mutex was not inited correctly.
                return -2;
        }

        // Check and see if the condition is already inited.
        if (this->condition_init)
        {
                // Error, condition must not be inited.
                return -4;
        }
        else
        {
                // Check and see if the attribs object is inited.
                if (this->cattrib_init)
                {
                        // Check and see if the attribs object was specified by the user.
                        if (!this->cuser_attrib)
                        {
                                // We need to destroy the attribs object first.
                                this->rc_from_prevOP = pthread_condattr_destroy(&cattribs);

                                // Check for error.
                                if (this->rc_from_prevOP)
                                {
                                        // An error occured.
                                        return -5;
                                }

                                // Set attrib_init to false.
                                this->cattrib_init = false;
                        }
                }

                // Init the attribs object.
                // Note: if statement used due to the above if statement possibly destroying the attribs object.
                if (!this->cattrib_init)
                {
                        // Init attribs.
                        this->rc_from_prevOP = pthread_condattr_init(&cattribs);

                        // Check for error.
                        if (this->rc_from_prevOP)
                        {
                                // An error occured.
                                return -5;
                        }

                        // Set attrib init.
                        this->cattrib_init = true;
                }

                // Init the actual condition.
                this->rc_from_prevOP = pthread_cond_init(&condition, &cattribs);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set condition init.
                this->condition_init = true;
        }

        // Exit function.
        return 0;
}

short TU_Condition_pthread::Destroy_Condition()
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This condition was not created by our library. Abort.
                return -1;
        }

        // Check and see if the condition object is inited.
        if (this->condition_init)
        {
                // Destroy condition.
                this->rc_from_prevOP = pthread_cond_destroy(&condition);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set condition_init to false.
                this->condition_init = false;
        }

        // Check and see if the attribs object is inited.
        if (this->cattrib_init)
        {
                // Destroy the attribs object.
                this->rc_from_prevOP = pthread_condattr_destroy(&cattribs);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // An error occured.
                        return -5;
                }

                // Set cattrib_init to false.
                this->cattrib_init = false;

                // Set cuser_attrib to false.
                this->cuser_attrib = false;
        }

        // Exit function.
        return 0;
}

short TU_Condition_pthread::Wait()
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This condition variable was not created by our library. Abort.
                return -1;
        }

        // Check to see if the mutex is initilized.
        if ((!this->condition_init) || (!this->mutex_init))
        {
                // We are not inited yet, return -2.
                return -2;
        }

        // Check to see if mutex is currently locked.
        if (this->Try_Lock_Mutex() != 0)
        {
                // Could not lock mutex abort.
                return -4;
        }

        // Call wait.
        this->rc_from_prevOP = pthread_cond_wait(&condition, &mutex);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // Unlock the mutex.
                this->Unlock_Mutex();

                // Send error.
                return -5;
        }

        // Unlock the mutex.
        this->Unlock_Mutex();

        // Exit function.
        return 0;
}

short TU_Condition_pthread::Timed_Wait(const unsigned long & seconds_to_wait)
{
        // Init timespec object.
        timespec time;

        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This condition variable was not created by our library. Abort.
                return -1;
        }

        // Check to see if the given amount of time to wait is less than or equal to zero.
        if (seconds_to_wait > 0)
        {
                // Check to see if the mutex is initilized.
                if ((!this->condition_init) || (!this->mutex_init))
                {
                        // We are not inited yet, return -2.
                        return -2;
                }

                // Check to see if mutex is currently locked.
                if (this->Try_Lock_Mutex() != 0)
                {
                        // Could not lock mutex abort.
                        return -4;
                }

                // Get the time.
                if (clock_gettime(CLOCK_REALTIME, &time) != 0)
                {
                        // Throw an error.
                        this->rc_from_prevOP = errno;

                        // Unlock the mutex.
                        this->Unlock_Mutex();

                        // Exit function.
                        return -6;
                }

                // Increment the timeout period.
                time.tv_sec += seconds_to_wait;

                // Call wait.
                this->rc_from_prevOP = pthread_cond_timedwait(&condition, &mutex, &time);

                // Check for error.
                if (this->rc_from_prevOP)
                {
                        // Check to see if we wokeup because of the timeout.
                        if (this->rc_from_prevOP == ETIMEDOUT)
                        {
                                // We hit the timeout.

                                // Unlock the mutex.
                                this->Unlock_Mutex();

                                // Exit function.
                                return 1;
                        }

                        // Unlock the mutex.
                        this->Unlock_Mutex();

                        // Otherwise send error.
                        return -5;
                }

                // Unlock the mutex.
                this->Unlock_Mutex();

                // Exit function.
                return 0;
        }

        /*
                Pretend that moron who called us specified that the
                amount of time to wait was one second and that the
                amount of time since that moron called us is
                0.999999999999~ seconds. :P
        */
        return 1;
}

short TU_Condition_pthread::Signal()
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This condition variable was not created by our library. Abort.
                return -1;
        }

        // Call signal.
        this->rc_from_prevOP = pthread_cond_signal(&condition);

        // Check for error.
        if (this->rc_from_prevOP)
        {
                // Send error.
                return -5;
        }

        // Exit function.
        return 0;
}

short TU_Condition_pthread::Set_Attribs(pthread_condattr_t * attr)
{
        // Check and see if the thread_lib used is ours.
        if ((this->lib.bIsPlugin != TU_LibID_pthreads.bIsPlugin) ||
	    (this->lib.Name == NULL) || (strcmp(this->lib.Name, TU_LibID_pthreads.Name) != 0))    // PThreads ID.
        {
                // This condition variable was not created by our library. Abort.
                return -1;
        }

        // Set the attribs object.
        if (attr != NULL)
        {
                // Copy the attrib object.
                this->cattribs = *attr;

                // Set the flags.
                this->cuser_attrib = true;
                this->cattrib_init = true;
        }
        else
        {
                // Destroy the object.
                this->rc_from_prevOP = pthread_condattr_destroy(&cattribs);

                // Set the flags.
                this->cuser_attrib = false;
                this->cattrib_init = true;
        }

        // Exit function.
        return 0;
}

TU_Thread * TU_Create_Pthread_Thread_Object()
{
        // Init vars.
        TU_Thread * result = NULL;

        // Allocate the thread object.
        result = new TU_Thread_pthread;

        // Return the new thread object.
        return result;
}

TU_Mutex * TU_Create_Pthread_Mutex_Object()
{
        // Init vars.
        TU_Mutex * result = NULL;

        // Allocate the mutex object.
        result = new TU_Mutex_pthread;

        // Return the new mutex object.
        return result;
}

TU_Condition * TU_Create_Pthread_Condition_Object()
{
        // Init vars.
        TU_Condition * result = NULL;

        // Allocate the condition object.
        result = new TU_Condition_pthread;

        // Return the new condition object.
        return result;
}

void TU_Destroy_Pthread_Thread_Object(TU_Thread ** thread)
{
	// Check for NULL pointer.
	if ((thread != NULL) && (*thread != NULL))
	{
		delete *thread;
		*thread = NULL;
	}

	// Exit function.
	return;
}

void TU_Destroy_Pthread_Mutex_Object(TU_Mutex ** mu)
{
	// Check for NULL pointer.
	if ((mu != NULL) && (*mu != NULL))
	{
		delete *mu;
		*mu = NULL;
	}

	// Exit function.
	return;
}

void TU_Destroy_Pthread_Condition_Object(TU_Condition ** cond)
{
	// Check for NULL pointer.
	if ((cond != NULL) && (*cond != NULL))
	{
		delete *cond;
		*cond = NULL;
	}

	// Exit function.
	return;
}

#endif // TW_PTHREADS_SUPPORT
