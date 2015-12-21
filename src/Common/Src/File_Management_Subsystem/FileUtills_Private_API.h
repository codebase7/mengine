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
