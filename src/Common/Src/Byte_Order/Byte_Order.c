/*!
    Multiverse Engine Project 03/6/2015 Common Byte_Order.c

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
#include "Byte_Order.h"

/* Check for C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

int Common_Byte_Swap(char * data, const size_t dataLength)
{
		/* Init ret. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result of this function. */
		size_t x = 0;								/* Counter used in the swap loop. */
		char tempByte = '\0';						/* Temporary memory storage for a byte being swapped out. */

		/* Check for invalid arguments. */
		if ((data != NULL) && ((dataLength % 2) == 0))
		{
				/* Begin swap loop. */
				for (x = 0; (x < (dataLength / 2)); x++)
				{
						/*
						 *		Each bit is swapped with it's partner on the other side of the array.
						 *		I.e. Each byte from x distance from the start of the array is swapped
						 *		with the byte x distance from the end of the array.
						 */
						 tempByte = data[x];
						 data[x] = data[((dataLength - 1) - x)];
						 data[((dataLength - 1) - x)] = tempByte;
				}

				/* Done! */
				ret = COMMON_ERROR_SUCCESS;
		}
		else
		{
				/* Invalid arguments. */
				ret = COMMON_ERROR_INVALID_ARGUMENT;
		}

		/* Exit function. */
		return ret;
}

int Common_Print_Bytes_To_CString(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const size_t base, const size_t width, const char fillValue, const bool spaceBetweenBytes)
{
		/* Init vars. */
		int ret = COMMON_ERROR_UNKNOWN_ERROR;				/* The result of this function. */
		size_t x = 0;										/* Counter used in the print and spacing loops. */
		size_t byteValueCount = 0;							/* Used to keep track of how many bytes we have outputted for the current byte. */
		unsigned char currentByte = '\0';					/* Temporary value used to store the current byte we are working on. */
		char outputValue = '\0';							/* The value that we need to write into the output buffer. (Calculated from currentValue.) */
		char * outputBuffer = NULL;							/* Pointer to the c-string that will be outputted to the standard output. */
		char * previousOutputBuffer = NULL;					/* Temporary pointer used to copy previously generated data into the current outputBuffer. */
		const char outputValues[17] = "0123456789ABCDEF";	/* C-String used to map a generated value to it's corresponding character. */
		size_t outputBufferSize = 1;						/* Current size of the outputBuffer. Set to one by default to allow the string to be NULL terminated. */

		/* Check for invalid arguments. */
		if ((data != NULL) && (dataLength > 0) && (retStr != NULL) && (retStrSize != NULL) && (base >= 2) && (base <= 16))
		{
				/* Begin data print loop. */
				for (x = 0; ((x < dataLength) && (ret != COMMON_ERROR_MEMORY_ERROR)); x++)
				{
						/* Copy current value. */
						currentByte = data[((dataLength - 1) - x)];

						/* Reset byte value count. */
						byteValueCount = 0;

						/* Begin value parsing loop. */
						do
						{
								/* Read the current byte's value from right to left. (Mod is a reduction operation.) */
								outputValue = (currentByte % base);

								/* Copy the current buffer's pointer because we are about to create a new one. */
								previousOutputBuffer = outputBuffer;

								/* Increment the size of the new buffer. */
								outputBufferSize++;

								/* Allocate the new buffer. */
								outputBuffer = (char*)malloc(outputBufferSize);

								/* Check for successful memory allocation. */
								if (outputBuffer != NULL)
								{
										/* Blank out the new buffer. */
										memset(outputBuffer, '\0', outputBufferSize);

										/* Set the first value as the previous data comes after it. */
										outputBuffer[0] = outputValues[outputValue];

										/* If we have any previous data we need to copy it into the new buffer and deallocate the previous one. */
										if (previousOutputBuffer != NULL)
										{
												memcpy((outputBuffer + 1), previousOutputBuffer, (outputBufferSize - 1));
												free(previousOutputBuffer);
												previousOutputBuffer = NULL;
										}

										/* Increment byte value count. */
										byteValueCount++;

										/* Get the next value by chopping off the "ones place", aka divide by the current base. */
										currentByte /= (unsigned char)base;
								}
								else
								{
										/* Could not allocate memory for output buffer. */
										ret = COMMON_ERROR_MEMORY_ERROR;
								}
						}while ((currentByte) && (ret != COMMON_ERROR_MEMORY_ERROR));

						/* Check and see if the generated values used up all of the requested width. */
						if ((ret != COMMON_ERROR_MEMORY_ERROR) && (outputBuffer != NULL) && (byteValueCount < width))
						{
								/* Copy the current buffer's pointer because we are about to create a new one. */
								previousOutputBuffer = outputBuffer;

								/* Increment the output buffer size by the remaining filler we need to add. */
								outputBufferSize += (width - byteValueCount);

								/* Allocate the new buffer. */
								outputBuffer = (char*)malloc(outputBufferSize);

								/* Check for successful memory allocation. */
								if (outputBuffer != NULL)
								{
										/* Blank out the new buffer. */
										memset(outputBuffer, '\0', outputBufferSize);

										/* Put in our filler. */
										memset(outputBuffer, fillValue, (width - byteValueCount));

										/* If we have any previous data we need to copy it into the new buffer and deallocate the previous one. */
										if (previousOutputBuffer != NULL)
										{
												memcpy((outputBuffer + (width - byteValueCount)), previousOutputBuffer, (outputBufferSize - (width - byteValueCount)));
												free(previousOutputBuffer);
												previousOutputBuffer = NULL;
										}
								}
								else
								{
										/* Could not allocate memory for output buffer. */
										ret = COMMON_ERROR_MEMORY_ERROR;
								}
						}

						/* Insert spacing if needed. */
						if ((spaceBetweenBytes) && (ret != COMMON_ERROR_MEMORY_ERROR) && (outputBuffer != NULL) && ((x + 1) < dataLength))
						{
								/* Copy the current buffer's pointer because we are about to create a new one. */
								previousOutputBuffer = outputBuffer;

								/* Increment the output buffer size. */
								outputBufferSize++;

								/* Allocate the new buffer. */
								outputBuffer = (char*)malloc(outputBufferSize);

								/* Check for successful memory allocation. */
								if (outputBuffer != NULL)
								{
										/* Blank out the new buffer. */
										memset(outputBuffer, '\0', outputBufferSize);

										/* Insert our space. */
										outputBuffer[0] = ' ';

										/* Copy the original buffer. */
										memcpy((outputBuffer + 1), previousOutputBuffer, (outputBufferSize - 1));
								}
								else
								{
										/* Could not allocate memory for output buffer. */
										ret = COMMON_ERROR_MEMORY_ERROR;
								}
						}
				}

				/* Check for NULL output buffer. */
				if ((ret != COMMON_ERROR_MEMORY_ERROR) && (outputBuffer != NULL) && (outputBufferSize > 0))
				{
						/* Copy the outputBuffer pointer to retStr. */
						(*retStr) = outputBuffer;

						/* Copy outputBufferSize to retStrSize. */
						(*retStrSize) = outputBufferSize;

						/* Done! */
						ret = COMMON_ERROR_SUCCESS;
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

void Common_Deallocate_Print_Bytes_CString(char ** str)
{
		/* Check for NULL. */
		if (str != NULL)
		{
				free((*str));
				(*str) = NULL;
		}

		/* Exit function. */
		return;
}

int Common_Print_Bytes_In_Hex(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes)
{
		return Common_Print_Bytes_To_CString(data, dataLength, retStr, retStrSize, 16, 2, '0', spaceBetweenBytes);
}

int Common_Print_Bytes_In_Binary(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes)
{
		return Common_Print_Bytes_To_CString(data, dataLength, retStr, retStrSize, 2, 8, '0', spaceBetweenBytes);
}

int Common_Print_Bytes_In_Decimal(const char * data, const size_t dataLength, char ** retStr, size_t * retStrSize, const bool spaceBetweenBytes)
{
		return Common_Print_Bytes_To_CString(data, dataLength, retStr, retStrSize, 10, 8, '0', spaceBetweenBytes);
}

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* __cplusplus */
