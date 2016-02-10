/*!
    Basic Test for the Common namespace Rendering Subsystem. 25/12/2013

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

// Include guard.
#ifndef RENDER_SUBSYS_UNIT_TESTS
#define RENDER_SUBSYS_UNIT_TESTS

// Include base header from Rendering Subsystem.
#include "../Common/Src/Rendering_Subsystem/Renderer.h"

// Define render data.
#ifndef RENDER_TEXT_CHAR_DOT
#define RENDER_TEXT_CHAR_DOT '.'
#endif

#ifndef RENDER_TEXT_BLANK_VALUE
#define RENDER_TEXT_BLANK_VALUE 'X'
#endif

// Define expected results from the render.
// Basic test result (Resolution: 3x3)
const static char RENDER_TEXT_BASIC_TEST_RESULT[] = {RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE,
						     RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE,
						     RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE};

// Edge test result (Resolution: 3x3) (Basicly an inverted basic test. Checks to see if the edges of a render are kept intact.)
const static char RENDER_TEXT_EDGE_TEST_RESULT[] = {RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT,
						    RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT,
						    RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT};

// Shift right down test result. (Resolution: 3x3) (The edge test result, shifted down and to the right by one.)
const static char RENDER_TEXT_SHIFT_RIGHT_DOWN_TEST_RESULT[] = {RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE,
								RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT,
								RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE};

// Shift right up test result. (Resolution: 3x3) (The edge test result, shifted up and to the right by one.)
const static char RENDER_TEXT_SHIFT_RIGHT_UP_TEST_RESULT[] = {RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE,
							      RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT,
							      RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE};

// Shift left down test result. (Resolution: 3x3) (The edge test result, shifted down and to the left by one.)
const static char RENDER_TEXT_SHIFT_LEFT_DOWN_TEST_RESULT[] = {RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE,
							       RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE,
							       RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE};

// Shift left up test result. (Resolution: 3x3) (The edge test result, shifted up and to the left by one.)
const static char RENDER_TEXT_SHIFT_LEFT_UP_TEST_RESULT[] = {RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE,
							   RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_BLANK_VALUE,
							   RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BLANK_VALUE};

// Fill test result. (Resolution: 3x3) (A basic solid fill pattern, that fills up the entire overlay.)
const static char RENDER_TEXT_BASIC_FILL_TEST_RESULT[] = {RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT,
							  RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT,
							  RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT, RENDER_TEXT_CHAR_DOT};

// Define test functions.
/*!
 * 	bool Renderer_Text_Console_Blit_Text_No_Overlay_Test_Function(const char & blank_value, const char * testArray, const size_t & testArraySize, const size_t & xResolution, const size_t & yResolution,
 * 								      const size_t & colorDepth, const bool & fullscreen)
 *
 * 	A generic version of Renderer_Text_Console_Basic_No_Overlay_Test() that accepts
 * 	any test array, instead of using a hardcoded test.
 *
 * 	Pram: const char & blank_value, the value to use for empty space. (This will appear in the final image, wherever you do not place any data in the overlays / working buffer. It IS checked for in the result.)
 * 	Pram: const char * testArray, a pointer to the array to test. (Array must be one dimentional.)
 * 	Pram: const size_t & testArraySize, the total length of the array.
 * 	Pram: const size_t & xResolution, the horazontal "row" length of the final image.
 * 	Pram: const size_t & yResolution, the vertical "column" length of the final image.
 * 	Pram: const size_t & colorDepth, the color depth of the final image. (Not currently used by the Common::Renderer::Renderer_Text_Console renderer.)
 * 	Pram: const bool & fullscreen, whether or not the given resolution above takes up the entire window / screen. (If false a newline will be output after each row.)
 *
 * 	Returns true if the call to render() is successful. (Or in a debug build, if the rendered image matches the testArray data.)
 * 	Returns false otherwise.
 */
bool Renderer_Text_Console_Blit_Text_No_Overlay_Test_Function(const char & blank_value, const char * testArray, const size_t & testArraySize, const size_t & xResolution, const size_t & yResolution, const size_t & colorDepth,
							      const bool & fullscreen);

/*!
 * 	bool Renderer_Text_Console_Blit_Text_No_Overlay_Transformation_Test_Function(const char & blank_value, const char * testArray, const size_t & testArraySize, const size_t & testXResolution, const size_t & testYResolution,
 * 										     const size_t & testColorDepth, const size_t & testResultXOffset, const size_t & testResultYOffset,
 * 										     const char * resultArray, const size_t & resultArraySize, const size_t & resultXResolution, const size_t & resultYResolution,
 * 										     const size_t & resultColorDepth, const bool & fullscreen)
 *
 * 	A function to test basic transformations on overlays.
 *
 * 	Pram: const char & blank_value, the value to use for empty space. (This will appear in the final image, wherever you do not place any data in the overlays / working buffer. It IS checked for in the result.)
 * 	Pram: const char * testArray, a pointer to the array to test. (Array must be one dimentional.)
 * 	Pram: const size_t & testXResolution, the horazontal "row" length of the testArray.
 * 	Pram: const size_t & testYResolution, the vertical "column" length of the testArray.
 * 	Pram: const size_t & testColorDepth, the color depth of the testArray. (Not currently used by the Common::Renderer::Renderer_Text_Console renderer.)
 * 	Pram: const long & testArrayXOffset, the offset from the origin point on the generated final image where the x origin point of the testArray will be placed.
 * 	Pram: const long & testArrayYOffset, the offset from the origin point on the generated final image where the y origin point of the testArray will be placed.
 * 	Pram: const char * resultArray, a pointer to the array that contains the expected final image. (Array must be one dimentional.)
 * 	Pram: const size_t & resultArraySize, the total length of the resultArray.
 * 	Pram: const size_t & resultXResolution, the horazontal "row" length of the resultArray.
 * 	Pram: const size_t & resultYResolution, the vertical "column" length of the resultArray.
 * 	Pram: const size_t & resultColorDepth, the color depth of the resultArray. (Not currently used by the Common::Renderer::Renderer_Text_Console renderer.)
 * 	Pram: const bool & fullscreen, whether or not the given resolution above takes up the entire window / screen. (If false a newline will be output after each row.)
 *
 * 	Returns true if the call to render() is successful. (Or in a debug build, if the rendered image matches the testArray data.)
 * 	Returns false otherwise.
 */
bool Renderer_Text_Console_Blit_Text_No_Overlay_Transformation_Test_Function(const char & blank_value, const char * testArray, const size_t & testXResolution, const size_t & testYResolution,
									     const size_t & testColorDepth, const long & testArrayXOffset, const long & testArrayYOffset,
									     const char * resultArray, const size_t & resultArraySize, const size_t & resultXResolution, const size_t & resultYResolution,
									     const size_t & resultColorDepth, const bool & fullscreen);

/*!
 * 	bool Renderer_Text_Console_Basic_No_Overlay_Test()
 *
 * 	Performs a basic "does it do anything" test on the
 * 	Renderer_Text_Console class, by trying to create
 * 	a dot at the center of the grid.
 *
 * 	Returns true if the call to render() succeeds.
 * 	Returns false otherwise.
 */
bool Renderer_Text_Console_Basic_No_Overlay_Test();

/*!
 * 	short Unit_Test_Rendering_Subsystem_Main()
 *
 * 	Main test function for the rendering subsystem unit tests.
 * 	Performs all tests.
 *
 * 	Returns zero if all tests succeed.
 * 	Returns a negative number if a test fails.
 */
short Unit_Test_Rendering_Subsystem_Main();

#endif

// End of Unit_Test_Rendering_Subsystem.h
