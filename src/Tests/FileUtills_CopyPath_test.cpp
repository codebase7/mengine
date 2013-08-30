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

#include "Test_Base_Header.h" 
#include "../Common/Src/FileUtills.h"
#include "../Core/Src/DataProcess.h"

#ifndef MAX_FAILURES
#define MAX_FAILURES 3
#endif

const std::string Get_FileUtills_CopyFile_Error_Message(const short & error_code)
{
	// Error code list below, should match function description.
	switch (error_code)
	{
		case -5:
		    return "The given begOffset is bigger than the given endOffset.\n";
		    break;
		case -9:
		    return "The memory buffer could not be allocated, or if an exception is thrown while copying data.\n";
		    break;
		case -10:
		    return "The source file was not given.\n";
		    break;
		case -11:
		    return "The source file could not be opened.\n";
		    break;
		case -12:
		    return "The beginning offset given is larger than the source file.\n";
		    break;
		case -13:
		    return "The ending offset given is larger than the source file.\n";
		    break;
		case -14:
		    return "An I/O error occured while reading the source file.\n";
		    break;
		case -15:
		    return "A logical error occured while reading the source file.\n";
		    break;
		case -16:
		    return "End of file was encountered unexpectedly. (I.e It was expected that the source file had more data in it.)\n";
		    break;
		case -20:
		    return "The dest file was not given.\n";
		    break;
		case -21:
		    return "Dest file could not be opened.\n";
		    break;
		case -24:
		    return "An I/O error occured while writing to the dest file.\n";
		    break;
		case -25:
		    return "A logical error occured while writing to the dest file.\n";
		    break;
		default:
		    return "Unknown error code.\n";
		    break;
	};
	
	// Exit function.
	return "END_ERRORMSG_FUNCTION\n";
}

bool Verify_Files(const std::string & src, const std::string & dest, const size_t & begOffset, const size_t & endOffset)
{
	// Init vars.
	bool result = false;			// Used to store result of function.
  	fstream original_file;			// Used to compare copied files.
	fstream dup_file;			// Used to compare copied files.
	size_t original_file_size = 0;		// Used to compare the file sizes.
	
	// Do some checks on those args.
	if (src.size() <= 0)
	{
		std::cout << "ERROR: No original file path given.\n\n";
	}
	else
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
							if ((original_file.tellg() < endOffset) || (dup_file.tellg() != (endOffset - begOffset)))
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
								for (size_t y = 0; y < original_file_size; y++)
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
	
	// Exit function.
	return result;
}

short Create_Temp_Files(const short & number_of_files_to_create, const short & filename_length, 
			const std::string & data_to_put_in_temp_files, std::vector<std::string> & fileList)
{
  	// Init vars.
	short result = 0;			// Used to return a result to the caller.
	int failure_count = 0;			// Used to abort file creation loops. 
  	std::string src_path = "";		// Used to create, copy, and delete files.
	fstream output;				// Used to create temp files.
	
  	// Create files.
	for (short x = 0; x < number_of_files_to_create; x++)
	{ 
		  // OK Generate a random file name.
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
	
	// Check failure_count.
	if (failure_count > 3)
	{
		std::cout << "TEST FAILURE.\n";
		std::cout << "Maximum failure limit reached, Test aborted.\n";
		std::cout.flush();
		result -9;
	}
	
	// Exit function.
	return result;
}

short indvidual_file_copy_test(std::vector<std::string> & fileList)
{
	// Init vars.
	bool bad_data = false;			// Used to tell if the copied file has bad data.
	short result = 0;			// Used to return a result to the caller.
	int failure_count = 0;			// Used to abort file creation loops.
	size_t original_file_size = 0;		// Used to compare the file sizes.
	std::string src_path = "";		// Used to create, copy, and delete files.
	std::string dest_path = "";		// Used to copy and delete files.
	fstream original_file;			// Used to compare copied files.
	fstream dup_file;			// Used to compare copied files.
	std::vector<std::string> tempList;	// Used to construct a new fileList.
  
	// Check size of fileList.
	if (fileList.size() > 0)
	{
		// OK, now start copy loop.
		for (size_t x = 0; x < fileList.size(); x++)
		{
			// OK Generate a random file name.
			dest_path.clear();		// Erase dest_path.
			dest_path = DataProcess::GenerateUID(fileList[x].size());
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
			result = FileUtills::CopyPath(fileList[x], dest_path);
			if (result != 0)
			{
				// Report error code.
				std::cout << "ERROR in individual file copy test, FileUtills::CopyFile() returned error code: " << result << ".\n";
				std::cout << Get_FileUtills_CopyFile_Error_Message(result);
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
			result -9;
		}
	}
	
	// Exit function.
	return result;
}

short random_length_copying_test(std::vector<std::string> fileList)
{
	// Init vars.
	bool bad_data = false;			// Used to tell if the copied file has bad data.
	short result = 0;			// Used to return a result to the caller.
	int failure_count = 0;			// Used to abort file creation loops.
	size_t original_file_size = 0;		// Used to compare the file sizes.
	size_t begOffset = 0;			// Used to hold the randomly generated begOffset.
	size_t endOffset = 0;			// Used to hold the randomly generated endOffset.
	size_t previous_begOffset = 0;		// Used to hold the previously generated begOffset.
	size_t previous_endOffset = 0;		// Used to hold the previously generated endOffset.
	size_t swap = 0;			// Used if the generated offsets are reversed to swap them.
	size_t number_of_files_to_copy = 5;	// Used to hold the real number of files tested. (In case the fileList vector has less than five elements in it.)
	std::string src_path = "";		// Used to create, copy, and delete files.
	std::string dest_path = "";		// Used to copy and delete files.
	fstream original_file;			// Used to compare copied files.
	fstream dup_file;			// Used to compare copied files.
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
					dest_path = DataProcess::GenerateUID(fileList[x].size());
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
							std::cout << Get_FileUtills_CopyFile_Error_Message(result);
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
		result -9;
	}
	
	// Exit function.
	return result;
}

int main()
{ 
	// Init vars.
	int result = 0;				// Result of tests.
	std::vector<std::string> fileList;	// Used to store file names.
	
	// Tell user we are testing the functions.
	std::cout << "FileUtills::CopyPath() test program\n";
	std::cout << "This program tests various abilites of FileUtills::CopyPath().\n";
	
	// Output compile date time.
        std::cout << "Compiled on " << TESTCOMPILEDATE << " at " << TESTCOMPILETIME << ".\n\n";

	std::cout << "Creating five (5) temp files to test basic file copying, please wait.\n";
	std::cout.flush();
	
	// Create five (5) temp files.
	result = Create_Temp_Files(5, 5, "Temp File. DELETE ME PLEASE!", fileList);
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
				
				// Below here is directory copying. In a different function.
			}
		}
	}
	
	// Clear the vector.
	fileList.clear();
	
	// Tell user we are finished.
	std::cout << "All tests completed. Exiting.\n\n";
	
	// Exit program.
	return result;
}