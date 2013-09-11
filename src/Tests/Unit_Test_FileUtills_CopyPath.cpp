/*!
    Basic Test for FileUtills::CopyPath(). 29/8/2013

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

#include "Unit_Tests.h"

const char * Get_FileUtills_CreateDirectory_Error_Message(const short & error_code)
{
        // Init vars.
        const char * result = NULL;										// Result given to caller.
        const size_t length = (sizeof(FileUtills_CreateDirectory_Error_Messages) / sizeof(Error_Messages));	// Length of array filled in by the compiler. (Provided it optimizes anything.)

        // Error code list below, should match function description.
        for (size_t x = 0; x < length; x++)
        {
                // Check and see if the error code matches.
                if (FileUtills_CreateDirectory_Error_Messages[x].error_code == error_code)
                {
                        // Return error message.
                        return FileUtills_CreateDirectory_Error_Messages[x].message;
                }
        }

        // If we get here and result is still NULL, then the error code is unknown.
        if (result == NULL)
        {
                result = UNKNOWN_ERROR;
        }

        // Exit function.
        return result;
}

const char * Get_FileUtills_CopyFile_Error_Message(const short & error_code)
{
        // Init vars.
        const char * result = NULL;									// Result given to caller.
        const size_t length = (sizeof(FileUtills_CopyFile_Error_Messages) / sizeof(Error_Messages));	// Length of array filled in by the compiler. (Provided it optimizes anything.)

        // Error code list below, should match function description.
        for (size_t x = 0; x < length; x++)
        {
                // Check and see if the error code matches.
                if (FileUtills_CopyFile_Error_Messages[x].error_code == error_code)
                {
                        // Return error message.
                        return FileUtills_CopyFile_Error_Messages[x].message;
                }
        }

        // If we get here and result is still NULL, then the error code is unknown.
        if (result == NULL)
        {
                result = UNKNOWN_ERROR;
        }

        // Exit function.
        return result;
}

const char * Get_FileUtills_DeletePath_Error_Message(const short & error_code)
{
        // Init vars.
        const char * result = NULL;									// Result given to caller.
        const size_t length = (sizeof(FileUtills_DeletePath_Error_Messages) / sizeof(Error_Messages));	// Length of array filled in by the compiler. (Provided it optimizes anything.)

        // Error code list below, should match function description.
        for (size_t x = 0; x < length; x++)
        {
                // Check and see if the error code matches.
                if (FileUtills_DeletePath_Error_Messages[x].error_code == error_code)
                {
                        // Return error message.
                        return FileUtills_DeletePath_Error_Messages[x].message;
                }
        }

        // If we get here and result is still NULL, then the error code is unknown.
        if (result == NULL)
        {
                result = UNKNOWN_ERROR;
        }

        // Exit function.
        return result;
}

const char * Get_FileUtills_IsFileOrDirectory_Error_Message(const short & error_code)
{
        // Init vars.
        const char * result = NULL;									// Result given to caller.
        const size_t length = (sizeof(FileUtills_IsFileOrDirectory_Error_Messages) / sizeof(Error_Messages));	// Length of array filled in by the compiler. (Provided it optimizes anything.)

        // Error code list below, should match function description.
        for (size_t x = 0; x < length; x++)
        {
                // Check and see if the error code matches.
                if (FileUtills_IsFileOrDirectory_Error_Messages[x].error_code == error_code)
                {
                        // Return error message.
                        return FileUtills_IsFileOrDirectory_Error_Messages[x].message;
                }
        }

        // If we get here and result is still NULL, then the error code is unknown.
        if (result == NULL)
        {
                result = UNKNOWN_ERROR;
        }

        // Exit function.
        return result;
}

bool Verify_Files(const std::string & src, const std::string & dest, const size_t & begOffset, const size_t & endOffset)
{
        // Init vars.
        bool result = false;			    // Used to store result of function.
        short file_utills_result = 0;       // Used to store return codes from FileUtills::IsFileOrDirectory().
        fstream original_file;			    // Used to compare copied files.
        fstream dup_file;			        // Used to compare copied files.
        streamsize original_file_size = 0;	// Used to compare the file sizes.

        // Do some checks on those args.
        if (src.size() <= 0)
        {
                std::cout << "ERROR: No original file path given.\n\n";
        }
        else
        {
                // Check to see if src is a directory.
                file_utills_result = FileUtills::IsFileOrDirectory(src);
                if (file_utills_result == 2)
                {
                        // Source is a directory it does not need to be verified.
                        result = true;
                }
                else
                {
                        // Check to see if the source is a file.
                        if ((file_utills_result == 1) || (file_utills_result == 0))
                        {
                                if (dest.size() <= 0)
                                {
                                        std::cout << "ERROR: No copied file path given.\n\n";
                                }
                                else
                                {
                                        if ((begOffset >= endOffset) && ((begOffset != 0) && (endOffset != 0)))		// begOffset must be smaller than endOffset, unless both are equal to zero.
                                        {
                                                // Invalid offsets.
                                                std::cout << "ERROR: Invalid offsets: begOffset = " << begOffset << ". endOffset = " << endOffset << ".\n\n";
                                        }
                                        else
                                        {
                                                // OK, now we must verify that the file was copied correctly, open both files.
                                                original_file.open(src.c_str(), ios::in | ios::binary);
                                                if (!original_file.is_open())
                                                {
                                                        // Could not open original_file.
                                                        std::cout << "ERROR: Could not open original file: " << src << " for reading.\n";
                                                        std::cout << "Skipping file, please verifiy the file manually.\n\n";
                                                        std::cout.flush();
                                                }
                                                else
                                                {
                                                        dup_file.open(dest.c_str(), ios::in | ios::binary);
                                                        if (!dup_file.is_open())
                                                        {
                                                                // Could not open dup_file.
                                                                std::cout << "ERROR: Could not open copied file: " << dest << " for reading.\n";
                                                                std::cout << "Skipping file, please verifiy the file manually.\n\n";
                                                                std::cout.flush();
                                                        }
                                                        else
                                                        {
                                                                // Get file lengths.
                                                                original_file.seekg(0, ios::end);
                                                                dup_file.seekg(0, ios::end);

                                                                // Check the files to see if they match the given offsets.
                                                                if (endOffset > 0)
                                                                {
                                                                        // Original file must contain the copied file's data, and the copied file's size must match the difference of endOffset and begOffset.
                                                                        if (((unsigned)original_file.tellg() < endOffset) || ((unsigned)dup_file.tellg() != (endOffset - begOffset)))
                                                                        {
                                                                                // File sizes do not match.
                                                                                std::cout << "ERROR: File sizes do not match.\n\n";
                                                                                std::cout.flush();
                                                                        }
                                                                        else
                                                                        {
                                                                                result = true;
                                                                        }
                                                                }
                                                                else	// If the end offset is zero, we assume that the beginning offset is zero as well, so we check the entire original file.
                                                                {
                                                                        if (original_file.tellg() != dup_file.tellg())
                                                                        {
                                                                                // File sizes do not match.
                                                                                std::cout << "ERROR: File sizes do not match.\n\n";
                                                                                std::cout.flush();
                                                                        }
                                                                        else
                                                                        {
                                                                                result = true;
                                                                        }
                                                                }
                                                                if (result)
                                                                {
                                                                        // Unset result.
                                                                        result = false;

                                                                        // Copy the original file size if we need it.
                                                                        if (endOffset <= 0)
                                                                        {
                                                                              original_file_size = original_file.tellg();
                                                                        }

                                                                        // Move back to the beginning offset in the files and do a compariasion.
                                                                        original_file.seekg(begOffset, ios::beg);
                                                                        dup_file.seekg(0, ios::beg);

                                                                        // If the endOffset is greater than zero check for offsets.
                                                                        if (endOffset > 0)
                                                                        {
                                                                                // Begin file data compare loop.
                                                                                for (size_t y = 0; y < (endOffset - begOffset); y++)
                                                                                {
                                                                                        // Check data char by char.
                                                                                        if (original_file.get() != dup_file.get())
                                                                                        {
                                                                                                // Data mismatch.
                                                                                                std::cout << "ERROR: Data in copied file does not match data in original_file.\n\n";
                                                                                                std::cout.flush();
                                                                                                break;
                                                                                        }
                                                                                        if ((y + 1) >= (endOffset - begOffset))
                                                                                        {
                                                                                                result = true;
                                                                                        }
                                                                                }
                                                                        }
                                                                        else	// Check entire file.
                                                                        {
                                                                                for (streamsize y = 0; y < original_file_size; y++)
                                                                                {
                                                                                        // Check data char by char.
                                                                                        if ((original_file.get()) != (dup_file.get()))
                                                                                        {
                                                                                                // Data mismatch.
                                                                                                std::cout << "ERROR: Data in copied file does not match data in original_file.\n\n";
                                                                                                std::cout.flush();
                                                                                                break;
                                                                                        }
                                                                                        if ((y + 1) >= original_file_size)
                                                                                        {
                                                                                                result = true;
                                                                                        }
                                                                                }
                                                                        }
                                                                }

                                                                // Close dup_file.
                                                                if (dup_file.is_open())
                                                                {
                                                                        dup_file.close();
                                                                }
                                                        }

                                                        // Close original file.
                                                        if (original_file.is_open())
                                                        {
                                                                original_file.close();
                                                        }
                                                }
                                        }
                                }
                        }
                        else
                        {
                                // An error was returned from FileUtills::IsFileOrDirectory().
                                std::cout << "An error was returned from FileUtills::IsFileOrDirectory(): " << file_utills_result << ".\n";
                        }
                }
        }

        // Exit function.
        return result;
}

short Create_Temp_Files(const short & filename_length, const std::string & data_to_put_in_temp_files,
			std::vector<std::string> & fileList, const short & number_of_files_to_create)
{
        // Init vars.
        short result = 0;			// Used to return a result to the caller.
        int failure_count = 0;			// Used to abort file creation loops.
        std::string src_path = "";		// Used to create, copy, and delete files.
        fstream output;				// Used to create temp files.

        // OK Generate a random directory name.
        std::cout << "Creating a temp directory in the current working directory to store files for this test program, please wait.\n";
        std::cout.flush();
        while (src_path.size() == 0)
        {
                if (filename_length > 0)
                {
                        src_path = DataProcess::GenerateUID(filename_length);
                }
                else
                {
                        src_path = DataProcess::GenerateUID(5);
                }
                if (src_path.size() <= 0)
                {
                        // Could not create temp directory name.
                        std::cout << "Could not create temp directory name.\n";
                        std::cout.flush();
                        failure_count++;
                        if (failure_count > MAX_FAILURES)
                        {
                                // Bailout.
                                break;
                        }
                        else
                        {
                                // Output number of remaining failures.
                                std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                std::cout.flush();
                        }
                }
                else
                {
                        // Call FileUtills::CreateDirectory().
                        result = FileUtills::CreateDirectory(src_path);
                        if (result != 0)
                        {
                                // Get error code.
                                std::cout << "FileUtills::CreateDirectory() returned error code: " << result << ", "
                                << Get_FileUtills_CreateDirectory_Error_Message(result) << '\n';
                                std::cout.flush();

                                // Erase src_path.
                                src_path.clear();

                                // Update failure_count.
                                failure_count++;
                                if (failure_count > MAX_FAILURES)
                                {
                                        // Bailout.
                                        break;
                                }
                                else
                                {
                                        // Output number of remaining failures.
                                        std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                        std::cout.flush();
                                }
                        }
                        else
                        {
                                // Push the path into the vector.
                                fileList.push_back(src_path);
                        }
                }
        }

        // Check and see if we can continue.
        if (src_path.size() > 0)
        {
                // Create files.
                std::cout << "Creating inital temp files for this test program, please wait.\n";
                std::cout.flush();
                for (short x = 0; x < number_of_files_to_create; x++)
                {
                      // OK Generate a random file name.
                      if (filename_length > 0)
                      {
                                src_path = fileList[0] + DIR_SEP + DataProcess::GenerateUID(filename_length);
                      }
                      else
                      {
                                src_path = fileList[0] + DIR_SEP + DataProcess::GenerateUID(5);
                      }
                      if (src_path.size() <= 0)
                      {
                                // Could not create temp file name.
                                std::cout << "Could not create temp filename.\n";
                                std::cout.flush();
                                failure_count++;
                                x--;		// Decrement x to try again.
                                if (failure_count > MAX_FAILURES)
                                {
                                        // Bailout.
                                        break;
                                }
                                else
                                {
                                        // Output number of remaining failures.
                                        std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                        std::cout.flush();
                                }
                      }
                      else
                      {
                              // Copy the path into the vector.
                              fileList.push_back(src_path);

                              // Now use the file name to create a file.
                              output.open(src_path.c_str(), ios::out | ios::binary | ios::trunc);
                              if (!output.is_open())
                              {
                                      // Could not open output file.
                                      std::cout << "Error could not open temp file.\n";
                                      std::cout.flush();
                                      failure_count++;
                                      x--;		// Decrement x to try again.
                                      if (failure_count > 3)
                                      {
                                            // Bailout.
                                            break;
                                      }
                                      else
                                      {
                                            // Output number of remaining failures.
                                            std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                            std::cout.flush();
                                      }
                              }
                              else
                              {
                                      // Output something.
                                      output << data_to_put_in_temp_files << '\n';
                                      output.flush();

                                      // Close the output file.
                                      if (output.is_open())
                                      {
                                            output.close();
                                      }
                              }
                      }

                      // Output the remaining files to create.
                      std::cout << "Number of temp files remaining to create: " << (number_of_files_to_create - (x + 1)) << ".\n";
                }
        }

        // Check failure_count.
        if (failure_count > 3)
        {
                std::cout << "TEST FAILURE.\n";
                std::cout << "Maximum failure limit reached, Test aborted.\n";
                std::cout.flush();
                result = -9;
        }

        // Exit function.
        return result;
}

short indvidual_file_copy_test(std::vector<std::string> & fileList)
{
        // Init vars.
        short result = 0;                   // Used to return a result to the caller.
        short file_utills_result = 0;       // Used to store results from FileUtills::IsFileOrDirectory().
        int failure_count = 0;			    // Used to abort file creation loops.
        std::string src_path = "";	    	// Used to create, copy, and delete files.
        std::string dest_path = "";	    	// Used to copy and delete files.
        fstream original_file;		    	// Used to compare copied files.
        fstream dup_file;			        // Used to compare copied files.
        std::vector<std::string> tempList;	// Used to construct a new fileList.

        // Check size of fileList.
        if (fileList.size() > 0)
        {
                // OK, now start copy loop.
                for (size_t x = 0; x < fileList.size(); x++)
                {
                        // Check for a directory.
                        file_utills_result = FileUtills::IsFileOrDirectory(fileList[x]);
                        if ((file_utills_result != 2) && ((file_utills_result == 0) || (file_utills_result == 1)))
                        {
                                // OK Generate a random file name.
                                dest_path.clear();		// Erase dest_path.
                                dest_path = fileList[0] + DIR_SEP + DataProcess::GenerateUID(fileList[x].size());
                                if (dest_path.size() <= 0)
                                {
                                        // Could not create temp file name.
                                        std::cout << "Could not create temp filename.\n";
                                        std::cout.flush();
                                        failure_count++;
                                        x--;		// Decrement x to try again.
                                        if (failure_count > 3)
                                        {
                                              // Bailout.
                                              break;
                                        }
                                        else
                                        {
                                              // Output number of remaining failures.
                                              std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                              std::cout.flush();
                                        }
                                        continue;
                                }

                                // Call FileUtills::CopyPath().
                                result = FileUtills::CopyPath(fileList[x], dest_path, false);
                                if (result != 0)
                                {
                                        // Report error code.
                                        std::cout << "ERROR in individual file copy test, FileUtills::CopyFile() returned error code: " << result << ".\n";
                                        std::cout << Get_FileUtills_CopyFile_Error_Message(result) << '\n';
                                        std::cout.flush();
                                        failure_count++;
                                        x--;		// Decrement x to try again.
                                        if (failure_count > 3)
                                        {
                                              // Bailout.
                                              break;
                                        }
                                        else
                                        {
                                              // Output number of remaining failures.
                                              std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                              std::cout.flush();
                                        }
                                }
                                else
                                {
                                        // Copy the new file name to the tempList.
                                        tempList.push_back(dest_path);

                                        // Tell user we are comparing the files.
                                        std::cout << "Comparing original file " << fileList[x] << " to copied file " << dest_path << ".\n";
                                        std::cout << "Running test: ";
                                        std::cout.flush();

                                        // Call Verify_Files().
                                        if (Verify_Files(fileList[x], dest_path, 0, 0))
                                        {
                                                // Test passed.
                                                std::cout << "Result: PASS\n";
                                                std::cout.flush();
                                        }
                                        else
                                        {
                                                // Test failed.
                                                std::cout << "Result: FAILURE\n";
                                                std::cout.flush();
                                                failure_count++;
                                                x--;		// Decrement x to try again.
                                                if (failure_count > 3)
                                                {
                                                      // Bailout.
                                                      break;
                                                }
                                                else
                                                {
                                                      // Output number of remaining failures.
                                                      std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                      std::cout.flush();
                                                }
                                        }
                                }
                        }
                        else
                        {
                                // Check for error.
                                if (file_utills_result < 0)
                                {
                                        std::cout << "FileUtills::IsFileOrDirectory() returned an error: " << file_utills_result << ".\n";
                                        std::cout.flush();
                                        failure_count++;
                                        x--;		// Decrement x to try again.
                                        if (failure_count > 3)
                                        {
                                              // Bailout.
                                              break;
                                        }
                                        else
                                        {
                                              // Output number of remaining failures.
                                              std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                              std::cout.flush();
                                        }
                                }
                        }
                }

                // OK, copy any created filenames from tempList to fileList.
                for (size_t x = 0; x < tempList.size(); x++)
                {
                        // Copy data.
                        fileList.push_back(tempList[x]);
                }

                // Clear tempList.
                tempList.clear();

                // Check failure_count.
                if (failure_count > 3)
                {
                        std::cout << "TEST FAILURE.\n";
                        std::cout << "Maximum failure limit reached, Test aborted.\n";
                        std::cout.flush();
                        result = -9;
                }
        }

        // Exit function.
        return result;
}

short random_length_copying_test(std::vector<std::string> & fileList)
{
        // Init vars.
        short result = 0;                   // Used to return a result to the caller.
        short file_utills_result = 0;       // Used to store results from FileUtills::IsFileOrDirectory().
        int failure_count = 0;			    // Used to abort file creation loops.
        streamsize original_file_size = 0;	// Used to compare the file sizes.
        streamsize begOffset = 0;			// Used to hold the randomly generated begOffset.
        streamsize endOffset = 0;		    // Used to hold the randomly generated endOffset.
        streamsize previous_begOffset = 0;	// Used to hold the previously generated begOffset.
        streamsize previous_endOffset = 0;	// Used to hold the previously generated endOffset.
        streamsize swap = 0;			    // Used if the generated offsets are reversed to swap them.
        size_t number_of_files_to_copy = 5;	// Used to hold the real number of files tested. (In case the fileList vector has less than five elements in it.)
        std::string src_path = "";		    // Used to create, copy, and delete files.
        std::string dest_path = "";		    // Used to copy and delete files.
        fstream original_file;			    // Used to compare copied files.
        fstream dup_file;			        // Used to compare copied files.
        std::vector<std::string> tempList;	// Used to construct a new fileList.

        // OK, for this test we need to select a few files (no more than 5) and try to copy random amounts using them.

        // Check to see if the given vector has 5 items in it.
        if (fileList.size() < number_of_files_to_copy)
        {
                // Use all of the items here.
                number_of_files_to_copy = fileList.size();
        }

        // Start main loop.
        for (size_t x = 0; x < number_of_files_to_copy; x++)
        {
                // Check for a directory.
                file_utills_result = FileUtills::IsFileOrDirectory(fileList[x]);
                if ((file_utills_result != 2) && ((file_utills_result == 0) || (file_utills_result == 1)))
                {
                        // Open the original file.
                        original_file.open(fileList[x].c_str(), ios::in | ios::binary);
                        if (!original_file.is_open())
                        {
                                // Could not open original_file.
                                std::cout << "ERROR: Could not open original file: " << fileList[x] << " for reading.\n";
                                std::cout << "Skipping file, please verifiy the file manually.\n";
                                std::cout.flush();
                                failure_count++;
                                if (failure_count > 3)
                                {
                                      // Bailout.
                                      break;
                                }
                                else
                                {
                                      // Output number of remaining failures.
                                      std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                      std::cout.flush();
                                }
                        }
                        else
                        {
                                // Determine the length of the file.
                                original_file.seekg(0, ios::end);
                                original_file_size = original_file.tellg();

                                // Close the file.
                                if (original_file.is_open())
                                {
                                        original_file.close();
                                }

                                // Check the original_file_size.
                                if (original_file_size <= 3)
                                {
                                        // Ok we need at least more than one char.
                                        std::cout << "WARNING: Original file: " << fileList[x] << " has a size of: " << original_file_size << ".\n";
                                        std::cout << "This file cannot be used for this test. Skipping file.\n";
                                        original_file_size = 0;
                                        std::cout.flush();
                                        failure_count++;
                                        if (failure_count > 3)
                                        {
                                              // Bailout.
                                              break;
                                        }
                                        else
                                        {
                                              // Output number of remaining failures.
                                              std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                              std::cout.flush();
                                        }
                                }
                                else
                                {
                                        // Randomly determine a length of the file to copy.
                                        while (begOffset == endOffset)
                                        {
                                                begOffset = DataProcess::Trivial_Random_Number_Generator(0, original_file_size);
                                                endOffset = DataProcess::Trivial_Random_Number_Generator(0, (original_file_size - 1));	// We want an offset not the entire file.

                                                // Check to see if the offsets are the same as the previously generated ones.
                                                if ((previous_begOffset == begOffset) && (previous_endOffset == endOffset))
                                                {
                                                        // Need new offsets.
                                                        std::cout << "ERROR: Generated the previous offsets.\n";
                                                        std::cout.flush();
                                                        failure_count++;
                                                        if (failure_count > 3)
                                                        {
                                                                // Bailout.
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                // Output number of remaining failures.
                                                                std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                                std::cout.flush();
                                                        }
                                                }
                                                else
                                                {
                                                        // Check to see if the offsets are reversed.
                                                        if (begOffset > endOffset)
                                                        {
                                                                // Swap the offsets.
                                                                swap = endOffset;
                                                                endOffset = begOffset;
                                                                begOffset = swap;
                                                                swap = 0;
                                                        }
                                                        else
                                                        {
                                                                if (begOffset == endOffset)
                                                                {
                                                                        std::cout << "ERROR: Generated the same offsets.\n";
                                                                        std::cout << "Skipping file, please verifiy the file manually.\n";
                                                                        std::cout.flush();
                                                                        failure_count++;
                                                                        if (failure_count > 3)
                                                                        {
                                                                                // Bailout.
                                                                                break;
                                                                        }
                                                                        else
                                                                        {
                                                                                // Output number of remaining failures.
                                                                                std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                                                std::cout.flush();
                                                                        }
                                                                }
                                                        }
                                                }
                                        }

                                        // Check to see if we failed to create some random file offsets.
                                        if (failure_count > 3)
                                        {
                                                // Bailout.
                                                break;
                                        }
                                        else
                                        {
                                                // Copy the offsets.
                                                previous_begOffset = begOffset;
                                                previous_endOffset = endOffset;

                                                // OK Generate a random file name.
                                                dest_path.clear();		// Erase dest_path.
                                                dest_path = fileList[0] + DIR_SEP + DataProcess::GenerateUID(fileList[x].size());
                                                if (dest_path.size() <= 0)
                                                {
                                                        // Could not create temp file name.
                                                        std::cout << "Could not create temp filename.\n";
                                                        std::cout.flush();
                                                        failure_count++;
                                                        x--;		// Decrement x to try again.
                                                        if (failure_count > 3)
                                                        {
                                                              // Bailout.
                                                              break;
                                                        }
                                                        else
                                                        {
                                                              // Output number of remaining failures.
                                                              std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                              std::cout.flush();
                                                        }
                                                }
                                                else
                                                {
                                                        // Call FileUtills::CopyPath().
                                                        result = FileUtills::CopyPath(fileList[x], dest_path, false, false, false, false, begOffset, endOffset);
                                                        if (result != 0)
                                                        {
                                                                // Report error code.
                                                                std::cout << "ERROR in individual file copy test, FileUtills::CopyFile() returned error code: " << result << ".\n";
                                                                std::cout << Get_FileUtills_CopyFile_Error_Message(result) << '\n';
                                                                std::cout.flush();
                                                                failure_count++;
                                                                x--;		// Decrement x to try again.
                                                                if (failure_count > 3)
                                                                {
                                                                      // Bailout.
                                                                      break;
                                                                }
                                                                else
                                                                {
                                                                      // Output number of remaining failures.
                                                                      std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                                      std::cout.flush();
                                                                }
                                                        }
                                                        else
                                                        {
                                                                // Copy the new file name to the tempList.
                                                                tempList.push_back(dest_path);

                                                                // Tell user we are comparing the files.
                                                                std::cout << "Comparing original file " << fileList[x] << " to copied file " << dest_path << ".\n";
                                                                std::cout << "Original file offsets: begOffset = " << begOffset << ". endOffset = " << endOffset << ".\n";
                                                                std::cout << "Total amount of bytes to compare: " << (endOffset - begOffset) << ".\n";
                                                                std::cout << "Running test: ";
                                                                std::cout.flush();

                                                                // Call Verify_Files().
                                                                if (Verify_Files(fileList[x], dest_path, begOffset, endOffset))
                                                                {
                                                                        // Test passed.
                                                                        std::cout << "Result: PASS\n";
                                                                        std::cout.flush();
                                                                }
                                                                else
                                                                {
                                                                        // Test failed.
                                                                        std::cout << "Result: FAILURE\n";
                                                                        std::cout.flush();
                                                                        failure_count++;
                                                                        x--;		// Decrement x to try again.
                                                                        if (failure_count > 3)
                                                                        {
                                                                              // Bailout.
                                                                              break;
                                                                        }
                                                                        else
                                                                        {
                                                                              // Output number of remaining failures.
                                                                              std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                                              std::cout.flush();
                                                                        }
                                                                }

                                                                // Output the remaining files to copy.
                                                                std::cout << "Number of temp files remaining to copy: " << (number_of_files_to_copy - (x + 1)) << ".\n";
                                                        }
                                                }
                                        }
                                }
                        }
                }
                else
                {
                        // Check for error.
                        if (file_utills_result < 0)
                        {
                                std::cout << "FileUtills::IsFileOrDirectory() returned an error: " << file_utills_result << ".\n";
                                std::cout.flush();
                                failure_count++;
                                x--;		// Decrement x to try again.
                                if (failure_count > 3)
                                {
                                        // Bailout.
                                        break;
                                }
                                else
                                {
                                        // Output number of remaining failures.
                                        std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                        std::cout.flush();
                                }
                        }
                }
        }

        // OK, copy any created filenames from tempList to fileList.
        for (size_t x = 0; x < tempList.size(); x++)
        {
                // Copy data.
                fileList.push_back(tempList[x]);
        }

        // Clear tempList.
        tempList.clear();

        // Check failure_count.
        if (failure_count > MAX_FAILURES)
        {
                std::cout << "TEST FAILURE.\n";
                std::cout << "Maximum failure limit reached, Test aborted.\n";
                std::cout.flush();
                result = -9;
        }

        // Exit function.
        return result;
}

short recursive_directory_copy_test(std::vector<std::string> & fileList)
{
        // Init vars.
        short result = 0;				// Result of tests.
        int failure_count = 0;			    // Used to abort file creation loops.
        std::string dest_path = "";		// Used to create a new subdirectory path.

        // Check to see if the first entry in the given vector has data in it.
        if ((fileList.size() > 0) && (fileList[0].size() > 0))
        {
                // Create new directory path.
                while (dest_path.size() == 0)
                {
                        // Tell user what we are doing.
                        std::cout << "Creating a temp directory path to test recursive directory copying, please wait.\n";
                        std::cout.flush();

                        // Generate random ID and chcek for valid unused ID.
                        dest_path = DataProcess::GenerateUID(fileList[0].size());
                        if (dest_path.size() <= 0)
                        {
                                // Could not create temp directory name.
                                std::cout << "Could not create temp directory name.\n";
                                std::cout.flush();
                                failure_count++;
                                if (failure_count > MAX_FAILURES)
                                {
                                        // Bailout.
                                        break;
                                }
                                else
                                {
                                        // Output number of remaining failures.
                                        std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                        std::cout.flush();
                                }
                        }
                        else
                        {
                                // Check to see if the dest path exists.
                                result = FileUtills::IsFileOrDirectory(dest_path);
                                if (result < 0)
                                {
                                        // Check for an error.
                                        if (result != -6)
                                        {
                                                // An error occured. Print error code and print human readable error message.
                                                std::cout << "ERROR: FileUtills::IsFileOrDirectory() returned error code: " << result << ' ';
                                                std::cout << Get_FileUtills_IsFileOrDirectory_Error_Message(result) << '\n';
                                                std::cout.flush();

                                                // Erase dest_path.
                                                dest_path.clear();

                                                // Update failure_count.
                                                failure_count++;
                                                if (failure_count > MAX_FAILURES)
                                                {
                                                        // Bailout.
                                                        break;
                                                }
                                                else
                                                {
                                                        // Output number of remaining failures.
                                                        std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                        std::cout.flush();
                                                }
                                        }
                                        else
                                        {
                                                // Tell user we are performing the test.
                                                std::cout << "Attempting to copy source directory: " << fileList[0];
                                                std::cout << " to dest directory: " << dest_path << ".\n";
                                                std::cout << "Result: ";
                                                std::cout.flush();

                                                // Call FileUtills::CopyPath().
                                                result = FileUtills::CopyPath(fileList[0], dest_path, true);
                                                if (result != 0)
                                                {
                                                        // Get error code.
                                                        std::cout << "FAIL\n";
                                                        std::cout << "FileUtills::CopyPath() returned error code: " << result << ", "
                                                        << Get_FileUtills_CreateDirectory_Error_Message(result) << '\n';
                                                        std::cout.flush();

                                                        // Erase dest_path.
                                                        dest_path.clear();

                                                        // Update failure_count.
                                                        failure_count++;
                                                        if (failure_count > MAX_FAILURES)
                                                        {
                                                                // Bailout.
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                // Output number of remaining failures.
                                                                std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                                std::cout.flush();
                                                        }
                                                }
                                                else
                                                {
                                                        // Successfull! Delete the copied directory.
                                                        std::cout << "PASS\n";
                                                        std::cout << "Please wait deleting copied directory.\n";

                                                        // Call DeletePath().
                                                        result = FileUtills::DeletePath(dest_path, true);
                                                        if (result != 0)
                                                        {
                                                                std::cout << "FileUtills::DeletePath() returned error code: " << result << ", "
                                                                << Get_FileUtills_DeletePath_Error_Message(result) << '\n';
                                                                std::cout << "Copied subdirectory could not be deleted, please delete it manually.\n";
                                                                std::cout.flush();
                                                        }
                                                        else
                                                        {
                                                                std::cout << "Copied subdirectory deleted successfully.\n";
                                                                std::cout.flush();
                                                        }
                                                }
                                        }
                                }
                                else
                                {
                                        // Path exists.
                                        std::cout << "Generated path name already exists.\n";
                                        std::cout.flush();

                                        // Erase dest_path.
                                        dest_path.clear();

                                        // Update failure_count.
                                        failure_count++;
                                        if (failure_count > MAX_FAILURES)
                                        {
                                                // Bailout.
                                                break;
                                        }
                                        else
                                        {
                                                // Output number of remaining failures.
                                                std::cout << "Attempts remaining: " << (MAX_FAILURES - failure_count) << ".\n";
                                                std::cout.flush();
                                        }
                                }
                        }
                }
        }
        else
        {
                // Error, No temp files.
                std::cout << "TEST FAILURE\n";
                std::cout << "ERROR: No temp files, cannot perform recursive directory copy test.\n";
                result = -1;
        }

        // Check failure_count.
        if (failure_count > MAX_FAILURES)
        {
                std::cout << "TEST FAILURE.\n";
                std::cout << "Maximum failure limit reached, Test aborted.\n";
                std::cout.flush();
                result = -9;
        }

        // Exit function.
        return result;
}

short fileutills_cleanup(std::vector<std::string> & fileList)
{
        // Init vars.
        short result = 0;				// Result of tests.

        // Tell the user we are cleaning up.
        std::cout << "Removing temp files and directories, please wait.\n";
        std::cout.flush();

        // The first entry is the created top-level directory.
        if (fileList.size() > 0)
        {
                // Call FileUtills::DeletePath().
                result = FileUtills::DeletePath(fileList[0], true);
                if (result != 0)
                {
                        std::cout << "FileUtills::DeletePath() returned error code: " << result << ", "
                        << Get_FileUtills_DeletePath_Error_Message(result) << '\n';
                        std::cout << "Not all temp files and directories could be deleted, please delete them manually.\n";
                        std::cout.flush();
                }
                else
                {
                        std::cout << "All temp files and directories deleted successfully.\n";
                        std::cout.flush();
                }
        }

        // Flush fileList.
        fileList.clear();

        // Exit function.
        return result;
}

short unit_test_fileutills_main()
{
        // Init vars.
        short result = 0;			// Result of tests.
        std::vector<std::string> fileList;	// Used to store file names.

        // Tell user we are starting to create temp files and directories.
        std::cout << "Creating five (5) temp files to test basic file copying, please wait.\n";
        std::cout.flush();

        // Create five (5) temp files.
        result = Create_Temp_Files(5, "Temp File. DELETE ME PLEASE!", fileList, 5);
        if (result != 0)
        {
                std::cout << "Could not create files for testing, please delete any remaining files manually.\n";
                std::cout << "Aborting.\n";
        }
        else
        {
                // Output START OF TEST SECTION.
                std::cout << START_TEST_SECTION;

                // Now call indvidual_file_copy_test().
                std::cout << "Now testing FileUtills::CopyPath() individual file copy.\n";
                std::cout << "(This also tests FileUtills::CopyFile().)\n";
                std::cout << "Please wait.\n\n";
                std::cout.flush();
                result = indvidual_file_copy_test(fileList);
                if (result != 0)
                {
                        std::cout << "Please delete any remaining files manually.\n";
                        std::cout << "Aborting.\n";

                        // Output END OF TEST SECTION.
                        std::cout << END_TEST_SECTION;
                }
                else
                {
                        // Output END OF TEST SECTION.
                        std::cout << END_TEST_SECTION;

                        // Output START OF TEST SECTION.
                        std::cout << START_TEST_SECTION;

                        // Now call random_length_copying_test().
                        std::cout << "Now testing FileUtills::CopyPath() random offset copying.\n";
                        std::cout << "(I.e. Copying a portion of a file using randomly generated offsets.)\n";
                        std::cout << "(This also tests FileUtills::CopyFile().)\n";
                        std::cout << "Please wait.\n\n";
                        std::cout.flush();
                        result = random_length_copying_test(fileList);
                        if (result != 0)
                        {
                                std::cout << "Please delete any remaining files manually.\n";
                                std::cout << "Aborting.\n";

                                // Output END OF TEST SECTION.
                                std::cout << END_TEST_SECTION;
                        }
                        else
                        {
                                // Output END OF TEST SECTION.
                                std::cout << END_TEST_SECTION;

                                // Output START OF TEST SECTION.
                                std::cout << START_TEST_SECTION;

                                // Below here is directory copying. In a different function.
                                std::cout << "Now testing FileUtills::CopyPath() recursive directory copying.\n";
                                std::cout << "Please wait.\n\n";
                                std::cout.flush();
                                result = recursive_directory_copy_test(fileList);
                                if (result != 0)
                                {
                                        std::cout << "Please delete any remaining files manually.\n";
                                        std::cout << "Aborting.\n";
                                }

                                // Output END OF TEST SECTION.
                                std::cout << END_TEST_SECTION;
                        }
                }
        }

        // Cleanup.
        if (fileList.size() > 0)
        {
                fileutills_cleanup(fileList);
        }

        // Tell user we are finished.
        std::cout << "All tests completed. Exiting.\n\n";

        // Exit program.
        return result;
}
