//******************************************************************************
//                    GEOEXIT.H
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
#include "camgeoimpexp.h"

#ifndef __CAMGEOEXIT__
#define __CAMGEOEXIT__

void __IMPEXP__ CAMgeoExit();
void __IMPEXP__ CAMgeoExit(char* ErrorMessage);

#ifdef __BCPLUSPLUS__

class __IMPEXP__ CAMgeoException
{
	public :

	CAMgeoException();
	CAMgeoException(const CAMgeoException& C);
	CAMgeoException(char* msg);
    ~CAMgeoException();
    
	char* getMessage() const {return errorMessage;};

	private :

	char* errorMessage;
};
#endif
#endif
 
