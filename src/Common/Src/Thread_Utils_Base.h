/*!
    Multiverse Engine Project 16/5/2013 Common Thread_Utils_Base.h
    
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

#ifndef THREAD_UTILS_BASE_H
#define THREAD_UTILS_BASE_H

namespace Common
{
        namespace Thread_Utils
        {
                /*!
                        enum supportedThreadLibs

                        Contains a list of supported threadding libraries.

                        The actual list used by the engine is generated at compile time.

                        Below is the entire list of supported libraries that could be avaiable.

                        Note: That some of the libraries below may not be avaiable to the engine
                        at run-time due to external reasons.
                        (Ex. The library is not supported on the given platform, was disabled at compile
                         time due to user override, etc.)

                        Note: If you add support for a library, you must define a unique id number for it.
                        (This is to prevent the enum'd list from generating errors due to an id mismatch.)
                        Also you must add a string for it in Get_Library_Name(). See below for description.
                */
                enum supportedThreadLibs {
#ifdef TW_PTHREADS_SUPPORT
                        pthreads = 1,
#endif
                        none = 0
                };

                /*!
                    const char * Get_Library_Name(const supportedThreadLibs & lib)

                    Returns a human readable string to identify a given supported library.

                    If no supported library is given it returns "none / unsupported".
                */
                const char * Get_Library_Name(const supportedThreadLibs & lib);

                /*!
                        class Common::Thread_Utils::Thread

                        This class is used to contain information about threads used with the thread wrapper.
                */
                class Thread
                {
                        private:

                        protected:
                            supportedThreadLibs thread_lib; // Thread library used to create thread.
                            int rc_from_prevOP;             // Return code from the actual thread library function.

                        public:
                            Thread()
                            {
                                    thread_lib = none;
                                    rc_from_prevOP = 0;
                            }
                            virtual ~Thread()
                            {

                            }

                            supportedThreadLibs Get_Thread_Library() const;
                            int Get_Return_Code() const;

                            virtual short Create_Thread(void *(*real_funct_ptr)(void*), void * function_args = NULL, unsigned long int * thread_id = NULL);

                            virtual short Detach_Thread();

                            virtual short Join_Thread(void * ret_from_thread = NULL);
                };

                /*!
                        class Common::Thread_Utils::Mutex

                        This class is a generic wrapper for mutexes.

                        Note: That this class does not contain the REAL mutex.
                        The mutex is defined in the wrapper, by deriving the actual class from this one.
                */
                class Mutex
                {
                        private:


                        protected:
                            supportedThreadLibs thread_lib; // Thread library used to create mutex.
                            int rc_from_prevOP;             // Return code from the actual thread library function.

                        public:
                            Mutex()
                            {
                                    thread_lib = none;
                                    rc_from_prevOP = 0;
                            }
                            virtual ~Mutex()
                            {
                                    thread_lib = none;
                            }

                            // Accessor function for the thread_lib.
                            supportedThreadLibs Get_Thread_Library() const;
                            int Get_Return_Code() const;

                            virtual short Init_Mutex();
                            virtual short Destroy_Mutex();
                            virtual short Lock_Mutex();
                            virtual short Try_Lock_Mutex();
                            virtual short Unlock_Mutex();
                };
        };
};

#endif

// End of Thread_Utils_Base.h
