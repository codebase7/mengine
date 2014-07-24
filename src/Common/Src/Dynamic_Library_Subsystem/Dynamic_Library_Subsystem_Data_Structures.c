/*!
    Multiverse Engine Project 01/4/2014 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Data_Structures.c

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

#include "Dynamic_Library_Subsystem.h"

#ifdef __cplusplus
// Define extern C.
extern "C" {
#endif
		Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * Common_Dynamic_Library_Subsystem_Create_Loaded_Dynamic_Library()
		{
			// Create the referece.
			Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * result = NULL;
			result = ((Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library*)(malloc(sizeof(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library))));

			// Check for a valid result.
			if (result != NULL)
			{
				// Initilize the vars.
				result->bIsLoaded = false;
				result->bLastCallEncounteredAnError = false;
				result->osSpecificPointerData = NULL;
				result->pathToLibrary = NULL;
			}

			// Return result.
			return result;
		}

		void Common_Dynamic_Library_Subsystem_Destroy_Loaded_Dynamic_Library(Common_Dynamic_Library_Subsystem_Loaded_Dynamic_Library * lib)
		{
			// Check for valid pointer.
			if (lib != NULL)
			{
				// Free the structure.
				free(lib);
			}

			// Exit function.
			return;
		}
#ifdef __cplusplus
}		// End of extern C.
#endif
