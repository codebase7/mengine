/*!
    Multiverse Engine Project 12/4/2015 Common MSYS_Mutexes_Thread_Utils_Plugin_Support.cpp

    Copyright (C) 2015 Multiverse Engine Project

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

// Internal includes.
#include "MSYS_Mutexes_Thread_Utils_Support.h"

// Define plugin functions if needed.
#ifdef MSYS_PLUGIN_BUILD

// Allow building with a C compiler.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
  
// Define Thread Utils plugin functions.
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

TU_Mutex * TU_Create_Mutex_Object()
{
	return TU_Create_MSYS_Mutex_Object();
}

const TU_Library_Support_Status * TU_Get_Library_Support_Status_Plugin()
{
        // Return the library support status object.
        return &TU_LibSupport_MSYS_Mutex_Support;
}

void TU_Destroy_Mutex_Object(TU_Mutex ** mu)
{
	// Call plugin destruction function.
	TU_Destroy_MSYS_Mutex_Object(mu);

	// Exit function.
	return;
}

#ifdef __cplusplus
}		// End of extern C.
#endif	// __cplusplus

#endif // MSYS_PLUGIN_BUILD

// End of MSYS_Mutexes_Thread_Utils_Plugin_Support.cpp
