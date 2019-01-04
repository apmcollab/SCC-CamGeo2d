//
//******************************************************************************
//                    ENTITYGRAPHICS.CPP
//******************************************************************************
//
#include "entitygph.h"

#include <cmath>
#include <cstring>
using namespace std;

#ifndef CAM_PI
#define CAM_PI  3.14159265358979323846
#endif
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//                       6/19/97
//
//
//******************************************************************************
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
CAMentityGraphics::CAMentityGraphics(): CAMgraphicsProcess()
{}

void CAMentityGraphics::draw(const CAMpolygonEntity &P)
{
    double*  x = P.getXvertices();
    double*  y = P.getYvertices();
    long     n = P.getSideCount();
    if(n != 0)
    {
	 plot(x,y,n+1);
    }
}

void CAMentityGraphics::draw(const CAMxyRectangleEntity &R)
{
	double  x[5];
	double  y[5];
   double x_a    =  R.getLowerLeftXpoint();
   double y_a    =  R.getLowerLeftYpoint();
   double x_b    =  R.getUpperRightXpoint();
   double y_b    =  R.getUpperRightYpoint();
	x[0] = x_a; y[0] = y_a;
	x[1] = x_b; y[1] = y_a;
	x[2] = x_b; y[2] = y_b;
	x[3] = x_a; y[3] = y_b;
	x[4] = x_a; y[4] = y_a;
	plot(x,y,5);
}

void CAMentityGraphics::draw(const CAMcircleEntity &C)
{
   double center_x = C.getXcenter();
   double center_y = C.getYcenter();
   double radius   = C.getRadius();
	long i;
	long nTheta = 50;
	double dTheta = (2.0*CAM_PI)/double(nTheta);
	double* x = new double[nTheta +1];
	double* y = new double[nTheta +1];
	for(i = 1; i <= 51; i++)
	{
	x[i-1] =  center_x + radius*cos(dTheta*double((i-1)));
	y[i-1] =  center_y + radius*sin(dTheta*double((i-1)));
	}
	plot(x,y,nTheta + 1);

	delete [] x;
   delete [] y;
}

void CAMentityGraphics::draw(const CAMcombinedEntity &E)
{
   CAMcircleEntity      C;
   CAMxyRectangleEntity R;
   CAMpolygonEntity     P;
	for(long i = 0; i < E.getEntityCount(); i++)
	{
     if(strcmp(E[i].getEntityType(),C.getEntityType()) == 0)
     {
        CAMentityGraphics::draw((CAMcircleEntity&)E[i]);
     }
     else
     if(strcmp(E[i].getEntityType(),R.getEntityType()) == 0)
     {
        CAMentityGraphics::draw((CAMxyRectangleEntity&)E[i]);
     }
     else
     if(strcmp(E[i].getEntityType(),P.getEntityType()) == 0)
     {
        CAMentityGraphics::draw((CAMpolygonEntity&)E[i]);
     }
	}
}




 
