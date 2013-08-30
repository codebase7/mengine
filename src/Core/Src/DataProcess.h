/*!
    Multiverse Engine Project DataProcess DataProcess.h

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

#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include "BaseHeader.h"
#include "Panic.h"

namespace DataProcess{

class Data_Object{
    private:
        char * data;        // Pointer to data.
        size_t length;      // Length of data.
        size_t capacity;    // Length of data we can store.

    public:
        Data_Object()
        {
                data = NULL;
                length = 0;
                capacity = 0;
        }
        ~Data_Object()
        {
                if (data != NULL)
                {
                        free(data);
                        data = NULL;
                }
                length = 0;
                capacity = 0;
        }
        Data_Object(const Data_Object & source);
        Data_Object(const std::string & source);
        Data_Object(const char * source, size_t str_length);
        Data_Object(const char & source);
        Data_Object & operator= (const Data_Object &source);
        Data_Object & operator= (const std::string &source);
        Data_Object & operator= (const char &source);
        Data_Object & operator+= (const char &source);
        Data_Object & operator+= (const std::string source);
        Data_Object & operator+= (const Data_Object & source);
        char * substr(size_t offset, size_t endpoint) const;

        /*!
            int DataProcess::Data_Object::Buffer_Copy(const DataProcess::Data_Object & source, size_t copy_offset, size_t copy_length)

            This function is designed to copy data from one data_object, to another without performing a memory reallocation.

            By default this function assumes to try and copy all data in the source data_object.

            Returns 0 on success.
            Returns -1 if the destionation buffer ran out of space before all of the requested data was copied.
            Returns -3 if the function reaches a default return.
            Returns -5 if the one or more of the following is true:
                        The source buffer has nothing in it.
                        The source buffer's data length is less than the requested amount of data to be copied.
                        The source buffer's data length is less than the requested offset.
                        The source buffer's data length is less than the requested offset plus the requested length.
            Returns -9 on a memory error, (Note You may need to re check the buffer to make sure that the data_object was not reallocated.)
        */
        int Buffer_Copy(const DataProcess::Data_Object & source, size_t copy_offset = 0, size_t copy_length = 0);

        /*!
                const char * DataProcess::Data_Object::get_Pointer() const

                This function returns a constant pointer to the Data_Object's data pointer.

                If the Data_Object has no allocated memory, capacity equals zero (0), this function returns NULL.
        */
        const char * get_Pointer() const;

        /*!
                char * DataProcess::Data_Object::get_Copy() const

                This function creates a copy of the data in the Data_Object and then returns a non-const pointer to that copy.

                Note: The copy that is created will not be freed after the Data_Object goes out of scope. (I.e is destroyed.)
                The caller must free the copy's memory on their own.

                If this function fails to allocate memory, it will return NULL.
        */
        char * get_Copy() const;
        size_t get_length() const
        {
                return this->length;
        }

        /*!
                size_t DataProcess::Data_Object::get_Capacity() const

                This function returns the capacity (total allocated memory)
                of the Data_Object.

                If no memory has been allocated this function returns zero (0).
        */
        size_t get_Capacity() const
        {
                return this->capacity;
        }

        /*!
                size_t DataProcess::Data_Object::size() const

                This function returns the current length (size) of actual data in
                the Data_Object.

                If no data is present zero (0) is returned.
        */
        size_t size() const
        {
                return this->length;
        }
        void set(const char * source, size_t source_length);

        /*!
                void DataProcess::Data_Object::clear()

                This function deallocates (frees) the Data_Object's memory, and resets
                length and capacity to zero (0).
        */
        void clear();

        /*!
                void DataProcess::Data_Object::reset()

                This function erases all data in the Data_Object, (Sets all bytes to NULL)
                and sets length to zero (0). The capacity is left unchanged.
        */
        void reset();

        /*!
                void DataProcess::Data_Object::reserve(size_t new_length)

                This function reserves memory (preallocates) for a Data_Object.

                Note: This function expects that the given length is the total amount
                of memory to allocate for the Data_Object, not the amount added.

                i.e if you have allocated 6 bytes, and then call this function with the amount
                of 7 bytes you will get a total size of 7 bytes not 13 bytes.

                This function tries to be non destructive. If a smaller length than what is
                already allocated is requested, this function will silently fail.

                This function can fail to allocate memory, if this occurs no modifications will
                be made to the Data_Object.

                This function can also fail to copy data to the new memory buffer, in this case
                the Data_Object will contain the data that was successfully copied prior to the failure.
                All other data will be lost.
        */
        void reserve(size_t new_length);
        bool Compare(const Data_Object &source) const;
        bool NCompare(const Data_Object &source) const;

        /*!
                bool DataProcess::Data_Object::Data_Compare(const DataProcess::Data_Object & source) const

                This function checks the data section of the Data_Object against another Data_Object to
                see if they equal each other.

                Note: Unlike DataProcess::Data_Object::Compare(), this function does not check capacity
                only length and actual data is checked.

                Returns true if both the length and data of the two Data_Objects are equal.
                Returns false if etheir the length or data does not match.
        */
        bool Data_Compare(const DataProcess::Data_Object & source) const;

        /*!
                bool DataProcess::Data_Object::Data_NCompare(const DataProcess::Data_Object & source) const

                This function checks the data section of the Data_Object against another Data_Object to
                see if they are not equal each other.

                Note: Unlike DataProcess::Data_Object::NCompare(), this function does not check capacity
                only length and actual data is checked.

                Returns false if both the length and data of the two Data_Objects are equal.
                Returns true if etheir the length or data does not match.
        */
        bool Data_NCompare(const DataProcess::Data_Object & source) const;

        /*!
                size_t DataProcess::Data_Object::insert(size_t offset, const char source)

                This function inserts a single char into the Data_Object at the given offset.

                Note: This function will reallocate the buffer if needed.

                Returns amount of inserted data if successfull. (In this case one (1).)
                Returns zero (0) if an error occurs or if no data was copied.
        */
        size_t insert(size_t offset, const char source);

        /*!
                size_t DataProcess::Data_Object::insert(size_t offset, const std::string & source)

                This function inserts a string into the Data_Object at the given offset.

                Note: This function will reallocate the buffer if needed.

                This function will copy all of the contents of the given string.

                Returns amount of inserted data if successfull.
                Returns zero (0) if an error occurs or if no data was copied.
        */
        size_t insert(size_t offset, const std::string & source);

        /*!
                size_t DataProcess::Data_Object::insert(size_t offset, const Data_Object & source)

                This function inserts a DataProcess::Data_Object's contents into the Data_Object at the given offset.

                Note: This function will reallocate the buffer if needed.

                This function will copy all of the contents of the given Data_Object.

                Returns amount of inserted data if successfull.
                Returns zero (0) if an error occurs or if no data was copied.
        */
        size_t insert(size_t offset, const Data_Object & source);
};

/*!
	size_t DataProcess::Trivial_Random_Number_Generator(const size_t & min_value, const size_t & max_value, const bool & reset_rand)
	
	This function generates psudo-random numbers based on the given max_value.
	
	@pram min_value, the minimum value that is acceptable for the function to return.
	@pram max_value, the maximum value that is acceptable for the function to return.
	
	E.x. If you want a range of 1 to 100 set min_value to 1 and max_value to 100.
	
	By default this function returns a number between 0 and 255.
	
	@pram reset_rand, if this is set to true, the rng will be re-seeded with the current time value returned by time(NULL).
	Otherwise the next psudo-random number from the current seed will be returned. (Default)
	
	Returns the generated psudo-random number.
*/
size_t Trivial_Random_Number_Generator(const size_t & min_value = 0, const size_t & max_value = 255, const bool & reset_rand = false);

/*!
        short DataProcess::IncrementingSort(std::vector<std::string> & sort)

        This function sorts strings by incrementing value.
        ( I.e The entire string is parsed, and the strings with
         characters that are larger in value than the previous string
         are moved up the list. I.e Have their positions swapped
         in the list.)

         Returns 0 on success.
         Returns -9 if an exception is thrown.
*/
short IncrementingSort(std::vector<std::string> & sort);

/*!
        short DataProcess::DecrementingSort(std::vector<std::string> & sort)

        This function sorts strings by decrementing value.
        ( I.e The entire string is parsed, and the strings with
         characters that are larger in value than the previous string
         are moved down the list. I.e Have their positions swapped
         in the list.)

         Returns 0 on success.
         Returns -9 if an exception is thrown.
*/
short DecrementingSort(std::vector<std::string> & sort);

/*!
    bool DataProcess::CheckForEOF(fstream & source)

    Checks the given file stream for eof (End of File) status and returns the result.

    Note: This function ignores the EOF (End of File) flag on the fstream. Instead it checks by checking the current get pointer's position
    against the end of the file.

    Returns true if the fstream is at EOF. (End of File)
    Returns false otherwise. (Note: This function will return false if the fstream has failed. (i.e source.fail() == true).)
*/
bool CheckForEOF(fstream & source);

/*!
    GenerateUID(long int length)

    Generates an pseduo-random alphanumeric string of given length. Default length is 25 charaters.
    WARNING: The longer the length the longer it will take to create the UID.

    Returns string of given length.
*/
std::string GenerateUID(long int length = 25);

/*!
        getnumberFromString(std::string source, std::string varName, std::string limiter , bool isdecimal, Panic::ERROR & error)

        Gets number(s) from a string.

        Returns number if successful.
        Otherwise returns 0.
*/
double getnumberFromString(std::string source, std::string varName, std::string limiter , bool isdecimal, Panic::ERROR & error);

/*!
        getIntFromInput()

        Gets an Integer from console, clears the Newline from the buffer, and then
        Returns the integer.

        Returns integer from console if successful,
        Otherwise returns 0.
*/
int getIntFromInput();

/*!
        bool DataProcess::yesNoConsolePrompt()

        Prompts the user via the console to answer a YES or NO question.

        Returns true if the user said YES.
        Otherwise returns false. (Defaults to NO.)
*/
bool yesNoConsolePrompt();

bool getboolFromstring(std::string source, std::string varName, char delimiter, Panic::ERROR & error);
// Reads input string for a true or false statement then returns the result.
// if no varible statement is found it returns the following string "ERROR: NO VAR."

// Takes a pointer to an integer and converts the integer back to a binary number.
// Return value is the binary equilvent to the given integer. Which is wrote back into the pointer.
long ConvertToBinary(int input);

/*!
        getnumberFromString(const char * string, size_t string_size)

        Extracts a number from the given string.

        Will skip any data before an actual number is found. After a number is found it will be extracted
        along with any number following it until etheir a non number is found (including end of stream), or
        the number of extracted numbers = sizeof(long int).

        Note: Will extract a negative number if number is proceeded by a '-'.

        Returns the extracted number on success.
        Returns zero (0) otherwise.
*/
long int getnumberFromString(const char * string, size_t string_size);

/*!
        size_t DataProcess::getSize_TFromString(const char * string, size_t string_size)

        Extracts an unsigned int from the given string.

        Will skip any data before an actual number is found. After a number is found it will be extracted
        along with any number following it until etheir a non number is found (including end of stream), or
        the number of extracted numbers = sizeof(long int).

        Note: Will extract a negative number if number is proceeded by a '-'.

        Returns the extracted number on success.
        Returns zero (0) otherwise.
*/
size_t getSize_TFromString(const char * string, size_t string_size);

/*!
        getnumberFromString(char input)

        Converts a single character to the number it repesents. Much like atoi().

        If the character given is not a number, then zero (0) is returned.
        Otherwise the number is returned.
*/
short getnumberFromString(char input);

/*!
        dumpDataToConsole(const char * data, size_t length, size_t offset, bool print_bad_chars, bool memory_format)

        Writes length amount of data in given pointer starting at offset to the console (std out).
        If data can't be printed on the console (i.e non char data) then one of the
        following takes place.

        If print_bad_chars is false (Default) then the char is
        replaced with a period (.)

        If print_bad_chars is true then the char code (char converted to int) is
        printed.

        memory_format is a method to print out the data with each character
        clearly numbered as an offset from the addess given. (This is off by
                                                              default.)
*/
void dumpDataToConsole(const char * data, size_t length, size_t offset = 0, bool print_bad_chars = false, bool memory_format = false);

/*!
        DataProcess::Data_Object DataProcess::getStringFromSizeT(size_t number)

        Takes given size_t and outputs the equilvent string in a DataProcess::Data_Object.

        Returns: DataProcess::Data_Object with string equilvent to number if successful.
        Returns: empty DataProcess::Data_Object if this function fails.
*/
DataProcess::Data_Object getStringFromSizeT(size_t number);

/*!
        DataProcess::Data_Object DataProcess::getStringFromInt(long int number)

        Takes the given integer, and outputs the equilvent string in a DataProcess::Data_Object.

        Note: This function operates on base-10 only.

        Returns: DataProcess::Data_Object with string equilvent to number if successful.
        Returns: empty DataProcess::Data_Object if this function fails.
*/
DataProcess::Data_Object getStringFromInt(long int number);

/*!
        short DataProcess::RegularExpressionParser(const std::string & expression, const std::string & input, Panic::ERROR * error)

        This function takes a input string and an expression string, compares them, then returns the result.
        This is the std::string version.

        This function can also be debugged by giving an error handler with the error level set to at least ERROR_VERBOSE or higher. By default no error handler is expected.

        Note: The documatation for the expression rules and syntax is in the docs subdirectory of the top level source directory. (Look for Regular_Expression_Rules.txt)

        Returns 0 if the expression matches the input string.
        Returns -2 if the expression does NOT match the input string.
        Returns -5 on an argument error. (Lack of string(s), or a syntax error in the expression string.)
        Returns -9 on control loop out of bounds, or a memory error.
*/
short RegularExpressionParser(const std::string & expression, const std::string & input, Panic::ERROR * error = NULL);

/*!
        short DataProcess::RegularExpressionParser(const DataProcess::Data_Object & expression, const DataProcess::Data_Object & input, Panic::ERROR * error)

        This function takes a input string and an expression string, compares them, then returns the result.
        This is the DataProcess::Data_Object version.

        This function can also be debugged by giving an error handler with the error level set to at least ERROR_VERBOSE or higher. By default no error handler is expected.

        Note: The documatation for the expression rules and syntax is in the docs subdirectory of the top level source directory. (Look for Regular_Expression_Rules.txt)

        Returns 0 if the expression matches the input string.
        Returns -2 if the expression does NOT match the input string.
        Returns -5 on an argument error. (Lack of string(s), or a syntax error in the expression string.)
        Returns -9 on control loop out of bounds, or a memory error.
*/
short RegularExpressionParser(const DataProcess::Data_Object & expression, const DataProcess::Data_Object & input, Panic::ERROR * error = NULL);
}

#endif

// End of DataProcess.h
