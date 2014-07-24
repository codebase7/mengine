/*!
    Multiverse Engine Project 31/7/2013 Common Generic_Wrapper.h 

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

#ifndef GENERIC_WRAPPER_H
#define GENERIC_WRAPPER_H

// Include LibraryID_Struct.h.
#include "LibraryID_Struct.h"
#include <stddef.h> // Defines NULL.

	/*!
	 * 	class Common_Generic_Wrapper
	 * 
	 * 	This class is a generic class for creating a library wrapper.
	*/
	class Common_Generic_Wrapper
	{
		private:
		
		protected:
			// Define LibraryID struct.
			Common_LibraryID lib;		// Identifies the library in use.

		public:
			/*!
			 * 	const char * Common_Generic_Wrapper::Get_Library_Name()
			 * 
			 * 	This function returns a c-string with the name of the library in use.
			 */
			const char * Get_Library_Name();
			
			/*!
			 * 	bool Common_Generic_Wrapper::Is_Library_A_Plugin()
			 * 
			 * 	This function returns whether or not the library is a loaded plugin.
			 */
			bool Is_Library_A_Plugin();
	};
#endif

// End of Generic_Wrapper.h
