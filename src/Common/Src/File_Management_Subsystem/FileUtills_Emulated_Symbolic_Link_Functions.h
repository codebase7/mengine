/*!
    Multiverse Engine Project 21/8/2014 FileUtills FileUtills_Emulated_Symbolic_Link_Functions.h
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

// Include guard.
#ifndef FILEUTILLS_EMULATED_SYMBOLIC_LINK_FUNCTIONS_H
#define FILEUTILLS_EMULATED_SYMBOLIC_LINK_FUNCTIONS_H

// Internal includes.
#include "../Error_Handler/Common_Error_Handler.h"
#include "../Error_Handler/Common_Error_Handler_Internal.h"

// External includes.
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>


/*!
 * 	Description of the emulated symbolic link file format:
 *
 * 	Offset 0: Magic string. (E.g. "MSYS_EMU_SYMLINK")
 *
 * 	Offset (0 + sizeof(<Magic string>)): uint (4 bytes, little endian) size of the length value. (I.e. sizeof(size_t)).
 * 
 * 	Offset (0 + sizeof(<Magic string>) + 4): length of the link. (Length is the same as the read size variable.)
 *
 * 	Offset (0 + sizeof(<Magic string>) + 4 + (size of the length value)): Start of link.
 *
 * 	Offset (0 + sizeof(<Magic string>) + 4 + (size of the length value) + <length of the link>): End of the link, and enf of file.
 */


// Define namespace.
namespace FileUtills
{
	// Define magic string for the emulated symbolic link file.
	#define MSYS_EMU_SYMLINK_MAGIC "MSYS_EMU_SYMLINK"

	// Define file extension for the emulated symbolic link file.
	#define MSYS_EMU_SYMLINK_FILE_EXT "msl"

	// Define functions.

	/*!
	 * 	int FileUtills::Create_MSYS_Emulated_Symbolic_Link(const std::string & linkDestionation, const std::string & pathToLinkFile)
	 * 
	 * 	Takes the given linkDestionation string and creates an emulated symbolic link file with the string's
	 * 	contents at the given path on the filesystem.
	 *
	 * 	NOTE: This function expects that the given path is invalid. (I.e. That no file / directory / some other
	 * 	filesystem entry exists at the given path.) In addition this function expects that the given path's
	 * 	parent directory exists at the time that this function is called. (I.e. That this function does not
	 * 	need to create the directory tree leading up to the file to create.) If either of these assumptions
	 * 	are false, this function will abort and return an error.
	 *
	 * 	If successfull this function will return COMMON_ERROR_SUCCESS, and the emulated symbolic link file
	 * 	will be present at the given location on the filesystem.
	 *
	 * 	If an error occurs, the approperite Common namespace error code will be returned. In addition, the
	 * 	emulated link file will be rendered invalid on the filesystem. (It will still be present on the
	 * 	filesystem however, as such it will need to be deleted manually.)
	 *
	 * 	In all instances the returned error code will be copied to Common::commonLastErrorCode. (In addition,
	 * 	depending on the configured log level, a human readable error message will be outputted to the logging
	 * 	function to better describe the error that occured.)
	 */
	int Create_MSYS_Emulated_Symbolic_Link(const std::string & linkDestionation, const std::string & pathToLinkFile);

	/*!
	 * 	int FileUtills::Read_MSYS_Emulated_Symbolic_Link(std::string & link, const std::string & pathToLinkFile)
	 *
	 * 	Erases the given link argument string, then reads the file from the given path for a symbolic link
	 * 	string, and writes it to the given link argument string.
	 *
	 * 	NOTE: This function does NOT resolve the read symbolic link, and will return it as is on the filesystem.
	 * 	To resolve the link, either call your own resolver function, or call FileUtills::ResolvePath().
	 *
	 * 	NOTE: This function is called automaticly by FileUtills::ResolvePath() if symbolic link resolution is
	 * 	enabled by the caller (it is by default), and an emulated link file is found during path resolution.
	 * 	As such it's not nessacarry to call this function directly before FileUtills::ResolvePath().
	 *
	 * 	(Sidenote: This function returns read links as is, if the read link is relative to the directory it is in,
	 * 	 then the link string will need to have the path to the directory that the emulated link file is stored
	 * 	 in prepended to the link string before calling FileUtills::ResolvePath(). If you fail to do this,
	 * 	 FileUtills::ResolvePath() will assume that the given emulated link string is relative to the
	 * 	 calling program's current working directory. (Along with all of the issues that come with that
	 * 	 assumption.))
	 *
	 * 	If successfull, the given link argument string will have it's contents replaced with the read link
	 * 	string, and COMMON_ERROR_SUCCESS will be returned.
	 *
	 * 	If an error occurs then the given link argument string will be blank / empty, and the approperite
	 * 	Common namespace error code will be returned.
	 *
	 * 	In all instances the returned error code will be copied to Common::commonLastErrorCode. (In addition,
	 * 	depending on the configured log level, a human readable error message will be outputted to the logging
	 * 	function to better describe the error that occured.)
	 */
	int Read_MSYS_Emulated_Symbolic_Link(std::string & link, const std::string & pathToLinkFile);

	/*!
	 * 	int FileUtills::Update_MSYS_Emulated_Symbolic_Link(const std::string & linkDestionation, const std::string & pathToLinkFile)
	 *
	 * 	This function updates a pre-existing emulated link file at the given path on the filesystem, with the contents
	 * 	of the given linkDestionation argument string.
	 *
	 * 	NOTE: This function expects that the emulated link file already exists on the filesystem at the given path. It also
	 * 	expects that the emulated link file will be valid. If either of these two conditions are not true, then this function
	 * 	will abort and return an error.
	 *
	 * 	If successfull, the given emulated link file will contain the contents of the given linkDestionation argument string, and
	 * 	the returned error code will be COMMON_ERROR_SUCCESS.
	 *
	 * 	If an error occurs, the approperite Common namespace error code will be returned. In addition, the
	 * 	emulated link file will be rendered invalid on the filesystem. (It will still be present on the
	 * 	filesystem however, as such it will need to be deleted manually.)
	 *
	 * 	In all instances the returned error code will be copied to Common::commonLastErrorCode. (In addition,
	 * 	depending on the configured log level, a human readable error message will be outputted to the logging
	 * 	function to better describe the error that occured.)
	 */
	int Update_MSYS_Emulated_Symbolic_Link(const std::string & linkDestionation, const std::string & pathToLinkFile);
};

#endif

// End of FileUtills_Emulated_Symbolic_Link_Functions.h
