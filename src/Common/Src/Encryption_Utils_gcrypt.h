/*!
    Multiverse Engine Project 02/7/2013 Common Encryption_Utils_gcrypt.h
    
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

#ifndef ENCRYPTION_UTILS_GCRYPT_H
#define ENCRYPTION_UTILS_GCRYPT_H

// Guard against building this if not supported.
#ifdef GCRYPT_SUPPORT

// External include.
#include <gcrypt.h>

namespace Common
{
      namespace Encryption_Utils
      {
	      // Library support status structure.
	      const Common::Encryption_Utils::Library_Support_Status LibSupport_gcrypt =
	      {
		      &Common::Encryption_Utils::supportedEncryptionLibs[1],          // {1, "gcrypt"}  (ID of the encryption library that this struct is for.)
	      };
	
	
	      // Derived types.
	      class CryptoEngine_gcrypt : public CryptoEngine
	      {
		    private:
		      
		    protected:
		      
		    public:
			CryptoEngine_gcrypt()
			{
			      enc_lib = Common::Encryption_Utils::supportedEncryptionLibs[1]; // {1, "gcrypt"}  (ID of the encryption library that this struct is for.)
			      libReturnCode = 0;
			}
			~CryptoEngine_gcrypt()
			{
			  
			}
		      
			// Crypto functions.
			short Encrypt(const char * data, const size_t & data_size, const char ** enc_data, size_t & enc_data_size);
			short Encrypt(const DataProcess::Data_Object & data, const DataProcess::Data_Object ** enc_data);
			short Decrypt(const char * enc_data, const size_t & enc_data_size, const char ** data, size_t & data_size);
			short Decrypt(const DataProcess::Data_Object & enc_data, const DataProcess::Data_Object ** data);
		      
			// Key functions.
			short Create_Private_Key(const size_t & key_Length);
			short Create_Public_Key(const size_t & key_Length);
			short Load_Private_Key(const char * path, size_t & path_size);
			short Load_Public_Key(const char * path, size_t & path_size);
			void Get_Private_Key(const char * key, size_t & key_size);
			void Get_Public_Key(const char * key, size_t & key_size);
			
			/*!
				virtual void Erase_Private_Key()
				
				This function unloads the private key from memory,
				and zeros out the memory that was used.
			*/
			void Erase_Private_Key();
			
			/*!
				 virtual void Erase_Public_Key()
				 
				 This function unloads the public key from memory,
				 and zeros out the memory that was used.
			*/
			void Erase_Public_Key();
	      };
      };
};

#endif
#endif

// End of Encryption_Utils_gcrypt.h