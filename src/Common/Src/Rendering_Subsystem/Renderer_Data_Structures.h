/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Data_Structures.h	20/12/2013

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

#ifndef COMMON_RENDER_DATA_STRUCT_H
#define COMMON_RENDER_DATA_STRUCT_H

// Declare namespaces.
namespace Common
{
	namespace Renderer
	{
		/*!
		 * 	static Panic::ERROR Common::Renderer::DebugChannel
		 *
		 * 	A class used to allow error / debug logging by various portions of the Rendering Subsystem.
		 */
		static Panic::ERROR DebugChannel;

		// Declare 2D renderer base class.
		class Renderer2D
		{
			private:

			protected:
				bool bOverlaysEnabled;		// Whether or not to use the overlay vector.
				size_t xScreenResolution;	// Holds the horazontal (X axis) size of the window / screen.
				size_t yScreenResolution;	// Holds the vertical (Y axis) size of the window / screen.
				size_t colorDepth;		// Holds the color depth of the window / screen.
				const char * lastError;		// Points to a c-string that contains the human readable version of the last error that the renderer encountered.

			public:
				Renderer2D()
				{
					bOverlaysEnabled = false;
					xScreenResolution = 0;
					yScreenResolution = 0;
					colorDepth = 0;
					lastError = NULL;
				}

				// Declare virtual destructor.
				virtual ~Renderer2D()
				{
				  
				}

				/*
				 * 	Wondering if the renderer subsystem should include a function to import bitmaps and characters into
				 * 	a given Renderer class.
				 * 
				 * 	Something like a static conversion function, that calls the needed class functions for bliting.
				 *
				 * 	Of cource the text console renderer is special as it lacks the needed support for graphical display.
				 * 	(Hence the name TEXT console renderer.) All other renderers should not be required to act on character
				 * 	data however. (They may not support it. Also the text console renderer, does not act on bitmap requests.)
				 * 
				 * 	Of cource the real issue is that we need generic functions that default to doing nothing.
				 * 	Templates have no way to lock them to specific types. (Yes template specialisation exists,
				 * 	but we can't say ONLY the special templates may be used. As if a type can be converted to 
				 * 	another supported type, the compiler will accept it, even if our code won't, and there will
				 * 	be no warning at compile time. (Unless that default template winds up calling the #error preprocessor macro.))
				 *
				 * 	The alternitve is to create overloaded functions. (But this requires all of the data types to be
				 * 	accepted by the base class, which would be impossible to maintain.)
				 *
				 * 	I could create a second data structure to contain different data types and pass that to the renderer objects.
				 * 	The problem then becomes how do you figure out if a given renderer supports a given data type?
				 */

				// Declare basic functions.
				virtual bool Change_Resolution(const size_t & xScreenResolution, const size_t & yScreenResolution, const size_t & colorDepth) = 0;

				virtual const char * Get_Last_Error();	// Returns a human readable string of the last error that the renderering backend encountered.

				virtual bool Render() = 0;

				virtual bool Blit_Text(const char * textString, const size_t & string_length, const size_t & xCoordOffset = 0, const size_t & yCoordOffset = 0, const size_t & overlayNumber = 0) = 0;

				virtual bool Blit_Bitmap(const char * bitmap, const size_t & xCoordOffset = 0, const size_t & yCoordOffset = 0, const size_t & overlayNumber = 0) = 0;

				// Declare overlay functions.
				virtual bool Create_Overlay() = 0;

				virtual bool Destroy_Overlay(const size_t & overlayNumber) = 0;

				virtual void Clear_Overlay(const size_t & overlayNumber) = 0;

				void Move_Entire_Overlay(const long & xCoordOffset, const long & yCoordOffset = 0);

				bool Swap_Overlays(const size_t & firstOverlayNumber, const size_t & secondOverlayNumber = 0);

				bool Duplicate_Overlay(const size_t & overlayNumber, const size_t & duplicateOverlayNumber = 0);
		};
	};
};

#endif

// End of Renderer_Data_Structures.h