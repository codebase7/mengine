/*!
    Multiverse Engine Project Core/FileStreams.h 11/19/2010

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
    
#ifndef FILESTREAMS_H
#define FILESTREAMS_H

#include "BaseHeader.h"
#include "Panic.h"

//ToDo Remove SystemFileOpen Function.
namespace FileStreams
{

/*!
  configCreate(std::string path, Panic::ERROR & error)

  Creates a new config file for use with the other config* functions.

  Pram: Path to file.
  Return: returns OK if successful. Otherwise an error is given.
*/
std::string configCreate(std::string path, Panic::ERROR & error);


/*!
  configParser(std::string path, std::string key, Panic::ERROR & Error)

  Reads a given config file for a varaible.

  @pram location of config file to parse.
  @pram varaible name to find in given config file.
  returns string with requested varaible if found otherwise returns error.
*/
std::string configParser(std::string path, std::string key, Panic::ERROR & Error);

/*!
  configWriter(std::string path, std::string key, std::string value, Panic::ERROR & error, bool createkey)

  Writes a configfile value to disk.

  @pram path to config File on disk to write to.
  @pram unique identifier to write value to.
  @pram value to write.
  @pram If true the key will be created if it does not exist in the file. If false, key will not be written. If key is not
  present and false is given an error will be returned. Default is false.

  @return Retuns OK if successful, otherwise an error is given.
*/
std::string configWriter(std::string path, std::string key, std::string value, Panic::ERROR & error, bool createkey = false);

std::string Filechange();

/*!
  UserFileWrite(std::string file_name, int mode, std::string data)

  UserFileWrite is for writing out files specific to users. The file_name var is relitive to the
  working path. mode is the file writing mode and expects ether a 0 for Create or a 1 For append to file.
  data is a string that will be converted to a c_string before it is written to the file.
  Generaly only use the File Create mode for a file eraser. it will destroy the contents of the file it opens.
  The return value is 0 if the operation is successful, 1 if the file did not open correctly,
  or 2 if the file writing mode was invalid.
*/
int UserFileWrite(std::string file_name, int mode, std::string data);


//extern std::string readFile(std::string file_name, int indexNumber);
/*
   readSystemFile is for reading files specfic to the Program and not users.
   the file_name var is for the filename of the file to be read and is relitive to the working dir.
   indexNumber is a location within that file. all lines in the file expect the first one have a index number.
   this index number is used to get to a specfic location quickly. the index numbers start at one (indexNumber = 1)
   and continue until the end of the file is reached. the return value is the string requested, unless an error
   occurs in which case the error will be printed to the screen / stdout.
*/

std::string readEntireFile(std::string filename, Panic::ERROR & error);

/*!
  FileSearch(std::string filename, std::string key, Panic::ERROR & error)

  Looks in given file for data returns data found.

  @pram location of file to search
  @pram string to search for in file.
  returns string if found in file otherwise an error is given.
*/
std::string FileSearch(std::string filename, std::string key, Panic::ERROR & error);

}
#endif

// End of FileStreams.h
