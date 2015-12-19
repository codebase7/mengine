/*!
    Multiverse Engine Project 17/12/2015 FileUtills FileUtills.c

    Copyright (C) 2015 Multiverse Engine Project

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

/* Internal includes. */
#include "FileUtills.h"
#include "FileUtills_Private_API.h"

/*!
 *		int FileUtills_RemoveTrailingSlash(char ** retStr, size_t * retStrSize)
 *
 *		Removes a DIR_SEP (Either a '\\' or '/' character) on the end of the given NULL terminated path string.
 *
 * 		WARNING: This function will DEALLOCATE the original string if it finds a character to remove. As such,
 * 		if this call returns COMMON_ERROR_SUCCESS, any pointer to the original string will be INVALID. The
 * 		result of attempting to dereference such a pointer is undefined.
 *
 * 		Returns COMMON_ERROR_SUCCESS if the removal was successful, or if there was not a character to remove.
 * 		(The character at the end of the string was NOT a '\\' or '/' character.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL, or if the given size is less
 * 		than 3.
 *
 * 		Returns COMMON_ERROR_MEMORY_ERROR if a memory allocation attempt fails.
 *
 * 		Otherwise returns the appropriate error code.
 *
 * 		In case of error, (the return code is NOT COMMON_ERROR_SUCCESS), this function will NOT alter any given
 * 		arguments.
 */
int FileUtills_RemoveTrailingSlash(char ** retStr, size_t * retStrSize)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code for this function. */
		char * tempBuffer = NULL;				/* Temporary buffer to alter the string with. */

		/* Check for invalid arguments. */
		if ((retStr != NULL) && ((*retStr) != NULL) && (retStrSize != NULL) && ((*retStrSize) > 2))
		{
				/* Check and see if the last character in the string is either '/' or '\\'. */
				/* String should be NULL terminated. */
				if (((*retStr)[((*retStrSize) - 2)] == '\\') || ((*retStr)[((*retStrSize) - 2)] == '/'))
				{
						/* OK, allocate a new string. */
						tempBuffer = (char*)malloc(((*retStrSize) - 1));
						if (tempBuffer != NULL)
						{
								/* NULL out the buffer. */
								memset(tempBuffer, '\0', ((*retStrSize) - 1));

								/* Copy the data. */
								memcpy(tempBuffer, retStr, ((*retStrSize) - 2));

								/* Deallocate the original string. */
								free((*retStr));

								/* Copy the new pointer. */
								(*retStr) = tempBuffer;

								/* Copy the new size. */
								(*retStrSize) = ((*retStrSize) - 1);

								/* Done! */
								ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
								/* Could not allocate memory for new string. */
								ret = COMMON_ERROR_MEMORY_ERROR;
						}
				}
				else
				{
						/* There is no DIR_SEP character ('\\' or '/') to remove. */
						ret = COMMON_ERROR_SUCCESS;
				}
		}
		else
		{
				/* We can't remove anything, if we do the return would be empty. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
		}

		/* Exit function. */
		return ret;
}

/*!
 * 		int FileUtills_CheckPathType(const char * path, const size_t pathSize, bool * bIsDosStylePath)
 *
 * 		Checks the given path to see if it matches the DOS / Windows path format.
 * 		(I.e. <Drive Letter>:\<some path> OR <some relative path>\<some other path>).
 *		The assumption being that if a '/' is found then it's a POSIX style path.
 *
 * 		Returns COMMON_ERROR_SUCCESS if the check was performed.
 * 		(Result will be stored in the given bIsDosStylePath argument.)
 *
 * 		Returns COMMON_ERROR_INVALID_ARGUMENT if the given pointers are NULL, or the
 * 		given path size is less than 1.
 *
 * 		Otherwise returns the appropriate error code.
 *
 * 		In case of error, (the return code is NOT COMMON_ERROR_SUCCESS), this function will NOT
 * 		alter any given arguments.
 *
 * 		Under NO circumstance is the given path or pathSize argument altered in any way.
 */
int FileUtills_CheckPathType(const char * path, const size_t pathSize, bool * bIsDosStylePath)
{
		/* Init vars. */
		short ret = COMMON_ERROR_INTERNAL_ERROR;		/* Result of this function. */
		size_t x = 0;									/* Counter used in check loop. */

		/* Check for valid arguments. */
		if ((path != NULL) && (pathSize > 0) && (bIsDosStylePath != NULL))
		{
				/* Check for a DOS style absolute path reference. */
				if ((pathSize > 3) && (path[1] == ':') && (path[2] == '\\')) 
				{
						/* This is DOS style absolute path. */
						(*bIsDosStylePath) = true;
				}
				else
				{
						/* Set bIsDosStylePath. */
						(*bIsDosStylePath) = true;

						/*
						 * 	We are assuming that if a '/' character is found
						 * 	in the path, it is a POSIX style path.
						 *
						 * 	(Probably a dangerous assumption, but there is not
						 * 	much of a way to determine the path type short of
						 * 	determining the OS in use. (And even then it's a
						 * 	problem if the target is different than the host.))
						 *
						 * 	Hopefully the target OS will complain if it gets an
						 * 	invalid path......
						 */
						for (x = 0; ((x < pathSize) && ((*bIsDosStylePath) == true)); x++)
						{
								/* Check for a '/' character. */
								if (path[x] == '/')
								{
										/* OK this is a reserved character on windows, so assume the path is a POSIX style path. */
										(*bIsDosStylePath) = false;
								}
						}
				}

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
				/* Invalid path. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
		}

		/* Return the result. */
		return ret;
}

int FileUtills_Create_MSYS_FILESIZE_Structure(MSYS_FILESIZE_T ** str)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code of this function. */
	struct MSYS_FILESIZE_PRIV * realStr = NULL;	/* Temporary pointer for creation of structure. */

	/* Check for invalid argument. */
	if (str != NULL)
	{
		/* Allocate memory. */
		realStr = (struct MSYS_FILESIZE_PRIV *)malloc(sizeof(struct MSYS_FILESIZE_PRIV));
		if (realStr != NULL)
		{
			/* Blank out the structure. */
			memset(realStr, '\0', sizeof(struct MSYS_FILESIZE_PRIV));

			/* Set the type. */
#ifdef _MSC_VER
			realStr->type = WINDOWS_FILESIZE_TYPE;
#else
			realStr->type = POSIX_FILESIZE_TYPE;
#endif	/* _MSC_VER */

			/* Copy the pointer. */
			(*str) = (struct MSYS_FILESIZE *)realStr;

			/* Done. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for structure. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

void FileUtills_Destroy_MSYS_FILESIZE_Structure(MSYS_FILESIZE_T ** str)
{
	/* Check for invalid argument. */
	if ((str != NULL) && ((*str) != NULL))
	{
		/* Deallocate the structure. */
		free((*str));
		(*str) = NULL;
	}

	/* Exit function. */
	return;
}

int FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(const MSYS_FILESIZE_T * str, long long int * retVal)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result code of this function. */
	const struct MSYS_FILESIZE_PRIV * realStr = NULL;	/* Temporary pointer for dereferencing of structure. */

	/* Check for invalid argument. */
	if ((str != NULL) && (retVal != NULL))
	{
		/* Reinterpret the struct. */
		realStr = (const struct MSYS_FILESIZE_PRIV *)str;

		/* Set retVal. */
		(*retVal) = realStr->length;

		/* Done. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int FileUtills_Set_Length_From_MSYS_FILESIZE_Structure_LLINT(MSYS_FILESIZE_T * str, const long long int * val)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	struct MSYS_FILESIZE_PRIV * realStr = NULL;		/* Temporary pointer for dereferencing of structure. */

	/* Check for invalid argument. */
	if ((str != NULL) && (val != NULL))
	{
		/* Reinterpret the struct. */
		realStr = (struct MSYS_FILESIZE_PRIV *)str;

		/* Set length. */
		realStr->length = (*val);

		/* Done. */
		ret = COMMON_ERROR_SUCCESS;
	}
	else
	{
		/* Invalid argument. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

void FileUtills_Destroy_FileUtills_dirlist_Structure(struct FileUtills_dirlist_T ** dirList)
{
	/* Check for valid args. */
	if ((dirList != NULL) && ((*dirList) != NULL))
	{
		/* Check and see if the member pointer is NULL. */
		if ((*dirList)->pointer != NULL)
		{
			/* Call private object's destructor. */
			FileUtills_Destroy_dirList_PRIV_Object(((*dirList)->pointer));
		}

		/* Destroy our object. */
		free((*dirList));
		(*dirList) = NULL;
	}

	/* Exit function. */
	return;
}

int FileUtills_Get_File_Length_By_Filename(const char * filename, const size_t filenameSize, MSYS_FILESIZE_T * fileLength)
{
		/* Init vars. */
		int retFromC = 0;							/* The result from C calls. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of this function. */
		FILE * fp = NULL;							/* Pointer to the file. */
		MSYS_FILESIZE_T * fileSize = NULL;			/* Returned size from Get_File_Length(). */

		/* Check for invalid arguments. */
		if ((filename != NULL) && (filenameSize > 0) && (fileLength != NULL))
		{
			/* Allocate memory for the size structure. */
			ret = FileUtills_Create_MSYS_FILESIZE_Structure(&fileSize);
			if (ret == COMMON_ERROR_SUCCESS)
			{
				/* Open the file. */
				fp = fopen(filename, "rb");
				if (fp != NULL)
				{
					/* Call correct function. */
					ret = FileUtills_Get_File_Length(fp, fileSize);
					if (ret == COMMON_ERROR_SUCCESS)
					{
						/* Close the file. */
						retFromC = fclose(fp);
						if (retFromC == 0)
						{
							/* Copy the size. */
							(*fileLength).length = (*fileSize).length;

							/* SUCCESS. */
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* Could not close the file. */
							ret = COMMON_ERROR_IO_ERROR;
						}
					}
					else
					{
						/* Close the file. */
						retFromC = fclose(fp);
						if (retFromC != 0)
						{
							/* Could not close the file. */
							ret = COMMON_ERROR_IO_ERROR;
						}
					}
				}
				else
				{
					/* Could not open file. */
					ret = COMMON_ERROR_IO_ERROR;
				}

				/* Deallocate the fileSize structure. */
				Destroy_MSYS_FILESIZE_Structure(&fileSize);
			}
			else
			{
				/* Could not allocate memory for the fileSize structure. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		else
		{
				/* Invalid arguments. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
		}

		/* Exit function. */
		return ret;
}

int FileUtills_Get_File_Length(FILE * fp, MSYS_FILESIZE_T * fileLength)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromC = 0;								/* The result of C calls. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of a call to an engine function. */
	fpos_t * previousLocation = NULL;				/* The location to restore us to at the end of the function. */
	long long int retFromGetPos = 0;				/* Result from the various calls to ftell*(). */

	/* Check for invalid arguments. */
	if ((fp != NULL) && (fileLength != NULL))
	{
		/* Check for errors. */
		retFromC = ferror(fp);
		if (retFromC == 0)
		{
			/* Allocate memory for fpos_t. */
			previousLocation = (fpos_t *)malloc(sizeof(fpos_t));
			if (previousLocation != NULL)
			{
				/* NULL out the previousLocation buffer. */
				memset(previousLocation, '\0', sizeof(fpos_t));

				/* Set previousLocation to a known value. */
				(*previousLocation) = 0;

				/* Get the current position. */
				retFromC = fgetpos(fp, previousLocation);
				if (retFromC == 0)
				{
					/* Go back to the beginining of the file. */
					rewind(fp);

					/* Begin loop to find the end of the file. */
					while ((ferror(fp) == 0) && (feof(fp) == 0))
					{
						/* Get next char. */
						retFromC = fgetc(fp);
					}

					/* OK, now figure out if we hit the end of the file or if we hit an error. */
					retFromC = ferror(fp);
					if (retFromC == 0)		/* No error. */
					{
						/* Check for eof. */
						retFromC = feof(fp);
						if (retFromC != 0)		/* Hit EOF. */
						{
							/* Get the end of file position. */
#ifdef _MSC_VER
							retFromGetPos = _ftelli64(fp);	/* Visual C is special. */
#else
							retFromGetPos = ftello(fp);
#endif	/* _MSC_VER */
							if ((retFromGetPos == -1) || (retFromGetPos < 0))
							{
								/* Check and see if the error is EOVERFLOW. */
								if ((retFromGetPos == -1) && (errno == EOVERFLOW))
								{
									/* This is a memory error, as we can't store the result. */
									ret = COMMON_ERROR_MEMORY_ERROR;
								}
								else
								{
									/* OK, yet another IO_ERROR. */
									ret = COMMON_ERROR_IO_ERROR;
								}
							}
						}
						else
						{
							/* We hit a file stream error. */
							ret = COMMON_ERROR_IO_ERROR;
						}
					}
					else
					{
						/* We hit a file stream error. */
						ret = COMMON_ERROR_IO_ERROR;
					}

					/* Clear the error status, and reset the file position. */
					clearerr(fp);
					retFromC = fsetpos(fp, previousLocation);
					if ((retFromC == 0) && (tempSize->length >= 0))
					{
						/* Copy the length to the given MSYS_FILESIZE structure. */
						retFromCall = FileUtills_Set_Length_From_MSYS_FILESIZE_Structure_LLINT(fileLength, retFromGetPos);
						if (retFromCall == COMMON_ERROR_SUCCESS)
						{
							/* Set success. */
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* Internal engine error. */
							ret = COMMON_ERROR_INTERNAL_ERROR;
							COMMON_LOG_DEBUG("FileUtills_Get_File_Length(): Could not copy file length to management structure.");
						}
					}
					else
					{
						/* File stream error. */
						ret = COMMON_ERROR_IO_ERROR;
					}
				}
				else
				{
					/* Could not get current file position. */
					ret = COMMON_ERROR_IO_ERROR;
				}

				/* Free previousLocation. */
				free(previousLocation);
				previousLocation = NULL;
			}
			else
			{
				/* Could not allocate memory for fpos_t buffer. */
				ret = COMMON_ERROR_MEMORY_ERROR;
			}
		}
		else
		{
			/* File stream has errored out. */
			ret = COMMON_ERROR_IO_ERROR;
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int FileUtills_Read_Bytes_From_File(FILE * IN, const size_t dataLength, char * dataBuf, const size_t dataBufLength, const size_t destStaringOffset, const bool blankDataBuf)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of this function. */
	int retFromC = 0;							/* The result of C calls. */
	size_t x = 0;								/* Counter in for loop. */

	/* Check for invalid arguments. */
	if ((IN != NULL) && (!ferror(IN)) && (!feof(IN)) && (dataBuf != NULL) && (dataBufLength > 0) && (dataLength > 0) && ((destStaringOffset + dataLength) < dataBufLength))
	{
		/* Blank out dataBuf with NULL bytes if needed. */
		if (blankDataBuf)
		{
			memset(dataBuf, '\0', dataBufLength);
		}

		/* Begin data input loop. */
		for (x = 0; ((x < dataLength) && ((destStaringOffset + x) < dataBufLength) && (!ferror(IN)) && (!feof(IN))); x++)
		{
			/* Get the data. */
			retFromC = fgetc(IN);

			/* Check for EOF. */
			if (retFromC == EOF)
			{
				/* Check for actual EOF or error. */
				if ((!(feof(IN))) && (!(ferror(IN))))
				{
					/* The input value is (0xFF) which just so happens to be EOF,
						but it is not an error. So copy the value.
					*/
					dataBuf[x] = retFromC;
				}
			}
			else
			{
				/* Copy data to dataBuf. */
				dataBuf[x] = retFromC;
			}
		}

		/* Check for success. */
		if ((!ferror(IN)) && (x == dataLength))
		{
			/* Data read successfully. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			if (feof(IN))
			{
				/* End of file. */
				ret = COMMON_ERROR_END_OF_DATA;

				/* Log error. */
				COMMON_LOG_DEBUG("DEBUG: FileUtills_Read_Bytes_From_File(): Reached end of file before reading the given amount of data.");
			}
			else
			{
				/* Bad file stream. */
				ret = COMMON_ERROR_IO_ERROR;

				/* Log error. */
				COMMON_LOG_DEBUG("DEBUG: FileUtills_Read_Bytes_From_File(): Input file handle has failed.");
			}
		}
	}
	else
	{
		/* Invalid arguments. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		/* Log error. */
		COMMON_LOG_DEBUG("DEBUG: FileUtills_Read_Bytes_From_File(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
	}

	/* Exit function. */
	return ret;
}

int FileUtills_Write_Data_To_File_From_File(FILE * OUT, const char * filename, const size_t filenameLength, const MSYS_FILESIZE_T * fileStartingOffset, const size_t dataLength)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of this function. */
		int retFromC = 0;							/* The result of C calls. */
		MSYS_FILESIZE_T * inFileLength = NULL;		/* The size of the input file. */
		FILE * IN = NULL;							/* The input file. */
		char * inputBuf = NULL;						/* Memory buffer used for reading in data from a file. NOT on the stack! Bad input can follow! */
		size_t remainingLength = 0;					/* Used to calculate remaining bytes to write in output loop. */
		size_t x = 0;								/* Counter used in I/O loop. */
		size_t y = 0;								/* Counter used in Input Loop and Output Loop. */
		long long int realStartOffset = 0;			/* The position to start writing data into the file at. */

		/* Check for invalid arguments. */
		if ((OUT != NULL) && (ferror(OUT) == 0) && (filename != NULL) && (filenameLength > 0) && (fileStartingOffset != NULL) && (fileStartingOffset->length >= 0) && (dataLength > 0))
		{
			/* Allocate memory for the filesize structures. */
			ret = FileUtills_Create_MSYS_FILESIZE_Structure(&inFileLength);
			if (ret == COMMON_ERROR_SUCCESS)
			{
				/* Open the input file. */
				IN = fopen(filename, "rb");
				if (IN != NULL)
				{
					/* Get the length of the input file. */
					ret = FileUtills_Get_File_Length(IN, inFileLength);

					/* Make sure we got a valid file length and that the length of the file is big enough to store the data we want. */
					if ((ret == COMMON_ERROR_SUCCESS) && (inFileLength->length > 0) && ((((unsigned)(fileStartingOffset->length)) + dataLength) <= ((unsigned)(inFileLength->length))))
					{
						/* Reset ret. */
						ret = COMMON_ERROR_UNKNOWN_ERROR;

						/* Get the starting offset. */
						retFromCall = FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(fileStartingOffset, realStartOffset);
						if (retFromCall == COMMON_ERROR_SUCCESS)
						{
							/* Skip to the starting offset. */
#ifdef _MSC_VER	/* VC is special */
							retFromC = _fseeki64(IN, realStartOffset, SEEK_SET);
#else
							retFromC = fseeko64(IN, realStartOffset, SEEK_SET);
#endif	/* _MSC_VER */
							if (retFromC == 0)
							{
								/* Allocate input buffer. */
								inputBuf = (char*)malloc(IO_BUF_SIZE);
								if (inputBuf != NULL)
								{
									/* Begin I/O loop. */
									for (x = 0; ((x < dataLength) && (!ferror(IN)) && (!feof(IN)) && (!ferror(OUT)));)
									{
										/* Determine if the remaining data to read in is less than the buffer size. */
										remainingLength = (dataLength - x);
										if (remainingLength >= IO_BUF_SIZE)
										{
											/* Set remaining length to the buffer size. */
											remainingLength = IO_BUF_SIZE;
										}

										/* Begin input loop. */
										for (y = 0; ((y < remainingLength) && (!ferror(IN)) && (!feof(IN))); y++)
										{
											/* Read in the remaining data. */
											retFromC = fgetc(IN);
											inputBuf[y] = retFromC;
										}

										/* Check for successful read. */
										if ((!ferror(IN)) && (!feof(IN)))
										{
											/* OK, begin the output loop. */
											for (y = 0; ((y < remainingLength) && (!ferror(OUT))); y++)
											{
												/* Output the current buffer. */
												fputc(inputBuf[y], OUT);
											}

											/* Check for successful output. */
											if (!ferror(OUT))
											{
												/* OK, flush the buffer. */
												retFromC = fflush(OUT);
												if (retFromC == 0)
												{
													/* OK, add the remaining amount to x. */
													x = (x + remainingLength);
												}
												else
												{
													/* Could not flush the buffer. */
													ret = COMMON_ERROR_IO_ERROR;

													/* Log error. */
													COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not flush output buffer data to output file.\n");
												}
											}
											else
											{
												/* Bad output file stream. */
												ret = COMMON_ERROR_IO_ERROR;

												/* Log error. */
												COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not write data to output file.\n");
											}
										}
										else
										{
											/* Bad input file stream. */
											ret = COMMON_ERROR_IO_ERROR;

											/* Log error. */
											COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not read data from input file.\n");
										}
									}

									/* Deallocate the input memory buffer. */
									if (inputBuf != NULL)
									{
										free(inputBuf);
										inputBuf = NULL;
									}

									/* Check for success. */
									if ((ret == COMMON_ERROR_UNKNOWN_ERROR) && (!ferror(IN)) && (!feof(IN)) && (!ferror(OUT)))
									{
										/* Success! */
										ret = COMMON_ERROR_SUCCESS;
									}
									else
									{ 
										/* Check for and log IO errors. */
										if (ret == COMMON_ERROR_IO_ERROR)
										{
											/* Log error. */
											COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): File I/O Error.\n");
										}
									}
								}
								else
								{
									/* Could not allocate memory for input buffer. */
									ret = COMMON_ERROR_MEMORY_ERROR;

									/* Log error. */
									COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not allocate memory for input buffer.\n");
								}
							}
							else
							{
								/* Bad file stream. */
								ret = COMMON_ERROR_IO_ERROR;

								/* Log error. */
								COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not seek to starting offset.\n");
							}
						}
						else
						{
							/* Could not get starting offset. */
							ret = COMMON_ERROR_INTERNAL_ERROR;
							
							/* Log error. */
							COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not get starting offset from management structure.");
						}
					}
					else
					{
						/* Invalid input file. */
						ret = COMMON_ERROR_IO_ERROR;

						/* Log error. */
						COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not get input file length or input file is empty.\n");
					}

					/* Close the input file. */
					retFromC = fclose(IN);
					if ((retFromC != 0) && (ret != COMMON_ERROR_IO_ERROR))
					{
						/* Could not close the input file. */
						ret = COMMON_ERROR_IO_ERROR;

						/* Log error. */
						COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not close input file ( ");
						COMMON_LOG_DEBUG(filename);
						COMMON_LOG_DEBUG(" ).\n");
					}
				}
				else
				{
					/* Could not open input file. */
					ret = COMMON_ERROR_IO_ERROR;

					/* Log error. */
					COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not open input file ( ");
					COMMON_LOG_DEBUG(filename);
					COMMON_LOG_DEBUG(" ).\n");
				}
				
				/* Deallocate inFileLength. */
				FileUtills_Destroy_MSYS_FILESIZE_Structure(&inFileLength);
			}
			else
			{
				/* Could not allocate memory for the inFileLength structure. */
				ret = COMMON_ERROR_MEMORY_ERROR;

				/* Log error. */
				COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Could not allocate memory for MSYS_FILESIZE structure.\n");
			}
		}
		else
		{
			/* Invalid arguments. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			/* Log error. */
			COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_File(): Invalid argument.\n");
		}

		/* Exit function. */
		return ret;
}

int FileUtills_Write_Data_To_File_From_Memory(FILE * OUT, const char * data, const size_t dataLength)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of this function. */
		int retFromC = 0;							/* The result of C calls. */
		size_t x = 0;								/* Counter used in output loop. */

		/* Check for invalid arguments. */
		if ((OUT != NULL) && (!ferror(OUT)) && (data != NULL) && (dataLength > 0))
		{
				/* Begin output loop. */
				for (x = 0; ((x < dataLength) && (!ferror(OUT))); x++)
				{
						/* Write out the data. */
						fputc(data[x], OUT);
				}

				/* Check for good file stream. */
				if (!ferror(OUT))
				{
						/* Flush the buffer. */
						retFromC = fflush(OUT);
						if ((retFromC == 0) && (!ferror(OUT)))
						{
							/* Done! */
							ret = COMMON_ERROR_SUCCESS;
						}
						else
						{
							/* Bad file stream. */
							ret = COMMON_ERROR_IO_ERROR;

							/* Log error. */
							COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_Memory(): Could not flush remaining output file data to disk.\n");
						}
				}
				else
				{
					/* Bad file stream. */
					ret = COMMON_ERROR_IO_ERROR;

					/* Log error. */
					COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_Memory(): Could not write data to file.\n");
				}
		}
		else
		{
			/* Invalid arguments. */
			ret = COMMON_ERROR_INVALID_ARGUMENT;

			/* Log error. */
			COMMON_LOG_DEBUG("DEBUG: FileUtills_Write_Data_To_File_From_Memory(): Invalid argument.\n");
		}

		/* Exit function. */
		return ret;
}

int FileUtills_Get_Last_Path_Component(char ** retStr, size_t * retStrLength, const int getParent)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code of this function. */
	char * cleanedPath = NULL;					/* Path without a trailing PATH_SEP. */
	char * tempSubStr = NULL;					/* Used to create the substr. */
	size_t tempSubStrLength = 0;				/* Size of the tempSubString. */
	size_t cleanedPathLength = 0;				/* Length of the cleanedPath string. */

	/* Check for invalid arguments. */
	if ((retStr != NULL) && ((*retStr) != NULL) && (retStrLength != NULL) && ((*retStrLength) > 0))
	{
		/* Allocate memory for the cleanedPath string. */
		cleanedPathLength = (*retStrLength);
		cleanedPath = (char *)malloc(cleanedPathLength);
		if (cleanedPath != NULL)
		{
			/* NULL out the cleaned path string. */
			memset(cleanedPath, '\0', cleanedPathLength);

			/* Copy the given path to cleanedPath. */
			memcpy(cleanedPath, (*retStr), cleanedPathLength);

			/* Call FileUtills_RemoveTrailingSlash(). (Path had to be copied as this function will reallocate the path if it needs to.) */
			ret = FileUtills_RemoveTrailingSlash(&cleanedPath, &cleanedPathLength);
			if (ret == COMMON_ERROR_SUCCESS)
			{
				/* Call DataProcess_Get_SubString_Using_Delimiter(). */
				ret = DataProcess_Get_SubString_Using_Delimiter(cleanedPath, cleanedPathLength, DIR_SEP_STR,
					/* (Note: DIR_SEP_STR is NULL terminated, so we are subtracting one from the length of the delimiter.) */
					((DIR_SEP_STR[(sizeof(DIR_SEP_STR) - 1)] == '\0') ? (sizeof(DIR_SEP_STR) - 1) : (sizeof(DIR_SEP_STR))),
					/* If getParent is non-zero then we need to return the parent path, otherwise we need to only return the last path component. */
					&tempSubStr, &tempSubStrLength, true, (getParent ? true : false));
				if ((ret == COMMON_ERROR_SUCCESS) && (tempSubStr != NULL) && (tempSubStrLength > 0))
				{
					/* Copy the pointer and length. */
					(*retStr) = tempSubStr;
					(*retStrLength) = tempSubStrLength;

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Change the error code to internal error if it's not range or end of data. */
					if ((ret != COMMON_ERROR_RANGE_ERROR) && (ret != COMMON_ERROR_END_OF_DATA))
					{
						/* Internal error. */
						ret = COMMON_ERROR_INTERNAL_ERROR;
					}

					/* Deallocate the tempSubStr if needed. */
					if (tempSubStr != NULL)
					{
						DataProcess_Deallocate_CString(&tempSubStr);
					}
				}
			}
			else
			{
				/* Call to FileUtills_RemoveTrailingSlash() failed. */
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}

			/* Deallocate the cleanedPath string. */
			free(cleanedPath);
			cleanedPath = NULL;
			cleanedPathLength = 0;
		}
		else
		{
			/* Could not allocate memory for cleanedPath. */
			ret = COMMON_ERROR_MEMORY_ERROR;
		}
	}
	else
	{
		/* Invalid argument(s). */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}

int FileUtills_Get_File_Name_Component(const char * path, const size_t pathLength, char ** retStr, size_t * retStrLength, const int getExtension)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code of this function. */
	char * tempFilename = NULL;					/* Used to create the filename. */
	char * tempSubStr = NULL;					/* Used to create the substr. */
	size_t tempFilenameLength = 0;				/* Size of the tempFilename string. */
	size_t tempSubStrLength = 0;				/* Size of the tempSubString. */

	/* Check for invalid arguments. */
	if ((path != NULL) && (pathLength > 0) && (retStr != NULL) && (retStrLength != NULL))
	{
		/* Call DataProcess_Get_SubString_Using_Delimiter() to get the filename. */
		ret = DataProcess_Get_SubString_Using_Delimiter(path, pathLength, DIR_SEP_STR,
			/* (Note: DIR_SEP_STR is NULL terminated, so we are subtracting one from the length of the delimiter.) */
			((DIR_SEP_STR[(sizeof(DIR_SEP_STR) - 1)] == '\0') ? (sizeof(DIR_SEP_STR) - 1) : (sizeof(DIR_SEP_STR))),
			&tempFilename, &tempFilenameLength, true, false);
		if ((ret == COMMON_ERROR_SUCCESS) && (tempFilename != NULL) && (tempFilenameLength > 0))
		{
			/* Call DataProcess_Get_SubString_Using_Delimiter() to get the file name (if getExtension is zero) / extension. (if getExtension is non-zero) */
			ret = DataProcess_Get_SubString_Using_Delimiter(tempFilename, tempFilenameLength, FILEEXT_SEP_STR,
				/* (Note: FILEEXT_SEP_STR is NULL terminated, so we are subtracting one from the length of the delimiter.) */
				((FILEEXT_SEP_STR[(sizeof(FILEEXT_SEP_STR) - 1)] == '\0') ? (sizeof(FILEEXT_SEP_STR) - 1) : (sizeof(FILEEXT_SEP_STR))),
				&tempSubStr, &tempSubStrLength, true, (getExtension ? false : true));
			if ((ret == COMMON_ERROR_SUCCESS) && (tempSubStr != NULL) && (tempSubStrLength > 0))
			{
				/* Copy the pointer and length. */
				(*retStr) = tempSubStr;
				(*retStrLength) = tempSubStrLength;

				/* Done. */
				ret = COMMON_ERROR_SUCCESS;
			}
			else
			{
				/* Change the error code to internal error if it's not range or end of data. */
				if ((ret != COMMON_ERROR_RANGE_ERROR) && (ret != COMMON_ERROR_END_OF_DATA))
				{
					/* Internal error. */
					ret = COMMON_ERROR_INTERNAL_ERROR;
				}

				/* Deallocate the tempSubStr if needed. */
				if (tempSubStr != NULL)
				{
					DataProcess_Deallocate_CString(&tempSubStr);
				}
			}

			/* Deallocate the temporary filename string. */
			DataProcess_Deallocate_CString(&tempFilename);
		}
		else
		{
			/* Check for a path without a directory component. */
			if (ret == COMMON_ERROR_RANGE_ERROR)
			{
				/* There is not a directory component in this path, so just check for the file name (if getExtension is zero) / extension. (if getExtension is non-zero) */
				ret = DataProcess_Get_SubString_Using_Delimiter(path, pathLength, FILEEXT_SEP_STR,
					/* (Note: FILEEXT_SEP_STR is NULL terminated, so we are subtracting one from the length of the delimiter.) */
					((FILEEXT_SEP_STR[(sizeof(FILEEXT_SEP_STR) - 1)] == '\0') ? (sizeof(FILEEXT_SEP_STR) - 1) : (sizeof(FILEEXT_SEP_STR))),
					&tempSubStr, &tempSubStrLength, true, (getExtension ? false : true));
				if ((ret == COMMON_ERROR_SUCCESS) && (tempSubStr != NULL) && (tempSubStrLength > 0))
				{
					/* Copy the pointer and length. */
					(*retStr) = tempSubStr;
					(*retStrLength) = tempSubStrLength;

					/* Done. */
					ret = COMMON_ERROR_SUCCESS;
				}
				else
				{
					/* Change the error code to internal error if it's not range or end of data. */
					if ((ret != COMMON_ERROR_RANGE_ERROR) && (ret != COMMON_ERROR_END_OF_DATA))
					{
						/* Internal error. */
						ret = COMMON_ERROR_INTERNAL_ERROR;
					}

					/* Deallocate the tempSubStr if needed. */
					if (tempSubStr != NULL)
					{
						DataProcess_Deallocate_CString(&tempSubStr);
					}
				}
			}
			else
			{
				/* Change the error code to internal error if it's not a range error. */
				ret = COMMON_ERROR_INTERNAL_ERROR;
			}

			/* Deallocate the tempFilename if needed. */
			if (tempFilename != NULL)
			{
				DataProcess_Deallocate_CString(&tempFilename);
			}
		}
	}
	else
	{
		/* Invalid argument(s). */
		ret = COMMON_ERROR_INVALID_ARGUMENT;
	}

	/* Exit function. */
	return ret;
}
