/*!
	Multiverse Engine Project 06/7/2015 FileUtills FileUtills_Private_API_Windows_Syscall.h

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
#ifndef FILEUTILLS_PRIVATE_API_WINDOWS_SYSCALL_H
#define FILEUTILLS_PRIVATE_API_WINDOWS_SYSCALL_H

/* Define CSIDL values. */
#define FILEUTILLS_USER_PROFILE_ID CSIDL_PROFILE
#define FILEUTILLS_USER_DOCUMENTS_ID CSIDL_PERSONAL
#define FILEUTILLS_APPDATA_ID CSIDL_LOCAL_APPDATA

/* Define MSYS_MAX_SYMLINK_DEPTH.
	MSDN Says the max depth is 31.
	https://msdn.microsoft.com/en-us/library/windows/desktop/aa365460%28v=vs.85%29.aspx
*/
#define MSYS_MAX_SYMLINK_DEPTH 31

/* Define extended length prefix for filesystem calls to use Unicode mode. */
#define MSYS_FILEUTILLS_WINDOWS_SYSCALL_EXTENDED_LENGTH_PREFIX "\\?\"

#endif	/* FILEUTILLS_PRIVATE_API_WINDOWS_SYSCALL_H */

/* End of FileUtills_Private_API_Windows_Syscall.h. */
