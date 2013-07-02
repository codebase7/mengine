/*!
    Multiverse Engine Project 04/12/2011 FileUtills FileUtills.h
    Yes we are reinventing the wheel here, go with it.

    Copyright (C) 2013 Multiverse Engine Project

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
#include "BaseHeader.h"

namespace FileUtills{

#ifdef _WIN32
// Define the Windows Directory seperator
#define DIR_SEP = '\\'
#else
// Define the Posix Directory Seperator.
#ifndef DIR_SEP
#define DIR_SEP '/'
#define Relative_Symbol "./"
#endif
#endif

// Define the directory list structure
struct dirlist{
    long int numOfEntries; 	            // Used to store the number of entries in the list array.
    std::vector<std::string> list;	    // Used to store the directory's entry data.
    std::string path;	                // Used to store the path of the directory that the entry list is about.
    Panic::ERROR error;		            // Used to store an errorcode if one occurs.
};

/*!
      FileUtills::dirlist * getDirectory(const std::string & path)

      Lists the given directory's contents.

      Pram: path of directory to check.

      Returns a pointer to a dirlist if successfull.
      Returns NULL if an error occurs.
*/
dirlist * getDirectory(const std::string & path);

/*!
      int FileUtills::DoesExist(const std::string & Filename, Panic::ERROR & error)
      Prams: @std::string Filename

      Checks to see if given file or directory exists.

      This function is called by FileUtills::CheckPermissions() before runing permission checks.

      This function uses the Panic::ERROR class.

      Returns 0 if file or directory exists on the system.
      Returns -1 if file or directory does not exist on the system.
      Returns -2 if an error occurs, call ReturnLastError() on the error instance to get details.
      Note it will also return -2 if the function does not have an implementation for your OS / arch.
*/
int DoesExist(const std::string & Filename, Panic::ERROR & error);

/*!
      int FileUtills::DoesExist(const std::string & Filename)
      Prams: @std::string Filename

      Checks to see if given file or directory exists.

      This function is called by FileUtills::CheckPermissions() before runing permission checks.

      Returns 0 if file or directory exists on the system.
      Returns -1 if file or directory does not exist on the system.
      Returns -2 if an error occurs.
      Note it will also return -2 if the function does not have an implementation for your OS / arch.
*/
int DoesExist(const std::string & Filename);

/*!
        FileUtills::IsFileOrDirectory(const std::string & path)

        Checks to see if a given path is a file or directory.

        Returns 0 if the path exists but it is not a file or directory.
        Returns 1 if the path is a file.
        Returns 2 if the path is a directory.
        Returns -3 if the given system is unsupported.
        Returns -4 if a permissions error occurs.
        Returns -5 if the given path is empty.
        Returns -6 if a path componet does not exist.
        Returns -7 if the path has a file in it and is not at the end. (I.e you are treating a file as a directory.)
        Returns -9 on all other errors.
*/
int IsFileOrDirectory(const std::string & path);

/*!
        int FileUtills::CheckParent(const std::string & path, bool read, bool write)

        Acts as a wrapper to DoesExist and CheckPermissions
        Checks for the parent directory's existance in the path given.
        Also Checks to see if it is accessible. By default it checks for Read and Write access.

        Ex. This path is given "/home/user/Homework.txt"  this function will check and see if the "/home/user" parent
        directory exists, and if it is accessable.

        Returns 0 if the directory exists and is accessible with the requested permissions.
        Returns -1 if A permission error occurs
        Returns -2 if the parent directory does not exist.
        Returns -3 if the OS / Arch is not supported.
        Returns -5 if an unknown error occurs.
*/
int CheckParent(const std::string & path, bool read = true, bool write = true);

/*!
        std::string FileUtills::GetParent(const std::string & path)

        Returns the parent directory for the given file.

        Gets the path exactly like FileUtills::CheckParent().

        Returns std::string with parent directory path if successful.
        Returns an empty string otherwise.
*/
std::string GetParent(const std::string & path);

/*!
        std::string FileUtills::CheckPathType(const std::string & path)

        Checks the path given, and converts it to a absolute path.

        Returns absoulte path on success.
        Returns a zero length string otherwise.
*/
std::string CheckPathType(const std::string & path);

/*!
          int FileUtills::CreateDirectory(const std::string & directory, Panic::ERROR & error, bool createRecursive)
          Prams : @std::string directory

          Creates given directory on the filesystem. if a parent directory does not exist
          it will create it.

          This function uses the Panic::ERROR class.

          Returns 0 if directory creation was successful.
          Returns -1 if permission is denied.
          Returbs -2 if the parent directory does not exist and createRecursive is false.
          Returns -3 if this function is unsupported.
          Returns -4 if the disk is full.
          Returns -5 if the directory already exists.
          Returns -6 if another error is encountered.
*/
int CreateDirectory(const std::string & directory, Panic::ERROR & error, bool createRecursive = false);

/*!
          int FileUtills::CheckPermissions(const std::string & path, Panic::ERROR & error, bool read, bool write)

          Checks Permissions on the given file or directory. Also checks if the given file or directory
          actully exists first before checking other permissions. By default it will check for both read and
          write permissions.

          This function uses the Panic::ERROR class.

          Pram: path to directory or file to check.
          Pram: error handler instance.
          Pram: check for read permission. default is true.
          Pram: check for wrtie permission. default is true.

          Return: 0 if all permission checks pass.
          Return: -1 if permission check fails.
          Return: -2 if the file does not exist.
          Return: -3 if a diffrent error occurs. Call ReturnLastError for details.
*/
int CheckPermissions(const std::string & path, Panic::ERROR & error, bool read = true, bool write = true);

/*!
          int FileUtills::CheckPermissions(const std::string & path, bool read, bool write)
          Checks Permissions on the given file or directory. Also checks if the given file or directory
          actully exists first before checking other permissions. By default it will check for both read and
          write permissions.

          Pram: path to directory or file to check.
          Pram: check for read permission. default is true.
          Pram: check for wrtie permission. default is true.

          Return: 0 if all permission checks pass.
          Return: -1 if permission check fails.
          Return: -2 if the file does not exist.
          Return: -3 if a diffrent error occurs.
*/
int CheckPermissions(const std::string & path, bool read = true, bool write = true);

/*!
          short FileUtills::GetFreespace(const std::string & path, size_t & result)
          Returns the remaining disk space in Megabytes (SI Unit) on the given disk.

          Note if an error occurs, result will be set to zero, and an error code will be returned.
          (Although result can also be set to zero if there really is no remaining disk space.)

          std::string path : volume / path to check.
          Returns 0 if successfull, result will contain the remaining space.
          Returns -1 if an input / output error occurs.
          Returns -2 if a permission error is found.
          Returns -3 if function is unimplemented on the target platform.
          Returns -4 if too many symbolic links are encountered.
          Returns -5 if the given path is too long for the filesystem to handle.
          Returns -6 if the given path does not exist.
          Returns -7 if the filesystem is unsupported.
          Returns -8 if a part of the path is not a valid directory.
          Returns -9 if some data was too big to returned.
          Returns -10 if we run out of kernel memory.
          Returns -11 for all other errors.
*/
short GetFreespace(const std::string & path, size_t & result);

/*!
          short FileUtills::GetKiloFreespace(const std::string & path, size_t & result)
          Returns the remaining disk space in Kilobytes (SI Unit) on the given disk.

          Note if an error occurs, result will be set to zero, and an error code will be returned.
          (Although result can also be set to zero if there really is no remaining disk space.)

          std::string path : volume / path to check.
          Returns 0 if successfull, result will contain the remaining space.
          Returns -1 if an input / output error occurs.
          Returns -2 if a permission error is found.
          Returns -3 if function is unimplemented on the target platform.
          Returns -4 if too many symbolic links are encountered.
          Returns -5 if the given path is too long for the filesystem to handle.
          Returns -6 if the given path does not exist.
          Returns -7 if the filesystem is unsupported.
          Returns -8 if a part of the path is not a valid directory.
          Returns -9 if some data was too big to returned.
          Returns -10 if we run out of kernel memory.
          Returns -11 for all other errors.
*/
short GetKiloFreespace(const std::string & path, size_t & result);

/*!
          short FileUtills::GetByteFreespace(const std::string & path, size_t & result)
          Returns the remaining disk space in Bytes (SI Unit) on the given disk.

          Note if an error occurs, result will be set to zero, and an error code will be returned.
          (Although result can also be set to zero if there really is no remaining disk space.)

          std::string path : volume / path to check.
          Returns 0 if successfull, result will contain the remaining space.
          Returns -1 if an input / output error occurs.
          Returns -2 if a permission error is found.
          Returns -3 if function is unimplemented on the target platform.
          Returns -4 if too many symbolic links are encountered.
          Returns -5 if the given path is too long for the filesystem to handle.
          Returns -6 if the given path does not exist.
          Returns -7 if the filesystem is unsupported.
          Returns -8 if a part of the path is not a valid directory.
          Returns -9 if some data was too big to returned.
          Returns -10 if we run out of kernel memory.
          Returns -11 for all other errors.
*/
short GetByteFreespace(const std::string & path, size_t & result);

/*!
          short FileUtills::GetGigaFreespace(const std::string & path, size_t & result)
          Returns the remaining disk space in Gigabytes (SI Unit) on the given disk.

          Note if an error occurs, result will be set to zero, and an error code will be returned.
          (Although result can also be set to zero if there really is no remaining disk space.)

          std::string path : volume / path to check.
          Returns 0 if successfull, result will contain the remaining space.
          Returns -1 if an input / output error occurs.
          Returns -2 if a permission error is found.
          Returns -3 if function is unimplemented on the target platform.
          Returns -4 if too many symbolic links are encountered.
          Returns -5 if the given path is too long for the filesystem to handle.
          Returns -6 if the given path does not exist.
          Returns -7 if the filesystem is unsupported.
          Returns -8 if a part of the path is not a valid directory.
          Returns -9 if some data was too big to returned.
          Returns -10 if we run out of kernel memory.
          Returns -11 for all other errors.
*/
short GetGigaFreespace(const std::string & path, size_t & result);

/*!
        int FileUtills::DeletePath(const std::string & path, bool recursive)

        Deletes the file or directory given by path.

        Returns 0 if successful
        -1 if the user lacks permission to remove the path.
        -2 if the path does not exist.
        -3 if the function is not supported.
        -4 if a memory error occurs.
        -5 if an unknown error occurs.
        -6 if the path is a non empty directory and recursive is set to false.
*/
int DeletePath(const std::string & path, bool recursive = false);

/*!
        int FileUtills::CopyFile(const std::string & src, const std::string & dest, bool append, size_t begOffset, size_t endOffset)

        Copies endOffset bytes starting at begOffset, from source file to dest file.

        By default the entire file is copied.

        Note: This function expects that dest is the file path to copy to not the parent directory.

        Returns 0 on success.
        -1 on Source permission error.
        -10 on destiation directory permission error.
        -2 if source does not exist.
        -20 if destiontion directory does not exist.
        -21 if the destionation path / file already exists.
        -3 if the function is not supported.
        -4 if a memory error occurs.
        -5 if an unknown error occurs.
        -6 if copy fails.
*/
int CopyFile(const std::string & src, const std::string & dest, bool append = false, size_t begOffset = 0, size_t endOffset = 0);

/*!
        int FileUtills::MoveFile(const std::string & src, const std::string & dest, bool overwrite)

        Acts as a wrapper for a call to CopyFile and DeletePath.
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
int MoveFile(const std::string & src, const std::string & dest, bool overwrite = false);

}


#endif

// End of FileUtills.h
