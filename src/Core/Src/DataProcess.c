/*!
    Multiverse Engine Project DataProcess DataProcess.c	07/8/2015

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

/* Set extern C. */
#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

/* Internal includes. */
#include "DataProcess.h"

/* External includes. */
#include <time>

size_t DataProcess_Trivial_Random_Number_Generator(const size_t min_value, const size_t max_value, const bool reset_rand)
{
	/* NO, it's not 4..... (Although it could be. I won't lie.) */

	/* Set static. */
	static bool rand_set;

	/* Check if we need to set the RNG. */
	if ((!rand_set) || (reset_rand))
	{
		/* Seed random number generator. */
		srand(time(NULL));

		/* Set rand_set. */
		rand_set = true;
	}

	/* Return the result. */
	return (rand() % max_value + min_value);
}

#ifdef __cplusplus
}	/* End of extern "C". */
#endif	__cplusplus
