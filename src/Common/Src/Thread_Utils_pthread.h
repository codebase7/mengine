/*!
    Multiverse Engine Project 16/5/2013 Common Thread_Utils_pthread.h

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

// Only define things if the pthread support is enabled.
#ifdef TW_PTHREADS_SUPPORT

// Include guard.
#ifndef THREAD_UTILS_PTHREAD_H
#define THREAD_UTILS_PTHREAD_H

// External includes.
#include <pthread.h>
#include <cerrno>

namespace Common
{
        namespace Thread_Utils
        {
                // PThreads Library_Support_Status structure.
                const Library_Support_Status LibSupport_pthreads =
                {
                        &Common::Thread_Utils::supportedThreadLibs[1],          // {1, "Pthreads"}  (ID of the thread library that this struct is for.)
                        true,                                                   // bThreadsSupport  (Do we support creating threads with this library.)
                        true,                                                   // bJoinThreadSupport   (Do we support joining threads with this library.)
                        true,                                                   // bDetachThreadSupport (Do we support detaching threads with this library.)
                        true,                                                   // bLibraryRequiresSpecificFunctionSig  (Do we require that the user use a specific function signature when creating threads?)
                        true,                                                   // bMutexesSupport  (Do we support creating mutexes with this library. Also basic lock and unlock support.)
                        true,                                                   // bTryLockSupport  (Do we support trying to lock mutexes with this library.)
                        true,                                                   // bConditionVariableSupport  (Do we support condition variables with this library.)
                        true                                                    // bConditionWaitTimeoutSupport  (Do we support a timeout limit when waiting on a condition variable with this library.)
                };

                // Derived types.
                class Thread_pthread : public Thread
                {
                        private:
                            bool thread_init;               // Used to tell if the user has spawned a thread with this object.
                            bool attrib_init;               // Used to tell if the attribs object has been inited.
                            bool user_attrib;		        // Used to tell if the user has specified an attributes object manually.
                            pthread_t pid;                  // Used to store the thread's ID.
                            pthread_attr_t attribs;         // The thread attribs object.

                        protected:

                        public:
                            Thread_pthread()
                            {
                                    lib = Common::Thread_Utils::supportedThreadLibs[1];      // {1, "Pthreads"}
                                    thread_init = false;
                                    attrib_init = false;
                                    user_attrib = false;
                            }
                            ~Thread_pthread()
                            {
                                    Destroy_Thread();
                            }

                            /*!
                                    short Common::Thread_Utils::Thread_pthread::Create_Thread(void *(*real_funct_ptr)(void*), void * function_args = NULL, unsigned long int * thread_id = NULL)

                                    This function is the real wrapper function for creating threads using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if the thread object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the thread has already been created. (Use Destroy_Thread() first.)
                                    Returns -5 if an error occurs in the library. (Return code will be stored in rc_from_prevOP.)
                            */
                            virtual short Create_Thread(void *(*real_funct_ptr)(void*), void * function_args = NULL, unsigned long int * thread_id = NULL);

                            /*!
                                    short Common::Thread_Utils::Thread_pthread::Destroy_Thread()

                                    This function is the real wrapper function for destroying threads using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if the thread object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 if an error occurs in the library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Destroy_Thread();

                            /*!
                                    short Common::Thread_Utils::Thread_pthread::Detach_Thread()

                                    This function is the real wrapper function for detaching threads using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if the thread object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 if an error occurs in the library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Detach_Thread();

                            /*!
                                    short Common::Thread_Utils::Thread_pthread::Join_Thread(void ** ret_from_thread = NULL)

                                    This function is the real wrapper function for joining threads using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if the thread object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 if an error occurs in the library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Join_Thread(void ** ret_from_thread = NULL);

                            // Below is library specific functions.

                            /*!
                                    short Common::Thread_Utils::Thread_pthread::Set_Attribs(pthread_attr_t * attr = NULL)

                                    This function allows setting the attributes object for the created thread.
                                    Note: The attributes object must be set before calling Create_Thread(). Setting the attributes
                                    afterward will have no effect on the running thread.

                                    By default this deletes the given attribs object (if any) and makes Create_Thread()
                                    use the defaults.

                                    Returns 0 on success.
                                    Returns -1 if the thread object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 if an error occurs in the library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Set_Attribs(pthread_attr_t * attr = NULL);
                };

                class Mutex_pthread : public Mutex
                {
                        private:
                            Common::LibraryID thread_lib;   // Thread library used to create mutex.
                            int rc_from_prevOP;             // Return code from the actual thread library function.

                        protected:
                            bool mutex_init;                // Used to tell if the mutex object has been inited by the user.
                            bool attrib_init;               // Used to tell if the attribs object has been inited by the user.
                            bool user_attrib;		        // Used to tell if the user has specified an attributes object manually.
                            pthread_mutex_t mutex;          // The mutex itself.
                            pthread_mutexattr_t attribs;    // Attribs for the mutex.

                        public:
                            Mutex_pthread()
                            {
                                    thread_lib = Common::Thread_Utils::supportedThreadLibs[1];      // {1, "Pthreads"}
                                    rc_from_prevOP = 0;
                                    mutex_init = false;
                                    attrib_init = false;
                                    user_attrib = false;
                            }
                            ~Mutex_pthread()
                            {
                                    Destroy_Mutex();
                            }

                            // Accessor function for the thread_lib.
                            virtual const Common::LibraryID & Get_Thread_Library() const;   // Used to return the external LibraryID for this object.
                            virtual int Get_Return_Code() const;        // Used to get return code from the external library. (NOT Thread_Utils!)

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Init_Mutex()

                                    This function is the real wrapper function for creating mutexes using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the mutex was already inited. (Use Destroy_Mutex() first.)
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Init_Mutex();

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Destroy_Mutex()

                                    This function is the real wrapper function for destroying mutexes using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the mutex object is not inited. (I.e you have not used it yet.)
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Destroy_Mutex();

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Lock_Mutex()

                                    This function is the real wrapper function for locking mutexes using the pthreads library.

                                    Note: This function will block the calling thread, until the mutex is locked by it.

                                    Returns 0 on success. (Or if the mutex is already held by the current thread. In this case Get_Return_Code() will return EDEADLK.)
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Lock_Mutex();

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Try_Lock_Mutex()

                                    This function is the real wrapper function for trying to lock a mutex using the pthreads library.

                                    Note: This function will NOT block the calling thread, if the mutex is already locked it returns 1.

                                    Returns 0 on success.
                                    Returns 1 if the mutex is locked already.
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Try_Lock_Mutex();

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Unlock_Mutex()

                                    This function is the real wrapper function for unlocking mutexes using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -2 if unlocking fails due to the mutex not being held by the current thread.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Unlock_Mutex();

                            // BELOW HERE IS LIBRARY SPECIFIC FUNCTIONS.

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Set_Attribs(pthread_mutexattr_t * attr)

                                    This function allows you to set the pthread_mutexattr_t object used to init the mutex.

                                    Returns 0 on success.
                                    Returns -1 if a different threading library was used to create this mutex object.
                            */
                            short Set_Attribs(pthread_mutexattr_t * attr = NULL);

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Destroy_Mutex_Only()

                                    This function only destroys the mutex itself. Not the attribs object.

                                    Returns 0 on success.
                                    Returns -1 if the mutex object was created for a different library.
                                    Returns -5 if the external library returns an error. (Can be fetched by calling Get_Return_Code().)
                            */
                            short Destroy_Mutex_Only();
                };

                class Condition_pthread : public Condition, public Mutex_pthread
                {
                        private:
                            Common::LibraryID thread_lib;   // Thread library used to create mutex.
                            int rc_from_prevOP;             // Return code from the actual thread library function.
                            bool condition_init;            // Used to tell if the condition object has been inited by the user.
                            bool cattrib_init;              // Used to tell if the condition attribs object has been inited by the user.
                            bool cuser_attrib;              // Used to tell if the user has specified an condition attributes object manually.

                            pthread_cond_t condition;       // The condtion variable itself.
                            pthread_condattr_t cattribs;    // Attribs for the condtion variable.


                        protected:

                        public:
                            Condition_pthread()
                            {
                                    thread_lib = Common::Thread_Utils::supportedThreadLibs[1];      // {1, "Pthreads"}
                                    rc_from_prevOP = 0;
                                    condition_init = false;
                                    attrib_init = false;
                                    user_attrib = false;
                                    cattrib_init = false;
                                    cuser_attrib = false;
                            }
                            ~Condition_pthread()
                            {

                            }

                            // Accessor function for the thread_lib.
                            virtual const Common::LibraryID & Get_Thread_Library() const;   // Used to return the external LibraryID for this object.
                            virtual int Get_Return_Code() const;        // Used to get return code from the external library. (NOT Thread_Utils!)

                            /*!
                                    short Common::Thread_Utils::Condition_pthread::Init_Condition()

                                    This function is the real wrapper function for creating condition variables using the pthreads library.

                                    NOTE: You MUST call Init_Mutex() before the condition object can be used.
                                    Otherwise, Wait() will throw an error.

                                    Returns 0 on success.
                                    Returns -1 if condition object was created for a different library.
                                    Returns -2 if the internal mutex object was not inited correctly. (You can fetch the return code from pthreads by calling Get_Return_Code().)
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the condition was already inited. (Use Destroy_Condition() first.)
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Init_Condition();

                            /*!
                                    short Common::Thread_Utils::Condition_pthread::Destroy_Condition()

                                    This function is the real wrapper function for destroying condition variables using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if condition object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the condition object is not inited. (I.e you have not used it yet.)
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Destroy_Condition();

                            /*!
                                    short Common::Thread_Utils::Condition_pthread::Wait()

                                    This function will block the calling thread until a signal is received to continue.

                                    Note: This function uses Try_Lock_Mutex() to lock the internal mutex. If the lock cannot
                                    be obtained imeadently this function will NOT block the calling thread.
                                    This is to prevent an excessively long block due to not being able to lock the internal mutex
                                    object. Thus preventing the calling thread from recicveing the signal to continue, which would
                                    result in the thread never continuing. I.e A deadlocked thread.

                                    Returns 0 on success.
                                    Returns -1 if condition object was created for a different library.
                                    Returns -2 if the object is not inited.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the internal mutex object cannot be locked. (Error from library can be fetched by calling Get_Return_Code().)
                                    Returns -5 on error from library. (Error from library can be fetched by calling Get_Return_Code().)
                            */
                            short Wait();

                            /*!
                                    short Common::Thread_Utils::Condition_pthread::Timed_Wait(const unsigned long & seconds_to_wait)

                                    This function will block the calling thread until a signal is received to continue OR the requested amount of time
                                    in seconds has passed.

                                    Note: This function uses Try_Lock_Mutex() to lock the internal mutex. If the lock cannot
                                    be obtained imeadently this function will NOT block the calling thread.
                                    This is to prevent an excessively long block due to not being able to lock the internal mutex
                                    object. Thus preventing the calling thread from recicveing the signal to continue, which would
                                    result in the thread never continuing. I.e A deadlocked thread.

                                    Returns 0 on success.
                                    Returns 1 if the timeout was reached. (I.e the given amount of time to wait has passed, no signal to continue was recicvied.)
                                    Returns -1 if condition object was created for a different library.
                                    Returns -2 if the object is not inited.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the internal mutex object cannot be locked. (Error from library can be fetched by calling Get_Return_Code().)
                                    Returns -5 on error from library. (Error from library can be fetched by calling Get_Return_Code().)
                                    Returns -6 if the current time cannot be retrived. (The error code from the system can be retrived by calling Get_Return_Code().)
                            */
                            short Timed_Wait(const unsigned long & seconds_to_wait);

                            /*!
                                    short Common::Thread_Utils::Condition_pthread::Signal()

                                    This function tells a thread waiting on this condition object to continue.

                                    Returns 0 on success.
                                    Returns -1 if condition object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 on error from library. (Error from library can be fetched by calling Get_Return_Code().)
                            */
                            short Signal();

                            // BELOW HERE IS LIBRARY SPECIFIC FUNCTIONS.

                            /*!
                                    short Common::Thread_Utils::Condition_pthread::Set_Attribs(pthread_condattr_t * attr)

                                    This function allows you to set the pthread_condattr_t object used to init the condition variable.

                                    Returns 0 on success.
                                    Returns -1 if a different threading library was used to create this condition object.
                            */
                            short Set_Attribs(pthread_condattr_t * attr = NULL);
                };
        };
};

#endif
#endif

// End of Thread_Utils_pthread.h
