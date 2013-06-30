/*!
    Multiverse Engine Project 21/8/2012 Core UnitTests.cpp
        
    Copyright (C) 2013 Multiverse Engine Project

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

#include "CoreMain.h"
#include "Unit_Tests.h"

#ifdef CORE_UNIT_TESTS_H
int main()
{
        // Init result var.
        int result = 0;

        // Starting Unit tests.
        std::cout << "Multiverse_Engine_Project " << COREVERSION << " Compiled on: " << CORECOMPILEDATE << " " << CORECOMPILETIME << "\n";
        std::cout << "Core Unit tests build\n\n";
        std::cout << "Starting Unit tests for DataProcess::Data_Object. Please be pacent this can take some time.\n";
        result = Unit_Test_Data_Object();
        std::cout << "Result: ";
        std::cout << result <<"\n\n";
        return result;
}

#endif
