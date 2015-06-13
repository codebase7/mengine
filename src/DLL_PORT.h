/*!
	Multiverse Engine Project 13/6/2015 DLL_PORT.h

    Copyright (C) 2015 Multiverse Engine Project

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
#ifndef MSYS_DLL_PORT_H
#define MSYS_DLL_PORT_H

/* Define MSYS_DLL_EXPORT and MSYS_DLL_IMPORT_TEMPLATE */
#ifdef _MSC_VER
#ifdef _DLL	/* Determine if we are building an executable or a dll. */
/* DLL */
#define EXP_STL	/* Required by msdn. */
#define MSYS_DLL_EXPORT __declspec(dllexport)
#define MSYS_DLL_IMPORT_TEMPLATE 
#else	/* _DLL */
/* EXECUTABLE */
#define MSYS_DLL_EXPORT __declspec(dllimport)
#define MSYS_DLL_IMPORT_TEMPLATE extern
#endif	/* _DLL */
#else	/* _MSC_VER */
/* Non MSVC Compilers do not need this... */
#define MSYS_DLL_EXPORT 
#define MSYS_DLL_IMPORT_TEMPLATE
#endif	/* _MSC_VER */

#endif	/* MSYS_DLL_PORT_H */

/* End of DLL_PORT.h */
