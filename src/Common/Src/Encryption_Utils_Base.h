/*!
    Multiverse Engine Project 01/7/2013 Common Encryption_Utils_Base.h
    
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

#ifndef ENCRYPTION_UTILS_BASE_H
#define ENCRYPTION_UTILS_BASE_H
namespace Common
{
      namespace Encryption_Utils
      {
	      class CryptoEngine : public Generic_Wrapper
	      {
			private:
			  
			protected:
			  int libReturnCode;			// Previous return code from the library.
			  
			public:
			  virtual ~CryptoEngine()
			  {
			    
			  }
			  
			  // Basic functions.
			  const Common::LibraryID & Get_Encryption_Library() const;
			  int Get_Return_Code() const;
			  
			  // Crypto functions.
			  virtual short Encrypt(const char * data, const size_t & data_size, const char ** enc_data, size_t & enc_data_size) = 0;
			  virtual short Encrypt(const DataProcess::Data_Object & data, const DataProcess::Data_Object ** enc_data) = 0;
			  virtual short Decrypt(const char * enc_data, const size_t & enc_data_size, const char ** data, size_t & data_size) = 0;
			  virtual short Decrypt(const DataProcess::Data_Object & enc_data, const DataProcess::Data_Object ** data) = 0;
			  
			  // Key functions.
			  virtual short Create_Private_Key(const size_t & key_Length) = 0;
			  virtual short Create_Public_Key(const size_t & key_Length) = 0;
			  virtual short Load_Private_Key(const char * path, size_t & path_size) = 0;
			  virtual short Load_Public_Key(const char * path, size_t & path_size) = 0;
			  virtual void Get_Private_Key(const char * key, size_t & key_size) = 0;
			  virtual void Get_Public_Key(const char * key, size_t & key_size) = 0;
			  
			  /*!
				virtual void Erase_Private_Key()
				
				This function unloads the private key from memory,
				and zeros out the memory that was used.
			  */
			  virtual void Erase_Private_Key() = 0;
			  
			  /*!
				 virtual void Erase_Public_Key()
				 
				 This function unloads the public key from memory,
				 and zeros out the memory that was used.
			  */
			  virtual void Erase_Public_Key() = 0;
	      };
	      
	      class HashEngine
	      {
			private:
			  
			protected:
			
			public:
			  
			  
	      };
      };
};
#endif

// End of Encryption_Utils_Base.h