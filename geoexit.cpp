//******************************************************************************
//                    GEOEXIT.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//            6/27/97
//
//
//********************************************************************************
//

/*
#############################################################################
#
# Copyright 1997-2019 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/
#include "geoexit.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

void CAMgeoExit()
{
	cerr << " Fatal Error : Program Stopped " << endl;
	exit(1);
};
void CAMgeoExit(char* ErrorMessage)
{
	cerr << ErrorMessage << endl << endl << endl;
	cerr << " Fatal Error " << endl;
	exit(1);
};

 
