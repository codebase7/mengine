/*!
    Multiverse Engine Project 11/19/2010 Core FileStreams.cpp
        
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

/* Core FileStreams: used to open, and close file streams.
all read and writes must be handled by the module that made the request.
Mode Values are

0 Create a new file (will not add to an existing file, if a file exists with the same filename it will be overwriiten.)
1 Append To File (if a file with the same file name does not exist it will be created.)
2 Read Only
*/
#include "FileStreams.h"

std::string FileStreams::configCreate(std::string path, Panic::Panic_ERROR & error)
{
	// init vars
	std::ofstream Ini;

	// open file on disk.
	Ini.open(path.c_str());

	// Make sure file is open
	if (Ini.is_open() == false)
	{
		error.PanicHandler("FileStreams::configCreate : Could not open file.");
		return "configCreate: Could not open file for writing.";
	}

	// Put in a comment.
	Ini << "# Config File \n";

	// Close file
	Ini.close();

	return "OK";
}

std::string FileStreams::configParser(std::string path, std::string key, Panic::Panic_ERROR & Error)
{
	// init vars

	std::ifstream Ini;
	bool dataFound = false;
	bool fileatEOF = false;
	bool fileFail = false;
	std::string temp = "";
	std::string output = "";
	long dStartLocation = -1;
	long dEndLocation = -1;
	long tempsize = 0;
	long diff = 0;

	// Open file
	Ini.open(path.c_str(), std::ios::in);

	// check if file open failed

	if (Ini.is_open() == false)
	{
		Error.PanicHandler("FileStreams::configParser : Error Opening File.");
		output = "ERROR: Opening File.";
		return output;
	}

	// get data from file.

	while (dataFound != true && fileatEOF != true && fileFail != true)
	{
		getline(Ini, temp);
		if (Ini.fail() == true)
		{
			// File Stream has errored out. Clear the buffers, close the file, warn the user, and exit the function.
			fileFail = true;
			Error.PanicHandler("FileStreams::configParser(): File Stream has failed.");
			Ini.close();
			output = "ERROR";
		}

		// Look for data in the temp buffer.
		if (temp.find_first_of("#") == 0)
		{
		  // Comment Line ignore it.
		  temp = "";
		}
		if (temp.find(key) != std::string::npos)
		{
			// data found. Condence variable to just data and return it.
			dStartLocation = temp.find("=");
			dStartLocation++;
			dEndLocation = temp.find(";");
			tempsize = temp.size();

			if (dEndLocation <= tempsize)
			{
			  // Compute size of data to import.
			  diff = dEndLocation - dStartLocation;
			  temp = temp.substr(dStartLocation, diff);
			}
			if (dEndLocation > tempsize)
			{
			  // Bad data don't load it. and throw error.
			  Error.PanicHandler("FileStreams::configParser(): data location out of buffer range.");
			  return "ERROR";
			}

			// Clear buffers and exit loop.
			dataFound = true;
			output = temp;
			Ini.close();
		}
		if (temp.find(key) == std::string::npos && Ini.eof() != true)
		{
			// data not found try again.
			fileatEOF = false;
		}
		if (temp.find(key) == std::string::npos && Ini.eof() == true)
		{
			// We didn't find what we were looking for so close the file, warn the user, clear the buffers, and exit the function.
			fileatEOF = true;
			Error.PanicHandler("data not found. reached end of file.");
			Ini.close();
			output = "ERROR";
		}
		temp = ""; // clear the buffer for the next go around.
	}
	return output;

}

std::string FileStreams::configWriter(std::string path, std::string key, std::string value, Panic::Panic_ERROR & error , bool createkey)
{
	// Init vars.
	std::fstream OUT;			// Output File stream
	bool keyfound = false;		// has key been found in file
	bool atEOF = false;		// has end of file been hit.
	std::string buffer = "";	// Temp buffer for data from file.
	long int location = 0;		// location of key in file.
	long int position = 0;		// current read / write position in file.

	// Open File
	OUT.open(path.c_str());

	// Check and see if the file was opened.
	if (OUT.is_open() == true)
	{
		// Panic Handler
		error.PanicHandler("FileStreams::configWriter : File could not be opened.");
		return "ERROR";
	}

	// Check if key is present
	while (keyfound == false && atEOF == false)
	{
		// Check if bad bit or EOF is set.
		if (OUT.fail() == true)
		{
			// Panic Handler
			error.PanicHandler("FileStreams::configWriter : Bad file stream.");
			atEOF = true;
		}
		if (OUT.eof() == true)
		{
			// At end of file.
			atEOF = true;
		}

		// Increase Position counter.
		position++;

		// Begin actual check for key.
		if (OUT.fail() != true && OUT.eof() != true)
		{
			// Get line from file
			getline(OUT , buffer);

			// Check buffer for std::string
			if (buffer.find(key.c_str()) != std::string::npos)
			{
				  // Key found
				  keyfound = true;

				  // Store location of key in file.
				  location = OUT.tellg();
			}
		}
	}

	// Close file.
	OUT.close();

	// If key is not present and createkey is false , throw error.
	if (keyfound == false && createkey == false)
	{
	  // Panic Handler
	  error.PanicHandler("FileStreams::configWriter : Value Key not found. Will not create key.");
	  // return
	  return "NO KEY";
	}


	// Open file in write mode.
	OUT.open(path.c_str(), std::ios::out);


	// If key is not present and createkey is true write key into file.

	if (keyfound == false && createkey == true)
	{
		// Seek to eof.
		OUT.seekp(std::ios::end);

		// Write key to file before writing variable.
		OUT << key <<" = " ;
	}

	// Seek to position if key was found previously.
	if (keyfound == true)
	{
		// Move to correct line.
		OUT.seekp(std::ios::beg+location);
		getline(OUT, buffer);
	}

	// Write value to disk.


	// Close File.

	// Return Sucessful.
	return "OK";
}


/*
std::string readFile(std::string file_name, int indexNumber)
{

	//char input[900];
	std::string output;
	output = "";
	std::ifstream SYSIN;
	bool indexnumberFound = false;
	bool fileatEOF = false;
	std::string temp = "";
	long size = 0;
	std::string realIndexNumber = "";

	//Construct the Index Number.
	temp = indexNumber;

	realIndexNumber = '[';

	realIndexNumber = realIndexNumber += indexNumber;

	realIndexNumber = realIndexNumber += ']';
	std::cout << "the realIndexNumber is : " <<realIndexNumber <<endl;

	temp = "";

	//Open the input file
	SYSIN.open(file_name.c_str(), std::ios::in);


	//Look for the index number.
	while(indexnumberFound != true && fileatEOF != true)
	{
		getline(SYSIN, temp);
		std::cout << temp <<endl;
		if (temp.find(realIndexNumber) == std::string::npos)
		{
			if (SYSIN.eof() == true)
			{
				fileatEOF = true;
				std::cout << "reached end of file. indexnumber not found.\n";
				output = "ERROR: No indexNumber found.";
			}
			if (SYSIN.fail() == true)
			{
				std::cout << "ERROR: FileStream Has errored out.\n";
				SYSIN.close();
				fileatEOF = true;
				output = "ERROR: FileStream has errored out.";
			}
		}
		if (temp.find(realIndexNumber) != std::string::npos)
		{
			std::cout <<"index Number " << indexNumber << " found.\n";
			output = temp;
			indexnumberFound = true;
		}
		else
		{
			std::cout << "ERROR: Unknown error in readFile.\n";
			fileatEOF = true;
		}

	}
	//SYSIN.getline(input, 900, '\n'); //SIDENOTE An _ifdef for diffrent platforms would be good here.
	//output = input;
	std::cout <<endl <<output <<endl;
	SYSIN.close();
	return output;
}

*/

std::string FileStreams::Filechange()
{
	std::string filename = "";
	std::cout << "Input a filename: ";
	getline(std::cin, filename);
	return filename;
}

int FileStreams::UserFileWrite(std::string file_name, int mode, std::string data)
{
	int errorCode;
	if (mode == 0) //Creating New user File.
	{
		std::cout << "the mode is : " << mode <<"\n" << "the filename is : " << file_name.c_str() <<"\n" << "the data is: " << data.c_str() << "\n";
		std::ofstream uFilewrite;
		uFilewrite.open(file_name.c_str(), std::ios::out | std::ios::trunc);
		uFilewrite << data;
		// TODO: uFilewrite << end of line
		uFilewrite.close();
		errorCode = 0;
	}
	if (mode == 1) //Appending to file.
	{
		std::cout << "the mode is : " << mode <<"\n" << "the filename is : " << file_name.c_str() <<"\n" << "the data is: " << data.c_str() << "\n";
		std::ofstream uFilewrite;
		uFilewrite.open(file_name.c_str(), std::ios::out | std::ios::app);
		uFilewrite << data;
		// TODO: uFilewrite << end of line
		uFilewrite.close();
		errorCode = 0;
	}
	if (mode == 2)
	{
		std::cout << "ERROR: FileStreams.cpp: Opening a Read Only FileStream For Writing. \n";
		errorCode = 2;
	}
	else if (mode > 2)
	{
		std::cout << "ERROR: FileStreams.cpp: Unknown Command. \n";
		std::cout << "the mode is : " << mode <<"\n" << "the filename is : " << file_name.c_str() <<"\n" << "the data is: " << data.c_str() << "\n";
		errorCode = mode;
	}
	return errorCode;
}

std::string FileStreams::readEntireFile(std::string filename, Panic::Panic_ERROR & error)
{
	// init vars
	std::string output = "";
	std::string temp = "";
	std::ifstream SYSIN;

	// Open the file
	SYSIN.open(filename.c_str(), std::ios::in);

	// Make sure file is open
	if (SYSIN.is_open() != true)
	{
		// File did not open call PanicHandler and exit the function.
		std::cout << "ERROR: Opening File " <<filename <<" .\n";
		error.PanicHandler("FileStreams::readEntireFile : Unable to open file.");
		SYSIN.close(); //Just to be safe.
		return "ERROR";
	}

	// Run loop.
	while (SYSIN.eof() != true && SYSIN.fail() != true)
	{
		// Get line from file
		getline(SYSIN, temp);

		// Add it to our output.
		output = output += temp;

		// Clear input buffer.
		temp = "";
	}

	// Output error if file stream failed.
	if (SYSIN.fail() == true)
	{
		error.PanicHandler("FileStreams::readEntireFile : File stream has failed.");
		SYSIN.close();
		return "ERROR: Reading File.";
	}

	// Make sure buffer is cleared and exit function.
	temp = "";
	return output;
}

std::string FileStreams::FileSearch(std::string filename, std::string key, Panic::Panic_ERROR & error)
{
	// init vars
	std::ifstream FILEIN;
	bool dataFound = false;
	bool fileatEOF = false;
	bool fileFail = false;
	std::string temp = "";
	std::string output = "";

	// Open file
	FILEIN.open(filename.c_str(), std::ios::in);

	// check if file open failed
	if (FILEIN.is_open() == false)
	{
		error.PanicHandler("FileStreams::FileSearch : Unable to open file.");
		output = "ERROR";
		return output;
	}

	// get data from file.
	while (dataFound != true && fileatEOF != true && fileFail != true)
	{
		getline(FILEIN, temp);
		if (FILEIN.fail() == true)
		{
			// File Stream has errored out. Clear the buffers, close the file, warn the user, and exit the function.
			fileFail = true;
			error.PanicHandler("FileStreams::FileSearch : File Stream has failed.");
			FILEIN.close();
			output = "ERROR";
		}
		// Look for data in the temp buffer.
		if (temp.find(key) != std::string::npos)
		{
			// data found. clear temp buffer, return std::string. Close file and exit function.
			dataFound = true;
			output = temp;
			FILEIN.close();
		}
		if (temp.find(key) == std::string::npos && FILEIN.eof() != true)
		{
			// data not found try again.
			fileatEOF = false;
		}
		if (temp.find(key) == std::string::npos && FILEIN.eof() == true)
		{
			// We didn't find what we were looking for so close the file, warn the user, clear the buffers, and exit the function.
			fileatEOF = true;
			error.PanicHandler("FileStreams::FileSearch : data not found. reached end of file.");
			FILEIN.close();
			output = "ERROR";
		}
		temp = ""; // clear the buffer for the next go around.
	}
	return output;
}
