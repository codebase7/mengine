/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer.h	20/12/2013

	This is the base header for the rendering subsystem.
	You should only include this header when using the rendering subsystem.

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
#define COMMON_RENDER_SUBSYSTEM_H

// Standard library includes.
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>

// Internal library header includes.
#include "../Error_Handler/Common_Error_Handler.h"	// Used for error handling.
#include "../../../Core/Src/DataProcess.h"		// Used for DataProcess::removeFromVector().

// Internal includes.
#include "Renderer_Basic_Functions.h"				// Functions that are used in both the renderer and overlay classes.
#include "Renderer_Data_Structures.h"				// Renderer base class.
#include "Renderer_Data_Structures_Overlay_Base_Functions.h"	// Base functions for the overlay template class defined in Renderer_Data_Structures.h.
#include "Renderer_Management_Functions.h"			// Static renderer functions. (Create_Renderer(), Choose_Renderer(), etc.)
#include "Renderer_Text_Console.h"				// Text Console Renderer.

#endif

// End of Renderer.h

