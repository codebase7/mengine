/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Text_Console.cpp	22/12/2013

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

#include "Renderer.h"

bool Common::Renderer::Renderer_Text_Console::Generate_Fake_Transparency_Data(const char * dataArray, const size_t & dataLength, char *& transparencyData)
{
	// Init result.
	bool result = false;

	// Debug args.
	//std::cout << "Generate_Fake_Transparency_Data() Arguments:\n";
	//std::cout << "dataArray: " << &dataArray << ".\n";
	//std::cout << "dataLength: " << dataLength << ".\n";
	//std::cout << "transparencyData: " << &transparencyData << ".\n";
	//std::cout.flush();

	// Make sure dataArray is not NULL.
	if (dataArray != NULL)
	{
		// Make sure dataLength is greater than zero.
		if (dataLength > 0)
		{
			// Begin try block.
			try{
				// Check and see if the transparencyData buffer is allocated.
				if (transparencyData != NULL)
				{
					// Release the transparencyData buffer.
					delete[] transparencyData;
					transparencyData = NULL;
				}

				// Allocate the transparencyData buffer.
				transparencyData = new char[dataLength];

				// Check and see if it was allocated.
				if (transparencyData != NULL)
				{
					// Set the values to NULL.
					memset(transparencyData, '\0', dataLength);

					// Start generation loop.
					for (size_t x = 0; x < dataLength; x++)
					{
						/*
						 * For each value in dataArray that is not blankValue,
						 * make the corrosponding value in transparencyData, TEXT_CONSOLE_RENDERER_TRANSPARENCY_VALUE.
						 *
						 * (This performs the same effect as the original blank value.
						 *  I.e. If the blankValue is not present at that location,
						 *  the renderer considers it part of the image.
						 *
						 *  If the blankValue is present at that location, then the
						 *  renderer considers that location blank, and anything
						 *  under that overlay on the final image will not be altered.
						 *
						 *  Short version: Fake transparency, as the text console does
						 *  not display actual images only characters.)
						 */
						if (dataArray[x] != this->blankValue)
						{
							transparencyData[x] = TEXT_CONSOLE_RENDERER_TRANSPARENCY_VALUE;
						}
					}

					// Set result.
					result = true;
				}
				else
				{
					// Could not allocate memory.
					this->lastError = -25;
				}
			}
			catch(...)
			{
				// Clear the buffer if it was allocated.
				if (transparencyData != NULL)
				{
					delete[] transparencyData;
					transparencyData = NULL;
				}

				// Exception thrown.
				this->lastError = -13;
			}
		}
	}

	// Return result.
	return result;
}

void Common::Renderer::Renderer_Text_Console::Calculate_Transparency(const char & srcImgVal, const char & srcTransVal, char & destImgVal, char & destTransVal)
{
	// Check and see if the srcTransVal is equal to TEXT_CONSOLE_RENDERER_TRANSPARENCY_VALUE.
	if (srcTransVal == TEXT_CONSOLE_RENDERER_TRANSPARENCY_VALUE)
	{
		// Copy the data and continue.
		destImgVal = srcImgVal;
		destTransVal = srcTransVal;
	}

	// Exit function.
	return;
}

size_t Common::Renderer::Get_TEXT_CONSOLE_ERROR_TABLE_Size()
{
	// Return the size of the table. (Size of the table divided by the size of a single element in the table.)
	return (sizeof(Common::Renderer::TEXT_CONSOLE_ERROR_TABLE) / sizeof(Common_Error_Object));
}

bool Common::Renderer::Renderer_Text_Console::Change_Resolution(const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth, const bool & fullscreen)
{
	// Init char pointer.
	bool result = false;				// Result of this function.
	Common::Renderer::Overlay<char> temp;		// Used to create an overlay buffer if needed.
	size_t finalResultXResolution = 0;
	size_t finalResultYResolution = 0;

	// Reset last error.
	this->lastError = 0;

	// Begin try block.
	try{
		// Set the change flag.
		this->bChangeSinceLastRender = true;

		// Allocate new memory. (c-string length is the product of the xScreenResolution and yScreenResolution arguments.)
		this->finalResult.Create_Overlay(this->blankValue, 0, 0, xScreenResolution, yScreenResolution);

		// Check that the overlay was setup correctly.
		this->finalResult.Get_Resolution(finalResultXResolution, finalResultYResolution);
		if ((finalResultXResolution == xScreenResolution) && (finalResultYResolution == yScreenResolution))
		{
			// Set the finalResult blankValue.
			this->finalResult.Set_Blank_Value(this->blankValue);

			// Set the renderer transparency function.
			this->finalResult.Set_Transparency_Function(Common::Renderer::Renderer_Text_Console::Calculate_Transparency);

			// Check to see if the overlay system is disabled.
			if (!this->bOverlaysEnabled)
			{
				// Overlays are disabled, reset the overlay vector.
				this->overlayStack.clear();

				// Place the temp value in the vector.
				this->overlayStack.push_back(temp);

				// Make sure we added the overlay to the overlayStack.
				if (this->overlayStack.size() == 1)
				{
					// Now create a new overlay for a working buffer.
					// Allocate new memory. (c-string length is the product of the xScreenResolution and yScreenResolution arguments.)
					if (this->overlayStack[0].Create_Overlay(this->blankValue, 0, 0, xScreenResolution, yScreenResolution))
					{
						// Set the remaining class pramaters.
						this->xScreenResolution = xScreenResolution;
						this->yScreenResolution = yScreenResolution;
						this->colorDepth = colorDepth;
						this->bFullscreen = fullscreen;

						// Set result.
						result = true;
					}
					else
					{
						// Could not allocate memory for overlay image buffer.
						this->lastError = -11;
						this->overlayStack.clear();
					}
				}
				else
				{
					// Could not create a new overlay in the overlay stack.
					this->lastError = -10;
				}
			}
			else
			{
				// Set the remaining class pramaters.
				this->xScreenResolution = xScreenResolution;
				this->yScreenResolution = yScreenResolution;
				this->colorDepth = colorDepth;
				this->bFullscreen = fullscreen;

				// Set result.
				result = true;
			}
		}
		else
		{
			// Set lastError.
			this->lastError = -12;
		}
	}
	catch(...)
	{
		// If the memory was allocated, free it.
		this->finalResult.Reset_Overlay();

		// If needed reset the overlayStack.
		if (!this->bOverlaysEnabled)
		{
			// Reset the overlay stack.
			this->overlayStack.clear();
		}

		// Set lastError.
		this->lastError = -13;
	}

	// Return the result.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Set_Blank_Value(const char & value)
{
	// Init result.
	bool result = false;

	// Guard against using newline as a blank value.
	if (value != '\n')
	{
		// Set blank value.
		this->blankValue = value;

		// Set it on all overlays if needed.
		if (bOverlaysEnabled)
		{
			for (size_t x = 0; x < this->overlayStack.size(); x++)
			{
				this->overlayStack[x].Set_Blank_Value(this->blankValue);
			}
		}

		// Set the change flag.
		this->bChangeSinceLastRender = true;

		// Set result.
		result = true;
	}
	else
	{
		// You cannot use a newline ('\n') character as a blank value.
		this->lastError = -14;
	}

	// Return the result.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Set_Blank_Value(const size_t & overlayNumber, const char & value)
{
	// Init result.
	bool result = false;

	// Guard against using newline as a blank value.
	if (value != '\n')
	{
		// Check and see if overlays are enabled, and that the overlayNumber is valid.
		if ((bOverlaysEnabled) && ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size())))
		{
			// Set the overlay's blankValue.
			this->overlayStack[overlayNumber].Set_Blank_Value(this->blankValue);

			// Set the change flag.
			this->bChangeSinceLastRender = true;

			// Set result.
			result = true;
		}
		else
		{
			// Invalid overlayNumber.
			this->lastError = -17;
		}
	}
	else
	{
		// You cannot use a newline ('\n') character as a blank value.
		this->lastError = -14;
	}

	// Return the result.
	return result;
}

char Common::Renderer::Renderer_Text_Console::Get_Blank_Value() const
{
	// Return blankValue.
	return this->blankValue;
}

char Common::Renderer::Renderer_Text_Console::Get_Blank_Value(const size_t & overlayNumber) const
{
	// Init result.
	char result = this->blankValue;

	// Check and see if the given overlay exists.
	if ((this->bOverlaysEnabled) && ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size())))
	{
		// Get the overlay's blankValue.
		result = this->overlayStack[overlayNumber].Get_Blank_Value();
	}

	// Return the result.
	return result;
}

const char * Common::Renderer::Renderer_Text_Console::Get_Last_Error() const
{
	// Init result.
	const char * result = TEXT_CONSOLE_ERROR_TABLE[1].error;	// Default is to return the unknown error code message.

	// Guard against no errors.
	if (this->lastError != 0)
	{
		// Start lookup loop.
		for (size_t x = 0; ((x < Common::Renderer::Get_TEXT_CONSOLE_ERROR_TABLE_Size()) && (result == TEXT_CONSOLE_ERROR_TABLE[1].error)); x++)
		{
			// Check for matching error code.
			if (this->lastError == TEXT_CONSOLE_ERROR_TABLE[x].errorCode)
			{
				// Set the error message.
				result = TEXT_CONSOLE_ERROR_TABLE[x].error;
			}
		}
	}
	else
	{
		// Return no error message.
		result = TEXT_CONSOLE_ERROR_TABLE[0].error;
	}

	// Return the result.
	return result;
}

short Common::Renderer::Renderer_Text_Console::Get_Last_Error_Code() const
{
	// Return lastError.
	return this->lastError;
}

bool Common::Renderer::Renderer_Text_Console::Render()
{
	// Init result.
	bool result = false;			// The result of this function.
	long overlayXOffset = 0;		// Holds the X axis offset for the current overlay.
	long overlayYOffset = 0;		// Holds the Y axis offset for the current overlay.
	size_t finalResultXResolution = 0;	// Holds the X axis resolution of the finalResult overlay.
	size_t finalResultYResolution = 0;	// Holds the Y axis resolution of the finalResult overlay.

	// Reset last error.
	this->lastError = 0;

	// Make sure finalResult is allocated.
	this->finalResult.Get_Resolution(finalResultXResolution, finalResultYResolution);
	if ((finalResultXResolution > 0) && (finalResultYResolution > 0))
	{
		// Check for a change since the last time we were called.
		if (this->bChangeSinceLastRender)
		{
			// Reset the finalResult buffer.
			this->finalResult.Clear_Overlay_Data();

			// Begin overlayStack iteration loop.
			for (size_t x = this->overlayStack.size(); x > 0; x--)
			{
				// Get the overlay offsets.
				this->overlayStack[(x - 1)].Get_Overlay_Offsets(overlayXOffset, overlayYOffset);

				// Call Blit().
				this->finalResult.Blit(this->overlayStack[(x - 1)], overlayXOffset, overlayYOffset);
			}

			// Clear the change flag.
			this->bChangeSinceLastRender = false;
		}

		// Output the data to std::cout.
		for (size_t x = 0; x < (this->xScreenResolution * this->yScreenResolution); x++)
		{
			/*
				Newlines must be inserted at the end of the row after the output.

				(XRes - 1) = last element on row
				XRes = first element on next row

				XRes: 3 YRes: 3

				[0] [1] [2] <'\n'>
				[3] [4] [5] <'\n'>
				[6] [7] [8] <'\n'>
			*/

			// Check and see if a newline is needed.
			if ((!this->bFullscreen) && ((x % (this->xScreenResolution) == 0) && (x > 0)))
			{
				// Output a newline character.
				std::cout << '\n';

				// Flush the output buffer.
				std::cout.flush();
			}

			// Output data from the buffer.
			std::cout << this->finalResult.Get_Data_Element(x);
			std::cout.flush();
		}

		// Set result.
		result = true;
	}
	else
	{
		// Internal Error, finalResult buffer is not allocated while trying to output to console.
		this->lastError = -15;
	}

	// Exit function.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Blit_Text(const char * textString, const size_t & overlayNumber, const bool & lineWrap, const size_t & textStringXResolution, const size_t & textStringYResolution, const size_t & xCoordOffset, const size_t & yCoordOffset)
{
	// Init result.
	bool result = false;			// The result of this function.
	char * transparencyData = NULL;		// Holds a pointer to the fake transparency data buffer.

	// Reset lastError.
	this->lastError = 0;

	// Check for a valid string.
	if ((textString != NULL) && (textStringXResolution > 0))
	{
		// Check for a valid overlay.
		if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
		{
			// Generate fake transparency data.
			if (Common::Renderer::Renderer_Text_Console::Generate_Fake_Transparency_Data(textString, (textStringXResolution * textStringYResolution), transparencyData))
			{
				// Blit the data.
				this->overlayStack[overlayNumber].Blit(textString, transparencyData, xCoordOffset, yCoordOffset, textStringXResolution, textStringYResolution, lineWrap);

				// Release the transparencyData buffer.
				if (transparencyData != NULL)
				{
					delete[] transparencyData;
					transparencyData = NULL;
				}

				// Set result.
				result = true;
			}
			else
			{
				// Set last error. (Could not generate transparency data.)
				this->lastError = -26;
			}
		}
		else
		{
			// Set last error.
			this->lastError = -17;
		}
	}
	else
	{
		// Set last error.
		this->lastError = -18;
	}

	// Exit function.
	return result;
}

short Common::Renderer::Renderer_Text_Console::Get_Overlay_Debugging_Level(const size_t & overlayNumber)
{
	// Init result.
	short result = 0;	// Holds the returned debugging level from the overlay. (Default is debugging level zero (0).)

	// Check to see if the given overlay number exists.
	if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
	{
		// Get the overlay's debugging level.
		result = this->overlayStack[overlayNumber].Get_Debug_Level();
	}
	else
	{
		// No overlay exists with the given offset.
		this->lastError = -17;
	}

	// Return the result.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Set_Overlay_Debugging_Level(const size_t & overlayNumber, const short & level)
{
	// Init result.
	bool result = false;

	// Check to see if the given overlay number exists.
	if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
	{
		// Set the overlay's debugging level.
		this->overlayStack[overlayNumber].Set_Debug_Level(level);

		// Set result.
		result = true;
	}
	else
	{
		// No overlay exists with the given offset.
		this->lastError = -17;
	}

	// Return the result.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Create_Overlay(const size_t & xResolution, const size_t & yResolution, const long & xCoordOffset, const long & yCoordOffset)
{
	// Init result.
	bool result = false;					// The result of this function.
	size_t overlayStackSize = this->overlayStack.size();	// Holds the overlay stack size prior to creating the new overlay.
	size_t createdOverlayXAxisResolution = 0;		// Used to check the created overlay's x axis resolution.
	size_t createdOverlayYAxisResolution = 0;		// Used to check the created overlay's y axis resolution.
	Common::Renderer::Overlay<char> temp;			// Used to create an overlay buffer.

	std::cout << "xCoordOffset = " << xCoordOffset << ".\nyCoordOffset = " << yCoordOffset << ".\n";
	std::cout.flush();

	// Check to see if overlays are enabled.
	if (this->bOverlaysEnabled)
	{
		// Check for invalid resolutions.
		if ((xResolution > 0) && (yResolution > 0))
		{
			// Begin try block.
			try{
				// Place the temp value in the vector.
				this->overlayStack.push_back(temp);

				// Make sure we added the overlay to the overlayStack.
				if ((overlayStackSize + 1) == this->overlayStack.size())
				{
					// Set renderer transparency function.
					this->finalResult.Set_Transparency_Function(Common::Renderer::Renderer_Text_Console::Calculate_Transparency);

					// Allocate new memory. (c-string length is the product of the xResolution and yResolution arguments.)
					this->overlayStack[(this->overlayStack.size() - 1)].Create_Overlay(this->blankValue, xCoordOffset, yCoordOffset, xResolution, yResolution);

					// Check that the overlay was setup correctly.
					this->overlayStack[(this->overlayStack.size() - 1)].Get_Resolution(createdOverlayXAxisResolution, createdOverlayYAxisResolution);
					if ((createdOverlayXAxisResolution == xResolution) && (createdOverlayYAxisResolution == yResolution))
					{
						// Set result.
						result = true;
					}
					else
					{
						// Could not allocate memory for overlay image buffer.
						this->lastError = -11;
					}
				}
				else
				{
					// Could not create a new overlay in the overlay stack.
					this->lastError = -10;
				}
			}
			catch(...)
			{
				// An exception was thrown while attempting to create the overlay.
				this->lastError = -19;

				// If the memory was allocated, free it.
				if ((overlayStackSize + 1) == this->overlayStack.size())
				{
					// Clear the overlay data.
					this->overlayStack[overlayStackSize].Clear_Overlay_Data();

					// Erase the created overlay.
					DataProcess::removeFromVector(this->overlayStack, overlayStackSize);
				}
			}
		}
	}

	// Exit function.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Destroy_Overlay(const size_t & overlayNumber)
{
	// Init result.
	bool result = false;			// The result of this function.

	// Check to see if overlays are enabled.
	if (this->bOverlaysEnabled)
	{
		// Check to see if the given overlay number exists.
		if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
		{
			// Clear the overlay's data.
			this->overlayStack[overlayNumber].Clear_Overlay_Data();

			// Destroy that overlay.
			DataProcess::removeFromVector(this->overlayStack, overlayNumber);

			// Set the change flag.
			this->bChangeSinceLastRender = true;

			// Set result.
			result = true;
		}
		else
		{
			// No overlay exists with the given offset.
			this->lastError = -17;
		}
	}

	// Exit function.
	return result;
}

void Common::Renderer::Renderer_Text_Console::Clear_Overlay(const size_t & overlayNumber)
{
	// Check to see if the given overlay number exists.
	if ((this->bOverlaysEnabled) && (overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
	{
		// Clear that overlay.
		this->overlayStack[overlayNumber].Clear_Overlay_Data();

		// Set the change flag.
		this->bChangeSinceLastRender = true;
	}
	else
	{
		// No overlay exists with the given offset.
		this->lastError = -17;
	}

	// Exit function.
	return;
}

void Common::Renderer::Renderer_Text_Console::Reset_Overlay(const size_t & overlayNumber)
{
	// Check to see if the given overlay number exists.
	if ((this->bOverlaysEnabled) && (overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
	{
		// Reset the overlay.
		this->overlayStack[overlayNumber].Reset_Overlay();

		// Set the change flag.
		this->bChangeSinceLastRender = true;
	}
	else
	{
		// No overlay exists with the given offset.
		this->lastError = -17;
	}

	// Exit function.
	return;
}

bool Common::Renderer::Renderer_Text_Console::Change_Overlay_Resolution(const size_t & overlayNumber, const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth, const bool & fullscreen)
{
	// Init char pointer.
	bool result = false;				// Result of this function.

	// Check and see if overlays are enabled, and that the overlayNumber is valid.
	if ((bOverlaysEnabled) && ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size())))
	{
		// Change the overlay's resolution.
		result = this->overlayStack[overlayNumber].Change_Resolution(xScreenResolution, yScreenResolution);
	}

	// Return the result.
	return result;
}

void Common::Renderer::Renderer_Text_Console::Get_Overlay_Offsets(long & xCoordOffset, long & yCoordOffset, const size_t & overlayNumber)
{
	// Check to see if overlays are enabled.
	if (this->bOverlaysEnabled)
    {
        // Check to see if the given overlay number exists.
        if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
        {
            // Get the offsets.
            this->overlayStack[(overlayNumber)].Get_Overlay_Offsets(xCoordOffset, yCoordOffset);
        }
        else
        {
            // No overlay exists with the given offset.
            this->lastError = -17;
        }
    }
    else
    {
        // Make sure the working buffer is allocated.
        if (this->overlayStack.size() == 1)
        {
            // Get the offsets for the working buffer.
            this->overlayStack[0].Get_Overlay_Offsets(xCoordOffset, yCoordOffset);
        }
        else
        {
            // We don't have a working buffer.
            this->lastError = -16;
        }
    }

	// Exit function.
	return;
}

void Common::Renderer::Renderer_Text_Console::Set_Overlay_Offsets(const long & xCoordOffset, const long & yCoordOffset, const size_t & overlayNumber)
{
	// Check to see if overlays are enabled.
	if (this->bOverlaysEnabled)
    {
        // Check to see if the given overlay number exists.
        if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
        {
            // Move overlay.
            this->overlayStack[overlayNumber].Set_Overlay_Offsets(xCoordOffset, yCoordOffset);

            // Set the change flag.
            this->bChangeSinceLastRender = true;
        }
        else
        {
            // No overlay exists with the given offset.
            this->lastError = -17;
        }
    }
    else
    {
        // Check and see if the working buffer is allocated.
        if (this->overlayStack.size() == 1)
        {
            // Move overlay.
            this->overlayStack[0].Set_Overlay_Offsets(xCoordOffset, yCoordOffset);

            // Set the change flag.
            this->bChangeSinceLastRender = true;
        }
        else
        {
            // We don't have a working buffer.
            this->lastError = -16;
        }
    }

	// Exit function.
	return;
}

bool Common::Renderer::Renderer_Text_Console::Swap_Overlays(const size_t & firstOverlayNumber, const size_t & secondOverlayNumber)
{
	// Init vars.
	bool result = false;			// The result of this function.

	// Check to see if overlays are enabled.
	if (this->bOverlaysEnabled)
	{
		// Check to see if the given overlay numbers exist.
		if (((firstOverlayNumber >= 0) && (firstOverlayNumber < this->overlayStack.size())) && ((secondOverlayNumber >= 0) && (secondOverlayNumber < this->overlayStack.size())))
		{
			// Call Overlay<>::Swap_Overlays().
			if (this->overlayStack[firstOverlayNumber].Swap_Overlays(this->overlayStack[secondOverlayNumber]))
			{
				// Set the change flag.
				this->bChangeSinceLastRender = true;
			}
		}
		else
		{
			// A given overlay does not exist.
			this->lastError = -20;
		}
	}
	else
	{
		// Overlays are disabled.
		this->lastError = -21;
	}

	// Exit function.
	return result;
}

bool Common::Renderer::Renderer_Text_Console::Duplicate_Overlay(const size_t & sourceOverlayNumber, const size_t & destOverlayNumber)
{
	// Init vars.
	bool result = false;			// The result of this function.

	// Check to see if overlays are enabled.
	if (this->bOverlaysEnabled)
	{
		// Check to make sure that the given overlays are not the same overlay.
		if (sourceOverlayNumber != destOverlayNumber)
		{
			// Begin try block.
			try{
				// Check to see if the given overlay numbers exist.
				if (((sourceOverlayNumber >= 0) && (sourceOverlayNumber < this->overlayStack.size())) && ((destOverlayNumber >= 0) && (destOverlayNumber < this->overlayStack.size())))
				{
					// Call Overlay<T>::Duplicate_Overlay().
					if (!this->overlayStack[destOverlayNumber].Duplicate_Overlay(this->overlayStack[sourceOverlayNumber]))
					{
						// Error copying overlay, get last error.
						this->lastError = -27;

						// Reset the overlay.
						this->overlayStack[destOverlayNumber].Clear_Overlay_Data();
						this->overlayStack[destOverlayNumber].Reset_Overlay();
					}
					else
					{
						// Set result.
						result = true;
					}
				}
			}
			catch(...)
			{
				// Exception thrown while duplicating overlay, clearing dest overlay.
				this->lastError = -23;
				this->overlayStack[destOverlayNumber].Clear_Overlay_Data();
				this->overlayStack[destOverlayNumber].Reset_Overlay();
			}
		}
		else
		{
			// Given overlay offsets are the same. Cannot overwrite an overlay with itself.
			this->lastError = -24;
		}
	}
	else
	{
		// Overlays are disabled.
		this->lastError = -21;
	}

	// Exit function.
	return result;
}

const char * Common::Renderer::Renderer_Text_Console::Get_Last_Error_From_Overlay(const size_t & overlayNumber) const
{
	// Init result.
	const char * result = Common::commonErrorTable[2].error;	// Holds the pointer to the error message string. (Default is to return the invalid argument message. (If the overlay is valid it will set unknown error.))

	// Check and see if the given overlay exists.
	if ((this->bOverlaysEnabled) && ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size())))
	{
		// Get the overlay's last error.
		result = this->overlayStack[overlayNumber].Get_Last_Error();
	}

	// Return the result.
	return result;
}

short Common::Renderer::Renderer_Text_Console::Get_Last_Error_Code_From_Overlay(const size_t & overlayNumber) const
{
	// Init result.
	short result = COMMON_INVALID_ARGUMENT;		// Holds the error code from the overlay. (Default is to return invalid argument.)

	// Check and see if the given overlay exists.
	if ((this->bOverlaysEnabled) && ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size())))
	{
		// Get the overlay's last error code.
		result = this->overlayStack[overlayNumber].Get_Last_Error_Code();
	}

	// Return the result.
	return result;
}

#ifndef _NDEBUG
const char * Common::Renderer::Renderer_Text_Console::Return_Current_Final_Image_Buffer()
{
	// Return the pointer.
	return this->finalResult.Get_Overlay_Data();
}

const char * Common::Renderer::Renderer_Text_Console::Return_Current_Overlay_Image_Buffer(const size_t & overlayNumber)
{
	// Init result.
	const char * result = NULL;

	// Get the correct overlay.
	if ((overlayNumber >= 0) && (overlayNumber < this->overlayStack.size()))
	{
		result = this->overlayStack[overlayNumber].Get_Overlay_Data();
	}

	// Return the result.
	return result;
}

#endif
