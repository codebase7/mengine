/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Basic_Functions.cpp	21/12/2013

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

int Common::Renderer::Get_Rendering_Subsystem_API_Major_Version_Number()
{
	return MSYS_RENDERING_SUBSYS_API_MAJOR_VER;
}

int Common::Renderer::Get_Rendering_Subsystem_API_Minor_Version_Number()
{
	return MSYS_RENDERING_SUBSYS_API_MINOR_VER;
}

int Common::Renderer::Get_Rendering_Subsystem_API_Revision_Version_Number()
{
	return MSYS_RENDERING_SUBSYS_API_REVISION_VER;
}

bool Common::Renderer::Calculate_Offsets_From_Coordnates(const long & destXCoordOffset, const long & destYCoordOffset, const size_t & destXAxisResolution, const size_t & destYAxisResolution,
							 const size_t & sourceXAxisResolution, const size_t & sourceYAxisResolution, size_t & currentSourceXCoordOffset, size_t & currentDestXCoordOffset, size_t & currentDestOffset,
							 size_t & currentSourceOffset, size_t & nextDestEndOfLineOffset, size_t & nextSourceEndOfLineOffset)
{
	// Init vars.
	bool result = false;				// The result of this function.
	std::stringstream errorText;			// Used to construct error messages.

	/*
	 * 	Varaiable definitions:
	 *
	 * 	destXCoordOffset: The difference between the destionation and source x axis origin point.
	 * 	destYCoordOffset: The difference between the destionation and source y axis origin point.
	 * 	destXAxisResolution: The horazontal resolution (width) of the destionation.
	 * 	destYAxisResolution: The vertical resolution (length) of the destionation.
	 * 	sourceXAxisResolution: The horazontal resolution (width) of the source.
	 * 	sourceYAxisResolution: The vertical resolution (length) of the source.
	 * 	currentSourceOffset: The offset within the source to start at.
	 * 	currentDestOffset: The offset within the destionation to start at.
	 * 	nextDestEndOfLineOffset: The offset within the destionation where the current line will end.
	 * 	nextSourceEndOfLineOffset: The offset within the source where the current line will end.
	 * 	currentSourceXCoordOffset: The amount the Overlay::Blit() function must jump forward when moving to a new line in the source.
	 * 	currentDestXCoordOffset: The amount the Overlay::Blit() function must jump forward when moving to a new line in the destionation.
	 */

	// Debug output for the arguments.
	if (Common::Renderer::DebugChannel.get_log_level() >= ERROR_VERBOSE)
	{
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): Arguments:\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): destXCoordOffset: " << destXCoordOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): destYCoordOffset: " << destYCoordOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): sourceXAxisResolution: " << sourceXAxisResolution << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): sourceYAxisResolution: " << sourceYAxisResolution << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): destXAxisResolution: " << destXAxisResolution << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): destYAxisResolution: " << destYAxisResolution << ".\n";
		Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);		// Send to the debug channel.
		errorText.str(std::string());	// Clear errorText.
	}

	// Set all of the non-const arguments to zero.
	currentSourceXCoordOffset = 0;
	currentDestXCoordOffset = 0;
	currentDestOffset = 0;
	currentSourceOffset = 0;
	nextDestEndOfLineOffset = 0;
	nextSourceEndOfLineOffset = 0;

	/* Check and see if at least part of the overlay is inside the final image area.
	 *
	 * Assumptions made:
	 * If the offset is greater than the destionation overlay's resolution, then the source overlay is to the right of the destionation overlay's area.
	 *
	 * If the source overlay's resolution minus the offset is less than one (1), then the source overlay is to the left of the destionation overlay's area.
	 *
	 * If the offset is negative, then it must be made positive before it can be checked or compared.
	 *
	 * If the offset is negative, then it can be made positive without overflowing the buffer. (Bad assumption.)
	 *
	 * source resolution minus the offset equals the remaining amount of data on each line after jumping to that offset, if this value is less than one we don't need to do anything.
	 *
	 * All overlays start at coordnates (0,0) and overlay coordnates cannot be negative.
	 *
	 * The total size of the overlay's allocated memory buffer is the overlay's xAxisResolution times the overlay's yAxisResolution minus one (1).
	 * E.g. ((xAxisResolution * yAxisResolution) - 1) = <total allocated overlay memory buffer size>.
	 *
	 *
	 * Horazontal check. If the below is not true, then the overlay does not overlap the final
	 * image, nor is the overlay on the final image.
	 *
	 * The format for this is coordnate is destionation overlay starting offset is less than the destionation overlay's resolution, and
	 *
	 * eg. ((offset to start coping data to is within destionation memory buffer) &&
	 * (offset to start coping data to minus the source overlay's resolution is greater than zero. I.e. We have data to copy starting at that offset.))
	 *
	 * The (is offset negative) check at the beginning of each individual condition block is used to slightly alter the
	 * checks performed as the negative offset requires special handling to get valid results due to the integer comparision
	 * treating it as an unsigned value.
	 *
	 * (I.e. The overlay is "outside" / "seperate from" the final image.)
	 *
	 * So this overlay must be skipped.
	 */
	if (((destXCoordOffset > -1) && ((size_t)destXCoordOffset < destXAxisResolution) && ((sourceXAxisResolution - destXCoordOffset) > 0)) ||
	   ((destXCoordOffset <= -1) && (((size_t)(destXCoordOffset * -1)) < destXAxisResolution) && ((((size_t)(destXCoordOffset * -1)) < sourceXAxisResolution) && (sourceXAxisResolution + destXCoordOffset) > 0)))
	{

		/* Check and see if at least part of the overlay is inside the final image area.
		 *
		 * Vertical check. If the below is not true, then the overlay does not overlap the final
		 * image, nor is the overlay on the final image.
		 *
		 * (I.e. The overlay is "outside" / "seperate from" the final image.)
		 *
		 * So this overlay must be skipped.
		 */
		if (((destYCoordOffset > -1) && ((size_t)destYCoordOffset < destYAxisResolution) && ((sourceYAxisResolution - destYCoordOffset) > 0)) ||
		  ((destYCoordOffset <= -1) && (((size_t)(destYCoordOffset * -1)) < destYAxisResolution) && ((((size_t)(destYCoordOffset * -1)) < sourceYAxisResolution) && (sourceYAxisResolution + destYCoordOffset) > 0)))
		{
			/*
			 * Negative offset check.
			 *
			 * If the offset is negative then we must make it positive. Then treat that positive offset
			 * as if it is part of the origin point on the overlay.
			 *
			 * (I.e. We can't render something off-screen. So we have to start rendering from the overlay
			 *  where it overlaps the final image's origin point.)
			 *
			 * If both offsets are greater than or equal to zero, (0), then we need to set the currentScreenOffset
			 * variable using the offsets, instead of the currentOverlayOffset variable.
			 */
			if (destXCoordOffset < 0)
			{
				// Set currentDestOffset to zero. (Where we will start at on the destionation.)
				currentDestOffset = 0;

				// Set nextDestEndOfLineOffset to destXAxisResolution minus one. (destXAxisResolution = destionation horazontal resolution, lin)
				nextDestEndOfLineOffset = (destXAxisResolution - 1);

				/*
				 * We need to check and see if the y axis (vertical axis) offset is negative. (As we won't check it later.)
				 * So that we can correct our starting point in the overlay.
				 */
				if (destYCoordOffset < 0)
				{
					// Both offsets are negative. So both must be made positive and multiplied together, to get our starting point in the overlayData.
					currentSourceOffset = ((size_t)(((sourceXAxisResolution - 1) * ((size_t)(destXCoordOffset * (-1)))) * ((sourceYAxisResolution - 1) * ((size_t)(destYCoordOffset * (-1))))));
				}
				else
				{
					// Only the x axis (horazontal axis) offset is negative, so only the x offset needs to be made positive, to get our starting point in the overlayData.
					currentSourceOffset = ((size_t)(((sourceXAxisResolution - 1) * ((size_t)(destXCoordOffset * (-1)))) * ((sourceYAxisResolution - 1) * destYCoordOffset)));
				}

				// Prime the nextSourceEndOfLineOffset value.
				nextSourceEndOfLineOffset = (sourceXAxisResolution - 1);

				// The nextSourceEndOfLineOffset is greater than the currentSourceOffset.
				while ((nextSourceEndOfLineOffset < currentSourceOffset) && (nextSourceEndOfLineOffset < (sourceXAxisResolution * sourceYAxisResolution)))
				{
					nextSourceEndOfLineOffset += sourceXAxisResolution;
				}

				/*
				 * currentDestXCoordOffset must be set to zero here as the source's x offset is negative,
				 * therefore the source must shift forward not the destionation overlay.
				 */
				currentDestXCoordOffset = 0;

				// If the source's x offset is negative, make it positive.
				currentSourceXCoordOffset = ((size_t)(destXCoordOffset * (-1)));

				// Set result.
				result = true;
			}
			else
			{
				// Set the currentSourceMasterXOffset.
				currentDestXCoordOffset = ((size_t)(destXCoordOffset));

				// Check and see if the y axis offset is negative.
				if (destYCoordOffset < 0)
				{
					// Set currentDestOffset to zero.
					currentDestOffset = 0;

					// Set nextDestEndOfLineOffset to destXAxisResolution minus one.
					nextDestEndOfLineOffset = (destXAxisResolution - 1);

					/*
					 * Because we would have gotten caught on the x axis offset check earier, we know that the x axis offset is positive if we get here.
					 * So only the y axis offset needs to be made positive, to get our starting point in the overlayData.
					 */
					currentSourceOffset = ((size_t)((sourceXAxisResolution - 1) * destXCoordOffset) * ((sourceYAxisResolution - 1) * ((size_t)destYCoordOffset * (-1))));
				}
				else
				{
					// Both offsets are positive, so use them to set the currentDestOffset variable.
					currentDestOffset = ((size_t)(((sourceXAxisResolution - 1) * ((size_t)destXCoordOffset)) * ((sourceYAxisResolution - 1) * ((size_t)destYCoordOffset))));

					// Prime the nextDestEndOfLineOffset value.
					nextDestEndOfLineOffset = (destXAxisResolution - 1);

					// The nextDestEndOfLineOffset is greater than the currentDestOffset.
					while (nextDestEndOfLineOffset < currentDestOffset)
					{
						nextDestEndOfLineOffset += destXAxisResolution;
					}
				}

				// Prime the nextSourceEndOfLineOffset value.
				nextSourceEndOfLineOffset = (sourceXAxisResolution - 1);

				// The nextSourceEndOfLineOffset is greater than the currentSourceOffset.
				while ((nextSourceEndOfLineOffset < currentSourceOffset) && (nextSourceEndOfLineOffset < (sourceXAxisResolution * sourceYAxisResolution)))
				{
					nextSourceEndOfLineOffset += sourceXAxisResolution;
				}

				// Set result.
				result = true;
			}
		}
	}

	// Debug output the results.
	if (Common::Renderer::DebugChannel.get_log_level() >= ERROR_VERBOSE)
	{
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): Results:\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): currentSourceOffset: " << currentSourceOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): currentDestOffset: " << currentDestOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): currentSourceXCoordOffset: " << currentSourceXCoordOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): currentDestXCoordOffset: " << currentDestXCoordOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): nextSourceEndOfLineOffset: " << nextSourceEndOfLineOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): nextDestEndOfLineOffset: " << nextDestEndOfLineOffset << ".\n";
		errorText << "Common::Renderer::Calculate_Offsets_From_Coordnates(): result: ";
		if (result)
		{
			errorText << "True";
		}
		else
		{
			errorText << "False";
		}
		errorText << ".\n";
		Common::Renderer::DebugChannel.PanicHandler(errorText.str(), COMMON_ID, ERROR_VERBOSE);		// Send to the debug channel.
		errorText.str(std::string());	// Clear errorText.
	}

	// Exit function.
	return result;
}
