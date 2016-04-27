/*!
    Multiverse Engine Project DataProcess DataProcess.cpp

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

/* Internal includes. */
#include "DataProcess.h"
#include "FileStreams.h"
#include "../../Common/Src/Error_Handler/Common_Error_Handler_Error_Codes.h"

/* External includes. */
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

int DataProcess::CopyCStringToStdString(const char * source, const size_t & sourceLength, std::string & dest)
{
	/* Init result. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	std::string tempStr = "";						/* Temporary string used to copy data. */

	/* Check for valid data. */
	if ((source != NULL) && (sourceLength > 0))
	{
		/* Begin loop to copy data. */
		for (size_t x = 0; (x < sourceLength); x++)
		{
			tempStr += source[x];
		}

		/* Copy the tempStr to dest. */
		dest = tempStr;

		/* Success. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int DataProcess::CopyStdStringToCString(const std::string & source, char ** dest)
{
	/* Init result. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* Result code of other engine functions. */
	size_t sourceLength = 0;						/* The length of the source string. */
	char * tempStr = NULL;							/* Temporary string used to copy data. */
	const char * sourcePtr = NULL;					/* Temporary pointer used to copy the source string's data. */

	/* Get the source string's length, and pointer. */
	sourceLength = source.size();
	sourcePtr = source.c_str();

	/* Check for valid data. */
	if ((dest != NULL) && (sourceLength > 0) && (sourcePtr != NULL))
	{
		/* Allocate memory for dest string. */
		retFromCall = DataProcess_Reallocate_C_String(&tempStr, 0, sourceLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempStr != NULL))
		{
			/* Begin loop to copy data. */
			for (size_t x = 0; (x < sourceLength); x++)
			{
				tempStr[x] = sourcePtr[x];
			}

			/* Copy the tempStr to dest. */
			(*dest) = tempStr;

			/* Success. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for tempStr. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Check for success. */
	if (ret != COMMON_ERROR_SUCCESS)
	{
		/* Deallocate the tempStr if needed. */
		if (tempStr != NULL)
		{
			DataProcess_Deallocate_CString(&tempStr);
		}
	}

	/* Exit function. */
	return ret;
}

size_t DataProcess::Trivial_Random_Number_Generator(const size_t & min_value, const size_t & max_value, const bool & reset_rand)
{
	/* Call C function. */
	return (DataProcess_Trivial_Random_Number_Generator(min_value, max_value, reset_rand));
}

short DataProcess::IncrementingSort(std::vector<std::string> & sort)
{
        // Init vars.
        const char * current_entry = NULL;      // Used for comparing entries.
        const char * next_entry = NULL;         // Used for comparing entries.
        size_t current_entry_index = 0;         // Used to access the current entry in the vector.
        size_t next_entry_index = 1;            // Used to access the entry after the current one in the vector.
        std::string temp = "";                  // Used to hold temporary value.

        // Check size of sort. (We only need to sort data if there is more than one thing to sort.)
        if (sort.size() > 1)
        {
                // Create a try block.
                try{

                        // OK start main loop.
                        for (size_t x = 0; x < sort.size(); x++)
                        {
                                // Start internal loop.
                                for (size_t y = 0; y < sort.size(); y++)
                                {
                                        // Check to see if this is the last entry in the list.
                                        if ((y + 1) >= sort.size())
                                        {
                                                // This is the last entry, get out of the loop.
                                                break;
                                        }

                                        // Get pointers.
                                        current_entry = sort[current_entry_index].c_str();
                                        next_entry = sort[next_entry_index].c_str();

                                        // Figure out which string is smaller.
                                        if ((sort[current_entry_index].size()) >= (sort[next_entry_index].size()))
                                        {
                                                // Compare using the shorter string.
                                                for (size_t z = 0; z < (sort[next_entry_index].size()); z++)
                                                {
                                                        // Dereference position in the vector, then dereference the position in the string.
                                                        if (current_entry[z] < next_entry[z])
                                                        {
                                                                // The current entry is less than the next one.
                                                                temp = sort[next_entry_index];

                                                                // Copy the current entry to the next one.
                                                                sort[next_entry_index] = sort[current_entry_index];

                                                                // Now copy the temp value (next entry) to the current entry.
                                                                sort[current_entry_index] = temp;

                                                                // Clear vars.
                                                                temp.clear();
                                                                current_entry = NULL;
                                                                next_entry = NULL;

                                                                // Get out of the loop.
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                if (current_entry[z] > next_entry[z])
                                                                {
                                                                        // OK, in this case the entries are where they need to be.
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                // Compare using the shorter string.
                                                for (size_t z = 0; z < (sort[current_entry_index].size()); z++)
                                                {
                                                        // Dereference position in the vector, then dereference the position in the string.
                                                        if (current_entry[z] < next_entry[z])
                                                        {
                                                                // The current entry is less than the next one.
                                                                temp = sort[next_entry_index];

                                                                // Copy the current entry to the next one.
                                                                sort[next_entry_index] = sort[current_entry_index];

                                                                // Now copy the temp value (next entry) to the current entry.
                                                                sort[current_entry_index] = temp;

                                                                // Clear vars.
                                                                temp.clear();
                                                                current_entry = NULL;
                                                                next_entry = NULL;

                                                                // Get out of the loop.
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                if (current_entry[z] > next_entry[z])
                                                                {
                                                                        // OK, in this case the entries are where they need to be.
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }

                                        // Increment the indexes.
                                        current_entry_index++;
                                        next_entry_index++;
                                }

                                // Reset the index values.
                                current_entry_index = 0;
                                next_entry_index = 1;
                        }
                }
                catch (...)
                {
                        // std::exception thrown.
                        return -9;
                }
        }

        // Exit function.
        return 0;
}

short DataProcess::DecrementingSort(std::vector<std::string> & sort)
{
        // Init vars.
        const char * current_entry = NULL;      // Used for comparing entries.
        const char * next_entry = NULL;         // Used for comparing entries.
        size_t current_entry_index = 0;         // Used to access the current entry in the vector.
        size_t next_entry_index = 1;            // Used to access the entry after the current one in the vector.
        std::string temp = "";                  // Used to hold temporary value.

        // Check size of sort. (We only need to sort data if there is more than one thing to sort.)
        if (sort.size() > 1)
        {
                // Create a try block.
                try{

                        // OK start main loop.
                        for (size_t x = 0; x < sort.size(); x++)
                        {
                                // Start internal loop.
                                for (size_t y = 0; y < sort.size(); y++)
                                {
                                        // Check to see if this is the last entry in the list.
                                        if ((y + 1) >= sort.size())
                                        {
                                                // This is the last entry, get out of the loop.
                                                break;
                                        }

                                        // Get pointers.
                                        current_entry = sort[current_entry_index].c_str();
                                        next_entry = sort[next_entry_index].c_str();

                                        // Figure out which string is smaller.
                                        if ((sort[current_entry_index].size()) >= (sort[next_entry_index].size()))
                                        {
                                                // Compare using the shorter string.
                                                for (size_t z = 0; z < (sort[next_entry_index].size()); z++)
                                                {
                                                        // Dereference position in the vector, then dereference the position in the string.
                                                        if (current_entry[z] > next_entry[z])
                                                        {
                                                                // The current entry is greater than the next one.
                                                                temp = sort[next_entry_index];

                                                                // Copy the current entry to the next one.
                                                                sort[next_entry_index] = sort[current_entry_index];

                                                                // Now copy the temp value (next entry) to the current entry.
                                                                sort[current_entry_index] = temp;

                                                                // Clear vars.
                                                                temp.clear();
                                                                current_entry = NULL;
                                                                next_entry = NULL;

                                                                // Get out of the loop.
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                if (current_entry[z] < next_entry[z])
                                                                {
                                                                        // OK, in this case the entries are where they need to be.
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }
                                        else
                                        {
                                                // Compare using the shorter string.
                                                for (size_t z = 0; z < (sort[current_entry_index].size()); z++)
                                                {
                                                        // Dereference position in the vector, then dereference the position in the string.
                                                        if (current_entry[z] > next_entry[z])
                                                        {
                                                                // The current entry is greater than the next one.
                                                                temp = sort[next_entry_index];

                                                                // Copy the current entry to the next one.
                                                                sort[next_entry_index] = sort[current_entry_index];

                                                                // Now copy the temp value (next entry) to the current entry.
                                                                sort[current_entry_index] = temp;

                                                                // Clear vars.
                                                                temp.clear();
                                                                current_entry = NULL;
                                                                next_entry = NULL;

                                                                // Get out of the loop.
                                                                break;
                                                        }
                                                        else
                                                        {
                                                                if (current_entry[z] < next_entry[z])
                                                                {
                                                                        // OK, in this case the entries are where they need to be.
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }

                                        // Increment the indexes.
                                        current_entry_index++;
                                        next_entry_index++;
                                }

                                // Reset the index values.
                                current_entry_index = 0;
                                next_entry_index = 1;
                        }
                }
                catch (...)
                {
                        // std::exception thrown.
                        return -9;
                }
        }

        // Exit function.
        return 0;
}

bool DataProcess::CheckForEOF(std::fstream & source)
{
        // Init vars.
        size_t current_pos = 0;         // Used to store current pos.
        bool result = false;            // Returned result.

        // Dumb check.
        if (source.fail() == true)
        {
                // File stream is bad.
                result = false;
        }
        else
        {
                // Get current pos.
                current_pos = source.tellg();

                // Seek to the end of the file.
                source.seekg(0, std::ios::end);

                // Compare positions.
                if (current_pos == (unsigned)source.tellg())
                {
                        // At EOF (End of File).
                        result = true;
                }

                // Seek back to the original position.
                source.seekg(current_pos, std::ios::beg);
        }

        // Exit function and return the result.
        return result;
}

std::string DataProcess::GenerateUID(long int length)
{
        // Init vars.
        std::string output = "";        // Data that will be returned.
        int y = 0;                      // Result from rand().

        // Until we fill the buffer generate a random number.
        for (long int x = 0; x < length; x++)
        {
                // Check and see if we go out of bounds of our array.
                if (x > length || x < 0)
                {
                        // Got out of bounds.
                        return "";
                }

                // Otherwise generate a random number and put it into the array.
                else
                {
                        // Generate Random
                        y = DataProcess::Trivial_Random_Number_Generator();

                        // Check for Alpha numeric. ASCII CODES 0-9 (48-57) A-Z (65 - 90) a-z (97 - 122)
                        if (((y > 47) & (y < 58)) || ((y > 64) & (y < 91)) || ((y > 96) & (y < 123)))
                        {
                                // Send the alpha numaric to the output.
                                output += y;
                                y = 0;
                        }
                        else
                        {
                                // Cause the counter to not go anywhere.
                                x--;
                                y = 0;
                        }
                }
        }

        // Done. Exit function.
        return output;
}

double DataProcess::getnumberFromString(std::string source, std::string varName, std::string limiter , bool isdecimal, Panic::Panic_ERROR & error)
{
	// Initlize vars.
	double output = 0;
	std::string real_limiter = " ";
	std::string temp1 = "";
	std::string temp2 = "";
	bool number_found = false;
	int varNamesize = 0;
	long varNamelocation = 0;
	long real_location = 0;
	long sourceSize = 0;
	bool endofString = false;

	// Check to see if the string is empty.
	if (source.empty() == true)
	{
		error.PanicHandler("DataProcess::getnumberFromString : String is empty. Returning 0 although this is probably not what you wanted.");
		return 0;
	}

	// Set the size into the buffer.
	sourceSize = source.size();

	// Check and see if the limiter is empty.
	if (limiter.empty() == true)
	{
		error.PanicHandler("DataProcess::getnumberFromString : Your limiter is bad. Using a whitespace charater for the limiter.");
	}
	if (limiter.empty() != true)
	{
		real_limiter = limiter;
	}

	// Check and see if varName is empty.
	if (varName.empty() == true)
	{
		error.PanicHandler("DataProcess::getnumberFromString : varName not given. Returning 0.");
		return 0;
	}

	// Look for the varName.
	if (source.find(varName) == std::string::npos)
	{
		error.PanicHandler("DataProcess::getnumberFromString : Can't find varName in string. Returning default 0.");
		real_limiter = "";
		return 0;
	}
	// found varName get size and location
	varNamesize = varName.size();
	varNamelocation = source.find(varName);
	// get to the actual int. varNamelocation is the first letter of varName in the string
	// varNamesize is the total number of charaters in the string.
	// therefor to get the location of the int
	// go to the location of the varName then add the total length of varName
	// to that location and then subtract 1 from the result because of the first charater being count twice.
	real_location = varNamelocation + varNamesize - 1;

	// Run while loop
	while (number_found == false && endofString == false)
	{
		real_location = real_location + 1;
		if (real_location < sourceSize)
		{
			temp2 = source.at(real_location);
			if (temp2 == "1")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "2")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "3")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "4")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "5")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "6")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "7")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "8")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "9")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == "0")
			{
				temp1 = temp1 += temp2;
				std::cout << temp1 << std::endl;
			}
			if (temp2 == real_limiter)
			{
				std::cout << temp1 << std::endl;
				number_found = true;
			}
			if (temp2 == ".")
			{
				if (isdecimal == true)
				{
					temp1 = temp1 += temp2;
					std::cout << temp1 << std::endl;
				}
				if (isdecimal == false)
				{
					// Do nothing.
				}
			}
		}
		if (real_location >= sourceSize)
		{
			endofString = true;
		}
	}

	// Check for std::exception, if thrown return 0. otherwise return result.
	try{
        std::istringstream (temp1) >> output;
	}
	catch(std::exception& ex){
        std::cout << "\n ERROR: DataProcess::getnumberFromString() std::exception: " << ex.what() << "\n Clearing data buffer and returning zero.\n\n";

	// Guess what? we found bullshit. we can't clear it now so dump the buffer and exit.
		error.PanicHandler("DataProcess::getnumberFromString : Can't convert number string back to double.");
		temp1 = "";
		temp2 = "";
		output = 0;
		real_limiter = "";
		varNamesize = 0;
		varNamelocation = 0;
	    real_location = 0;
	    sourceSize = 0;
	}
	std::cout << " the result is: " << output << std::endl;
	return output;
}

int DataProcess::getIntFromInput()
{
	int number = 0;
	std::string dummy = "";
	std::cin >> number;
	getline(std::cin, dummy);    	// std::cin appends a end line char, so we use this to get rid of it. other wise it will show up on the next std::cin op.
	if (std::cin.fail() == true) 	// If this goes true user has inputed a non int.
	{
		std::cout << " invalid data \n ";
		// Fix the buffer.
		std::cin.clear();
		getline(std::cin, dummy);
	}
	return number;
}

bool DataProcess::yesNoConsolePrompt()
{
        // Init var.
        std::string dummy;
        dummy.clear();

        // Prompt user.
        std::cout << "(YES or NO) (Must be in CAPS): ";
        getline(std::cin, dummy);

        // Check result, if user said YES then return true.
        if (dummy == "YES")
        {
                return true;
        }

        // Otherwise return false.
        return false;
}

bool DataProcess::getboolFromstring(std::string source, std::string varName, char delimiter, Panic::Panic_ERROR & error)
{
	// Initlize the vars. Used to determine if we hit someting or not.
	int foundTrue = -1;
	int foundFalse = -1;
	int location1 = 0;
	int location2 = 0;
	char delimiterReal = ' ';
	std::string searchString = "";

	// Look for the var name
	if (source.find(varName) == std::string::npos)
	{
		// If varname is not found in the string return default.
		error.PanicHandler("DataProcess::getboolFromstring : Varname not found.");
				return false;
	}
	else
	{
		// Set the read location of the string to varname's position.
		location1 = source.find(varName);
	}

	// Check and see if the delimiter we got was valid or not.
	if (delimiter == '\0')
	{
		delimiterReal = '\n';
	}
	if (source.find(delimiterReal, location1) == std::string::npos)
	{
		location2 = -1;
	}
	if (source.find('\n', location1) == std::string::npos)
	{
		location2 = -1;
	}

	// Delimiter is used to destroy everything after the bool. default is the new line char '\n'.
	if (location2 != -1)
	{
		searchString = source.erase(location2);
	}
	else
	{
		searchString = source;
	}
// Debug
	std::cout << searchString << std::endl;



// Look for the var.
	if (searchString.find("true") == std::string::npos && searchString.find("True") == std::string::npos)
	{
		foundTrue = 0;
	}
	if (searchString.find( "True") != std::string::npos || searchString.find("true") != std::string::npos)
	{
		foundTrue = 1;
	}
	if (searchString.find("false") != std::string::npos || searchString.find("False") != std::string::npos)
	{
		foundFalse = 1;
	}
	if (searchString.find("false") == std::string::npos && searchString.find("False") == std::string::npos)
	{
		foundFalse = 0;
	}
	// See if we found a true or false statement.
	if (foundFalse == 1)
	{
		foundTrue = -1;
		foundFalse = -1;
		return false;
	}
	if (foundTrue == 1)
	{
		foundTrue = -1;
		foundFalse = -1;
		return true;
	}
	if (foundTrue == 0 && foundFalse == 0)
	{
		foundTrue = -1;
		foundFalse = -1;
		// Default return
		error.PanicHandler("DataProcess::getboolFromstring : Unknown Result.");
		return false;
	}
	else // Should not occur. Unless we get screwed up somewhere.
	{
		foundTrue = -1;
		foundFalse = -1;
		error.PanicHandler("DataProcess::getboolFromstring : Unknown Result.");
		return false;
	}

	//return "getboolFromstring: function incomplete.";	// default until function is complete.

}

long DataProcess::ConvertToBinary(int input)
{
  char intbuffer[32] = {0};
  char outputbuffer[32] = {0};
  int inputcounter = 0;
  int outputcounter = 0;
  while (input)
  {
    // Mod 2
    intbuffer[inputcounter] = (input % 2) + 0;
    input =  input / 2;
    inputcounter++;
  }

  // Decrment counter untill we finish
  while(inputcounter--)
  {
    // Reverse the bit order
    outputbuffer[outputcounter] = intbuffer[inputcounter];
    // Incrment the output counter
    outputcounter++;
  }


  std::cout <<"Outputbuffer  = " <<outputbuffer[inputcounter] << std::endl << std::endl;
  return 0;
}

long int DataProcess::getnumberFromString(const char * string, size_t string_size)
{
        // Dumb check.
        if (string == NULL)
        {
                // Invalid string.
                return 0;
        }
        if (string_size <= 0)
        {
                // Invalid size.
                return 0;
        }

        // Init vars.
        long int result = 0;
        bool isNegative = false;
        bool check_negative = false;
        bool checked_negative = false;

        // Check for number.
        for (size_t x = 0; x < string_size; x++)
        {
                if ((string[x] == '-') && (check_negative == false) && (checked_negative == false))
                {
                        isNegative = true;
                        check_negative = true;
                }

                if ((string[x] >= '0' ) && (string[x] <= '9'))
                {
                        // Reset result.
                        result = 0;

                        // Begin Extraction loop.
                        for (size_t y = 0; y < (string_size-x); y++)
                        {
                                // Extract the number.
                                switch (string[(x+y)])
                                {
                                        case '0':
                                            result = (result*10)+0;
                                            break;
                                        case '1':
                                            result = (result*10)+1;
                                            break;
                                        case '2':
                                            result = (result*10)+2;
                                            break;
                                        case '3':
                                            result = (result*10)+3;
                                            break;
                                        case '4':
                                            result = (result*10)+4;
                                            break;
                                        case '5':
                                            result = (result*10)+5;
                                            break;
                                        case '6':
                                            result = (result*10)+6;
                                            break;
                                        case '7':
                                            result = (result*10)+7;
                                            break;
                                        case '8':
                                            result = (result*10)+8;
                                            break;
                                        case '9':
                                            result = (result*10)+9;
                                            break;
                                        default:
                                            // Check for a negative.
                                            if ((isNegative == true) && (checked_negative == true))
                                            {
                                                    // Make our number negative.
                                                    result = (result*-1);
                                            }
                                            return result;
                                            break;
                                };

                                // Check for the negative check.
                                if (check_negative == true)
                                {
                                        // It's a negative number.
                                        check_negative = false;
                                        checked_negative = true;
                                }
                        }
                        break;
                }

                // Check and see if a number was next to that negative.
                if (check_negative == true)
                {
                            // No number was found, so it must be a dash.
                            check_negative = false;
                            isNegative = false;
                }

                // Boundry check.
                if (x < 0)
                {
                        // Error.
                        return 0;
                }
                if ((x + 1) == string_size)
                {
                        // No number data in string.
                        return result;
                }
        }

        // Default return.
        return result;
}

size_t DataProcess::getSize_TFromString(const char * string, size_t string_size)
{
        // Dumb check.
        if (string == NULL)
        {
                // Invalid string.
                return 0;
        }
        if (string_size <= 0)
        {
                // Invalid size.
                return 0;
        }

        // Init vars.
        size_t result = 0;

        // Check for number.
        for (size_t x = 0; x < string_size; x++)
        {
                if ((string[x] >= '0' ) && (string[x] <= '9'))
                {
                        // Reset result.
                        result = 0;

                        // Begin Extraction loop.
                        for (size_t y = 0; y < (string_size-x); y++)
                        {
                                // Extract the number.
                                switch (string[(x+y)])
                                {
                                        case '0':
                                            result = (result*10)+0;
                                            break;
                                        case '1':
                                            result = (result*10)+1;
                                            break;
                                        case '2':
                                            result = (result*10)+2;
                                            break;
                                        case '3':
                                            result = (result*10)+3;
                                            break;
                                        case '4':
                                            result = (result*10)+4;
                                            break;
                                        case '5':
                                            result = (result*10)+5;
                                            break;
                                        case '6':
                                            result = (result*10)+6;
                                            break;
                                        case '7':
                                            result = (result*10)+7;
                                            break;
                                        case '8':
                                            result = (result*10)+8;
                                            break;
                                        case '9':
                                            result = (result*10)+9;
                                            break;
                                        default:
                                            return result;
                                            break;
                                };
                        }
                        break;
                }

                // Boundry check.
                if (x < 0)
                {
                        // Error.
                        return 0;
                }
                if ((x + 1) == string_size)
                {
                        // No number data in string.
                        return result;
                }
        }

        // Default return.
        return result;
}

DataProcess::Data_Object DataProcess::getStringFromSizeT(const size_t & number)
{
        // Init vars.
        DataProcess::Data_Object result;
        std::stringstream ss;

        // Blank result.
        result.clear();

        // Copy the size_t into the stringstream object.
        ss << number;

        // Allocate memory for the result string object.
        result.reserve(ss.tellp());

        // Copy the character data from the stringstream object to the result.
        for (int x = 0; ((x < ss.tellp()) && (x >= 0)); x++)
        {
                result += ss.get();
        }

        // Return the result.
        return result;
}

std::string DataProcess::getStdStringFromSizeT(const size_t & number)
{
        // Init vars.
        std::string result;
        std::stringstream ss;

        // Blank the string.
        result.clear();

        // Copy the size_t into the stringstream object.
        ss << number;

        // Allocate memory for the result string object.
        result.reserve(ss.tellp());

        // Copy the character data from the stringstream object to the result string.
        for (int x = 0; ((x < ss.tellp()) && (x >= 0)); x++)
        {
                result += ss.get();
        }

        // Return the result.
        return result;
}

DataProcess::Data_Object DataProcess::getStringFromInt(long int number)
{
        // Init vars.
        DataProcess::Data_Object result;
        result.clear();
        long int temp = 0;
        size_t count = 0;
        bool done = false;

        // Check and see if the number is zero.
        if (number == 0)
        {
                result = "0";
                return result;
        }

        // Check and see if number is negative.
        if (number < 0)
        {
                result = "-";
        }

        // Check and see if the number is between 0-9.
        if (((number > 0) && (number < 10)) || ((number > -10) && (number < 0)))
        {
                // Figure out what number it is.
                switch(number)
                {
                        case 0:
                            result += '0';
                            return result;
                            break;
                        case 1:
                            result += '1';
                            return result;
                            break;
                        case 2:
                            result += '2';
                            return result;
                            break;
                        case 3:
                            result += '3';
                            return result;
                            break;
                        case 4:
                            result += '4';
                            return result;
                            break;
                        case 5:
                            result += '5';
                            return result;
                            break;
                        case 6:
                            result += '6';
                            return result;
                            break;
                        case 7:
                            result += '7';
                            return result;
                            break;
                        case 8:
                            result += '8';
                            return result;
                            break;
                        case 9:
                            result += '9';
                            return result;
                            break;
                        default:
                            result.clear();
                            return result;
                            break;
                };
        }

        // Devide by 10 until we get a number between 0-9.
        while (!done)
        {
                // Check to determine which division to do.
                if (count == 0)
                {
                        // Do inital devide.
                        temp = (number / 10);
                }
                else
                {
                        // Devide by temp.
                        temp = (temp / 10);
                }

                count++;

                // We have to do the boundry checking diffrently if number is negative.
                if (number < 0)
                {
                        if ((temp > -10) && (temp < 1))
                        {
                                // Found the total amount of division we must do.
                                done = true;
                        }
                        if (temp > 0)
                        {
                                // Out of bounds.
                                result.clear();
                                return result;
                        }
                }
                else
                {
                        if ((temp < 10) && (temp > -1))
                        {
                                // Found the total amount of division we must do.
                                done = true;
                        }
                        if (temp < 0)
                        {
                                // Out of bounds.
                                result.clear();
                                return result;
                        }
                }
        }

        for (size_t x = 0; x <= count; x++)
        {
                // Compute the needed number.
                temp = number;
                if (x < count)
                {
                        temp = (temp / (10^x));
                }
                temp = (temp % 10);

                // Figure out what number it is.
                switch(temp)
                {
                        case 0:
                            result += '0';
                            break;
                        case 1:
                            result += '1';
                            break;
                        case 2:
                            result += '2';
                            break;
                        case 3:
                            result += '3';
                            break;
                        case 4:
                            result += '4';
                            break;
                        case 5:
                            result += '5';
                            break;
                        case 6:
                            result += '6';
                            break;
                        case 7:
                            result += '7';
                            break;
                        case 8:
                            result += '8';
                            break;
                        case 9:
                            result += '9';
                            break;
                        default:
                            result.clear();
                            return result;
                            break;
                };

                // Boundry check.
                if ((x > count) || (x < 0))
                {
                        result.clear();
                        return result;
                }
        }

        // Exit function.
        return result;
}

void DataProcess::dumpDataToConsole(const char * data, size_t length, size_t offset, bool print_bad_chars, bool memory_format)
{
        // Dumb Check.
        if (data == NULL)
        {
                // No data to print.
                return;
        }
        if (length <= 0)
        {
                // No data to print. (Bad length)
                return;
        }
        if (offset < 0)
        {
                // Invalid offset.
                return;
        }
        if (offset >= length)
        {
                // Invalid offset.
                return;
        }

        // Disable the memory_format option.
        memory_format = false;

        // Init vars.
        size_t collem_count = 0;

        // Check to see if we are printing non printable chars.
        if (print_bad_chars == false)
        {
                if (memory_format == true)
                {
                        // Begin main loop.
                        try{
                            // Output first number.
                            std::cout << "0 ";

                            // Begin loop.
                            for(size_t output_count = 1; output_count < length; output_count++)
                            {
                                    for (unsigned short x = 0; x < 10; x++)
                                    {
                                            // Output the output_count.
                                            std::cout << output_count;

                                            // Check and see if the current count is changing colloms.
                                            if ((output_count%10) == 0)
                                            {
                                                    /*
                                                            Determine the number of decimal places away from one.
                                                            So we can line up the output with the correct offset.
                                                    */
                                                    if ((output_count/(10^collem_count)) >= 10)
                                                    {
                                                            // Increment collom.
                                                            collem_count++;
                                                    }

                                                    for (size_t y = 1; y <= collem_count; y++)
                                                    {
                                                            std::cout << " ";
                                                    }
                                            }
                                            else
                                            {
                                                    for (size_t y = 1; y <= collem_count; y++)
                                                    {
                                                            std::cout << " ";
                                                    }
                                            }

                                            // Check for ending statement.
                                            if ((output_count%10) == 0)
                                            {
                                                    // Output newline.
                                                    std::cout << "\n";
                                            }
                                    }

                            }
                        }
                        catch(...)
                        {
                                // Flush buffer.
                                std::cout.flush();
                        }
                }

                // Begin main loop.
                try{
                    for (size_t x = offset; x < length; x++)
                    {
                            if ((data[x] > 31 ) && (data[x] < 127))
                            {
                                    if (memory_format == true)
                                    {
                                            std::cout << data[x] << " ";
                                    }
                                    else
                                    {
                                            std::cout << data[x];
                                    }
                            }
                            else
                            {
                                    if (memory_format == true)
                                    {
                                            std::cout << '.' << " ";
                                    }
                                    else
                                    {
                                            std::cout << '.';
                                    }
                            }
                            if (memory_format == true)
                            {
                                    if (x%15 == 0)
                                    {
                                            // Print current line.
                                            std::cout << (x/15) << "\n";
                                    }
                            }
                    }
                }
                catch(...)
                {
                        // Some error.

                        // Flush console buffer.
                        std::cout.flush();

                        // Output a newline.
                        std::cout << "\n\n";

                        // Exit function.
                        return;
                }
        }
        if (print_bad_chars == true)
        {
                // Begin main loop.
                try{
                        for(size_t x = offset; x < length; x++)
                        {
                                if ((data[x] > 31 ) && (data[x] < 127))
                                {
                                        std::cout << data[x] << " ";
                                }
                                else
                                {
                                        std::cout << " 0x" << (int)data[x] << " ";
                                }
                                if (memory_format == true)
                                {
                                        if (x%15 == 0)
                                        {
                                                // Print current line.
                                                std::cout << (x/15) << "\n";
                                        }
                                }
                        }
                }
                catch (...)
                {
                        // Some error.

                        // Flush console buffer.
                        std::cout.flush();

                        // Output a new line.
                        std::cout << "\n\n";

                        // Exit function.
                        return;
                }
        }

        // Flush console buffer.
        std::cout.flush();

        // Flush console buffer.
        std::cout.flush();

        // Default return.
        return;
}

short DataProcess::getnumberFromString(char input)
{
        // Convert the char.
        switch (input)
        {
                case '0':
                    return 0;
                    break;
                case '1':
                    return 1;
                    break;
                case '2':
                    return 2;
                    break;
                case '3':
                    return 3;
                    break;
                case '4':
                    return 4;
                    break;
                case '5':
                    return 5;
                    break;
                case '6':
                    return 6;
                    break;
                case '7':
                    return 7;
                    break;
                case '8':
                    return 8;
                    break;
                case '9':
                    return 9;
                    break;
                default:        // Not a number.
                    return 0;
                    break;
            };

            // Default return.
            return 0;
}

const char * DataProcess::Data_Object::get_Pointer() const
{
	/* Init vars. */
	const char * ptr = NULL;
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Check for valid C library object. */
	if (this->obj != NULL)
	{
		/* Call C library. */
		retFromCall = MSYS_DataObject_Get_Pointer(this->obj, &ptr);
	}

	/* Exit function. */
    return ptr;
}

char * DataProcess::Data_Object::get_Data_Copy() const
{
	/* Init vars. */
	char * ptr = NULL;
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Check for valid C library object. */
	if (this->obj != NULL)
	{
		/* Begin try block. */
		try {
			/* Call C library. */
			retFromCall = MSYS_DataObject_Get_Data_Copy(this->obj, &ptr);
			if ((retFromCall != COMMON_ERROR_SUCCESS) && (ptr != NULL))
			{
				DataProcess_Deallocate_CString(&ptr);
			}
		}
		catch (...)
		{
			if (ptr != NULL)
			{
				DataProcess_Deallocate_CString(&ptr);
			}
		}
	}

    /* Exit function. */
    return ptr;
}

DataProcess::Data_Object::Data_Object()
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	// Set variables to known safe values.
    this->obj = NULL;

	/* Attempt to allocate the C library object. */
	try {
		/* Call C Library. */
		retFromCall = MSYS_Create_DataObject((&(this->obj)));
		if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			MSYS_Destroy_DataObject(&(this->obj));
		}
	}
	catch(...)
	{
		// Error.
        this->clear();
	}
}

DataProcess::Data_Object::Data_Object(const DataProcess::Data_Object & source)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    // Set variables to known safe values.
    this->obj = NULL;

    // Now deep copy data if it is allocated.
    if (source.obj != NULL)
    {
        try {
			/* Call C Library. */
			retFromCall = MSYS_DataObject_Create_From_Existing_DataObject(source.obj, (&(this->obj)));
			if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
			{
				MSYS_Destroy_DataObject(&(this->obj));
			}
        }
        catch(...)
        {
            // Error.
            this->clear();
        }
    }
}

DataProcess::Data_Object::Data_Object(const std::string & source)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    // Set variables to known safe values.
    this->obj = NULL;

    // Now deep copy data if it is allocated.
    if (source.size() > 0)
    {
        try{
			/* Create the object. */
			retFromCall = MSYS_Create_DataObject(&(this->obj));
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (this->obj != NULL))
			{
				/* Copy the data. */
				retFromCall = MSYS_DataObject_Set_Data_From_CString(this->obj, source.c_str(), source.size());
				if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
				{
					MSYS_Destroy_DataObject(&(this->obj));
				}
			}
			else
			{
				if (this->obj != NULL)
				{
					MSYS_Destroy_DataObject(&(this->obj));
				}
			}
        }
        catch(...)
        {
            // Some error.
            this->clear();
        }
    }
}

DataProcess::Data_Object::Data_Object(const char * source, size_t str_length)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    // Set variables to known safe values.
    this->obj = NULL;

    // Now deep copy data if it is allocated.
    if ((source != NULL) && (str_length > 0))
    {
        try{
			/* Create the object. */
			retFromCall = MSYS_Create_DataObject(&(this->obj));
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (this->obj != NULL))
			{
				/* Copy the data. */
				retFromCall = MSYS_DataObject_Set_Data_From_CString(this->obj, source, str_length);
				if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
				{
					MSYS_Destroy_DataObject(&(this->obj));
				}
			}
			else
			{
				if (this->obj != NULL)
				{
					MSYS_Destroy_DataObject(&(this->obj));
				}
			}
        }
        catch(...)
        {
            // Some error.
            this->clear();
        }
    }
}

DataProcess::Data_Object::Data_Object(const char & source)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    // Set variables to known safe values.
    this->obj = NULL;

    // Now deep copy data if it is allocated.
    try{
		/* Create the object. */
		retFromCall = MSYS_Create_DataObject(&(this->obj));
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			/* Copy the data. */
			retFromCall = MSYS_DataObject_Set_Data_From_Char(this->obj, source);
			if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
			{
				MSYS_Destroy_DataObject(&(this->obj));
			}
		}
		else
		{
			if (this->obj != NULL)
			{
				MSYS_Destroy_DataObject(&(this->obj));
			}
		}
    }
    catch(...)
    {
        // Some error.
        this->clear();
    }
}

DataProcess::Data_Object & DataProcess::Data_Object::operator= (const DataProcess::Data_Object & source)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    // Prevent self assignment.
    if (this != &source)
    {
		/* Check for allocated buffer. */
		if (this->obj == NULL)
		{
			/* Allocate the data object. */
			retFromCall = MSYS_Create_DataObject(&(this->obj));
			if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
			{
				MSYS_Destroy_DataObject(&(this->obj));
			}
		}

        // Now deep copy data if it is allocated.
        if ((source.obj != NULL) && (this->obj != NULL))
        {
            try {
                retFromCall = MSYS_Deep_Copy_DataObject(source.obj, this->obj);
            }
            catch(...)
            {
                // Error.
                this->clear();
            }
        }
    }

    // Exit function.
    return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator= (const std::string & source)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for allocated buffer. */
	if (this->obj == NULL)
	{
		/* Allocate the data object. */
		retFromCall = MSYS_Create_DataObject(&(this->obj));
		if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			MSYS_Destroy_DataObject(&(this->obj));
		}
	}

    // Now copy data if it is allocated.
    if (this->obj != NULL)
    {
		// If the source is empty then we've already finished (the clear command above is enough).
		if (source.size() > 0)
		{
			try{
				retFromCall = MSYS_DataObject_Set_Data_From_CString(this->obj, source.c_str(), source.size());
			}
			catch(...)
			{
				// Some error.
				this->clear();
			}
		}
	}

    // Exit function.
    return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator= (const char & source)
{
    /* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for allocated buffer. */
	if (this->obj == NULL)
	{
		/* Allocate the data object. */
		retFromCall = MSYS_Create_DataObject(&(this->obj));
		if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			MSYS_Destroy_DataObject(&(this->obj));
		}
	}

	// Now copy data if the object is allocated.
    if (this->obj != NULL)
    {
		try{
			retFromCall = MSYS_DataObject_Set_Data_From_Char(this->obj, source);
		}
		catch(...)
		{
			// Some error.
			this->clear();
		}
	}

    // Exit function.
    return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator+= (const char & source)
{
    /* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for allocated buffer. */
	if (this->obj == NULL)
	{
		/* Allocate the data object. */
		retFromCall = MSYS_Create_DataObject(&(this->obj));
		if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			MSYS_Destroy_DataObject(&(this->obj));
		}
	}

	// Now copy data if the object is allocated.
    if (this->obj != NULL)
    {
		try{
			retFromCall = MSYS_DataObject_Append_Char(this->obj, source);
		}
		catch(...)
		{

		}
	}

    // Exit function.
    return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator+= (const std::string & source)
{
    /* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for allocated buffer. */
	if (this->obj == NULL)
	{
		/* Allocate the data object. */
		retFromCall = MSYS_Create_DataObject(&(this->obj));
		if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			MSYS_Destroy_DataObject(&(this->obj));
		}
	}

	// Now copy data if the object is allocated.
    if ((this->obj != NULL) && (source.size() > 0))
    {
		try{
			retFromCall = MSYS_DataObject_Append_CString(this->obj, source.c_str(), source.size());
		}
		catch(...)
		{

		}
	}

    // Exit function.
    return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator+= (const DataProcess::Data_Object & source)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Check for allocated buffer. */
	if (this->obj == NULL)
	{
		/* Allocate the data object. */
		retFromCall = MSYS_Create_DataObject(&(this->obj));
		if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
		{
			MSYS_Destroy_DataObject(&(this->obj));
		}
	}

	// Now copy data if the object is allocated.
    if ((this->obj != NULL) && (source.obj != NULL))
    {
		try{
			retFromCall = MSYS_DataObject_Append_DataObject(this->obj, source.obj);
		}
		catch(...)
		{

		}
	}

    // Exit function.
    return *this;
}

char * DataProcess::Data_Object::substr(size_t offset, size_t endpoint) const
{
 	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;
	char * ret = NULL;

	// Check vars.
    if (this->obj != NULL)
    {
		try{
			retFromCall = MSYS_DataObject_Substr(this->obj, offset, endpoint, &ret);
			if ((retFromCall != COMMON_ERROR_SUCCESS) && (ret != NULL))
			{
				DataProcess_Deallocate_CString(&ret);
			}
		}
		catch(...)
		{
			if (ret != NULL)
			{
				DataProcess_Deallocate_CString(&ret);
			}
		}
	}

    // Exit function.
    return ret;
}

int DataProcess::Data_Object::Buffer_Copy(const DataProcess::Data_Object & source, size_t copy_offset, size_t copy_length)
{
 	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;

	// Check vars.
	if ((this->obj != NULL) && (source.obj != NULL))
    {
		try{
			ret = MSYS_DataObject_Buffer_Copy(this->obj, source.obj, copy_offset, copy_length);
		}
		catch(...)
		{
			ret = COMMON_ERROR_EXCEPTION_THROWN;
		}
	}
	else
	{
		/* Invalid object. */
		ret = COMMON_ERROR_SUBSYSTEM_OBJECT_NOT_INITED;
	}

    // Exit function.
    return ret;
}

bool DataProcess::Data_Object::Compare(const DataProcess::Data_Object &source) const
{
 	/* Init vars. */
	bool ret = false;
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Begin try block. */
	try{
		/* Call C library. (Note: It can handle invalid objects.) */
		retFromCall = MSYS_DataObject_Compare(this->obj, source.obj);
		ret = ((retFromCall == COMMON_ERROR_COMPARISON_PASSED) ? (true) : (false));
	}
	catch(...)
	{
		ret = false;
	}

    // Exit function.
    return ret;
}

bool DataProcess::Data_Object::NCompare(const DataProcess::Data_Object &source) const
{
        return !(this->Compare(source));
}

bool DataProcess::Data_Object::Data_Compare(const DataProcess::Data_Object & source) const
{
 	/* Init vars. */
	bool ret = false;
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Begin try block. */
	try{
		/* Call C library. (Note: It can handle invalid objects.) */
		retFromCall = MSYS_DataObject_Data_Compare(this->obj, source.obj);
		ret = ((retFromCall == COMMON_ERROR_COMPARISON_PASSED) ? (true) : (false));
	}
	catch(...)
	{
		ret = false;
	}

    // Exit function.
    return ret;
}

bool DataProcess::Data_Object::Data_NCompare(const DataProcess::Data_Object & source) const
{
        return !(this->Data_Compare(source));
}

void DataProcess::Data_Object::clear()
{
	/* Check for valid object. */
	if (this->obj != NULL)
	{
		MSYS_Clear_DataObject(this->obj);
	}

	/* Exit function. */
	return;
}

size_t DataProcess::Data_Object::get_length() const
{
	/* Init vars. */
	size_t ret = 0;

	/* Check for valid object. */
	if (this->obj != NULL)
	{
		try {
			MSYS_DataObject_Get_Length(this->obj, &ret);
		}
		catch(...)
		{
			/* Bad result... (Need to fix this function.) */
			ret = 0;
		}
	}

	/* Exit function. */
	return ret;
}

size_t DataProcess::Data_Object::get_Capacity() const
{
	/* Init vars. */
	size_t ret = 0;

	/* Check for valid object. */
	if (this->obj != NULL)
	{
		try {
			MSYS_DataObject_Get_Capacity(this->obj, &ret);
		}
		catch(...)
		{
			/* Bad result... (Need to fix this function.) */
			ret = 0;
		}
	}

	/* Exit function. */
	return ret;
}

size_t DataProcess::Data_Object::size() const
{
	/* Init vars. */
	size_t ret = 0;

	/* Check for valid object. */
	if (this->obj != NULL)
	{
		try {
			MSYS_DataObject_Get_Length(this->obj, &ret);
		}
		catch(...)
		{
			/* Bad result... (Need to fix this function.) */
			ret = 0;
		}
	}

	/* Exit function. */
	return ret;
}

int DataProcess::Data_Object::Shallow_Copy(const DataProcess::Data_Object & source)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Check for valid object. */
	if ((this->obj != NULL) && (source.obj != NULL))
	{
		/* Call C Library function. */
		retFromCall = MSYS_Shallow_Copy_DataObject(source.obj, this->obj);

		/* Set result. */
		ret = ((retFromCall != COMMON_ERROR_INVALID_ARGUMENT) ? (retFromCall) : (COMMON_ERROR_SUBSYSTEM_OBJECT_NOT_INITED));
	}
	else
	{
		/* Invalid object. */
		ret = COMMON_ERROR_SUBSYSTEM_OBJECT_NOT_INITED;
	}

	/* Exit function. */
	return ret;
}

void DataProcess::Data_Object::set(const char * source, const size_t & source_length)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	// Check vars.
    if ((source != NULL) && (source_length > 0))
    {
        try{
			/* Create the object. (If needed.) */
			if (this->obj == NULL)
			{
				retFromCall = MSYS_Create_DataObject(&(this->obj));
				if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
				{
					MSYS_Destroy_DataObject(&(this->obj));
				}
			}
			else
			{
				/* Indicate that when we checked the object it was initilized. */
				retFromCall = COMMON_ERROR_SUCCESS;
			}

			/* Copy the data. */
			if ((this->obj != NULL) && (retFromCall == COMMON_ERROR_SUCCESS))
			{
				retFromCall = MSYS_DataObject_Set_Data_From_CString(this->obj, source, source_length);
				if ((retFromCall != COMMON_ERROR_SUCCESS) && (this->obj != NULL))
				{
					/* The object won't be modified here, but we need to return the error code. */
				}
			}
			else
			{
				/* Need to return an error here... */
			}
        }
        catch(...)
        {
			/* More error codes needed. */
        }
    }
}

void DataProcess::Data_Object::reset()
{
	/* Check for valid object. */
	if (this->obj != NULL)
	{
		try {
			MSYS_Reset_DataObject(this->obj);
		}
		catch(...)
		{
			/* Ignore the error. */
		}
	}

	/* Exit function. */
	return;
}

void DataProcess::Data_Object::reserve(size_t new_length)
{
	/* Init vars. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

	/* Check for valid object. */
	if (this->obj != NULL)
	{
		try {
			retFromCall = MSYS_DataObject_Reserve_Memory(this->obj, new_length);
		}
		catch(...)
		{
			/* Bad result... (Need to fix this function.) */

		}
	}

	/* Exit function. */
	return;
}

size_t DataProcess::Data_Object::insert(size_t offset, const char source)
{
    /* Init vars. */
    int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for valid object. */
    if (this->obj != NULL)
    {
        /* Call C library function. */
        retFromCall = MSYS_DataObject_Insert_CString(this->obj, offset, &source, sizeof(char));
    }

    /* Exit function. (Bad error code.) */
    return (sizeof(char));
}

size_t DataProcess::Data_Object::insert(size_t offset, const std::string & source)
{
    /* Init vars. */
    int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for valid object. */
    if ((this->obj != NULL) && (source.size() > 0))
    {
        /* Call C library function. */
        retFromCall = MSYS_DataObject_Insert_CString(this->obj, offset, source.c_str(), source.size());
    }

    /* Exit function. (Bad error code.) */
    return (source.size());
}

size_t DataProcess::Data_Object::insert(size_t offset, const DataProcess::Data_Object & source)
{
    /* Init vars. */
    int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

    /* Check for valid object. */
    if ((this->obj != NULL) && (source.obj != NULL))
    {
        /* Call C library function. */
        retFromCall = MSYS_DataObject_Insert_From_DataObject(this->obj, offset, source.obj);
    }

    /* Exit function. (Bad error code.) */
    return 1;
}

short DataProcess::RegularExpressionParser(const std::string & expression, const std::string & input, Panic::Panic_ERROR * error)
{
	// Dumb check.
	if (expression.size() <= 0)
	{
		// No expression given.
		if (error != NULL)
		{
            error->PanicHandler("RegularExpressionParser: No expression given, aborting.", CORE_ID, ERROR_VERBOSE);
		}
		return -5;
	}
	if (input.size() <= 0)
	{
		// No input string given.
        if (error != NULL)
        {
            error->PanicHandler("RegularExpressionParser: No input string given, aborting.", CORE_ID, ERROR_VERBOSE);
        }
		return -5;
	}

	// Declare special characters.
	const char ESCAPE_CHARACTER = '\\';
	const char MATCH_SINGLE_CHARACTER = '?';
	const char MATCH_MULTIPLE_CHARACTER = '*';
	const char BLOCK_QUOTE_CHARACTER = '"';

	// Init vars.
	size_t input_position = 0;          // Used to store current position in the input string.
	size_t expression_position = 0;         // Used to store current position in the expression string.
	size_t counter = 0;             // Used to count the increse in the regular expression position during a block quote match. (Considering we can't change it from the beginning until after the match is made.)
	const char * input_pointer = NULL;
	const char * exp_pointer = NULL;

	// Get pointers.
	input_pointer = input.c_str();
	exp_pointer = expression.c_str();

	// Check for valid pointers.
	if ((input_pointer == NULL) || (exp_pointer == NULL))
	{
		// Invalid pointers cannot continue.
		if (error != NULL)
		{
            error->PanicHandler("RegularExpressionParser: Invalid pointers cannot compare regular expression with input string, aborting.", CORE_ID, ERROR_VERBOSE);
		}
		return -9;
	}

	// Begin expression parsing loop.
	while ((expression_position >= 0) && (expression_position < expression.size()))
	{
		// Boundry check.
		if ((expression_position < 0) || (expression_position >= expression.size()))
		{
			// Out of bounds.
			if (error != NULL)
			{
                error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
			}
			return -9;
		}

		// Check for special characters.
		switch (exp_pointer[expression_position])
		{
			case MATCH_SINGLE_CHARACTER:        // Match any character.
				if (input_position >= input.size())
				{
					// Invalid match.
					if (error != NULL)
					{
                        error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, Match to any character when no characters remain. Aborting.", CORE_ID, ERROR_VERBOSE);
					}
					return -2;
				}
				else
				{
					// Increment the input position.
					input_position++;

					// Increment the expression position.
					expression_position++;
				}
				break;
			case MATCH_MULTIPLE_CHARACTER:      // Match any following characters.
				// Check for any remaining characters in the regular expression.
				if ((expression_position + 1) == expression.size())
				{
					// Any remaining characters in the input string match the regular expression.
					break;
				}
				else
				{
					// Block quote match.
					if (exp_pointer[(expression_position + 1)] == BLOCK_QUOTE_CHARACTER)
					{
						/*
						    This is a special case. We have to match the exact string in the block quote to stop.
						    First increment the expression position.
						*/
						expression_position += 2;

						// Now check to see if there is data after this point.
						if ((expression_position + 1) >= expression.size())
						{
							// End of expression.
							if (error != NULL)
							{
                                error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, no characters remain in regular expression after initial block quote special character. Aborting.", CORE_ID, ERROR_VERBOSE);
							}
							return -5;
						}

						// Start sub-parsing loop.
						while ((input_position >= 0) && (input_position < input.size()))
						{
							// Boundry check.
							if ((input_position < 0) || (input_position >= input.size()) || ((expression_position + counter) < 0) || ((expression_position + counter) >= expression.size()))
							{
								// Out of bounds.
								if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
								}
								return -9;
							}

							// Check for special character in the expression.
							switch (exp_pointer[(expression_position + counter)])
							{
								case MATCH_SINGLE_CHARACTER:    // Match any character.
									// Increment input_position and counter.
									counter++;
									input_position++;
									break;
								case MATCH_MULTIPLE_CHARACTER:  // Match any character (multiple version.)
									// ERROR: Attempt to match multiple characters while we are matching multiple characters.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, match multiple character found inside of a block quote following another match multiple character. This behavoir is not supported. You cannot use the match multiple character while matching multiple characters. Aborting.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -5;
									break;
								case BLOCK_QUOTE_CHARACTER: // End of block quote.
									// ERROR: End of block quote should have been detected at the start of this loop not here.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Internal error: End of block quote detected in special character check. This should have already been detected. Aborting.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -9;
									break;
								case ESCAPE_CHARACTER:  // Look for special character in the input string.
									// Check for remaining characters in the regular expression.
									if (((expression_position + counter) + 1) > expression.size())
									{
										// No characters after escape character.
                                        if (error != NULL)
                                        {
                                            error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, last character in the expression is an escape character, Aborting.", CORE_ID, ERROR_VERBOSE);
                                        }
										return -5;
									}

									// Check the next symbol in the reqular expression.
									switch (exp_pointer[((expression_position + counter) + 1)])
									{
										case MATCH_SINGLE_CHARACTER:        // Match a ? character in the input string.
											break;
										case MATCH_MULTIPLE_CHARACTER:      // Match a * character in the input string.
											break;
										case ESCAPE_CHARACTER:          // Match a \ character int the input string.
											break;
										case BLOCK_QUOTE_CHARACTER:     // Match a " character in the input string.
											break;
										default:                // Invalid regular expression, escape character without following special symbol.
                                            if (error != NULL)
                                            {
                                                error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, encountered an escape character without a following speical character. Aborting.", CORE_ID, ERROR_VERBOSE);
                                            }
											return -5;
											break;
									};

									if (exp_pointer[((expression_position + counter) + 1)] != input_pointer[input_position])
									{
										// This is not the termination string. (I.e the block quote does not match this section of the input.) Therefore this is part of the match multiple character.

										// Reset counter.
										counter = 0;

										// Increment input position.
										input_position++;
									}
									else
									{
										// Increment input_position and counter.
										counter += 2;
										input_position++;
									}
									break;
								default:    // Compare against normal character. (Default.)
									if (exp_pointer[(expression_position + counter)] != input_pointer[input_position])
									{
										// This is not the termination string. (I.e the block quote does not match this section of the input.) Therefore this is part of the match multiple character.

										// Reset counter.
										counter = 0;

										// Increment input position.
										input_position++;
									}
									else
									{
										// Increment input_position and counter.
										counter++;
										input_position++;
									}
									break;
							};

                            // Check for end of expression.
							if ((expression_position + counter) >= expression.size())
							{
								// End of expression.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, no characters remain in regular expression while in block quote. All block quotes must be terminated with the block quote character. Aborting.", CORE_ID, ERROR_VERBOSE);
								}
								return -5;
							}

                            // Check for end of block quote
                            if (exp_pointer[(expression_position + counter)] == BLOCK_QUOTE_CHARACTER)
                            {
                                // End of block quote reached, update the expression position.
                                expression_position += (counter + 1);

                                // Exit loop.
                                break;
                            }

                            // Check for end of input string.
							if (input_position >= input.size())
							{
                                // End of input string.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string without a match to the block quote string.", CORE_ID, ERROR_VERBOSE);
								}
                                return -2;
							}
						}

						// Reset counter.
						counter = 0;
					}
					else
					{
						// Match escape character.
						if (exp_pointer[(expression_position + 1)] == ESCAPE_CHARACTER)
						{
							// Check for remaining characters in the regular expression.
							if ((expression_position + 2) >= expression.size())
							{
								// No characters after escape character.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, last character in the expression is an escape character, Aborting.", CORE_ID, ERROR_VERBOSE);
								}
								return -5;
							}

							// Check the next symbol in the reqular expression.
							switch (exp_pointer[(expression_position + 2)])
							{
								case MATCH_SINGLE_CHARACTER:        // Match a ? character in the input string.
									break;
								case MATCH_MULTIPLE_CHARACTER:      // Match a * character in the input string.
									break;
								case ESCAPE_CHARACTER:          // Match a \ character int the input string.
									break;
								case BLOCK_QUOTE_CHARACTER:     // Match a " character in the input string.
									break;
								default:                // Invalid regular expression, escape character without following special symbol.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, encountered an escape character without a following speical character. Aborting.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -5;
									break;
							};

							// Check for remaining characters in the input string.
							if ((input_position + 1) >= input.size())
							{
								// No characters remain in input string.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for special character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
								}
								return -2;
							}

							// Cycle through the remaining input string looking for the given character, if it is not found the input string does not match the expresion.
							while ((input_position >= 0) && (input_position < input.size()))
							{
                                // Boundry check.
								if ((input_position < 0) || (input_position >= input.size()))
								{
									// Out of bounds.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -9;
								}

								// OK we are looking for a special character in the input string.
								if (exp_pointer[(expression_position + 2)] == input_pointer[input_position])
								{
									// Increment the input position.
									input_position++;

									// Increment expression position.
									expression_position += 3;

									// Get out of this loop.
									break;
								}

								// Check for end of loop.
								if ((input_position + 1) >= input.size())
								{
									// Input string does not match the given expression.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for special character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
                                    }
									return -2;
								}
								else
								{
								    // Increment input position.
								    input_position++;
								}
							}
						}
						else
						{
							// Check for remaining characters in the input string.
							if ((input_position + 1) >= input.size())
							{
								// No characters remain in input string.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for normal character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
								}
								return -2;
							}

							// Match next character in the input string against this character in the expression.
							while ((input_position >= 0) && (input_position < input.size()))
							{
                                // Boundry check.
								if ((input_position < 0) || (input_position >= input.size()))
								{
									// Out of bounds.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -9;
								}

								// OK we are looking for a special character in the input string.
								if (exp_pointer[(expression_position + 1)] == input_pointer[input_position])
								{
									// Increment the input position.
									input_position++;

									// Increment the expression position.
									expression_position += 2;

									// Get out of this loop.
									break;
								}

								// Check for end of loop.
								if ((input_position + 1) >= input.size())
								{
									// Input string does not match the given expression.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for normal character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
                                    }
									return -2;
								}
								else
								{
								    // Increment input position.
								    input_position++;
								}
							}
						}
					}
				}
				break;
			case ESCAPE_CHARACTER:          // Escape Character.
				// Check that the regular expression has another character.
				if ((expression_position + 1) >= expression.size())
				{
					// No remaining characters to process in the regular expression.
                    if (error != NULL)
                    {
                        error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, last character in the expression is an escape character, Aborting.", CORE_ID, ERROR_VERBOSE);
                    }
					return -5;
				}

				// Check the next symbol in the reqular expression.
				switch (exp_pointer[(expression_position + 1)])
				{
					case MATCH_SINGLE_CHARACTER:        // Match a ? character in the input string.
						if (input_pointer[(input_position)] != MATCH_SINGLE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character MATCH_SINGLE_CHARACTER is not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					case MATCH_MULTIPLE_CHARACTER:      // Match a * character in the input string.
						if (input_pointer[(input_position)] != MATCH_MULTIPLE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character MATCH_MULTIPLE_CHARACTER not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					case ESCAPE_CHARACTER:          // Match a \ character int the input string.
						if (input_pointer[(input_position)] != ESCAPE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character ESCAPE_CHARACTER not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					case BLOCK_QUOTE_CHARACTER:     // Match a " character in the input string.
						if (input_pointer[(input_position)] != BLOCK_QUOTE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character BLOCK_QUOTE_CHARACTER not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					default:                // Invalid regular expression, escape character without following special symbol.
                        if (error != NULL)
                        {
                            error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, encountered an escape character without a following speical character. Aborting.", CORE_ID, ERROR_VERBOSE);
                        }
						return -5;
						break;
				};

				// Increment the input position and regular expression position.
				input_position++;
				expression_position += 2;
				break;
			case BLOCK_QUOTE_CHARACTER: // This is not valid without a MATCH_MULTIPLE_CHARACTER proceeding it. The other valid use is to terminate a block quote following the former case.
                if (error != NULL)
                {
                    error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, block quote character encountered in expression not following a match multiple character, nor terminating a block quote. (Free standing block quote.) This is not permitted, Aborting.", CORE_ID, ERROR_VERBOSE);
                }
				return -5;
				break;
			default:    // No special character.
				if (exp_pointer[expression_position] != input_pointer[input_position])
				{
                    if (error != NULL)
                    {
                        error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, normal character not present in the input string.", CORE_ID, ERROR_VERBOSE);
                    }
					return -2;
				}
				else
				{
					// Increment the input position and regular expression position.
					input_position++;
					expression_position++;
				}
				break;
		};

        // Check for end of expression.
        if ((expression_position + 1) >= expression.size())
        {
            // Check and see if we are at the end of the input string.
            if (input_position == input.size())
            {
                // We are at the end of the input string which means the expression matches the input string.
                if (error != NULL)
                {
                    error->PanicHandler("RegularExpressionParser: Regular expression matches the input string.", CORE_ID, ERROR_VERBOSE);
                }
                return 0;
            }
        }
	}

	// String does not match if we get here.
    if (error != NULL)
    {
        error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, reached the end of the expression.", CORE_ID, ERROR_VERBOSE);
    }
	return -2;
}

short DataProcess::RegularExpressionParser(const DataProcess::Data_Object & expression, const DataProcess::Data_Object & input, Panic::Panic_ERROR * error)
{
	// Dumb check.
	if (expression.size() <= 0)
	{
		// No expression given.
		if (error != NULL)
		{
            error->PanicHandler("RegularExpressionParser: No expression given, aborting.", CORE_ID, ERROR_VERBOSE);
		}
		return -5;
	}
	if (input.size() <= 0)
	{
		// No input string given.
        if (error != NULL)
        {
            error->PanicHandler("RegularExpressionParser: No input string given, aborting.", CORE_ID, ERROR_VERBOSE);
        }
		return -5;
	}

	// Declare special characters.
	const char ESCAPE_CHARACTER = '\\';
	const char MATCH_SINGLE_CHARACTER = '?';
	const char MATCH_MULTIPLE_CHARACTER = '*';
	const char BLOCK_QUOTE_CHARACTER = '"';

	// Init vars.
	size_t input_position = 0;          // Used to store current position in the input string.
	size_t expression_position = 0;         // Used to store current position in the expression string.
	size_t counter = 0;             // Used to count the increse in the regular expression position during a block quote match. (Considering we can't change it from the beginning until after the match is made.)
	const char * input_pointer = NULL;
	const char * exp_pointer = NULL;

	// Get pointers.
	input_pointer = input.get_Pointer();
	exp_pointer = expression.get_Pointer();

	// Check for valid pointers.
	if ((input_pointer == NULL) || (exp_pointer == NULL))
	{
		// Invalid pointers cannot continue.
		if (error != NULL)
		{
            error->PanicHandler("RegularExpressionParser: Invalid pointers cannot compare regular expression with input string, aborting.", CORE_ID, ERROR_VERBOSE);
		}
		return -9;
	}

	// Begin expression parsing loop.
	while ((expression_position >= 0) && (expression_position < expression.size()))
	{
		// Boundry check.
		if ((expression_position < 0) || (expression_position >= expression.size()))
		{
			// Out of bounds.
			if (error != NULL)
			{
                error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
			}
			return -9;
		}

		// Check for special characters.
		switch (exp_pointer[expression_position])
		{
			case MATCH_SINGLE_CHARACTER:        // Match any character.
				if (input_position >= input.size())
				{
					// Invalid match.
					if (error != NULL)
					{
                        error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, Match to any character when no characters remain. Aborting.", CORE_ID, ERROR_VERBOSE);
					}
					return -2;
				}
				else
				{
					// Increment the input position.
					input_position++;

					// Increment the expression position.
					expression_position++;
				}
				break;
			case MATCH_MULTIPLE_CHARACTER:      // Match any following characters.
				// Check for any remaining characters in the regular expression.
				if ((expression_position + 1) == expression.size())
				{
					// Any remaining characters in the input string match the regular expression.
					break;
				}
				else
				{
					// Block quote match.
					if (exp_pointer[(expression_position + 1)] == BLOCK_QUOTE_CHARACTER)
					{
						/*
						    This is a special case. We have to match the exact string in the block quote to stop.
						    First increment the expression position.
						*/
						expression_position += 2;

						// Now check to see if there is data after this point.
						if ((expression_position + 1) >= expression.size())
						{
							// End of expression.
							if (error != NULL)
							{
                                error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, no characters remain in regular expression after initial block quote special character. Aborting.", CORE_ID, ERROR_VERBOSE);
							}
							return -5;
						}

						// Start sub-parsing loop.
						while ((input_position >= 0) && (input_position < input.size()))
						{
							// Boundry check.
							if ((input_position < 0) || (input_position >= input.size()) || ((expression_position + counter) < 0) || ((expression_position + counter) >= expression.size()))
							{
								// Out of bounds.
								if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
								}
								return -9;
							}

							// Check for special character in the expression.
							switch (exp_pointer[(expression_position + counter)])
							{
								case MATCH_SINGLE_CHARACTER:    // Match any character.
									// Increment input_position and counter.
									counter++;
									input_position++;
									break;
								case MATCH_MULTIPLE_CHARACTER:  // Match any character (multiple version.)
									// ERROR: Attempt to match multiple characters while we are matching multiple characters.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, match multiple character found inside of a block quote following another match multiple character. This behavoir is not supported. You cannot use the match multiple character while matching multiple characters. Aborting.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -5;
									break;
								case BLOCK_QUOTE_CHARACTER: // End of block quote.
									// ERROR: End of block quote should have been detected at the start of this loop not here.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Internal error: End of block quote detected in special character check. This should have already been detected. Aborting.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -9;
									break;
								case ESCAPE_CHARACTER:  // Look for special character in the input string.
									// Check for remaining characters in the regular expression.
									if (((expression_position + counter) + 1) > expression.size())
									{
										// No characters after escape character.
                                        if (error != NULL)
                                        {
                                            error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, last character in the expression is an escape character, Aborting.", CORE_ID, ERROR_VERBOSE);
                                        }
										return -5;
									}

									// Check the next symbol in the reqular expression.
									switch (exp_pointer[((expression_position + counter) + 1)])
									{
										case MATCH_SINGLE_CHARACTER:        // Match a ? character in the input string.
											break;
										case MATCH_MULTIPLE_CHARACTER:      // Match a * character in the input string.
											break;
										case ESCAPE_CHARACTER:          // Match a \ character int the input string.
											break;
										case BLOCK_QUOTE_CHARACTER:     // Match a " character in the input string.
											break;
										default:                // Invalid regular expression, escape character without following special symbol.
                                            if (error != NULL)
                                            {
                                                error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, encountered an escape character without a following speical character. Aborting.", CORE_ID, ERROR_VERBOSE);
                                            }
											return -5;
											break;
									};

									if (exp_pointer[((expression_position + counter) + 1)] != input_pointer[input_position])
									{
										// This is not the termination string. (I.e the block quote does not match this section of the input.) Therefore this is part of the match multiple character.

										// Reset counter.
										counter = 0;

										// Increment input position.
										input_position++;
									}
									else
									{
										// Increment input_position and counter.
										counter += 2;
										input_position++;
									}
									break;
								default:    // Compare against normal character. (Default.)
									if (exp_pointer[(expression_position + counter)] != input_pointer[input_position])
									{
										// This is not the termination string. (I.e the block quote does not match this section of the input.) Therefore this is part of the match multiple character.

										// Reset counter.
										counter = 0;

										// Increment input position.
										input_position++;
									}
									else
									{
										// Increment input_position and counter.
										counter++;
										input_position++;
									}
									break;
							};

                            // Check for end of expression.
							if ((expression_position + counter) >= expression.size())
							{
								// End of expression.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, no characters remain in regular expression while in block quote. All block quotes must be terminated with the block quote character. Aborting.", CORE_ID, ERROR_VERBOSE);
								}
								return -5;
							}

                            // Check for end of block quote
                            if (exp_pointer[(expression_position + counter)] == BLOCK_QUOTE_CHARACTER)
                            {
                                // End of block quote reached, update the expression position.
                                expression_position += (counter + 1);

                                // Exit loop.
                                break;
                            }

                            // Check for end of input string.
							if (input_position >= input.size())
							{
                                // End of input string.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string without a match to the block quote string.", CORE_ID, ERROR_VERBOSE);
								}
                                return -2;
							}
						}

						// Reset counter.
						counter = 0;
					}
					else
					{
						// Match escape character.
						if (exp_pointer[(expression_position + 1)] == ESCAPE_CHARACTER)
						{
							// Check for remaining characters in the regular expression.
							if ((expression_position + 2) >= expression.size())
							{
								// No characters after escape character.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, last character in the expression is an escape character, Aborting.", CORE_ID, ERROR_VERBOSE);
								}
								return -5;
							}

							// Check the next symbol in the reqular expression.
							switch (exp_pointer[(expression_position + 2)])
							{
								case MATCH_SINGLE_CHARACTER:        // Match a ? character in the input string.
									break;
								case MATCH_MULTIPLE_CHARACTER:      // Match a * character in the input string.
									break;
								case ESCAPE_CHARACTER:          // Match a \ character int the input string.
									break;
								case BLOCK_QUOTE_CHARACTER:     // Match a " character in the input string.
									break;
								default:                // Invalid regular expression, escape character without following special symbol.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, encountered an escape character without a following speical character. Aborting.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -5;
									break;
							};

							// Check for remaining characters in the input string.
							if ((input_position + 1) >= input.size())
							{
								// No characters remain in input string.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for special character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
								}
								return -2;
							}

							// Cycle through the remaining input string looking for the given character, if it is not found the input string does not match the expresion.
							while ((input_position >= 0) && (input_position < input.size()))
							{
                                // Boundry check.
								if ((input_position < 0) || (input_position >= input.size()))
								{
									// Out of bounds.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -9;
								}

								// OK we are looking for a special character in the input string.
								if (exp_pointer[(expression_position + 2)] == input_pointer[input_position])
								{
									// Increment the input position.
									input_position++;

									// Increment expression position.
									expression_position += 3;

									// Get out of this loop.
									break;
								}

								// Check for end of loop.
								if ((input_position + 1) >= input.size())
								{
									// Input string does not match the given expression.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for special character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
                                    }
									return -2;
								}
								else
								{
								    // Increment input position.
								    input_position++;
								}
							}
						}
						else
						{
							// Check for remaining characters in the input string.
							if ((input_position + 1) >= input.size())
							{
								// No characters remain in input string.
                                if (error != NULL)
								{
                                    error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for normal character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
								}
								return -2;
							}

							// Match next character in the input string against this character in the expression.
							while ((input_position >= 0) && (input_position < input.size()))
							{
                                // Boundry check.
								if ((input_position < 0) || (input_position >= input.size()))
								{
									// Out of bounds.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Loop Out of Bounds error.", CORE_ID, ERROR_VERBOSE);
                                    }
									return -9;
								}

								// OK we are looking for a special character in the input string.
								if (exp_pointer[(expression_position + 1)] == input_pointer[input_position])
								{
									// Increment the input position.
									input_position++;

									// Increment the expression position.
									expression_position += 2;

									// Get out of this loop.
									break;
								}

								// Check for end of loop.
								if ((input_position + 1) >= input.size())
								{
									// Input string does not match the given expression.
                                    if (error != NULL)
                                    {
                                        error->PanicHandler("RegularExpressionParser: Regular expression does not match input string, reached end of input string while looking for normal character in input string. (Multiple Character Match Mode.)", CORE_ID, ERROR_VERBOSE);
                                    }
									return -2;
								}
								else
								{
								    // Increment input position.
								    input_position++;
								}
							}
						}
					}
				}
				break;
			case ESCAPE_CHARACTER:          // Escape Character.
				// Check that the regular expression has another character.
				if ((expression_position + 1) >= expression.size())
				{
					// No remaining characters to process in the regular expression.
                    if (error != NULL)
                    {
                        error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, last character in the expression is an escape character, Aborting.", CORE_ID, ERROR_VERBOSE);
                    }
					return -5;
				}

				// Check the next symbol in the reqular expression.
				switch (exp_pointer[(expression_position + 1)])
				{
					case MATCH_SINGLE_CHARACTER:        // Match a ? character in the input string.
						if (input_pointer[(input_position)] != MATCH_SINGLE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character MATCH_SINGLE_CHARACTER is not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					case MATCH_MULTIPLE_CHARACTER:      // Match a * character in the input string.
						if (input_pointer[(input_position)] != MATCH_MULTIPLE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character MATCH_MULTIPLE_CHARACTER not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					case ESCAPE_CHARACTER:          // Match a \ character int the input string.
						if (input_pointer[(input_position)] != ESCAPE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character ESCAPE_CHARACTER not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					case BLOCK_QUOTE_CHARACTER:     // Match a " character in the input string.
						if (input_pointer[(input_position)] != BLOCK_QUOTE_CHARACTER)
						{
							// Input string does not match the regular expression.
                            if (error != NULL)
                            {
                                error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, special character BLOCK_QUOTE_CHARACTER not at current position in the input string. Aborting.", CORE_ID, ERROR_VERBOSE);
                            }
							return -2;
						}
						break;
					default:                // Invalid regular expression, escape character without following special symbol.
                        if (error != NULL)
                        {
                            error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, encountered an escape character without a following speical character. Aborting.", CORE_ID, ERROR_VERBOSE);
                        }
						return -5;
						break;
				};

				// Increment the input position and regular expression position.
				input_position++;
				expression_position += 2;
				break;
			case BLOCK_QUOTE_CHARACTER: // This is not valid without a MATCH_MULTIPLE_CHARACTER proceeding it. The other valid use is to terminate a block quote following the former case.
                if (error != NULL)
                {
                    error->PanicHandler("RegularExpressionParser: Syntax error in regular expression, block quote character encountered in expression not following a match multiple character, nor terminating a block quote. (Free standing block quote.) This is not permitted, Aborting.", CORE_ID, ERROR_VERBOSE);
                }
				return -5;
				break;
			default:    // No special character.
				if (exp_pointer[expression_position] != input_pointer[input_position])
				{
                    if (error != NULL)
                    {
                        error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, normal character not present in the input string.", CORE_ID, ERROR_VERBOSE);
                    }
					return -2;
				}
				else
				{
					// Increment the input position and regular expression position.
					input_position++;
					expression_position++;
				}
				break;
		};

        // Check for end of expression.
        if ((expression_position + 1) >= expression.size())
        {
            // Check and see if we are at the end of the input string.
            if (input_position == input.size())
            {
                // We are at the end of the input string which means the expression matches the input string.
                if (error != NULL)
                {
                    error->PanicHandler("RegularExpressionParser: Regular expression matches the input string.", CORE_ID, ERROR_VERBOSE);
                }
                return 0;
            }
        }
	}

	// String does not match if we get here.
    if (error != NULL)
    {
        error->PanicHandler("RegularExpressionParser: Regular expression does not match the input string, reached the end of the expression.", CORE_ID, ERROR_VERBOSE);
    }
	return -2;
}
