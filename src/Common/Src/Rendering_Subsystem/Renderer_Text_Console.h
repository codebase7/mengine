/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Text_Console.h	20/12/2013

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

//#ifndef COMMON_RENDER_DATA_STRUCT_H
//#define COMMON_RENDER_DATA_STRUCT_H

#define TEXT_CONSOLE_RENDERER_TRANSPARENCY_VALUE '1'

// Declare namespaces.
namespace Common
{
	namespace Renderer
	{
		// Declare the text console error table.
		/*!
		 * 	const static Common_Error_Object TEXT_CONSOLE_ERROR_TABLE[]
		 *
		 * 	Contains a mapping of error messages and their respective error
		 * 	codes.
		 *
		 * 	Used to display human readable error messages when
		 * 	Renderer_Text_Console::Get_Last_Error() is called.
		 */
		const static Common_Error_Object TEXT_CONSOLE_ERROR_TABLE[] = {
			{0, "No error."},
			{-1, "Unknown error code."},
			{-3, "Function not supported with this renderer."},
			{-10, "Could not create a new overlay in the overlay stack."},
			{-11, "Could not allocate memory for overlay image buffer."},
			{-12, "Unable to allocate memory for finalImage buffer."},
			{-13, "Exception thrown while attempting to allocate memory buffer(s)."},
			{-14, "You cannot use a newline (\\n) character as a blank value."},
			{-15, "Internal Error, finalResult buffer is not allocated while trying to output to console."},
			{-16, "Internal Error, working buffer is not allocated while attempting an operation on it."},
			{-17, "No overlay exists with the given offset."},
			{-18, "No text given to blit."},
			{-19, "An exception was thrown while attempting to create the overlay."},
			{-20, "A given overlay does not exist."},
			{-21, "Overlays are disabled."},
			{-22, "Source overlay is not set up correctly, it does not have an allocated memory buffer, destroying source overlay."},
			{-23, "Exception thrown while duplicating overlay, clearing dest overlay."},
			{-24, "Given overlay offsets are the same. Cannot overwrite an overlay with itself."},
			{-25, "Unable to allocate memory for fake transparency data generation."},
			{-26, "Unable to generate fake transparency data."},
			{-27, "Error duplicating overlay. Check the overlay for the real error."}
		};

		/*!
		 * 	Common::Renderer::Get_TEXT_CONSOLE_ERROR_TABLE_Size()
		 *
		 * 	Returns the size (number of elements) of the TEXT_CONSOLE_ERROR_TABLE.
		 */
		size_t Get_TEXT_CONSOLE_ERROR_TABLE_Size();

		/*!
		 * 	class Common::Renderer::Renderer_Text_Console
		 *
		 * 	This class is a renderer that supports a text-based console only.
		 *
		 * 	Notes about this renderer:
		 * 		This renderer uses a 2D plane to render it's images.
		 *
		 * 		This renderer's plane starts at coordnates (0,0), and expands by "falling" to the right.
		 * 		(I.e. There are no negative offsets / coordnates, and the top left corner of the screen
		 * 		 is the origin point while the bottom right corner is the (resolution - 1) point.
		 * 		 (AKA the (xScreenResolution, yResolution) point.))
		 *
		 * 		Unless otherwise stated, all functions of this class will destroy any overlay that
		 * 		is considered invalid. (I.e. Missing a valid pointer to it's data.)
		 *
		 * 		All overlays are stored in an overlay "stack" that starts at zero. The number of created
		 * 		overlays - 1, is the last overlay in the stack.
		 *
		 * 		To get the correct overlayNumber / offset, use this formula:
		 * 		offset_of_overlay_in_overlay_stack = overlay_you_want_to_use - 1.
		 *
		 * 		Overlays are rendered starting with the last overlay in the overlay stack, and ending
		 * 		with the first overlay in the overlay stack, with the data from the previous overlays being
		 * 		overwritten with the current overlay's data if the current overlay overlaps the
		 * 		previous overlays. (Data from the previous overlays is kept intact only if the current
		 * 		overlay has a blank value at the same position.)
		 * 		This means the first overlay is the most visible, and the last overlay is the least
		 * 		visible.
		 * 			An example of this using a 7 layer overlay stack:
		 * 				Overlay Number:		Visiblity:
		 * 					0		ALWAYS
		 * 					1		 |
		 * 					2		 |
		 * 					3		 |
		 * 					4		\ /
		 * 					5		 .
		 * 					6		LEAST
		 *
		 * 		The blank value is used as a transpareny value on the overlays, and a blank space
		 * 		on the final image.
		 * 		Because the text console does not support color output, there is no seperation
		 * 		between transpareny and blank values. There is also no way to create a real
		 * 		translucent image. (I.e. The output cannot "appear" to be transparent.)
		 *
		 * 		The blank value is also forbidden from being a character that causes the output
		 * 		to jump to the next line. (This is to prevent errors in output as std::cout is used
		 * 		for output.)
		 *
		 * 		Fullscreen means whether or not the current resolution takes up the entire window / screen.
		 * 		(If fullscreen is true, the renderer assumes that after outputting xScreenResolution characters to the backend, that the next character
		 * 		 outputted will appear on the next line automaticly.
		 * 		 If this value is false, the renderer assumes it needs to manually output a newline character, after outputting xScreenResolution
		 * 		 characters, to get further output to appear on the next line.)
		 */
		class Renderer_Text_Console
		{
			private:
				bool bChangeSinceLastRender;				// Whether or not a change that would affect the final image has occured since the last call to Render().
				bool bOverlaysEnabled;					// Whether or not to use the overlay vector.
				bool bFullscreen;					// Whether or not the given resolution is the size of the screen. (Determines whether or not to output a newline after outputting xScreenResolution characters.)
				short lastError;					// Holds the error code of the last error that the renderer encountered.
				size_t xScreenResolution;				// Holds the horazontal (X axis) size of the window / screen.
				size_t yScreenResolution;				// Holds the vertical (Y axis) size of the window / screen.
				size_t colorDepth;					// Holds the color depth of the window / screen.
				Overlay<char> finalResult;				// What is actually printed out to std::cout. (Or returned.)
				char blankValue;					// What is used to fill unused portions of overlays and the final image. (Could also be the transpareny color.)
				std::vector<Overlay<char> > overlayStack;		// The stack of overlays.

				// Private functions.
				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Generate_Fake_Transparency_Data(const char * dataArray, const size_t & dataLength, char ** transparencyData)
				 *
				 * 	Generates fake transparency data for the renderer to send to the overlay blit function.
				 * 	(Transparency data is required by the overlay object, but transparency beyond seeing
				 * 	 something behind a given overlay layer is not possible on a text console, as the text
				 * 	 console has no concept of displaying bitmap images.)
				 *
				 * 	Double delete / free Warning: transparencyData will be deallocated (by calling delete) if transparencyData
				 * 	when this function is called is not equal to NULL.
				 *
				 * 	Below is copied from the function itself:
				 *
				 * 	For each value in dataArray that is not blankValue,
				 * 	make the corrosponding value in transparencyData '1'.
				 *
				 * 	(This performs the same effect as the original blank value.
				 * 	 I.e. If the blankValue is not present at that location,
				 * 	 the renderer considers it part of the image.
				 *
				 * 	 If the blankValue is present at that location, then the
				 * 	 renderer considers that location blank, and anything
				 * 	 under that overlay on the final image will not be altered.
				 *
				 * 	 Short version: Fake transparency, as the text console does
				 * 	 not display actual images only characters.)
				 *
				 * 	Returns true if the generation is successfull. (transparencyData will be non-NULL and have the same length as defined by dataLength.)
				 * 	Returns false otherwise. (Note: If false is returned, then transparencyData will be deallocated and set to NULL.)
				 */
				bool Generate_Fake_Transparency_Data(const char * dataArray, const size_t & dataLength, char *& transparencyData);

				/*!
				 * 	static void Common::Renderer::Renderer_Text_Console::Calculate_Transparency(const char & srcImgVal, const char & srcTransVal, char & destImgVal, char & destTransVal)
				 *
				 * 	Internal transparency calculation function used by Common::Renderer::Overlay::Blit().
				 *
				 * 	This function is called by an overlay that is created by this renderer to perform
				 * 	transparency calculations for the image data.
				 *
				 * 	The reason for this is that only the renderer knows how to calculate transparency, as only the
				 * 	renderer knows how to interpret the data stored in the overlay.
				 *
				 * 	The result is calculated based on the current values of the arguments when the function is called.
				 * 	The results are then stored in destImgVal and destTransVal.
				 * 	(I.e. destImgVal and destTransVal are used in the calculation and the results from the calculation
				 * 	overwrite destImgVal and destTransVal.)
				 *
				 * 	Pram: const char & srcImgVal, source overlay's image value. (I.e. the image screen element value.)
				 * 	Pram: const char & srcTransVal, source overlay's transparency value. (I.e. the transparency screen element value.)
				 * 	Pram: char & destImgVal, destionation overlay's image value. (I.e. the image screen element value.)
				 * 	Pram: char & destTransVal, destionation overlay's transparency value. (I.e. the transparency screen element value.)
				 */
				static void Calculate_Transparency(const char & srcImgVal, const char & srcTransVal, char & destImgVal, char & destTransVal);
			protected:

			public:
				Renderer_Text_Console()
				{
					bChangeSinceLastRender = false;
					bOverlaysEnabled = false;
					bFullscreen = false;
					lastError = 0;
					xScreenResolution = 0;
					yScreenResolution = 0;
					colorDepth = 0;
					blankValue = ' ';
				}

				~Renderer_Text_Console()
				{
					// Free the overlayStack.
					overlayStack.clear();
				}

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Change_Resolution(const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth, const bool & fullscreen)
				 *
				 * 	This function changes the resolution of the final image.
				 *
				 * 	If overlays are disabled, then this function will destroy the working buffer, and destroy the final image buffer, then recreate them.
				 * 	If overlays are enabled, then only the final image buffer will be destroyed, and recreated.
				 *
				 * 	Pram: xScreenResolution, the new horazontal resolution of the final image.
				 *
				 * 	Pram: yScreenResolution, the new vertical resolution of the final image.
				 *
				 * 	Pram: colorDepth, the colorDepth of the final image. (Currently not used at all.)
				 *
				 * 	Pram: fullscreen, whether or not the given xScreenResolution and yScreenResolution is the resolution of the actual screen / window.
				 * 	(If this is true, the renderer assumes that after outputting xScreenResolution characters to the backend, that the next character
				 * 	 outputted will appear on the next line automaticly.
				 * 	 If this value is false, the renderer assumes it needs to manually output a newline character, after outputting xScreenResolution
				 *	 characters, to get further output to appear on the next line.)
				 *
				 * 	Returns true if resolution change was successful, and all of the buffers were reallocated successfully.
				 * 	Returns false otherwise.
				 */
				bool Change_Resolution(const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth, const bool & fullscreen);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Set_Blank_Value(const char & value)
				 *
				 * 	This function sets the blank value that is used for transpareny (during rendering) and empty space on the final image and all overlays. (if enabled.)
				 *
				 * 	Note: You cannot use the newline character, ('\n'), as the blank value.
				 *
				 * 	Pram: value, character to use as the blank value.
				 */
				bool Set_Blank_Value(const char & value);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Set_Blank_Value(const size_t & overlayNumber, const char & value)
				 *
				 * 	This function sets the blank value that is used for transpareny (during rendering) and empty space on the given overlay.
				 *
				 * 	Note: You cannot use the newline character, ('\n'), as the blank value.
				 *
				 * 	Pram: value, character to use as the blank value.
				 */
				bool Set_Blank_Value(const size_t & overlayNumber, const char & value);

				/*!
				 * 	char Common::Renderer::Renderer_Text_Console::Get_Blank_Value() const
				 *
				 * 	Returns the current blank value used by the renderer.
				 */
				char Get_Blank_Value() const;

				/*!
				 * 	char Common::Renderer::Renderer_Text_Console::Get_Blank_Value(const size_t & overlayNumber) const
				 *
				 * 	Returns the current blank value used by the given overlay.
				 *
				 * 	Note: If the given overlay does not exist, then this function will silently fail,
				 * 	returning the renderer's blankValue.
				 */
				char Get_Blank_Value(const size_t & overlayNumber) const;

				/*!
				 * 	const char * Common::Renderer::Renderer_Text_Console::Get_Last_Error() const
				 *
				 * 	Returns a human readable string of the last error that the renderering backend encountered.
				 */
				const char * Get_Last_Error() const;

				/*!
				 * 	short Common::Renderer::Renderer_Text_Console::Get_Last_Error_Code() const
				 *
				 * 	Returns the last error code that the renderering backend encountered.
				 */
				short Get_Last_Error_Code() const;

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Render()
				 *
				 * 	"Renders" the overlays / working buffer to the final image, then sends the final
				 * 	image to std::cout.
				 *
				 * 	Note: This function blits from the top left corner to the bottom right corner of
				 * 	the final image.
				 *
				 * 	Returns true if image was successfully sent to std::cout.
				 * 	Returns false otherwise.
				 */
				bool Render();

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Blit_Text(const char * textString, const size_t & textStringXResolution, const size_t & textStringYResolution, const size_t & xCoordOffset, const size_t & yCoordOffset, const size_t & overlayNumber)
				 *
				 * 	Takes the given c-string and blits it to the given overlay, at the given offsets on that overlay.
				 * 	(Note: If overlays are disabled, it blits the given text to the working buffer, but only if the given overlay is not changed from the default.)
				 *
				 * 	This function will continue bliting on the next line if the newline character, ('\n'), is found in the given c-string.
				 * 	(This allows multiple lines to be blited at once.)
				 *
				 * 	If while bliting the given c-string, the function reaches the end of the given overlay / working buffer,
				 * 	then this function will not blit the remaining data, and return true.
				 * 	(All data blited prior to this will remain uneffected.)
				 *
				 * 	If while bliting the given c-string, the function reaches the end of the current line on the final image,
				 * 	any data left on that line in the given c-string will be skipped.
				 *
				 * 	Note: This function blits from the top left corner to the bottom right corner of the given overlay / working buffer.
				 *
				 * 	Pram: textString, a pointer that points to the actual text to copy to the given overlay.
				 * 	Pram: textStringXResolution, horazontal resolution of textString. Multiplied with textStringYResolution to get the total textString length. Must be defined by the caller.
				 * 	Pram: textStringYResolution, vertical resolution of textString. Multipled with textStringXResolution to get the total textString length. Defaults to one (1) so that single line strings only need textStringXResolution defined.
				 * 	Pram: xCoordOffset, horazontal offset where the given c-string will start being blited to on the overlay / working buffer. Defaults to the top left corner of the given overlay. (Coordnate pair: 0, 0)
				 * 	Pram: yCoordOffset, vertical offset where the given c-string will start being blited to on the overlay / working buffer. Defaults to the top left corner of the given overlay. (Coordnate pair: 0, 0)
				 * 	Pram: overlayNumber, overlay to blit the given c-string to. (Default is the top overlay, 0. (This is also the working buffer if overlays are disabled.))
				 * 	Pram: const bool & lineWrap, if true, any remaining data on the current dataArray line will be blited to the next overlay line if the end of
				 * 	      the current overlay line is reached. Otherwise any remaining data on the current dataArray line not be blited onto the overlay. Defaults to false.
				 */
				bool Blit_Text(const char * textString, const size_t & overlayNumber = 0, const bool & lineWrap = false, const size_t & textStringXResolution = 0, const size_t & textStringYResolution = 0, const size_t & xCoordOffset = 0, const size_t & yCoordOffset = 0);

				// Declare overlay functions.
				/*!
				 * 	short Common::Renderer::Renderer_Text_Console::Get_Overlay_Debugging_Level(const size_t & overlayNumber)
				 *
				 * 	Returns the given overlay's current debugging level.
				 *
				 * 	If the given overlay does not exist, error level zero (0) is returned.
				 */
				short Get_Overlay_Debugging_Level(const size_t & overlayNumber);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Set_Overlay_Debugging_Level(const size_t & overlayNumber, const short & level)
				 *
				 * 	Sets the given overlay's debugging level.
				 *
				 * 	Returns true if successfull.
				 * 	Returns false otherwise.
				 */
				bool Set_Overlay_Debugging_Level(const size_t & overlayNumber, const short & level);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Create_Overlay(const size_t & xResolution, const size_t & yResolution, const long & xCoordOffset, const long & yCoordOffset)
				 *
				 * 	Creates a new overlay with the given resolution / final image offsets, and inserts it into
				 * 	the overlay stack at the bottom of the stack.
				 * 	(This means the newly created overlay is the least visible overlay.)
				 *
				 * 	Pram: xResolution, the horazontal resolution of the new overlay.
				 * 	Pram: yResolution, the vertical resolution of the new overlay.
				 * 	Pram: xCoordOffset, the horazontal offset on the final image where the new overlay's top left corner will be placed.
				 * 	Pram: yCoordOffset, the vertical offset on the final image where the new overlay's top left corner will be placed.
				 *
				 * 	Returns true if the overlay was created and inserted into the overlay stack successfully.
				 * 	Returns false otherwise.
				 */
				bool Create_Overlay(const size_t & xResolution, const size_t & yResolution, const long & xCoordOffset, const long & yCoordOffset);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Destroy_Overlay(const size_t & overlayNumber)
				 *
				 * 	Destroys the given overlay.
				 *
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay.
				 *
				 * 	Returns true if the given overlay was successfully destroyed.
				 * 	Returns false otherwise.
				 */
				bool Destroy_Overlay(const size_t & overlayNumber);

				/*!
				 * 	void Common::Renderer::Renderer_Text_Console::Clear_Overlay(const size_t & overlayNumber)
				 *
				 * 	Overwrites the entirity of the given overlay with the current blank value.
				 *
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay.
				 */
				void Clear_Overlay(const size_t & overlayNumber);

				/*!
				 * 	void Common::Renderer::Renderer_Text_Console::Reset_Overlay(const size_t & overlayNumber)
				 *
				 * 	Deallocates any of the given overlay's allocated memory buffers, and sets the given overlay back to it's default state.
				 *
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay.
				 */
				void Reset_Overlay(const size_t & overlayNumber);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Change_Overlay_Resolution(const size_t & overlayNumber, const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth, const bool & fullscreen)
				 *
				 * 	This function changes the resolution of the given overlay.
				 *
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay.
				 *
				 * 	Pram: xScreenResolution, the new horazontal resolution for the given overlay.
				 *
				 * 	Pram: yScreenResolution, the new vertical resolution for the given overlay.
				 *
				 * 	Pram: colorDepth, the colorDepth for the given overlay. (Currently not used at all.)
				 *
				 * 	Pram: fullscreen, whether or not the given xScreenResolution and yScreenResolution is the resolution of the actual screen / window.
				 *
				 * 	Returns true if resolution change was successful, and all of the buffers were reallocated successfully.
				 * 	Returns false otherwise.
				 */
				bool Change_Overlay_Resolution(const size_t & overlayNumber, const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth, const bool & fullscreen);

				/*!
				 * 	void Common::Renderer::Renderer_Text_Console::Get_Overlay_Offsets(long & xCoordOffset, long & yCoordOffset, const size_t & overlayNumber)
				 *
				 * 	Retrives the current offsets for the given overlay.
				 *
				 * 	Pram: xCoordOffset, will hold the current x axis offset for the given overlay if successful. Otherwise no change will be made.
				 * 	Pram: yCoordOffset, will hold the current y axis offset for the given overlay if successful. Otherwise no change will be made.
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay. (Default is the top overlay in the overlay stack, or the working buffer if overlays are disabled.)
				 */
				void Get_Overlay_Offsets(long & xCoordOffset, long & yCoordOffset, const size_t & overlayNumber = 0);

				/*!
				 * 	void Common::Renderer::Renderer_Text_Console::Set_Overlay_Offsets(const long & xCoordOffset, const long & yCoordOffset, const size_t & overlayNumber)
				 *
				 * 	Moves the entire given overlay to the given position on the final image. (Transform overlay by changing it's starting offsets.)
				 *
				 * 	Pram: xCoordOffset, the new horazontal offset on the final image where the overlay's top left corner will be placed.
				 * 	Pram: yCoordOffset, the new vertical offset on the final image where the overlay's top left corner will be placed.
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay. (Default is the top overlay in the overlay stack, or the working buffer if overlays are disabled.)
				 */
				void Set_Overlay_Offsets(const long & xCoordOffset, const long & yCoordOffset, const size_t & overlayNumber = 0);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Swap_Overlays(const size_t & firstOverlayNumber, const size_t & secondOverlayNumber)
				 *
				 * 	Swaps the positions of the two given overlays in the overlay stack.
				 *
				 * 	Pram: firstOverlayNumber, the offset of an overlay to swap.
				 * 	Pram: secondOverlayNumber, the offset of an overlay to swap.
				 *
				 * 	Returns true if the overlays were swapped successfully.
				 * 	Returns false otherwise.
				 */
				bool Swap_Overlays(const size_t & firstOverlayNumber, const size_t & secondOverlayNumber);

				/*!
				 * 	bool Common::Renderer::Renderer_Text_Console::Duplicate_Overlay(const size_t & sourceOverlayNumber, const size_t & destOverlayNumber)
				 *
				 * 	Overwrites the destionation overlay with the source overlay.
				 * 	(The result is two identical overlays in the overlay stack
				 * 	at the given positions within the overlay stack.)
				 *
				 * 	This function will NOT clear the source overlay.
				 *
				 * 	Note: This function will NOT create the destionation overlay if it does not exist
				 * 	when this function is called. If the destionation overlay does not exist, then this
				 * 	function will fail.
				 *
				 * 	Note: This function CAN overwrite an invalid destionation overlay.
				 *
				 * 	Pram: sourceOverlayNumber, the offset of the overlay to duplicate.
				 * 	Pram: destOverlayNumber, the offset of the overlay that will be overwritten.
				 *
				 * 	Returns true if the source overlay was copied to the destionation overlay successfully.
				 * 	Returns false otherwise.
				 */
				bool Duplicate_Overlay(const size_t & sourceOverlayNumber, const size_t & destOverlayNumber);

				/*!
				 * 	const char * Common::Renderer::Renderer_Text_Console::Get_Last_Error_From_Overlay() const
				 *
				 * 	Returns a human readable string of the last error that the given overlay encountered.
				 *
				 * 	Note: If the given overlay does not exist or overlay support is disabled, then the returned error message will be
				 * 	the default unknown error code message.
				 */
				const char * Get_Last_Error_From_Overlay(const size_t & overlayNumber) const;

				/*!
				 * 	short Common::Renderer::Renderer_Text_Console::Get_Last_Error_Code_From_Overlay() const
				 *
				 * 	Returns the last error code that the given overlay encountered.
				 *
				 * 	Note: If the given overlay does not exist or overlay support is disabled, then the returned error message will be
				 * 	the default unknown error code.
				 */
				short Get_Last_Error_Code_From_Overlay(const size_t & overlayNumber) const;
#ifndef _NDEBUG
				/*!
				 * 	const char * Common::Renderer::Renderer_Text_Console::Return_Current_Final_Image_Buffer()
				 *
				 * 	A debug function that does exactly what it says, it returns a pointer to the current final
				 * 	image buffer.
				 *
				 * 	This pointer can become invalid if the internal final image buffer is reallocated.
				 * 	(So you should probably use the pointer to copy the data it points to the second you get it,
				 * 	or not do anything else with the renderer until you are done with that data. (Unless you
				 * 	want that segfault anyway.) As a sidenote: I realize that this seems to come off as rude,
				 * 	however I think that the point needs to be made: This is NOT a standard function! It only
				 * 	exists to debug the output from the renderer, so don't expect it to work in a release build,
				 * 	and don't use it for a purpose other than DEBUGGING!)
				 *
				 * 	Returns a pointer to the current final image buffer if it is allocated when this function is called.
				 * 	Returns NULL otherwise.
				 */
				const char * Return_Current_Final_Image_Buffer();

				/*!
				 * 	const char * Common::Renderer::Renderer_Text_Console::Return_Current_Overlay_Image_Buffer(const size_t & overlayNumber)
				 *
				 * 	A debug function that does exactly what it says, it returns a pointer to the given overlay's
				 * 	image data buffer.
				 *
				 * 	This pointer can become invalid if the internal overlay image buffer is reallocated.
				 * 	(So you should probably use the pointer to copy the data it points to the second you get it,
				 * 	or not do anything else with the renderer until you are done with that data. (Unless you
				 * 	want that segfault anyway.) As a sidenote: I realize that this seems to come off as rude,
				 * 	however I think that the point needs to be made: This is NOT a standard function! It only
				 * 	exists to debug the output from the renderer, so don't expect it to work in a release build,
				 * 	and don't use it for a purpose other than DEBUGGING!)
				 *
				 * 	Pram: overlayNumber, the offset in the overlay stack for the requested overlay.
				 * 	Default is the working buffer if overlays are disabled (provided the overlayNumber
				 * 	is not changed), and the first (most visible) overlay in the overlay stack, if
				 * 	overlays are enabled.
				 *
				 * 	Returns a pointer to the current overlay image buffer if it is allocated when this function is called.
				 * 	Returns NULL otherwise.
				 */
				const char * Return_Current_Overlay_Image_Buffer(const size_t & overlayNumber = 0);
#endif
		};
	};
};

//#endif

// End of Renderer_Text_Console.h
