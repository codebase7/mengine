/*!
    Basic Test for thread_utils. 22/5/2013

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

#include "../Common/Src/Thread_Utils.h"
#include <iostream>

void *Test_Function_1(void * dummy)
{
        std::cout << "Test_Function.\n";
}

int main()
{
        // Init ret.
        short ret = 0;
	unsigned long int pid = 0;
	void * ret_from_thread = NULL;

        // Init thread object.
        Common::Thread_Utils::Thread * th = NULL;

        // Tell user we are creating the thread.
        std::cout << "Creating thread.\n";

        th = Common::Thread_Utils::Create_Thread(Common::Thread_Utils::pthreads);

        // Check for NULL.
        if (th == NULL)
        {
                // Error.
                std::cout << "An error occured while initing the thread, aborting.\n";
                return -1;
        }

        // Tell user we are initing the thread.
        std::cout << "Initing thread.\n";

        // Init the thread.
        ret = th->Create_Thread(Test_Function_1, NULL, &pid);

        if (ret != 0)
        {
                // Output error code.
                std::cout << "Error occured while initing the thread, thread library was: " << Common::Thread_Utils::Get_Library_Name(th->Get_Thread_Library()) << ".\n"; 
		std::cout << "Return code from Thread_Utils function was: " << ret << ".\n";
                std::cout << "Return code from library was: " << th->Get_Return_Code() << ".\n";
                std::cout << "Aborting.\n";
                return -1;
        }

        // Tell the user the pid.
        std::cout << "PID for new thread is: " << pid << ".\n";

        // Tell user we are waiting on the thread to finish.
        std::cout << "Waiting on all threads to finish.\n";

        // Join the thread.
        ret = th->Join_Thread(ret_from_thread);

        // Tell user return code from thread_utils.
        std::cout << "Return code from Join_Thread() for PID: " << pid << " was: ";
        std::cout << ret << ".\n";

	// Tell user the pointer address for the return value from the thread.
	std::cout << "Return value pointer address from thread is: " << ret_from_thread << ".\n";

        // Exit test.
        return 0;
}
