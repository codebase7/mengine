/*!
    Multiverse Engine Project 08/8/2015 FileUtills FileUtills_Private_API.c

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

/* Internal includes. */
#include "FileUtills.h"
#include "FileUtills_Private_API.h"

int FileUtills_IsAbsolutePathReference(const char * path, const size_t pathSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* Result of this function. */

	/* Check for a valid arguments. */
	if ((path != NULL) && (pathSize > 0))
	{
		/* Check for a valid string. */
		if (path[0] == '/')	/* Posix style path. */
		{
			/* Valid Posix style path. */
			ret = FILEUTILLS_ERROR_PATH_IS_ABSOLUTE;
		}
		else
		{
			/* Check for a Windows / DOS style path. */
			if ((pathSize > 2) && (path[0] != '\0') && (path[1] == ':') && (path[2] == '\\'))
			{
				/* Valid Windows / DOS style path. */
				ret = FILEUTILLS_ERROR_PATH_IS_ABSOLUTE;
			}
			else
			{
				/* Path is not absolute. */
				ret = FILEUTILLS_ERROR_PATH_IS_RELATIVE;
			}
		}
	}
	else
	{
		/* Invalid pointer. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
		COMMON_LOG_VERBOSE("FileUtills_IsAbsolutePathReference(): ");
		COMMON_LOG_VERBOSE(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	/* Return the result. */
	return ret;
}

