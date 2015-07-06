/*!
    Multiverse Engine Project 21/8/2014 FileUtills FileUtills_Emulated_Symbolic_Link_Functions.cpp
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

// Include header file.
#include "FileUtills_Emulated_Symbolic_Link_Functions.h"
#include "../Byte_Order.h"		/* Defines the various Common_*_Endianness_Check() functions. */

int FileUtills::Create_MSYS_Emulated_Symbolic_Link(const char * linkDestionation, const size_t linkDestionationSize,
												   const char * pathToLinkFile, const size_t pathToLinkFileSize)
{
		/* Init vars. */
		int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;		/* The result of this function. */
		int retFromC = 0;										/* The result of C calls. */
		FILE * outputFile = NULL;								/* The FILE pointer for the emulated link file. */
		size_t tempSize = 0;									/* Temporary size used to calculate the size of variables. */
		
		/* Check for valid arguments. */
		if ((linkDestionation != NULL) && (pathToLinkFile != NULL) && (linkDestionationSize > 0) && (pathToLinkFileSize > 0))
		{
					/* Check and see if the file already exists. */
					ret = FileUtills::DoesExist(pathToLinkFile, pathToLinkFileSize);
					if (ret == FILEUTILLS_ERROR_NON_EXISTANT)
					{
							/* Open the new link file for writing. */
							outputFile = fopen(pathToLinkFile, "wb");
							if (outputFile != NULL)
							{
									/* Now output the magic string. */
									ret = FileUtills_Write_Data_To_File_From_Memory(outputFile, MSYS_EMU_SYMLINK_MAGIC, sizeof MSYS_EMU_SYMLINK_MAGIC);
									if (ret == COMMON_ERROR_SUCCESS)
									{
											/* Set tempSize to the length of a size_t. (length of the path length integer.) */
											tempSize = sizeof (size_t);

											/* Determine if we need to swap the byte order of the integers. (size of length and the length itself are supposed to be big-endian encoded.) */
											if (Common_UINT_Endianness_Check() == MSYS_BIG_ENDIAN)
											{
													/* Now we need to output the number of bytes for the linkDestionation string's length. (ie. sizeof(size_t)). (This is in big-endianess format.) */
													ret = FileUtills_Write_Data_To_File_From_Memory(outputFile, ((char*)(&tempSize)), MSYS_EMU_SYMLINK_BYTE_COUNT_FIELD_SIZE);
													if (ret == COMMON_ERROR_SUCCESS)
													{
															/* Now we need to output the length of the linkDestionation string. (This is in big-endianess format.) */
															tempSize = linkDestionationSize;
															ret = FileUtills_Write_Data_To_File_From_Memory(outputFile, ((char*)(&tempSize)), sizeof(size_t));
													}
											}
											else
											{
													/* Convert the bits to big endian first. */
													ret = Common_Host_To_Big_Endian_UInt(&tempSize);
													if (ret == COMMON_ERROR_SUCCESS)
													{
															/* Now we need to output the number of bytes for the linkDestionation string's length. (ie. sizeof(size_t)). (This is in big-endianess format.) */
															ret = FileUtills_Write_Data_To_File_From_Memory(outputFile, ((char*)(&tempSize)), MSYS_EMU_SYMLINK_BYTE_COUNT_FIELD_SIZE);
															if (ret == COMMON_ERROR_SUCCESS)
															{
																	/* Now convert the length of the string to big-endian format. */
																	tempSize = linkDestionationSize;
																	ret = Common_Host_To_Big_Endian_UInt(&tempSize);
																	if (ret == COMMON_ERROR_SUCCESS)
																	{
																			/* Now we need to output the length of the linkDestionation string. (This is in big-endianess format.) */
																			ret = FileUtills_Write_Data_To_File_From_Memory(outputFile, ((char*)(&tempSize)), sizeof(size_t));
																	}
															}
													}
											}

											/* Only continue if we were successful in outputting the length. */
											if (ret == COMMON_ERROR_SUCCESS)
											{
													/* Output the linkDestionation string. */
													ret = FileUtills_Write_Data_To_File_From_Memory(outputFile, linkDestionation, linkDestionationSize);
											}
											
											/* Close the file. */
											retFromC = fclose(outputFile);
											if (retFromC != 0)
											{
													if (ret == COMMON_ERROR_SUCCESS)
													{
															/* OK, we could not close the file for some reason. */
															ret = COMMON_ERROR_IO_ERROR;
															COMMON_LOG_DEBUG("FileUtills_Create_MSYS_Emulated_Symbolic_Link(): ");
															COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_IO_ERROR));
															COMMON_LOG_DEBUG(" Could not close link file.");
															
													}
													else
													{
															/* Previous errors detected. */
															COMMON_LOG_DEBUG("FileUtills_Create_MSYS_Emulated_Symbolic_Link(): ");
															COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_IO_ERROR));
															COMMON_LOG_DEBUG(" Could not close link file, another error was detected: ");
															COMMON_LOG_DEBUG(Common_Get_Error_Message(ret));
															ret = COMMON_ERROR_IO_ERROR;
													}
											}
									}
							}
							else
							{
									/* Could not open output file for writing. */
									ret = COMMON_ERROR_IO_ERROR;
									
									/* Log the error. */
									COMMON_LOG_DEBUG("FileUtills_Create_MSYS_Emulated_Symbolic_Link(): ");
									COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_IO_ERROR));
									COMMON_LOG_DEBUG(" could not open ( ");
									COMMON_LOG_DEBUG(pathToLinkFile);
									COMMON_LOG_DEBUG(" ) for writing.");
							}
					}
					else
					{
							/* File is not empty, abort. */
							ret = FILEUTILLS_ERROR_EXISTANT;

							/* Log the error. */
							COMMON_LOG_INFO("FileUtills_Create_MSYS_Emulated_Symbolic_Link(): ");
							COMMON_LOG_INFO(Common_Get_Error_Message(FILEUTILLS_ERROR_EXISTANT));
							COMMON_LOG_INFO(" The given path ( ");
							COMMON_LOG_INFO(pathToLinkFile);
							COMMON_LOG_INFO(" ) already exists.");
					}
		}
		else
		{
				/* Invalid destionationLink. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;

				/* Log the error. */
				COMMON_LOG_DEBUG("FileUtills_Create_MSYS_Emulated_Symbolic_Link(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
				COMMON_LOG_DEBUG(" Given destination link string is invalid.");
		}

		/* Return the result. */
		return ret;
}

int FileUtills::Read_MSYS_Emulated_Symbolic_Link(char ** retStr, size_t * retStrSize, const char * pathToLinkFile, 
												 const size_t pathToLinkFileSize)
{
		/* Init vars. */
		int ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;		/* The result of this function. */
		int retFromC = 0;										/* The result of C calls. */
		unsigned int byteCount = 0;								/* The number of bytes in a size_t variable, as reported from the file. */
		FILE * inputFile = NULL;								/* The FILE pointer for the emulated link file. */
		char * tempRetStr = NULL;								/* Used to construct the retStr before we copy the pointer at the end. */
		size_t tempSize = 0;									/* Temporary size used to calculate the size of variables. */
		size_t fileSize = 0;									/* Size of the given input file. */
		

		/* Check for valid arguments. */
		if ((retStr != NULL) && (pathToLinkFile != NULL) && (retStrSize != NULL) && (pathToLinkFileSize > 0))
		{
				/* Open the file for reading. */
				inputFile = fopen(pathToLinkFile, "rb");
				if (inputFile != NULL)
				{
							/* Get the size of the file. */
							
					
							/* Allocate the needed tempRetStr buffer. */
							tempRetStr = (char*)malloc(MSYS_FILEUTILLS_IO_BUFFER_LENGTH);
							if (tempRetStr != NULL)
							{
										/* OK, check and see if this is a link file. */
										ret = FileUtills_Read_Bytes_From_File(IN, (sizeof MSYS_EMU_SYMLINK_MAGIC), tempRetStr, MSYS_FILEUTILLS_IO_BUFFER_LENGTH, 0, true);
										if (ret == COMMON_ERROR_SUCCESS)
										{
												/* Check and see if the given bytes are the correct magic signature. */
												if (memcmp(tempRetStr, MSYS_EMU_SYMLINK_MAGIC, (sizeof MSYS_EMU_SYMLINK_MAGIC)) == 0)
												{
															/* Valid magic signature found, check and see if we can store the byte count in a size_t variable. */
															if (MSYS_EMU_SYMLINK_BYTE_COUNT_FIELD_SIZE < (sizeof(size_t)))
															{
																	/* Load the length of size_t from the file. */
																	ret = FileUtills_Read_Bytes_From_File(IN, MSYS_EMU_SYMLINK_BYTE_COUNT_FIELD_SIZE, tempRetStr, MSYS_FILEUTILLS_IO_BUFFER_LENGTH, ((sizeof (size_t)) - MSYS_EMU_SYMLINK_BYTE_COUNT_FIELD_SIZE), true);
																	if (ret == COMMON_ERROR_SUCCESS)
																	{
																			/* Memcpy the data into tempSize. */
																			memcpy(((char*)&tempSize), tempRetStr, sizeof (tempSize));

																			/* Get the system's endianess. */
																			ret = Common_SIZE_T_Endianness_Check();
																			switch (ret)
																			{
																					MSYS_BIG_ENDIAN:
																						/* Nothing to do. */
																						ret = COMMON_ERROR_SUCCESS;
																						break;
																					MSYS_LITTLE_ENDIAN:
																						/* We need to convert the bytes. */
																						ret = Common_Big_Endian_To_Host_UInt(tempSize);
																						break;
																					MSYS_UNKNOWN_ENDIANNESS:
																					default:
																						/* ERROR, we cannot convert the bytes due to unknown host endianess. */
																						ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;
																						break;
																			};
															
																			/* Make sure we can store the size_t from the file. */
																			if (tempSize <= sizeof(size_t))
																			{
																					/* Get link length variable. */
																					ret = FileUtills_Read_Bytes_From_File(IN, , tempRetStr , );
																					if (ret == COMMON_ERROR_SUCCESS)
																					{
																							/* OK copy the bytes from the tempRetStr buffer to byteCount. */
																							memcpy(((char*)&byteCount), tempRetStr, MSYS_EMU_SYMLINK_BYTE_COUNT_FIELD_SIZE);
																	
																							/* Check and see if we need to convert the bytes to the host's format. */
																							ret = Common_SIZE_T_Endianness_Check();
																							switch (ret)
																							{
																									MSYS_BIG_ENDIAN:
																										/* Nothing to do. */
																										ret = COMMON_ERROR_SUCCESS;
																										break;
																									MSYS_LITTLE_ENDIAN:
																										/* We need to convert the bytes. */
																										ret = Common_Big_Endian_To_Host_UInt(tempSize);
																										break;
																									MSYS_UNKNOWN_ENDIANNESS:
																									default:
																										/* ERROR, we cannot convert the bytes due to unknown host endianess. */
																										ret = COMMON_ERROR_FUNCTION_NOT_IMPLEMENTED;
																										break;
																							};
																				
																							/* Check for success. */
																							if (ret == COMMON_ERROR_SUCCESS)
																							{
																										/* OK, check and see if our size_t can store that much data. */
																										if (byteCount <= (sizeof size_t))
																										{
																									
																										}
																										else
																										{
																												/* Size of length variable is too big for us to process. */
																												ret = ;
																										}
																				}
																		}
															}
												}
										}
							}
							else
							{
										/* Could not allocate memory. */
										ret = COMMON_ERROR_MEMORY_ERROR;
							}
							
							/* Close the input file. */
							retFromC = fclose(IN);
							if (retFromC != 0)
							{
										/* Could not close the input file. */
										if (ret != COMMON_ERROR_IO_ERROR)
										{
												ret = COMMON_ERROR_IO_ERROR;
										}
										
										/* Log the error. */
										COMMON_LOG_DEBUG("FileUtills_Read_MSYS_Emulated_Symbolic_Link(): ");
										COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_IO_ERROR));
										COMMON_LOG_DEBUG(" could not close input file.");
							}
				}
				else
				{
							/* Could not open input file for reading. */
							ret = COMMON_ERROR_IO_ERROR;
									
							/* Log the error. */
							COMMON_LOG_DEBUG("FileUtills_Read_MSYS_Emulated_Symbolic_Link(): ");
							COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_IO_ERROR));
							COMMON_LOG_DEBUG(" could not open ( ");
							COMMON_LOG_DEBUG(pathToLinkFile);
							COMMON_LOG_DEBUG(" ) for reading.");
				}
		}
		else
		{
				/* Invalid arguments. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;

				/* Log the error. */
				COMMON_LOG_DEBUG("FileUtills_Read_MSYS_Emulated_Symbolic_Link(): ");
				COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		}

		/* Return the result. */
		return ret;
}

/* End of FileUtills_Emulated_Symbolic_Link_Functions.cpp */
