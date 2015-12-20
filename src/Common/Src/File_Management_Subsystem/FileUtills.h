/*!
    Multiverse Engine Project 04/12/2011 FileUtills FileUtills.h
    Yes we are reinventing the wheel here, go with it.

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
#ifndef FILEUTILLS_H
#define FILEUTILLS_H

/* Check for MSVC and disable the CRT_SECURE_WARNINGS so that the compiler will be quiet about finding portable code... */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif	/* _MSC_VER */

/* Define extern C if needed. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus. */

/* External Includes. */
#include <stdio.h>	/* Defines FILE and friends. */

/* Engine Includes */
#ifdef _WIN32
#include "..\Error_Handler\Common_Error_Handler.h"
#include "..\Error_Handler\Common_Error_Handler_Internal.h"
#include "..\..\..\Core\Src\DataProcess.h"
#else
#include "../Error_Handler/Common_Error_Handler.h"
#include "../Error_Handler/Common_Error_Handler_Internal.h"
#include "../../../Core/Src/DataProcess.h"
#endif

/* Define the stringifier. */
#ifndef MSYS_REAL_STRINGIFIY
#define MSYS_REAL_STRINGIFIY(s) #s
#endif	/* MSYS_REAL_STRINGIFIY */

#ifndef MSYS_STRINGIFIY
#define MSYS_STRINGIFIY(s) MSYS_REAL_STRINGIFIY(s)
#endif	/* MSYS_STRINGIFIY */

/* Define the appropriate Directory seperators and Symbols. */
#ifdef _WIN32
/* Define the Windows Directory seperator */
#define DIR_SEP '\\'
#define DIR_SEP_STR MSYS_STRINGIFIY(DIR_SEP)
#define HOME_DIR_SYMBOL '~'
#define FILEEXT_SEP '.'
#define FILEEXT_SEP_STR MSYS_STRINGIFIY(FILEEXT_SEP)
/* Define the minimal valid absolute directory path length. */
/*
 * MINIMAL_VALID_ABSOLUTE_PATH_LENGTH is supposed to include the needed DIR_SEP for the root directory.
 * In addition it is supposed to be the minimal number of char(s) needed to represent a valid absolute path
 * to a root directory.
 * 
 * In windows "<Drive letter>:<DIR_SEP>" is minimal for an absolute path. (Root of given drive.)
 */
#define MINIMAL_VALID_ABSOLUTE_PATH_LENGTH 3
#else
/* Define the Posix Directory Seperator. */
#ifndef DIR_SEP
#define DIR_SEP '/'
#define DIR_SEP_STR MSYS_STRINGIFIY(DIR_SEP)
#define HOME_DIR_SYMBOL '~'
#define Relative_Symbol "./"
#define FILEEXT_SEP '.'
#define FILEEXT_SEP_STR MSYS_STRINGIFIY(FILEEXT_SEP)
/*
 * MINIMAL_VALID_ABSOLUTE_PATH_LENGTH is supposed to include the needed DIR_SEP for the root directory.
 * In addition it is supposed to be the minimal number of char(s) needed to represent a valid absolute path
 * to a root directory.
 * 
 * In linux "<DIR_SEP>" is minimal for an absolute path. (Root of the entire filesystem / chroot.)
 */
#define MINIMAL_VALID_ABSOLUTE_PATH_LENGTH 1
#endif	/* DIR_SEP */
#endif	/* _WIN32 */

/*!
 *		enum MSYS_FILESIZE_TYPES
 *
 *		Defines the types that an MSYS_FILESIZE object may have.
 */
enum MSYS_FILESIZE_TYPES {
	UNKNOWN_FILESIZE_TYPE = 0,
	WINDOWS_FILESIZE_TYPE = 1,
	POSIX_FILESIZE_TYPE = 2,
};

/* File size structure. Contains the length of a file's size. */
typedef struct MSYS_FILESIZE {
	enum MSYS_FILESIZE_TYPES type;			/* What type of struct it is. (Windows or POSIX. )*/
} MSYS_FILESIZE_T;

/* Define the directory list structure. */
typedef struct FileUtills_dirlist {
    void * pointer;		/* Pointer to object. */
} FileUtills_dirlist_T;

/*!
 *		void FileUtills_Deallocate_CString(char ** str)
 *
 *		Deallocates C strings made by FileUtills, and sets the given pointer to NULL.
 *		Once the object is deallocated, it should not be dereferenced again.
 *
 *		If given a string NOT created by FileUtills, the behaviour and result of this function is undefined.
 *
 *		If given an invalid (NULL) pointer this function will silently fail.
 *
 *		This function has no return.
 */
void FileUtills_Deallocate_CString(char ** str);

/*!
 *		int FileUtills_Create_MSYS_FILESIZE_Structure(MSYS_FILESIZE_T ** str)
 *
 *		Factory function for MSYS_FILESIZE structures.
 *
 *		WARNING: This function will NOT deallocate a preexisting object pointed to by the given
 *		pointer argument. The function WILL overwrite the original pointer if it is successful.
 *		If you need to keep that pointer for later deallocation, copy it elsewhere before calling
 *		this function.
 *
 *		Returns COMMON_ERROR_SUCCESS if creation of structure was successful.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointer to pointer is NULL.
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation fails.
 *		Otherwise returns the appropriate error code.
 *
 *		In case of error, this function will NOT modify it's argument.
 */
int FileUtills_Create_MSYS_FILESIZE_Structure(MSYS_FILESIZE_T ** str);

/*!
 *		void FileUtills_Destroy_MSYS_FILESIZE_Structure(MSYS_FILESIZE_T ** str)
 *
 *		Destructor for MSYS_FILESIZE structures. Takes the given pointer to pointer, derefs it and
 *		deallocates the pointer to object if it is allocated.
 *
 *		WARNING: This function is a destructor for MSYS_FILESIZE objects ONLY! Giving a different object
 *		to this function will cause undefined behavior.
 *
 *		If the given pointer is NULL, then this function will silently fail.
 *
 *		This function has no return.
 */
void FileUtills_Destroy_MSYS_FILESIZE_Structure(MSYS_FILESIZE_T ** str);

/*!
 *		int FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(const MSYS_FILESIZE_T * str, long long int * retVal)
 *
 *		Accessor function.
 *
 *		Returns the length variable from the given MSYS_FILESIZE structure.
 *
 *		Returns COMMON_ERROR_SUCCESS if successful. retVal will hold the result.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL.
 *		Otherwise returns the appropriate error code.
 *
 *		In case of error, this function will NOT modify it's arguments.
 */
int FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(const MSYS_FILESIZE_T * str, long long int * retVal);

/*!
 *		int FileUtills_Set_Length_From_MSYS_FILESIZE_Structure_LLINT(MSYS_FILESIZE_T * str, const long long int * val)
 *
 *		Accessor function.
 *
 *		Sets the length variable for the given MSYS_FILESIZE structure.
 *
 *		Returns COMMON_ERROR_SUCCESS if successful.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL.
 *		Otherwise returns the appropriate error code.
 *
 *		In case of error, this function will NOT modify it's arguments.
 */
int FileUtills_Set_Length_From_MSYS_FILESIZE_Structure_LLINT(MSYS_FILESIZE_T * str, const long long int * val);

/*!
		void FileUtills_Destroy_FileUtills_dirlist_Structure(FileUtills_dirlist_T ** dirList)

		Destroys (frees) the given FileUtills_dirlist data structure, and sets the (*dirList) pointer to NULL.
		Once destroyed, the given object should not be reused.

		If given an object that is not a FileUtills_dirlist data structure, the result is undefined.

		Returns nothing.
 */
void FileUtills_Destroy_FileUtills_dirlist_Structure(FileUtills_dirlist_T ** dirList);

/*
 * 		int FileUtills_Get_File_Length_By_Filename(const char * filename, const size_t filenameSize, MSYS_FILESIZE_T * fileLength)
 *
 * 		Returns the length of the given file.
 * 		(This is just a wrapper around FileUtills_Get_File_Length().)
 *
 * 		Returns COMMON_ERROR_SUCCESS if the length is read in successfully. (fileLength will be set to the named file's length in this case.)
 * 		Otherwise returns the appropriate error code.
 *
 * 		In case of error, (the returned error code is not COMMON_ERROR_SUCCESS), the fileLength argument will NOT be altered.
 */
int FileUtills_Get_File_Length_By_Filename(const char * filename, const size_t filenameSize, MSYS_FILESIZE_T * fileLength);

/*!
 * 		int FileUtills_Get_File_Length(FILE * fp, MSYS_FILESIZE_T * fileLength)
 *
 * 		Gets the length of the given open file.
 *
 * 		This function expects the file stream to be in a good state, (I.e. It's error flag is not set), and that the file
 * 		stream was opened in binary mode. (If the stream is not already open, use FileUtills_Get_File_Length_By_Filename() instead,
 * 		it will ensure that these requirements are met.)
 *
 * 		This function calculates the size of the file by starting at the beginning and working it's way to the end by calling
 * 		fgetc(), and then checking the state flags (error and eof) after each call to fgetc(). When the EOF flag is set,
 * 		(and the error flag is not set), the function will call ftello() to get the offset and check it for error. Finally
 * 		regardless if an error has occurred or not, the function will attempt to restore the previous position in the file
 * 		that the file was at when the call to this function was made.
 *
 * 		Returns COMMON_ERROR_SUCCESS if the file length is determined. (fileLength will be set to the determined length in this case.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given file pointer or fileLength pointer is NULL.
 *
 * 		Returns COMMON_ERROR_IO_ERROR if one of the f*() functions fails.
 *
 * 		Returns COMMON_ERROR_MEMORY_ERROR if the file length was determined, but could not be retrieved from the file stream because the
 * 		value could not be converted and stored. (Blame the C standard in this case.....)
 *
 * 		Otherwise returns the appropriate error code.
 *
 * 		In case of error, (the returned error code is not COMMON_ERROR_SUCCESS), the fileLength argument will NOT be altered.
 */
int FileUtills_Get_File_Length(FILE * fp, MSYS_FILESIZE_T * fileLength);

/*!
 *		int FileUtills_Read_Bytes_From_File(FILE * IN, const size_t dataLength, char * dataBuf, const size_t dataBufLength, const size_t destStaringOffset, const bool blankDataBuf)
 *
 *		Reads the given amount of bytes from the given input file and copies them
 *		to the given memory buffer.
 *
 * 		WARNING: This function expects a pre-allocated memory buffer as big as the
 *		given data length. If the buffer is smaller than this a memory access violation
 *		WILL HAPPEN.
 *
 *		NOTE: This function expects that the given input file is already open and not errored out when called.
 *		The input file will remain open after the function returns. (It will still be usable if the returned error code is SUCCESS.)
 *
 *		The input position of the file will NOT be restored in ANY instance after this function returns.
 *		If you need the current position for something, copy it elsewhere before calling this function.
 *
 * 		@pram IN: C FILE structure that points to a pre-opened file that data will be read from. (Cannot be in an error state, data will be read from the file's current offset.)
 * 		@pram dataLength: The amount of data to read from the file.
 * 		@pram dataBuf: Preallocated C-String where the data read from the file will be stored. (Will not be reallocated if too small.)
 * 		@pram dataBufLength: The total length of the pre-allocated dataBuf string.
 * 		@pram destStaringOffset: Position in the dataBuf string where read data from the file will start at.
 * 		@pram blankDataBuf: Whether or not to blank out the dataBuf with NULL bytes.
 *
 *		Returns COMMON_ERROR_SUCCESS if the data is read into the memory buffer successfully.
 *
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if a given pointer is NULL,
 *		the given input file has errored out prior to the function call,
 *		dataLength or dataBufLength is less than 1, or destStaringOffset plus dataLength
 * 		is greater than or equal to dataBufLength.
 *
 * 		Returns COMMON_ERROR_IO_ERROR on all f*() errors, or if the end of the file is hit prior to reading
 *		the amount of requested data.
 *
 *		Otherwise returns the appropriate error code.
 */
int FileUtills_Read_Bytes_From_File(FILE * IN, const size_t dataLength, char * dataBuf, const size_t dataBufLength, const size_t destStaringOffset, const bool blankDataBuf);

/*!
 *		int FileUtills_Write_Data_To_File_From_File(FILE * OUT, const char * filename, const size_t filenameLength, const MSYS_FILESIZE_T * fileStartingOffset, const size_t dataLength)
 *
 *		Opens the given input file in binary mode and jumps to the given starting offset,
 *		then reads the given amount of data and writes it directly to the given output file,
 *		finally it closes the input file.
 *
 *		NOTE: This function expects that the given output file is already open and not errored out when called.
 *		The output file will remain open after the function returns. (It will still be usable if the returned error code is SUCCESS.)
 *
 *		The output position of the file will NOT be restored in ANY instance after this function returns.
 *		If you need the current position for something, copy it elsewhere before calling this function.
 *
 *		Returns COMMON_ERROR_SUCCESS if the data is written to the output file successfully.
 *
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given output file pointer is NULL,
 *		the given output file has errored out prior to the function call,
 *		filename is NULL, filenameLength is less than 1, fileStartingOffset is less than 0,
 *		or dataLength is less than 1.
 *
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *
 *		Returns COMMON_ERROR_IO_ERROR on all f*() errors, or if the end of the file is hit prior to reading
 *		the amount of requested data.
 *
 *		Otherwise returns the appropriate error code.
 */
int FileUtills_Write_Data_To_File_From_File(FILE * OUT, const char * filename, const size_t filenameLength, const MSYS_FILESIZE_T * fileStartingOffset, const size_t dataLength);

/*!
 *		int FileUtills_Write_Data_To_File_From_Memory(FILE * OUT, const char * data, const size_t dataLength)
 *
 *		Writes out the given data in memory to the given output file.
 *
 *		NOTE: This function expects that the given output file is already open and not errored out when called.
 *		The output file will remain open after the function returns. (It will still be usable if the returned error code is SUCCESS.)
 *		
 *		The output position of the file will NOT be restored in ANY instance after this function returns.
 *		If you need the current position for something, copy it elsewhere before calling this function.
 *
 *		Returns COMMON_ERROR_SUCCESS if the data is written to the output file successfully.
 *
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if the given output file pointer is NULL,
 *		the given output file has errored out prior to the function call,
 *		data is NULL, or dataLength is less than 1.
 *
 *		Returns COMMON_ERROR_IO_ERROR on all f*() errors.
 *
 *		Otherwise returns the appropriate error code.
 */
int FileUtills_Write_Data_To_File_From_Memory(FILE * OUT, const char * data, const size_t dataLength);

/*!
 *		int FileUtills_Get_Last_Path_Component(char ** retStr, size_t * retStrLength, const int getParent)
 *
 *		Fetches the last part of the given path and creates a sub-string from it.
 *
 *		Alternatively, this function can be used to return a sub-string with the parent path of the last path component,
 *		if getParent is set to a non-zero value.
 *
 *		(This is a wrapper around DataProcess_Get_SubString_Using_Delimiter(), and as such has similar error codes.)
 *
 *		@pram getParent: If set to a non-zero value, then the parent path of the last path component will be used for the sub-string.
 *		Otherwise, the last path component will be used for the sub-string.
 *
 *		WARNING: This function will NOT deallocate the given c-string argument (*retStr). If this function returns COMMON_ERROR_SUCCESS,
 *		the given c-string pointer (*retStr) will be overwritten with a pointer to the newly created sub-string. If you need to deallocate
 *		the original c-string, copy the pointer elsewhere before calling this function.
 *
 *		Returns COMMON_ERROR_SUCCESS if the last path component (or parent path) was found and a sub-string was created.
 *		Returns COMMON_ERROR_RANGE_ERROR if the path is a relative path without any directory components.
 *		Returns COMMON_ERROR_END_OF_DATA if the path is a directory with directory separator on the end. 
 *										 (This should be stripped off by this function if needed, but may still be returned.)
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if a given argument is invalid.
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *		Returns COMMON_ERROR_INTERNAL_ERROR if a call to an engine function fails.
 *		Otherwise returns the appropriate error code.
 *
 *		No alteration clause:
 *		In case of error, this function will not alter any given argument.
 *		(For the purposes of this no-alteration clause, the error codes COMMON_ERROR_RANGE_ERROR and COMMON_ERROR_END_OF_DATA
 *		 are considered errors.)
 */
int FileUtills_Get_Last_Path_Component(char ** retStr, size_t * retStrLength, const int getParent);

/*!
 *		int FileUtills_Get_File_Name_Component(const char * path, const size_t pathLength, char ** retStr, size_t * retStrLength, 
 *												const int getExtension)
 *
 *		Fetches the file name or extension from the given path and creates a sub-string from it.
 *
 *		(This is a wrapper around DataProcess_Get_SubString_Using_Delimiter(), and as such has similar error codes.)
 *
 *		@pram getExtension whether or not to get the file extension. If set to zero the file name will be put into the sub-string,
 *							otherwise the file extension will be put into the sub-string.
 *
 *		Returns COMMON_ERROR_SUCCESS if the file name / extension was found and a sub-string was created.
 *		Returns COMMON_ERROR_RANGE_ERROR if the path is a path without an name / extension.
 *		Returns COMMON_ERROR_END_OF_DATA if the path is a path with an extension separator ('.') (on the end / at the beginning)
 *				 and nothing (before / after) it.
 *		Returns COMMON_ERROR_INVALID_ARGUMENT if a given argument is invalid.
 *		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *		Returns COMMON_ERROR_INTERNAL_ERROR if a call to an engine function fails.
 *		Otherwise returns the appropriate error code.
 *
 *		No alteration clause:
 *		In case of error, this function will not alter any given argument.
 *		(For the purposes of this no-alteration clause, the error codes COMMON_ERROR_RANGE_ERROR and COMMON_ERROR_END_OF_DATA
 *		 are considered errors.)
 */
int FileUtills_Get_File_Name_Component(const char * path, const size_t pathLength, char ** retStr, size_t * retStrLength, const int getExtension);

/*!
 * 	int FileUtills_GetUserProfileDirectoryPath(char ** retStr, size_t * retStrSize)
 *
 * 	Fetches the user's profile directory from the environment, and stores
 * 	it in the given path argument.
 *
 * 	If the function fails for any reason, the arguments will NOT be altered,
 * 	and the appropriate error will be returned to the caller.
 */
int FileUtills_GetUserProfileDirectoryPath(char ** retStr, size_t * retStrSize);

/*!
 * 	int FileUtills_GetCurrentWorkingDirectoryPath(char ** path, size_t * pathSize)
 *
 * 	Fetches the current working directory from the environment, and stores
 * 	it in the given retStr argument.
 *
 *	If the function fails for any reason, the arguments will NOT be altered,
 * 	and the appropriate error will be returned to the caller.
 */
int FileUtills_GetCurrentWorkingDirectoryPath(char ** retStr, size_t * retStrSize);

/*!
 * 	int FileUtills_GetExecDirectory(char ** path, size_t * pathSize)
 *
 * 	Replaces the contents of the given retStr argument with a NULL
 * 	terminated C-String that contains the path to the directory where the
 * 	executable is stored.
 *
 * 	If the function fails for any reason, the arguments will NOT be altered,
 * 	and the appropriate error will be returned to the caller.
 */
int FileUtills_GetExecDirectory(char ** retStr, size_t * retStrSize);

/*!
        int getDirectory(const char * path, const size_t pathSize, FileUtills_dirlist_T ** dirTree, const bool & cleanList)

        Lists the given directory's contents.

        Pram: path, path of directory to check.

        Pram: FileUtills_dirlist ** dirTree, pointer to a pointer to a
        FileUtills_dirlist structure that will contain the resulting
        directory listing if successful. If the structure is already
        allocated when passed to this function and this function succeeds,
		the pre-existing structure will be deallocated.

        Pram: cleanList, If this is true then, the generated list will be sorted
        (via decrementing sort), and the list will have the entries for the current
        and parent directories removed.
        Default is to do nothing, and return the list as the OS generated it.
        
        WARNING: The OS generated list has no guarantee that it will always show up
        in the same order, as that depends on the underlying OS and filesystem.
        
        If you need a predictable list, (I.e. a list that always shows up in the same
        order (excluding ANY modifications to the filesystem)) then you should always 
        set cleanList to true when calling this function.

        Returns COMMON_ERROR_SUCCESS if successfull, dirTree's pointer will point to a valid
		FileUtills_dirlist structure with the given path's contents in this case.
		(Any previous structure pointed to by the dirTree pointer will be deallocated.)

        Otherwise this function will return the appropriate error, and dirTree's pointer will
        not be modified.
*/
int FileUtills_getDirectory(const char * path, const size_t pathSize, FileUtills_dirlist_T ** dirTree, const bool cleanList);

/*!
	int FileUtills_DoesExist(const char * path, const size_t pathSize)

	Prams: @std::string path, path to check for existence on the filesystem.

	This function checks to see if given file or directory exists.

	This function is called by FileUtills_CheckPermissions() before running permission checks.

	Returns FILEUTILLS_ERROR_EXISTANT if file or directory exists on the system.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if file or directory does not exist on the system.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given path is empty.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given system is unsupported.
	Returns the appropriate error in all other instances.
*/
int FileUtills_DoesExist(const char * path, const size_t pathSize);

/*!
	FileUtills_IsFileOrDirectory(const char * path, const size_t pathSize)

	Checks to see if a given path is a file or directory.

	Returns COMMON_ERROR_SUCCESS if the path exists but it is not a file or directory.
	Returns FILEUTILLS_ERROR_PATH_IS_A_FILE if the path is a file.
	Returns FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY if the path is a directory.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given system is unsupported.
	Returns COMMON_ERROR_ACCESS_DENIED if a permissions error occurs.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given path is empty.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if a path component does not exist.
	Returns FILEUTILLS_ERROR_ if the path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
	Returns the appropriate error in all other instances.
*/
int FileUtills_IsFileOrDirectory(const char * path, const size_t pathSize);

/*!
	int FileUtills_CheckParent(const char * path, const size_t pathSize, const bool read, const bool write, const bool exec)

	Acts as a wrapper to DoesExist and CheckPermissions
	Checks for the parent directory's existence in the path given.
	Also Checks to see if it is accessible. By default it checks for Read and Write access.
	(Optionally it can check for execute permissions, and any combination of the three. This
	function will return a COMMON_ERROR_INVALID_ARGUMENT error however if all of the permissions to check
	are false.)

	Ex. If this path is given: "/home/user/Homework.txt", this function will check and see if the "/home/user" parent
	directory exists, and if it is accessible.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if the directory exists and is accessible with the requested permissions.
	Returns COMMON_ERROR_ACCESS_DENIED if A permission error occurs.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if the parent directory does not exist.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the OS / Arch is not supported.
	Returns COMMON_ERROR_SYSTEM_SPECIFIC if a system specific / untranslated error occurs.
	Returns COMMON_ERROR_INTERNAL_ERROR if an engine error occurs.
	Returns COMMON_ERROR_UNKNOWN_ERROR if an unknown error occurs.
	Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown.
	Returns the appropriate error in all other cases.
*/
int FileUtills_CheckParent(const char * path, const size_t pathSize, const bool read, const bool write, const bool exec);

/*!
	int FileUtills_GetParent(char ** retStr, size_t * retStrLength)

	Returns the parent directory for the given file.

	This function is now a wrapper for FileUtills_Get_Last_Path_Component() with getParent set to true.

	WARNING: This function will NOT deallocate the given c-string argument (*retStr). If this function returns COMMON_ERROR_SUCCESS,
	the given c-string pointer (*retStr) will be overwritten with a pointer to the newly created sub-string. If you need to deallocate
	the original c-string, copy the pointer elsewhere before calling this function.

	Returns COMMON_ERROR_SUCCESS with parent directory path set in retStr, and length of retStr set in retStrLength if successful.
	(retStr's size will be set in retStrSize.)
	
	Returns the appropriate error code otherwise. (See error code description for FileUtills_Get_Last_Path_Component() for error codes.)
	(retStr and retStrLength will NOT be altered in this case.)
*/
int FileUtills_GetParent(char ** retStr, size_t * retStrLength);

/*!
	int FileUtills_ResolvePath(const char * path, const size_t pathSize, char ** retStr, size_t * retStrSize, const bool disableSymLinkResolution)

	Checks the path given, and converts it to a absolute path. The result is allocated by this function,
	and a pointer to it is stored in retStr. The size of the result is stored in retStrSize.

	WARNING: If this function returns success, the contents of retStr and retStrSize will be overwritten,
	and no deallocation attempt will be made on them. (Even if they were created by this function.)
	If the contents of retStr and retStrSize are needed for use after this function returns, then the
	contents should be copied elsewhere before calling this function.

	When the result of this function is no longer needed it should be deallocated with FileUtills_Deallocate_CString().

	Setting disableSymLinkResolution to true will disable resolving any symbolic link(s) if a
	symbolic link is encountered while resolving the given path(s). Setting
	disableSymLinkResolution to false will make this function resolve any
	symbolic link(s) that are encountered while resolving the given path(s).

	Returns COMMON_ERROR_SUCCESS if successful, retStr and retStrSize will be altered in this
	case.

	Returns COMMON_ERROR_INVALID_ARGUMENT if the given path is empty, it's size is less than or equal to zero,
	or a given pointer is NULL.

	Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.

	Returns COMMON_ERROR_INTERNAL_ERROR if an unexpected error occurs while processing the path.

	No alteration clause:
 		In case of error, this function will not alter any given argument.
*/
int FileUtills_ResolvePath(const char * path, const size_t pathSize, char ** retStr, size_t * retStrSize, const bool disableSymLinkResolution);

/*!
	int FileUtills_CreateDirectory(const char * directory, const size_t directorySize, const bool createRecursive)
	@pram : directory, path to create.
	@pram : createRecursive, if this is set to true, then this function will try to create the 
	parent directories of the given directory if they do not exist.

	This function attempts to create the given directory on the filesystem.

	Returns COMMON_ERROR_SUCCESS if directory creation was successful.
	Returns COMMON_ERROR_ACCESS_DENIED if permission is denied.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if this function is unsupported.
	Returns FILEUTILLS_ERROR_FILESYSTEM_FULL if the disk is full.
	Returns FILEUTILLS_ERROR_EXISTANT if the directory already exists.
	Returns the appropriate error or COMMON_ERROR_UNKNOWN_ERROR if another error is encountered.
*/
int FileUtills_CreateDirectory(const char * directory, const size_t directorySize, const bool createRecursive);

/*!
	int FileUtills_CheckPermissions(const char * path, const size_t pathSize, const bool read, const bool write, const bool exec)

	Checks Permissions on the given file or directory. Also checks if the given file or directory
	actually exists first before checking other permissions. By default it will check for both read and
	write permissions. (Optionally it can check for execute permissions, and any combination of the three. This
	function will return a COMMON_ERROR_INVALID_ARGUMENT error however if all of the permissions to check
	are false.)

	Pram: path to directory or file to check.
	Pram: check for read permission. default is true.
	Pram: check for write permission. default is true.
	Pram: check for execute permission. default is false.

	Returns COMMON_ERROR_SUCCESS if the directory exists and is accessible with the requested permissions.
	Returns COMMON_ERROR_ACCESS_DENIED if A permission error occurs.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if the parent directory does not exist.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the OS / Arch is not supported.
	Returns COMMON_ERROR_SYSTEM_SPECIFIC if a system specific / untranslated error occurs.
	Returns COMMON_ERROR_INTERNAL_ERROR if an engine error occurs.
	Returns COMMON_ERROR_UNKNOWN_ERROR if an unknown error occurs.
	Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown.
	Returns the appropriate error in all other cases.
*/
int FileUtills_CheckPermissions(const char * path, const size_t pathSize, const bool read, const bool write, const bool exec);

/*!
	int FileUtills_GetGigaFreespace(const char * path, const size_t pathSize, size_t * result)

	Returns the remaining disk space in Gigabytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const char * path : string that contains the volume / path to check.
	@pram const size_t pathSize: length of the path string.
	@pram size_t & result : The remaining space on the filesystem.

	Returns COMMON_ERROR_SUCCESS if successful, result will contain the remaining space.
	Returns a Common name-space error if an error occurs. result will not be altered in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int FileUtills_GetGigaFreespace(const char * path, const size_t pathSize, size_t * result);

/*!
	int FileUtills_GetFreespace(const char * path, const size_t pathSize, size_t * result)

	Returns the remaining disk space in Megabytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const char * path : string that contains the volume / path to check.
	@pram const size_t pathSize: length of the path string.
	@pram size_t & result : The remaining space on the filesystem.

	Returns COMMON_ERROR_SUCCESS if successful, result will contain the remaining space.
	Returns a Common name-space error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int FileUtills_GetFreespace(const char * path, const size_t pathSize, size_t * result);

/*!
	int FileUtills_GetKiloFreespace(const char * path, const size_t pathSize, size_t * result)

	Returns the remaining disk space in Kilobytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const char * path : string that contains the volume / path to check.
	@pram const size_t pathSize: length of the path string.
	@pram size_t & result : The remaining space on the filesystem.

	Returns COMMON_ERROR_SUCCESS if successful, result will contain the remaining space.
	Returns a Common name-space error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int FileUtills_GetKiloFreespace(const char * path, const size_t pathSize, size_t * result);

/*!
	int FileUtills_GetByteFreespace(const char * path, const size_t pathSize, size_t * result)

	Returns the remaining disk space in Bytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const char * path : string that contains the volume / path to check.
	@pram const size_t pathSize: length of the path string.
	@pram size_t & result : The remaining space on the filesystem.

	Returns COMMON_ERROR_SUCCESS if successful, result will contain the remaining space.
	Returns a Common name-space error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int FileUtills_GetByteFreespace(const char * path, const size_t pathSize, size_t * result);

/*!
	int FileUtills_DeletePath(const char * path, const size_t pathSize, const bool recursive)

	This function attempts to delete the given file or directory from the filesystem.

	By default this function will NOT delete recursively.
	If the given path is a non-empty directory, by default this function will throw an error.
	If the given path is an empty directory, however by default this function WILL delete it.

	Note: If while deleting recursively, a file or subdirectory can't be deleted, this function will try to continue
	deleting any other files and subdirectories that can be deleted, but it will throw an error upon exit.

	Returns COMMON_ERROR_SUCCESS if successful.
	COMMON_ERROR_ACCESS_DENIED if the user lacks permission to delete the path. (Or if recursively deleting a directory, a file or subdirectory could not be deleted.)
	FILEUTILLS_ERROR_NON_EXISTANT if the path does not exist. (Or if recursively deleting a directory, a file or subdirectory does not exist.)
	COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the function is not supported.
	COMMON_ERROR_MEMORY_ERROR if a memory error occurs.
	COMMON_ERROR_UNKNOWN_ERROR if an unknown error occurs. (An error other than a permissions error occured while deleting something.)
	FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY if the path is a non empty directory and recursive is set to false.
	COMMON_ERROR_IO_ERROR if while deleting recursively, the parent directory of a deleted directory could not be obtained. (I.e could not "go up a level in the directory tree.")
	COMMON_ERROR_IO_ERROR if while deleting recursively, there were files and or subdirectories that could not be deleted. (Some files may have been deleted however.)
*/
int FileUtills_DeletePath(const char * path, const size_t pathSize, const bool recursive);

/*!
        int FileUtills_CopyFile(const char * srcPath, const size_t srcPathSize, const char * destPath, const size_t destPathSize, 
								 const bool append, const size_t begOffset, const size_t endOffset)

        Copies endOffset bytes starting at begOffset, from source file to dest file.

        Offset rules:
         - If offsets are used, they must be positive. (If one or both of the given offsets is negative,
         then COMMON_ERROR_INVALID_ARGUMENT will be returned.)
        
         - If zeros are used for both offsets, then the entire file will be copied.
        
         - If endOffset is greater than begOffset then the given range of bytes
         from the file will be copied.
	 
	 - If begOffset is equal to zero and endOffset is greater than zero, then
	 the file will be copied from the start of the file to endOffset.

	 - If begOffset is greater than zero and endOffset is equal to zero, then
	 the file will be copied from begOffset to the end of the file.

	 - If any offset is not zero, then ONLY IF the file has enough bytes in it
	 to copy the given range of bytes from the given beginning offset, will the
	 copy take place.
	 (This allows for some insurance if the source file's size is known before
	 calling this function.)

        This function only works on FILES. Not directories. To copy a directory, call FileUtills_CopyPath().

        @pram src, path to the source file.
        @pram dest, path to the dest file.
        
        @pram append, Whether or not to append data to the dest file.
        (Note only applies if the dest file exists. If append is false, then the dest file will be overwritten.)
                                                                        
        @pram begOffset, Location in the source file to start copying data from.
        @pram endOffset, Location in the source file to stop copying data when it is reached.

        By default the entire file is copied and the dest file is overwritten.

        Note: This function does NOT make any attempt to preserve the destination file if it already exists.

        Note: This function can return ANY error in the Common name-space error list, below is only an example
        of what errors this function itself may generate. (I.e. This function calls other FileUtills functions
        and as such can return the errors generated by them.) If you need a more detailed error message, you
        should register a callback function for the Common error handler (via Common::Register_Error_Log_Callback())
        before calling this function.

        Returns COMMON_ERROR_SUCCESS on success.
        Returns COMMON_ERROR_INVALID_ARGUMENT if a given offset is negative.
        Returns COMMON_ERROR_INVALID_ARGUMENT if the given begOffset is bigger than the given endOffset. (I.e you reversed the offsets.)
        Returns COMMON_ERROR_MEMORY_ERROR if the memory buffer could not be allocated.
        Returns COMMON_ERROR_INVALID_ARGUMENT if the source file was not given.
        Returns COMMON_ERROR_IO_ERROR if the source file could not be opened.
        Returns COMMON_ERROR_IO_ERROR if an I/O error occurred while reading the source file.
        Returns COMMON::FILEUTILLS_PATH_IS_A_DIRECTORY if the given source file was a directory.
        Returns COMMON_ERROR_INVALID_ARGUMENT if the dest file was not given.
        Returns COMMON_ERROR_IO_ERROR if dest file could not be opened.
        Returns COMMON_ERROR_IO_ERROR if an I/O error occurred while writing to the dest file.
        Returns FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY if the given dest file was a directory.
        Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown while copying data.
*/
int FileUtills_CopyFile(const char * srcPath, const size_t srcPathSize, const char * destPath, const size_t destPathSize, const bool append,
             const size_t begOffset, const size_t endOffset);

/*!
	int FileUtills_CopyPath(const char * srcPath, const size_t srcPathSize, const char * destPath, const size_t destPathSize, const bool recursive,
	       const bool rename, const bool abort_on_failure, const bool append, const size_t begOffset, const size_t endOffset)

	This function takes a given source path and copies it to the given dest path.

	This function supports files and directories.
	If you give a file as src and a directory as dest, the function WILL return an error.

	If the given src is a file, then this function acts as a wrapper to FileUtills_CopyFile(), and returns all of it's
	error codes.

	If the given src is a directory, then this function will copy the entire directory to the given dest, creating dest if
	necessary. If recursive is set to true, then the entire directory AND it's subdirectories will be copied.
	(The subdirectories will be created as needed, if a subdirectory already exists, then the data from src will be merged.)

	@pram recursive, if this is true, then this function will recursively copy all subdirectories from src. Merging / creating
	subdirectories as needed. Otherwise this function will only copy the top level directory. (Default)
	If src is a file, then this pram has no effect.

	@pram rename, if this is set to true, then this function will try to rename the file rather than copy it.
	otherwise a copy will be performed (Default).
	It should be noted that a rename is equivalent to calling CopyFile(), and then DeletePath() on the same source.
	(Minus the overhead and extra disk space use of actually copying the source first.) And that renaming a
	src will only work if the dest is on the same filesystem.
	In the event that rename fails, then a copy will be performed UNLESS abort_on_failure is set to true. In that case
	the function will abort imeadently.
	NOTE: Currently rename does nothing, as the RenamePath() function does not exist.

	@pram abort_on_failure, if this is set to true then this function will abort when the first failure is encountered.
	otherwise this function will try to continue with the remaining list of files and subdirectories. (Default)

	@pram append, this is only used if src is a file. (As this function acts as a wrapper to CopyFile() in that case,
	see FileUtills_CopyFile() for it's description. This function provides the same default value for this pram as CopyFile().)
	If src is a directory, this pram has no effect.

	@pram begOffset, this is only used if src is a file. (As this function acts as a wrapper to CopyFile() in that case,
	see FileUtills_CopyFile() for it's description. This function provides the same default value for this pram as CopyFile().)
	If src is a directory, this pram has no effect.

	@pram endOffset, this is only used if src is a file. (As this function acts as a wrapper to CopyFile() in that case,
	see FileUtills_CopyFile() for it's description. This function provides the same default value for this pram as CopyFile().)
	If src is a directory, this pram has no effect.

	Below are return codes for when src is a directory, if src is a file, then the return codes for this function are identical to
	FileUtills_CopyFile(). Please see FileUtills_CopyFile() for it's return codes.

	Returns COMMON_ERROR_SUCCESS on success.
	Returns -1 if the function was unable to create top level dest path and top level dest path does not exist.
	Returns -2 if the top level dest path exists and is a file or some other filesystem entry.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the host OS / Arch is unsupported.
	Returns -4 if the function could not get a directory listing.
	Returns -5 if the function could not get parent directory string.
	Returns -6 if the function was unable to copy all files. (Some files may have been copied however.)
	Returns -13 if FileUtills_IsFileOrDirectory() returns -3. (OS / Arch not supported.)
	Returns -14 if FileUtills_IsFileOrDirectory() returns -4. (A permissions error occurred.)
	Returns -15 if FileUtills_IsFileOrDirectory() returns -5. (The given path is empty.)
	Returns -16 if FileUtills_IsFileOrDirectory() returns -6. (A path component does not exist.)
	Returns -17 if FileUtills_IsFileOrDirectory() returns -7. (The path has a file in it and is not at the end. (I.e you are treating a file as a directory.))
	Returns COMMON_ERROR_UNKNOWN_ERROR if FileUtills_IsFileOrDirectory() returns -9. (All other errors.)
*/
int FileUtills_CopyPath(const char * srcPath, const size_t srcPathSize, const char * destPath, const size_t destPathSize, const bool recursive,
			 const bool rename, const bool abort_on_failure, const bool append, const size_t begOffset, const size_t endOffset);

/*!
        int FileUtills_MovePath(const char * srcPath, const size_t srcPathSize, const char * destPath, const size_t destPathSize, const bool overwrite)

        Acts as a wrapper for a call to CopyPath and DeletePath.
        The srcPath is copied to the destPath and then the srcPath is deleted.

        Returns COMMON_ERROR_SUCCESS on success.
        Returns -10 If an error occurs while accessing the src file.
        Returns -20 If dest already exists and overwriting is disabled.
        Returns -21 If dest already exists and can't be deleted. (overwrite = true)
        Returns -22 If an error occurs while accessing the dest file.
        Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED If an Implementation does not exist for your system.
        Returns COMMON_ERROR_IO_ERROR If an error occurs while moving data.
        Returns COMMON_ERROR_INVALID_ARGUMENT If an argument to the function is bad.
*/
int FileUtills_MovePath(const char * srcPath, const size_t srcPathSize, const char * destPath, const size_t destPathSize, const bool overwrite);

#ifdef __cplusplus
}	/* End of extern "C" */
#endif	/* __cplusplus. */

/* Include C++ header if needed. */
#ifdef __cplusplus
#include "FileUtills_CPP.h"
#endif	/* __cplusplus. */

#endif	/* FILEUTILLS_H */

/* End of FileUtills.h */
