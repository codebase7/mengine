/*!
    Multiverse Engine Project 17/12/2015 FileUtills FileUtills_CPP.h

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
#ifndef FILEUTILLS_CPP_H
#define FILEUTILLS_CPP_H

/* Check for defined FILEUTILLS_H. */
#ifndef FILEUTILLS_H
#error "This header should not be included directly. It will be included automaticly by FileUtills.h if the compiler is a C++ compiler."
#endif	/* FILEUTILLS_H */

/* Check for a C++ compiler. */
#ifdef __cplusplus

namespace FileUtills {
	/*!
	 * 	int FileUtills::GetUserProfileDirectoryPath(std::string & path)
	 *
	 *	This function is a wrapper around FileUtills_GetUserProfileDirectoryPath() that takes the
	 *	string returned from FileUtills_GetUserProfileDirectoryPath() and turns it into an std::string object.
	 *
	 * 	Fetches the user's profile directory from the environment, and stores
	 * 	it in the given path argument.
	 *
	 * 	If the function fails for any reason, the arguments will NOT be altered,
	 * 	and the appropriate error will be returned to the caller.
	 *
	 *	Returns COMMON_ERROR_SUCCESS if successful.
	 *	Otherwise returns all error codes from FileUtills_GetUserProfileDirectoryPath(). See documentation
	 *	for the error code descriptions.
	 */
	int GetUserProfileDirectoryPath(std::string & path);

	/*!
	 * 	int FileUtills::GetCurrentWorkingDirectoryPath(std::string & path)
	 *
	 *	This function is a wrapper around FileUtills_GetCurrentWorkingDirectoryPath() that takes the
	 *	string returned from FileUtills_GetCurrentWorkingDirectoryPath() and turns it into an std::string object.
	 *
	 * 	Fetches the current working directory from the environment, and stores
	 * 	it in the given path argument.
	 *
	 * 	If the function fails for any reason, the arguments will NOT be altered,
	 * 	and the appropriate error will be returned to the caller.
	 *
	 *	Returns COMMON_ERROR_SUCCESS if successful.
	 *	Otherwise returns all error codes from FileUtills_GetCurrentWorkingDirectoryPath(). See documentation
	 *	for the error code descriptions.
	 */
	int GetCurrentWorkingDirectoryPath(std::string & path);

	/*!
	 * 	int FileUtills::GetExecDirectory(std::string & path)
	 *
	 *	This function is a wrapper around FileUtills_GetExecDirectory() that takes the
	 *	string returned from FileUtills_GetExecDirectory() and turns it into an std::string object.
	 *
	 * 	Fetches the engine's executable directory from the environment, and stores
	 * 	it in the given path argument.
	 *
	 * 	If the function fails for any reason, the arguments will NOT be altered,
	 * 	and the appropriate error will be returned to the caller.
	 *
	 *	Returns COMMON_ERROR_SUCCESS if successful.
	 *	Otherwise returns all error codes from FileUtills_GetExecDirectory(). See documentation
	 *	for the error code descriptions.
	 */
	int GetExecDirectory(std::string & path);

	/*!
	 *	int FileUtills_ResolvePath(const std::string path, std::string & resolvedPath, const bool disableSymLinkResolution)
	 *
	 *	Checks the path given, and converts it to a absolute path.
	 *
	 *	This function is a wrapper to FileUtills_ResolvePath(), and returns all of it's error codes.
	 *
	 *	Setting disableSymLinkResolution to true will disable resolving any symbolic link(s) if a
	 *	symbolic link is encountered while resolving the given path(s). Setting
	 *	disableSymLinkResolution to false will make this function resolve any
	 *	symbolic link(s) that are encountered while resolving the given path(s).
	 *
	 *	Returns COMMON_ERROR_SUCCESS if successful, retStr and retStrSize will be altered in this
	 *	case.
	 *
	 *	Otherwise returns all error codes from FileUtills_ResolvePath(). See documentation
	 *	for the error code descriptions.
	 */
	int ResolvePath(const std::string path, std::string & resolvedPath, const bool disableSymLinkResolution);
}	/* End of FileUtills namespace. */

#endif	/* __cplusplus */

#endif	/* FILEUTILLS_CPP_H */

/* End of FileUtills_CPP.h. */
