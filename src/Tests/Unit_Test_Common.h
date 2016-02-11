/*!
    Multiverse Engine Project 04/9/2013 Unit Tests Unit_Test_Common.h

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

/* Include guard. */
#ifndef COMMON_UNIT_TESTS_H
#define COMMON_UNIT_TESTS_H

/* Include headers from Common. (If needed.) */
#include "Unit_Tests_Byte_Order.h"

#ifdef MSYS_HAVE_FILEUTILLS
#include "Unit_Tests_FileUtills.h"
#endif	/* MSYS_HAVE_FILEUTILLS */

#ifdef MSYS_HAVE_THREAD_UTILS
#include "Unit_Tests_Thread_Utils.h"
#endif	/* MSYS_HAVE_THREAD_UTILS */

#ifdef MSYS_HAVE_RENDERING_SUBSYS
#include "Unit_Test_Rendering_Subsystem.h"
#endif	/* MSYS_HAVE_RENDERING_SUBSYS */

#ifdef MSYS_HAVE_COMMON_ERROR_HANDLER
#include "Unit_Tests_Common_Error_Handler.h"
#endif	/* MSYS_HAVE_COMMON_ERROR_HANDLER */

#endif	/* COMMON_UNIT_TESTS_H */

/* End of Unit_Test_Common.h */
