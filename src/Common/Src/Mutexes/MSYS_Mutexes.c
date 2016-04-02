/*!
    Multiverse Engine Project 17/3/2015 Common MSYS_Mutexes.c

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

/* Internal includes. */
#include "MSYS_Mutexes.h"

/* Define extern C */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/*!
 * 	typedef struct MSYS_Mutex_Private
 *
 * 	Defines a basic mutex type.
 * 	(It's a struct instead of a typedef as a precatuion to allow future modifications.)
 *
 * 	Note: This is the real mutex data structure. The other one exists as the public interface
 * 	so that we can hide the real implmentation.
 */
typedef struct {
	/* Define the lock. */
/*!
 * 	MSYS_INSUFFIENCT_BITS_LONG_LOCK
 *
 * 	This definintion is defined if the target system does
 * 	not support long integers with an atomic compare and
 * 	swap operation.
 *
 * 	If this definintion is NOT defined, then the code
 * 	generated will use tidLock for all operations.
 * 	(I.e. If tidLock != 0, then the mutex is locked;
 * 	 If tidLock == 0, then the mutex is unlocked.)
 *
 * 	If this definintion is defined, then the code generated
 * 	will use a boolean lock (one bit lock) for mutexes.
 * 	The tidLock variable will then be used to confirm
 * 	the ownership of a lock prior to allowing a thread
 * 	to unlock it.
 *
 * 	This behavior is not exactly safe, as the check
 * 	for ownership could fail due to the tidLock
 * 	variable being updated simulatiously. Therefore
 * 	care must be made by us to prevent any updates
 * 	to tidLock from occuring while the check is being
 * 	made. Currently this is done by the MSYS_Lock_Mutex()
 * 	function only performing an update if the lock on the
 * 	boolean succeeds, and MSYS_Unlock_Mutex() only
 * 	performing a check if the boolean is locked.
 * 	(I.e. If lock == true, then tidLock != 0;
 * 	 If lock == false, then tidLock == 0.)
 *
 * 	Although we really need to hide the mutex structure
 * 	from prying eyes, to help prevent that.......
 */
#ifdef MSYS_INSUFFIENCT_BITS_LONG_LOCK
	bool lock;												/*
															 *  Whether or not the lock is aquired or in the process of being acquired.
															 *
															 *  This value is declared when the host system cannot support reading and
															 *  writing tidLock atomicly.
															 *
															 *  It is used as a memory barrior for checking the tidLock value for ownership,
															 *  along with any possible modifications, and is released apon completion of
															 *  the check and after any possible modifications have been flushed to memory.
															 */
#endif	/* MSYS_INSUFFIENCT_BITS_LONG_LOCK */
	long tidLock;		/*
				 *  The owner of the lock. (Set to zero if there is no owner.)
				 *
				 *  On host systems that support writing to this variable atomicly,
				 *  this variable is the lock, as well as the id for who owns the
				 *  lock.
				 *
				 *  If the host system lacks support to write this value atomicly,
				 *  then the MSYS_INSUFFIENCT_BITS_LONG_LOCK flag should be defined
				 *  at build time. In that case, tidLock is not the lock variable, but
				 *  does still keep track of ownership.
				 */
} MSYS_Mutex_Private;

MSYS_Mutex * MSYS_Create_Mutex()
{
	/* Init vars. */
	MSYS_Mutex * ret = NULL;			/* The result of this function. */
	MSYS_Mutex_Private * temp = NULL;	/* Temporary pointer to allocate the mutex. */

	/* Allocate memory. */
	ret = (MSYS_Mutex *)malloc((sizeof(MSYS_Mutex)));
	if (ret != NULL)
	{
		/* Allocate the real data structure. */
		temp = (MSYS_Mutex_Private *)malloc((sizeof(MSYS_Mutex_Private)));
		if (temp != NULL)
		{
			/* Set initial data. */
#ifdef MSYS_INSUFFIENCT_BITS_LONG_LOCK
			temp->lock = false;	/* Only defined when the host system does not support reading / writing to tidLock atomicly. */
#endif	/* MSYS_INSUFFIENCT_BITS_LONG_LOCK */
			temp->tidLock = MSYS_INVALID_TID;

			/* Copy the pointer. */
			ret->lock = (void *)temp;
		}
		else
		{
			/* Deallocate ret. */
			free(ret);
			ret = NULL;
		}
	}

	/* Return the result. */
	return ret;
}

void MSYS_Destroy_Mutex(MSYS_Mutex ** mu)
{
	/* Check for valid pointers. */
	if ((mu != NULL) && (*mu != NULL))
	{
		/* Check for valid real structure. */
		if ((*mu)->lock != NULL)
		{
			free((*mu)->lock);
			(*mu)->lock = NULL;
		}
		free(*mu);
		*mu = NULL;
	}

	/* Exit function. */
	return;
}

MSYS_Mutex * MSYS_Lock_Mutex(MSYS_Mutex * mu)
{
	/*
	 * 	Run down of this function:
	 *
	 * 	1. Check for valid mutex structure and abort if the pointer is NULL.
	 * 	2. Call MSYS_Try_Lock_Mutex() until the lock succeeds.
	 */

	/* Init vars. */
	int retFromLOCK = MSYS_MU_UNKNOWN_ERROR;		/* Result from MSYS_Compare_And_Swap(). */
	MSYS_Mutex * ret = NULL;						/* Result from this function. */

	/* Make sure mu and mu->lock are valid pointers. */
	if ((mu != NULL) && (mu->lock != NULL))
	{
		/* Begin loop. */
		while ((retFromLOCK != MSYS_MU_SUCCESS) || (retFromLOCK != MSYS_MU_ALREADY_OWNED))
		{
			/* Attempt to lock the mutex. */
			retFromLOCK = MSYS_Try_Lock_Mutex(mu);
		}

		/* Successfull. */
		ret = mu;
	}

	/* Exit function. */
	return ret;
}

short MSYS_Try_Lock_Mutex(MSYS_Mutex * mu)
{
	/*
	 * 	Run down of this function:
	 *
	 * 	For systems that cannot support reading and writing to tidLock atomicly:
	 * 	1. Check for valid mutex structure and abort if the pointer is NULL.
	 * 	2. Get the calling thread's thread ID.
	 * 	3. Gain ownership of mu->lock.
	 * 	4. Check for an unowned mutex by checking to see if mu->tidLock is equal to MSYS_INVALID_TID.
	 * 		4.a. If the check fails, release ownership of mu->lock and exit the function.
	 * 
	 * 	STEPS BELOW ONLY OCCUR IF THE MUTEX IS UNOWNED.
	 * 	5. Write the calling thread's thread ID to mu->tidLock.
	 * 	6. Set the result of the function to indicate success.
	 * 	7. Flush memory by calling MSYS_Sync_Memory().
	 * 	8. Release ownership of mu->lock.
	 * 	9. Return the result of the function.
	 *
	 * 	For systems that can read and write to tidLock atomicly:
	 * 	1. Check for valid mutex structure and abort if the pointer is NULL.
	 * 	2. Get the calling thread's thread ID.
	 *
	 * 	3. Attempt to lock the mutex by calling MSYS_Compare_And_Swap() on mu->tidLock,
	 * 	with MSYS_INVALID_TID as the check value, and the calling thread's thread ID as the value to write if the check succeeds.
	 *
	 * 	4. Return the result of the call to MSYS_Compare_And_Swap() as the result of the function.
	 */
  
	/* Init vars. */
	bool retFromCAS = false;			/* Result from MSYS_Compare_And_Swap(). */
	short ret = MSYS_MU_UNKNOWN_ERROR;	/* The result of this function. */
	long tid = MSYS_INVALID_TID;		/* Result from MSYS_Get_Thread_ID(). */

	/* Make sure mu and mu->lock are valid pointers. */
	if ((mu != NULL) && (mu->lock != NULL))
	{
		/* Get the thread ID. */
		tid = MSYS_Get_Thread_ID();

#ifdef MSYS_INSUFFIENCT_BITS_LONG_LOCK
		/* Call compiler specific function for compare and swap. */
		while (!retFromCAS)
		{
			/* Indefinite wait..... */
			retFromCAS = MSYS_Compare_And_Swap((&((MSYS_Mutex_Private *)mu->lock)->lock), FALSE, TRUE);
		}

		/* Check for ownership. */
		if (((MSYS_Mutex_Private *)mu->lock)->tidLock == MSYS_INVALID_TID)
		{
			/* Lock the mutex with the calling thread's thread ID. */
			((MSYS_Mutex_Private *)mu->lock)->tidLock = tid;

			/* Set ret. */
			ret = MSYS_MU_SUCCESS;

			/* Flush memory changes. */
			MSYS_Sync_Memory();
		}
		else
		{
			/* Check and see if we own the lock. */
			if (((MSYS_Mutex_Private *)mu->lock)->tidLock == tid)
			{
				/* Lock is already held by us. */
				ret = MSYS_MU_ALREADY_OWNED;
			}
			else
			{
				/* Lock is owned by someone else. */
				ret = MSYS_MU_ALREADY_LOCKED;
			}
		}

		/* Release the lock. */
		MSYS_Compare_And_Swap((&((MSYS_Mutex_Private *)mu->lock)->lock), TRUE, FALSE);
#else
		/* Attempt to lock the mutex. */
		retFromCAS = MSYS_Compare_And_Swap_Long((&((MSYS_Mutex_Private *)mu->lock)->tidLock), MSYS_INVALID_TID, tid);
		if (retFromCAS == TRUE)
		{
			/* Set ret. */
			ret = MSYS_MU_SUCCESS;
		}
		else
		{
			/* Check and see if we own the lock. */
			retFromCAS = MSYS_Compare_And_Swap_Long((&((MSYS_Mutex_Private *)mu->lock)->tidLock), tid, tid);
			if (retFromCAS)
			{
				/* Lock is already held by us. */
				ret = MSYS_MU_ALREADY_OWNED;
			}
			else
			{
				/* Lock is owned by someone else. */
				ret = MSYS_MU_ALREADY_LOCKED;
			}
		}
#endif	/* MSYS_INSUFFIENCT_BITS_LONG_LOCK */
	}

	/* Return the result. */
	return ret;
}

short MSYS_Unlock_Mutex(MSYS_Mutex * mu)
{
	/*
	 * 	Run down of this function:
	 *
	 * 	For systems that cannot support reading and writing to tidLock atomicly:
	 * 	1. Check for valid mutex structure and abort if the pointer is NULL.
	 * 	2. Get the calling thread's thread ID.
	 * 	3. Gain ownership of mu->lock.
	 * 	4. Check for ownership of the mutex by checking to see if mu->tidLock is equal to the calling thread's thread ID.
	 * 		4.a. If the calling thread owns the mutex, then release ownership by writing the MSYS_INVALID_TID value to mu->tidLock.
	 * 		4.b. Flush memory by calling MSYS_Sync_Memory().
	 * 	5. Release ownership of mu->lock.
	 *
	 * 	For systems that can read and write to tidLock atomicly:
	 * 	1. Check for valid mutex structure and abort if the pointer is NULL.
	 * 	2. Get the calling thread's thread ID.
	 *
	 * 	3. Attempt to release the mutex lock by calling MSYS_Compare_And_Swap() on mu->tidLock,
	 * 	with the calling thread's thread ID as the check value, and MSYS_INVALID_TID as the value to write if the check succeeds.
	 */

	/* Init vars. */
	bool retFromCAS = false;			/* Result from MSYS_Compare_And_Swap(). */
	short ret = MSYS_MU_UNKNOWN_ERROR;	/* Result from this function. */
	long tid = MSYS_INVALID_TID;		/* Result from MSYS_Get_Thread_ID(). */

	/* Make sure mu and mu->lock are valid pointers. */
	if ((mu != NULL) && (mu->lock != NULL))
	{
		/* Get the thread ID. */
		tid = MSYS_Get_Thread_ID();

		/*
		 *	It seems that in some libraries, attempting to unlock an unowned mutex will result in undefined behavior on some systems.
		 *	(Pthreads) In our case we simply return if the mutex is not locked by us. 
		 * 
		 *	A lock attempt is required by us to complete successfully before control is returned to the caller (ie. memory must be
		 *	sync'd before control is returned to the caller.), therefore there is not a possibility to run into a race condition
		 *	during an unlock attempt if the thread attempting to unlock the mutex is the same one as the one that locked it.
		 *
		 *	For other threads, the initial compare and swap to gain hold over the lock variable, prevents another thread
		 *	from attempting to access tidLock while it is being accessed in our thread.
		 */
		/* Call compiler specific function for compare and swap. */
#ifdef MSYS_INSUFFIENCT_BITS_LONG_LOCK
		/* Begin waiting loop. */
		while (!retFromCAS)
		{
			/* Wait until we get the lock we need to check the tidLock value. */
			retFromCAS = MSYS_Compare_And_Swap((&((MSYS_Mutex_Private *)mu->lock)->lock), FALSE, TRUE);
		}

		/* Perform ownership check on tidLock. */
		if (((MSYS_Mutex_Private *)mu->lock)->tidLock == tid)
		{
			/* This mutex is locked by us, so release the lock. */
			((MSYS_Mutex_Private *)mu->lock)->tidLock = MSYS_INVALID_TID;

			/* Resync memory. */
			MSYS_Sync_Memory();

			/* Successfull. */
			ret = MSYS_MU_SUCCESS;
		}
		else
		{
			/* Check whether lock is owned by another thread, or is unowned. */
			if (((MSYS_Mutex_Private *)mu->lock)->tidLock == MSYS_INVALID_TID)
			{
				/* The mutex is not owned by anyone. */
				ret = MSYS_MU_ALREADY_UNLOCKED;
			}
			else
			{
				/* The mutex is locked by another thread. */
				ret = MSYS_MU_ALREADY_LOCKED;
			}
		}

		/* Release the lock. */
		MSYS_Compare_And_Swap((&((MSYS_Mutex_Private *)mu->lock)->lock), TRUE, FALSE);
#else
		retFromCAS = MSYS_Compare_And_Swap_Long((&((MSYS_Mutex_Private *)mu->lock)->tidLock), tid, MSYS_INVALID_TID);
		if (retFromCAS)
		{
			/* Successfull. */
			ret = MSYS_MU_SUCCESS;
		}
		else
		{
			/* Check whether lock is owned by another thread, or is unowned. */
			retFromCAS = MSYS_Compare_And_Swap_Long((&((MSYS_Mutex_Private *)mu->lock)->tidLock), MSYS_INVALID_TID, MSYS_INVALID_TID);
			if (retFromCAS == TRUE)
			{
				/* The mutex is not owned by anyone. */
				ret = MSYS_MU_ALREADY_UNLOCKED;
			}
			else
			{
				/* The mutex is locked by another thread. */
				ret = MSYS_MU_ALREADY_LOCKED;
			}
		}
#endif	/* MSYS_INSUFFIENCT_BITS_LONG_LOCK */
	}

	/* Exit function. */
	return ret;
}

#ifdef __cplusplus
}	/* extern C */
#endif	/* __cplusplus */

/* End of MSYS_Mutexes.c */
