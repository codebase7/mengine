/*!
    Multiverse Engine Project 23/1/2016 Dynamic_Library_Subsystem Dynamic_Library_Subsystem_Syscall.h

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

/* Include guard. */
#ifndef MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_SYSCALL_H
#define MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_SYSCALL_H

/* External includes. */
#include <stddef.h>

/*!
	int Common_Dynamic_Library_Subsystem_Load_Library_Syscall(	const char * pathToLibrary,
																const size_t pathToLibraryLength,
																void ** osSpecificPointerData)

	Issues the system call that performs the actual loading of a library.

	NOTE: This function should NOT be called directly by anything except
	Common_Dynamic_Library_Subsystem_Load_Library(). Use that function
	if you want to load a given library.

	Any reference / data structure returned by the host system call that is required to
	reference the loaded library in the future will be pointed to by osSpecificPointerData.
	(Memory allocation may be performed here, but any allocation must be deallocated by the
	 Unload Library syscall function if an allocation is performed.)

	This function also translates any error code given by the host system into a
	Common Namespace Error Code before returning it.

	---General result code list---
	Note: Due to translation of host error codes, ANY Common Namespace Error Code
	is possible here:
		Returns COMMON_ERROR_SUCCESS if the library was loaded successfully.

		Returns COMMON_ERROR_INVALID_ARGUMENT if one of the given pointers is NULL,
		or the length argument is less than or equal to zero.

		Otherwise returns the appropriate error code.

	No-alteration clause:
		- In case of error, this function will not modify it's arguments.
 */
int Common_Dynamic_Library_Subsystem_Load_Library_Syscall(const char * pathToLibrary, const size_t pathToLibraryLength, void ** osSpecificPointerData);

/*!
	int Common_Dynamic_Library_Subsystem_Unload_Library_Syscall(void * osData)

	Issues the system call that performs the actual unloading of a library.

	NOTE: This function should NOT be called directly by anything except
	Common_Dynamic_Library_Subsystem_Unload_Library(). Use that function
	if you want to unload a given library.

	Any allocation made by the Load Library syscall must be deallocated by this function,
	if an allocation was performed.

	This function also translates any error code given by the host system into a
	Common Namespace Error Code before returning it.

	---General result code list---
	Note: Due to translation of host error codes, ANY Common Namespace Error Code
	is possible here:
		Returns COMMON_ERROR_SUCCESS if the library was unloaded successfully.

		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.

		Otherwise returns the appropriate error code.

	No-alteration clause:
		- In case of error, this function will not modify it's arguments.
 */
int Common_Dynamic_Library_Subsystem_Unload_Library_Syscall(void * osData);

/*!
	int Common_Dynamic_Library_Subsystem_Get_Symbol_Syscall(void * osData,
															const char * symbolName,
															const size_t symbolNameLength,
															void ** retSym)

	Issues the system call that performs the actual lookup of a given symbol in a given library.

	NOTE: This function should NOT be called directly by anything except
	Common_Dynamic_Library_Subsystem_Get_Symbol(). Use that function
	if you want to lookup a given symbol.

	This function also translates any error code given by the host system into a
	Common Namespace Error Code before returning it.

	---General result code list---
	Note: Due to translation of host error codes, ANY Common Namespace Error Code
	is possible here:
		Returns COMMON_ERROR_SUCCESS if the given symbol was found successfully.
		(The given symbol will be pointed to by retSym.)

		Returns COMMON_ERROR_INVALID_ARGUMENT if one of the given pointers is NULL,
		or the length argument is less than or equal to zero.

		Otherwise returns the appropriate error code.

	No-alteration clause:
		- In case of error, this function will not modify it's arguments.
 */
int Common_Dynamic_Library_Subsystem_Get_Symbol_Syscall(void * osData, const char * symbolName, const size_t symbolNameLength, void ** retSym);

#endif /* MSYS_DYNAMIC_LIBRARY_SUBSYSTEM_SYSCALL_H */

/* End of Dynamic_Library_Subsystem_Syscall.h. */
