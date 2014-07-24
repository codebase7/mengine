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

namespace Common
{
	/*!
	 * 	struct Common::posixErrnoTableEntry
	 * 
	 * 	Used to construct the errno translation table.
	 * 	for POSIX compliant systems.
	 */
	struct posixErrnoTableEntry{
		int posixErrorNo;
		int commonErrorCode;
	};

	/*!
	 * 	const int posixErrorTranslationTableAPIVersion
	 * 
	 * 	Defines the API version of the posix errno to
	 * 	common namespace error code translation table.
	 * 
	 * 	If you change the table increment the version
	 * 	number.
	 */
	const int posixErrorTranslationTableAPIVersion = 1;
	
	/*!
	 * 	const Common::posixErrnoTableEntry Common::posixErrorTranslationTable[]
	 * 
	 * 	A table that contains (some) POSIX errno codes and their
	 * 	Common namespace error code equilivants.
	 * 
	 * 	Not all POSIX errno(s) are present in this table, as
	 * 	some POSIX errno(s) are specific to POSIX compliant
	 * 	systems. As such there is no Common namespace error
	 * 	code (beyond COMMON_SYSTEM_SPECIFIC) to represent them.
	 */
	const posixErrnoTableEntry posixErrorTranslationTable[] = {
		{EACCES, Common::COMMON_ACCESS_DENIED},
		{ENOENT, Common::FILEUTILLS_NON_EXISTANT},
		{EEXIST, Common::FILEUTILLS_EXISTANT},
		{EROFS, Common::FILEUTILLS_READ_ONLY},
		{EINVAL, Common::COMMON_INVALID_ARGUMENT},
		{ENAMETOOLONG, Common::FILEUTILLS_PATH_LENGTH_INVALID},
		{ENOTDIR, Common::FILEUTILLS_PATH_FILE_AS_DIRECTORY},
		{ENOMEM, Common::COMMON_MEMORY_ERROR},
		{EFAULT, Common::COMMON_INVALID_ARGUMENT},
		{ENOSPC, Common::FILEUTILLS_FILESYSTEM_FULL},
		{EDQUOT, Common::FILEUTILLS_FILESYSTEM_QUOTA_REACHED},
	};

	/*!
	 * 	unsigned int Common::Get_Posix_Error_Translation_Table_Size()
	 * 
	 * 	Returns the size of the Common::posixErrorTranslationTable
	 * 	array.
	 */
	unsigned int Get_Posix_Error_Translation_Table_Size();

	/*!
	 * 	int Common::Translate_Posix_Errno_To_Common_Error_Code(const int & err)
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

#endif	// POSIX_ERROR_TRANSLATION_TABLE_H

// End of Posix_Error_Translation_Table.h