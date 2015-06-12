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

/* External includes. */
#include <ctime>

size_t DataProcess::Trivial_Random_Number_Generator(const size_t & min_value, const size_t & max_value, const bool & reset_rand)
{
	// NO, it's not 4..... (Although it could be. I won't lie.)

	// Set static.
	static bool rand_set;

	// Check if we need to set the rng.
	if ((!rand_set) || (reset_rand))
	{
		// Seed random number generator.
		srand(time(NULL));

		// Set rand_set.
		rand_set = true;
	}

	// Return the result.
	return (rand() % max_value + min_value);
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
                        // Exception thrown.
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
                        // Exception thrown.
                        return -9;
                }
        }

        // Exit function.
        return 0;
}

bool DataProcess::CheckForEOF(fstream & source)
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
                source.seekg(0, ios::end);

                // Compare positions.
                if (current_pos == (unsigned)source.tellg())
                {
                        // At EOF (End of File).
                        result = true;
                }

                // Seek back to the original position.
                source.seekg(current_pos, ios::beg);
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

double DataProcess::getnumberFromString(std::string source, std::string varName, std::string limiter , bool isdecimal, Panic::ERROR & error)
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
	if (source.find(varName) == string::npos)
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
				cout <<temp1 <<endl;
			}
			if (temp2 == "2")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "3")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "4")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "5")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "6")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "7")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "8")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "9")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == "0")
			{
				temp1 = temp1 += temp2;
				cout <<temp1 <<endl;
			}
			if (temp2 == real_limiter)
			{
				cout <<temp1 <<endl;
				number_found = true;
			}
			if (temp2 == ".")
			{
				if (isdecimal == true)
				{
					temp1 = temp1 += temp2;
					cout <<temp1 <<endl;
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

	// Check for exception, if thrown return 0. otherwise return result.
	try{
        istringstream (temp1) >> output;
	}
	catch(exception& ex){
        cout << "\n ERROR: DataProcess::getnumberFromString() Exception: " << ex.what() << "\n Clearing data buffer and returning zero.\n\n";

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
	cout <<" the result is: " <<output <<endl;
	return output;
}

int DataProcess::getIntFromInput()
{
	int number = 0;
	std::string dummy = "";
	cin >> number;
	getline(cin, dummy);    	// cin appends a end line char, so we use this to get rid of it. other wise it will show up on the next cin op.
	if (cin.fail() == true) 	// If this goes true user has inputed a non int.
	{
		cout << " invalid data \n ";
		// Fix the buffer.
		cin.clear();
		getline(cin, dummy);
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
        getline(cin, dummy);

        // Check result, if user said YES then return true.
        if (dummy == "YES")
        {
                return true;
        }

        // Otherwise return false.
        return false;
}

bool DataProcess::getboolFromstring(std::string source, std::string varName, char delimiter, Panic::ERROR & error)
{
	// Initlize the vars. Used to determine if we hit someting or not.
	int foundTrue = -1;
	int foundFalse = -1;
	int location1 = 0;
	int location2 = 0;
	char delimiterReal = ' ';
	std::string searchString = "";

	// Look for the var name
	if (source.find(varName) == string::npos)
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
	if (source.find(delimiterReal, location1) == string::npos)
	{
		location2 = -1;
	}
	if (source.find('\n', location1) == string::npos)
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
	cout << searchString <<endl;



// Look for the var.
	if (searchString.find("true") == string::npos && searchString.find("True") == string::npos)
	{
		foundTrue = 0;
	}
	if (searchString.find( "True") != string::npos || searchString.find("true") != string::npos)
	{
		foundTrue = 1;
	}
	if (searchString.find("false") != string::npos || searchString.find("False") != string::npos)
	{
		foundFalse = 1;
	}
	if (searchString.find("false") == string::npos && searchString.find("False") == string::npos)
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


  cout <<"Outputbuffer  = " <<outputbuffer[inputcounter] <<endl <<endl;
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
                            cout << "0 ";

                            // Begin loop.
                            for(size_t output_count = 1; output_count < length; output_count++)
                            {
                                    for (unsigned short x = 0; x < 10; x++)
                                    {
                                            // Output the output_count.
                                            cout << output_count;

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
                                                            cout << " ";
                                                    }
                                            }
                                            else
                                            {
                                                    for (size_t y = 1; y <= collem_count; y++)
                                                    {
                                                            cout << " ";
                                                    }
                                            }

                                            // Check for ending statement.
                                            if ((output_count%10) == 0)
                                            {
                                                    // Output newline.
                                                    cout << "\n";
                                            }
                                    }

                            }
                        }
                        catch(...)
                        {
                                // Flush buffer.
                                cout.flush();
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
                                            cout << data[x] << " ";
                                    }
                                    else
                                    {
                                            cout << data[x];
                                    }
                            }
                            else
                            {
                                    if (memory_format == true)
                                    {
                                            cout << '.' << " ";
                                    }
                                    else
                                    {
                                            cout << '.';
                                    }
                            }
                            if (memory_format == true)
                            {
                                    if (x%15 == 0)
                                    {
                                            // Print current line.
                                            cout << (x/15) << "\n";
                                    }
                            }
                    }
                }
                catch(...)
                {
                        // Some error.

                        // Flush console buffer.
                        cout.flush();

                        // Output a newline.
                        cout << "\n\n";

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
                                        cout << data[x] << " ";
                                }
                                else
                                {
                                        cout << " 0x" << (int)data[x] << " ";
                                }
                                if (memory_format == true)
                                {
                                        if (x%15 == 0)
                                        {
                                                // Print current line.
                                                cout << (x/15) << "\n";
                                        }
                                }
                        }
                }
                catch (...)
                {
                        // Some error.

                        // Flush console buffer.
                        cout.flush();

                        // Output a new line.
                        cout << "\n\n";

                        // Exit function.
                        return;
                }
        }

        // Flush console buffer.
        cout.flush();

        // Flush console buffer.
        cout.flush();

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
        return this->data;
}

char * DataProcess::Data_Object::get_Copy() const
{
        // Dumb check.
        if (this->data == NULL)
        {
                return NULL;
        }
        if (this->length <= 0)
        {
                return NULL;
        }

        // Init vars.
        char * result = NULL;

        try{
                result = (char*)malloc(this->length);
                memset(result, '\0', this->length);
                for(size_t x = 0; x < this->length; x++)
                {
                        result[x] = this->data[x];
                }
                return result;
        }
        catch(...)
        {
                if (result != NULL)
                {
                        free(result);
                        return NULL;
                }
        }

        // Default return.
        return NULL;
}

DataProcess::Data_Object::Data_Object(const DataProcess::Data_Object & source)
{
        // Set variables to known safe values.
        this->length = 0;
        this->capacity = 0;
        this->data = NULL;

        // Now deep copy data if it is allocated.
        if ((source.capacity > 0) && (source.data != NULL))
        {
                try {
                        this->data = (char*)malloc(source.capacity);
                        memset(this->data, '\0', source.capacity);

                        // Init loop.
                        for (size_t x = 0; x < source.capacity; x++)
                        {
                                this->data[x] = source.data[x];
                        }

                        // Set final vars.
                        this->length = source.length;
                        this->capacity = source.capacity;
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
        // Set variables to known safe values.
        this->length = 0;
        this->capacity = 0;
        this->data = NULL;

        // Now deep copy data if it is allocated.
        if (source.size() > 0)
        {
                try{
                        this->data = (char*)malloc(source.size());
                        memset(this->data, '\0', (source.size()));

                        for(size_t x = 0; x < source.size(); x++)
                        {
                                this->data[x] = source[x];
                        }

                        // Put the variable update here after we have actually set everything up.
                        this->length = source.size();
                        this->capacity = this->length;
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
        // Set variables to known safe values.
        this->length = 0;
        this->capacity = 0;
        this->data = NULL;

        // Now deep copy data if it is allocated.
        if ((source != NULL) && (str_length > 0))
        {
                try{
                        this->data = (char*)malloc(str_length);
                        memset(this->data, '\0', str_length);

                        for(size_t x = 0; x < str_length; x++)
                        {
                                this->data[x] = source[x];
                        }

                        // Put the variable update here after we have actually set everything up.
                        this->length = str_length;
                        this->capacity = str_length;
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
        // Set variables to known safe values.
        this->length = 0;
        this->capacity = 0;
        this->data = NULL;

        // Now deep copy data if it is allocated.
        try{
                // Allocate memory.
                this->data = (char*)malloc(1);
                memset(this->data, '\0', 1);

                // Set the source value.
                this->data[0] = source;

                // Put the variable update here after we have actually set everything up.
                this->length = 1;
                this->capacity = 1;
        }
        catch(...)
        {
                // Some error.
                this->clear();
        }
}

DataProcess::Data_Object & DataProcess::Data_Object::operator= (const DataProcess::Data_Object & source)
{
        // Prevent self assignment.
        if (this != &source)
        {
                // Set variables to known safe values.
                this->length = 0;
                this->capacity = 0;
                this->data = NULL;

                // Now deep copy data if it is allocated.
                if ((source.capacity > 0) && (source.data != NULL))
                {
                        try {
                                this->data = (char*)malloc(source.capacity);
                                memset(this->data, '\0', source.capacity);

                                // Init loop.
                                for (size_t x = 0; x < source.capacity; x++)
                                {
                                        this->data[x] = source.data[x];
                                }

                                // Set final vars.
                                this->length = source.length;
                                this->capacity = source.capacity;
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
        // Set varaiables to known safe values.
        this->length = 0;
        this->capacity = 0;
        this->data = NULL;

        // If the source is empty then we've already finished (the clear command above is enough).
        if (source.size() <= 0)
        {
                return *this;
        }

        try{
                this->data = (char*)malloc(source.size());
                memset(this->data, '\0', (source.size()));

                for(size_t x = 0; x < source.size(); x++)
                {
                        this->data[x] = source[x];
                }

                // Put the variable update here after we have actually set everything up.
                this->length = source.size();
                this->capacity = this->length;
        }
        catch(...)
        {
                // Some error.
                this->clear();
        }

        // Exit function.
        return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator= (const char & source)
{
        // Set varaiables to known safe values.
        this->length = 0;
        this->capacity = 0;
        this->data = NULL;

        try{
                // Allocate memory.
                this->data = (char*)malloc(1);
                memset(this->data, '\0', 1);

                // Set the source value.
                this->data[0] = source;

                // Put the variable update here after we have actually set everything up.
                this->length = 1;
                this->capacity = 1;
        }
        catch(...)
        {
                // Some error.
                this->clear();
        }

        // Exit function.
        return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator+= (const char & source)
{
        // Init vars.
        char * result = NULL;

        // Check and see if we need to reallocate memory.
        try{
                if ((this->length + 1) <= this->capacity)
                {
                        this->data[(this->length)] = source;
                        this->length++;
                }
                else
                {
                        result = (char*)malloc((this->capacity + 1));
                        memset(result, '\0', (this->capacity + 1));
                        if (this->length > 0)
                        {
                                for(size_t x = 0; x < (this->length); x++)
                                {
                                        result[x] = this->data[x];
                                }
                        }
                        result[(this->length)] = source;
                        free(this->data);
                        this->data = result;
                        this->length++;
                        this->capacity++;
                        result = NULL;
                }
        }
        catch(...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                this->clear();
        }

        // Exit function.
        return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator+= (const std::string source)
{
        // Check for blank string.
        if (source.size() <= 0)
        {
                return *this;
        }

        // Init var.
        char * result = NULL;
        size_t old_size = this->length;

        // Check and see if we need to reallocate memory.
        try{
                if ((this->length + source.size()) <= this->capacity)
                {
                        // Copy the data into the buffer.
                        for (size_t x = 0; x < source.size(); x++)
                        {
                                this->data[((old_size) + x)] = source[x];
                        }
                        this->length = ((old_size) + source.size());
                }
                else
                {
                        // Allocate the new buffer.
                        result = (char*)malloc((this->length + source.size()));
                        memset(result, '\0', (this->length + source.size()));

                        if (this->data != NULL)
                        {
                                // Copy data to new buffer then free the old one.
                                for(size_t x = 0; x < this->length; x++)
                                {
                                        result[x] = this->data[x];
                                }
                                this->clear();
                        }
                        for (size_t x = 0; x < (source.size()); x++)
                        {
                                // Copy the new data into the new buffer.
                                result[((old_size) + x)] = source[x];
                        }

                        // Set the new buffer, and update the length and capacity.
                        this->data = result;
                        this->length = (old_size + source.size());
                        this->capacity = this->length;
                }
        }
        catch(...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                this->clear();
        }

        // Exit function.
        return *this;
}

DataProcess::Data_Object & DataProcess::Data_Object::operator+= (const DataProcess::Data_Object & source)
{
        // Check for empty source.
        if (source.size() <= 0)
        {
                // Nothing to do.
                return *this;
        }

        // Init vars.
        char * result = NULL;
        size_t old_size = this->length;

        // Check and see if we need to reallocate memory.
        try{
                if ((this->length + source.size()) <= this->capacity)
                {
                        // Copy the data into the buffer.
                        for (size_t x = 0; x < source.size(); x++)
                        {
                                this->data[((old_size) + x)] = source.data[x];
                        }
                        this->length = ((old_size) + source.size());
                }
                else
                {
                        // Allocate new buffer.
                        result = (char*)malloc((this->length + source.size()));
                        memset(result, '\0', (this->length + source.size()));

                        // Copy old data into the new buffer.
                        if (this->data != NULL)
                        {
                                for(size_t x = 0; x < this->length; x++)
                                {
                                        result[x] = this->data[x];
                                }

                                // Clear the old data.
                                this->clear();
                        }

                        // Copy in new data.
                        for (size_t x = 0; x < (source.size()); x++)
                        {
                                result[((old_size)+x)] = source.data[x];
                        }

                        // Update the data pointer, and the length and capacity.
                        this->data = result;
                        this->length = (old_size + source.size());
                        this->capacity = this->length;
                }
        }
        catch (...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                this->clear();
        }

        // Exit function.
        return *this;
}

char * DataProcess::Data_Object::substr(size_t offset, size_t endpoint) const
{
        // Dumb check.
        if ((this->data == NULL) || (this->length <= 0))
        {
                // Nothing to do.
                return NULL;
        }
        if ((offset > this->length) || (offset < 0) || (offset >= endpoint))
        {
                // Invalid offset.
                return NULL;
        }
        if ((endpoint > this->length) || (endpoint < 0) || (endpoint <= offset))
        {
                // Invalid endpoint.
                return NULL;
        }

        // Init vars.
        char * result = NULL;
        size_t result_size = 0;

        // Compute diffrence between endpoint and offset.
        result_size = (endpoint - offset);
        if (result_size <= 0)
        {
                // Bad args.
                return NULL;
        }
        try{
                result = (char*)malloc(result_size);
                memset(result, '\0', result_size);
                for (size_t x = 0; x < result_size; x++)
                {
                        result[x] = this->data[(offset+x)];
                }
                return result;
        }
        catch(...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                return NULL;
        }

        if (result != NULL)
        {
                free(result);
                result = NULL;
        }
        // Default return.
        return result;
}

int DataProcess::Data_Object::Buffer_Copy(const DataProcess::Data_Object & source, size_t copy_offset, size_t copy_length)
{
        // Reset our buffers.
        this->reset();

        // Dumb check.
        if ((source.length <= 0) || (source.length < copy_offset))
        {
                // Can not copy non existant data.
                return -5;
        }
        if ((copy_offset == 0) && (copy_length == 0))
        {
                // Copy all data from source.
                copy_length = source.length;
        }
        if ((copy_offset != 0) && (copy_length == 0))
        {
                // Bad range.
                return -5;
        }
        if ((source.length < copy_length) || (source.length < (copy_offset + copy_length)))
        {
                // Bad range.
                return -5;
        }
        try{
                // Copy data.
                for (size_t x = 0; x < this->capacity; x++)
                {
                        // Get data.
                        this->data[x] = source.data[(copy_offset + x)];

                        // Increment length.
                        this->length++;

                        // Check for end of data.
                        if ((x + 1) == copy_length)
                        {
                                // Data copied.
                                return 0;
                        }

                        // Check for end of buffer.
                        if ((x + 1) == this->capacity)
                        {
                                // End of buffer, due to the fact that we ran out of space in the buffer, return -1.
                                return -1;
                        }

                        // Boundry check.
                        if ((x < 0) || (x >= this->capacity) || (x > copy_length))
                        {
                                // Out of bounds.
                                this->reset();
                                return -9;
                        }
                }
        }
        catch(...)
        {
                // Some error.
                this->reset();
                return -9;
        }

        // Default return.
        this->reset();
        return -3;
}

bool DataProcess::Data_Object::Compare(const DataProcess::Data_Object &source) const
{
        // Init var.
        const char * test = NULL;
        test = source.get_Pointer();

        if (source.get_length() != this->length)
        {
                return false;
        }

        if (source.get_Capacity() != this->capacity)
        {
                return false;
        }

        if ((this->data == NULL) && (test != NULL))
        {
                return false;
        }

        if ((this->data != NULL) && (test == NULL))
        {
                return false;
        }

        if ((test != NULL) && (this->data != NULL))
        {
                for (size_t x = 0; x < this->length; x++)
                {
                        if (this->data[x] != test[x])
                        {
                                return false;
                        }
                }
        }

        return true;
}

bool DataProcess::Data_Object::NCompare(const DataProcess::Data_Object &source) const
{
        return !(this->Compare(source));
}

bool DataProcess::Data_Object::Data_Compare(const DataProcess::Data_Object & source) const
{
        // Check length.
        if (source.length != this->length)
        {
                return false;
        }

        // Check pointers.
        if ((this->data == NULL) && (source.data != NULL))
        {
                return false;
        }

        if ((this->data != NULL) && (source.data == NULL))
        {
                return false;
        }

        // Check data.
        if ((source.data != NULL) && (this->data != NULL))
        {
                for (size_t x = 0; x < this->length; x++)
                {
                        if (this->data[x] != source.data[x])
                        {
                                return false;
                        }
                }
        }

        // Data is equal.
        return true;
}

bool DataProcess::Data_Object::Data_NCompare(const DataProcess::Data_Object & source) const
{
        return !(this->Data_Compare(source));
}

void DataProcess::Data_Object::clear()
{
        if (this->data != NULL)
        {
                free(this->data);
                this->data = NULL;
        }
        this->length = 0;
        this->capacity = 0;
        return;
}

void DataProcess::Data_Object::set(const char * source, const size_t & source_length)
{
        // Clear the old data.
        this->clear();

        // Dumb check.
        if (source == NULL)
        {
                // Nothing to do.
                return;
        }
        if (source_length <= 0)
        {
                // Nothing to do.
                return;
        }

        // Try and set the vars.
        try{
                // Allocate the new buffer.
                this->data = (char*)malloc(source_length);
                memset(this->data, '\0', source_length);

                // Copy the data into the new buffer.
                for(size_t x = 0; x < source_length; x++)
                {
                        this->data[x] = source[x];
                }

                // Update capacity and length.
                this->length = source_length;
                this->capacity = source_length;
        }
        catch(...)
        {
                this->clear();
        }

        // Exit function.
        return;
}

void DataProcess::Data_Object::reset()
{
        // Dumb check.
        if ((this->data == NULL) || (this->capacity <= 0))
        {
                // Nothing to do.
                return;
        }

        // Reset the data buffer.
        try{
                memset(this->data, '\0', (this->capacity - 1));
                this->length = 0;
                return;
        }
        catch(...)
        {
                // Error.
                return;
        }

        // Exit function.
        return;
}

void DataProcess::Data_Object::reserve(size_t new_length)
{
        // Check and see if length is less than our current size.
        if (new_length < this->length)
        {
                // Failsafe, we don't want to destroy data if we can help it.
                return;
        }

        // Init vars.
        char * temp_buffer = NULL;
        size_t old_length = 0;

        try{
                // Allocate new buffer.
                temp_buffer = (char*)malloc(new_length);
                if (temp_buffer == NULL)
                {
                        // Cannot allocate memory.
                        return;
                }
                memset(temp_buffer, '\0', new_length);
        }
        catch(...)
        {
                // Could not realloc memory.
                return;
        }

        // Copy old data if nessacarry.
        if (this->data != NULL)
        {
                try{
                        // Set old length.
                        old_length = this->length;

                        // Reset length.
                        this->length = 0;

                        // Copy the contents of the original data.
                        for (size_t x = 0; x < old_length; x++)
                        {
                                temp_buffer[x] = this->data[x];
                                this->length++;
                        }
                }
                catch(...)
                {

                }

                // Free the original buffer.
                if (this->data != NULL)
                {
                        free(this->data);
                        this->data = NULL;
                }

                // Set our new buffer.
                this->data = temp_buffer;

                // Set our new capacity.
                this->capacity = new_length;

                // Exit function.
                return;
        }
        else
        {
                // Set our new length.
                this->length = 0;

                // Set our new capacity.
                this->capacity = new_length;

                // Set our new buffer.
                this->data = temp_buffer;

                // Exit function.
                return;
        }

        // Default return.
        return;
}

size_t DataProcess::Data_Object::insert(size_t offset, const char source)
{
        // Check for bad offset.
        if ((offset < 0) || (offset > this->length))
        {
                // Bad offset.
                return 0;
        }

        // Init vars.
        char current_char = '\0';
        char next_char = '\0';
        char * result = NULL;

        // Check and see if we need to reallocate memory.
        try{
                if ((this->length + 1) <= this->capacity)
                {
                        // Set the inital current char, to the source value.
                        current_char = source;

                        // At the offset read in the next char.
                        for (size_t x = offset; x < (this->length); x++)
                        {
                                // Read in the next char.
                                next_char = this->data[x];

                                // Copy the current_char.
                                this->data[x] = current_char;

                                // Current char is updated.
                                current_char = next_char;
                        }

                        // Insert the last char.
                        this->data[(this->length)] = current_char;

                        // Increment the length.
                        this->length++;

                        // Exit function.
                        return 1;
                }
                else
                {
                        result = (char*)malloc((this->capacity + 1));
                        memset(result, '\0', (this->capacity + 1));
                        if (this->length > 0)
                        {
                                // Copy data until we reach the offset.
                                for(size_t x = 0; x < ((this->length) + 1); x++)
                                {
                                        // If we have not yet reached the offset, copy data directly.
                                        if (x < offset)
                                        {
                                                result[x] = this->data[x];
                                        }

                                        // If we are at the offset, copy the source value.
                                        if (x == offset)
                                        {
                                                result[x] = source;
                                        }

                                        /*
                                            If we are past the offset, copy the remaining data.
                                            Note: This is correct as x - 1 equals the data without
                                            the source value added.
                                        */
                                        if (x > offset)
                                        {
                                                result[x] = this->data[x - 1];
                                        }

                                }
                        }
                        else
                        {
                                // We have no data so just insert the source value.
                                this->data[0] = source;
                        }

                        // Free the old data buffer.
                        if (this->data != NULL)
                        {
                                free(this->data);
                                this->data = NULL;
                        }

                        // Set the new buffer.
                        this->data = result;

                        // Update length and capacity.
                        this->length++;
                        this->capacity++;

                        // Exit function.
                        return 1;
                }
        }
        catch(...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                this->clear();
        }

        // Default return.
        return 0;
}

size_t DataProcess::Data_Object::insert(size_t offset, const std::string & source)
{
        // Check for empty source.
        if (source.size() <= 0)
        {
                // Nothing to do.
                return 0;
        }

        // Check for bad offset.
        if ((offset < 0) || (offset > this->length))
        {
                // Bad offset.
                return 0;
        }

        // Init vars.
        size_t old_size = this->length;
        char * result = NULL;

        try{
                if ((this->length + source.size()) <= this->capacity)
                {
                        for (size_t x = 0; x < source.size(); x++)
                        {
                                if (this->insert((offset + x), source[x]) != 1)
                                {
                                        // Error Could not copy all data.
                                        return x;
                                }
                        }

                        // Exit the function.
                        return source.size();
                }
                else
                {
                        // Allocate new buffer.
                        result = (char*)malloc((this->length + source.size()));
                        memset(result, '\0', (this->length + source.size()));

                        // Copy old data into the new buffer until we reach the offset.
                        if (this->data != NULL)
                        {
                                for (size_t x = 0; x < offset; x++)
                                {
                                        result[x] = this->data[x];
                                }
                        }

                        // Copy in new data.
                        for (size_t x = 0; x < (source.size()); x++)
                        {
                                result[(offset + x)] = source[x];
                        }

                        // Copy remaining data from the old buffer.
                        if (this->data != NULL)
                        {
                                for(size_t x = offset; x < old_size; x++)
                                {
                                        result[(offset + (source.size()) + x)] = this->data[(offset + x)];
                                }
                        }

                        // Release the old memory.
                        if (this->data != NULL)
                        {
                                free(this->data);
                                this->data = NULL;
                        }

                        // Update the data pointer, and the length and capacity.
                        this->data = result;
                        this->length = (old_size + source.size());
                        this->capacity = this->length;

                        // Exit function.
                        return source.size();
                }
        }
        catch (...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                this->clear();
        }

        // Default return.
        return 0;
}

size_t DataProcess::Data_Object::insert(size_t offset, const DataProcess::Data_Object & source)
{
        // Check for empty source.
        if (source.size() <= 0)
        {
                // Nothing to do.
                return 0;
        }

        // Check for bad offset.
        if ((offset < 0) || (offset > this->length))
        {
                // Bad offset.
                return 0;
        }

        // Init vars.
        size_t old_size = this->length;
        char * result = NULL;

        try{
                if ((this->length + source.size()) <= this->capacity)
                {
                        // This is a single char insert, but short of creating a second buffer, This is the best way to do it.
                        for (size_t x = 0; x < source.size(); x++)
                        {
                                if (this->insert((offset + x), source.data[x]) != 1)
                                {
                                        // Error Could not copy all data.
                                        return x;
                                }
                        }

                        // Exit function.
                        return source.size();
                }
                else
                {
                        // Allocate new buffer.
                        result = (char*)malloc((this->length + source.size()));
                        memset(result, '\0', (this->length + source.size()));

                        // Copy old data into the new buffer until we reach the offset.
                        if (this->data != NULL)
                        {
                                for (size_t x = 0; x < offset; x++)
                                {
                                        result[x] = this->data[x];
                                }
                        }

                        // Copy in new data.
                        for (size_t x = 0; x < (source.size()); x++)
                        {
                                result[(offset + x)] = source.data[x];
                        }

                        // Copy remaining data from the old buffer.
                        if (this->data != NULL)
                        {
                                for(size_t x = offset; x < old_size; x++)
                                {
                                        result[(offset + (source.size()) + x)] = this->data[(offset + x)];
                                }
                        }

                        // Release the old memory.
                        if (this->data != NULL)
                        {
                                free(this->data);
                                this->data = NULL;
                        }

                        // Update the data pointer, and the length and capacity.
                        this->data = result;
                        this->length = (old_size + source.size());
                        this->capacity = this->length;

                        // Exit function.
                        return source.size();
                }
        }
        catch (...)
        {
                if (result != NULL)
                {
                        free(result);
                        result = NULL;
                }
                this->clear();
        }

        // Default return.
        return 0;
}

short DataProcess::RegularExpressionParser(const std::string & expression, const std::string & input, Panic::ERROR * error)
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

short DataProcess::RegularExpressionParser(const DataProcess::Data_Object & expression, const DataProcess::Data_Object & input, Panic::ERROR * error)
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
