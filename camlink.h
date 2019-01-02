//
//******************************************************************************
//                    CAMLINK.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//            2/11/97
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

#include <cstring>
using namespace std;

#include "camgeoimpexp.h"

#ifndef __CAM_LINK__
#define __CAM_LINK__

class __IMPEXP__ CAMlink
{
    public :
    
	 static int onLink(double xa, double ya, double xb, double yb,
    double xp, double yp, double tol, double& s, double& d);

    static int onConnectedLinks(double* X, double*Y , long nLinks,
    double xp, double yp, double tol, long& linkIndex, double& s);

    static int linkIntersection(double* Qx, double* Qy, double *Rx , double* Ry,
    double tol, double& s);

    private :

    static double normalize(double s);
};
#endif
//
//********************************************************************************
//                     Header File End
//********************************************************************************
// 
