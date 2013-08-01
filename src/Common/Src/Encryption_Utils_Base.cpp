/*!
    Multiverse Engine Project 02/7/2013 Common Encryption_Utils_Base.cpp
    
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

#include "Encryption_Utils.h"

int Common::Encryption_Utils::CryptoEngine::Get_Return_Code() const
{
      return this->libReturnCode;
}

const Common::LibraryID & Common::Encryption_Utils::CryptoEngine::Get_Encryption_Library() const
{
      return this->lib;
}