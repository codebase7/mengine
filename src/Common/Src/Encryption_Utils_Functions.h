/*!
    Multiverse Engine Project 02/7/2013 Common Encryption_Utils_Functions.h
    
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

#ifndef ENCRYPTION_UTILS_FUNCTIONS_H
#define ENCRYPTION_UTILS_FUNCTIONS_H

// Internal includes.
#include "Encryption_Utils.h"

namespace Common
{
	namespace Encryption_Utils
	{       
		// Most of the below is shamelessly copied from Thread_Utils.
	  
		/*!
                        short Common::Encryption_Utils::Get_Number_of_Supported_Encryption_Libraries()

                        This function is used internaly to get the total number of supported encryption libraries at runtime.
                */
                short Get_Number_of_Supported_Encryption_Libraries();
	  
		/*!
                        Common::Encryption_Utils::CryptoEngine * Common::Encryption_Utils::Create_CryptoEngine(const Common::LibraryID & lib)

                        This function creates a CryptoEngine class object for use with the given encryption library.
                        Note: This function uses new to allocate the new object.
                        When you are done with it you must use delete to release it's memory.

                        Returns a pointer to the created CryptoEngine class object if successfull.
                        Otherwise returns NULL.
                */
                CryptoEngine * Create_CryptoEngine(const Common::LibraryID & lib);
		
		/*!
                        void Common::Encryption_Utils::Init_Library_Support_Status(Common::Encryption_Utils::Library_Support_Status * str)

                        This function initilizes a Library_Support_Status structure.

                        You should use this to initilize any structure you create at runtime. (It's the equilvant to the Class Constructor.)

                        Note To Library Maintainers: No staticly defined Library_Support_Status structure should need this function and should
                        be properly initilized at compile-time. (I.e bools and lib set. If there is no lib to set, you must set lib to NULL.)

                        This function is to be used by users of the library only. (Mainly for creating structures to pass to Select_Library().)
                */
		void Init_Library_Support_Status(Common::Encryption_Utils::Library_Support_Status * str);
	  
		/*!
                        const Common::Encryption_Utils::Library_Support_Status * Common::Encryption_Utils::Get_Library_Stats(const Common::LibraryID & lib)

                        This function returns the support status of a given library.
                        (I.e What functions are supported by Encryption_Utils.)
                */
		const Common::Encryption_Utils::Library_Support_Status * Get_Library_Stats(const Common::LibraryID & lib);
	  
		const Common::LibraryID & Select_Library(const Common::Encryption_Utils::Library_Support_Status & required_stats, const Common::LibraryID & skip_past_this_lib = Common::Encryption_Utils::supportedEncryptionLibs[0]); // supportedEncryptionLibs[0] = {0, "None / Unsupported"}
	};
};

#endif 