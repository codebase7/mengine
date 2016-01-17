/*!
    Multiverse Engine Project 17/1/2016 Common Windows_Error_Translation_Table.c

    Copyright (C) 2016 Multiverse Engine Project

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

/* Internal includes. */
#include "Common_Error_Handler_Structures.h"
#include "Windows_Error_Translation_Table.h"

/* Include Extern C if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

const unsigned int Common_Get_Windows_Error_Translation_Table_API_Version()
{
	return COMMON_WINDOWS_ERROR_TRANSLATION_TABLE_API_VERSION;
}

const unsigned int Common_Get_Windows_Error_Translation_Table_Size()
{
	return (sizeof(Common_windowsErrorTranslationTable) / sizeof(Common_windowsErrorCodeTableEntry));
}

int Common_Translate_Windows_Error_Code_To_Common_Error_Code(const DWORD err)
{
	/* Init result. */
	int ret = COMMON_ERROR_SYSTEM_SPECIFIC;	/*
						 * Default is COMMON_ERROR_SYSTEM_SPECIFIC, as
						 * not all Windows error codes are / can be
						 * reperesented in the Common namespace
						 * error code table.
						 */
	unsigned int x = 0;		/* Loop counter */

	/* Run loop. */
	for (x = 0; ((x < Common_Get_Windows_Error_Translation_Table_Size()) &&
	     (ret == COMMON_ERROR_SYSTEM_SPECIFIC)); x++)
	{
		/* Check for a match in the error code translation table. */
		if (Common_windowsErrorTranslationTable[x].windowsErrorCode == err)
		{
			/* Match found, return the Common namespace error code. */
			ret = Common_windowsErrorTranslationTable[x].commonErrorCode;
		}
	}

	/* Return the result. */
	return ret;
}

/* Terminate C linkage if needed. */
#ifdef __cplusplus
}
#endif	/* __cplusplus */
