/*!
    Multiverse Engine Project 21/8/2014 FileUtills FileUtills_Emulated_Symbolic_Link_Functions.cpp
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

// Include header file.
#include "FileUtills_Emulated_Symbolic_Link_Functions.h"

int FileUtills::Create_MSYS_Emulated_Symbolic_Link(const std::string & linkDestionation, const std::string & pathToLinkFile)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;		// The result of this function.
	size_t linkSize = linkDestionation.size();			// The size of the link destionation.
	fstream outputFile;						// The fstream for the emulated link file.

	// Check for valid arguments.
	if (linkSize > 0)
	{
		if (pathToLinkFile.size() > 0)
		{
			// Begin try block.
			try {
				// Open the link file in append mode.
				outputFile.open(pathToLinkFile.c_str(), std::ios::out | std::ios::binary | std::ios::append);
				if (outputFile.is_open())
				{
					// OK, Check to see if the file is blank.
					outputFile.seekg(0, std::ios::end);
					if (outputFile.tellg() == 0)
					{
						// OK, seek back to the beginning.
						outputFile.seekg(0, std::ios::beg);

						// Now output the magic string.
						outputFile << MSYS_EMU_SYMLINK_MAGIC;

						// Determine if we need to swap the byte order of the integers. (size of length and the length itself are supposed to be little-endian encoded.)
						if (DataProcess::)
						{
							// Now we need to output the number of bytes for the destionationLink string's length. (ie. sizeof(size_t)). (This is in little-endianess format.) 
							outputFile << 

							// Now we need to output the length of the destionationLink string. (This is in little-endianess format.)
							outputFile << 
						}
						else
						{
							// Now we need to output the number of bytes for the destionationLink string's length. (ie. sizeof(size_t)). (This is in little-endianess format.) 
							outputFile << 

							// Now we need to output the length of the destionationLink string. (This is in little-endianess format.)
							outputFile << 
						}

						// Output the destionationLink string.
						outputFile << destionationLink;

						// Flush the output buffer.
						outputFile.flush();

						// Check for good output buffer.
						if (outputFile.good())
						{
							// Success.
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							// IO Error.
							ret = COMMON_ERROR_IO_ERROR;

							// Log the error.
							COMMON_LOG_DEBUG("FileUtills::Create_MSYS_Emulated_Symbolic_Link(): ");
							COMMON_LOG_DEBUG(Common::Get_Error_Message(ret));
							COMMON_LOG_DEBUG(" Unable to create emulated symbolic link file ( ");
							COMMON_LOG_DEBUG(pathToLinkFile.c_str());
							COMMON_LOG_DEBUG(" )\n");

							// Invalidate link file.
							outputFile.clear();
							outputFile.seekp(0, std::ios::beg);
							outputFile.seekg(0, std::ios::beg);
							outputFile.put('\0');
						}

						// Close the file.
						outputFile.close();
					}
					else
					{
						// File is not empty, abort.
						ret = FILEUTILLS_ERROR_EXISTANT;

						// Log the error.
						COMMON_LOG_INFO("FileUtills::Create_MSYS_Emulated_Symbolic_Link(): ");
						COMMON_LOG_INFO(Common::Get_Error_Message(ret));
						COMMON_LOG_INFO(" The given path ( ");
						COMMON_LOG_INFO(pathToLinkFile.c_str());
						COMMON_LOG_INFO(" ) already exists.\n");
					}
				}
				else
				{
					// Could not open output file for writing.
					ret = COMMON_ERROR_IO_ERROR;

					// Log the error.
					COMMON_LOG_INFO("FileUtills::Create_MSYS_Emulated_Symbolic_Link(): ");
					COMMON_LOG_INFO(Common::Get_Error_Message(ret));
					COMMON_LOG_INFO(" Unable to open ( ");
					COMMON_LOG_INFO(pathToLinkFile.c_str());
					COMMON_LOG_INFO(" ) for writing.\n");
				}
			}
			catch(exception &ex)
			{
				// Exception thown.
				ret = COMMON_ERROR_EXCEPTION_THROWN;
				COMMON_LOG_VERBOSE("FileUtills::Create_MSYS_Emulated_Symbolic_Link(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
				COMMON_LOG_VERBOSE(" ");
				COMMON_LOG_VERBOSE(ex.what());
				COMMON_LOG_VERBOSE("\n");
			}
		}
		else
		{
			// Invalid path.
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::Create_MSYS_Emulated_Symbolic_Link(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			COMMON_LOG_DEBUG(" Given path to the emulated link file is invalid.\n");
		}
	}
	else
	{
		// Invalid destionationLink.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::Create_MSYS_Emulated_Symbolic_Link(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given destionation link string is invalid.\n");
	}

	// Close the file if it's still open.
	if (outputFile.is_open())
	{
		outputFile.close();
	}

	// Copy the result to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::Read_MSYS_Emulated_Symbolic_Link(std::string & link, const std::string & pathToLinkFile)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;		// The result of this function.
	std::string tempLinkBuf = "";					// Temporary buffer for constructing the link string.
	fstream inputFile;						// The fstream for the emulated link file.

	// Blank the link string.
	link.clear();

	// Check for valid argument.
	if (pathToLinkFile.size() > 0)
	{
		// Begin try block.
		try {


		}
		catch(exception &ex)
		{
			// Exception thown.
			ret = COMMON_ERROR_EXCEPTION_THROWN;
			COMMON_LOG_VERBOSE("FileUtills::Read_MSYS_Emulated_Symbolic_Link(): ");
			COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
			COMMON_LOG_VERBOSE(" ");
			COMMON_LOG_VERBOSE(ex.what());
			COMMON_LOG_VERBOSE("\n");
		}
	}
	else
	{
		// Invalid path.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::Read_MSYS_Emulated_Symbolic_Link(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path to the emulated link file is invalid.\n");
	}

	// Close the file if it's still open.
	if (inputFile.is_open())
	{
		inputFile.close();
	}

	// If we failed, blank the link string.
	if (ret != COMMON_ERROR_SUCCESS)
	{
		tempLinkBuf.clear();
		link.clear();
	}

	// Copy the result to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

int FileUtills::Update_MSYS_Emulated_Symbolic_Link(const std::string & linkDestionation, const std::string & pathToLinkFile)
{
	// Init vars.
	int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;		// The result of this function.
	size_t linkSize = linkDestionation.size();			// The size of the link destionation.
	std::string tempLinkBuf = "";					// Temporary buffer for constructing the link string.
	fstream linkFile;						// The fstream for the emulated link file.

	// Check for valid arguments.
	if (linkSize > 0)
	{
		if (pathToLinkFile.size() > 0)
		{
			// Begin try block.
			try {


			}
			catch(exception &ex)
			{
				// Exception thown.
				ret = COMMON_ERROR_EXCEPTION_THROWN;
				COMMON_LOG_VERBOSE("FileUtills::Update_MSYS_Emulated_Symbolic_Link(): ");
				COMMON_LOG_VERBOSE(Common::Get_Error_Message(ret));
				COMMON_LOG_VERBOSE(" ");
				COMMON_LOG_VERBOSE(ex.what());
				COMMON_LOG_VERBOSE("\n");
			}
		}
		else
		{
			// Invalid path.
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			// Log the error.
			COMMON_LOG_DEBUG("FileUtills::Update_MSYS_Emulated_Symbolic_Link(): ");
			COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
			COMMON_LOG_DEBUG(" Given path to the emulated link file is invalid.\n");
		}
	}
	else
	{
		// Invalid destionationLink.
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		// Log the error.
		COMMON_LOG_DEBUG("FileUtills::Update_MSYS_Emulated_Symbolic_Link(): ");
		COMMON_LOG_DEBUG(Common::Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given destionation link string is invalid.\n");
	}

	// Close the file if it's still open.
	if (linkFile.is_open())
	{
		linkFile.close();
	}

	// If we failed, blank the link string.
	if (ret != COMMON_ERROR_SUCCESS)
	{
		tempLinkBuf.clear();
	}

	// Copy the result to Common::commonLastErrorCode.
	Common::commonLastErrorCode = ret;

	// Return the result.
	return ret;
}

// End of FileUtills_Emulated_Symbolic_Link_Functions.cpp
