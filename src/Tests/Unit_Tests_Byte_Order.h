/*!
    Multiverse Engine Project 11/7/2015 Unit Tests Unit_Tests_Byte_Order.h
    
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

/* Include guard. */
#ifndef UNIT_TESTS_BYTE_ORDER_H
#define UNIT_TESTS_BYTE_ORDER_H

/* Internal includes. */
#include "../Common/Src/Byte_Order/Byte_Order.h"

/* Define test functions. */
/*!
 * 		void Print_Random_Bits(const char bits)
 *
 *		Wrapper around Common_Print_Bytes_In_Binary() and 
 * 		Common_Deallocate_Print_Bytes_CString() to print 
 *		the given byte to the standard output.
 *
 *		This function has no return.
 */
void Print_Random_Bits(const char bits);

/*!
 *		char Generate_Random_Bit_Mask(const char bitMask)
 *
 *		Generates some random bits between 1 and 254, retrying if it 
 *		generates the given bitMask, while telling the user
 *		it is doing so.
 *
 *		Returns the generated bit mask.
 */
char Generate_Random_Bit_Mask(const char bitMask);

/*!
 *		char Generate_Random_Bits(const char notThisValue)
 *
 *		Generates some random bits between 2 and 254, retrying if it 
 *		generates the given notThisValue, while telling the user
 *		it is doing so.
 *
 *		Returns the generated bits.
 */
char Generate_Random_Bits(const char notThisValue);

int unit_test_byte_order_Common_Print_Bytes_In_Binary_check();

/*!
 *		int unit_test_byte_order_comparison_check()
 *
 *		Performs tests on the Byte_Order_Bit_Comparison() function.
 */
int unit_test_byte_order_comparison_check();

/*!
 *		int Unit_Test_Byte_Order_Main()
 *
 *		Main test function for Byte_Order.
 */
int Unit_Test_Byte_Order_Main();

#endif	/* UNIT_TESTS_BYTE_ORDER_H */

/* End of Unit_Tests_Byte_Order.h */
