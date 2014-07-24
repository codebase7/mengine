/*!
    Multiverse Engine Project 19/4/2014 Common Thread_Utils_pthread_Plugin.cpp

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

// Only define things if pthread support is enabled.
#ifdef TW_PTHREADS_SUPPORT

// Define plugin functions if needed.
#ifdef MSYS_PLUGIN_BUILD

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
int TU_Get_Plugin_ABI_Version(const int & hostABIVersion)
{
        // Init vars.
        int result = TW_PLUGIN_ABI_VERSION;

        // Check to see if the hostABIVersion is not zero.
        if (hostABIVersion != 0)
        {
                // Check and see if we support the given ABI version.
                switch (hostABIVersion)
                {
                        // We only have a default here, because there are no older ABI versions (yet.)
                        default:    // Return our ABI version if we don't support the given ABI version.
                            break;
                };
        }

        // Return the result.
        return result;
}

TU_Thread * TU_Create_Thread_Object()
{
	return TU_Create_Pthread_Thread_Object();
}

TU_Mutex * TU_Create_Mutex_Object()
{
	return TU_Create_Pthread_Mutex_Object();
}

TU_Condition * TU_Create_Condition_Object()
{
	return TU_Create_Pthread_Condition_Object();
}

const TU_Library_Support_Status * TU_Get_Library_Support_Status_Plugin()
{
        // Return the library support status object.
        return &TU_LibSupport_pthreads;
}

void TU_Destroy_Thread_Object(TU_Thread ** thread)
{
	// Call plugin destruction function.
	TU_Destroy_Pthread_Thread_Object(thread);

	// Exit function.
	return;
}

void TU_Destroy_Mutex_Object(TU_Mutex ** mu)
{
	// Call plugin destruction function.
	TU_Destroy_Pthread_Mutex_Object(mu);

	// Exit function.
	return;
}

void TU_Destroy_Condition_Object(TU_Condition ** cond)
{
	// Call plugin destruction function.
	TU_Destroy_Pthread_Condition_Object(cond);

	// Exit function.
	return;
}

#ifdef __cplusplus
}		// End of extern C.
#endif

#endif // MSYS_PLUGIN_BUILD
#endif // TW_PTHREADS_SUPPORT
