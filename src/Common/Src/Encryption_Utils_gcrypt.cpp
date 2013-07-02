/*!
    Multiverse Engine Project 02/7/2013 Common Encryption_Utils_gcrypt.cpp
    
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

short Common::Encryption_Utils::CryptoEngine_gcrypt::Encrypt(const char * data, const size_t & data_size, const char ** enc_data, size_t & enc_data_size)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Encrypt(const DataProcess::Data_Object & data, const DataProcess::Data_Object ** enc_data)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Decrypt(const char * enc_data, const size_t & enc_data_size, const char ** data, size_t & data_size)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Decrypt(const DataProcess::Data_Object & enc_data, const DataProcess::Data_Object ** data)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Create_Private_Key(const size_t & key_Length)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Create_Public_Key(const size_t & key_Length)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Load_Private_Key(const char * path, size_t & path_size)
{
      // Exit function.
      return -3;
}

short Common::Encryption_Utils::CryptoEngine_gcrypt::Load_Public_Key(const char * path, size_t & path_size)
{
      // Exit function.
      return -3;
}

void Common::Encryption_Utils::CryptoEngine_gcrypt::Get_Private_Key(const char * key, size_t & key_size)
{
      // Exit function.
      return;
}

void Common::Encryption_Utils::CryptoEngine_gcrypt::Get_Public_Key(const char * key, size_t & key_size)
{
      // Exit function.
      return;
}

void Common::Encryption_Utils::CryptoEngine_gcrypt::Erase_Private_Key()
{
      // Exit function.
      return;
}

void Common::Encryption_Utils::CryptoEngine_gcrypt::Erase_Public_Key()
{
      // Exit function.
      return;
}