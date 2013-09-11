/*!
    Multiverse Engine Project 04/9/2013 Unit Tests Unit_Test_Common.h

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

#ifndef COMMON_UNIT_TESTS_H
#define COMMON_UNIT_TESTS_H

// Include headers from Common.
#include "../Common/Src/FileUtills.h"
#include "../Common/Src/Thread_Utils.h"

// Define FileUtills error messages structs.
const Error_Messages FileUtills_CopyFile_Error_Messages[] = {
    {-1, "A given offset was negative."},
	{-5, "The given begOffset is bigger than the given endOffset."},
	{-9, "The memory buffer could not be allocated."},
	{-10, "The source file was not given."},
	{-11, "The source file could not be opened."},
	{-12, "The beginning offset given is larger than the source file."},
	{-13, "The ending offset given is larger than the source file."},
	{-14, "An I/O error occured while reading the source file."},
	{-15, "A logical error occured while reading the source file."},
	{-16, "End of file was encountered unexpectedly. (I.e It was expected that the source file had more data in it.)"},
	{-17, "The given source file was a directory."},
	{-20, "The dest file was not given."},
	{-21, "Dest file could not be opened."},
	{-24, "An I/O error occured while writing to the dest file."},
	{-25, "A logical error occured while writing to the dest file."},
	{-27, "The given dest file was a directory."},
	{-33, "FileUtills::IsFileOrDirectory() returns -3. (OS / Arch not supported.)"},
	{-34, "FileUtills::IsFileOrDirectory() returns -4. (A permissions error occured.)"},
	{-35, "FileUtills::IsFileOrDirectory() returns -5. (The given path is empty.)"},
	{-36, "FileUtills::IsFileOrDirectory() returns -6. (A path componet does not exist.)"},
	{-37, "FileUtills::IsFileOrDirectory() returns -7. (The path has a file in it and is not at the end. (I.e you are treating a file as a directory.))"},
	{-39, "FileUtills::IsFileOrDirectory() returns -9. (All other errors.)"},
	{-99, "An exception was thrown while copying data."}
};

const Error_Messages FileUtills_CreateDirectory_Error_Messages[] = {
	{-1, "Permission denied."},
	{-2, "The parent directory does not exist and createRecursive is false."},
	{-3, "OS / Arch is unsupported."},
	{-4, "The disk is full."},
	{-5, "The directory already exists."},
	{-6, "Another error is encountered. (Unknown Error.)"}
};

const Error_Messages FileUtills_DeletePath_Error_Messages[] = {
	{-1, "Permission denied."},
	{-2, "The path does not exist. (Or if recursively deleting a directory, a file or subdirectory does not exist.)"},
	{-3, "OS / Arch is unsupported."},
	{-4, "A memory error occured. (Control loop out of bounds, execption thrown, etc.)"},
	{-5, "An error other than a permissions error occured while deleting something."},
	{-6, "The given path is a non empty directory and recursive deletion was disabled."},
	{-7, "While recursively deleting data, the parent directory of a deleted directory could not be obtained. (I.e could not \"go up a level in the directory tree.\")"},
	{-8, "While recursively deleting data, there were files and or subdirectories that could not be deleted. (Some files may have been deleted however.)"}
};

const Error_Messages FileUtills_IsFileOrDirectory_Error_Messages[] = {
    {-3, "OS / Arch is unsupported."},
    {-4, "A permissions error occured."},
    {-5, "The given path was empty."},
    {-6, "A path componet does not exist."},
    {-7, "The given path has a file in it and is not at the end. (I.e you are treating a file as a directory.)"}
};

// Define error functions.
const char * Get_FileUtills_CreateDirectory_Error_Message(const short & error_code);
const char * Get_FileUtills_CopyFile_Error_Message(const short & error_code);
const char * Get_FileUtills_DeletePath_Error_Message(const short & error_code);

// Define fileutills test functions.
bool Verify_Files(const std::string & src, const std::string & dest, const size_t & begOffset, const size_t & endOffset);
short Create_Temp_Files(const short & filename_length, const std::string & data_to_put_in_temp_files,
			std::vector<std::string> & fileList, const short & number_of_files_to_create = 0);
short indvidual_file_copy_test(std::vector<std::string> & fileList);
short random_length_copying_test(std::vector<std::string> & fileList);
short recursive_directory_copy_test(std::vector<std::string> & fileList);
short fileutills_cleanup(std::vector<std::string> & fileList);
short unit_test_fileutills_main();

// Define thread_utils test structs.
struct return_me
{
        bool cont;
        void * object;
        short rc;
};

// Define thread_utils test functions.
void Hacky_Delay();
void *Test_Function_1(void * dummy);
void *Test_Function_Mutex_Lock(void * dummy);
void *Test_Function_Condition_Lock(void * dummy);
void *Test_Function_Condition_Wait_Lock(void * dummy);
Common::Thread_Utils::Thread * Create_NONE_UNSUPPORTED_Thread_Class();
void Output_All_Supported_Threading_Libraries();
void Basic_Thread_Test();
void Test_Select_Library_Perferred_Library_Setting();
bool Test_Thread_Support(Common::Thread_Utils::Library_Support_Status & our_requirements,
			 const Common::Thread_Utils::Library_Support_Status * lib_status);
bool Test_Mutex_Support(Common::Thread_Utils::Library_Support_Status & our_requirements,
			const Common::Thread_Utils::Library_Support_Status * lib_status);
bool Test_Condition_Variable_Support(Common::Thread_Utils::Library_Support_Status & our_requirements,
				     const Common::Thread_Utils::Library_Support_Status * lib_status);
void Library_Test(const Common::LibraryID & lib);
int unit_test_thread_utils_main();

#endif

// End of Unit_Test_Common.h
