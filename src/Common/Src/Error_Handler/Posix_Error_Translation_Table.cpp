/*!
    Multiverse Engine Project 05/7/2014 Common Posix_Error_Translation_Table.cpp

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

// Internal includes.
#include "Common_Error_Handler_Structures.h"
#include "Posix_Error_Translation_Table.h"

unsigned int Common::Get_Posix_Error_Translation_Table_Size()
{
	return (sizeof(Common::posixErrorTranslationTable) / sizeof(Common::posixErrnoTableEntry));
}

int Common::Translate_Posix_Errno_To_Common_Error_Code(const int & err)
{
	// Init result.
	int ret = COMMON_SYSTEM_SPECIFIC;	/*
						 * Default is COMMON_SYSTEM_SPECIFIC, as
						 * not all POSIX errno(s) are / can be
						 * reperesented in the Common namespace
						 * error code table.
						 */

	// Run loop.
	for (unsigned int x = 0; ((x < Common::Get_Posix_Error_Translation_Table_Size()) &&
	     (ret == COMMON_SYSTEM_SPECIFIC)); x++)
	{
		// Check for a match in the error code translation table.
		if (Common::posixErrorTranslationTable[x].posixErrorNo == err)
		{
			// Match found, return the Common namespace error code.
			ret = Common::posixErrorTranslationTable[x].commonErrorCode;
		}
	}

	// Return the result.
	return ret;
}