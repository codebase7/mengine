/*!
    Multiverse Engine Project 01/7/2013 Common Encryption_Utils.h
    
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

#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

// Define what libraries to build support for.
#define GCRYPT_SUPPORT 1

// External includes.


// Internal includes.
#include "BaseHeader.h"
#include "Encryption_Utils_Structures.h"
#include "Encryption_Utils_Base.h"
#include "Encryption_Utils_Functions.h"

// Includes for specific libraries.
#ifdef GCRYPT_SUPPORT
#include "Encryption_Utils_gcrypt.h"
#endif

#endif

// End of Encryption_Utils.h
