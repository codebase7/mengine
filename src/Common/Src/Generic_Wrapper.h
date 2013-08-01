/*!
    Multiverse Engine Project 31/7/2013 Common Generic_Wrapper.h 

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

#include "LibraryID_Struct.h"

namespace Common
{
	/*!
	 * 	class Common::Generic_Wrapper
	 * 
	 * 	This class is a generic class for creating a library wrapper.
	*/
	class Generic_Wrapper
	{
		private:
		
		protected:
			// Define LibraryID struct.
			Common::LibraryID lib;		// Identifies the library in use.
			
		public:
			/*!
			 * 	const char * Common::Generic_Wrapper::Get_Library_Name()
			 * 
			 * 	This function returns a c-string with the name of the library in use.
			 */
			const char * Get_Library_Name();
			
			/*!
			 * 	short Common::Generic_Wrapper::Get_Library_ID()
			 * 
			 * 	This function returns a short containing the library's ID number.
			 * 
			 * 	(Note: Library ID numbers are specific to the wrapper in use, and may not be
			 * 	the same in all instances.)
			 */
			short Get_Library_ID();
	};
};
