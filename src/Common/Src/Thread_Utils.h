/*!
    Multiverse Engine Project 06/5/2013 Common Thread_Utils.h
    
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

#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

// These lines determine what libraries to build wappers for.
#define TW_PTHREADS_SUPPORT 1

// External includes.
#include <stddef.h>     // For errno.
#include <time.h>       // For timespec and clock_gettime().

// Internal includes.
#include "Thread_Utils_Structures.h"
#include "Thread_Utils_Base.h"
#include "Thread_Utils_Functions.h"

/*
        Below are includes for the different library wrappers if they are enabled.
        NOTE: The actual includes for the external libraries should be put in the wrapper include NOT HERE!
*/
#ifdef TW_PTHREADS_SUPPORT
#include "Thread_Utils_pthread.h"
#endif

#endif

// End of Thread_Utils.h
