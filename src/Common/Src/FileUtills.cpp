/*!
    Multiverse Engine Project 04/12/2011 FileUtills FileUtills.cpp
    
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


#include "FileUtills.h"

/*!
    std::string RemoveTrailingSlash(const std::string & path)

    Removes a DIR_SEP on the end of the given path string (if it exists)
    Will not do anything and return the original string if there is only 1 charater in the given path string.
    Will also return the original string if a memory error occurs.
*/
std::string RemoveTrailingSlash(const std::string & path)
{
	 //init vars
	size_t size = 0;
	std::string buffer = "";

	// Get size of the Directory string.
	size = path.size();

	// Check the length of the string see if it is only 1 charater
	if (size == 1)
	{
	    // We can't remove anything, if we do the return would be empty.
	    return path;
	}

	// Copy the directory string to buffer
	buffer = path;

	// Check and see if a directory seperator is on the end of the string.
	if ((path.find_last_of(DIR_SEP)) == (size-1))
	{
		 // Remove the trailing Directory seperator so we don't screw up the next check.
		 // Note substr CAN throw an exception so we must put it in a try catch block
		 try{
            buffer = path.substr(0, (size-1));
		 }
		 catch(exception ex)
		 {
		     // We can't return an error so we will silently fail.
		     return path;
		 }
	}

	// Return new path.
	return buffer;
}

std::string FileUtills::CheckPathType(const std::string & path)
{
        // Init vars.
        std::string output = "";
        char charArray[1000];			// Used for the cwd function.
        char * pCWD;				// Used to store result of the getCWD function.
        long int size = 0;          // Size of path string.

        // Set size.
        size = path.size();

        // Check and see if a directory seperator is in the path.
        if (path.find(DIR_SEP) == string::npos)
        {
                // Going with realtive path.
                pCWD = getcwd(charArray, sizeof(charArray));
                output = pCWD;
                output += DIR_SEP;
                output += path;
                return output;
        }

        // Look for home '~'.
        if (path.find_first_of('~') == 0)
        {
                // Get the home path.
                pCWD = getenv("HOME");
                output = pCWD;
                output += path.substr(1, size);

                // Remove the slash if it was added back.
                output = RemoveTrailingSlash(output);

                // Return output.
                return output;
        }

        // Look for "./" (Relative)
        if(path.find("./") == 0)
        {
                // Get current directory.
                pCWD = getcwd(charArray, sizeof(charArray));
                output = pCWD;

                // Add a DIR_SEP to the string or we will mess up the directory name.
                output += DIR_SEP;

                // Add data from the Directory string.
                output += path.substr(2, size);

                // Remove the slash if it was added back.
                output = RemoveTrailingSlash(output);

                // Return the output.
                return output;
        }

        // Look for absolute path.
        if (path.find(DIR_SEP) == 0)
        {
                // Path is absolute.
                return path;
        }
        else // If all else fails it must be relative.
        {
                // Assuming relative path.
                pCWD = getcwd(charArray, sizeof(charArray));
                output = pCWD;
                output += DIR_SEP;
                output += path;
                return output;
        }

        // Default return
        return "";
}

FileUtills::dirlist * FileUtills::getDirectory(const std::string & path)
{
#ifdef POSIX_COMMON_H
        // Dumb check.
        if (path.size() <= 0)
        {
                // Invalid path.
                return NULL;
        }

        // Init vars.
        FileUtills::dirlist * buffer;
        struct dirent * dir;                        // ''
        DIR * dp;	                    		    // Directory stream to hold directory name..... (Why can't it just take a c string?)
        std::string tempname = "";	                // Used to store the filename / subdirectory name for the addToArray function.

        // Allocate the dirlist.
        try{
                buffer = new FileUtills::dirlist;
        }
        catch(bad_alloc)
        {
                // Could not allocate struct.
                return NULL;
        }

        // Set the path.
        buffer->path = path;

        // Dump the path as a c string into the Directory stream object......(Overly complicated POS......)

        // Check and make sure we can open the directory first.
        if ((dp = (opendir(path.c_str()))) == NULL)
        {
                // An error occured.
                if (buffer != NULL)
                {
                        delete buffer;
                        buffer = NULL;
                }

                // Exit function.
                return NULL;
        }

        // Start filesystem fetch loop.
        while ((dir = readdir(dp))) // Call Host OS function.
        {
                // Check and see if the cleanList flag is set.
                if (cleanList)
                {
                        // Check to see if d_name is a POSIX directory shortcut.
                        if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0))
                        {
                                // d_name is a directory shortcut, do not add it to the list.
                                continue;
                        }
                }

                // Cast d_name to a string
                tempname = dir->d_name;

                // Add the data to the array.
                buffer->list.push_back(tempname);
        }

        // Close the directory stream and reset it.
        closedir(dp);

        // If we are cleaning the list, call DataProcess::DecrementingSort().
        if (DataProcess::DecrementingSort(buffer->list) != 0)
        {
                // An exception was thrown in the DecrementingSort() function, bail out.
                if (buffer != NULL)
                {
                        delete buffer;
                        buffer = NULL;
                }

                // Exit function.
                return NULL;
        }

        // Set the number of entries
        buffer->numOfEntries = buffer->list.size();

        // Return the buffer.
        return buffer;
#endif
        // Default return for unimplemted function.
        return NULL;
}

short FileUtills::GetGigaFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		}
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine gigabyte conversion.
	result = (free_blocks * block_size) / ((double)1000000000);

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif

	// Default return for unimplemented function.
	return -3;
}

short FileUtills::GetFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		}
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine megabyte conversion.
	result = (free_blocks * block_size) / ((double)(1000000));

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif
	// Default return for unimplemented function.
	return -3;
}

short FileUtills::GetKiloFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		}
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine byte conversion.
	result = ((free_blocks * block_size) / ((double)(1000)));

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif
	// Default return for unimplemented function.
	return -3;
}

short FileUtills::GetByteFreespace(const std::string & path, size_t & result)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0;
	size_t block_size = 0;
	size_t free_blocks = 0;
	struct statvfs * buffer;

    // Reset result.
    result = 0;

	// Create buffer
	buffer = new struct statvfs;

	// Call host's function
	errorcode = statvfs(path.c_str(), buffer);

	// Check if an error as thrown.
	if (errorcode != 0)
	{
		// Figure out what the error we got back was.
		switch (errno){
		  case EACCES:		// Permission error.
		    return -2;
		    break;
		  case EIO:		// I/O error.
		    return -1;
		    break;
		  case ELOOP:		// Too many symbolic links.
		    return -4;
		    break;
		  case ENAMETOOLONG:	// Path is too long for the filesystem to handle.
		    return -5;
		    break;
		  case ENOENT:		// File or directory does not exist.
		    return -6;
		    break;
		  case ENOSYS:		// Filesystem unsupported.
		    return -7;
		    break;
		  case ENOTDIR:		// A part of the path is not a valid directory.
		    return -8;
		    break;
		  case EOVERFLOW:	// Some data returned was too big for the struct.
		    return -9;
		    break;
		  case ENOMEM:		// Out of kernel memory. Probably should kill the engine here.....
		    return -10;
		    break;
		  default:		// We really don't care about the other errors.
		    return -11;
		    break;
		};
	}

	// Read the remaining blocks from the filesystem.
	free_blocks = buffer->f_bavail;

	// Read the file system block size.
	block_size = buffer->f_bsize;

	// Determine byte conversion.
	result = (free_blocks * block_size);

	// Delete the buffer
	delete buffer;

	// Return remaining space
	return 0;
#endif
	// Default return for unimplemented function.
	return -3;
}

int FileUtills::CreateDirectory(const std::string & directory, Panic::ERROR & error, bool createRecursive)
{
#ifdef POSIX_COMMON_H
	// Init vars.
	std::string buffer = ""; 		// Used to store the current directory path.
	std::string parentbuffer = "";	// Used to store the parent directory's path.
	std::string realpath = "";		// Used to store the real directory path if a relative path or a user path is given instead of an absolute path.
	int errorcode = 0;			    // Used to store return error codes.
	size_t position = 0;			// Used to store current search position in buffer.
	size_t size = 0;			    // Used to store the size of the path string
	int permission = 0;			    // Used to store return code from FileUtills::CheckPermissions().
	bool skiploop = false;			// Used to control the recursive directory creation loop.
	bool isrelative = false;		// Used to tell if the path is relative or abosulute.
	bool isHome = false;			// Used to tell if the path is in a user's home directory.
	char charArray[1000];			// Used for the cwd function.
	char * pCWD;				    // Used to store result of the getCWD function.

    	// Check to see if the full directory path already exists.
	if (FileUtills::DoesExist(directory, error) == true)
	{
	    // Directory already exists thus return true.
	    return -3;
	}

	// Check for a directory seperator on the end of the path and remove it if it is found.
	buffer = RemoveTrailingSlash(directory);

	// Get the size of the buffer string.
	size = buffer.size();

	// Determine if we have a relative path or a absolute one.
	if (buffer.find_first_of(DIR_SEP) == 0)
	{
		isrelative = false;
	}

	if (buffer.find("./") == 0) // BUG: this should not be called when string != "./"<some path>.
	{
		// Ok relative path get the full path
		isrelative = true;
		pCWD = getcwd(charArray, sizeof(charArray));
		buffer = pCWD;

		buffer += directory.substr(1, size);

		// Remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the realpath.
		realpath = buffer;

	}

	// Also check if it's in a user's home subdirectory.
	if (buffer.find_first_of('~') == 0)
	{
		// Ok user path, get the full path.
		isHome = true;
		pCWD = getenv("HOME");
		buffer = pCWD;
		buffer += directory.substr(1, size);

		// remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the real path.
		realpath = buffer;
	}

	// Assume relative if we have something else here.
	if (buffer.find_first_of(DIR_SEP) != 0 && isHome == false && isrelative == false) // BUG: This does not get called.
	{
		// Set isrelative to true and retrive the current working directory.
		isrelative = true;
		pCWD = getcwd(charArray, sizeof(charArray));
		buffer = pCWD;

		// Add a DIR_SEP to the string or we will mess up the directory name.
		buffer += DIR_SEP;

		// Add all data from the Directory string because the string does not have a DIR_SEP at position zero.
		buffer += directory.substr(0, size);

		// Remove the slash if it was added back.
		buffer = RemoveTrailingSlash(buffer);

		// Copy it to the realpath.
		realpath = buffer;
	}

	// Get the parent directory out of the buffer and store it for later.
	position = buffer.find_last_of(DIR_SEP);
	parentbuffer = buffer.substr(0, position);

	 // Check and see if the parent directory exists.
	errorcode = FileUtills::CheckParent(directory);	// Switch

	switch (errorcode) {
      case -1:  // Can't write to the parent directory exit the function.
        error.PanicHandler("FileUtills::CreateDirectory : Parent Directory not writable. will not create directory.");
		return -1;
		permission = 0;
        break;
	  case -2:  // Parent Directory does not exist,
	    if (createRecursive == false)
	    {
                // Don't create the directory structure.
                error.PanicHandler("FileUtills::CreateDirectory : Parent Directory does not exist. createRecursive is false, will not create directory.");
                return -2;
	    }
	    break;

	  case 0:  // Parent Directory does exist and is writeable.
        // since we can write to the directory skip the loop.
		skiploop = true;
		break;
      default: // Ether there was an unknown error or this Arch / OS is not supported. ether way return -4.
	    return -4;
	    errorcode = 0;
	    break;
	}

	// Clear the vars for the recursive directory creation loop.
	permission = 0;
	position = 0;
	errorcode = 0;

	// Set buffer so we can check the path correctly.
	// If we have a relative or user path use the real path.
	if (isHome == true || isrelative == true)
	{
		buffer = realpath.substr(0, (realpath.find_first_of( DIR_SEP , 1)));

		// Also set the size of the string correctly.
		size = realpath.size();
	}
	else
	{
		// Otherwise use the directory string.
		buffer = directory.substr(0, (directory.find_first_of( DIR_SEP, 1)));

		// Also set the size of the string correctly.
		size = directory.size();
	}

	// If the parent directory does not exist and createRecursive is true then begin main loop.
	while (skiploop != true)
	{
		// If we are at position 0 and there is a DIR_SEP there incremnt position by one.
		if (position == 0 && buffer.find_first_of(DIR_SEP) == 0)
		{
			// Incremnt the position by one.
			position++;
		}

		// Start with root directory and run though the following until we reach the requested directory.

		if (isHome == true || isrelative == true)	// If true use realpath
		{
			if ((position = realpath.find_first_of(DIR_SEP, position)) == string::npos)
			{
				// This is the requested directory so exit the loop.
				skiploop = true;
				break;
			}
		}
		else 		// Otherwise use directory.
		{
			if ((position = directory.find_first_of(DIR_SEP, position)) == string::npos)
			{
				// This is the requested directory so exit the loop.
				skiploop = true;
				break;
			}
		}

		// Do a sanity check for the size of the string.
		if (position < 0 || position > size)
		{
			// Ok something went wrong.
			return -4;
		}

		// Dump the last buffer into the parentdirectory buffer.
		parentbuffer = buffer;

		// Cut up the directory string so we can check for it.

		if (isHome == true || isrelative == true)
		{
			buffer = realpath.substr(0, position);
		}
		else
		{
			buffer = directory.substr(0, position);
		}

		// Do Check.
		errorcode = FileUtills::DoesExist(buffer, error);

		switch (errorcode){
		  case -1:		// Directory does not exist on system.
		    // Check and see if we can create it.
		    permission = FileUtills::CheckPermissions(parentbuffer, error);

		    switch (permission){
		      case -1:
			// Permission Check Failed.
			return false;
			break;

		      case 0:
			// Ok try and create the directory.
			if ((errorcode = (mkdir(buffer.c_str(), S_IRWXU))) != 0)
			{
				// An error ocurred find out what.

				switch (errno) {
				  case EACCES:		// Permission error.
				    return -1;
				    break;
				  case EEXIST:		// Path exists on system.
				    return -3;
				    break;
				  case ENOSPC:		// Out of disk space.
				    return -2;
				    break;
				  default:		// We really don't care about the other errors.
				    return -4;
				    break;
				}
			}

			// Update the position counter.
			position++;

			// Check and see if that was the last directory to create.
			if (isHome == true || isrelative == true)
			{
				// Check realpath.
				if (buffer == realpath)
				{
				  skiploop = true;
				  return 0;
				}
			}
			// Otherwise check the directory buffer.
			if (buffer == directory)
			{
				skiploop = true;
				return 0;
			}
			break;

		      default:
			// Bad errorcode exit function.
			return -4;
			break;
		    }
		    permission = 0;
		    errorcode = 0;
		    break;

		  case 0:		// Ok directory does exist.
		    position++;
		    break;

		  default:
		    // Bad error code exit function.
		    return -4;
		}



		// If the next directory does exist then skip the remaining portion of the checks and restart with the next directory.

		// If the next directory does not exist the check the permissions of this one.

			// If we can write to this directory then create the directory.

				// If the directory creation was successful then check and see what to do next.

					// If we have created the requested directory exit the function
					//return true.

					// If we have not created the requested directory contiune loop with the next
					// directory.

				// If we encountered a fatal error exit the function return false.

			// If we can't write to this directory exit the function, return false.

			// If the permission check fails with a fatal error exit the function return false.

		// If the existance check fails exit the function, return false.
	}



	//If we have a relative or user path use realpath.
	if (isHome == true || isrelative == true)
	{
		buffer = realpath;
	}
	else // Otherwise use the directory string.
	{

		buffer = directory;
	}

	// Ok try and create the directory.
	if ((errorcode = (mkdir(buffer.c_str(), S_IRWXU))) != 0)
	{
		// An error ocurred find out what.

		switch (errno) {
		  case EACCES:		// Permission error.
		    return -1;
		    break;
		  case EEXIST:		// Path exists on system.
		    return -5;
		    break;
		  case ENOSPC:		// Out of disk space.
		    return -4;
		    break;
		  default:		// We really don't care about the other errors.
		    return -6;
		    break;
		}
	}
	if (errorcode == 0)
	{
		return 0;
	}
#endif
	// If an implemetation does not exist for this platform then exit the function, return false.
	return -3;
}


/*bool FileUtills::CreateDirectory(std::string directory, Panic::ERROR & error, bool createRecursive)
{
#ifdef POSIX_COMMON_H
	// Init vars
	int errorcode = 0; 			// Used to tell if we get an error
	int permissioncheck = 0;		// Used for return code from FileUtills::CheckPermissions
	int position = 0; 			// Used for storing the last seperator location.
	int size = 0; 				// Stores the total size of the directory string.
	std::string buffer = ""; 		// Used to contain a partial directory path.
	std::string parentbuffer = "";		// Used to store the Parent directory path.
	bool foundSeperator = false; 		// Used to end the search loop for a Path Seperator.
	bool done = false; 			// Used to end the check for directory exist loop.
	bool relitivepath = false;		// Used to tell if we have a relitvie path.

	// Check to see if the full directory path already exists.
	if (FileUtills::DoesExist(directory, error) == true)
	{
	    // Directory already exists thus return true.
	    return true;
	}



	// Get size of the Directory string.
	size = directory.size();

	// Copy the directory string to buffer
	buffer = directory;

	// Check and see if a directory seperator is on the end of the string.
	if ((directory.find_last_of(DIR_SEP)) == (size-1))
	{
		// Remove the trailing Directory seperator so we don't screw up the next check.
		 buffer = directory.substr(0, (size-1));
	}

	// Remove the directory to create from the path so we can see if the Parent directory exists.
	position = buffer.find_last_of(DIR_SEP);
	parentbuffer = buffer.substr(0, position);

	// Check and see if the parent directory exists.
	errorcode = DoesExist(parentbuffer, error);

	// Check and make sure we didn't get a -2 out of DoesExist. (Or a bad error code.)
	if (errorcode == -2 || errorcode > 0 || errorcode < -2)
	{
		// Ok we have a problem. Exit the function. Do not call PanicHandler.
		return false;
	}

	// If createRecursive is false and the parent does not exist exit the function.
	if (errorcode == -1 && createRecursive == false)
	{
		// Don't create the directory structure. Call PanicHandler and return false.
		error.PanicHandler("FileUtills::CreateDirectory : Parent Directory does not exist. createRecursive is false, will not create directory.");
		return false;
	}

	// If Parent directory exists skip the Create Parent Directory loop.
	if (errorcode == 0)
	{
	  // Set done to true so we skip the loop.
	  done = true;
	}

	// Reset vars for detection loop
	errorcode = 0;
	position = 0;
	buffer = parentbuffer;

	// Check and see if we have a relitive directory or a full path.
	if ((buffer.find_first_of(DIR_SEP, position)) != 0)
	{
		relitivepath = true;
	}

	// Begin trying to create the upper level directories if they don't exist.
	while (done != true)
	{
			// Update the total size
			size = buffer.size();

			// In POSIX the seperator will always be at position 0. Unless a relitive directory is given.
			// So we have to compensate for this.

			if (relitivepath == false && position == 0 && size > 0)
			{
				// Fix the position.
				position++;
			}

			// if we really are at the root level do nothing about the position

			// Find first seperator.
			position = buffer.find_first_of(DIR_SEP, position);

			// If position is past the end of the string or if it's less than 0 call PanicHandler
			if (position > size || position < 0)
			{
				// Error Call PanicHandler
				error.PanicHandler("FileUtills::CreateDirectory : position is out of bounds. Unable to continue parsing directories. Returning false.");
				return false;
			}

			// Remove everything after it and the seperator as well
			buffer = directory.substr(0, (position));

			// Check and see if the directory exists.
			errorcode = FileUtills::DoesExist(buffer, error);

			// Check errorcode.
			if (errorcode == 0)
			{

			  // OK the directory exists so let's see if we can actully write to it.
			  permissioncheck = FileUtills::CheckPermissions(buffer, error);

			  if (permissioncheck == -1) // Permission for / or /home is read only this condition will always be true.
			  {
				// We can't write here so we have to exit the function.
				error.PanicHandler("FileUtills::CreateDirectory : Unable to write to parent folder, Access Denied. Returning false.");
				return false;
			  }

			  if (permissioncheck == -2)
			  {
				// OK we got a does not exist. The check has failed regardless so exit the function.
				error.PanicHandler("FileUtills::CreateDirectory : Parent Directory does not exist, second check failed. Returning false.");
				return false;
			  }

			  if (permissioncheck < -2 || permissioncheck > 0)
			  {
				// Ok this should not happen exit the function.
				return false;
			  }
			  // The directory exists so check to see if it's the last one before the to be created directory.
			  if (buffer == parentbuffer)
			  {
				 // Set exit condition
				 done = true;

				 // Reset errorcode and permissioncheck
				 errorcode = 0;
				 permissioncheck = 0;
			  }
			}
			cout <<"\n\nend of test.\n\n";
			// If the directory does not exist attpemt to create it.
			if (errorcode == -1)
			{
				// Reset errorcode
				errorcode = 0;

				// First Check Permissions so we know if this will work or not.
				permissioncheck = FileUtills::CheckPermissions(buffer, error);

				// If permissions are bad bail out.
				if (permissioncheck == -1)
				{
					// User lacks permission exit function.
					error.PanicHandler("FileUtills::CreateDirectory : User lacks permission to create directory. Access Denied.");
					return false;
				}

				// If anything else exit function.
				if (permissioncheck > 0 || permissioncheck <= -2)
				{
					// Exit function
					return false;
				}

				if (permissioncheck == 0)
				{
					// Reset errorcode and permissioncheck
					errorcode = 0;
					permissioncheck = 0;

					// Directory does not exist so we must create it.
					errorcode = mkdir(buffer.c_str(), 770);
				}

				// Verifiy that new directory exists
				errorcode = FileUtills::DoesExist(buffer, error);

				// if errorcode is -1 we have a problem.
				if (errorcode == -1)
				{
					// Call PanicHandler
					error.PanicHandler("FileUtills::CreateDirectory : Parent Directory creation has failed. Returning false.");
					return false;
				}

				// If errorcode is anything else we really have a problem.
				if (errorcode > 0 || errorcode < -1)
				{
					// Exit the function return false
					return false;
				}

				// errorcode is good reset it to be safe though
				errorcode = 0;

			}

			// Check and see if errorcode is bad.
			if (errorcode > 0 || errorcode < -1)
			{
				// We have an issue return false.
				return false;int
			}
			// TODO: did this backwards should go form root level to the directory we need to create.

		// Reset the buffer
		buffer = directory.substr(0, (directory.size()));

		// Increment position
		position++;
	}
	// Reset permissioncheck
	permissioncheck = 0;

	// Check the permissions on the parent directory.
	permissioncheck = FileUtills::CheckPermissions(parentbuffer, error);

	// If we have permission create the directory.
	if (permissioncheck == 0)
	{
		// Make the directory
		errorcode = mkdir(directory.c_str(), 770);

		// Check for error TODO: actully return what error we recive.
		if (errorcode < 0)
		{
			 return false;
		}
		if (errorcode == 0)
		{
			// Exit Function.
			return true;
		}
	}
	if (permissioncheck == -1)
	{
		// Permission Denied return false
		error.PanicHandler("FileUtills::CreateDirectory : User lacks permission to create directory. Access Denied.");
		return false;
	}
	if (permissioncheck > 0 || permissioncheck <= -2)
	{
		 // Error occured exit function
		 return false;
	}
#endif

	// Return False as we have no support on this platform.
	return false;
}
*/

int FileUtills::CheckPermissions(const std::string & Filename, Panic::ERROR & error, bool read, bool write)
{
	// Double check and make sure we have something to do.
	if (read == false && write == false)
	{
		// Ok what? Call PanicHandler.
		error.PanicHandler("FileUtills::CheckPermissions : CheckPermissions called but no permissions to check due to args. Returning -3");

		// Return -3
		return -3;
	}

#ifdef POSIX_COMMON_H
	//init vars
	int errorcode = 0;

	// Find out if file or directory exists
	if ((errorcode = DoesExist(Filename, error)) == -1)
	{
		// File does not exist return -2.
		return -2;
	}

	// Also check and make sure no other error occured.
	if (errorcode == -2)
	{
		// Something went wrong with DoesExist return -3.
		return -3;
	}

	// Reset errorcode
	errorcode = 0;

	// DoesExist returned ok, Begin check
	if (read == true && write == false)
	{
		// Check for read only permission.
		errorcode = access(Filename.c_str(), R_OK);
		if (errorcode != 0)
		{
			// File or Directory is not readable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable return 0.
			return 0;
		}

		// Unknown error call Panic Handler
		error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during read permission check. Returning -3");
		return -3;
	}

	if (read == false && write == true)
	{
		// Check for write only permission. (odd but for rundundantcy.)
		errorcode = access(Filename.c_str(), W_OK);

		if (errorcode != 0)
		{
			// File or Directory is not writeable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is writeable return 0.
			return 0;
		}

		// Unknown error call Panic Handler
		error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during write permission check. Returning -3");
		return -3;
	}

	if (read == true && write == true)
	{
		// Check for read and write permissions.
		errorcode = access(Filename.c_str(), R_OK);
		if (errorcode != 0)
		{
		    // File or directory is not readable. it has failed one critera for check, return -1.
		    return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable check for write permission.
			errorcode = access(Filename.c_str(), W_OK);

			if (errorcode != 0)
			{
				// File or Directory is not writeable return -1
				return -1;
			}
			if (errorcode == 0)
			{
				// File or directory is writeable return 0.
				return 0;
			}
			else
			{
				// Unknown error call panic handler.
				error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during write permission check. Returning -3");
				return -3;
			}
		}
		else
		{
			// Unknown error call panic handler.
			error.PanicHandler("FileUtills::CheckPermissions : Unknown Error occured during read permission check. Returning -3");
			return -3;
		}
	}

#endif
  // Call Panic Handler there is no OS / arch impilmentation.
  error.PanicHandler("FileUtills::CheckPermissions : OS / arch not supported. No Implementation found. Returning -3.");

  // Default Return
  return -3;
}


int FileUtills::CheckPermissions(const std::string & path, bool read, bool write)
{
	// Double check and make sure we have something to do.
	if (read == false && write == false)
	{
		// Return -3
		return -3;
	}

#ifdef POSIX_COMMON_H
	//init vars
	int errorcode = 0;

	// Find out if file or directory exists
	if ((errorcode = DoesExist(path)) == -1)
	{
		// File does not exist return -2.
		return -2;
	}

	// Also check and make sure no other error occured.
	if (errorcode == -2)
	{
		// Something went wrong with DoesExist return -3.
		return -3;
	}

	// Reset errorcode
	errorcode = 0;

	// DoesExist returned ok, Begin check
	if (read == true && write == false)
	{
		// Check for read only permission.
		errorcode = access(path.c_str(), R_OK);
		if (errorcode != 0)
		{
			// File or Directory is not readable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable return 0.
			return 0;
		}
        // Unknown error
		return -3;
	}

	if (read == false && write == true)
	{
		// Check for write only permission. (odd but for rundundantcy.)
		errorcode = access(path.c_str(), W_OK);

		if (errorcode != 0)
		{
			// File or Directory is not writeable return -1
			return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is writeable return 0.
			return 0;
		}

		// Unknown error
		return -3;
	}

	if (read == true && write == true)
	{
		// Check for read and write permissions.
		errorcode = access(path.c_str(), R_OK);
		if (errorcode != 0)
		{
		    // File or directory is not readable. it has failed one critera for check, return -1.
		    return -1;
		}
		if (errorcode == 0)
		{
			// File or directory is readable check for write permission.
			errorcode = access(path.c_str(), W_OK);

			if (errorcode != 0)
			{
				// File or Directory is not writeable return -1
				return -1;
			}
			if (errorcode == 0)
			{
				// File or directory is writeable return 0.
				return 0;
			}
			else
			{
				// Unknown error
				return -3;
			}
		}
		else
		{
			// Unknown error
			return -3;
		}
	}

#endif
  // there is no OS / arch impilmentation return default.
  // Default Return
  return -3;
}


int FileUtills::DoesExist(const std::string & Filename, Panic::ERROR & error)
{
#ifdef POSIX_COMMON_H

    // Declare some vars.
    int errorcode = 0; // Holds error number.

    // Check and see if the file exists.
    errorcode = access(Filename.c_str(), F_OK);

    // Get error code.
    if (errorcode == 0)
    {
	// File exists return ok
	return 0;
    }
    if (errorcode == -1)
    {
	// File does not exist return false.
	return -1;
    }
    else
    {
	// Ok What happened? Call PanicHandler
	error.PanicHandler("FileUtills::DoesExist : Unknown Error, returning false on file exist check.");
    }
#endif
  // Call Panic Handler arch / OS not supported.
  error.PanicHandler("FileUtils::DoesExist : OS / arch not supported. No Implementation found. Returning -2.");

  // Default return.
  return -2;
}

int FileUtills::DoesExist(const std::string & Filename)
{
#ifdef POSIX_COMMON_H

    // Declare some vars.
    int errorcode = 0; // Holds error number.

    // Check and see if the file exists.
    errorcode = access(Filename.c_str(), F_OK);

    // Get error code.
    if (errorcode == 0)
    {
	// File exists return ok
	return 0;
    }
    if (errorcode == -1)
    {
	// File does not exist return false.
	return -1;
    }
    else
    {
        // Unknown error return false.
        return -1;
    }
#endif
  // arch / OS not supported.

  // Default return.
  return -2;
}

int FileUtills::IsFileOrDirectory(const std::string & path)
{
        // Make sure that the path is not empty.
        if (path.size() <= 0)
        {
                // Empty path.
                return -5;
        }

#ifdef POSIX_COMMON_H
        // Init vars.
        int result = 0;
        int call_result = 0;
        struct stat * buf = NULL;

        // Init stat buffer.
        buf = new struct stat;

        // Ask the OS to stat() the path.
        call_result = stat(path.c_str(), buf);

        // Check the result.
        if (call_result != 0)
        {
                // Error, see if it was a permissions error.
                if (errno == EACCES)
                {
                        // Permissions error.
                        result = -4;
                }
                if (errno == ENOENT)
                {
                        // A path componet does not exist.
                        result = -6;
                }
                if (errno == ENOTDIR)
                {
                        // Path has a file in it, and is not the final componet.
                        result = -7;
                }
                else
                {
                        // Some other error.
                        result = -9;
                }
        }

        // Guard against failed operation.
        if (call_result == 0)
        {
                // Check the stat structure.
                if (S_ISREG((buf->st_mode)))
                {
                        // Path is a regular file.
                        result = 1;
                }
                if (S_ISDIR((buf->st_mode)))
                {
                        // Path is a directory.
                        result = 2;
                }
        }

        // Delete stat buffer.
        delete buf;
        buf = NULL;

        // Exit function.
        return result;
#endif

        // System unsupported, why not add support for it? :)
        return -3;
}

int FileUtills::CheckParent(const std::string & path, bool read, bool write)
{
#ifdef POSIX_COMMON_H
    // Init vars
    std::string parentbuffer = "";
    long int length = 0;
    long int location = 0;
    int result = 0;

    // Remove the trailing slash if present.
    parentbuffer = RemoveTrailingSlash(path);

    // Check the Path for absolute path.
    parentbuffer = FileUtills::CheckPathType(parentbuffer);

    // Check the length of the path.
    length = parentbuffer.length();

    // Check and see if the length is zero.
    if (length == 0)
    {
        // Nothing to do so return that the path does not exist. (It clearly does not exist.)
        return -2;
    }

    // Locate the path seperator before the last directory / file name.
    location = parentbuffer.find_last_of(DIR_SEP);

    // Check and make sure that the location of the dir sep is inside the string
    if (location > length || length < 0 ||  location < 0)
    {
        // Memory error or someone is fucking with us.
        // Either way kill the function
        return -5;
    }

    // Check and see if the parentbuffer is a root directory
    if (length > 1)
    {

        // Get the parent directory path.
        // Note substr CAN throw an exception. so we need to put this in a try catch block.
        try{
            parentbuffer = parentbuffer.substr(0, location);
        }
        catch(exception &ex)
        {
            // If we end up here we're in trouble.
            // Kill the function to be safe.
            return -5;
        }

        // Now rerun the check for a dir sep on the end.
        parentbuffer = RemoveTrailingSlash(parentbuffer);
    }

    // Call the other functions
    result = FileUtills::CheckPermissions(parentbuffer, read, write);

    // Check the result
    switch (result)
    {
        // Successful
        case 0:
            return 0;
            break;
        // Permission error
        case -1:
            return -1;
            break;
        // Parent Does not exist
        case -2:
            return -2;
            break;
        // Unknown error (Probabliy a memory error)
        default:
            return -5;
            break;
    };
#endif
  // arch / OS not supported.
  return -3;
}

std::string FileUtills::GetParent(const std::string & path)
{
    // Init vars.
    std::string parentbuffer = "";
    long int length = 0;
    long int location = 0;

#ifdef POSIX_COMMON_H
    // Remove the trailing slash if present.
    parentbuffer = RemoveTrailingSlash(path);

    // Check the Path for absolute path.
    parentbuffer = FileUtills::CheckPathType(parentbuffer);

    // Check the length of the path.
    length = parentbuffer.length();

    // Check and see if the length is zero.
    if (length == 0)
    {
        // Nothing to do so return that the path does not exist. (It clearly does not exist.)
        parentbuffer = "";
        return parentbuffer;
    }

    // Locate the path seperator before the last directory / file name.
    location = parentbuffer.find_last_of(DIR_SEP);

    // Check and make sure that the location of the dir sep is inside the string
    if (location > length || length < 0 ||  location < 0)
    {
        // Memory error or someone is fucking with us.
        // Either way kill the function
        parentbuffer = "";
        return parentbuffer;
    }

    // Check and see if the parentbuffer is a root directory
    if (length > 1)
    {
        // Get the parent directory path.
        // Note substr CAN throw an exception. so we need to put this in a try catch block.
        try{
            parentbuffer = parentbuffer.substr(0, location);
        }
        catch(exception &ex)
        {
            // If we end up here we're in trouble.
            // Kill the function to be safe.
            parentbuffer = "";
            return parentbuffer;
        }

        // Now rerun the check for a dir sep on the end.
        parentbuffer = RemoveTrailingSlash(parentbuffer);

        // Exit function.
        return parentbuffer;

    }
#endif
  // arch / OS not supported.
  parentbuffer = "";
  return parentbuffer;

}

short FileUtills::DeletePath(const std::string & path, const bool & recursive)
{
#ifdef POSIX_COMMON_H
        // Init vars.
        bool done = false;                              // Used to know when to exit the recursive iterator loop.
        bool resetIterLoop = false;                     // Used to control resetting the recursive iterator loop.
        bool unableToDeleteAll = false;                 // Used to tell if we could not delete something while deleting recursively.
        int result = 0;                                 // Used to store results from calls to other functions.
        size_t x = 0;                                   // Used by the recursion loop, for accessing the directory list.
        std::string currentabspath = "";                // Used to contain the current absolute path.
        std::string dummy = "";                         // Used to construct temporary paths.
        FileUtills::dirlist * plist = NULL;             // Used to store paths for recursive deletions.
        std::vector<std::string>::iterator iter;        // plist->list (Directory Listing).
        std::vector<size_t> directory_offsets;          // Used to store the offsets in the directory listings.

        // Check and see if the file can be erased.
        result = FileUtills::CheckPermissions(path);

        // Attempt to delete the path if the OS permissions allow it.
        if (result == 0)
        {
                // Call removal function.
                if (remove(path.c_str()) != 0)
                {
                        // Check the error.
                        if (errno == EACCES)
                        {
                                // Permissions error.
                                return -1;
                        }
                        if (errno == EPERM)
                        {
                                // Permissions error.
                                return -1;
                        }
                        if (errno == ENOTEMPTY) // Path is a non empty directory.
                        {
                                // If we have recursive set to true we can delete the path, else return an error.
                                if (recursive)
                                {
                                        // Copy the src path to the currentabspath var.
                                        currentabspath = path;

                                        // Begin recursion loop.
                                        do
                                        {
                                                // OK we need to get the paths of every file in the directory and any other directories.
                                                plist = NULL;
                                                plist = FileUtills::getDirectory(currentabspath, true);
                                                if (plist == NULL)
                                                {
                                                        // Could not get directory list.
                                                        if (plist != NULL)
                                                        {
                                                                delete plist;
                                                                plist = NULL;
                                                        }
                                                        return -4;
                                                }

                                                // Reset the iter just to be safe.
                                                iter = plist->list.begin();

                                                // Check and see if the directory offset list has anything in it.
                                                if ((!resetIterLoop) && (directory_offsets.size() > 0))
                                                {
                                                        // We have an offset, so init x to that offset.
                                                        x = directory_offsets[(directory_offsets.size() - 1)];      // size() returns the number of valid elements in the vector.

                                                        // Fix the iterator.
                                                        iter = iter + x;

                                                        // Erase the offset from the vector.
                                                        directory_offsets.erase((directory_offsets.end() - 1));     // end() returns the position after the last valid element in the vector.
                                                }
                                                else
                                                {
                                                        // We don't have any offsets, (or we just switched to a subdirectory) so init x to zero.
                                                        x = 0;

                                                        // Unset resetIterLoop.
                                                        resetIterLoop = false;
                                                }

                                                // Begin loop to check for more subdirectories.
                                                for (; x < plist->list.size(); x++)
                                                {
                                                        // Create temp path.
                                                        dummy.clear();
                                                        dummy = currentabspath + DIR_SEP + (plist->list[x]);
                                                        dummy = RemoveTrailingSlash(dummy);     // If we got a DIR_SEP at the end of the string get rid of it.

                                                        // Check to see if the current entry in the list is a directory.
                                                        switch (FileUtills::IsFileOrDirectory(dummy))
                                                        {
                                                                case 0:         // Not a file or directory. (Try to remove anyway.)
                                                                case 1:         // File.
                                                                    // Attempt to delete file.
                                                                    if (remove(dummy.c_str()) != 0)
                                                                    {
                                                                            // Set unableToDeleteAll.
                                                                            unableToDeleteAll = true;

                                                                            /*
                                                                                Note: We need someway of keeping track of what
                                                                                files we've already attempted to delete,
                                                                                Otherwise we'll end up in an indefinte loop.

                                                                                The easist way to to have the list generated the same
                                                                                way each time and store the offsets. (I.e each call to
                                                                                FileUtills::getDirectory() returns the same list. As
                                                                                opposed to just the way the OS spits out the directory
                                                                                listing.)

                                                                                Then when the subdirectory is removed, (or after the failed removal
                                                                                attempt) find where that subdirectory was in the list and continue.
                                                                            */
                                                                    }
                                                                    break;
                                                                case 2:         // Directory.
                                                                    // Set currentabspath to this path.
                                                                    currentabspath = dummy;

                                                                    // Set the current directory list offset (x) in to the vector.
                                                                    directory_offsets.push_back(x);

                                                                    // Set reset flag.
                                                                    resetIterLoop = true;

                                                                    // Get out of this loop.
                                                                    break;
                                                                case -3:        // OS not supported.
                                                                    if (plist != NULL)
                                                                    {
                                                                            delete plist;
                                                                            plist = NULL;
                                                                    }
                                                                    return -3;
                                                                case -4:        // Permission error.
                                                                case -5:        // Arg error.
                                                                case -6:        // Path componet does not exist.
                                                                case -7:        // Part of path is a file.
                                                                case -9:        // Memory error.
                                                                default:
                                                                    // Set unableToDeleteAll.
                                                                    unableToDeleteAll = true;
                                                                    break;
                                                        };

                                                        // Check to see if reset flag is set.
                                                        if (resetIterLoop)
                                                        {
                                                                // Get out of this loop.
                                                                break;
                                                        }
                                                }

                                                // Check to see how the previous loop exited.
                                                if (!resetIterLoop)
                                                {
                                                        // Remove the directory.
                                                        if (remove(currentabspath.c_str()) != 0)
                                                        {
                                                                // Check and see if unableToDeleteAll was set. If it was set, we ignore this error.
                                                                if (!unableToDeleteAll)
                                                                {
                                                                        // Check the error.
                                                                        if (errno == EACCES)
                                                                        {
                                                                                // Permissions error.
                                                                                if (plist != NULL)
                                                                                {
                                                                                        delete plist;
                                                                                        plist = NULL;
                                                                                }
                                                                                return -1;
                                                                        }
                                                                        else
                                                                        {
                                                                                if (errno == EPERM)
                                                                                {
                                                                                        // Permissions error.
                                                                                        if (plist != NULL)
                                                                                        {
                                                                                                delete plist;
                                                                                                plist = NULL;
                                                                                        }
                                                                                        return -1;
                                                                                }
                                                                                else
                                                                                {
                                                                                        // Some other error.
                                                                                        if (plist != NULL)
                                                                                        {
                                                                                                delete plist;
                                                                                                plist = NULL;
                                                                                        }
                                                                                        return -5;
                                                                                }
                                                                        }
                                                                }
                                                                else
                                                                {
                                                                        // Increment the offset in the vector. (We have dealt with this subdirectory.)
                                                                        if (directory_offsets.size() > 0)
                                                                        {
                                                                                directory_offsets[(directory_offsets.size() - 1)] = (directory_offsets[(directory_offsets.size() - 1)] + 1);
                                                                        }
                                                                }
                                                        }

                                                        // Check to see if we removed the source dir.
                                                        if (currentabspath != path)
                                                        {
                                                                // Get the parent directory of currentabspath.
                                                                currentabspath = FileUtills::GetParent(currentabspath);
                                                                if (currentabspath.size() <= 0)
                                                                {
                                                                        // Could not get parent directory.
                                                                        if (plist != NULL)
                                                                        {
                                                                                delete plist;
                                                                                plist = NULL;
                                                                        }
                                                                        return -7;
                                                                }

                                                                // Delete the old plist.
                                                                if (plist != NULL)
                                                                {
                                                                        delete plist;
                                                                        plist = NULL;
                                                                }
                                                        }
                                                        else
                                                        {
                                                                // Delete the old plist.
                                                                if (plist != NULL)
                                                                {
                                                                        delete plist;
                                                                        plist = NULL;
                                                                }

                                                                // All directories have been deleted.
                                                                done = true;
                                                        }
                                                }
                                                else
                                                {
                                                        // Delete the old plist.
                                                        if (plist != NULL)
                                                        {
                                                                delete plist;
                                                                plist = NULL;
                                                        }
                                                }
                                        }while (!done);

                                        // Delete the plist.
                                        if (plist != NULL)
                                        {
                                                delete plist;
                                                plist = NULL;
                                        }

                                        // Clear dummy and currentabspath.
                                        dummy.clear();
                                        currentabspath.clear();

                                        // Flush the directory_offsets vector.
                                        directory_offsets.clear();

                                        // Check and see if the unableToDeleteAll flag is set.
                                        if (unableToDeleteAll)
                                        {
                                                // We can't delete some things so return an error.
                                                return -8;
                                        }
                                }
                                else
                                {
                                        // Path is not empty and we are not deleting recursively.
                                        return -6;
                                }
                        }
                        else
                        {
                                // Some other error.
                                return -5;
                        }
                }
        }
        else
        {
                // Determine the error.
                switch (result){
                    // Permission BAD
                    case -1:
                        return -1;
                        break;
                    // Path does not exist
                    case -2:
                        return -2;
                        break;
                    // Either an unknown error or function is not supported
                    case -3:
                        return -3;
                        break;
                    // Possible memory error
                    default:
                        return -4;
                        break;
                };
        }

        // Exit function.
        return 0;
#endif
        // System not supported.
        return -3;
}

short FileUtills::CopyFile(const std::string & src, const std::string & dest, const bool & append, const size_t & begOffset, const size_t & endOffset)
{
        // Init vars.
        const size_t buffer_size = 512;                 // Constant used to determine the size of the file copy buffer.
        size_t result = 0;                              // Used to hold the returned result of this function to the caller.
        size_t count = 0;                               // Used while copying data to count the number of copied bytes.
        size_t total_bytes_copied = 0;                  // Holds the total amount of copied bytes.
        size_t input_size = 0;                          // Holds the size of the input file.
        size_t bytes_to_copy = 0;                       // Holds the total amount of bytes to copy from the input file.
        char * pBuffer = NULL;                          // Used as a buffer for copying data.
        fstream input;                                  // File stream for input file.
        fstream output;                                 // File stream for output file.

        // Check and make sure that the beginning offset is smaller than the ending offset.
        if (begOffset > endOffset)
        {
                // Offsets are out of order.
                result = -5;
        }
        else
        {
                // Check the source file name length.
                if (src.size() <= 0)
                {
                        // Invalid source file name.
                        result = -10;
                }
                else
                {
                        // Attempt to open the file.
                        input.open(src.c_str(), ios::in | ios::binary);
                        if (!input.is_open())
                        {
                                // Could not open file.
                                result = -11;
                        }
                        else
                        {
                                // Get file size.
                                input.seekg(0, ios::end);
                                input_size = input.tellg();
                                input.seekg(0, ios::beg);

                                // Determine if the input file has the needed amount of bytes to copy.
                                if (input_size < begOffset)
                                {
                                        // Input file is smaller than the beginning offset.
                                        result = -12;
                                }
                                else
                                {
                                        if (input_size < endOffset)
                                        {
                                                // Input file is smaller than the ending offset.
                                                result = -13;
                                        }
                                        else
                                        {
                                                // Check to see if we are copying the entire file.
                                                if ((begOffset == 0) && (endOffset == 0))   // Shortcut so the caller does not need to know the size of the file.
                                                {
                                                        // We are copying the entire file.
                                                        bytes_to_copy = input_size;
                                                }
                                                else
                                                {
                                                        // Calculate the total amount of bytes to copy.
                                                        bytes_to_copy = endOffset - begOffset;

                                                        // Seek to the beginning offset in the source file.
                                                        input.seekg(begOffset, ios::beg);
                                                }

                                                // Check the length of the dest.
                                                if (dest.size() <= 0)
                                                {
                                                        // Invalid dest path.
                                                        result = -20;
                                                }
                                                else
                                                {
                                                        // Open output file.
                                                        if (append)
                                                        {
                                                                output.open(dest.c_str(), ios::in | ios::out | ios::binary | ios::app);
                                                                output.seekg(0, ios::end);
                                                                output.seekp(0, ios::end);
                                                        }
                                                        else
                                                        {
                                                                output.open(dest.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
                                                        }

                                                        // Check to see if the file is open.
                                                        if (!output.is_open())
                                                        {
                                                                // Could not open output file.
                                                                result = -21;
                                                        }
                                                        else
                                                        {
                                                                // Begin try block.
                                                                try{
                                                                        // Allocate memory buffer.
                                                                        pBuffer = (char*)malloc(buffer_size);
                                                                        if (pBuffer == NULL)
                                                                        {
                                                                                // Could not allocate memory buffer.
                                                                                result = -9;
                                                                        }
                                                                        else
                                                                        {
                                                                                // Blank the buffer.
                                                                                memset(pBuffer, '\0', buffer_size);

                                                                                // Start copy loop.
                                                                                while (total_bytes_copied < bytes_to_copy)
                                                                                {
                                                                                        // Check the state of the file streams.
                                                                                        if (input.fail())
                                                                                        {
                                                                                                // Input file stream error.
                                                                                                if (input.bad())
                                                                                                {
                                                                                                        // Read IO error.
                                                                                                        result = -14;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        // Logical IO error.
                                                                                                        result = -15;
                                                                                                }

                                                                                                // Get out of the loop.
                                                                                                break;
                                                                                        }
                                                                                        if (input.eof())
                                                                                        {
                                                                                                // ??? We should not have hit eof....
                                                                                                result = -16;

                                                                                                // Get out of the loop.
                                                                                                break;
                                                                                        }
                                                                                        if (output.fail())
                                                                                        {
                                                                                                // Output file stream error.
                                                                                                if (output.bad())
                                                                                                {
                                                                                                        // Write IO error.
                                                                                                        result = -24;
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                        // Logical IO error.
                                                                                                        result = -25;
                                                                                                }

                                                                                                // Get out of the loop.
                                                                                                break;
                                                                                        }

                                                                                        // Check and see if the data remaining to copy is less than the buffer size.
                                                                                        if ((bytes_to_copy - total_bytes_copied) < buffer_size)
                                                                                        {
                                                                                                // OK we only need to copy the remaining data.
                                                                                                input.read(pBuffer, (bytes_to_copy - total_bytes_copied));
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                                // Fill up the buffer.
                                                                                                input.read(pBuffer, buffer_size);
                                                                                        }

                                                                                        // Get the number of read bytes.
                                                                                        count = input.gcount();

                                                                                        // Write out the bytes to the output file.
                                                                                        output.write(pBuffer, count);

                                                                                        // Add the bytes copied to the total.
                                                                                        total_bytes_copied += count;
                                                                                }

                                                                                // Deallocate memory buffer.
                                                                                memset(pBuffer, '\0', buffer_size);
                                                                                if (pBuffer != NULL)
                                                                                {
                                                                                        free(pBuffer);
                                                                                        pBuffer = NULL;
                                                                                }
                                                                        }
                                                                }
                                                                catch(...)
                                                                {
                                                                        // Exception thrown during copy loop.
                                                                        result = -9;
                                                                }

                                                                // Close output file.
                                                                if (output.is_open())
                                                                {
                                                                        output.close();
                                                                }
                                                        }
                                                }
                                        }
                                }

                                // Close input file.
                                if (input.is_open())
                                {
                                        input.close();
                                }
                        }
                }
        }

        // Exit function.
        return result;
}

int FileUtills::MoveFile(const std::string & src, const std::string & dest, bool overwrite)
{
        // Dumb check.
        if (src.size() <= 0)
        {
                // Bad src.
                return -5;
        }
        if (dest.size() <= 0)
        {
                // Bad dest.
                return -5;
        }

        // Init vars.
        int fileResult = 0;         // Used for return codes.

        // Check and see if dest already exists.
        fileResult = FileUtills::DoesExist(dest);
        switch (fileResult)
        {
                case 0:     // File exists.
                    if (overwrite == true)
                    {
                            // Attempt to delete dest file.
                            fileResult = FileUtills::DeletePath(dest);
                            switch (fileResult)
                            {
                                    case 0:     // Delete OK.
                                        break;
                                    default:    // Unable to delete file.
                                        return -21;
                                        break;
                            };
                    }
                    else
                    {
                            // Can't delete existing file bail out.
                            return -20;
                            break;
                    }
                    break;
                case -1:    // File does not exist.
                    break;
                default:    // Some error.
                    return -22;
                    break;
        };

        // Copy entire file to the dest.
        fileResult = FileUtills::CopyFile(src, dest);
        switch (fileResult)
        {
                case 0:     // Copy ok.
                    break;
                case -1:    // Source Permission error.
                    return -10;
                case -2:    // Source Does not exist.
                    return -10;
                default:    // Some error.
                    return -4;
                    break;
        };

        // Delete original file.
        fileResult = FileUtills::DeletePath(src);
        switch (fileResult)
        {
                case 0:     // Delete ok.
                    return 0;
                    break;
                default:    // Some error.
                    return -4;
                    break;
        };

        // Default return.
        return -3;
}
