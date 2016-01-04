/*!
    Multiverse Engine Project 05/7/2014 Common Posix_Error_Translation_Table.h

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

// Include guard.
#ifndef POSIX_ERROR_TRANSLATION_TABLE_H
#define POSIX_ERROR_TRANSLATION_TABLE_H

// Include POSIX errno header.
#include <errno.h>

// Enable C linkage if needed.
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus

/* Include common error code definitions. */
#include "Common_Error_Handler_Error_Codes.h"

/*!
 * 	#define COMMON_POSIX_ERROR_TRANSLATION_TABLE_API_VERSION
 * 
 * 	Defines the API version of the posix errno to
 * 	common namespace error code translation table.
 * 
 * 	If you change the table increment the version
 * 	number.
 */
#define COMMON_POSIX_ERROR_TRANSLATION_TABLE_API_VERSION 1

/*!
 * 	typedef struct Common_posixErrnoTableEntry_T Common_posixErrnoTableEntry
 *
 * 	(C Binding.)
 *
 * 	Used to construct the errno translation table.
 * 	for POSIX compliant systems.
 */
typedef struct Common_posixErrnoTableEntry_T {
	int posixErrorNo;
	int commonErrorCode;
} Common_posixErrnoTableEntry;

/*!
 * 	const static Common_posixErrnoTableEntry Common_posixErrorTranslationTable[]
 * 
 * 	A table that contains (some) POSIX errno codes and their
 * 	Common namespace error code equilivants.
 * 
 * 	Not all POSIX errno(s) are present in this table, as
 * 	some POSIX errno(s) are specific to POSIX compliant
 * 	systems. As such there is no Common namespace error
 * 	code (beyond COMMON_SYSTEM_SPECIFIC) to represent them.
 */
const static Common_posixErrnoTableEntry Common_posixErrorTranslationTable[] = {
	{EACCES, COMMON_ERROR_ACCESS_DENIED},
	{ENOENT, FILEUTILLS_ERROR_NON_EXISTANT},
	{EEXIST, FILEUTILLS_ERROR_EXISTANT},
	{EROFS, FILEUTILLS_ERROR_READ_ONLY},
	{EINVAL, COMMON_ERROR_INVALID_ARGUMENT},
	{ENAMETOOLONG, FILEUTILLS_ERROR_PATH_LENGTH_INVALID},
	{ENOTDIR, FILEUTILLS_ERROR_PATH_FILE_AS_DIRECTORY},
	{ENOMEM, COMMON_ERROR_MEMORY_ERROR},
	{EFAULT, COMMON_ERROR_INVALID_ARGUMENT},
	{ENOSPC, FILEUTILLS_ERROR_FILESYSTEM_FULL},
	{EDQUOT, FILEUTILLS_ERROR_FILESYSTEM_QUOTA_REACHED},
	{ENOTEMPTY, FILEUTILLS_ERROR_NON_EMPTY_DIRECTORY},
};

/*!
 * 	const unsigned int Common_Get_Posix_Error_Translation_Table_API_Version()
 * 
 * 	Returns the API Version number of the Common_posixErrorTranslationTable
 * 	array.
 */
const unsigned int Common_Get_Posix_Error_Translation_Table_API_Version();

/*!
 * 	const unsigned int Common_Get_Posix_Error_Translation_Table_Size()
 * 
 * 	Returns the size of the Common::posixErrorTranslationTable
 * 	array.
 */
const unsigned int Common_Get_Posix_Error_Translation_Table_Size();

/*!
 * 	int Common_Translate_Posix_Errno_To_Common_Error_Code(const int err)
 * 
 * 	Translates the given POSIX errno to it's Common namespace
 * 	error code equilivant. (If applicable.)
 * 
 * 	WARNING: Because the POSIX errno variable is global, you
 * 	should never call this function passing errno directly.
 * 
 * 	Instead, copy the errno to a temporary variable and then
 * 	pass the temporary variable to this function.
 * 
 * 	(Otherwise just calling this function could change errno
 * 	 before it is checked.)
 * 
 * 	@pram const int err, the POSIX error code to translate.
 * 
 * 	Returns the translated Common namespace error code if applicable.
 * 
 * 	Returns COMMON_SYSTEM_SPECIFIC if the POSIX errno does not have a
 * 	Common namespace error code translation.
 */
int Common_Translate_Posix_Errno_To_Common_Error_Code(const int err);

// End C Linkage if needed.
#ifdef __cplusplus
}
#endif	// __cplusplus

// Check for a C compiler.
#ifdef __cplusplus
namespace Common
{
	/*!
	 * 	typedef Common_posixErrnoTableEntry Common::posixErrnoTableEntry
	 *
	 * 	(C++ Binding.)
	 *
	 * 	Used to construct the errno translation table.
	 * 	for POSIX compliant systems.
	 */
	typedef Common_posixErrnoTableEntry posixErrnoTableEntry;

	/*!
	 * 	const unsigned int Common::Get_Posix_Error_Translation_Table_API_Version()
	 * 
	 * 	Returns the API Version number of the Common_posixErrorTranslationTable
	 * 	array.
	 */
	const unsigned int Get_Posix_Error_Translation_Table_API_Version();

	/*!
	 * 	const unsigned int Common::Get_Posix_Error_Translation_Table_Size()
	 *
	 * 	(C++ Binding)
	 *
	 * 	Returns the size of the Common::posixErrorTranslationTable
	 * 	array.
	 */
	const unsigned int Get_Posix_Error_Translation_Table_Size();

	/*!
	 * 	int Common::Translate_Posix_Errno_To_Common_Error_Code(const int & err)
	 *
	 * 	(C++ Binding)
	 *
	 * 	Translates the given POSIX errno to it's Common namespace
	 * 	error code equilivant. (If applicable.)
	 * 
	 * 	WARNING: Because the POSIX errno variable is global, you
	 * 	should never call this function passing errno directly.
	 * 
	 * 	Instead, copy the errno to a temporary variable and then
	 * 	pass the temporary variable to this function.
	 * 
	 * 	(Otherwise just calling this function could change errno
	 * 	 before it is checked.)
	 * 
	 * 	@pram const int & err, the POSIX error code to translate.
	 * 
	 * 	Returns the translated Common namespace error code if applicable.
	 * 
	 * 	Returns COMMON_SYSTEM_SPECIFIC if the POSIX errno does not have a
	 * 	Common namespace error code translation.
	 */
	int Translate_Posix_Errno_To_Common_Error_Code(const int & err);
};
#endif	// __cplusplus

#endif	// POSIX_ERROR_TRANSLATION_TABLE_H

// End of Posix_Error_Translation_Table.h