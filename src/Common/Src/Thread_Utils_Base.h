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
                // Below is a instance of the Library_Support_Status struct for the none / unsupported library.
                const Library_Support_Status LibSupport_none =
                {
                        &Common::Thread_Utils::supportedThreadLibs[0],           // idNum                                (ID of the thread library that this struct is for.)
                        false,          // bThreadsSupport                      (Do we support creating threads with this library.)
                        false,          // bJoinThreadSupport                   (Do we support joining threads with this library.)
                        false,          // bDetachThreadSupport                 (Do we support detaching threads with this library.)
                        false,          // bLibraryRequiresSpecificFunctionSig  (Do we require that the user use a specific function signature when creating threads?)
                        false,          // bMutexesSupport                      (Do we support creating mutexes with this library. Also basic lock and unlock support.)
                        false,          // bTryLockSupport                      (Do we support trying to lock mutexes with this library.)
                        false,          // bConditionVariableSupport            (Do we support condition variables with this library.)
                        false           // bConditionWaitTimeoutSupport         (Do we support a timeout limit when waiting on a condition variable with this library.)
                };

                /*!
                        class Common::Thread_Utils::Thread

                        This class is used to contain information about threads used with the thread wrapper.
                */
                class Thread : public Generic_Wrapper
                {
                        private:

                        protected:
                            int rc_from_prevOP;             // Return code from the actual thread library function.

                        public:
                            Thread()
                            {
                                    lib = Common::Thread_Utils::supportedThreadLibs[0];      // None / Unsupported.
                                    rc_from_prevOP = -3;
                            }
                            virtual ~Thread()
                            {

                            }

                            const Common::LibraryID & Get_Thread_Library() const;
                            int Get_Return_Code() const;

                            virtual short Create_Thread(void *(*real_funct_ptr)(void*), void * function_args = NULL, unsigned long int * thread_id = NULL);

                            virtual short Detach_Thread();

                            virtual short Join_Thread(void ** ret_from_thread = NULL);
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
                        /*
                            Common::LibraryID thread_lib;   // Thread library used to create mutex.
                            int rc_from_prevOP;             // Return code from the actual thread library function.
                            NOTE: The above is only here to show intent. A derived class should put the above in it's
                            private feild. (To allow other classes to deive from it.)
                        */

                        protected:

                        public:
                            /*
                            A basic constructor to show how the drived object should work. (I.e what vars to set at initilization.)
                            Mutex()
                            {
                                    lib = Common::Thread_Utils::supportedThreadLibs[0];      // None / Unsupported.
                                    rc_from_prevOP = -3;
                            }
                            */

                            virtual ~Mutex()
                            {

                            }

                            // Accessor function for the thread_lib.
                            virtual const Common::LibraryID & Get_Thread_Library() const = 0;  	// Used to return the external LibraryID for this object.
                            virtual int Get_Return_Code() const = 0;        // Used to get return code from the external library. (NOT Thread_Utils!)

                            virtual short Init_Mutex() = 0;
                            virtual short Destroy_Mutex() = 0;
                            virtual short Lock_Mutex() = 0;
                            virtual short Try_Lock_Mutex() = 0;
                            virtual short Unlock_Mutex() = 0;
                };

                /*!
                        class Common::Thread_Utils::Condition

                        This class is a generic wrapper for condition variables.

                        This class is also incomplete. (Ie. Virtual.) It must be derived to be used.
                        It is to be used as a base class for pointer dereferening.
                        (This is due to the condition class needing an internal mutex class to be usable.)

                        Note: That this class does not contain the REAL condition variable.
                        The condition variable is defined in the wrapper, by deriving the actual class from this one.
                */
                class Condition
                {
                        private:
                        /*
                            Common::LibraryID thread_lib;   // Thread library used to create mutex.
                            int rc_from_prevOP;             // Return code from the actual thread library function.
                            NOTE: The above is only here to show intent. A derived class should put the above in it's
                            private feild. (To allow other classes to deive from it.)
                        */

                        protected:

                        public:
                            /*
                            A basic constructor to show how the drived object should work. (I.e what vars to set at initilization.)
                            Condition()
                            {
                                    lib = Common::Thread_Utils::supportedThreadLibs[0];      // None / Unsupported.
                                    rc_from_prevOP = -3;
                            }
                            */

                            virtual ~Condition()
                            {

                            }

                            // Accessor function for the thread_lib.
                            virtual const Common::LibraryID & Get_Thread_Library() const = 0;   // Used to return the external LibraryID for this object.
                            virtual int Get_Return_Code() const = 0;        // Used to get return code from the external library. (NOT Thread_Utils!)

                            virtual short Init_Condition() = 0;
                            virtual short Destroy_Condition() = 0;
                            virtual short Wait() = 0;
                            virtual short Timed_Wait(const unsigned long & seconds_to_wait) = 0;
                            virtual short Signal() = 0;
                };
        };
};

#endif

// End of Thread_Utils_Base.h
