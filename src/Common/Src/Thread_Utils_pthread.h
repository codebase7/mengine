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
                                    thread_lib = pthreads;
                                    thread_init = false;
                                    attrib_init = false;
                                    user_attrib = false;
                            }
                            ~Thread_pthread()
                            {
                                    Destroy_Thread();
                            }

                            /*!
                                    short Common::Thread_Utils::Thread_pthread::Create_Thread()

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
                                    short Common::Thread_Utils::Thread_pthread::Join_Thread()

                                    This function is the real wrapper function for joining threads using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if the thread object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 if an error occurs in the library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Join_Thread(void * ret_from_thread = NULL);

                            // Below is library specific functions.

                            /*!
                                                short Common::Thread_Utils::Thread_pthread::Set_Attribs()

                                                This function allows setting the attributes object for the created thread.
                                                Note: The attributes object must be set before calling Create_Thread(). Setting the attributes
                                                afterward will have no effect on the running thread.

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
                            bool mutex_init;                // Used to tell if the mutex object has been inited by the user.
                            bool attrib_init;               // Used to tell if the attribs object has been inited by the user.
                            pthread_mutex_t mutex;          // The mutex itself.
                            pthread_mutexattr_t attribs;    // Attribs for the mutex.

                        protected:

                        public:
                            Mutex_pthread()
                            {
                                    Common::Thread_Utils::Mutex(pthreads);
                                    mutex_init = false;
                                    attrib_init = false;
                            }
                            ~Mutex_pthread()
                            {
                                    Destroy_Mutex();
                            }

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Init_Mutex()

                                    This function is the real wrapper function for creating mutexes using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -4 if the mutex was already inited. (Use Destroy_Mutex() first.)
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Init_Mutex(pthread_mutexattr_t * attr = NULL);

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Destroy_Mutex()

                                    This function is the real wrapper function for destroying mutexes using the pthreads library.

                                    Returns 0 on success.
                                    Returns -1 if mutex object was created for a different library.
                                    Returns -3 if the function is not implimented.
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Destroy_Mutex();

                            /*!
                                    short Common::Thread_Utils::Mutex_pthread::Lock_Mutex()

                                    This function is the real wrapper function for locking mutexes using the pthreads library.

                                    Note: This function will block the calling thread, until the mutex is locked by it.

                                    Returns 0 on success.
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
                                    Returns -3 if the function is not implimented.
                                    Returns -5 on error from library. (Return code will be stored in rc_from_prevOP.)
                            */
                            short Unlock_Mutex();
                };
        };
};

#endif
#endif

// End of Thread_Utils_pthread.h
