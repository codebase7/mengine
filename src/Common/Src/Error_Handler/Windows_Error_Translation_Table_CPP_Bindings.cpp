/*!
    Multiverse Engine Project 17/1/2016 Common Windows_Error_Translation_Table_CPP_Bindings.cpp

    Copyright (C) 2016 Multiverse Engine Project

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

/* C++ Bindings. */
#ifdef __cplusplus

/* Internal includes. */
#include "Common_Error_Handler_Structures.h"
#include "Windows_Error_Translation_Table.h"

/* External includes. */
#include <exception>

const unsigned int Common::Get_Windows_Error_Translation_Table_API_Version()
{
	return Common_Get_Windows_Error_Translation_Table_API_Version();
}

const unsigned int Common::Get_Windows_Error_Translation_Table_Size()
{
	return Common_Get_Windows_Error_Translation_Table_Size();
}

int Common::Translate_Windows_Error_Code_To_Common_Error_Code(const DWORD & err)
{
	return Common_Translate_Windows_Error_Code_To_Common_Error_Code(err);
}
#endif	/* __cplusplus */
