/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Data_Structures_Overlay_Base_Functions.h	21/12/2013

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
#ifndef COMMON_RENDER_SUBSYSTEM_H
#error "You must include the Renderer.h header file. It will include all of the other needed headers."
#endif

#ifndef COMMON_RENDER_DATA_STRUCT_OVERLAY_BASE_FUNCTIONS_H
#define COMMON_RENDER_DATA_STRUCT_OVERLAY_BASE_FUNCTIONS_H

namespace Common
{
	namespace Renderer
	{
		/*
		 * 	class Common::Renderer::Overlay
		 *
		 * 	This class is designed to use / manage raw bitmap data directly.
		 * 	(It can use other formatted data, by overriding the Get_Data_Element() and Set_Data_Element() functions,
		 * 	 but the functions must allow access to the raw bitmap data.)
		 *
		 * 	The generated output can be any data type, but the data type is used strictly as a storage variable,
		 * 	and not for processing data.
		 * 	(I.e. if it is a class for some rendering backend, none of it's functions except for accessing the raw
		 * 	 bitmap storage are used.)
		 *
		 * 	The goal of this class is to provide an overlay system, completely independant of whatever rendering backend
		 * 	is used to actually display the final result.
		 *
		 * 	A crude data flow diagram:
		 * 		[bitmap data]	[Rendering Backend]
		 * 			\       	/\
		 * 			 \      	/
		 * 			  \    	       /
		 * 			  _\/	      /
		 * 			[overlay system]
		 */
		template<class T>
		class Overlay
		{
			private:
				bool created;				// Whether or not the Create_Overlay() function has run at least once.
				bool transparencyBufferEnabled;		// Whether or not the transparencyData memory buffer is enabled for use.
				short lastError;			// The last error encountered by the overlay.
				short debugLevel;			// What debugging level to use for this Overlay.
				long masterXAxisOffset;			// The X axis offset on the final image where this overlay's top left corner will be placed.
				long masterYAxisOffset;			// The Y axis offset on the final image where this overlay's top left corner will be placed.
				size_t overlayXAxisResolution;		// The X resolution of the overlay. (Normally this applies to the amount of horazontal pixels, but in this case it applies to whatever your base unit of mesurement is. (Pixel, character, etc.))
				size_t overlayYAxisResolution;		// The Y resolution of the overlay. (Normally this applies to the amount of vertical pixels, but in this case it applies to whatever your base unit of mesurement is. (Pixel, character, etc.))
				T * overlayData;			// The actual image data in the overlay.
				T * transparencyData;			// Same size as overlayData, contains transparency information for each screen element in overlayData.
				void (*calcTrans)(const T& srcImgVal, const T& srcTransVal, T& destImgVal, T& destTransVal);	// Pointer to the transparency calculation function in the renderer.
				T blankValue;				// The value used to indicate no data is at that offset.


			protected:

			public:
				Overlay()
				{
					created = false;
					transparencyBufferEnabled = true;
					lastError = COMMON_ERROR_SUCCESS;
					debugLevel = ERROR_CRITICAL;
					masterXAxisOffset = 0;
					masterYAxisOffset = 0;
					overlayXAxisResolution = 0;
					overlayYAxisResolution = 0;
					overlayData = NULL;
					transparencyData = NULL;
					calcTrans = NULL;
				}
				~Overlay()
				{
					if (overlayData != NULL)
					{
						delete[] overlayData;
						overlayData = NULL;
					}
					if (transparencyData != NULL)
					{
						delete[] transparencyData;
						transparencyData = NULL;
					}
					calcTrans = NULL;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Set_Transparency_Function(void(*funct)(const T& srcImgVal, const T& srcTransVal, T& destImgVal, T& destTransVal))
				 *
				 * 	Sets the function callback used by the overlay to calculate transparencies.
				 *
				 * 	NOTE: The function callback is only used if the transparency buffer is enabled.
				 *
				 * 	Note: This is / SHOULD BE set by the renderer.
				 */
				void Set_Transparency_Function(void(*funct)(const T& srcImgVal, const T& srcTransVal, T& destImgVal, T& destTransVal))
				{
					// Set the function.
					this->calcTrans = funct;

					// Reset lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Exit function.
					return;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Enable_Transparency_Buffer()
				 *
				 * 	Enables the transparencyData memory buffer and allocates it.
				 *
				 * 	If the transparencyData memory buffer is already enabled this function will silently fail.
				 */
				void Enable_Transparency_Buffer()
				{
					// Init result.
					bool result = false;

					// Reset lastError.
					this->lastError = COMMON_SUCCESS;

					// Check and see if Create_Overlay() has been called at least once.
					if (this->created)
					{
						// Check and see if the transparencyBufferEnabled flag is false.
						if (!this->transparencyBufferEnabled)
						{
							// Begin try block.
							try{
								// Check to see if the transparencyData buffer is allocated.
								if (this->transparencyData != NULL)
								{
									delete[] this->transparencyData;
									this->transparencyData = NULL;
								}

								// Run the allocation code.
								this->transparencyData = new T[(this->overlayXAxisResolution * this->overlayYAxisResolution)];

								// Check to make sure it was allocated.
								if (this->transparencyData != NULL)
								{
									// Blank out the transparencyData buffer.
									memset(this->transparencyData, this->blankValue, (this->overlayXAxisResolution * this->overlayYAxisResolution));

									// Set the transparencyBufferEnabled flag.
									this->transparencyBufferEnabled = true;

									// Set the result flag.
									result = true;
								}
								else
								{
									// Could not allocate memory for transparencyData memory buffer.
									this->lastError = RENDERER_UNABLE_TO_ALLOC_TD_BUF;
								}
							}
							catch(...)
							{
								// Check to see if the transparencyData buffer is allocated.
								if (this->transparencyData != NULL)
								{
									delete[] this->transparencyData;
									this->transparencyData = NULL;
								}

								// Set the transparencyBufferEnabled flag to false.
								this->transparencyBufferEnabled = false;

								// Exception thrown.
								this->lastError = RENDERER_MEM_BUF_ALLOC_EXCEPTION;
							}
						}
					}

					// Return the result.
					return result;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Disable_Transparency_Buffer()
				 *
				 * 	Disables the transparencyData memory buffer, and deallocates it, if it has been allocated.
				 *
				 * 	If the transparencyData memory buffer is already disabled this function will silently fail.
				 */
				void Disable_Transparency_Buffer()
				{
					// Reset lastError.
					this->lastError = COMMON_SUCCESS;  

					// Check and see if the transparencyData buffer is enabled and allocated.
					if (this->transparencyBufferEnabled)
					{
						// Set the transparencyBufferEnabled flag to false.
						this->transparencyBufferEnabled = false;

						// Deallocate the transparencyData buffer.
						if (this->transparencyData != NULL)
						{
							delete[] this->transparencyData;
							this->transparencyData = NULL;
						}
					}

					// Exit function.
					return;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::is_Transparency_Buffer_Enabled() const
				 *
				 * 	Returns true if the overlay's transparencyData memory buffer is enabled, and allocated.
				 * 	Returns false otherwise.
				 */
				bool is_Transparency_Buffer_Enabled() const
				{
					// Check and see if the transparencyData buffer is enabled and allocated.
					return ((this->transparencyBufferEnabled) && (this->transparencyData != NULL));
				}

				/*!
				 * 	const char * Common::Renderer::Overlay<T>::Get_Last_Error() const
				 *
				 * 	Returns a human readable string of the last error that the overlay encountered.
				 */
				const char * Get_Last_Error() const
				{
					// Init result.
					const char * result = NULL;	// Default is unknown error.

					// Guard against no error.
					if (this->lastError != 0)
					{
						/* Call error lookup function call. */
						result = Common_Get_Error_Message(this->lastError);
					}
					else
					{
						// Result is no error.
						result = Common_Get_Error_Message(COMMON_ERROR_SUCCESS);
					}

					// Return the result.
					return result;
				}

				/*!
				 * 	short Common::Renderer::Overlay<T>::Get_Last_Error_Code() const
				 *
				 * 	Returns the last error code encountered by the overlay.
				 */
				short Get_Last_Error_Code() const
				{
					// Return the last error we encountered.
					return this->lastError;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Clear_Last_Error()
				 *
				 * 	Clears the last error encountered variable.
				 */
				void Clear_Last_Error()
				{
					// Reset lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Exit function.
					return;
				}

				/*!
				 * 	short Common::Renderer::Overlay<T>::Get_Debug_Level() const
				 *
				 * 	Returns the error / debug logging level for an overlay.
				 */
				short Get_Debug_Level() const
				{
					// Return the current error / debug logging level.
					return this->debugLevel;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Set_Debug_Level(const short & level)
				 *
				 * 	Sets the error / debug logging level for an overlay.
				 */
				void Set_Debug_Level(const short & level)
				{
					// Set the error / debug logging level.
					this->debugLevel = level;
					Common::Renderer::DebugChannel.change_log_level(this->debugLevel);

					// Exit function.
					return;
				}

				/*!
				 * 	bool Common::Renderer::Overlay<T>::is_Overlay_Created() const
				 *
				 * 	Returns whether or not the Create_Overlay() function has been called at least once for this overlay.
				 */
				bool is_Overlay_Created() const
				{
					// Return the created flag.
					return this->created;
				}

				/*!
				 * 	bool Common::Renderer::Overlay<T>::Create_Overlay(const long & xOffset, const long & yOffset, const size_t & xResolution, const size_t & yResolution)
				 *
				 * 	Sets up the overlay for the user.
				 *
				 * 	Returns true if the overlay is set up properly and it's buffers were allocated.
				 * 	Returns false otherwise.
				 */
				bool Create_Overlay(const T & newBlankValue, const long & xOffset, const long & yOffset, const size_t & xResolution, const size_t & yResolution)
				{
					// Init result.
					bool result = false;					// The result of this function.

					// Reset this->lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Check for invalid resolutions.
					if ((xResolution > 0) && (yResolution > 0))
					{
						// Check and see if the overlayData and transparencyData buffers are allocated.
						if (this->overlayData != NULL)
						{
							// Delete the old buffer.
							delete[] this->overlayData;
							this->overlayData = NULL;
						}
						if (this->transparencyData != NULL)
						{
							// Delete the old buffer.
							delete[] this->transparencyData;
							this->transparencyData = NULL;
						}

						// Reset the other data members.
						this->masterXAxisOffset = 0;
						this->masterYAxisOffset = 0;
						this->overlayXAxisResolution = 0;
						this->overlayYAxisResolution = 0;

						// Begin try block.
						try{
							// Set the blank value.
							this->blankValue = newBlankValue;

							// Allocate new memory. (Array length is the product of the xScreenResolution and yScreenResolution arguments.)
							this->overlayData = new T[(xResolution * yResolution)];

							// Check and see if the transparencyData buffer is enabled.
							if (this->transparencyBufferEnabled)
							{
								// Allocate the transparencyData buffer.
								this->transparencyData = new T[(xResolution * yResolution)];
							}

							// Make sure that array was allocated.
							if (this->overlayData != NULL)
							{
								// Fill the array with the blank value.
								for (size_t x = 0; x < (xResolution * yResolution); x++)
								{
									this->overlayData[x] = this->blankValue;
								}

								// Set data values in the overlay.
								this->masterXAxisOffset = xOffset;
								this->masterYAxisOffset = yOffset;
								this->overlayXAxisResolution = xResolution;
								this->overlayYAxisResolution = yResolution;

								// Check and see if the transparencyData buffer is enabled.
								if (this->transparencyBufferEnabled)
								{
									// Make sure the transparencyData buffer was allocated.
									if (this->transparencyData != NULL)
									{
										// Fill the array with the blank value.
										for (size_t x = 0; x < (xResolution * yResolution); x++)
										{
											this->transparencyData[x] = this->blankValue;
										}

										// Set created.
										this->created = true;

										// Set result.
										result = true;
									}
									else
									{
										// Release memory for overlayData.
										if (this->overlayData != NULL)
										{
											delete[] this->overlayData;
											this->overlayData = NULL;
										}

										// Could not allocate memory for overlay transparency data buffer.
										this->lastError = RENDERER_ERROR_UNABLE_TO_ALLOC_TD_BUF;
									}
								}
								else
								{
									// Set created.
									this->created = true;

									// Set result.
									result = true;
								}
							}
							else
							{
								// Could not allocate memory for overlay image buffer.
								this->lastError = RENDERER_ERROR_UNABLE_TO_ALLOC_OI_BUF;
							}
						}
						catch(...)
						{
							// An exception was thrown while attempting to create the overlay.
							this->lastError = RENDERER_ERROR_MEM_BUF_ALLOC_EXCEPTION;

							// Check to see the overlay data image buffer was allocated.
							if (this->overlayData != NULL)
							{
								// Release the overlay data image buffer.
								delete[] this->overlayData;
								this->overlayData = NULL;
							}

							// Check to see the transparency data buffer was allocated.
							if (this->transparencyData != NULL)
							{
								// Release the transparency data buffer.
								delete[] this->transparencyData;
								this->transparencyData = NULL;
							}

							// Blank the other variables.
							this->overlayXAxisResolution = 0;
							this->overlayYAxisResolution = 0;
							this->masterXAxisOffset = 0;
							this->masterYAxisOffset = 0;
						}
					}

					// Exit function.
					return result;
				}

				/*!
				 * 	template<class T>
				 * 	void Common::Renderer::Overlay<T>::Blit(const T * dataArray, const long & startingXoffset, const long & startingYoffset, const size_t & dataXResolution, const size_t & dataYResolution, const bool & lineWrap)
				 *
				 * 	Copies data from an array of the same data type as the overlay's template to the destionation overlay's data buffer.
				 *
				 * 	Pram: const T * dataArray, The array to copy image data from. Must be the same data type as the Overlay's templated data type.
				 * 	Pram: const T * transparencyArray, The array to copy transparency data from. Must be the same data type as the Overlay's templated data type.
				 * 	Pram: const long & startingXoffset, the starting x axis offset in the overlay where data from the given array will be copied to.
				 * 	Pram: const long & startingYoffset, the starting y axis offset in the overlay where data from the given array will be copied to.
				 * 	Pram: const size_t & dataXResolution, the horazontal resolution of the dataArray. (Multiplied with dataYResolution to get the dataArray size.)
				 * 	Pram: const size_t & dataYResolution, the vertical resolution of the dataArray. (Multiplied with dataXResolution to get the dataArray size.)
				 * 	Pram: const bool & lineWrap, if true, any remaining data on the current dataArray line will be blited to the next destionation overlay line if the end of
				 * 	      the current destionation overlay line is reached. Otherwise any remaining data on the current dataArray line not be blited onto the destionation overlay. Defaults to false.
				 */
				void Blit(const T * dataArray, const T * transparencyArray, const long & startingXoffset, const long & startingYoffset, const size_t & dataXAxisResolution, const size_t & dataYAxisResolution, const bool & lineWrap = false)
				{
					// Init vars.
					size_t currentSourceOffset = 0;			// The current offset in the data array.
					size_t currentDestOffset = 0;			// The current offset in the overlay.
					size_t currentSourceXCoordOffset = 0;		// The offset that must be added to the start of a new line in the source data array to align the biltted data.
					size_t currentDestXCoordOffset = 0;		// The offset that must be added to the start of a new line in the overlay to align the biltted data.
					size_t nextSourceEndOfLineOffset = 0;		// The offset where the end of the current line in the data array is located.
					size_t nextDestEndOfLineOffset = 0;		// The offset where the end of the current line in the overlay is located.
					std::stringstream errorText;			// Holds error messages.

#ifndef _NDEBUG
					// Debug the arguments.
					if (this->debugLevel >= ERROR_INFO)
					{
						errorText << "VERBOSE Channel: Overlay::Blit(dataArray): Arguments:\n";
						errorText << "Overlay::Blit(dataArray): dataArray: " << &dataArray << ".\n";
						errorText << "Overlay::Blit(dataArray): transparencyArray: " << &transparencyArray << ".\n";
						errorText << "Overlay::Blit(dataArray): startingXoffset: " << startingXoffset << ".\n";
						errorText << "Overlay::Blit(dataArray): startingYoffset: " << startingYoffset << ".\n";
						errorText << "Overlay::Blit(dataArray): dataXAxisResolution: " << dataXAxisResolution << ".\n";
						errorText << "Overlay::Blit(dataArray): dataYAxisResolution: " << dataYAxisResolution << ".\n";
						errorText << "Overlay::Blit(dataArray): lineWrap: ";
						if (lineWrap)
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_INFO);
						errorText.str(std::string());
					}

					// Debug the object.
					if (this->debugLevel >= ERROR_VERBOSE)
					{
						errorText << "VERBOSE Channel: Overlay::Blit(dataArray): Object data members:\n";
						errorText << "Overlay::Blit(dataArray): masterXAxisOffset: " << this->masterXAxisOffset << ".\n";
						errorText << "Overlay::Blit(dataArray): masterYAxisOffset: " << this->masterYAxisOffset << ".\n";
						errorText << "Overlay::Blit(dataArray): overlayXAxisResolution: " << this->overlayXAxisResolution << ".\n";
						errorText << "Overlay::Blit(dataArray): overlayYAxisResolution: " << this->overlayYAxisResolution << ".\n";
						errorText << "Overlay::Blit(dataArray): overlayData: " << std::hex << &overlayData << std::dec << ".\n";
						errorText << "Overlay::Blit(dataArray): transparencyData: " << std::hex << &transparencyData << std::dec << ".\n";
						errorText << "Overlay::Blit(dataArray): calcTrans: " << std::hex << calcTrans << std::dec << ".\n";
						errorText << "Overlay::Blit(dataArray): lastError: " << this->lastError << ".\n";
						errorText << "Overlay::Blit(dataArray): created: ";
						if (this->created)
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						errorText << "Overlay::Blit(dataArray): transparencyBufferEnabled: ";
						if (this->transparencyBufferEnabled)
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
						errorText.str(std::string());
					}
#endif

					// Make sure we were set up properly.
					if ((this->created) && ((this->overlayXAxisResolution > 0) && (this->overlayYAxisResolution > 0)) && (this->overlayData != NULL))
					{
						// Check for valid pointer.
						if (dataArray != NULL)
						{
							// Make sure the given resolution is not zero.
							if ((dataXAxisResolution > 0) && (dataYAxisResolution > 0))
							{
								// Calculate the starting offsets.
								if (Common::Renderer::Calculate_Offsets_From_Coordnates(startingXoffset, startingYoffset, this->overlayXAxisResolution, this->overlayYAxisResolution,
															dataXAxisResolution, dataYAxisResolution, currentSourceXCoordOffset, currentDestXCoordOffset, currentDestOffset,
															currentSourceOffset, nextDestEndOfLineOffset, nextSourceEndOfLineOffset))
								{
									// Begin blitting loop.
									for (; (currentSourceOffset < (dataXAxisResolution * dataYAxisResolution)) && (currentDestOffset < (this->overlayXAxisResolution * this->overlayYAxisResolution)); currentSourceOffset++)
									{
										/*
										 * 	Note the expected behavior of this process is the following:
										 *
										 * 	This copies data from the current offset in the overlay data to the current offset in the finalImage buffer.
										 * 	the masterXAxisOffset and masterYAxisOffset values are used to determine where to start copying data to with the
										 * 	for loop's currentOverlayOffset value acting as a counter of the amount of data copied.
										 *
										 * 	The main loop allows iterating through each overlay starting at the last overlay and proceeding until we copy the first overlay.
										 *
										 * 	All x values in the main for loop are decremented by one because the last element in a vector is: n - 1, where n is equal to the current amount of elements in the vector.
										 *
										 * 	The reason for this is because the overlay system renders each overlay in reverse.
										 * 	(I.e. For any given overlay that overlay has a lower priority (with regards to visibility) than those that come before it in the overlay system's vector,
										 * 	and that overlay has a higher priority than those that come after it in the overlay system's vector.)
										 *
										 * 	Which means something on a lower priority overlay, at the same position on screen as something at a higher priority overlay, will never be shown on screen.
										 * 	(I.e. The higher priority overlay will "cover up" anything under it.)
										 *
										 * 	To achive this effect, the main for loop must start with the last overlay in the vector and finish with the first overlay in the vector.
										 * 	(Due to the way for loops work (when dealing with decrementing unsigned integers), (at least in gcc), the x value in the main for loop
										 * 	must start at one past the last the last element in the vector and finish when it reaches zero. (Otherwise it results in an indefinite
										 * 	loop because the x value will wrap around to the highest positive value it can hold.) Which nessatates decrementing x by one to access
										 * 	the correct element. (Unless you'd like that segfault to happen..... :P))
										 */

										/*
										 * 	Issue: In order for an image to "scroll" off-screen, we need to be able to depeict an overlay that is not fully on the screen.
										 *
										 * 	Which means we need to do two things:
										 *
										 * 		1. When we reach the end of the current line on the screen, we need to output a newline character.
										 * 		   (This prevents us from distoring the screen via a wrap-around effect, if the set resolution is not correct.
										 * 		    (I.e. Otherwise this would require an image editor to (realign / cut-and-paste different lines on) the
										 * 		     image so it could be viewed properly.))
										 *
										 * 		2. We need to detect where in an overlay a newline starts at, so that when we do reach the end of a
										 * 		   line on the screen, we can skip the data that should not be shown.
										 * 		   (This prevents us from displaying the image incorrectly making it un-recognizable.)
										 *
										 * 		3. We need to continue at the correct horazontal offset on the next line.
										 * 		   (This prevents us from splitting up the image on different sides of the screen.)
										 *
										 * 		How to do this:
										 * 		1. Compute the current screen offset, and if we are at the end of the current line, jump to the next one,
										 * 		   fix the horazontal offset in the screen image, and skip to the next line in the overlay data.
										 * 		   (I.e. currentScreenOffset = ((< Compute offset for start of next screen line >) + overlay.MasterXOffset);
										 * 			 currentOverlayOffset += (< Compute amount of data to skip to next line >);
										 * 		   )
										 *
										 * 		2. Detect newlines in the for loop, if one is found fix the current offset in the screen image. (Jump to the next line
										 * 		   and fix the horazontal offset. (I.e. currentScreenOffset = ((< Compute offset for start of next screen line >) + overlay.MasterXOffset);)
										 *
										 * 		3. Fix the current offset in the screen image. (Jump to the next line
										 * 		   and fix the horazontal offset. (I.e. currentScreenOffset = ((< Compute offset for start of next screen line >) + overlay.MasterXOffset);)
										 *
										 */

										// Check and see if the transparencyData buffer is enabled.
										if (this->transparencyBufferEnabled)
										{
											// Check and see if the transparency function is set and use it if it is. Otherwise do a raw copy, and expect the renderer does something with it.
											if (this->calcTrans != NULL)
											{
												// Call the transparency function.
												(*calcTrans)(dataArray[currentSourceOffset], transparencyArray[currentSourceOffset], this->overlayData[currentDestOffset], this->transparencyData[currentDestOffset]);
											}
											else
											{
												// Copy the image data and continue.
												this->overlayData[currentDestOffset] = dataArray[(currentSourceOffset)];

												// Get the transparency value.
												this->transparencyData[currentDestOffset] = transparencyArray[(currentSourceOffset)];
											}
#ifndef _NDEBUG
											// Only output message if we are in verbose error reporting mode.
											if (this->debugLevel >= ERROR_VERBOSE)
											{
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): overlayData[" << currentDestOffset << "] = " << this->overlayData[currentDestOffset] << "\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): transparencyData[" << currentDestOffset << "] = " << this->transparencyData[currentDestOffset] << "\n";
												Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
												errorText.str(std::string());
											}
#endif
										}
										else
										{
											// Check for a blank value and output the data if it is not one.
											if (dataArray[(currentSourceOffset)] != this->blankValue)
											{
												// Not a blank value, so copy the data and continue.
												this->overlayData[currentDestOffset] = dataArray[(currentSourceOffset)];
#ifndef _NDEBUG
												// Only output message if we are in verbose error reporting mode.
												if (this->debugLevel >= ERROR_VERBOSE)
												{
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): overlayData[" << currentDestOffset << "] = " << this->overlayData[currentDestOffset] << "\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): transparencyData[" << currentDestOffset << "] = " << this->transparencyData[currentDestOffset] << "\n";
													Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
													errorText.str(std::string());
												}
#endif
											}
										}

										// Check to see if we have reached the end of the current line in the overlay data. (current position % (overlay horazontal resolution - 1)) will equal 0 if we are at the end of that line.
										if (currentSourceOffset == nextSourceEndOfLineOffset)
										{
#ifndef _NDEBUG
											// Only output message if we are in verbose error reporting mode.
											if (this->debugLevel >= ERROR_VERBOSE)
											{
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentSourceOffset before end of data line jump: " << currentSourceOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentDestOffset before end of data line jump: " << currentDestOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextSourceEndOfLineOffset before end of data line jump: " << nextSourceEndOfLineOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextDestEndOfLineOffset before end of data line jump: " << nextDestEndOfLineOffset << ".\n";
												Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
												errorText.str(std::string());
											}
#endif

											// Check and see if we have already moved to the next line in the final image.
											if (currentDestOffset < nextDestEndOfLineOffset)
											{
												// We have hit a newline in the overlay data, so we need to jump to the next line and offset in the final image. (One is added at the end of the loop, no need to add it here.)
												currentDestOffset += ((nextDestEndOfLineOffset - currentDestOffset) + currentDestXCoordOffset);

												// Calculate new nextDestEndOfLineOffset.
												nextDestEndOfLineOffset += this->overlayXAxisResolution;
											}
											else
											{
												// Check if we are at the end of the current Screen line.
												if (currentDestOffset == nextDestEndOfLineOffset)
												{
													// Jump to the correct offset. (One is added at the end of the loop, no need to add it here.)
													currentDestOffset += currentDestXCoordOffset;

													// Calculate new nextDestEndOfLineOffset.
													nextDestEndOfLineOffset += this->overlayXAxisResolution;
												}
											}

											// Calculate the nextSourceEndOfLineOffset.
											nextSourceEndOfLineOffset += dataXAxisResolution;

											// Jump the current source offset forward by the offset amount.
											currentSourceOffset += currentSourceXCoordOffset;
#ifndef _NDEBUG
											// Only output message if we are in verbose error reporting mode.
											if (this->debugLevel >= ERROR_VERBOSE)
											{
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentSourceOffset after end of data line jump: " << currentSourceOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentDestOffset after end of data line jump: " << currentDestOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextSourceEndOfLineOffset after end of data line jump: " << nextSourceEndOfLineOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextDestEndOfLineOffset after end of data line jump: " << nextDestEndOfLineOffset << ".\n";
												Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
												errorText.str(std::string());
											}
#endif

											// DO NOT OUTPUT THE NEWLINE CHARACTER IN THE OVERLAY DATA!
										}
										else
										{
											// Check and see if we are at the end of the current line on the overlay. (current position % (screen horazontal resolution - 1)) will equal 0 if we are at the end of that line.
											if (currentDestOffset == nextDestEndOfLineOffset)
											{
#ifndef _NDEBUG
												// Only output message if we are in verbose error reporting mode.
												if (this->debugLevel >= ERROR_VERBOSE)
												{
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentSourceOffset before end of overlay line jump: " << currentSourceOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentDestOffset before end of overlay line jump: " << currentDestOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextSourceEndOfLineOffset before end of overlay line jump: " << nextSourceEndOfLineOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextDestEndOfLineOffset before end of overlay line jump: " << nextDestEndOfLineOffset << ".\n";
													Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
													errorText.str(std::string());
												}
#endif

												// We've reached the end of the current line on the overlay, calculate new nextDestEndOfLineOffset.
												nextDestEndOfLineOffset += this->overlayXAxisResolution;

												// Because we reached the end of the overlay line, we need to skip forward until we reach the next line in the data array.
												// First, check and see if we have already reached the next line in the data array.
												if (currentSourceOffset < nextSourceEndOfLineOffset)
												{
													// Only jump forward if lineWrap is false.
													if (!lineWrap)
													{
														/*
														 * Determine how much more to add to the current data offset to reach the next line in the data array.
														 *
														 * This is done by subtracting the currentSourceOffset from the nextSourceEndOfLineOffset.
														 *
														 * The result of that is the amount of elements in the array we need to add to the current offset, to reach the next line
														 * in the data array.
														 */
														currentSourceOffset += (nextSourceEndOfLineOffset - currentSourceOffset);

														// Calculate new nextSourceEndOfLineOffset.
														nextSourceEndOfLineOffset += dataXAxisResolution;
													}
												}
												else
												{
													// Check to see if we are at the end of the current line in the data array.
													if (currentSourceOffset == nextSourceEndOfLineOffset)
													{
														// Calculate new nextSourceEndOfLineOffset.
														nextSourceEndOfLineOffset += dataXAxisResolution;
													}
												}

												// Jump the current source offset forward by the offset amount.
												currentSourceOffset += currentSourceXCoordOffset;
#ifndef _NDEBUG
												// Only output message if we are in verbose error reporting mode.
												if (this->debugLevel >= ERROR_VERBOSE)
												{
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentSourceOffset after end of overlay line jump: " << currentSourceOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): currentDestOffset after end of overlay line jump: " << currentDestOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextSourceEndOfLineOffset after end of overlay line jump: " << nextSourceEndOfLineOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(dataArray): nextDestEndOfLineOffset after end of overlay line jump: " << nextDestEndOfLineOffset << ".\n";
													Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
													errorText.str(std::string());
												}
#endif

											}
										}

										// Increment the currentDestOffset.
										currentDestOffset++;
									}
								}
							}
#ifndef _NDEBUG
							else
							{
								// Only output an error message if we are actually outputing error messages.
								if (this->debugLevel >= ERROR_WARNING)
								{
									errorText << "DEBUG Channel: Overlay::Blit(dataArray): Invalid dataArray resolution: " << dataXAxisResolution << 'x' << dataYAxisResolution << ". Resolution must be greater than zero, aborting with no changes to overlay data.\n";
									Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_WARNING);
									errorText.str(std::string());
								}
							}
#endif
						}
					}

#ifndef _NDEBUG
					else
					{
						// Only output message if we are in verbose error reporting mode.
						if (this->debugLevel >= ERROR_VERBOSE)
						{
							// We were not setup properly, abort.
							errorText << "DEBUG Channel: Overlay::Blit(dataArray): Destination overlay is invalid, memory buffer and / or dimentions not setup correctly.";
							Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
							errorText.str(std::string());
						}
					}
#endif

					// Reset this->lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Exit function.
					return;
				}

				/*!
				 * 	template<class T>
				 * 	void Common::Renderer::Overlay<T>::Blit(const Overlay<T> & data, const long & startingXoffset, const long & startingYoffset, const bool & lineWrap)
				 *
				 * 	Copies data from an overlay of the same data type as the overlay's template data type to the overlay's data buffer.
				 *
				 * 	Pram: const Overlay<T> & data, The overlay to copy data from.
				 * 	Pram: const long & startingXoffset, the starting x axis offset in the overlay where data from the given overlay will be copied to. Defaults to the overlay origin point.
				 * 	Pram: const long & startingYoffset, the starting y axis offset in the overlay where data from the given overlay will be copied to. Defaults to the overlay origin point.
				 * 	Pram: const bool & lineWrap, if true, any remaining data on the current source overlay line will be blited to the next memory buffer line if the end of
				 * 	      the current memory buffer line is reached. Otherwise any remaining data on the current source overlay line will not be blited into the destionation overlay's buffer. Defaults to false.
				 */
				void Blit(const Overlay<T> & data, const long & startingXoffset = 0, const long & startingYoffset = 0, const bool & lineWrap = false)
				{
					// Init vars.
					size_t currentSourceOffset = 0;			// The current offset in the source overlay.
					size_t currentDestOffset = 0;			// The current offset in our memory buffer.
					size_t currentSourceXCoordOffset = 0;		// The offset that must be added to the start of a new line in the source overlay to align the biltted data.
					size_t currentDestXCoordOffset = 0;		// The offset that must be added to the start of a new line in the overlay to align the biltted data.
					size_t nextSourceEndOfLineOffset = 0;		// The offset where the end of the current line in the source overlay is located.
					size_t nextDestEndOfLineOffset = 0;		// The offset where the end of the current line in our memory buffer is located.
					size_t dataXAxisResolution = 0;			// The source overlay's x axis resolution.
					size_t dataYAxisResolution = 0;			// The source overlay's y axis resolution.
					const T * dataArray = NULL;			// Pointer to the source overlay's image data buffer.
					const T * transparencyArray = NULL;		// Pointer to the source overlay's transparency data buffer.
					T sourceBlankValue = data.Get_Blank_Value();	// Holds a copy of the source overlay's blank value.
					std::stringstream errorText;			// Holds error messages.

					// Get the source overlay's resolution.
					data.Get_Resolution(dataXAxisResolution, dataYAxisResolution);
#ifndef _NDEBUG
					// Debug the arguments.
					if (this->debugLevel >= ERROR_INFO)
					{
						errorText << "VERBOSE Channel: Overlay::Blit(Overlay): Arguments:\n";
						errorText << "Overlay::Blit(Overlay): data: " << &data << ".\n";
						errorText << "Overlay::Blit(Overlay): startingXoffset: " << startingXoffset << ".\n";
						errorText << "Overlay::Blit(Overlay): startingYoffset: " << startingYoffset << ".\n";
						errorText << "Overlay::Blit(Overlay): dataXAxisResolution: " << dataXAxisResolution << ".\n";
						errorText << "Overlay::Blit(Overlay): dataYAxisResolution: " << dataYAxisResolution << ".\n";
						errorText << "Overlay::Blit(Overlay): lineWrap: ";
						if (lineWrap)
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_INFO);
						errorText.str(std::string());
					}

					// Debug the object.
					if (this->debugLevel >= ERROR_VERBOSE)
					{
						errorText << "VERBOSE Channel: Overlay::Blit(Overlay): Object data members:\n";
						errorText << "Overlay::Blit(Overlay): masterXAxisOffset: " << this->masterXAxisOffset << ".\n";
						errorText << "Overlay::Blit(Overlay): masterYAxisOffset: " << this->masterYAxisOffset << ".\n";
						errorText << "Overlay::Blit(Overlay): overlayXAxisResolution: " << this->overlayXAxisResolution << ".\n";
						errorText << "Overlay::Blit(Overlay): overlayYAxisResolution: " << this->overlayYAxisResolution << ".\n";
						errorText << "Overlay::Blit(Overlay): overlayData: " << std::hex << &overlayData << std::dec << ".\n";
						errorText << "Overlay::Blit(Overlay): transparencyData: " << std::hex << &transparencyData << std::dec << ".\n";
						errorText << "Overlay::Blit(Overlay): calcTrans: " << std::hex << calcTrans << std::dec << ".\n";
						errorText << "Overlay::Blit(Overlay): lastError: " << this->lastError << ".\n";
						errorText << "Overlay::Blit(Overlay): created: ";
						if (this->created)
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						errorText << "Overlay::Blit(Overlay): Source Overlay transparencyBufferEnabled: ";
						if (data.is_Transparency_Buffer_Enabled())
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						errorText << "Overlay::Blit(Overlay): Destination Overlay transparencyBufferEnabled: ";
						if (this->transparencyBufferEnabled)
						{
							errorText << "True";
						}
						else
						{
							errorText << "False";
						}
						errorText << ".\n";
						if (data.is_Transparency_Buffer_Enabled() != this->transparencyBufferEnabled)
						{
							errorText << "WARNING: Attempting to blit overlays when one overlay uses a transparency data buffer and the other does not.\n";
							errorText << "The result will probably NOT be what you were expecting.\n";
						}
						Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
						errorText.str(std::string());
					}
#endif

					// Make sure we were set up properly.
					if ((this->created) && ((this->overlayXAxisResolution > 0) && (this->overlayYAxisResolution > 0)) && (this->overlayData != NULL))
					{
						// Make sure that the source overlay's resolution is valid.
						if ((dataXAxisResolution > 0) && (dataYAxisResolution > 0))
						{
							// Get the source overlay's data pointers.
							dataArray = data.Get_Overlay_Data();

							// Get the transparencyArray pointer if transparencies are enabled.
							if (data.is_Transparency_Buffer_Enabled())
							{
								transparencyArray = data.Get_Transparency_Data();
							}

							// Make sure that the pointers are valid.
							if ((dataArray != NULL) && (((data.is_Transparency_Buffer_Enabled()) && (transparencyArray != NULL)) || ((!data.is_Transparency_Buffer_Enabled()) && (transparencyArray == NULL))))
							{
								// Calculate the starting offsets.
								if (Common::Renderer::Calculate_Offsets_From_Coordnates(startingXoffset, startingYoffset, this->overlayXAxisResolution, this->overlayYAxisResolution,
															dataXAxisResolution, dataYAxisResolution, currentSourceXCoordOffset, currentDestXCoordOffset, currentDestOffset,
															currentSourceOffset, nextDestEndOfLineOffset, nextSourceEndOfLineOffset))
								{
									// Begin blitting loop.
									for (; (currentSourceOffset < (dataXAxisResolution * dataYAxisResolution)) && (currentDestOffset < (this->overlayXAxisResolution * this->overlayYAxisResolution)); currentSourceOffset++)
									{
										/*
										 * 	Note the expected behavior of this process is the following:
										 *
										 * 	This copies data from the current offset in the overlay data to the current offset in the finalImage buffer.
										 * 	the masterXAxisOffset and masterYAxisOffset values are used to determine where to start copying data to with the
										 * 	for loop's currentOverlayOffset value acting as a counter of the amount of data copied.
										 *
										 * 	The main loop allows iterating through each overlay starting at the last overlay and proceeding until we copy the first overlay.
										 *
										 * 	All x values in the main for loop are decremented by one because the last element in a vector is: n - 1, where n is equal to the current amount of elements in the vector.
										 *
										 * 	The reason for this is because the overlay system renders each overlay in reverse.
										 * 	(I.e. For any given overlay that overlay has a lower priority (with regards to visibility) than those that come before it in the overlay system's vector,
										 * 	and that overlay has a higher priority than those that come after it in the overlay system's vector.)
										 *
										 * 	Which means something on a lower priority overlay, at the same position on screen as something at a higher priority overlay, will never be shown on screen.
										 * 	(I.e. The higher priority overlay will "cover up" anything under it.)
										 *
										 * 	To achive this effect, the main for loop must start with the last overlay in the vector and finish with the first overlay in the vector.
										 * 	(Due to the way for loops work (when dealing with decrementing unsigned integers), (at least in gcc), the x value in the main for loop
										 * 	must start at one past the last the last element in the vector and finish when it reaches zero. (Otherwise it results in an indefinite
										 * 	loop because the x value will wrap around to the highest positive value it can hold.) Which nessatates decrementing x by one to access
										 * 	the correct element. (Unless you'd like that segfault to happen..... :P))
										 */

										/*
										 * 	Issue: In order for an image to "scroll" off-screen, we need to be able to depeict an overlay that is not fully on the screen.
										 *
										 * 	Which means we need to do two things:
										 *
										 * 		1. When we reach the end of the current line on the screen, we need to output a newline character.
										 * 		   (This prevents us from distoring the screen via a wrap-around effect, if the set resolution is not correct.
										 * 		    (I.e. Otherwise this would require an image editor to (realign / cut-and-paste different lines on) the
										 * 		     image so it could be viewed properly.))
										 *
										 * 		2. We need to detect where in an overlay a newline starts at, so that when we do reach the end of a
										 * 		   line on the screen, we can skip the data that should not be shown.
										 * 		   (This prevents us from displaying the image incorrectly making it un-recognizable.)
										 *
										 * 		3. We need to continue at the correct horazontal offset on the next line.
										 * 		   (This prevents us from splitting up the image on different sides of the screen.)
										 *
										 * 		How to do this:
										 * 		1. Compute the current screen offset, and if we are at the end of the current line, jump to the next one,
										 * 		   fix the horazontal offset in the screen image, and skip to the next line in the overlay data.
										 * 		   (I.e. currentScreenOffset = ((< Compute offset for start of next screen line >) + overlay.MasterXOffset);
										 * 			 currentOverlayOffset += (< Compute amount of data to skip to next line >);
										 * 		   )
										 *
										 * 		2. Detect newlines in the for loop, if one is found fix the current offset in the screen image. (Jump to the next line
										 * 		   and fix the horazontal offset. (I.e. currentScreenOffset = ((< Compute offset for start of next screen line >) + overlay.MasterXOffset);)
										 *
										 * 		3. Fix the current offset in the screen image. (Jump to the next line
										 * 		   and fix the horazontal offset. (I.e. currentScreenOffset = ((< Compute offset for start of next screen line >) + overlay.MasterXOffset);)
										 *
										 */

										// Check and see if the transparencyData buffers are enabled.
										if ((this->transparencyBufferEnabled) && (data.is_Transparency_Buffer_Enabled()))
										{
											// Check and see if the transparency function is set and use it if it is. Otherwise do a raw copy, and expect the renderer does something with it.
											if (this->calcTrans != NULL)
											{
												// Call the transparency function.
												(*calcTrans)(dataArray[currentSourceOffset], transparencyArray[currentSourceOffset], this->overlayData[currentDestOffset], this->transparencyData[currentDestOffset]);
											}
											else
											{
												// Copy the image data and continue.
												this->overlayData[currentDestOffset] = dataArray[(currentSourceOffset)];

												// Get the transparency value.
												this->transparencyData[currentDestOffset] = transparencyArray[(currentSourceOffset)];
											}
#ifndef _NDEBUG
											// Only output message if we are in verbose error reporting mode.
											if (this->debugLevel >= ERROR_VERBOSE)
											{
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): overlayData[" << currentDestOffset << "] = " << this->overlayData[currentDestOffset] << "\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): transparencyData[" << currentDestOffset << "] = " << this->transparencyData[currentDestOffset] << "\n";
												Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
												errorText.str(std::string());
											}
#endif
										}
										else
										{
											// Check for a blank value and output the data if it is not one.
											if (dataArray[(currentSourceOffset)] != this->blankValue)
											{
												// Not a blank value, so copy the data and continue.
												this->overlayData[currentDestOffset] = dataArray[(currentSourceOffset)];
#ifndef _NDEBUG
												// Only output message if we are in verbose error reporting mode.
												if (debugLevel >= ERROR_VERBOSE)
												{
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): overlayData[" << currentDestOffset << "] = " << this->overlayData[currentDestOffset] << "\n";
													Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
													errorText.str(std::string());
												}
#endif
											}
										}

										// Check to see if we have reached the end of the current line in the overlay data. (current position % (overlay horazontal resolution - 1)) will equal 0 if we are at the end of that line.
										if (currentSourceOffset == nextSourceEndOfLineOffset)
										{
#ifndef _NDEBUG
											// Debugging output for the calculations.
											if (this->debugLevel >= ERROR_VERBOSE)
											{
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentSourceOffset before end of data line jump: " << currentSourceOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentDestOffset before end of data line jump: " << currentDestOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextSourceEndOfLineOffset before end of data line jump: " << nextSourceEndOfLineOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextDestEndOfLineOffset before end of data line jump: " << nextDestEndOfLineOffset << ".\n";
												Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
												errorText.str(std::string());
											}
#endif

											// Check and see if we have already moved to the next line in the final image.
											if (currentDestOffset < nextDestEndOfLineOffset)
											{
												// We have hit a newline in the overlay data, so we need to jump to the next line and offset in the final image. (One is added at the end of the loop, no need to add it here.)
												currentDestOffset += ((nextDestEndOfLineOffset - currentDestOffset) + currentDestXCoordOffset);

												// Calculate new nextDestEndOfLineOffset.
												nextDestEndOfLineOffset += this->overlayXAxisResolution;
											}
											else
											{
												// Check if we are at the end of the current Screen line.
												if (currentDestOffset == nextDestEndOfLineOffset)
												{
													// Jump to the correct offset. (One is added at the end of the loop, no need to add it here.)
													currentDestOffset += currentDestXCoordOffset;

													// Calculate new nextDestEndOfLineOffset.
													nextDestEndOfLineOffset += this->overlayXAxisResolution;
												}
											}

											// Calculate the nextSourceEndOfLineOffset.
											nextSourceEndOfLineOffset += dataXAxisResolution;

											// Jump the current source offset forward by the offset amount.
											currentSourceOffset += currentSourceXCoordOffset;

#ifndef _NDEBUG
											// Debugging output for the calculations.
											if (this->debugLevel >= ERROR_VERBOSE)
											{
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentSourceOffset after end of data line jump: " << currentSourceOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentDestOffset after end of data line jump: " << currentDestOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextSourceEndOfLineOffset after end of data line jump: " << nextSourceEndOfLineOffset << ".\n";
												errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextDestEndOfLineOffset after end of data line jump: " << nextDestEndOfLineOffset << ".\n";
												Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
												errorText.str(std::string());
											}
#endif

											// DO NOT OUTPUT THE NEWLINE CHARACTER IN THE OVERLAY DATA!
										}
										else
										{
											// Check and see if we are at the end of the current line on the overlay. (current position % (screen horazontal resolution - 1)) will equal 0 if we are at the end of that line.
											if (currentDestOffset == nextDestEndOfLineOffset)
											{
#ifndef _NDEBUG
												// Only output message if we are in verbose error reporting mode.
												if (this->debugLevel >= ERROR_VERBOSE)
												{
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentSourceOffset before end of overlay line jump: " << currentSourceOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentDestOffset before end of overlay line jump: " << currentDestOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextSourceEndOfLineOffset before end of overlay line jump: " << nextSourceEndOfLineOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextDestEndOfLineOffset before end of overlay line jump: " << nextDestEndOfLineOffset << ".\n";
													Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
													errorText.str(std::string());
												}
#endif

												// Jump currentDestOffset forward by the data's masterXAxisOffset. (One is added at the end of the loop, no need to add it here.)
												currentDestOffset += currentDestXCoordOffset;

												// Calculate new nextDestEndOfLineOffset.
												nextDestEndOfLineOffset += this->overlayXAxisResolution;

												// Because we reached the end of the overlay line, we need to skip forward until we reach the next line in the data array.
												// First, check and see if we have already reached the next line in the data array.
												if (currentSourceOffset < nextSourceEndOfLineOffset)
												{
													// Only jump forward if lineWrap is false.
													if (!lineWrap)
													{
														/*
														 * Determine how much more to add to the current data offset to reach the next line in the data array.
														 *
														 * This is done by subtracting the currentSourceOffset from the nextSourceEndOfLineOffset.
														 *
														 * The result of that is the amount of elements in the array we need to add to the current offset, to reach the next line
														 * in the data array.
														 */
														currentSourceOffset += (nextSourceEndOfLineOffset - currentSourceOffset);

														// Calculate new nextSourceEndOfLineOffset.
														nextSourceEndOfLineOffset += dataXAxisResolution;
													}
												}
												else
												{
													// Check to see if we are at the end of the current line in the data array.
													if (currentSourceOffset == nextSourceEndOfLineOffset)
													{
														// Calculate new nextSourceEndOfLineOffset.
														nextSourceEndOfLineOffset += dataXAxisResolution;
													}
												}

												// Jump the current source offset forward by the offset amount.
												currentSourceOffset += currentSourceXCoordOffset;
#ifndef _NDEBUG
												// Only output message if we are in verbose error reporting mode.
												if (this->debugLevel >= ERROR_VERBOSE)
												{
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentSourceOffset after end of overlay line jump: " << currentSourceOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): currentDestOffset after end of overlay line jump: " << currentDestOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextSourceEndOfLineOffset after end of overlay line jump: " << nextSourceEndOfLineOffset << ".\n";
													errorText << "DEBUG Channel: Overlay::Blit(Overlay): nextDestEndOfLineOffset after end of overlay line jump: " << nextDestEndOfLineOffset << ".\n";
													Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
													errorText.str(std::string());
												}
#endif

											}
										}

										// Increment the currentDestOffset.
										currentDestOffset++;
									}
								}
#ifndef _NDEBUG
								else
								{
									// Source is outside of this overlay's bounds, or a calculation error occured.
									if (this->debugLevel >= ERROR_VERBOSE)
									{
										errorText << "DEBUG Channel: Overlay::Blit(Overlay): Source is outside of this overlay's bounds, or a calculation error occured.";
										Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
										errorText.str(std::string());
									}
								}
#endif
							}
#ifndef _NDEBUG
							else
							{
								if (this->debugLevel >= ERROR_WARNING)
								{
									// Could not get pointer to source overlay's data buffer.
									Common::Renderer::DebugChannel.PanicHandler("DEBUG Channel: Overlay::Blit(Overlay): Could not get pointer to source overlay's data buffer, exiting function without altering destionation overlay.\n", COMMON_ID, ERROR_WARNING);
								}
							}
#endif
						}
#ifndef _NDEBUG
						else
						{
							// Only output message if we are in verbose error reporting mode.
							if (this->debugLevel >= ERROR_VERBOSE)
							{
								errorText << "DEBUG Channel: Overlay::Blit(Overlay): Invalid source overlay resolution: " << dataXAxisResolution << 'x' << dataYAxisResolution << ". Resolution must be greater than zero, aborting with no changes to destionation overlay data.\n";
								Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
								errorText.str(std::string());
							}
						}
#endif
					}
#ifndef _NDEBUG
					else
					{
						// Only output message if we are in verbose error reporting mode.
						if (this->debugLevel >= ERROR_VERBOSE)
						{
							// We were not setup properly, abort.
							errorText << "DEBUG Channel: Overlay::Blit(Overlay): Destination overlay is invalid, memory buffer and / or dimentions not setup correctly.";
							Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);
							errorText.str(std::string());
						}
					}
#endif
					// Reset this->lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Exit function.
					return;
				}

				/*!
				 * 	template<class A>
				 * 	void Common::Renderer::Overlay<T>::Blit(const Overlay<A> & data, const long & startingXoffset, const long & startingYoffset)
				 *
				 * 	Copies data from an overlay of a different data type than the overlay's template data type to the overlay's data buffer. See note below about the required function template specialisation.
				 *
				 * 	Pram: const Overlay<A> & data, The overlay to copy data from. A template specialisation must exist for the Get_Overlay_Data() and Get_Blank_Value() functions to convert the data from the source overlay's data type.
				 * 	Pram: const size_t & startingXoffset, the starting x axis offset in the overlay where data from the given overlay will be copied to. Defaults to the overlay origin point.
				 * 	Pram: const size_t & startingYoffset, the starting y axis offset in the overlay where data from the given overlay will be copied to. Defaults to the overlay origin point.
				 */

				/*!
				 * 	void Common::Renderer::Overlay<T>::Clear_Overlay_Data()
				 *
				 * 	Fills the overlay's memory buffers with the overlay's current blank value.
				 *
				 * 	This function has no return.
				 */
				void Clear_Overlay_Data()
				{
					// Check and see if the Create_Overlay() function has been run at least once.
					if (this->created)
					{
						// Make sure we have a buffer to clear.
						if ((this->overlayData != NULL) && (this->overlayXAxisResolution > 0) && (this->overlayYAxisResolution > 0))
						{
							// Fill the array with the blank character.
							for (size_t x = 0; x < (this->overlayXAxisResolution * this->overlayYAxisResolution); x++)
							{
								this->overlayData[x] = this->blankValue;
							}
						}
						if ((this->transparencyBufferEnabled) && (this->transparencyData != NULL) && (this->overlayXAxisResolution > 0) && (this->overlayYAxisResolution > 0))
						{
							// Fill the array with the blank character.
							for (size_t x = 0; x < (this->overlayXAxisResolution * this->overlayYAxisResolution); x++)
							{
								this->transparencyData[x] = this->blankValue;
							}
						}
					}

					// Reset this->lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Exit function.
					return;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Reset_Overlay()
				 *
				 * 	Deallocates any allocated memory buffers, and sets the overlay back to it's default state.
				 * 	WARNING: This DOES set the transparency calculation function pointer to NULL.
				 */
				void Reset_Overlay()
				{
					// Check and see if the overlay data buffer is allocated.
					if (this->overlayData != NULL)
					{
						// Delete the old buffer.
						delete[] this->overlayData;
						this->overlayData = NULL;
					}

					// Check and see if the transparency data buffer is allocated.
					if (this->transparencyData != NULL)
					{
						// Delete the old buffer.
						delete[] this->transparencyData;
						this->transparencyData = NULL;
					}

					// Reset the remaining variables.
					this->transparencyBufferEnabled = false;
					this->calcTrans = NULL;
					this->lastError = COMMON_ERROR_SUCCESS;
					this->debugLevel = 0;
					Common::Renderer::DebugChannel.change_log_level(this->debugLevel);
					this->masterXAxisOffset = 0;
					this->masterYAxisOffset = 0;
					this->overlayXAxisResolution = 0;
					this->overlayYAxisResolution = 0;

					// Exit function.
					return;
				}

				/*!
				 * 	bool Common::Renderer::Overlay<T>::Change_Resolution(const size_t & newXResolution, const size_t & newYResolution)
				 *
				 * 	Changes the resolution of the overlay to the given resolution.
				 *
				 * 	Returns true if the resolution change / buffer reallocation is successfull.
				 * 	Returns false otherwise. (Error code will be set in this case.)
				 */
				bool Change_Resolution(const size_t & newXResolution, const size_t & newYResolution)
				{
					// Init result.
					bool result = false;		// The result of this function.

					// Reset this->lastError.
					this->lastError = COMMON_ERROR_SUCCESS;

					// Check and see if Create_Overlay() has been run at least once.
					if (this->created)
					{
						// Check to see if we need to release the previous buffers.
						if (this->overlayData != NULL)
						{
							// Delete the old buffer.
							delete[] this->overlayData;
							this->overlayData = NULL;
						}
						if (this->transparencyData != NULL)
						{
							// Delete the old buffer.
							delete[] this->transparencyData;
							this->transparencyData = NULL;
						}

						// Blank the overlay data members.
						this->overlayXAxisResolution = 0;
						this->overlayYAxisResolution = 0;

						// Begin try block.
						try{
							// Allocate new memory. (Array length is the product of the xScreenResolution and yScreenResolution arguments.)
							this->overlayData = new T[(newXResolution * newYResolution)];

							// Check and see if the transparencyData buffer is enabled.
							if (this->transparencyBufferEnabled)
							{
								// Allocate transparencyData buffer.
								this->transparencyData = new T[(newXResolution * newYResolution)];
							}

							// Check that the buffer was allocated.
							if (this->overlayData != NULL)
							{
								// Fill the array with the blank character.
								for (size_t x = 0; x < (newXResolution * newYResolution); x++)
								{
									this->overlayData[x] = this->blankValue;
								}

								// Set new resolution values in the overlay.
								this->overlayXAxisResolution = newXResolution;
								this->overlayYAxisResolution = newYResolution;

								// Check and see if the transparencyData buffer is enabled.
								if (this->transparencyBufferEnabled)
								{
									// Make sure the transparencyData buffer was allocated.
									if (this->transparencyData != NULL)
									{
										// Fill the array with the blank value.
										for (size_t x = 0; x < (newXResolution * newYResolution); x++)
										{
											this->transparencyData[x] = this->blankValue;
										}

										// Set result.
										result = true;
									}
									else
									{
										// Release memory for overlayData.
										if (this->overlayData != NULL)
										{
											delete[] this->overlayData;
											this->overlayData = NULL;
										}

										// Could not allocate memory for the transparencyData buffer.
										this->lastError = RENDERER_ERROR_UNABLE_TO_ALLOC_TD_BUF;
									}
								}
								else
								{
									// Set result.
									result = true;
								}
							}
							else
							{
								// Could not allocate memory for overlay image buffer.
								this->lastError = RENDERER_ERROR_UNABLE_TO_ALLOC_OI_BUF;
							}
						}
						catch(...)
						{
							// An exception was thrown while attempting to create the overlay.
							this->lastError = RENDERER_ERROR_MEM_BUF_ALLOC_EXCEPTION;

							// Check to see the overlay data image buffer was allocated.
							if (this->overlayData != NULL)
							{
								// Delete the old buffer.
								delete[] this->overlayData;
								this->overlayData = NULL;
							}

							// Check to see the transparency data buffer was allocated.
							if (this->transparencyData != NULL)
							{
								// Release the transparency data buffer.
								delete[] this->transparencyData;
								this->transparencyData = NULL;
							}

							// Blank the resolution sizes.
							this->overlayXAxisResolution = 0;
							this->overlayYAxisResolution = 0;
						}
					}

					// Exit function.
					return result;
				}

				/*!
				 * 	bool Common::Renderer::Overlay<T>::Swap_Overlays(Common::Renderer::Overlay<T> & src)
				 *
				 * 	Swaps the data members of the source overlay with this one.
				 *
				 * 	Note: This does not reallocate the memory buffers, it only swaps the pointers.
				 *
				 * 	If the source overlay is the same as the destionation overlay, then this function will fail.
				 * 	(An error code will be set in the destionation overlay.
				 * 	 The destionation overlay is the one whose Swap_Overlays() function was called.)
				 *
				 * 	Returns true if the swap was successfull.
				 * 	Returns false otherwise.
				 */
				bool Swap_Overlays(Common::Renderer::Overlay<T> & src)
				{
					// Init vars.
					bool result = false;					// The result of this function.
					bool temp_bool = false;					// Temporary variable used to hold a bool value while the original one is overwritten.
					size_t temp_size = 0;					// Temporary variable used to hold a size value while the original one is overwritten.
					void (*temp_fptr)(const T&, const T&, T&, T&) = NULL;	// Temporary variable used to hold a function pointer while the original one is overwritten.
					T * temp_data = NULL;					// Temporary variable used to hold a pointer while the original one is overwritten.
					T temp_blank = this->blankValue;			// Temporary variable used to hold a blank value while the original one is overwritten.

					// Prevent self-assignment.
					if (this != &src)
					{
						// Reset this->lastError.
						this->lastError = COMMON_ERROR_SUCCESS;

						// Swap the created flags.
						temp_bool = this->created;
						this->created = src.created;
						src.created = temp_bool;
						temp_bool = false;

						// Swap the transparencyBufferEnabled flags.
						temp_bool = this->transparencyBufferEnabled;
						this->transparencyBufferEnabled = src.transparencyBufferEnabled;
						src.transparencyBufferEnabled = temp_bool;
						temp_bool = false;

						// Swap the blank value.
						this->blankValue = src.blankValue;
						src.blankValue = temp_blank;

						// Swap the transparency calculation function pointer.
						temp_fptr = this->calcTrans;
						this->calcTrans = src.calcTrans;
						src.calcTrans = temp_fptr;
						temp_fptr = NULL;

						// Swap the masterXAxisOffset.
						temp_size = this->masterXAxisOffset;
						this->masterXAxisOffset = src.masterXAxisOffset;
						src.masterXAxisOffset = temp_size;
						temp_size = 0;

						// Swap the masterYAxisOffset.
						temp_size = this->masterYAxisOffset;
						this->masterYAxisOffset = src.masterYAxisOffset;
						src.masterYAxisOffset = temp_size;
						temp_size = 0;

						// Swap the overlayXAxisResolution.
						temp_size = this->overlayXAxisResolution;
						this->overlayXAxisResolution = src.overlayXAxisResolution;
						src.overlayXAxisResolution = temp_size;
						temp_size = 0;

						// Swap the overlayYAxisResolution.
						temp_size = this->overlayYAxisResolution;
						this->overlayYAxisResolution = src.overlayYAxisResolution;
						src.overlayYAxisResolution = temp_size;
						temp_size = 0;

						// Swap the overlay data pointers.
						temp_data = this->overlayData;
						this->overlayData = src.overlayData;
						src.overlayData = temp_data;
						temp_data = NULL;

						// Swap the transparency data pointers.
						temp_data = this->transparencyData;
						this->transparencyData = src.transparencyData;
						src.transparencyData = temp_data;
						temp_data = NULL;

						// Set result.
						result = true;
					}
					else
					{
						// We are the given overlay, cannot do self assignment.
						this->lastError = RENDERER_ERROR_INVAL_OVERLAY_SELF_OVERWRITE;
					}

					// Return the result.
					return result;
				}

				/*!
				 * 	bool Common::Renderer::Overlay<T>::Duplicate_Overlay(const Common::Renderer::Overlay<T> & src)
				 *
				 * 	Overwrites this overlay's data with the data from the source.
				 *
				 * 	Note: This is a deep copy function.
				 * 	(I.e. This function can reallocate this overlay's memory buffers,
				 * 	      if they are not the same size as the source overlay's memory buffers.)
				 *
				 * 	Note: If the source overlay is the same as the destionation overlay, then this function will fail.
				 *	(An error code will be set in the destionation overlay.
				 * 	 The destionation overlay is the one whose Duplicate_Overlay() function was called.)
				 *
				 * 	Returns true if the source overlay's data was successfully copied.
				 * 	Returns false otherwise. (Overlay's error code will be set in this case.)
				 */
				bool Duplicate_Overlay(const Common::Renderer::Overlay<T> & src)
				{
					// Init result.
					bool result = false;

					// Prevent duplicating ourselves.
					if (this != &src)
					{
						// Reset this->lastError.
						this->lastError = COMMON_ERROR_SUCCESS;

						// Copy the created flag of the source overlay.
						this->created = src.created;

						// Copy the transparency calculation function pointer.
						this->calcTrans = src.calcTrans;

						// Copy the overlay offsets.
						this->masterXAxisOffset = src.masterXAxisOffset;
						this->masterYAxisOffset = src.masterYAxisOffset;

						// Copy the blank value.
						this->blankValue = src.blankValue;

						// Check to see if we need to reallocate our buffers.
						if ((this->overlayXAxisResolution != src.overlayXAxisResolution) || (this->overlayYAxisResolution != src.overlayYAxisResolution))
						{
							// We need to reallocate our buffers.
							if (this->overlayData != NULL)
							{
								delete[] this->overlayData;
								this->overlayData = NULL;
							}
							if (this->transparencyData != NULL)
							{
								delete[] this->transparencyData;
								this->transparencyData = NULL;
							}

							// Clear our resolution settings.
							this->overlayXAxisResolution = 0;
							this->overlayYAxisResolution = 0;

							// Check and see if the source overlay's resolution is greater than zero.
							if ((src.overlayXAxisResolution > 0) && (src.overlayYAxisResolution > 0))
							{
								// Begin try block.
								try{
									// Reallocate the buffers.
									this->overlayData = new T[(src.overlayXAxisResolution * src.overlayYAxisResolution)];

									// Check and see if the source overlay's transparencyBufferEnabled flag is set.
									if (src.transparencyBufferEnabled)
									{
										// Allocate our transparencyData buffer.
										this->transparencyData = new T[(src.overlayXAxisResolution * src.overlayYAxisResolution)];
									}
									else
									{
										// Set our transparencyBufferEnabled flag to false.
										this->transparencyBufferEnabled = false;
									}
								}
								catch(...)
								{
									// Exception thrown.
									this->lastError = RENDERER_ERROR_MEM_BUF_ALLOC_EXCEPTION;
								}

								// Make sure that the overlayData buffer was allocated.
								if (this->overlayData != NULL)
								{
									// Blank out the overlayData buffer.
									for (size_t x = 0; x < (this->overlayXAxisResolution * this->overlayYAxisResolution); x++)
									{
										this->overlayData[x] = this->blankValue;
									}

									// Copy the resolution settings.
									this->overlayXAxisResolution = src.overlayXAxisResolution;
									this->overlayYAxisResolution = src.overlayYAxisResolution;

									// Check and see if the source overlay's transparencyData buffer is enabled.
									if (src.transparencyBufferEnabled)
									{
										// Check the transparencyData buffer.
										if (this->transparencyData != NULL)
										{
											// Blank out the transparencyData buffer.
											for (size_t x = 0; x < (this->overlayXAxisResolution * this->overlayYAxisResolution); x++)
											{
												this->transparencyData[x] = this->blankValue;
											}

											// Set our transparencyBufferEnabled flag.
											this->transparencyBufferEnabled = true;
										}
										else
										{
											// Deallocate overlayData buffer.
											if (this->overlayData != NULL)
											{
												delete[] this->overlayData;
												this->overlayData = NULL;
											}

											// Could not allocate memory for transparencyData buffer.
											this->lastError = RENDERER_ERROR_UNABLE_TO_ALLOC_TD_BUF;
										}
									}
								}
								else
								{
									// Could not allocate memory for overlay image buffer.
									this->lastError = RENDERER_ERROR_UNABLE_TO_ALLOC_OI_BUF;
								}
							}
						}

						// Check and see if the buffers are allocated.
						if ((this->overlayData != NULL) && (src.overlayData != NULL))
						{
							// Copy data from the source.
							for (size_t x = 0; ((x < (this->overlayXAxisResolution * this->overlayYAxisResolution)) && (x < (src.overlayXAxisResolution * src.overlayYAxisResolution))); x++)
							{
								// Copy the data.
								this->overlayData[x] = src.overlayData[x];
							}

							// Check and see if the source overlay's transparencyBufferEnabled flag and our transparencyBufferEnabled flags are set and our transparencyData buffer is allocated.
							if (this->transparencyBufferEnabled && src.transparencyBufferEnabled)
							{
								// Do the same for the transparencyData.
								if ((this->transparencyData != NULL) && (src.transparencyData != NULL))
								{
									// Copy data from the source.
									for (size_t x = 0; ((x < (this->overlayXAxisResolution * this->overlayYAxisResolution)) && (x < (src.overlayXAxisResolution * src.overlayYAxisResolution))); x++)
									{
										// Copy the data.
										this->transparencyData[x] = src.transparencyData[x];
									}

									// We are done.
									result = true;
								}
							}
							else
							{
								// We are done.
								result = true;
							}
						}
					}
					else
					{
						// We cannot duplicate ourselves.
						this->lastError = RENDERER_ERROR_INVAL_OVERLAY_SELF_OVERWRITE;
					}

					// Exit function.
					return result;
				}

				/*!
				 * 	const T * Common::Renderer::Overlay<T>::Get_Overlay_Data() const
				 *
				 * 	Returns a pointer to the overlay's current image buffer.
				 *
				 * 	WARNING: If another overlay function is called the returned pointer can become invalid, or
				 * 	the data can be altered. DO NOT USE THE RETURNED POINTER AFTER CALLING A DIFFERENT OVERLAY FUNCTION!
				 */
				const T * Get_Overlay_Data() const
				{
					// Return a const data pointer.
					return this->overlayData;
				}

				/*!
				 * 	const T * Common::Renderer::Overlay<T>::Get_Transparency_Data() const
				 *
				 * 	Returns a pointer to the overlay's current transparency data buffer.
				 *
				 * 	WARNING: If another overlay function is called the returned pointer can become invalid, or
				 * 	the data can be altered. DO NOT USE THE RETURNED POINTER AFTER CALLING A DIFFERENT OVERLAY FUNCTION!
				 */
				const T * Get_Transparency_Data() const
				{
					// Return a const data pointer.
					return this->transparencyData;
				}

				/*!
				 * 	const T & Common::Renderer::Overlay<T>::Get_Blank_Value() const
				 *
				 * 	Returns a reference to the overlay's current blank value.
				 */
				const T & Get_Blank_Value() const
				{
					// Return the blank value.
					return this->blankValue;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Set_Blank_Value(const T & value)
				 *
				 * 	Sets the overlay's blank value to the given value.
				 */
				void Set_Blank_Value(const T & value)
				{
					// Set the blankValue.
					this->blankValue = value;

					// Exit function.
					return;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Get_Overlay_Offsets(long & xOffset, long & yOffset) const
				 *
				 * 	Sets the overlay's current masterXAxisOffset to xOffset, and the overlay's current masterYAxisOffset to yOffset.
				 * 	(I.e. It sets the given arguments to the overlay's current offsets.)
				 *
				 * 	This function has no return, result is stored in the given arguments.
				 */
				void Get_Overlay_Offsets(long & xOffset, long & yOffset) const
				{
					// Set the values.
					xOffset = this->masterXAxisOffset;
					yOffset = this->masterYAxisOffset;

					// Exit function.
					return;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Set_Overlay_Offsets(const long & newXOffset, const long & newYOffset)
				 *
				 * 	Sets the overlay's offsets to the given offsets.
				 *
				 * 	This function has no return.
				 */
				void Set_Overlay_Offsets(const long & newXOffset, const long & newYOffset)
				{
					// Move overlay.
					this->masterXAxisOffset = newXOffset;
					this->masterYAxisOffset = newYOffset;

					// Exit function.
					return;
				}

				/*!
				 * 	void Common::Renderer::Overlay<T>::Get_Resolution(size_t & xResolution, size_t & yResolution) const
				 *
				 * 	Sets the overlay's current overlayXAxisResolution to xResolution, and the overlay's current overlayYAxisResolution to yResolution.
				 * 	(I.e. It sets the given arguments to the overlay's current resolution.)
				 *
				 * 	This function has no return, result is stored in the given arguments.
				 */
				void Get_Resolution(size_t & xResolution, size_t & yResolution) const
				{
					// Set the values.
					xResolution = this->overlayXAxisResolution;
					yResolution = this->overlayYAxisResolution;

					// Exit function.
					return;
				}

				/*
				* 	Specializations for the Get_Data_Element() and Set_Data_Element() functions go in the Renderer_Overlay_Element_Accessor_Functions.h file.
				*
				* 	NOT HERE!
				*/

				/*!
				 * 	T Common::Renderer::Overlay<T>::Get_Data_Element(const size_t & offset) const
				 *
				 * 	Returns the element at the given offset in the overlay's image data buffer.
				 *
				 * 	If an invalid offset is given then this function will return the overlay's current blank value.
				 */
				T Get_Data_Element(const size_t & offset) const
				{
					// Init result.
					T result = this->blankValue;

					// Check and see if we have data stored.
					if ((this->overlayData != NULL) && ((overlayXAxisResolution > 0) && (overlayYAxisResolution > 0)))
					{
						// Check for valid offset.
						if (offset < (overlayXAxisResolution * overlayYAxisResolution))
						{
							// Return the data at that offset.
							result = this->overlayData[offset];
						}
					}

					// Return the result.
					return result;
				}

				/*!
				 * 	T Common::Renderer::Overlay<T>::Get_Transparency_Element(const size_t & offset) const
				 *
				 * 	Returns the element at the given offset in the overlay's transparency data buffer.
				 *
				 * 	If an invalid offset is given then this function will return the overlay's current blank value.
				 */
				T Get_Transparency_Element(const size_t & offset) const
				{
					// Init result.
					T result = this->blankValue;

					// Check and see if we have data stored.
					if ((this->transparencyBufferEnabled) && (this->transparencyData != NULL) && ((overlayXAxisResolution > 0) && (overlayYAxisResolution > 0)))
					{
						// Check for valid offset.
						if (offset < (overlayXAxisResolution * overlayYAxisResolution))
						{
							// Return the data at that offset.
							result = this->transparencyData[offset];
						}
					}

					// Return the result.
					return result;
				}

				template<class A>
				T Get_Data_Element(const size_t & offset, const Overlay<A> * source) const
				{
					/*!
					 * 	This is the generic function for Get_Data_Element().
					 *
					 * 	All it does is return the current blankValue as we are required to return
					 * 	a valid object of type T.
					 *
					 * 	All Overlay functions call this function to access an element that is outside
					 * 	of the overlay object. This allows the Overlay object to cater to other data
					 * 	types as needed. Therefore, you must impliment the needed functionality as a
					 * 	template specialization in Renderer_Overlay_Element_Accessor_Functions.h. (NOT HERE!)
					 */

					// We don't do anything here except return a copy of the current blankValue.
					return this->blankValue;
				}

				template<class A>
				T Get_Transparency_Element(const size_t & offset, const Overlay<A> * source) const
				{
					/*!
					 * 	This is the generic function for Get_Transparency_Element().
					 *
					 * 	All it does is return the current blankValue as we are required to return
					 * 	a valid object of type T.
					 *
					 * 	All Overlay functions call this function to access an element that is outside
					 * 	of the overlay object. This allows the Overlay object to cater to other data
					 * 	types as needed. Therefore, you must impliment the needed functionality as a
					 * 	template specialization in Renderer_Overlay_Element_Accessor_Functions.h. (NOT HERE!)
					 */

					// We don't do anything here except return a copy of the current blankValue.
					return this->blankValue;
				}

				template<class A>
				void Set_Data_Element(const size_t & offset, const A & element)
				{
					/*!
					 * 	This is the generic function for Set_Data_Element().
					 *
					 * 	All it does is return the second it is called.
					 *
					 * 	All Overlay functions call this function to convert and set the given element
					 * 	from it's original data type, to the Overlay's data type, and then set the
					 * 	converted element at the given offset in the overlay's data array. Therefore,
					 * 	you must impliment the needed functionality as a template specialization in
					 * 	Renderer_Overlay_Element_Accessor_Functions.h. (NOT HERE!)
					 */

					// We don't do anything here except exit the function.
					return;
				}

				template<class A>
				void Set_Transparency_Element(const size_t & offset, const A & element)
				{
					/*!
					 * 	This is the generic function for Set_Transparency_Element().
					 *
					 * 	All it does is return the second it is called.
					 *
					 * 	All Overlay functions call this function to convert and set the given element
					 * 	from it's original data type, to the Overlay's data type, and then set the
					 * 	converted element at the given offset in the overlay's data array. Therefore,
					 * 	you must impliment the needed functionality as a template specialization in
					 * 	Renderer_Overlay_Element_Accessor_Functions.h. (NOT HERE!)
					 */

					// We don't do anything here except exit the function.
					return;
				}

				// Include Renderer_Overlay_Element_Accessor_Functions.h.
		};
	}
}

#endif

// End of Renderer_Data_Structures_Overlay_Base_Functions.h
