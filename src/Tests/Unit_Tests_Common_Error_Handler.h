/*!
    Multiverse Engine Project 13/6/2015 Unit Tests Unit_Tests_Common_Error_Handler.h

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

/* Include guard. */
#ifndef UNIT_TESTS_COMMON_ERROR_HANDLER_H
#define UNIT_TESTS_COMMON_ERROR_HANDLER_H

/* Internal includes. */
#include "../Common/Src/Error_Handler/Common_Error_Handler.h"

/*!
 * 	void Common_Error_Log_Callback(const int channelID, const unsigned int logLevel, const char * errorMsg)
 * 
 * 	Callback function for Common::Register_Error_Log_Callback().
 * 	Displays given error message on standard output.
 */
void Common_Error_Log_Callback(const int channelID, const unsigned int logLevel, const char * errorMsg);

#endif	/* UNIT_TESTS_COMMON_ERROR_HANDLER_H */

/* End of Unit_Tests_Common_Error_Handler.h */
