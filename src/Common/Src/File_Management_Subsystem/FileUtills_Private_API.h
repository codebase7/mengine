/*!
    Multiverse Engine Project 04/12/2011 FileUtills FileUtills_Private_API.h

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

/* Include guard. */
#ifndef FILEUTILLS_PRIVATE_API_H
#define FILEUTILLS_PRIVATE_API_H

/* External includes. */
/* Define extern C. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef __cplusplus
} /* End of extern C. */
#endif	/* __cplusplus */

#ifdef __cplusplus
/* C++ specific external includes. */
#include <cstring>
#endif	/* __cplusplus */

/* End of external includes. */

/* Define extern C. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Define the internal MSYS_FILESIZE_PRIV structure. */
typedef struct MSYS_FILESIZE_PRIV {
enum MSYS_FILESIZE_TYPES type;			/* What type of struct it is. (Windows or POSIX. )*/
#ifdef _MSC_VER
		__int64	length;		/* Length of the file. */
#else
		off_t	length;		/* Length of the file. */
#endif	/* _MSC_VER */
} MSYS_FILESIZE_PRIV_T;

#ifdef __cplusplus
} /* End of extern C. */
#endif	/* __cplusplus */


/* Only define the namespace if using a C++ compiler. */
#ifdef __cplusplus

// Namespace definition.
namespace FileUtills{

/*!
 * 	int FileUtills::IsAbsolutePathReference(const char * path, const size_t pathSize)
 *
 * 	This function checks the given path to see if it's beginning is in
 * 	absolute path reference form.
 *
 * 	Absolute path reference form is defined as:
 * 		- On DOS / Windows systems: Having the drive letter the colon
 * 		  and directory seperator as the first three (3) characters in
 * 		  the given path. E.x. "C:\Windows" or "D:\Setup.exe"
 *
 * 		- On all other systems: Having the directory seperator as the
 * 		  first character in the given path. E.x. "/usr" or "/home"
 * 		  or "/foo" or "/bar"
 *
 * 	If the given path is in absolute path reference form as defined above,
 * 	then the function will return FILEUTILLS_ERROR_PATH_IS_ABSOLUTE.
 *
 * 	If the given path is NOT in absolute path reference form as defined
 * 	above, then this function will return FILEUTILLS_ERROR_PATH_IS_RELATIVE.
 *
 * 	If any error occurs then, this function will return the appropriate error code.
 */
int IsAbsolutePathReference(const char * path, const size_t pathSize);

/*!
 * 	int FileUtills::IsAbsolutePathReference(const char * path, const size_t pathSize, char ** absRef, size_t * absRefSize)
 *
 * 	This function checks the given path to see if it's beginning is in
 * 	absolute path reference form. This version also copies the found
 * 	absolute path reference to the given absRef argument if applicable.
 *
 * 	Note: This function expects absRefSize to point to a valid size_t
 * 	variable when it is called. (This function will NOT allocate it.)
 * 	absRef will be allocated by this function, but will NOT deallocate
 * 	any pre-existing pointer. (As such you should deallocate it yourself
 * 	or copy the pointer somewhere else if you need to save it for later use.)
 *
 * 	Absolute path reference form is defined as:
 * 		- On DOS / Windows systems: Having the drive letter the colon
 * 		  and directory seperator as the first three (3) characters in
 * 		  the given path. E.x. "C:\Windows" or "D:\Setup.exe"
 *
 * 		- On all other systems: Having the directory seperator as the
 * 		  first character in the given path. E.x. "/usr" or "/home"
 * 		  or "/foo" or "/bar"
 *
 * 	If the given path is in absolute path reference form as defined above,
 * 	then the function will return FILEUTILLS_ERROR_PATH_IS_ABSOLUTE,
 * 	absRef will be set to the absolute path reference (Only the part that is
 * 	checked is stored in absRef as per above.
 * 	 E.x. On DOS / Windows systems: "<Drive Letter>:\" on all
 * 	other systems this will be set to "/".)
 * 	absRefSize will be set to the length of the absRef string.
 *
 * 	If the given path is NOT in absolute path reference form as defined
 * 	above, then this function will return FILEUTILLS_ERROR_PATH_IS_RELATIVE,
 * 	the absRef string and absRefSize variables will NOT BE ALTERED.
 *
 * 	If any error occurs then, this function will return the appropriate error code,
 * 	the absRef string and absRefSize variables will NOT BE ALTERED.
 */
bool IsAbsolutePathReference(const char * path, std::string & absRef);

/*!
 * 	int FileUtills::GetPathSegment(const std::string & path, const size_t & currentPathPos, std::string & pathSegment, const bool & blankPathSegment)
 *
 * 	This function looks for the last path segment from the given path
 * 	and copies it to the given pathSegment string argument.
 *
 * 	WARNING: If the given blankPathSegment boolean is true (default),
 * 	pathSegment is cleared (by calling std::string.clear().) even if the
 * 	function fails with an error. (So make sure pathSegment does not have
 * 	something in it you need to keep when you call this function.)
 *
 * 	(This function is mostly a slightly altered version of FileUtills::RemoveLastPathSegment()
 * 	 that copies the last path segment rather than remove it from the given path string.)
 *
 * 	The path segment to copy is determined by the given currentPathPos
 * 	variable. currentPathPos is checked to make sure it is within the capacity
 * 	of the given string and if it is, iterates backwards in the string until a
 * 	directory seperator (defined by DIR_SEP) is found. If the currentPathPos
 * 	check fails, then this function will return the COMMON_ERROR_INVALID_ARGUMENT
 * 	error code.
 *
 * 	The path segment is then copied from the directory seperator (but NOT including the directory
 * 	seperator) to pathSegment until it reaches the given currentPathPos offset in the path string.
 * 	(Or the end of the path string is reached which ever comes first.)
 *
 * 	If a path segment to copy cannot be found, then pathSegment will be cleared (if blankPathSegment is true (default))
 * 	or pathSegment will have it's original contents (if blankPathSegment is false), and
 * 	the function will return the COMMON_ERROR_SUCCESS error code.
 *
 * 	If a path segment to copy is found, then pathSegment will have a copy of the
 * 	path segment appended to it (if blankPathSegment is true (default) then only the copied path segment will
 * 	be in pathSegment, otherwise pathSegment will have it's original contents appended with the copied path
 * 	segment.), and the function will return the COMMON_ERROR_SUCCESS error code.
 *
 * 	In any case, the returned error code will also be written to Common::commonLastErrorCode.
 */
int GetPathSegment(const std::string & path, const size_t & currentPathPos, std::string & pathSegment, const bool & blankPathSegment = true);

/*!
 * 	int FileUtills::GetLastPathSegment(const std::string & path, std::string & pathSegment, const bool & blankPathSegment)
 *
 * 	This function acts as a wrapper to FileUtills::GetPathSegment(const std::string &, const size_t &, std::string &)
 * 	with the assumption that the path segment you want to copy is at the end of the
 * 	string. (end of the given string is determined by the string's size.)
 *
 * 	By default the given path segment argument will be cleared. To not clear the argument, set blankPathSegment to false.
 */
int GetLastPathSegment(const std::string & path, std::string & pathSegment, const bool & blankPathSegment = true);

/*!
 * 	int FileUtills::RemoveLastPathSegment(char ** path, size_t * currentPathPos)
 *
 * 	This function removes a path segment from the given path, and updates the
 * 	given currentPathPos variable to point to the location in the string
 * 	where the removed path segment began.
 *
 * 	Long description:
 * 	The given path argument is checked to see if is is big enough to have more
 * 	than just the filesystem root directory reference. If this is not the case
 * 	then this function will return the COMMON_ERROR_INVALID_ARGUMENT error
 * 	code, and the given path and position arguments will NOT be modified.
 *
 * 	The given path argument is copied to a temporary variable.
 *
 * 	The path segment to remove is determined by the given currentPathPos
 * 	variable. currentPathPos is checked to make sure it is within the capacity
 * 	of the given string and if it is, iterates backwards in the string until a
 * 	directory seperator (defined by DIR_SEP) is found. If the currentPathPos
 * 	check fails, then this function will return the COMMON_ERROR_INVALID_ARGUMENT
 * 	error code, and the given path and position arguments will NOT be modified.
 *
 * 	Once the path segment to remove is identfied, a check is performed to make sure
 * 	the function is not removing the filesystem root directory reference.
 *
 * 		If the path segment to be removed is within the filesystem root directory, then the
 * 		path segment is removed by replacing all of the bytes from the start of the path
 * 		segment to be removed (while preserving the DIR_SEP as required for the filesystem
 * 		root directory reference) to the end of the string with NULL character bytes.
 *
 * 		If removal of the path segment will not result in the removal of the filesystem root
 * 		directory reference, then the path segment is removed by replacing all of the bytes
 * 		from the start of the path segment to be removed (including the DIR_SEP) to the end
 * 		of the string with NULL character bytes.
 *
 * 	If the path segment is removed, then currentPathPos will be updated to indicate where
 * 	the next path segment's entry name (file or directory name) would start in the altered
 * 	string.
 *
 * 	If a path segment to remove cannot be found, then the given path and position arguments will
 * 	NOT be altered, and the function will return the COMMON_ERROR_SUCCESS error code.
 *
 * 	In any case, the returned error code will also be written to Common::commonLastErrorCode.
 *
 * 	Short description:
 * 	This function will return the COMMON_ERROR_SUCCESS error code if it is successfull,
 * 	the results will be stored in the given arguments.
 *
 * 	NOTE: This function will NOT deallocate a pre-existing pointer, but it WILL OVERWRITE IT.
 * 	(So if you need to use or deallocate it later, make sure to copy the pointer before calling
 * 	 this function.)
 *
 * 	If an error occurs, the error will be returned, and the given arguments will NOT
 * 	be altered.
 */
int RemoveLastPathSegment(char ** path, size_t * pathSize, size_t * currentPathPos);

/*!
 * 	int FileUtills::RemoveLastPathSegment(char ** path, size_t * pathSize)
 *
 * 	This function acts as a wrapper to FileUtills::RemoveLastPathSegment(char **, size_t *, size_t *)
 * 	with the assumption that the path segment you want to remove is at the end of the
 * 	string. (end of the given string is determined by the string's size.)
 *
 * 	See the function comment for FileUtills::RemoveLastPathSegment(char **, size_t *, size_t *)
 * 	the expected behavior of this wrapper function.
 */
int RemoveLastPathSegment(char ** path, size_t * pathSize);

/*!
 * 	size_t FileUtills::Get_Max_Symlink_Depth()
 *
 * 	Returns the maximum supported symbolic link depth.
 */
size_t Get_Max_Symlink_Depth()
{
	return 0;
}

/*!
 * 	int FileUtills::ResolvePath_Helper(char * retStr, size_t * retStrSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that resolves the given path and returns the result.
 *
 * 	WARNING: This function does NOT resolve any symbolic link(s) if a
 * 	symbolic link is encountered. If you need to resolve symbolic links,
 * 	use the public API version of this function: FileUtills::ResolvePath().
 *
 * 	The path resolution method is described below:
 *
 * 	First the path is checked for a user profile directory reference.
 * 	If one is found, then the profile directory path for the currently
 * 	effective user is prepended to the result and parsing continues as
 * 	if the remaining path segment(s) are relative to that profile
 * 	directory path. (The check below for a relative or absolute path
 * 	reference is skipped.)
 *
 * 	The given path is checked to determine whether it is an absolute path
 * 	reference or a relative (to the current working directory) path reference
 * 	by running it through FileUtills::IsAbsolutePathReference().
 *
 * 	If the path is considered a relative reference, the current working
 * 	directory is fetched from the host system and prepended to the result.
 * 	Parsing then continues on the remaining path segments.
 *
 * 	If the path is considered an absolute path reference, then the absolute
 * 	path reference is copied to the result, and parsing continues.
 *
 * 	The parsing loop starts which checks each given path segment to see if it
 * 	contains references to the current path segment or the parent of the current
 * 	path segment.
 *
 * 	If a reference to the current path segment is found, then the found reference
 * 	is ignored, and parsing continues with the next path segment.
 *
 * 	If a reference to the parent of the current path segment is found, then
 * 	the result is checked to see if removing the last path segment in the
 * 	result would cause going past the boundry of a root directory.
 * 	This check is defined below:
 * 		If the target system uses the DOS / Windows style path scheme,
 * 		then the check will indicate passing a root directory boundry
 * 		if the removal of the path segment would remove the drive letter
 * 		reference. (I.e. It would remove the
 * 		"<Drive letter>:<directory seperator>" portion.
 * 		(For Example: "C:\", "D:\", "Z:\", etc.))
 *
 * 		Otherwise the check will indicate passing a root directory
 * 		boundry if the removal of the path segment would remove the
 * 		initial directory seperator. (I.e. The first directory
 * 		seperator. A.K.A '/'.)
 *
 * 	If the check described above indicates that removal of the last path
 * 	segment in the result would pass the root directory boundry this function
 * 	will abort and return an error.
 *
 * 	If the check described above indicates that removal of the last path
 * 	segment would NOT result in passing the root directory boundry, then
 * 	the last segment will be removed from the result and parsing will
 * 	continue.
 *
 * 	Once the last path segment in the given path is reached, the result
 * 	will replace the contents of the retStr argument and COMMON_ERROR_SUCCESS
 * 	will be returned.
 *
 * 	If at any time an exception is thrown, the retStr argument will NOT be altered,
 * 	and COMMON_ERROR_EXCEPTION_THROWN will be returned to the caller.
 * 	(Depending on the set Common namespace logging level, a human readable
 * 	error message will be logged to describe the exception encountered more
 * 	throughly.)
 *
 * 	If an error is encountered at any point, the retStr argument will NOT be altered,
 * 	and the appropriate error will be returned to the caller.
 * 	(Depending on the set Common namespace logging level, a human readable
 * 	error message will be logged to describe the error encountered more
 * 	throughly.)
 */
int ResolvePath_Helper(char * retStr, size_t * retStrSize);

/*!
 * 	int FileUtills::ResolveSystemSymoblicLink_Syscall(char ** path, size_t * pathSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall(s) to resolve a given symbolic link.
 * 	(Note: This only works if the given symbolic link is in the format that the host system
 * 	expects / supports.)
 *
 * 	WARNING: This function verifies that the given path is a symbolic link using the host system's syscalls
 * 	for doing so. Depending on your views / requirements of secure programming, this function may not be
 * 	considered safe to call from certain contexts.
 *
 * 	All public FileUtills functions will wind up calling this function (directly or indirectly), as a side
 * 	effect of FileUtills::ResolvePath() encountering a symbolic link during path resolution. (Unless the
 * 	called public FileUtills function had it's disableSymLinkResolution boolean argument set to true
 * 	explisitly.)
 *
 * 	Returns COMMON_ERROR_SUCCESS if successful. (path with have it's contents reset and the resolved
 * 	path stored in it. pathSize will be reset and have the correct size in it for the resolved path.
 * 	Note: No deallocation is performed on either pointer, so if you need to keep the existing pointer
 * 	you should copy it elsewhere before calling this function.)
 *
 * 	Returns COMMON_ERROR_INVALID_ARGUMENT if the given path argument is empty, or if the given path string is
 * 	not a symbolic link as defined by the host system.
 *
 * 	Returns all other errors where appropriate.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	In the case of ANY error, the pointer arguments will NOT be altered.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int ResolveSystemSymoblicLink_Syscall(char ** path, size_t * pathSize);

/*!
 * 	int FileUtills::GetUserProfileDirectoryPath_Syscall(std::string & path)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	getting the user profile directory's location on
 * 	the filesystem for the current user.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode,
 * 	in addition to being returned. (The requested path will be stored in
 * 	given path argument.)
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int GetUserProfileDirectoryPath_Syscall(std::string & path);

/*!
 * 	int FileUtills::GetCurrentWorkingDirectoryPath_Syscall(std::string & path)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	getting the current working directory's location on
 * 	the filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode,
 * 	in addition to being returned. (The requested path will be stored in
 * 	given path argument.)
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int GetCurrentWorkingDirectoryPath_Syscall(std::string & path);

/*!
 * 	int FileUtills::GetExecDirectory_Syscall(char ** retStr, size_t * retStrSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	getting the main executable's location on the filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result code of this function is returned to the caller,
 * 	and the argument retStr is altered with the result.
 * 	(In case of error the arguments are NOT altered.)
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int GetExecDirectory_Syscall(char ** retStr, size_t * retStrSize);

/*!
 * 	FileUtills::dirlist * FileUtills::getDirectory_Helper(const std::string & absPath, const bool & cleanList)
 *
 * 	Helper function that calls FileUtills::getDirectory_Syscall() for
 * 	generating a list of the given path's directory contents. If cleanList
 * 	is set to true, then the list will have the references to the
 * 	given path's current directory and parent directory removed from the
 * 	generated list, as well as having the list sorted by
 * 	DataProcess::DecrementingSort().
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
FileUtills::dirlist * getDirectory_Helper(const std::string & absPath, const bool & cleanList);

/*!
 * 	FileUtills::dirlist * FileUtills::getDirectory_Syscall(const std::string & absPath, const bool & cleanList)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	getting a listing of the given path's directory contents
 * 	from the filesystem. If cleanList is set to true, then the
 * 	list will have the references to the given path's current
 * 	directory and parent directory removed from the generated
 * 	list. (The sorting is done by the Helper function.)
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode,
 * 	and a pointer to a FileUtills::dirlist is returned. (In case of error
 * 	the returned pointer will be NULL.)
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
FileUtills::dirlist * getDirectory_Syscall(const std::string & absPath, const bool & cleanList);

/*!
 * 	int FileUtills::GetGigaFreespace_Helper(const std::string & absPath, size_t & result)
 *
 * 	Helper function that calls FileUtills::GetByteFreespace_Syscall() for
 * 	getting the number of remaining free bytes on the given filesystem,
 * 	then performs the conversion of the remaining bytes to the SI unit
 * 	gigabyte (GB) representation.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int GetGigaFreespace_Helper(const std::string & absPath, size_t & result);

/*!
 * 	int FileUtills::GetFreespace_Helper(const std::string & absPath, size_t & result)
 *
 * 	Helper function that calls FileUtills::GetByteFreespace_Syscall() for
 * 	getting the number of remaining free bytes on the given filesystem,
 * 	then performs the conversion of the remaining bytes to the SI unit
 * 	megabyte (MB) representation.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int GetFreespace_Helper(const std::string & absPath, size_t & result);

/*!
 * 	int FileUtills::GetKiloFreespace_Helper(const std::string & absPath, size_t & result)
 *
 * 	Helper function that calls FileUtills::GetByteFreespace_Syscall() for
 * 	getting the number of remaining free bytes on the given filesystem,
 * 	then performs the conversion of the remaining bytes to the SI unit
 * 	kilobyte (kB) representation.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int GetKiloFreespace_Helper(const std::string & absPath, size_t & result);

/*!
 * 	int FileUtills::GetByteFreespace_Helper(const std::string & absPath, size_t & result)
 *
 * 	Helper function that calls FileUtills::GetByteFreespace_Syscall() for
 * 	getting the number of remaining free bytes on the given filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int GetByteFreespace_Helper(const std::string & absPath, size_t & result);

/*!
 * 	int FileUtills::GetByteFreespace_Syscall(const std::string & absPath, size_t & result)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	getting the number of remaining free bytes on the given filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int GetByteFreespace_Syscall(const std::string & absPath, size_t & result);

/*!
 * 	int FileUtills::CreateDirectory_Helper(const std::string & absPath, const bool & createRecursive)
 *
 * 	Helper function that calls FileUtills::CreateDirectory_Syscall() for
 * 	creating a directory on the filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int CreateDirectory_Helper(const std::string & absPath, const bool & createRecursive);

/*!
 * 	int FileUtills::CreateDirectory_Syscall(const char * absPath)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	creating a directory on the filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int CreateDirectory_Syscall(const char * absPath);

/*!
 * 	int FileUtills::CheckPermissions_Helper(const std::string & absPath, const bool & read, const bool & write, const bool & exec)
 *
 * 	Helper function that calls FileUtills::CheckPermissions_Syscall() for
 * 	checking the permissions of a given file or directory on the filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 *
 * 	WARNING: This function expects that the path given to it
 * 	is a filesystem entry within the directory to check. (I.e.
 * 	The given path is a file or directory whose parent directory
 * 	needs to be checked.) As such it will remove the last path
 * 	component from the given path before performing the checks.
 */
int CheckPermissions_Helper(const std::string & absPath, const bool & read, const bool & write, const bool & exec);

/*!
 * 	int FileUtills::CheckPermissions_Syscall(const std::string & absPath, const bool & read, const bool & write, const bool & exec)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	checking the permissions of a given file or directory on the filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int CheckPermissions_Syscall(const std::string & absPath, const bool & read, const bool & write, const bool & exec);

/*!
 * 	int FileUtills::CheckParent_Helper(const std::string & path, const bool & read, const bool & write, const bool & exec)
 *
 * 	Helper function that calls FileUtills::CheckPermissions_Helper() for
 * 	determining whether or not a given path's parent directory
 * 	exists and is accessable with the given permissions.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 *
 * 	WARNING: This function expects that the path given to it
 * 	is a filesystem entry within the directory to check. (I.e.
 * 	The given path is a file or directory whose parent directory
 * 	needs to be checked.) As such it will remove the last path
 * 	component from the given path before performing the checks.
 */
int CheckParent_Helper(const std::string & path, const bool & read, const bool & write, const bool & exec);

/*!
 * 	int FileUtills::DoesExist_Helper(const std::string & absPath)
 *
 * 	Helper function that calls FileUtills::DoesExist_Syscall() for
 * 	determining whether or not a given path exists on the given filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int DoesExist_Helper(const std::string & absPath);

/*!
 * 	int FileUtills::DoesExist_Syscall(const std::string & absPath)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	determining whether or not a given path exists on the given filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int DoesExist_Syscall(const std::string & absPath);

/*!
 * 	int FileUtills::IsFileOrDirectory_Helper(const char * absPath, const size_t absPathSize)
 *
 * 	Helper function that calls FileUtills::IsFileOrDirectory_Syscall() for
 * 	determining whether or not a given path is a file or
 * 	directory on a filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 *
 * 	Returns FILEUTILLS_ERROR_PATH_IS_A_FILE if the given absPath is a file
 * 	in the filesystem.
 *
 * 	Returns FILEUTILLS_PATH_IS_A_DIRECTORY if the given absPath is a
 * 	directory on the file system.
 *
 * 	Returns FILEUTILLS_ERROR_PATH_IS_A_SYMLINK if the given absPath is a
 * 	symbolic link in the file system.
 *
 * 	Returns COMMON_ERROR_SUCCESS if the given absPath is a valid (but unrecognised)
 * 	entry in the filesystem.
 *
 * 	Otherwise the appropriate error is returned to the caller.
 */
int IsFileOrDirectory_Helper(const char * absPath, const size_t absPathSize);

/*!
 * 	int FileUtills::IsFileOrDirectory_Syscall(const std::string & absPath)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	determining whether or not a given path is a file or 
 * 	directory on a filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int IsFileOrDirectory_Syscall(const std::string & absPath);

/*!
 * 	int FileUtills::DeletePath_Helper(const std::string & absPath, const bool & recursive)
 *
 * 	Helper function that calls FileUtills::DeletePath_Syscall() for
 * 	removing (unlinking / deleting) a given file or directory on a
 * 	filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills::ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills::ResolvePath().
 * 	If the path needs to be resolved (if you are unsure then
 * 	it does) use the public API version of this function,
 * 	which will resolve the path.
 */
int DeletePath_Helper(const std::string & absPath, const bool & recursive);

/*!
 * 	int FileUtills::DeletePath_Syscall(const std::string & absPath)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	removing (unlinking / deleting) a given file or 
 * 	directory on a filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int DeletePath_Syscall(const std::string & absPath);

/*!
 * 	int FileUtills::RenamePath_Syscall(const std::string & absPathSrc, const std::string & absPathDest, const bool & dereferenceSymLinks)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	renaming a given file or directory on the same filesystem.
 *
 * 	This function is NOT permitted to issue a call to CopyFile_Syscall()
 * 	(or actually use the host's copy syscall) under any circumstance.
 * 	(Even if the filesystems are the same.)
 *
 * 	In addition, this function is NOT permitted to move / copy files across
 * 	filesystem boundries under any circumstance.
 *
 * 	This function MUST resolve any symbolic links (symlinks) passed to it before
 * 	performing it's task, if the host's syscall for that task does not resolve them
 * 	automaticly. The ONLY exception is if the given dereferenceSymLinks argument is
 * 	set to false. The default for dereferenceSymLinks is true.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	The result of this function is stored in Common::commonLastErrorCode
 * 	in addition to being returned.
 *
 * 	This function is permitted to perform any nessacarry allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int RenamePath_Syscall(const std::string & absPathSrc, const std::string & absPathDest, const bool & dereferenceSymLinks = true);
};

#endif	/* __cplusplus */

#endif	/* FILEUTILLS_PRIVATE_API_H */

/* End of FileUtills_Private_API.h */
