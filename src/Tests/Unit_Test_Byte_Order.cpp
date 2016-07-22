/*!
    Multiverse Engine Project 11/7/2015 Unit Tests Unit_Test_Byte_Order.cpp
    
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
#include "Unit_Tests.h"

/* Check for GCC. */
#ifdef __GNUC__ 
#include <limits.h>	/* Defines CHAR_MIN and UCHAR_MAX. */
#endif /* End of __GNUC__ */

void Print_Random_Bits(const char bits)
{
	/* Init vars. */
	int retFromFunct = COMMON_ERROR_UNKNOWN_ERROR;	/* Result code from engine function. */
	char * bitMaskString = NULL;					/* The bitmask represented as a human-readable string. */
	size_t bitMaskStringLength = 0;					/* The length of the bit mask string. */
	
	/* Print the bits. */
	retFromFunct = Common_Print_Bytes_In_Binary(&bits, 1, &bitMaskString, &bitMaskStringLength, 1);
	if (retFromFunct == COMMON_ERROR_SUCCESS)
	{
		/* Print the string. */
		std::cout << bitMaskString << " ";

		/* Deallocate the string. */
		Common_Deallocate_Print_Bytes_CString(&bitMaskString);
	}
	else
	{
		std::cout << "< ERROR: Unable to print random bits, Common_Print_Bytes_In_Binary() failed. > ";
	}
	std::cout.flush();
	
	/* Exit function. */
	return;
}

void Print_Bits_and_BitMask(const char byteToCheck, const char bitMask, const char bitValues)
{
	/* Print the values. */
	std::cout << "DEBUG: BYTE:\t\t";
	Print_Random_Bits(byteToCheck);
	std::cout << "\nDEBUG: BITMASK:\t\t";
	Print_Random_Bits(bitMask);
	std::cout << "\nDEBUG: BIT_VALUES:\t";
	Print_Random_Bits(bitValues);
	std::cout << '\n';
	std::cout.flush();

	/* Exit function. */
	return;
}

char Generate_Random_Non_Conforming_Bit_Mask(const char byte1, const char byte2)
{
	/* Init vars. */
	char ret = '\0';				/* The result of this function. */

	/* Generate a random bit mask to check for. */
	std::cout << "Generating random bit mask. Please Wait.\n";
	std::cout.flush();

	/* Begin generation loop. */
	do
	{
		ret = ((char)DataProcess::Trivial_Random_Number_Generator(0, 255));
	} while ((byte1 | byte2) ^ ret);

	/* Exit function. */
	return ret;
}

char Generate_Random_Bit_Mask(const char bitMask)
{
	/* Init vars. */
	char ret = '\0';				/* The result of this function. */

	/* Generate a random bit mask to check for. */
	std::cout << "Generating random bit mask. Please Wait.\n";
	std::cout.flush();
	do
	{
		/* Generate a bit mask. */
		ret = ((char)DataProcess::Trivial_Random_Number_Generator(1, 254));
	} while (ret == bitMask);
	
	/* Exit function. */
	return ret;
}

char Generate_Random_Bits(const char notThisValue)
{
	/* Init vars. */
	char ret = '\0';				/* The result of this function. */
	
	/* Generate some random bits to check for. */
	std::cout << "Generating random bits. Please Wait.\n";
	std::cout.flush();
	
	/* Generate some bits, avoiding the given value if needed. */
	while (ret == notThisValue)
	{
		ret = ((char)DataProcess::Trivial_Random_Number_Generator(2, 254));
	}
	
	/* Exit function. */
	return ret;
}

int Generate_Matching_Bitmask_Random_Data(char * byteToCheck, char * bitMask, char * bitValues)
{
	/* Init vars. */
	int ret = COMMON_ERROR_UNKNOWN_ERROR;		/* The result code of this function. */

	/* Check for invalid arguments. */
	if ((byteToCheck != NULL) && (bitMask != NULL) && (bitValues != NULL))
	{
		/* Call bitmask generation function. */
		(*bitMask) = Generate_Random_Bit_Mask(0);

		/* Generate the byteToCheck and bitValues data. (If needed, check memory addresses.) */
		if (byteToCheck != bitMask)
		{
			(*byteToCheck) = Generate_Random_Bits((*bitMask));

			/* Bitwise Or the bitMask to the byteToCheck data. */
			(*byteToCheck) |= (*bitMask);
		}
		if ((bitValues != bitMask) && (bitValues != byteToCheck))
		{
			(*bitValues) = Generate_Random_Bits((*byteToCheck));

			/* Bitwise Or the bitMask to the bitValues data. */
			(*bitValues) |= (*bitMask);
		}		

		/* Done. */
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

int unit_test_byte_order_Common_Print_Bytes_In_Binary_check()
{
	/* Init vars. */
	int ret = 0;		/* The result of this function. */
	
	
	
	/* Exit function. */
	return ret;
}

int unit_test_byte_order_comparison_check()
{
	/* Init vars. */
	int ret = 0;									/* The result of this function. */
	char byteToCheck = '\0';						/* The byte to compare against. */
	char bitMask = '\0';							/* The bits we should compare. */
	char bitValues = '\0';							/* The bits we compare to. */
	char extraBits = '\0';							/* Used to generate extra random bits to test with. */
	
	/* Run zero comparison checks. */
	std::cout << "Byte_Order_Bit_Comparison() Test 1: All zero, no bits to check test. (Should result in COMMON_ERROR_COMPARISON_FAILED.): ";
	if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_FAILED)
	{
		/* Test 1 successful. */
		std::cout << "PASS\n";
		std::cout << "Byte_Order_Bit_Comparison() Test 2: All zero, check all bits test. (Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
		bitMask = CHAR_MIN;
		if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
		{
			/* Test 2 successful. */
			std::cout << "PASS\n";

			/* Generate random bit mask. */
			std::cout << "Byte_Order_Bit_Comparison() Test 3: All zero, random bit mask test.\n";
			bitMask = Generate_Random_Bit_Mask(0);
			Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
			std::cout << "(Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
			
			/* Perform all zero test with random bit mask. */
			if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
			{
				/* Test 3 successful. */
				std::cout << "PASS\n";
				
				std::cout << "Byte_Order_Bit_Comparison() Test 4: Non-zero matching bits, no bits to check test. (Should result in COMMON_ERROR_COMPARISON_FAILED.): ";
				/* Begin checks on non-zero bit values. */
				bitMask = 0;
				bitValues = 1;
				byteToCheck = 1;
				if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_FAILED)
				{
					/* Test 4 successful. */
					std::cout << "PASS\n";
					
					std::cout << "Byte_Order_Bit_Comparison() Test 5: Non-zero matching bits, check bits test. (Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
					bitMask = 1;

					if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
					{
						/* Test 5 successful. */
						std::cout << "PASS\n";
						
						std::cout << "Byte_Order_Bit_Comparison() Test 6: Non-zero matching bits, extra bits in byte, check bits test.\n";
						Generate_Matching_Bitmask_Random_Data(&byteToCheck, &bitMask, &bitMask);
						bitValues = bitMask;	/* Only the bits in the bit mask should be set in bitValues. */
						Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
						std::cout << "(Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
						
						/* Perform Non-zero matching bits, extra bits in byte, check bits test. */
						if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
						{
							/* Test 6 successful. */
							std::cout << "PASS\n";
							
							std::cout << "Byte_Order_Bit_Comparison() Test 7: Non-zero matching bits, extra bits in bitValues, check bits test.\n";
							Generate_Matching_Bitmask_Random_Data(&bitMask, &bitMask, &bitValues);
							byteToCheck = bitMask;	/* Only the bits in the bit mask should be set in byteToCheck. */
							Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
							std::cout << "(Should result in COMMON_ERROR_COMPARISON_PASSED.): ";

							/* Perform Non-zero matching bits, extra bits in bitValues, check bits test. */
							if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
							{
								/* Test 7 successful. */
								std::cout << "PASS\n";
								
								std::cout << "Byte_Order_Bit_Comparison() Test 8: Non-zero matching bits, extra bits in byte and bitValues, check bits test.\n";
								Generate_Matching_Bitmask_Random_Data(&byteToCheck, &bitMask, &bitValues);
								Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
								std::cout << "(Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
								
								/* Perform Non-zero matching bits, extra bits in byte and bitValues, check bits test. */
								if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
								{
									/* Test 8 successful. */
									std::cout << "PASS\n";
									
									std::cout << "Byte_Order_Bit_Comparison() Test 9: Non-zero matching bits, extra bits in byte and bitValues, random bitmask check bits test.\n";
									extraBits = Generate_Random_Bits(0);
									
									/* Binary OR the bits together so that the bits we check for will be valid. */
									byteToCheck = 0;
									byteToCheck |= extraBits;
									extraBits = Generate_Random_Bits(0);
									
									/* Binary OR the bits together so that the bits we check for will be valid. */
									bitValues = 0;
									bitValues |= extraBits;
									
									/* Generate random bit mask. */
									bitMask = Generate_Random_Bit_Mask(0);
									
									/* Binary OR the bits together so that the bits we check for will be valid. */
									byteToCheck |= bitMask;
									bitValues |= bitMask;
									
									Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
									std::cout << "(Should result in COMMON_ERROR_COMPARISON_PASSED.): ";

									/* Perform Non-zero matching bits, extra bits in byte and bitValues, random bitmask check bits test. */
									if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
									{
										/* Test 9 successful. */
										std::cout << "PASS\n";
										
										std::cout << "Byte_Order_Bit_Comparison() Test 10: Non-zero NON-matching bits, extra bits in byte and bitValues, random bitmask check bits test.\n";
										extraBits = Generate_Random_Bits(0);
										
										/* Binary OR the bits together so that the bits we check for will be valid. */
										byteToCheck = 0;
										byteToCheck |= extraBits;
										extraBits = Generate_Random_Bits(byteToCheck);
										
										/* Binary OR the bits together so that the bits we check for will be valid. */
										bitValues = 0;
										bitValues |= extraBits;
										
										/* Generate random bit mask. */
										bitMask = Generate_Random_Non_Conforming_Bit_Mask(byteToCheck, bitValues);
										
										Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
										std::cout << "(Should result in COMMON_ERROR_COMPARISON_FAILED.): ";
										
										/* Perform Non-zero NON-matching bits, extra bits in byte and bitValues, random bitmask check bits test. */
										if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_FAILED)
										{
											/* Test 10 successful. */
											std::cout << "PASS\n";
											
											std::cout << "Byte_Order_Bit_Comparison() Test 11: All bits set, check all bits test. (Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
											bitMask = UCHAR_MAX;
											byteToCheck = UCHAR_MAX;
											bitValues = UCHAR_MAX;
											
											/* Perform All bits set, check all bits test. */
											if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
											{
												/* Test 11 successful. */
												std::cout << "PASS\n";
												std::cout << "Byte_Order_Bit_Comparison() Test 12: All bits set, no bits to check test. (Should result in COMMON_ERROR_COMPARISON_FAILED.): ";
												bitMask = 0;
												
												/* Perform All bits set, no bits to check test. */
												if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_FAILED)
												{
													/* Test 12 successful. */
													std::cout << "PASS\n";
													
													std::cout << "Byte_Order_Bit_Comparison() Test 13: All bits set, random bit mask test.\n";
													bitMask = Generate_Random_Bit_Mask(0);
													Print_Bits_and_BitMask(byteToCheck, bitMask, bitValues);
													std::cout << "(Should result in COMMON_ERROR_COMPARISON_PASSED.): ";
													
													/* Perform All bits set, random bit mask test. */
													if (Byte_Order_Bit_Comparison(&byteToCheck, bitMask, bitValues) == COMMON_ERROR_COMPARISON_PASSED)
													{
														/* Test 13 successful. */
														std::cout << "PASS\n";
														
														/* End of tests. */
														ret = 0;
													}
													else
													{
														/* All bits set, random bit mask test failed. */
														ret = -13;
														std::cout << "FAIL\n";
													}
												}
												else
												{
													/* All bits set, no bits to check test failed. */
													ret = -12;
													std::cout << "FAIL\n";
												}
											}
											else
											{
												/* All bits set, check all bits test failed. */
												ret = -11;
												std::cout << "FAIL\n";
											}
										}
										else
										{
											/* Non-zero NON-matching bits, extra bits in byte and bitValues, random bitmask check bits test failed. */
											ret = -10;
											std::cout << "FAIL\n";
										}
									}
									else
									{
										/*  Non-zero matching bits, extra bits in byte and bitValues, random bitmask check bits test failed. */
										ret = -9;
										std::cout << "FAIL\n";
									}
								}
								else
								{
									/* Non-zero matching bits, extra bits in byte and bitValues, check bits test failed. */
									ret = -8;
									std::cout << "FAIL\n";
								}
							}
							else
							{
								/* Non-zero matching bits, extra bits in bitValues, check bits test failed. */
								ret = -7;
								std::cout << "FAIL\n";
							}
						}
						else
						{
							/* Non-zero matching bits, extra bits in byte, check bits test failed. */
							ret = -6;
							std::cout << "FAIL\n";
						}
					}
					else
					{
						/* Non-zero matching bits, check bits test failed. */
						ret = -5;
						std::cout << "FAIL\n";
					}
				}
				else
				{
					/* Non-zero matching bits, no bits to check test failed. */
					ret = -4;
					std::cout << "FAIL\n";
				}
			}
			else
			{
				/* All zero, random bit mask test failed. */
				ret = -3;
				std::cout << "FAIL\n";
			}
		}
		else
		{
			/* All zero, check all bits test failed. */
			ret = -2;
			std::cout << "FAIL\n";
		}
	}
	else
	{
		/* All zero no bits to check test failed. */
		ret = -1;
		std::cout << "FAIL\n";
	}
	
	/* Flush output buffer. */
	std::cout.flush();
	
	/* Exit function. */
	return ret;
}

int Unit_Test_Byte_Order_Main()
{
	/* Init vars. */
	int ret = 0;						/* The result of this function. */
	int result_comparision_check = 0;	/* The result of the comparison checks. */
	
	/* Output START OF TEST SECTION. */
    std::cout << START_TEST_SECTION;
	
	/* Run comparison checks. */
	result_comparision_check = unit_test_byte_order_comparison_check();
	
	/* Output END OF TEST SECTION. */
    std::cout << END_TEST_SECTION;
	
	/* Exit function. */
	return ret;
}
