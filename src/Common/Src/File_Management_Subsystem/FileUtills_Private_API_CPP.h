/*!
    Multiverse Engine Project 17/12/2015 FileUtills FileUtills_Private_API_CPP.h

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
#ifndef FILEUTILLS_PRIVATE_API_CPP_H
#define FILEUTILLS_PRIVATE_API_CPP_H

/* Check for defined FILEUTILLS_PRIVATE_API_H. */
#ifndef FILEUTILLS_PRIVATE_API_H
#error "This header should not be included directly. It will be included automaticly by FileUtills_Private_API.h if the compiler in use is a C++ compiler."
#endif	/* FILEUTILLS_PRIVATE_API_H */

/* Check for C++ compiler. */
#ifdef __cplusplus

/* C++ specific external includes. */
#include <cstring>
#include <string>

/* Namespace definition. */
namespace FileUtills{

/*!
 * 	int FileUtills::IsAbsolutePathReference(const char * path, const size_t pathSize)
 *
 * 	This function is a wrapper around FileUtills_IsAbsolutePathReference().
 *	See that function above for the documentation.
 */
int IsAbsolutePathReference(const char * path, const size_t pathSize);

/*!
 * 	int FileUtills::IsAbsolutePathReference(const char * path, const size_t pathSize, char ** absRef, size_t * absRefLength)
 *
 *	This function is a wrapper around FileUtills_IsAbsolutePathReference_absRef().
 *	See that function above for the documentation.
 */
int IsAbsolutePathReference(const char * path, const size_t pathSize, char ** absRef, size_t * absRefLength);

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
 * 	int FileUtills::RemoveLastPathSegment(std::string & path, size_t * currentPathPos)
 *
 * 	This function removes a path segment from the given path, and updates the
 * 	given currentPathPos variable to point to the location in the string
 * 	where the removed path segment began.
 *
 *	This function is a wrapper to FileUtills_RemoveLastPathSegmentAtPosition(), and performs
 *	conversions of the result to an std::string. As such this function will return all of
 *	FileUtills_RemoveLastPathSegmentAtPosition()'s error codes.
 *
 * 	This function will return the COMMON_ERROR_SUCCESS error code if it is successful,
 * 	the results will be stored in the given path argument.
 *
 *	See FileUtills_RemoveLastPathSegmentAtPosition() for the remaining error code descriptions.
 *
 * 	NOTE: This function will NOT deallocate a pre-existing string, but it WILL OVERWRITE IT.
 * 	(So if you need to use or deallocate it later, make sure to copy the string before calling
 * 	 this function.)
 *
 *	No alteration clause:
 *		In case of error, this function will not alter any given argument.
 */
int RemoveLastPathSegment(std::string & path, size_t * currentPathPos);

/*!
 * 	int FileUtills::RemoveLastPathSegment(std::string & path)
 *
 * 	This function acts as a wrapper to FileUtills::RemoveLastPathSegment(std::string &, size_t *)
 * 	with the assumption that the path segment you want to remove is at the end of the
 * 	string. (End of the given string is determined by the string's size.)
 *	As such, this function is equivalent to calling FileUtills::RemoveLastPathSegment(std::string &, size_t *) with a currentPathPos
 *	value of 0.
 *
 *	See FileUtills::RemoveLastPathSegment(std::string &, size_t *)'s documentation for the usage and error code documentation.
 */
int RemoveLastPathSegment(std::string & path);

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

#endif	/* FILEUTILLS_PRIVATE_API_CPP_H */

/* End of FileUtills_Private_API_CPP.h. */
