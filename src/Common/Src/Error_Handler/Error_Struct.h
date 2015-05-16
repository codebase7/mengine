/*!
    Multiverse Engine Project 29/12/2014 Common Error_Struct.h

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

// Include guard.
#ifndef ERROR_STRUCT_H
#define ERROR_STRUCT_H

// Enable C linkage if needed.
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

/*!
 * 	typedef struct Common_Error_Object_T
 *
 * 	Defines the data structure used by the Common Error Handler functions
 * 	to look up human-readable strings and their assoicated error codes.
 */
typedef struct Common_Error_Object_T {
	short errorCode;
	const char * error;
} Common_Error_Object;

// End C Linkage if needed.
#ifdef __cplusplus
}
#endif	// __cplusplus

#endif	// ERROR_STRUCT_H

// End of Error_Struct.h
