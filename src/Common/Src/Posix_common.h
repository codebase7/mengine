/*!
    Multiverse Engine Project 04/12/2011 Common Posix_common.h

    This file includes the header files unique to the POSIX family of operating systems.
    It is required to compile the engine correctly on a POSIX compilent OS. 
    It is NOT required to compile the core module on a POSIX OS.
    As always all OS / Arch specific functions must be in common to be included as a part of the main binary.
    Otherwise they must be in an external module.

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
#ifdef linux
#ifndef POSIX_COMMON_H
#define POSIX_COMMON_H

// Needed for FileUtills
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/statvfs.h>
#include <sys/statfs.h>
#include <dirent.h>
#include <string.h>
#include <stddef.h>     // For errno.
#include <time.h>       // For timespec and clock_gettime().

// Internal includes.
#include "../../Core/Src/DataProcess.h"
#include "../../Core/Src/Panic.h"

#endif
#endif

// End of Posix_common.h
