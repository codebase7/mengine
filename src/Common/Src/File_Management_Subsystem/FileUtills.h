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

#ifndef FILEUTILLS
#define FILEUTILLS

// Engine Includes
#ifdef __win32
#include "..\BaseHeader.h"
#include "..\Error_Handler\Common_Error_Handler.h"
#include "..\Error_Handler\Common_Error_Handler_Internal.h"
#else
#include "../BaseHeader.h"
#include "../Error_Handler/Common_Error_Handler.h"
#include "../Error_Handler/Common_Error_Handler_Internal.h"
#endif

namespace FileUtills{

#ifdef _WIN32
// Define the Windows Directory seperator
#define DIR_SEP '\\'
#define HOME_DIR_SYMBOL '~'
// Define the minimal valid absolute directory path length.
/*
 * MINIMAL_VALID_ABSOLUTE_PATH_LENGTH is supposed to include the needed DIR_SEP for the root directory.
 * In addition it is supposed to be the minimal number of char(s) needed to represent a valid absolute path
 * to a root directory.
 * 
 * In windows "<Drive letter>:<DIR_SEP>" is minimal for an absolute path. (Root of given drive.)
 */
#define MINIMAL_VALID_ABSOLUTE_PATH_LENGTH 3
#else
// Define the Posix Directory Seperator.
#ifndef DIR_SEP
#define DIR_SEP '/'
#define HOME_DIR_SYMBOL '~'
#define Relative_Symbol "./"
/*
 * MINIMAL_VALID_ABSOLUTE_PATH_LENGTH is supposed to include the needed DIR_SEP for the root directory.
 * In addition it is supposed to be the minimal number of char(s) needed to represent a valid absolute path
 * to a root directory.
 * 
 * In linux "<DIR_SEP>" is minimal for an absolute path. (Root of the entire filesystem / chroot.)
 */
#define MINIMAL_VALID_ABSOLUTE_PATH_LENGTH 1
#endif
#endif

// Define the directory list structure
struct dirlist{
    size_t numOfEntries;		// Used to store the number of entries in the list array.
    std::vector<std::string> list;	// Used to store the directory's entry data.
    std::string path;			// Used to store the path of the directory that the entry list is about.
};

/*!
 * 	int FileUtills::GetUserProfileDirectoryPath(std::string & path)
 *
 * 	Fetches the user's profile directory from the enviorment, and stores
 * 	it in the given path argument. (Note: The given path argument will be
 * 	erased when this function is called. So take care not to leave something
 * 	in it you need.)
 *
 * 	If the function fails for any reason, path will be an empty string,
 * 	the returned error code and Common::commonLastErrorCode will be set
 * 	to the approiate error.
 */
int GetUserProfileDirectoryPath(std::string & path);

/*!
 * 	int FileUtills::GetCurrentWorkingDirectoryPath(std::string & path)
 *
 * 	Fetches the current working directory from the enviorment, and stores
 * 	it in the given path argument. (Note: The given path argument will be
 * 	erased when this function is called. So take care not to leave something
 * 	in it you need.)
 *
 * 	If the function fails for any reason, path will be an empty string,
 * 	the returned error code and Common::commonLastErrorCode will be set
 * 	to the approiate error.
 */
int GetCurrentWorkingDirectoryPath(std::string & path);

/*!
 * 	int FileUtills::GetExecDirectory(std::string & retStr)
 *
 * 	Replaces the contents of the given retStr argument with a NULL
 * 	terminated std::string that contains the path to the directory where the
 * 	executable is stored.
 *
 * 	If the function fails for any reason, the retStr argument will NOT be altered,
 * 	and the appropriate error will be returned to the caller.
 */
int GetExecDirectory(std::string & retStr);

/*!
        int getDirectory(const std::string & path, FileUtills::dirlist ** dirTree, const bool & cleanList)

        Lists the given directory's contents.

        Pram: path, path of directory to check.

        Pram: FileUtills::dirlist ** dirTree, pointer to a pointer to a
        FileUtills::dirlist structure that will contain the resulting
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
	FileUtills::dirlist structure with the given path's contents in this case.
	(Any previous structure pointed to by the dirTree pointer will be deallocated.)

        Otherwise this function will return the appropriate error, and dirTree's pointer will
        not be modified.
*/
int getDirectory(const std::string & path, dirlist ** dirTree, const bool & cleanList = false);

/*!
	int FileUtills::DoesExist(const std::string & path)

	Prams: @std::string path, path to check for existance on the filesystem.

	This function checks to see if given file or directory exists.

	This function is called by FileUtills::CheckPermissions() before runing permission checks.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns FILEUTILLS_ERROR_EXISTANT if file or directory exists on the system.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if file or directory does not exist on the system.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given path is empty.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given system is unsupported.
	Returns the approiate error in all other instances.
*/
int DoesExist(const std::string & path);

/*!
	FileUtills::IsFileOrDirectory(const std::string & path)

	Checks to see if a given path is a file or directory.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if the path exists but it is not a file or directory.
	Returns FILEUTILLS_ERROR_PATH_IS_A_FILE if the path is a file.
	Returns FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY if the path is a directory.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the given system is unsupported.
	Returns COMMON_ERROR_ACCESS_DENIED if a permissions error occurs.
	Returns COMMON_ERROR_INVALID_ARGUMENT if the given path is empty.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if a path componet does not exist.
	Returns FILEUTILLS_ERROR_ if the path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
	Returns the approiate error in all other instances.
*/
int IsFileOrDirectory(const std::string & path);

/*!
	int FileUtills::CheckParent(const std::string & path, const bool & read, const bool & write, const bool & exec)

	Acts as a wrapper to DoesExist and CheckPermissions
	Checks for the parent directory's existance in the path given.
	Also Checks to see if it is accessible. By default it checks for Read and Write access.
	(Optionaly it can check for execute permissions, and any combonation of the three. This
	function will return a COMMON_ERROR_INVALID_ARGUMENT error however if all of the permissions to check
	are false.)

	Ex. If this path is given: "/home/user/Homework.txt", this function will check and see if the "/home/user" parent
	directory exists, and if it is accessable.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if the directory exists and is accessible with the requested permissions.
	Returns COMMON_ERROR_ACCESS_DENIED if A permission error occurs.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if the parent directory does not exist.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the OS / Arch is not supported.
	Returns COMMON_ERROR_SYSTEM_SPECIFIC if a system specific / untranslated error occurs.
	Returns COMMON_ERROR_INTERNAL_ERROR if an engine error occurs.
	Returns COMMON_ERROR_UNKNOWN_ERROR if an unknown error occurs.
	Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown.
	Returns the approiate error in all other cases.
*/
int CheckParent(const std::string & path, const bool & read = true, const bool & write = true, const bool & exec = false);

/*!
	std::string FileUtills::GetParent(const std::string & path)

	Returns the parent directory for the given file.

	Gets the path exactly like FileUtills::CheckParent().

	Returns std::string with parent directory path if successful.
	Returns an empty string otherwise, and sets
	Common::commonLastErrorCode to the approiate error code.
*/
std::string GetParent(const std::string & path);

/*!
	int FileUtills::ResolvePath(const char * path, const size_t pathSize, char * retStr, size_t * retStrSize, const bool disableSymLinkResolution)

	Checks the path given, and converts it to a absolute path.

	Setting disableSymLinkResolution to true will disable resolving any symbolic link(s) if a
	symbolic link is encountered while resolving the given path(s). Setting
	disableSymLinkResolution to false will make this function resolve any
	symbolic link(s) that are encountered while resolving the given path(s).

	Returns COMMON_ERROR_SUCCESS if successfull, retStr and retStrSize will be altered in this
	case. (Any pre-existing c-string given to this function as retStr will be deallocated.)

	Otherwise the approiate error code is returned. (retStr and retStrSize will be unaltered in
	this instance.)
*/
int ResolvePath(const char * path, const size_t pathSize, char * retStr, size_t * retStrSize, const bool disableSymLinkResolution);

/*!
	int FileUtills::CreateDirectory(const std::string & directory, const bool & createRecursive)
	@pram : directory, path to create.
	@pram : createRecursive, if this is set to true, then this function will try to create the 
	parent directories of the given directory if they do not exist.

	This function attempts to create the given directory on the filesystem.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if directory creation was successful.
	Returns COMMON_ERROR_ACCESS_DENIED if permission is denied.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if this function is unsupported.
	Returns FILEUTILLS_ERROR_FILESYSTEM_FULL if the disk is full.
	Returns FILEUTILLS_ERROR_EXISTANT if the directory already exists.
	Returns the approiate error or COMMON_ERROR_UNKNOWN_ERROR if another error is encountered.
*/
int CreateDirectory(const std::string & directory, const bool & createRecursive = false);

/*!
	int FileUtills::CheckPermissions(const std::string & path, const bool & read, const bool & write, const bool & exec)

	Checks Permissions on the given file or directory. Also checks if the given file or directory
	actully exists first before checking other permissions. By default it will check for both read and
	write permissions. (Optionaly it can check for execute permissions, and any combonation of the three. This
	function will return a COMMON_ERROR_INVALID_ARGUMENT error however if all of the permissions to check
	are false.)

	Pram: path to directory or file to check.
	Pram: check for read permission. default is true.
	Pram: check for wrtie permission. default is true.
	Pram: check for execute permission. default is false.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if the directory exists and is accessible with the requested permissions.
	Returns COMMON_ERROR_ACCESS_DENIED if A permission error occurs.
	Returns FILEUTILLS_ERROR_NON_EXISTANT if the parent directory does not exist.
	Returns COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED if the OS / Arch is not supported.
	Returns COMMON_ERROR_SYSTEM_SPECIFIC if a system specific / untranslated error occurs.
	Returns COMMON_ERROR_INTERNAL_ERROR if an engine error occurs.
	Returns COMMON_ERROR_UNKNOWN_ERROR if an unknown error occurs.
	Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown.
	Returns the approiate error in all other cases.
*/
int CheckPermissions(const std::string & path, const bool & read = true, const bool & write = true, const bool & exec = false);

/*!
	int FileUtills::GetGigaFreespace(const std::string & path, size_t & result)

	Returns the remaining disk space in Gigabytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const std::string & path : volume / path to check.
	@pram size_t & result : The remaining space on the filesystem.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if successfull, result will contain the remaining space.
	Returns a Common namespace error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int GetGigaFreespace(const std::string & path, size_t & result);

/*!
	int FileUtills::GetFreespace(const std::string & path, size_t & result)

	Returns the remaining disk space in Megabytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const std::string & path : volume / path to check.
	@pram size_t & result : The remaining space on the filesystem.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if successfull, result will contain the remaining space.
	Returns a Common namespace error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int GetFreespace(const std::string & path, size_t & result);

/*!
	int FileUtills::GetKiloFreespace(const std::string & path, size_t & result)

	Returns the remaining disk space in Kilobytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const std::string & path : volume / path to check.
	@pram size_t & result : The remaining space on the filesystem.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if successfull, result will contain the remaining space.
	Returns a Common namespace error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int GetKiloFreespace(const std::string & path, size_t & result);

/*!
	int FileUtills::GetByteFreespace(const std::string & path, size_t & result)

	Returns the remaining disk space in Bytes (SI Unit) on the given disk.

	Note if an error occurs, result will be set to zero, and an error code will be returned.
	(Although result can also be set to zero if there really is no remaining disk space.)

	@pram const std::string & path : volume / path to check.
	@pram size_t & result : The remaining space on the filesystem.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns COMMON_ERROR_SUCCESS if successfull, result will contain the remaining space.
	Returns a Common namespace error if an error occurs. Size will be equal to zero in this
	case. To obtain more detailed info register an error hander before calling this function.
*/
int GetByteFreespace(const std::string & path, size_t & result);

/*!
	int FileUtills::DeletePath(const std::string & path, const bool & recursive)

	This function attempts to delete the given file or directory from the filesystem.

	By default this function will NOT delete recursively.
	If the given path is a non-empty directory, by default this function will throw an error.
	If the given path is an empty directory, however by default this function WILL delete it.

	Note: If while deleting rescursively, a file or subdirectory can't be deleted, this function will try to continue
	deleting any other files and subdirectories that can be deleted, but it will throw an error apon exit.

	The returned error code is always copied to Common::commonLastErrorCode.

	Returns 0 if successful.
	-1 if the user lacks permission to delete the path. (Or if recursively deleting a directory, a file or subdirectory could not be deleted.)
	-2 if the path does not exist. (Or if recursively deleting a directory, a file or subdirectory does not exist.)
	-3 if the function is not supported.
	-4 if a memory error occurs.
	-5 if an unknown error occurs. (An error other than a permissions error occured while deleting something.)
	-6 if the path is a non empty directory and recursive is set to false.
	-7 if while deleting recursively, the parent directory of a deleted directory could not be obtained. (I.e could not "go up a level in the directory tree.")
	-8 if while deleting recursively, there were files and or subdirectories that could not be deleted. (Some files may have been deleted however.)
*/
int DeletePath(const std::string & path, const bool & recursive = false);

/*!
        int FileUtills::CopyFile(const std::string & src, const std::string & dest, const bool & append,
                                   const streamsize & begOffset, const streamsize & endOffset)

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

        This function only works on FILES. Not directories. To copy a directory, call FileUtills::CopyPath().

        @pram src, path to the source file.
        @pram dest, path to the dest file.
        
        @pram append, Whether or not to append data to the dest file.
        (Note only applies if the dest file exists. If append is false, then the dest file will be overwritten.)
                                                                        
        @pram begOffset, Location in the source file to start copying data from.
        @pram endOffset, Location in the source file to stop copying data when it is reached.

        By default the entire file is copied and the dest file is overwritten.

        Note: This function does NOT make any attempt to preserve the destionation file if it already exists.

        Note: This function can return ANY error in the Common namespace error list, below is only an example
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
        Returns COMMON_ERROR_IO_ERROR if an I/O error occured while reading the source file.
        Returns COMMON::FILEUTILLS_PATH_IS_A_DIRECTORY if the given source file was a directory.
        Returns COMMON_ERROR_INVALID_ARGUMENT if the dest file was not given.
        Returns COMMON_ERROR_IO_ERROR if dest file could not be opened.
        Returns COMMON_ERROR_IO_ERROR if an I/O error occured while writing to the dest file.
        Returns FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY if the given dest file was a directory.
        Returns COMMON_ERROR_EXCEPTION_THROWN if an exception is thrown while copying data.
*/
int CopyFile(const std::string & src, const std::string & dest, const bool & append = false,
               const streamsize & begOffset = 0, const streamsize & endOffset = 0);

/*!
	int FileUtills::CopyPath(const std::string & src, const std::string & dest, const bool & recursive,
				    const bool & rename, const bool & abort_on_failure,
				    const bool & append, const streamsize & begOffset,
				    const streamsize & endOffset)

	This function takes a given source path and copies it to the given dest path.

	This function supports files and directories.
	If you give a file as src and a directory as dest, the function WILL return an error.

	If the given src is a file, then this function acts as a wrapper to FileUtills::CopyFile(), and returns all of it's
	error codes.

	If the given src is a directory, then this function will copy the entire directory to the given dest, creating dest if
	nessacarry. If recursive is set to true, then the entire directory AND it's subdirectories will be copied.
	(The subdirectories will be created as needed, if a subdirectory already exists, then the data from src will be merged.)

	@pram recursive, if this is true, then this function will recursively copy all subdirectories from src. Merging / creating
	subdirectories as needed. Otherwise this function will only copy the top level directory. (Default)
	If src is a file, then this pram has no effect.

	@pram rename, if this is set to true, then this function will try to rename the file rather than copy it.
	otherwise a copy will be performed (Default).
	It should be noted that a rename is equivelent to calling CopyFile(), and then DeletePath() on the same source.
	(Minus the overhead and extra disk space use of actually copying the source first.) And that renaming a
	src will only work if the dest is on the same filesystem.
	In the event that rename fails, then a copy will be performed UNLESS abort_on_failure is set to true. In that case
	the function will abort imeadently.
	NOTE: Currently rename does nothing, as the RenamePath() function does not exist.

	@pram abort_on_failure, if this is set to true then this function will abort when the first failure is encountered.
	otherwise this function will try to continue with the remaining list of files and subdirectories. (Default)

	@pram append, this is only used if src is a file. (As this function acts as a wrapper to CopyFile() in that case,
	see FileUtills::CopyFile() for it's description. This function provides the same default value for this pram as CopyFile().)
	If src is a directory, this pram has no effect.

	@pram begOffset, this is only used if src is a file. (As this function acts as a wrapper to CopyFile() in that case,
	see FileUtills::CopyFile() for it's description. This function provides the same default value for this pram as CopyFile().)
	If src is a directory, this pram has no effect.

	@pram endOffset, this is only used if src is a file. (As this function acts as a wrapper to CopyFile() in that case,
	see FileUtills::CopyFile() for it's description. This function provides the same default value for this pram as CopyFile().)
	If src is a directory, this pram has no effect.

	Below are return codes for when src is a directory, if src is a file, then the return codes for this function are identical to
	FileUtills::CopyFile(). Please see FileUtills::CopyFile() for it's return codes.

	Returns 0 on success.
	Returns -1 if the function was unable to create top level dest path and top level dest path does not exist.
	Returns -2 if the top level dest path exists and is a file or some other filesystem entry.
	Returns -3 if the host OS / Arch is unsupported.
	Returns -4 if the function could not get a directory listing.
	Returns -5 if the function could not get parent directory string.
	Returns -6 if the function was unable to copy all files. (Some files may have been copied however.)
	Returns -13 if FileUtills::IsFileOrDirectory() returns -3. (OS / Arch not supported.)
	Returns -14 if FileUtills::IsFileOrDirectory() returns -4. (A permissions error occured.)
	Returns -15 if FileUtills::IsFileOrDirectory() returns -5. (The given path is empty.)
	Returns -16 if FileUtills::IsFileOrDirectory() returns -6. (A path componet does not exist.)
	Returns -17 if FileUtills::IsFileOrDirectory() returns -7. (The path has a file in it and is not at the end. (I.e you are treating a file as a directory.))
	Returns -19 if FileUtills::IsFileOrDirectory() returns -9. (All other errors.)
*/
int CopyPath(const std::string & src, const std::string & dest, const bool & recursive = false,
	       const bool & rename = false, const bool & abort_on_failure = false,
	       const bool & append = false, const streamsize & begOffset = 0, const streamsize & endOffset = 0);

/*!
        int FileUtills::MovePath(const std::string & src, const std::string & dest, const bool & overwrite)

        Acts as a wrapper for a call to CopyPath and DeletePath.
        The src file is copied to the dest file and then the src file is deleted.

        Returns 0 on success.
        Returns -10 If an error occurs while accessing the src file.
        Returns -20 If dest already exists and overwriting is disabled.
        Returns -21 If dest already exists and can't be deleted. (overwrite = true)
        Returns -22 If an error occurs while accessing the dest file.
        Returns -3 If an Implementation does not exist for your system.
        Returns -4 If an error occurs while moving data.
        Returns -5 If an argument to the function is bad.
*/
int MovePath(const std::string & src, const std::string & dest, const bool & overwrite = false);

}


#endif

// End of FileUtills.h
