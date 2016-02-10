/*
	Multiverse Engine Project	 Common Rendering_Subsystem Renderer_Management_Functions.h	4/2/2014

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

#ifndef COMMON_RENDER_MANAGEMENT_FUNCTIONS_H
#define COMMON_RENDER_MANAGEMENT_FUNCTIONS_H

// Declare namespaces.
namespace Common
{
	namespace Renderer
	{
		size_t Choose_Renderer();

		Common::Renderer::Renderer2D * Create_2D_Renderer(const size_t & rendererID);
	}
}

#endif

// End of Renderer_Management_Functions.h