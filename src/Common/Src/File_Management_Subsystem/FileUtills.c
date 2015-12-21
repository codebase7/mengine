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

void FileUtills_Deallocate_CString(char ** str)
{
	/* Check for valid args. */
	if ((str != NULL) && ((*str) != NULL))
	{
		/* Deallocate the string. */
		DataProcess_Deallocate_CString(str);
	}

	/* Exit function. */
	return;
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

void FileUtills_Destroy_FileUtills_dirlist_Structure(FileUtills_dirlist_T ** dirList)
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
		int retFromC = 0;								/* The result from C calls. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		long long int tempSize = 0;						/* The size of the file returned from FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(). */
		FILE * fp = NULL;								/* Pointer to the file. */
		MSYS_FILESIZE_T * fileSize = NULL;				/* Returned size from Get_File_Length(). */

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
							/* Get the size. */
							retFromCall = FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(fileSize, &tempSize);
							if (retFromCall == COMMON_ERROR_SUCCESS)
							{
								/* Set the size. */
								retFromCall = FileUtills_Set_Length_From_MSYS_FILESIZE_Structure_LLINT(fileSize, &tempSize);
								if (retFromCall == COMMON_ERROR_SUCCESS)
								{
									/* SUCCESS. */
									ret = COMMON_ERROR_SUCCESS;
								}
								else
								{
									/* Could not set size in structure. */
									ret = COMMON_ERROR_INTERNAL_ERROR;
									COMMON_LOG_DEBUG("FileUtills_Get_File_Length_By_Filename(): Could not set size in structure.");
								}
							}
							else
							{
								/* Could not get size from structure. */
								ret = COMMON_ERROR_INTERNAL_ERROR;
								COMMON_LOG_DEBUG("FileUtills_Get_File_Length_By_Filename(): Could not get size from structure.");
							}
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
				FileUtills_Destroy_MSYS_FILESIZE_Structure(&fileSize);
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
/* _ftelli64() in MSC does not return an EOVERFLOW errno status.
	Actually, it has no way to indicate (as of 19/12/2015 anyway...)
	that the file size is too big to store in the return variable.

	This will probably change one day, so if if / when it does,
	just add the detection code here and return COMMON_ERROR_MEMORY_ERROR.
*/
#ifndef _MSC_VER
								/* Check and see if the error is EOVERFLOW. */
								if ((retFromGetPos == -1) && (errno == EOVERFLOW))
								{
									/* This is a memory error, as we can't store the result. */
									ret = COMMON_ERROR_MEMORY_ERROR;
								}
								else
								{
#endif	/* _MSC_VER */
									/* OK, yet another IO_ERROR. */
									ret = COMMON_ERROR_IO_ERROR;
#ifndef _MSC_VER
								}
#endif	/* _MSC_VER */
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
					if ((retFromC == 0) && (retFromGetPos >= 0))
					{
						/* Copy the length to the given MSYS_FILESIZE structure. */
						retFromCall = FileUtills_Set_Length_From_MSYS_FILESIZE_Structure_LLINT(fileLength, &retFromGetPos);
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
/* Define IO_BUF_SIZE for this function if needed. */
#ifndef IO_BUF_SIZE
#define IO_BUF_SIZE 512
#define IO_BUF_SIZE_UNDEF 1	/* Used to undef this later if needed. */
#endif	/* IO_BUF_SIZE */

		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
		int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
		int retFromC = 0;								/* The result of C calls. */
		MSYS_FILESIZE_T * inFileLength = NULL;			/* The size of the input file. */
		FILE * IN = NULL;								/* The input file. */
		char * inputBuf = NULL;							/* Memory buffer used for reading in data from a file. NOT on the stack! Bad input can follow! */
		size_t remainingLength = 0;						/* Used to calculate remaining bytes to write in output loop. */
		size_t x = 0;									/* Counter used in I/O loop. */
		size_t y = 0;									/* Counter used in Input Loop and Output Loop. */
		long long int realStartOffset = 0;				/* The position to start writing data into the file at. */
		long long int realFileLengthlli = 0;			/* The length of the input file as a lli. */

		/* Check for invalid arguments. */
		if ((OUT != NULL) && (ferror(OUT) == 0) && (filename != NULL) && (filenameLength > 0) && (fileStartingOffset != NULL) && (dataLength > 0))
		{
			/* Check for valid file starting offset. */
			retFromCall = FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(fileStartingOffset, &realStartOffset);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (realStartOffset > 0))
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
						if ((ret == COMMON_ERROR_SUCCESS) && (inFileLength != NULL))
						{
							/* Get the length of the file. */
							retFromCall = FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT(inFileLength, &realFileLengthlli);
							if ((retFromCall == COMMON_ERROR_SUCCESS) && (realFileLengthlli > 0) &&
								((((unsigned)(realStartOffset)) + dataLength) <= ((unsigned)(realFileLengthlli))))
							{
								/* Reset ret. */
								ret = COMMON_ERROR_UNKNOWN_ERROR;

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
							/* Could not get length of the file. */
							if (retFromCall != COMMON_ERROR_SUCCESS)
							{
								/* FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT() Call errored out. */
								ret = retFromCall;
							}
							else
							{
								ret = COMMON_ERROR_INTERNAL_ERROR;
								COMMON_LOG_DEBUG("FileUtills_Write_Data_To_File_From_File(): Could not get length of file. FileUtills_Get_Length_From_MSYS_FILESIZE_Structure_LLINT() returned success without result.");
							}
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
				/* Either we have an invalid file starting offset or we could not get it from the file. */
				ret = ((retFromCall != COMMON_ERROR_SUCCESS) ? (COMMON_ERROR_INTERNAL_ERROR) : (COMMON_ERROR_INVALID_ARGUMENT));
				COMMON_LOG_DEBUG(((retFromCall != COMMON_ERROR_SUCCESS) ?
									("FileUtills_Write_Data_To_File_From_File(): Could not get starting offset from management structure.") :
									("FileUtills_Write_Data_To_File_From_File(): Invalid file starting offset.")));
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

/* Undef IO_BUF_SIZE if we defined it. */
#ifdef IO_BUF_SIZE_UNDEF
#undef IO_BUF_SIZE
#undef IO_BUF_SIZE_UNDEF
#endif	/* IO_BUF_SIZE_UNDEF */
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

int FileUtills_GetUserProfileDirectoryPath(char ** retStr, size_t * retStrSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of an engine call. */
	char * outputStr = NULL;						/* Pointer used to reallocate the string with our own allocator. */
	char * tempStr = NULL;							/* Temporary pointer used to get the path from the host. */
	size_t tempStrLength = 0;						/* Length of the temp string. */

	/* Call the syscall. */
	retFromCall = FileUtills_GetUserProfileDirectoryPath_Syscall(&tempStr, &tempStrLength);
	if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempStr != NULL) && (tempStrLength > 0))
	{
		/* Allocate memory so we can reallocate the string with our own allocator. */
		retFromCall = DataProcess_Reallocate_C_String(&outputStr, 0, tempStrLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputStr != NULL))
		{
			/* Copy the data. */
			memcpy(outputStr, tempStr, tempStrLength);

			/* Copy the pointer and length. */
			(*retStr) = outputStr;
			(*retStrSize) = tempStrLength;

			/* Success. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for output string. */
			ret = COMMON_ERROR_MEMORY_ERROR;
			COMMON_LOG_DEBUG("FileUtills_GetUserProfileDirectoryPath(): Could not allocate memory for output string.");
		}
	}
	else
	{
		/* Set internal error. (Unless it was a permissions error.) */
		ret = ((retFromCall != COMMON_ERROR_ACCESS_DENIED) ? (COMMON_ERROR_INTERNAL_ERROR) : (COMMON_ERROR_ACCESS_DENIED));

		/* Check for a INVALID_ARGUMENT. */
		if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
		{
			/* Log this error. */
			COMMON_LOG_WARNING("FileUtills_GetUserProfileDirectoryPath(): Syscall returned an invalid argument error. Please report this bug.\n");
		}
		else
		{
			/* Log the error. */
			COMMON_LOG_DEBUG("FileUtills_GetUserProfileDirectoryPath(): ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
			COMMON_LOG_DEBUG("\n");
		}
	}

	/* Check for allocated strings. */
	if (tempStr != NULL)
	{
		/* Call Syscall deallocator. */
		FileUtills_Deallocate_CString_Syscall(&tempStr);
	}
	if ((ret != COMMON_ERROR_SUCCESS) && (outputStr != NULL))
	{
		/* Call our deallocator. */
		DataProcess_Deallocate_CString(&outputStr);
	}

	/* Return the result. */
	return ret;
}

int FileUtills_GetCurrentWorkingDirectoryPath(char ** retStr, size_t * retStrSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of an engine call. */
	char * outputStr = NULL;						/* Pointer used to reallocate the string with our own allocator. */
	char * tempStr = NULL;							/* Temporary pointer used to get the path from the host. */
	size_t tempStrLength = 0;						/* Length of the temp string. */

	/* Call the syscall. */
	retFromCall = FileUtills_GetCurrentWorkingDirectoryPath_Syscall(&tempStr, &tempStrLength);
	if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempStr != NULL) && (tempStrLength > 0))
	{
		/* Allocate memory so we can reallocate the string with our own allocator. */
		retFromCall = DataProcess_Reallocate_C_String(&outputStr, 0, tempStrLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputStr != NULL))
		{
			/* Copy the data. */
			memcpy(outputStr, tempStr, tempStrLength);

			/* Copy the pointer and length. */
			(*retStr) = outputStr;
			(*retStrSize) = tempStrLength;

			/* Success. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for output string. */
			ret = COMMON_ERROR_MEMORY_ERROR;
			COMMON_LOG_DEBUG("FileUtills_GetCurrentWorkingDirectoryPath(): Could not allocate memory for output string.");
		}
	}
	else
	{
		/* Set internal error. (Unless it was a permissions error.) */
		ret = ((retFromCall != COMMON_ERROR_ACCESS_DENIED) ? (COMMON_ERROR_INTERNAL_ERROR) : (COMMON_ERROR_ACCESS_DENIED));

		/* Check for a INVALID_ARGUMENT. */
		if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
		{
			/* Log this error. */
			COMMON_LOG_WARNING("FileUtills_GetCurrentWorkingDirectoryPath(): Syscall returned an invalid argument error. Please report this bug.\n");
		}
		else
		{
			/* Log the error. */
			COMMON_LOG_DEBUG("FileUtills_GetCurrentWorkingDirectoryPath(): ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
			COMMON_LOG_DEBUG("\n");
		}
	}

	/* Check for allocated strings. */
	if (tempStr != NULL)
	{
		/* Call Syscall deallocator. */
		FileUtills_Deallocate_CString_Syscall(&tempStr);
	}
	if ((ret != COMMON_ERROR_SUCCESS) && (outputStr != NULL))
	{
		/* Call our deallocator. */
		DataProcess_Deallocate_CString(&outputStr);
	}

	/* Return the result. */
	return ret;
}

int FileUtills_GetExecDirectory(char ** retStr, size_t * retStrSize)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result code of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result code of an engine call. */
	char * outputStr = NULL;						/* Pointer used to reallocate the string with our own allocator. */
	char * tempStr = NULL;							/* Temporary pointer used to get the path from the host. */
	size_t tempStrLength = 0;						/* Length of the temp string. */

	/* Call the syscall. */
	retFromCall = FileUtills_GetExecDirectory_Syscall(&tempStr, &tempStrLength);
	if ((retFromCall == COMMON_ERROR_SUCCESS) && (tempStr != NULL) && (tempStrLength > 0))
	{
		/* Allocate memory so we can reallocate the string with our own allocator. */
		retFromCall = DataProcess_Reallocate_C_String(&outputStr, 0, tempStrLength);
		if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputStr != NULL))
		{
			/* Copy the data. */
			memcpy(outputStr, tempStr, tempStrLength);

			/* Copy the pointer and length. */
			(*retStr) = outputStr;
			(*retStrSize) = tempStrLength;

			/* Success. */
			ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
			/* Could not allocate memory for output string. */
			ret = COMMON_ERROR_MEMORY_ERROR;
			COMMON_LOG_DEBUG("FileUtills_GetExecDirectory(): Could not allocate memory for output string.");
		}
	}
	else
	{
		/* Set internal error. (Unless it was a permissions error.) */
		ret = ((retFromCall != COMMON_ERROR_ACCESS_DENIED) ? (COMMON_ERROR_INTERNAL_ERROR) : (COMMON_ERROR_ACCESS_DENIED));

		/* Check for a INVALID_ARGUMENT. */
		if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
		{
			/* Log this error. */
			COMMON_LOG_WARNING("FileUtills_GetExecDirectory(): Syscall returned an invalid argument error. Please report this bug.\n");
		}
		else
		{
			/* Log the error. */
			COMMON_LOG_DEBUG("FileUtills_GetExecDirectory(): ");
			COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
			COMMON_LOG_DEBUG("\n");
		}
	}

	/* Check for allocated strings. */
	if (tempStr != NULL)
	{
		/* Call Syscall deallocator. */
		FileUtills_Deallocate_CString_Syscall(&tempStr);
	}
	if ((ret != COMMON_ERROR_SUCCESS) && (outputStr != NULL))
	{
		/* Call our deallocator. */
		DataProcess_Deallocate_CString(&outputStr);
	}

	/* Return the result. */
	return ret;
}

int FileUtills_ResolvePath(const char * path, const size_t pathSize, char ** retStr, size_t * retStrSize, const bool disableSymLinkResolution)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;			/* The result of this function. */
	int retFromCall = COMMON_ERROR_UNKNOWN_ERROR;	/* The result of calls to other engine functions. */
	size_t numOfResolveAttempts = 0;				/* The number of times we have attempted to resolve a symbolic link. */
	size_t outputStrSize = 0;						/* The current size of the output string. */
	size_t tempLinkBufSize = 0;						/* The current size of the tempLinkBuf. */
	size_t x = 0;									/* Loop counter. */
	char * outputStr = NULL;						/* The resolved path. */
	char * tempLinkBuf = NULL;						/* Used to hold the result of FileUtills_ResolveSystemSymoblicLink_Syscall(). */

	/* Check for valid path. */
	if ((path != NULL) && (pathSize > 0) && (retStr != NULL) && (retStrSize != NULL))
	{
			/* Allocate buffer for outputStr. */
			retFromCall = DataProcess_Reallocate_C_String(&outputStr, 0, pathSize);
			if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputStr != NULL))
			{
				/* Copy path to outputStr. */
				for (outputStrSize = 0; ((ret == COMMON_ERROR_UNKNOWN_ERROR) && (outputStrSize < pathSize)); outputStrSize++)
				{
					/* Check for a NULL that's before the end of the buffer. */
					if ((path[outputStrSize] == '\0') && ((outputStrSize + 1) != pathSize))
					{
						/* Invalid path string. (NULL should be at the end of the buffer.) */
						ret = COMMON_ERROR_INVALID_ARGUMENT;
						COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
						COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
						COMMON_LOG_DEBUG(" given path argument has a NULL character before the end of the buffer.");
					}
					else
					{
						/* Copy the data. */
						outputStr[outputStrSize] = path[outputStrSize];
					}
				}

				/* Check for success. */
				if ((pathSize == outputStrSize) && (ret == COMMON_ERROR_UNKNOWN_ERROR))
				{
					/* Begin resolution loop. */
					for (numOfResolveAttempts = 0; ((retFromCall == FILEUTILLS_ERROR_PATH_IS_A_SYMLINK) && (numOfResolveAttempts < (FileUtills_Get_Max_Symlink_Depth()))); numOfResolveAttempts++)
					{
						/* Resolve the given path. */
						retFromCall = FileUtills_ResolvePath_Helper(&outputStr, &outputStrSize);

						/* Check for error. */
						if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputStr != NULL) && (outputStrSize > 0))
						{
							/* Check for valid result. */
							if ((outputStr != NULL) && (outputStrSize > 0))
							{
								/* Check to see if the path is a symbolic link. */
								retFromCall = FileUtills_IsFileOrDirectory_Helper(outputStr, outputStrSize);

								/* Check the result. */
								switch (retFromCall)
								{
									case COMMON_ERROR_SUCCESS:		/* System specific (unchecked) filesystem entry type. */
									case FILEUTILLS_ERROR_PATH_IS_A_DIRECTORY:
									case FILEUTILLS_ERROR_PATH_IS_A_FILE:
										/* Success. */
										ret = COMMON_ERROR_SUCCESS;
										break;
									case FILEUTILLS_ERROR_PATH_IS_A_SYMLINK:
										/* Check and see if we are resolving symbolic links. */
										if (!disableSymLinkResolution)
										{
											/* OK, Resolve the symbolic link. */
											retFromCall = FileUtills_ResolveSystemSymoblicLink_Syscall(outputStr, outputStrSize, &tempLinkBuf, &tempLinkBufSize);
											if (retFromCall == COMMON_ERROR_SUCCESS)
											{
												/* Check for success without result. */
												if ((tempLinkBuf != NULL) && (tempLinkBufSize > 0))
												{
													/* OK, we need to determine if the resolved symbolic link is a relative path or an absolute path. */
													retFromCall = FileUtills_IsAbsolutePathReference(tempLinkBuf, tempLinkBufSize);

													/* Check for absolute path result. */
													if (retFromCall == FILEUTILLS_ERROR_PATH_IS_ABSOLUTE)
													{
														/* Replace the result with the absolute path. */
														free(outputStr);
														outputStr = tempLinkBuf;
														outputStrSize = tempLinkBufSize;
													}
													else
													{
														/* Check for relative path. */
														if (retFromCall == FILEUTILLS_ERROR_PATH_IS_RELATIVE)
														{
															/* Remove the symlink from the outputStr. */
															retFromCall = FileUtills_RemoveLastPathSegment(&outputStr, &outputStrSize);
															if (retFromCall == COMMON_ERROR_SUCCESS)
															{
																/* Reallocate the buffer to store the relative path. */
																retFromCall = DataProcess_Reallocate_C_String(&outputStr, outputStrSize, (outputStrSize + tempLinkBufSize));
																if ((retFromCall == COMMON_ERROR_SUCCESS) && (outputStr != NULL))
																{
																	/* Reset retFromCall. */
																	retFromCall = COMMON_ERROR_UNKNOWN_ERROR;

																	/* Append the relative path to the result. */
																	for (x = outputStrSize; ((x < (outputStrSize + tempLinkBufSize)) && (ret == COMMON_ERROR_UNKNOWN_ERROR)); x++)
																	{
																		/* Check for NULL. */
																		if ((tempLinkBuf[x] == '\0') && ((x + 1) != (outputStrSize + tempLinkBufSize)))
																		{
																			/* Alright, the tempLinkBuf should NOT have a NULL character in the middle of the buffer. */
																			ret = COMMON_ERROR_INTERNAL_ERROR;
																			COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																			COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
																			COMMON_LOG_DEBUG(" invalid NULL character found in the middle of a resolved symbolic link's buffer.");
																		}
																		else
																		{
																			/* Copy the data. */
																			outputStr[x] = tempLinkBuf[x];
																		}
																	}
																}
																else
																{
																	/* An error occured while reallocating the buffer. */
																	if (retFromCall == COMMON_ERROR_MEMORY_ERROR)
																	{
																		/* Unable to allocate memory for buffer reallocation. */
																		ret = COMMON_ERROR_MEMORY_ERROR;
																		COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_MEMORY_ERROR));
																		COMMON_LOG_DEBUG(" out of usable memory. Cannot reallocate buffer for addition of relative path.");
																	}
																	else
																	{
																		/* All other errors. */
																		ret = COMMON_ERROR_INTERNAL_ERROR;
																		COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																		COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
																		COMMON_LOG_DEBUG(" unable to reallocate output buffer for addition of relative path. Please report this bug.");
																	}
																}
															}
															else
															{
																/* Unable to remove the last path segment. */
																ret = COMMON_ERROR_INTERNAL_ERROR;
																COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
																COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
																COMMON_LOG_DEBUG(" Call to path segment removal function failed. Please report this bug.");
															}
														}
														else
														{
															/* This is any other error. */
															ret = COMMON_ERROR_INTERNAL_ERROR;
															COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
															COMMON_LOG_DEBUG(Common_Get_Error_Message(retFromCall));
															COMMON_LOG_DEBUG(" Unable to resolve the given path ( ");
															COMMON_LOG_DEBUG(path);
															COMMON_LOG_DEBUG(" ) Unable to determine the type of the symbolic link.");
														}
													}
												}
												else
												{
													/* Success without result. */
													ret = COMMON_ERROR_INTERNAL_ERROR;

													/* Log the error. */
													COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
													COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
													COMMON_LOG_WARNING(" Call to system symbolic link resolution function indicated success but did not give a result. Please report this bug.");
												}
											}
											else
											{
												/* OK an error occured report and log it. */
												if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
												{
													/* This is an internal engine error. */
													ret = COMMON_ERROR_INTERNAL_ERROR;
													COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
													COMMON_LOG_WARNING(Common_Get_Error_Message(retFromCall));
													COMMON_LOG_WARNING(" Call to system symbolic link resolution function failed with the given path ( ");
													COMMON_LOG_WARNING(outputStr);
													COMMON_LOG_WARNING(" ) Please report this bug.");
												}
												else
												{
													/* This is any other error. */
													ret = COMMON_ERROR_INTERNAL_ERROR;
													COMMON_LOG_DEBUG("FileUtills_ResolvePath(): Unable to resolve the given path ( ");
													COMMON_LOG_DEBUG(outputStr);
													COMMON_LOG_DEBUG(" ) Unable to resolve system defined symbolic link.");
												}
											}
										}
										break;
									default:
										/* OK an error occured report and log it. */
										if (retFromCall == COMMON_ERROR_INVALID_ARGUMENT)
										{
											/* This is an internal engine error. */
											ret = COMMON_ERROR_INTERNAL_ERROR;
											COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
											COMMON_LOG_WARNING(Common_Get_Error_Message(retFromCall));
											COMMON_LOG_WARNING(" Call to FileUtills_IsFileOrDirectory() failed with the given path ( ");
											COMMON_LOG_WARNING(path);
											COMMON_LOG_WARNING(" ) Please report this bug.\n");
										}
										else
										{
											/* This is any other error. */
											ret = COMMON_ERROR_INTERNAL_ERROR;
											COMMON_LOG_DEBUG("FileUtills_ResolvePath(): Unable to resolve the given path ( ");
											COMMON_LOG_DEBUG(path);
											COMMON_LOG_DEBUG(" ) Unable to determine final path type.\n");
										}
										break;
								};
							}
							else
							{
								/* Success without result. */
								ret = COMMON_ERROR_INTERNAL_ERROR;

								/* Log the error. */
								COMMON_LOG_WARNING("FileUtills_ResolvePath(): ");
								COMMON_LOG_WARNING(Common_Get_Error_Message(COMMON_ERROR_INTERNAL_ERROR));
								COMMON_LOG_WARNING(" Call to helper function indicated success but did not give a result. Please report this bug.\n");
							}
						}
					}

					/* Check and see if the loop exited because we hit the resolution attempt limit. */
					if (numOfResolveAttempts >= FileUtills_Get_Max_Symlink_Depth())
					{
						/* Resolve attempt limit reached. */
						ret = FILEUTILLS_ERROR_SYMLINK_CHAIN_TOO_DEEP;

						/* Log the error. */
						COMMON_LOG_INFO("FileUtills_ResolvePath(): Unable to resolve the given path ( ");
						COMMON_LOG_INFO(path);
						COMMON_LOG_INFO(" ) ");
						COMMON_LOG_INFO(Common_Get_Error_Message(FILEUTILLS_ERROR_SYMLINK_CHAIN_TOO_DEEP));
						COMMON_LOG_INFO("\n");
					}
					else
					{
						/* Check and see if output str is valid and we have a success code. */
						if ((ret == COMMON_ERROR_SUCCESS) && (outputStr != NULL) && (outputStrSize > 0))
						{
							/* Copy output str. */
							(*retStr) = outputStr;
							(*retStrSize) = outputStrSize;
						}
					}
				}
			}
	}
	else
	{
		/* Given path is invalid. */
		ret = COMMON_ERROR_INVALID_ARGUMENT;

		/* Log the error. */
		COMMON_LOG_DEBUG("FileUtills_ResolvePath(): ");
		COMMON_LOG_DEBUG(Common_Get_Error_Message(COMMON_ERROR_INVALID_ARGUMENT));
		COMMON_LOG_DEBUG(" Given path is invalid.\n");
	}

	/* If we do not have success, we need to deallocate the outputStr buffer. */
	if (ret != COMMON_ERROR_SUCCESS)
	{
		if (outputStr != NULL)
		{
			DataProcess_Deallocate_CString(&outputStr);
		}
	}

	/* Return the result. */
	return ret;
}
