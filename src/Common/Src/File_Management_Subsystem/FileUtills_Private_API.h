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
#include <string.h>

#ifdef __cplusplus
} /* End of extern C. */
#endif	/* __cplusplus */

/* End of external includes. */

/* Define extern C. If needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Include the Basic_Linked_List header. */
#include "../../../Core/Src/Basic_Linked_List.h"

/* Define the internal MSYS_FILESIZE_PRIV structure. */
typedef struct MSYS_FILESIZE_PRIV {
enum MSYS_FILESIZE_TYPES type;			/* What type of struct it is. (Windows or POSIX. )*/
#ifdef _MSC_VER
		__int64	length;		/* Length of the file. */
#else
		off_t	length;		/* Length of the file. */
#endif	/* _MSC_VER */
} MSYS_FILESIZE_PRIV_T;

/* Define the internal FileUtills_dirList_private structure. */
typedef struct MSYS_FileUtills_dirList_PRIV {
	size_t numOfEntries;			/* Used to store the number of entries in the list array. */
	char * path;					/* Used to store the path of the directory that the entry list is about. */
	size_t pathLength;				/* Length of the path string. */
	MSYS_Linked_List_T * list;		/* The actual list of entries. */
} MSYS_FileUtills_dirList_PRIV_T;

/* Define C functions. */

/*!
 *		void FileUtills_Deallocate_CString_Syscall(char ** str)
 *
 *		Deallocates C strings made by FileUtills Syscall functions, and sets the given pointer to NULL.
 *		Once the object is deallocated, it should not be dereferenced again.
 *
 *		If given a string NOT created by a FileUtills Syscall function, the behaviour and result of this
 *		function is undefined.
 *
 *		If given an invalid (NULL) pointer this function will silently fail.
 *
 *		This function has no return.
 */
void FileUtills_Deallocate_CString_Syscall(char ** str);

/*!
	int FileUtills_Create_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV_T ** obj)

	Creates a MSYS_FileUtills_dirList_PRIV_T data structure, and set's obj to point to it.

	WARNING: This function will overwrite the *obj pointer. If you need the previous pointer after
	this function returns, you should copy it elsewhere before calling this function.

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given obj pointer is NULL.
	Returns COMMON_ERROR_MEMORY_ERROR if memory allocation fails.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
 */
int FileUtills_Create_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV_T ** obj);

/*!
	void FileUtills_Destroy_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV_T ** obj)

	Destroys (frees) the given MSYS_FileUtills_dirList_PRIV_T data structure, and
	sets the (*obj) pointer to NULL.
	Once destroyed, the given object should not be reused.

	If given an object that is not a MSYS_FileUtills_dirList_PRIV_T data structure, the result is undefined.

	Returns nothing.
 */
void FileUtills_Destroy_dirList_PRIV_Object(MSYS_FileUtills_dirList_PRIV_T ** obj);

/*!
int FileUtills_dirList_PRIV_Add_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv,
										const char * entry, const size_t entryLength)

	Copies the given entry data and inserts it into the entry list.

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL or the entry length is less than or equal to zero.
	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation fails.
	Returns COMMON_ERROR_INTERNAL_ERROR if an unexpected error occurs.
	Otherwise returns the appropriate error code.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
*/
int FileUtills_dirList_PRIV_Add_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv,
										const char * entry, const size_t entryLength);

/*!
	int FileUtills_dirList_PRIV_Get_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv, const size_t entryOffset,
										char ** entry, size_t * entryLength);

	Returns a copy of the requested entry's data. (If any.)
	This copy should be deallocated via FileUtills_dirList_PRIV_Deallocate_Entry_Data_Copy()
	when it is no longer needed.

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL.
	Returns COMMON_ERROR_RANGE_ERROR if the given entry offset is beyond the end of the entry list.
	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation fails.
	Returns COMMON_ERROR_INTERNAL_ERROR if an unexpected error occurs.
	Otherwise returns the appropriate error code.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
*/
int FileUtills_dirList_PRIV_Get_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv, const size_t entryOffset,
										char ** entry, size_t * entryLength);

/*!
	int FileUtills_dirList_PRIV_Remove_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv, const size_t entryOffset)

	Removes the given entry from the entry list.

	Returns COMMON_ERROR_SUCCESS if successful.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer is NULL.
	Returns COMMON_ERROR_RANGE_ERROR if the given entry offset is beyond the end of the entry list.
	Returns COMMON_ERROR_INTERNAL_ERROR if an unexpected error occurs.
	Otherwise returns the appropriate error code.

	No alteration clause:
		In the event of an error, this function will not modifiy the arguments given to it.
*/
int FileUtills_dirList_PRIV_Remove_Entry(MSYS_FileUtills_dirList_PRIV_T * dirListPriv, const size_t entryOffset);

/*!
	void FileUtills_dirList_PRIV_Deallocate_Entry_Data_Copy(char ** data)

	Deallocates entry data returned by FileUtills_dirList_PRIV_Get_Entry() and
	sets the given pointer to NULL.

	ALL entry data returned from FileUtills_dirList_PRIV_Get_Entry() should be
	deallocated by this function.

	If the given pointer is invalid this function will silently fail.
	This function has no return.
*/
void FileUtills_dirList_PRIV_Deallocate_Entry_Data_Copy(char ** data);

/*!
 * 	int FileUtills_IsAbsolutePathReference(const char * path, const size_t pathSize)
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
int FileUtills_IsAbsolutePathReference(const char * path, const size_t pathSize);

/*!
 * 	int FileUtills_IsAbsolutePathReference_absRef(const char * path, const size_t pathSize, char ** absRef, size_t * absRefLength)
 *
 * 	This function checks the given path to see if it's beginning is in
 * 	absolute path reference form. This function also copies the found
 * 	absolute path reference to the given absRef argument if absRef and
 *	absRefLength are non-NULL.
 *
 * 	WARNING: This function expects absRefLength to point to a valid size_t
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
 * 	absRefLength will be set to the length of the absRef string.
 *
 * 	If the given path is NOT in absolute path reference form as defined
 * 	above, then this function will return FILEUTILLS_ERROR_PATH_IS_RELATIVE,
 * 	the absRef string and absRefLength variables will NOT BE ALTERED.
 *
 * 	If any error occurs then, this function will return the appropriate error code,
 * 	the absRef string and absRefLength variables will NOT BE ALTERED.
 */
int FileUtills_IsAbsolutePathReference_absRef(const char * path, const size_t pathSize, char ** absRef, size_t * absRefLength);

/*!
 * 	int FileUtills_ResolvePath_Helper(char ** retStr, size_t * retStrSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY OUTSIDE OF THE
 * 	FILEUTILLS NAMESPACE. THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that resolves the given path and returns the result.
 *
 * 	WARNING: This function does NOT resolve any symbolic link(s) if a
 * 	symbolic link is encountered. If you need to resolve symbolic links,
 * 	use the public API version of this function: FileUtills_ResolvePath().
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
 * 	by running it through FileUtills_IsAbsolutePathReference().
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
 * 	If an error is encountered at any point, the retStr argument will NOT be altered,
 * 	and the appropriate error will be returned to the caller.
 * 	(Depending on the set Common namespace logging level, a human readable
 * 	error message will be logged to describe the error encountered more
 * 	throughly.)
 */
int FileUtills_ResolvePath_Helper(char ** retStr, size_t * retStrSize);

/*!
 * 	int FileUtills_RemoveLastPathSegmentAtPosition(char ** path, size_t * pathSize, size_t * currentPathPos)
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
 * 	Error Codes:
 * 	Returns COMMON_ERROR_SUCCESS if successful, the results will be stored in the given arguments.
 *
 *	Returns COMMON_ERROR_INVALID_ARGUMENT if a given path (pointer) is NULL, the given length of
 *	the path is less than or equal to zero, or if the currentPathPos is less than zero, or beyond
 *	the given path length.
 *
 *	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *
 *	Returns COMMON_ERROR_INTERNAL_ERROR if the memory allocation call fails for some other reason.
 *	(Reason for failure will be sent to the debug log.)
 *
 * 	NOTE: This function will NOT deallocate a pre-existing pointer, but it WILL OVERWRITE IT.
 * 	(So if you need to use or deallocate it later, make sure to copy the pointer before calling
 * 	 this function.)
 *
 *	No alteration clause:
 *		In the event of an error, this function will not modifiy the arguments given to it.
 */
int FileUtills_RemoveLastPathSegmentAtPosition(char ** path, size_t * pathSize, size_t * currentPathPos);

/*!
	int FileUtills_RemoveLastPathSegment(char ** path, size_t * pathSize)

	This function is a shortcut wrapper around FileUtills_RemoveLastPathSegmentAtPosition() with the assumption that
	the path segment to remove is at the end of the string. (End of the string is determined by the given pathSize.)
	As such, this function is equivalent to calling FileUtills_RemoveLastPathSegmentAtPosition() with a currentPathPos
	value of 0.

	See FileUtills_RemoveLastPathSegmentAtPosition()'s documentation for the usage and error code documentation.
*/
int FileUtills_RemoveLastPathSegment(char ** path, size_t * pathSize);

/*!
 * 	int FileUtills_IsFileOrDirectory_Helper(const char * absPath, const size_t absPathSize)
 *
 * 	Helper function that calls FileUtills_IsFileOrDirectory_Syscall() for
 * 	determining whether or not a given path is a file or
 * 	directory on a filesystem.
 *
 * 	This is used internally by other FileUtills functions to
 * 	prevent calling FileUtills_ResolvePath() multiple times.
 *
 * 	WARNING: This function expects that the given path has
 * 	already been resolved by FileUtills_ResolvePath().
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
int FileUtills_IsFileOrDirectory_Helper(const char * absPath, const size_t absPathSize);

/*!
 * 	int FileUtills_IsFileOrDirectory_Syscall(const char * absPath, const size_t absPathSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY.
 *	THIS FUNCTION EXPECTS ANY AND ALL OTHER
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
 * 	This function is permitted to perform any necessary allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int FileUtills_IsFileOrDirectory_Syscall(const char * absPath, const size_t absPathSize);

/*!
 * 	int FileUtills_GetUserProfileDirectoryPath_Syscall(char ** retStr, size_t * retStrSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY.
 *	THIS FUNCTION EXPECTS ANY AND ALL OTHER
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
 * 	This function is permitted to perform any necessary allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int FileUtills_GetUserProfileDirectoryPath_Syscall(char ** retStr, size_t * retStrSize);

/*!
 * 	int FileUtills_GetCurrentWorkingDirectoryPath_Syscall(char ** retStr, size_t * retStrSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY.
 *	THIS FUNCTION EXPECTS ANY AND ALL OTHER
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
 * 	This function is permitted to perform any necessary allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int FileUtills_GetCurrentWorkingDirectoryPath_Syscall(char ** retStr, size_t * retStrSize);

/*!
 * 	int FileUtills_GetExecDirectory_Syscall(char ** retStr, size_t * retStrSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY.
 *	THIS FUNCTION EXPECTS ANY AND ALL OTHER
 * 	SAFETY CHECKS HAVE PASSED BEFORE IT IS CALLED.
 *
 * 	Helper function that calls the host's syscall for
 * 	getting the main executable's location on the filesystem.
 *
 * 	This function is required to translate any error that
 * 	may be returned by the syscall into a Common namespace
 * 	error code.
 *
 * 	This function is permitted to perform any necessary allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 */
int FileUtills_GetExecDirectory_Syscall(char ** retStr, size_t * retStrSize);

/*!
 * 	int FileUtills_ResolveSystemSymoblicLink_Syscall(char ** path, size_t * pathSize)
 *
 * 	WARNING: NEVER CALL THIS FUNCTION DIRECTLY.
 *	THIS FUNCTION EXPECTS ANY AND ALL OTHER
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
 * 	effect of FileUtills_ResolvePath() encountering a symbolic link during path resolution. (Unless the
 * 	called public FileUtills function had it's disableSymLinkResolution boolean argument set to true
 * 	explicitly.)
 *
 * 	Returns COMMON_ERROR_SUCCESS if successful. (path will have it's contents reset and the resolved
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
 * 	This function is permitted to perform any necessary allocations or
 * 	modifications needed by the host's syscall to perform the task, however
 * 	these modifications and or allocations must be undone prior to the
 * 	function's return. In addition this function must catch any thrown
 * 	exception created by itself or the host's syscall. (In that instance
 * 	COMMON_ERROR_EXCEPTION_THROWN must be returned, regardless of result.)
 *
 *	No alteration clause:
 *		In the event of an error, this function will not modifiy the arguments given to it.
 */
int FileUtills_ResolveSystemSymoblicLink_Syscall(char ** path, size_t * pathSize);

/*!
 * 	size_t FileUtills_Get_Max_Symlink_Depth_Syscall()
 *
 * 	Returns the host's maximum supported symbolic link depth.
 */
size_t FileUtills_Get_Max_Symlink_Depth_Syscall();

#ifdef __cplusplus
} /* End of extern C. */
#endif	/* __cplusplus */

/* Check for C++ compiler and include the C++ specific header if needed. */
#ifdef __cplusplus
/* Include the C++ specific header. */
#include "FileUtills_Private_API_CPP.h"
#endif	/* __cplusplus */

#endif	/* FILEUTILLS_PRIVATE_API_H */

/* End of FileUtills_Private_API.h */
