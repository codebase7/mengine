/*!
    Multiverse Engine Project 29/5/2015 stdbool.h
	(Not a real implementation, just enough to enable the use of a boolean type on compilers like VC that only support C89.)

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
#ifndef MSYS_STD_BOOL_H
#define MSYS_STD_BOOL_H

/* This is only needed for C. */
#ifndef __cplusplus

/* Only define this if STD_BOOL is not defined. */
#ifndef _STDBOOL

/* Only define this if __bool_true_false_are_defined is not defined. */
#ifndef __bool_true_false_are_defined

/* Define true and false. */
#define TRUE 0x01	/* Really this could be anything. */
#define FALSE 0x00	/* Litteral NULL byte to conform to ANYTHING NOT NULL IS TRUE. */
#define true TRUE
#define false FALSE

/* Define the bool typedef. */
typedef char bool;	/* This is a char to conform to the expectation in C++ that sizeof(<bool>) is 1. */

/* Define __bool_true_false_are_defined (ISO) */
#define __bool_true_false_are_defined 1
#endif	/* __bool_true_false_are_defined */
#endif	/* _STDBOOL */
#endif	/* __cplusplus */

#endif	/* MSYS_STD_BOOL_H */

/* End of stdbool.h */
