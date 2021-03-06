/*!
    Multiverse Engine Project 13/6/2015 Unit Tests Unit_Tests_Common_Error_Handler.cpp

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
#include "Unit_Tests_Common_Error_Handler.h"

/* External includes. */
#include <iostream>

void Common_Error_Log_Callback(const unsigned int logLevel, const char * errorMsg)
{
	// Print to std::cout.
	if (errorMsg != NULL)
	{
		std::cout << errorMsg;
		std::cout.flush();
	}

	// Exit function.
	return;
}
