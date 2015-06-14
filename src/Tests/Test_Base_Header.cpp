/*!
    Multiverse Engine Project 13/6/2015 Unit Tests Test_Base_Header.cpp

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
#include "Test_Base_Header.h"

void Msys_Sleep(const unsigned int secondsToSleep)
{
		/* Check for valid time to sleep. */
		if (secondsToSleep > 0)
		{
				/* System specific sleep calls below. */
#ifdef _WIN32
				/* Windows SleepEx() takes milliseconds, instead of seconds. */
				SleepEx((secondsToSleep * 1000), false);
#else
				/* Posix sleep(). */
				sleep(secondsToSleep);
#endif	/* _WIN32 */
		}

		/* Exit function. */
		return;
}
