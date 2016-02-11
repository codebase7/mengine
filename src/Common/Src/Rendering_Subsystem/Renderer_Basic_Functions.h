/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Basic_Functions.h	20/12/2013

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
#else

#ifndef COMMON_RENDER_BASIC_FUNCTIONS_H
#define COMMON_RENDER_BASIC_FUNCTIONS_H

/* Include DLL_PORT.h */
#include "../../../DLL_PORT.h"

// Declare namespaces.
namespace Common
{
	namespace Renderer
	{
		/*!
		 *	int Common::Renderer::Get_Rendering_Subsystem_API_Major_Version_Number()
		 *
		 *	Returns the major version number of the Rendering Subsystem.
		 */
		MSYS_DLL_EXPORT int Get_Rendering_Subsystem_API_Major_Version_Number();

		/*!
		 *	int Common::Renderer::Get_Rendering_Subsystem_API_Minor_Version_Number()
		 *
		 *	Returns the minor version number of the Rendering Subsystem.
		 */
		MSYS_DLL_EXPORT int Get_Rendering_Subsystem_API_Minor_Version_Number();

		/*!
		 *	int Common::Renderer::Get_Rendering_Subsystem_API_Revision_Version_Number()
		 *
		 *	Returns the revision version number of the Rendering Subsystem.
		 */
		MSYS_DLL_EXPORT int Get_Rendering_Subsystem_API_Revision_Version_Number();

		/*!
		 * 	bool Common::Renderer::Calculate_Offsets_From_Coordnates(const long & destXCoordOffset, const long & destYCoordOffset, const size_t & destXAxisResolution, const size_t & destYAxisResolution,
		 * 								 const size_t & sourceXAxisResolution, const size_t & sourceYAxisResolution, size_t & currentSourceXCoordOffset, size_t & currentDestXCoordOffset, size_t & currentDestOffset,
		 * 								 size_t & currentSourceOffset, size_t & nextDestEndOfLineOffset, size_t & nextSourceEndOfLineOffset)
		 *
		 * 	Calculates offsets for use by the overlay system and renderer.
		 *
		 * 	If a given coordnate is negative it will be made positive prior to calculating the offset. (This will not change the given coordnate outside of the function.)
		 *
		 * 	Pram: const long & destXCoordOffset, the offset from the destionation's x axis origin point where the source's x axis origin point will be placed.
		 * 	Pram: const long & destYCoordOffset, the offset from the destionation's y axis origin point where the source's y axis origin point will be placed.
		 * 	Pram: const size_t & destXAxisResolution, the resolution of the destionation's x (horazontal) axis.
		 * 	Pram: const size_t & destYAxisResolution, the resolution of the destionation's y (vertical) axis.
		 * 	Pram: const size_t & sourceXAxisResolution, the resolution of the source's x (horazontal) axis.
		 * 	Pram: const size_t & sourceYAxisResolution, the resolution of the source's y (vertical) axis.
		 * 	Pram: size_t & currentSourceXCoordOffset, The amount the Overlay::Blit() function must jump forward when moving to a new line in the source.
		 * 	Pram: size_t & currentDestXCoordOffset, The amount the Overlay::Blit() function must jump forward when moving to a new line in the destionation.
		 * 	Pram: size_t & currentDestOffset, the offset in the destionation where we will start blitting data to.
		 * 	Pram: size_t & currentSourceOffset, the offset in the source where we will start blitting data from.
		 * 	Pram: size_t & nextDestEndOfLineOffset, the offset on the destionation where the first line we blit to will end.
		 * 	Pram: size_t & nextSourceEndOfLineOffset, the offset on the source where the first line we blit from will end.
		 *
		 * 	Returns true if the source will show up on destionation. (The needed offsets will be in their respective arguments.)
		 * 	Returns false otherwise. (All of the non-const offset arguments will be set to zero as well.)
		 */
		bool Calculate_Offsets_From_Coordnates(const long & destXCoordOffset, const long & destYCoordOffset, const size_t & destXAxisResolution, const size_t & destYAxisResolution,
						       const size_t & sourceXAxisResolution, const size_t & sourceYAxisResolution, size_t & currentSourceXCoordOffset, size_t & currentDestXCoordOffset, size_t & currentDestOffset,
						       size_t & currentSourceOffset, size_t & nextDestEndOfLineOffset, size_t & nextSourceEndOfLineOffset);
	};
};

#endif
#endif

// End of Renderer_Basic_Functions.h