/*!
    Multiverse Engine Project 02/7/2013 Common Encryption_Utils_Functions.cpp
    
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

#include "Encryption_Utils.h"

short Common::Encryption_Utils::Get_Number_of_Supported_Encryption_Libraries()
{
	/*
            Calculate size of array. (sizeof entire array / sizeof single element in array.)
            (Note: This works as the array is global to the namespace and therefore does not need to be passed to us.)
        */
        short ret = sizeof(Common::Encryption_Utils::supportedEncryptionLibs) / sizeof(Common::Encryption_Utils::supportedEncryptionLibs[0]);

        // Return result.
        return ret;
}

Common::Encryption_Utils::CryptoEngine * Common::Encryption_Utils::Create_CryptoEngine(const Common::LibraryID & lib)
{
	// Exit function.
	return NULL;
}

void Common::Encryption_Utils::Init_Library_Support_Status(Common::Encryption_Utils::Library_Support_Status * str)
{
	// Exit function.
	return;
}

const Common::Encryption_Utils::Library_Support_Status * Common::Encryption_Utils::Get_Library_Stats(const Common::LibraryID & lib)
{
	// Exit function.
	return NULL;
}

const Common::LibraryID & Select_Library(const Common::Encryption_Utils::Library_Support_Status & required_stats, const Common::LibraryID & skip_past_this_lib)
{
	// Exit function.
	return Common::Encryption_Utils::supportedEncryptionLibs[0]; 	// supportedEncryptionLibs[0] = {0, "None / Unsupported"}
}
