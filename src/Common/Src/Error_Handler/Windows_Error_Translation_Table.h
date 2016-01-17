/*!
    Multiverse Engine Project 17/1/2016 Common Windows_Error_Translation_Table.h

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
#ifndef WINDOWS_ERROR_TRANSLATION_TABLE_H
#define WINDOWS_ERROR_TRANSLATION_TABLE_H

/* Include common error code definitions. */
#include "Common_Error_Handler_Error_Codes.h"

/* Include Windows headers. */
#include <WinError.h>
#include <IntSafe.h>

/* Enable C linkage if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
 * 	#define COMMON_WINDOWS_ERROR_TRANSLATION_TABLE_API_VERSION
 * 
 * 	Defines the API version of the Windows Error code to
 * 	common namespace error code translation table.
 * 
 * 	If you change the table increment the version
 * 	number.
 */
#define COMMON_WINDOWS_ERROR_TRANSLATION_TABLE_API_VERSION 1

/*!
 * 	typedef struct Common_windowsErrorCodeTableEntry_T Common_windowsErrorCodeTableEntry_T
 *
 * 	(C Binding.)
 *
 * 	Used to construct the error code translation table
 * 	for Windows systems.
 */
typedef struct Common_windowsErrorCodeTableEntry_T {
	int windowsErrorCode;
	int commonErrorCode;
} Common_windowsErrorCodeTableEntry;

/*!
 * 	const static Common_windowsErrorCodeTableEntry Common_windowsErrorTranslationTable[]
 * 
 * 	A table that contains (some) Windows error codes and their
 * 	Common namespace error code equilivants.
 * 
 * 	Not all Windows error codes are present in this table.
 */
const static Common_windowsErrorCodeTableEntry Common_windowsErrorTranslationTable[] = {
	{ERROR_SUCCESS, COMMON_ERROR_SUCCESS},
	{ERROR_ACCESS_DENIED, COMMON_ERROR_ACCESS_DENIED},
	{ERROR_PATH_NOT_FOUND, FILEUTILLS_ERROR_NON_EXISTANT},
	{ERROR_FILE_NOT_FOUND, FILEUTILLS_ERROR_NON_EXISTANT},
	{ERROR_INVALID_HANDLE, COMMON_ERROR_INVALID_ARGUMENT},
	{ERROR_TOO_MANY_OPEN_FILES, COMMON_ERROR_MEMORY_ERROR},
	{ERROR_ARENA_TRASHED, COMMON_ERROR_MEMORY_ERROR},
	{ERROR_NOT_ENOUGH_MEMORY, COMMON_ERROR_MEMORY_ERROR},
	{ERROR_INVALID_BLOCK, COMMON_ERROR_INVALID_ARGUMENT},
	{ERROR_INVALID_ACCESS, COMMON_ERROR_ACCESS_DENIED},
	{ERROR_OUTOFMEMORY, COMMON_ERROR_MEMORY_ERROR},
	{ERROR_INVALID_DRIVE, FILEUTILLS_ERROR_NON_EXISTANT},
	{ERROR_CURRENT_DIRECTORY, COMMON_ERROR_PEBKAC_INVALID_OPERATION_ORDER},
	{ERROR_NO_MORE_FILES, COMMON_ERROR_END_OF_DATA},
	{ERROR_WRITE_PROTECT, FILEUTILLS_ERROR_READ_ONLY},
	{ERROR_BAD_LENGTH, COMMON_ERROR_INVALID_ARGUMENT},
	{ERROR_BAD_COMMAND, COMMON_ERROR_INVALID_ARGUMENT},
	{ERROR_WRITE_FAULT, COMMON_ERROR_IO_ERROR},
	{ERROR_READ_FAULT, COMMON_ERROR_IO_ERROR},
	{ERROR_HANDLE_DISK_FULL, FILEUTILLS_ERROR_FILESYSTEM_FULL},
	{ERROR_NOT_SUPPORTED, COMMON_ERROR_HOST_NOT_SUPPORTED},
	{ERROR_FILE_EXISTS, FILEUTILLS_ERROR_EXISTANT},
	{ERROR_CANNOT_MAKE, COMMON_ERROR_IO_ERROR},
	{ERROR_BUFFER_OVERFLOW, COMMON_ERROR_INVALID_ARGUMENT},
	{ERROR_DISK_FULL, FILEUTILLS_ERROR_FILESYSTEM_FULL},
	{ERROR_BAD_DRIVER_LEVEL, COMMON_ERROR_HOST_NOT_SUPPORTED},
	{ERROR_CALL_NOT_IMPLEMENTED, COMMON_ERROR_HOST_NOT_SUPPORTED},
	{ERROR_INSUFFICIENT_BUFFER, COMMON_ERROR_INVALID_ARGUMENT},
};

/*!
 * 	const unsigned int Common_Get_Windows_Error_Translation_Table_API_Version()
 * 
 * 	Returns the API Version number of the Common_windowsErrorTranslationTable
 * 	array.
 */
const unsigned int Common_Get_Windows_Error_Translation_Table_API_Version();

/*!
 * 	const unsigned int Common_Get_Windows_Error_Translation_Table_Size()
 * 
 * 	Returns the size of the Common_windowsErrorTranslationTable
 * 	array.
 */
const unsigned int Common_Get_Windows_Error_Translation_Table_Size();

/*!
 * 	int Common_Translate_Windows_Error_Code_To_Common_Error_Code(const DWORD err)
 * 
 * 	Translates the given Windows error code to it's Common namespace
 * 	error code equilivant. (If applicable.)
 * 
 * 	@pram const DWORD err, the Windows error code to translate.
 * 
 * 	Returns the translated Common namespace error code if applicable.
 * 
 * 	Returns COMMON_SYSTEM_SPECIFIC if the given Windows error code does not have a
 * 	Common namespace error code translation.
 */
int Common_Translate_Windows_Error_Code_To_Common_Error_Code(const DWORD err);

/* End C Linkage if needed. */
#ifdef __cplusplus
}
#endif	/* __cplusplus */

/* Check for a C compiler. */
#ifdef __cplusplus
namespace Common
{
	/*!
	 * 	typedef Common_windowsErrorCodeTableEntry Common::windowsErrorCodeTableEntry
	 *
	 * 	(C++ Binding.)
	 *
	 * 	Used to construct the windows error code translation table.
	 * 	for Windows systems.
	 */
	typedef Common_windowsErrorCodeTableEntry windowsErrorCodeTableEntry;

	/*!
	 * 	const unsigned int Common::Get_Windows_Error_Translation_Table_API_Version()
	 * 
	 * 	Returns the API Version number of the Common_windowsErrorTranslationTable
	 * 	array.
	 */
	const unsigned int Get_Windows_Error_Translation_Table_API_Version();

	/*!
	 * 	const unsigned int Common::Get_Windows_Error_Translation_Table_Size()
	 *
	 * 	(C++ Binding)
	 *
	 * 	Returns the size of the Common::windowsErrorTranslationTable
	 * 	array.
	 */
	const unsigned int Get_Windows_Error_Translation_Table_Size();

	/*!
	 * 	int Common::Translate_Windows_Error_Code_To_Common_Error_Code(const DWORD & err)
	 *
	 * 	(C++ Binding)
	 *
	 * 	Translates the given Windows error code to it's Common namespace
	 * 	error code equilivant. (If applicable.)
	 * 
	 * 	@pram const DWORD & err, the Windows error code to translate.
	 * 
	 * 	Returns the translated Common namespace error code if applicable.
	 * 
	 * 	Returns COMMON_SYSTEM_SPECIFIC if the given Windows error code does not have a
	 * 	Common namespace error code translation.
	 */
	int Translate_Windows_Error_Code_To_Common_Error_Code(const DWORD & err);
};
#endif	/* __cplusplus */

#endif /* WINDOWS_ERROR_TRANSLATION_TABLE_H */

/* End of Windows_Error_Translation_Table.h. */
