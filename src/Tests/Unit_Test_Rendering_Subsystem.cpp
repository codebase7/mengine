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

#include "Unit_Tests.h"

bool Renderer_Text_Console_Blit_Text_No_Overlay_Test_Function(const char & blank_value, const char * testArray, const size_t & testArraySize, const size_t & xResolution, const size_t & yResolution, const size_t & colorDepth,
							      const bool & fullscreen)
{
	// Init vars.
	bool result = false;					// The result of this test function.
#ifndef _NDEBUG
	const char * imageBuffer = NULL;			// Only used in a debug build, this holds a pointer to the final image buffer made by the renderer.
	const char * overlayBuffer = NULL;			// Only used in a debug build, this holds a pointer to an overlay image buffer made by the renderer.
#endif
	Common::Renderer::Renderer_Text_Console renderer;	// The renderer class we are testing.

	// Set the blank value.
	renderer.Set_Blank_Value(blank_value);

	// Set the resolution.
	if (renderer.Change_Resolution(xResolution, yResolution, colorDepth, fullscreen))
	{
		// Call Blit_Text().
		if (renderer.Blit_Text(testArray, 0, true, testArraySize, 1))
		{
// Show it.
			std::cout << "Attempting to render the test plane:\n\n";
			if (renderer.Render())
			{
#ifndef _NDEBUG
				// Because the Return_Current_Final_Image_Buffer() function is a debug function, we have to isolate it.
				// Get the pointer.
				imageBuffer = renderer.Return_Current_Final_Image_Buffer();
				if (imageBuffer != NULL)
				{
					// Inform user.
					std::cout << "\n\nChecking result of render: ";
					std::cout.flush();
					if (memcmp(testArray, imageBuffer, testArraySize) == 0)
					{
						// Test successful.
						std::cout << "PASS\n";
						std::cout.flush();
						result = true;
					}
					else
					{
						// Test failure.
						std::cout << "FAIL\n" << "Rendered image does not match expected result, there is a bug in the renderer.\n";
						std::cout << "The result should be:\n" << testArray << "\n";

						// Attempt to get the working buffer pointer.
						overlayBuffer = renderer.Return_Current_Overlay_Image_Buffer();
						if (overlayBuffer != NULL)
						{
							// Output the working buffer data.
							std::cout << "The working buffer data was: " << overlayBuffer << '\n';

							// Check to see if the working buffer is valid.
							if (memcmp(testArray, overlayBuffer, testArraySize) == 0)
							{
								std::cout << "Generated overlay data is correct, bug is located in the Render() function.\n";
								std::cout.flush();
							}
							else
							{
								std::cout << "Generated overlay data is invalid, at least one bug is present in the Blit_Text() function.\n";
								std::cout.flush();
							}
						}
						else
						{
							// Could not retrive pointer to the working buffer data.
							std::cout << "ERROR: Unable to retrive a pointer to the working buffer data.\n";
						}
						std::cout.flush();
						result = false;
					}
				}
				else
				{
					// Error.
					std::cout << "ERROR: Debug pointer to renderer's image buffer is invalid.\n\n";
					result = false;
				}
#else
				// Inform user.
				std::cout << "\n\nRender complete, unable to check result as this is a release build of the Unit_Tests program.\n" << "If this is not the desired result, file a bug.\n";

				// Set result.
				result = true;
#endif
			}
			else
			{
				// Render() failed.
				std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Render() failed.\n";
				std::cout << "Last error from renderer: " << renderer.Get_Last_Error() << "\n\n";
			}
		}
		else
		{
			// Blit_Text() failed.
			std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Blit_Text() failed.\n";
			std::cout << "Last error from class: " << renderer.Get_Last_Error() << "\n\n";
		}
	}
	else
	{
		// Error could not change resolution.
		std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Change_Resolution() failed.\n";
		std::cout << "Last error from class: " << renderer.Get_Last_Error() << "\n\n";
	}

	// Exit function.
	return result;
}

bool Renderer_Text_Console_Blit_Text_No_Overlay_Transformation_Test_Function(const char & blank_value, const char * testArray, const size_t & testArrayXResolution, const size_t & testArrayYResolution,
									     const size_t & testColorDepth, const long & testArrayXOffset, const long & testArrayYOffset,
									     const char * resultArray, const size_t & resultArraySize, const size_t & resultXResolution, const size_t & resultYResolution,
									     const size_t & resultColorDepth, const bool & fullscreen)
{
	// Init vars.
	bool result = false;					// The result of this test function.
#ifndef _NDEBUG
	const char * imageBuffer = NULL;			// Only used in a debug build, this holds a pointer to the final image buffer made by the renderer.
	const char * overlayBuffer = NULL;			// Only used in a debug build, this holds a pointer to an overlay image buffer made by the renderer.
#endif
	Common::Renderer::Renderer_Text_Console renderer;	// The renderer class we are testing.

	// Set the blank value.
	renderer.Set_Blank_Value(blank_value);

	// Set the resolution.
	if (renderer.Change_Resolution(resultXResolution, resultYResolution, resultColorDepth, fullscreen))
	{
		// Call Blit_Text(). (The additional args control offsets.)
		if (renderer.Blit_Text(testArray, 0, true, testArrayXResolution, testArrayYResolution))
		{
		    // Set the overlay's offsets.
		    renderer.Set_Overlay_Offsets(testArrayXOffset, testArrayYOffset);

			// Show it.
			std::cout << "Attempting to render the test plane:\n\n";
			std::cout.flush();
			if (renderer.Render())
			{
#ifndef _NDEBUG
				// Because the Return_Current_Final_Image_Buffer() function is a debug function, we have to isolate it.
				// Get the pointer.
				imageBuffer = renderer.Return_Current_Final_Image_Buffer();
				if (imageBuffer != NULL)
				{
					// Inform user.
					std::cout << "\n\nChecking result of render: ";
					std::cout.flush();
					if (memcmp(resultArray, imageBuffer, (testArrayXResolution * testArrayYResolution)) == 0)
					{
						// Test successful.
						std::cout << "PASS\n";
						std::cout.flush();
						result = true;
					}
					else
					{
						// Test failure.
						std::cout << "FAIL\n" << "Rendered image does not match expected result, there is a bug in the renderer.\n";
						std::cout << "The result should be:\n";
						for (size_t x = 0; x < (testArrayXResolution * testArrayYResolution); x++)
						{
							std::cout << resultArray[x];
						}
						std::cout << '\n';
						std::cout.flush();

						// Attempt to get the working buffer pointer.
						overlayBuffer = renderer.Return_Current_Overlay_Image_Buffer();
						if (overlayBuffer != NULL)
						{
							// Output the working buffer data.
							std::cout << "The working buffer data was:\n";
							for (size_t x = 0; x < (testArrayXResolution * testArrayYResolution); x++)
							{
								std::cout << overlayBuffer[x];
							}
							std::cout << '\n';
							std::cout.flush();

							// Check to see if the working buffer is valid.
							if (memcmp(testArray, overlayBuffer, (testArrayXResolution * testArrayYResolution)) == 0)
							{
								std::cout << "Generated overlay data is correct, bug is located in the Render() function.\n";
								std::cout.flush();
							}
							else
							{
								std::cout << "Generated overlay data is invalid, at least one bug is present in the Blit_Text() function.\n";
								std::cout << "The working buffer data should be:\n";
								for (size_t x = 0; x < (testArrayXResolution * testArrayYResolution); x++)
								{
									std::cout << testArray[x];
								}
								std::cout << '\n';
								std::cout.flush();
							}
						}
						else
						{
							// Could not retrive pointer to the working buffer data.
							std::cout << "ERROR: Unable to retrive a pointer to the working buffer data.\n";
						}
						std::cout.flush();
						result = false;
					}
				}
				else
				{
					// Error.
					std::cout << "ERROR: Debug pointer to renderer's image buffer is invalid.\n\n";
					result = false;
				}
#else
				// Inform user.
				std::cout << "\n\nRender complete, unable to check result as this is a release build of the Unit_Tests program.\n" << "If this is not the desired result, file a bug.\n";

				// Set result.
				result = true;
#endif
			}
			else
			{
				// Render() failed.
				std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Render() failed.\n";
				std::cout << "Last error from renderer: " << renderer.Get_Last_Error() << "\n\n";
			}
		}
		else
		{
			// Blit_Text() failed.
			std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Blit_Text() failed.\n";
			std::cout << "Last error from class: " << renderer.Get_Last_Error() << "\n\n";
		}
	}
	else
	{
		// Error could not change resolution.
		std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Change_Resolution() failed.\n";
		std::cout << "Last error from class: " << renderer.Get_Last_Error() << "\n\n";
	}

	// Exit function.
	return result;
}

bool Renderer_Text_Console_Basic_No_Overlay_Test()
{
	// Init vars.
	bool result = false;					// The result of this test function.
#ifndef _NDEBUG
	const char * imageBuffer = NULL;			// Only used in a debug build, this holds a pointer to the final image buffer made by the renderer.
	const char * overlayBuffer = NULL;			// Only used in a debug build, this holds a pointer to an overlay image buffer made by the renderer.
#endif
	Common::Renderer::Renderer_Text_Console renderer;	// The renderer class we are testing.

	// Define the used values.
	std::cout << "Dot value: (" << RENDER_TEXT_CHAR_DOT << ")\n";
	std::cout << "Blank value: (" << RENDER_TEXT_BLANK_VALUE << ")\n";
	std::cout.flush();

	// Set the blank value.
	renderer.Set_Blank_Value(RENDER_TEXT_BLANK_VALUE);

	// Set the resolution as 3x3.
	if (renderer.Change_Resolution(3, 3, 2, false))
	{
		// Blit a dot.
		if (renderer.Blit_Text(RENDER_TEXT_BASIC_TEST_RESULT, 0, true, (sizeof(RENDER_TEXT_BASIC_TEST_RESULT) / sizeof(char)), 1))  // Should produce a '.' at the center of the plane.
		{
			// Show it.
			std::cout << "Attempting to render a 3x3 plane with a dot at the center:\n\n";
			if (renderer.Render())
			{
#ifndef _NDEBUG
				// Because the Return_Current_Final_Image_Buffer() function is a debug function, we have to isolate it.
				// Get the pointer.
				imageBuffer = renderer.Return_Current_Final_Image_Buffer();
				if (imageBuffer != NULL)
				{
					// Inform user.
					std::cout << "\n\nChecking result of render: ";
					std::cout.flush();
					if (memcmp(&RENDER_TEXT_BASIC_TEST_RESULT, imageBuffer, (sizeof(RENDER_TEXT_BASIC_TEST_RESULT) / sizeof(char))) == 0)
					{
						// Test successful.
						std::cout << "PASS\n";
						std::cout.flush();
						result = true;
					}
					else
					{
						// Test failure.
						std::cout << "FAIL\n" << "Rendered image does not match expected result, there is a bug in the renderer.\n";
						std::cout << "The result should be:\n" << RENDER_TEXT_BASIC_TEST_RESULT << "\n";

						// Attempt to get the working buffer pointer.
						overlayBuffer = renderer.Return_Current_Overlay_Image_Buffer();
						if (overlayBuffer != NULL)
						{
							// Output the working buffer data.
							std::cout << "The working buffer data was: " << overlayBuffer << '\n';

							// Check to see if the working buffer is valid.
							if (memcmp(&RENDER_TEXT_BASIC_TEST_RESULT, overlayBuffer, (sizeof(RENDER_TEXT_BASIC_TEST_RESULT) / sizeof(char))) == 0)
							{
								std::cout << "Generated overlay data is correct, bug is located in the Render() function.\n";
								std::cout.flush();
							}
							else
							{
								std::cout << "Generated overlay data is invalid, at least one bug is present in the Blit_Text() function.\n";
								std::cout.flush();
							}
						}
						else
						{
							// Could not retrive pointer to the working buffer data.
							std::cout << "ERROR: Unable to retrive a pointer to the working buffer data.\n";
						}
						std::cout.flush();
						result = false;
					}
				}
				else
				{
					// Error.
					std::cout << "ERROR: Debug pointer to renderer's image buffer is invalid.\n\n";
					result = false;
				}
#else
				// Inform user.
				std::cout << "\n\nRender complete, unable to check result as this is a release build of the Unit_Tests program.\n" << "If this is not the desired result, file a bug.\n";

				// Set result.
				result = true;
#endif
			}
			else
			{
				// Render() failed.
				std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Render() failed.\n";
				std::cout << "Last error from renderer: " << renderer.Get_Last_Error() << "\n\n";
			}
		}
		else
		{
			// Blit_Text() failed.
			std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Blit_Text() failed.\n";
			std::cout << "Last error from class: " << renderer.Get_Last_Error() << "\n\n";
		}
	}
	else
	{
		// Error could not change resolution.
		std::cout << "\n\nERROR: Renderer_Text_Console_Basic_No_Overlay_Test(): renderer.Change_Resolution() failed.\n";
		std::cout << "Last error from class: " << renderer.Get_Last_Error() << "\n\n";
	}

	// Exit function.
	return result;
}

short Unit_Test_Rendering_Subsystem_Main()
{
	// Init result.
	short result = 0;

	// Output START OF TEST SECTION.
	std::cout << START_TEST_SECTION;

	// Enable debug output.
	Common::Renderer::DebugChannel.change_log_level(ERROR_VERBOSE);

	// Tell the user the Rendering Subsystem API Version.
	std::cout << "Rendering Subsystem Version: v" << Common::Renderer::Get_Rendering_Subsystem_API_Major_Version_Number() << '.';
	std::cout << Common::Renderer::Get_Rendering_Subsystem_API_Minor_Version_Number() << '.';
	std::cout << Common::Renderer::Get_Rendering_Subsystem_API_Revision_Version_Number() << ".\n";
	std::cout.flush();

	// Tell the user we are currently testing the Renderer_Text_Console class.
	std::cout << "Performing tests on the Renderer_Text_Console class.\n";
	std::cout << "Please wait.\n";
	std::cout.flush();

	// Call Renderer_Text_Console_Basic_No_Overlay_Test().
	if (!Renderer_Text_Console_Basic_No_Overlay_Test())
	{
		result = -1;
	}
	else
	{
		// Run the basic test again, but use the generic test function to do it.
		std::cout << "Rerunning basic test with generic test function.\n";
		std::cout.flush();
		if(!Renderer_Text_Console_Blit_Text_No_Overlay_Test_Function(RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_BASIC_TEST_RESULT, (sizeof(RENDER_TEXT_BASIC_TEST_RESULT) / sizeof(char)), 3, 3, 2, false))
		{
			result = -2;
		}
		else
		{
			// Run the edge test.
			std::cout << "Running edge test.\n";
			std::cout.flush();
			if (!Renderer_Text_Console_Blit_Text_No_Overlay_Test_Function(RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_EDGE_TEST_RESULT, (sizeof(RENDER_TEXT_EDGE_TEST_RESULT) / sizeof(char)), 3, 3, 2, false))
			{
				result = -3;
			}
			else
			{
				// Run the shift down tests.
				/*std::cout << "Running the left shift down test.\n";
				std::cout.flush();
				if (!Renderer_Text_Console_Blit_Text_No_Overlay_Test_Function(RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_EDGE_TEST_RESULT, (sizeof(RENDER_TEXT_EDGE_TEST_RESULT) / sizeof(char)), 3, 3, 2, false))
				{
					result = -4;
				}
				else
				{*/
					std::cout << "Running the right shift down test.\n";
					std::cout.flush();
					if (!Renderer_Text_Console_Blit_Text_No_Overlay_Transformation_Test_Function(RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_EDGE_TEST_RESULT, 3, 3, 2, 1, 1,
														    RENDER_TEXT_SHIFT_RIGHT_DOWN_TEST_RESULT, (sizeof(RENDER_TEXT_SHIFT_RIGHT_DOWN_TEST_RESULT) / sizeof(char)), 3, 3,
														    2, false))
					{
						result = -5;
					}
					else
					{
						std::cout << "Running the left shift up test.\n";
						std::cout.flush();
						if (!Renderer_Text_Console_Blit_Text_No_Overlay_Transformation_Test_Function(RENDER_TEXT_BLANK_VALUE, RENDER_TEXT_EDGE_TEST_RESULT, 3, 3, 2, -1, -1,
															    RENDER_TEXT_SHIFT_LEFT_UP_TEST_RESULT, (sizeof(RENDER_TEXT_SHIFT_LEFT_UP_TEST_RESULT) / sizeof(char)), 3, 3,
															    2, false))
						{
							result = -6;
						}
					}
				//}
			}
		}
	}

	// Output END OF TEST SECTION.
	std::cout << END_TEST_SECTION;
	std::cout.flush();

	// Return result.
	return result;
}
