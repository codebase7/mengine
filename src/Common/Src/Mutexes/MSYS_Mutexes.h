/*!
    Multiverse Engine Project 17/3/2015 Common MSYS_Mutexes.h

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
#ifndef MSYS_MUTEXES_H
#define MSYS_MUTEXES_H

/* Pull in DLL_PORT.h */
#include "../../../DLL_PORT.h"	/* Defines MSYS_DLL_EXPORT, and MSYS_DLL_IMPORT_TEMPLATE. */

/* Define extern C. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Define error codes. */
#define MSYS_MU_SUCCESS 0
#define MSYS_MU_ALREADY_UNLOCKED 3	/* Locked by no-one. */
#define MSYS_MU_ALREADY_OWNED 2		/* Locked by the current thread. */
#define MSYS_MU_ALREADY_LOCKED 1	/* Locked by another thread. */
#define MSYS_MU_INVALID -1
#define MSYS_MU_UNKNOWN_ERROR -2

/* External includes. */
#include <stdlib.h>	/* Defines malloc(), free(). */

/* Internal host specific includes. */
#ifdef __linux__
#include "Linux/MSYS_Mutexes_Linux.h"
#elif _WIN32
#include "Windows\MSYS_Mutexes_Windows.h"
#endif	/*  __linux__ */

/* Define the mutex type. */
typedef struct MSYS_Mutex_T {
	void * lock;	/* The mutex itself. */
} MSYS_Mutex;

/* We have to use a different header for MSVC due to it's crap support of the C standard. */
#ifdef _MSC_FULL_VER
#include "Windows\MSYS_Mutexes_MSVC.h"
#else

/* Define the functions. */

/*!
 * 	MSYS_Mutex * MSYS_Create_Mutex()
 *
 * 	Creates a MSYS_Mutex object.
 *
 * 	Returns a pointer to the created object if successful.
 * 	Returns NULL otherwise.
 */
MSYS_Mutex * MSYS_Create_Mutex();

/*!
 * 	void MSYS_Destroy_Mutex(MSYS_Mutex * mu)
 *
 * 	Destroys the given mutex.
 *
 * 	This function does not have a return.
 */
void MSYS_Destroy_Mutex(MSYS_Mutex ** mu);

/*!
 * 	MSYS_Mutex * MSYS_Lock_Mutex(MSYS_Mutex * mu)
 *
 * 	Takes the given MSYS_Mutex struct pointer and blocks the
 * 	caller until the lock is acquired.
 *
 * 	Returns the given pointer apon return, when the function returns, the
 * 	lock is guaranteed to be held by the caller.
 *
 * 	WARNING: If you give an invalid pointer to this function,
 * 	it will return without making any changes. In this case
 * 	because the mutex structure is invalid, the lock guarantee
 * 	is revoked.
 *
 * 	(I.e. calling this function with a NULL pointer argument,
 * 	although is not undefined behavior by itself, it will cause
 * 	undefined behavior in the calling program, if your program
 * 	assumes that the mutex was valid prior to the call.)
 * 
 * 	Therefore the lock guarantee is only valid if the given pointers
 * 	are valid.
 */
MSYS_Mutex * MSYS_Lock_Mutex(MSYS_Mutex * mu);

/*!
 * 	short MSYS_Try_Lock_Mutex(MSYS_Mutex ** mu)
 *
 * 	Takes the given MSYS_Mutex struct pointer and blocks the
 * 	caller until a lock attempt is made.
 *
 * 	Returns MSYS_MU_SUCCESS if the lock is aquired and now owned by the
 * 	calling thread.
 *
 * 	Returns MSYS_MU_ALREADY_LOCKED if the lock is already owned by another thread.
 *
 * 	Returns MSYS_MU_ALREADY_OWNED if owned by the calling thread.
 *
 * 	Returns MSYS_MU_INVALID if the given mutex pointer is invalid.
 */
short MSYS_Try_Lock_Mutex(MSYS_Mutex * mu);

/*!
 * 	short MSYS_Unlock_Mutex(MSYS_Mutex * mu)
 *
 * 	Takes the given MSYS_Mutex struct pointer and attempts
 * 	to release the mutex lock.
 *
 * 	Returns MSYS_MU_SUCCESS if successful.
 *
 * 	Returns MSYS_MU_ALREADY_UNLOCKED if the lock is free.
 *
 * 	Returns MSYS_MU_ALREADY_LOCKED the calling thread does not own the lock.
 *
 * 	Returns MSYS_MU_INVALID if the given mutex pointer is invalid.
 */
short MSYS_Unlock_Mutex(MSYS_Mutex * mu);

/*!
 * 	bool MSYS_Compare_And_Swap(bool * address, const bool oldValToCheckFor, const bool newValToWrite)
 *
 * 	The litteral compare and swap method used to allow the creation
 * 	of a mutex lock. This function takes a pointer to a bool, and
 * 	checks it against oldValToCheckFor, if the two values match,
 * 	the bool at the given address is changed to be equal to newValToWrite,
 * 	true is returned to the caller. If the bool at the given address does
 * 	not match oldValToCheckFor, then it is left unaltered, and false is
 * 	returned to the caller. This proceedure is done atomicly to ensure
 * 	accuracy.
 *
 * 	Returns true if the comparison was successful and newValToWrite was
 * 	written successfully to the given memory address.
 *
 * 	Returns false otherwise.
 *
 * 	A note about compilers:
 * 		- This function can only be implimented by compiler extensions, or assembly code.
 * 		  it cannot be implimented by a library, unless that library is staticly linked
 * 		  into the resulting object code. (This is not Thread_Utils, it is an actual implementation.)
 *
 * 		- This function tends to require specific code for each compiler that builds it, as there is
 * 		  no support currently for atomics in the language standard. (Or that is wide spread enough
 * 		  to be implimented in most compilers.) Due to this, if a compiler is used that is not
 * 		  recognised by the code, an #error will be thrown by the preprocessor to indicate that
 * 		  this function must be updated to support that compiler.
 *
 * 		- When adding support for a compiler, only add what is required for getting the atomics needed.
 * 		  DO NOT remove other sections of the code, or change the method signature / return values.
 * 		  Also, care should be made to identify the compiler that the code is for, and to reject
 * 		  attempts to compile the code by a different compiler. (Allow the preprocessor error to
 * 		  be thrown in this instance.)
 */
bool MSYS_Compare_And_Swap(bool * address, const bool oldValToCheckFor, const bool newValToWrite);

/*!
 * 	bool MSYS_Compare_And_Swap(long * address, const long oldValToCheckFor, const long newValToWrite)
 *
 * 	The litteral compare and swap method used to allow the creation
 * 	of a mutex lock. This function takes a pointer to a long, and
 * 	checks it against oldValToCheckFor, if the two values match,
 * 	the long at the given address is changed to be equal to newValToWrite,
 * 	true is returned to the caller. If the long at the given address does
 * 	not match oldValToCheckFor, then it is left unaltered, and false is
 * 	returned to the caller. This proceedure is done atomicly to ensure
 * 	accuracy.
 *
 * 	Returns true if the comparison was successful and newValToWrite was
 * 	written successfully to the given memory address.
 *
 * 	Returns false otherwise.
 *
 * 	A note about compilers:
 * 		- This function can only be implimented by compiler extensions, or assembly code.
 * 		  it cannot be implimented by a library, unless that library is staticly linked
 * 		  into the resulting object code. (This is not Thread_Utils, it is an actual implementation.)
 *
 * 		- This function tends to require specific code for each compiler that builds it, as there is
 * 		  no support currently for atomics in the language standard. (Or that is wide spread enough
 * 		  to be implimented in most compilers.) Due to this, if a compiler is used that is not
 * 		  recognised by the code, an #error will be thrown by the preprocessor to indicate that
 * 		  this function must be updated to support that compiler.
 *
 * 		- When adding support for a compiler, only add what is required for getting the atomics needed.
 * 		  DO NOT remove other sections of the code, or change the method signature / return values.
 * 		  Also, care should be made to identify the compiler that the code is for, and to reject
 * 		  attempts to compile the code by a different compiler. (Allow the preprocessor error to
 * 		  be thrown in this instance.)
 */
bool MSYS_Compare_And_Swap_Long(long * address, const long oldValToCheckFor, const long newValToWrite);

#endif	/* _MSC_FULL_VER */

#ifdef __cplusplus
}	/* extern C */
#endif /* __cplusplus */

#endif	/* MSYS_MUTEXES_H */

/* End of MSYS_Mutexes.h */
