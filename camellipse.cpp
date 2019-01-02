#include "camellipse.h"

#include <cmath>
#include <cstring>
using namespace std;

#ifndef CAM_PI
#define CAM_PI 3.14159265358979323846
#endif
//
//******************************************************************************
//                    CAMELLIPSE.CPP
//******************************************************************************
//
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 2002
//
//            Sept. 4, 2002
//
//******************************************************************************
//
//
// Under construction : the only things that are working are the i/o
// initialization and in/out testing.
//
// I need to come back and fix up the rest later.
//
//******************************************************************************
//                    CONSTRUCTORS
//******************************************************************************
//
//
//******************************************************************************
//               
//******************************************************************************
//
/*
#############################################################################
#
# Copyright 2002-2019 Chris Anderson
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
CAMellipseEntity::CAMellipseEntity(): CAMgeometricEntity()
{
    initialize();
}

CAMellipseEntity::CAMellipseEntity(const CAMellipseEntity& A) 
{
	initialize(A);
}

CAMellipseEntity::CAMellipseEntity(double x_center, double y_center, double radius_x, 
double radius_y, double theta)
{
	initialize(x_center,y_center,radius_x,radius_y,theta);
}

//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMellipseEntity::~CAMellipseEntity()
{}

//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//
CAMellipseEntity&  CAMellipseEntity::operator =( const CAMellipseEntity& A)
{
    initialize(A);
    return *this;
}
//
//********************************************************************************
//                    INITIALIZATION
//********************************************************************************
//
void  CAMellipseEntity::initialize()
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize();

	this->center_x = 0.0;
	this->center_y = 0.0;
	this->radius_x = 0.0;
	this->radius_y = 0.0;
	this->theta = 0.0;
	this->orientation = 1;
	this->line_tolerance = 1.0e-8;
}
void  CAMellipseEntity::initialize(const CAMellipseEntity& A)
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize(A);

	this->center_x       = A.center_x;
	this->center_y       = A.center_y;
	this->radius_x       = A.radius_x;
	this->radius_y       = A.radius_y;
	this->theta          = A.theta;
	this->orientation    = A.orientation;
	this->line_tolerance = A.line_tolerance;
}

void  CAMellipseEntity::initialize(double x_center, double y_center, double radius_x, 
double radius_y, double theta)
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize();

	this->center_x       = x_center;
	this->center_y       = y_center;
	this->radius_x       = radius_x;
	this->radius_y       = radius_y;
	this->theta          = theta;
	this->orientation    = 1;
	this->line_tolerance = 1.0e-8;
}
//
//********************************************************************************
//                    Creation
//********************************************************************************
//
CAMgeometricEntity*  CAMellipseEntity::newDuplicateEntity() const
{
	CAMellipseEntity* R = new CAMellipseEntity(*this);
	return  R;
}
//
//********************************************************************************
//                    Equality/Inequality
//********************************************************************************
//
int  CAMellipseEntity::operator ==(const CAMgeometricEntity &A) const
{
	if(strcmp(A.getEntityType(),getEntityType()) != 0) return 0;
	double* D = new double[5];
	long*   L = new long[1];
	char*   C = 0;
	A.getConstructorData(D,L,C);
	int flag = compareConstructorData(D,L,C);
	delete [] D; delete [] L;

	return flag;
}
int CAMellipseEntity::operator !=(const CAMgeometricEntity &A) const
{
	if(strcmp(A.getEntityType(),getEntityType()) != 0) return 1;
	double* D = new double[5];
	long*   L = new long[1];
	char*   C = 0;
	A.getConstructorData(D,L,C);
	int flag = 1 - compareConstructorData(D,L,C);
	delete [] D; delete [] L;

	return flag;
}
int  CAMellipseEntity::compareConstructorData(double* D, long* L, char*) const
{
   int flag = 1;
   if(D[0] != center_x)   flag = 0;
   if(D[1] != center_y)   flag = 0;
   if(D[2] != radius_x)   flag = 0;
   if(D[3] != radius_y)   flag = 0;
   if(D[4] != theta)      flag = 0;


   if(L[0] != orientation) flag = 0;
   return flag;
}
void CAMellipseEntity::getConstructorData(double* D, long* L, char*)  const
{
	D[0] = center_x;
	D[1] = center_y;
	D[2] = radius_x;
	D[3] = radius_y;
	D[4] = theta;
	L[0] = orientation;
}
//
//******************************************************************************
//                    MEMBER_FUNCTIONS
//******************************************************************************
//
//
//******************************************************************************
//                    INPUT/OUTPUT
//******************************************************************************
//
void  CAMellipseEntity::output(ostream& out_stream) const
{
   out_stream << "[BEGIN_ENTITY]\n";
   out_stream <<  getEntityType() << "\n";
   out_stream << "[ENTITY_DATA]\n";
   out_stream << center_x << "  " << center_y <<  '\n';
   out_stream << radius_x << "  " << radius_y <<  '\n';
   out_stream << theta    <<   '\n';
   out_stream << orientation << '\n';
   out_stream << "[END_ENTITY]\n";
}
ostream&  operator <<(ostream& out_stream, const CAMellipseEntity& A)
{
	 A.output(out_stream);
    return(out_stream);
}

istream&  operator >>(istream& in_stream, CAMellipseEntity& A)
{
	 A.input(in_stream);
    return(in_stream);
}

void  CAMellipseEntity::input(istream& in_stream)
{
	 char lineInput[256];
    in_stream >> lineInput;
    in_stream >> lineInput;
    inputData(in_stream);
}

void  CAMellipseEntity::inputData(istream& in_stream)
{
	 char lineInput[256];
    in_stream >> lineInput;
    in_stream >> center_x;
    in_stream >> center_y;
    in_stream >> radius_x;
    in_stream >> radius_y;
    in_stream >> theta;
    in_stream >> orientation;
    in_stream >> lineInput;

    line_tolerance = 1.0e-8;
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//

int CAMellipseEntity::interiorExteriorTest(double xTest, double yTest) const
/*
@begin_doc@
@title    @ interiorExteriorTest()
@Purpose  @ Returns +1 if test point is interior to the ellipse and
-1 if point is exterior to the ellipse, otherwise returns 0;
@end_doc  @
*/
{
    double rTest;

    double xp; double yp;

    double ct = cos(theta);
    double st = sin(theta);

    xp = ct*(xTest - center_x) - st*(yTest - center_y);
    yp = st*(xTest - center_x) + ct*(yTest - center_y);

	rTest   =  (xp*xp)/(radius_x*radius_x) 
             + (yp*yp)/(radius_y*radius_y);

	if(rTest < 1.0 - line_tolerance) return   1;
	if(rTest > 1.0 + line_tolerance) return  -1;

	return 0;
}

double CAMellipseEntity::getDistanceToBoundary(double x, double y) const
{


	return 0.0;
}

int  CAMellipseEntity::boundaryTest(double xTest, double yTest) const
/*
@begin_doc@
@title    @ boundaryTest(double xTest, double yTest)
@Purpose  @ Returns 1 if test point is on the boundary of the
ellipse. Returns 0 otherwise.
@end_doc  @ 
*/
{
    double rTest;

    double xp; double yp;

    double ct = cos(theta);
    double st = sin(theta);

    xp = ct*(xTest - center_x) - st*(yTest - center_y);
    yp = st*(xTest - center_x) + ct*(yTest - center_y);

	rTest   =  (xp*xp)/(radius_x*radius_x) 
             + (yp*yp)/(radius_y*radius_y);

	if(rTest < 1.0 - line_tolerance) return   1;
	if(rTest > 1.0 + line_tolerance) return  -1;

	return 0;


	if((rTest > 1.0 - line_tolerance)&&
	   (rTest < 1.0 + line_tolerance)) return 1;

	return 0;
}
int  CAMellipseEntity::boundaryTest(double s1, double s2, double xTest,
double yTest) const
/*
@begin_doc@
@title    @ boundaryTest(double xTest, double yTest)
@Purpose  @ Returns 1 if the test point is on the boundary of the
ellipse within the parametric coordinate range [s1, s2].
Returns 0 otherwise.
@end_doc  @ 
*/
{
	return 0;
}

void   	  CAMellipseEntity::scaleBy(double alpha)
/*
@begin_doc@
@title    @ scaleBy(double alpha)
@Purpose  @ 
@end_doc  @ 
*/
{
	radius_x = alpha*radius_x;
	radius_y = alpha*radius_y;
}

void   	  CAMellipseEntity::rotateBy(double theta)
/*
@begin_doc@
@title    @ rotateBy(double theta)
@Purpose  @ 
@end_doc  @ 
*/
{
	this->theta += theta;
}

void   	  CAMellipseEntity::translateBy(double x, double y)
/*
@begin_doc@
@title    @ translateBy(double x, double y)
@Purpose  @ 
@end_doc  @ 
*/
{
	center_x = center_x + x;
	center_y = center_y + y;
}

void   	  CAMellipseEntity::translateTo(double x, double y)
/*
@begin_doc@
@title    @ translateTo(double x, double y)
@Purpose  @ 
@end_doc  @ 
*/
{
	center_x = x;
	center_y = y;
}

double 	  CAMellipseEntity::getMinX() const
/*
@begin_doc@
@title    @ getMinX()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_x - radius_x;
}

double 	  CAMellipseEntity::getMaxX() const
/*
@begin_doc@
@title    @ getMaxX()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_x + radius_x;
}

double 	  CAMellipseEntity::getMinY() const
/*
@begin_doc@
@title    @ getMinY()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_y - radius_y;
}

double 	  CAMellipseEntity::getMaxY() const
/*
@begin_doc@
@title    @ getMaxY()
@Purpose  @ 
@end_doc  @  
*/
{
	return center_y + radius_y;
}

double	  CAMellipseEntity::getTotalArcLength() const
/*
@begin_doc@
@title    @ getTotalArcLength()
@Purpose  @ 
@end_doc  @ 
*/
{
	return 2.0*CAM_PI*radius_x;
}

int	  CAMellipseEntity::getParametricCoordinate(double& s, double x, double y) const
/*
@begin_doc@
@title    @ getParametricCoordinate(double& s, double x, double y)
@Purpose  @ This routine gets the parametric coordinate of the
point (x,y). If the point is not on the curve the routine returns
0, otherwise the routine returns a value of 1, and the variable s
is assigned to the parametric coordinate value.
@end_doc  @
*/
{
	if(boundaryTest(x,y) == 0)
	{return 0;}

	return 1;
}

int	  CAMellipseEntity::getParametricCoordinate(double& s, double s1, double s2, double x, double y) const
/*
@begin_doc@
@title    @ getParametricCoordinate(double& s, double s1, double s2, double x, double y)
@Purpose  @ This routine gets the parametric coordinate of the
point (x,y) when the cooresponding parametric coordinate of
the point is between s1 and s2.
If the point is not on the curve within the parametric coordinate
range [s1,s2] the routine returns
0, otherwise the routine returns a value of 1, and the variable s
is assigned to the parametric coordinate value.
@end_doc  @
*/
{
	if(boundaryTest(s1,s2,x,y) == 0)
	{return 0;}

	return 1;
}

double	  CAMellipseEntity::getXcoordinate(double s) const
/*
@begin_doc@
@title    @ getXcoordinate(double s)
@Purpose  @ 
@end_doc  @ 
*/
{

	return 0.0;
}

double	  CAMellipseEntity::getYcoordinate(double s) const
/*
@begin_doc@
@title    @ getYcoordinate(double s)
@Purpose  @ 
@end_doc  @ 
*/
{
	return 0.0;
}

int  CAMellipseEntity::getInteriorPoint(double& x, double& y) const
/*
@begin_doc@
@title    @ getInteriorPoint(double& x, double& y)
@Purpose  @ 
@end_doc  @ 
*/
{
	x = center_x;
    y = center_y;
	return 1;
}

int CAMellipseEntity::getSegmentIntersection(double& intersectPoint, double x_a,
			  double y_a, double x_b, double y_b) const
/*
@begin_doc@
@title    @ getSegmentIntersection(double& intersectPoint, double x_1,
			  double y_1, double x_2, double y_2)
@Purpose  @ 
@end_doc  @ 
*/
{
	return 0;
}

int CAMellipseEntity::getSegmentIntersection(double& intersectPoint, double s_1,
			  double s_2, double x_1, double y_1, double x_2, double y_2) const
/*
@begin_doc@
@title    @ getSegmentIntersection(double& intersectPoint, double s_1,
		      double s_2, double x_1, double y_1, double x_2, double y_2)
@Purpose  @ 
@end_doc  @ 
*/
{
	return 0;
}

void  CAMellipseEntity::getUnitNormal(double s, double& n_x, double& n_y) const
/*
@begin_doc@
@title    @ getNormal(double s, double& n_x, double& n_y)
@Purpose  @ 
@end_doc  @ 
*/
{
}

void  CAMellipseEntity::getUnitTangent(double s, double& t_x, double& t_y) const
/*
@begin_doc@
@title    @ getTangent(double s, double& t_x, double& t_y)
@Purpose  @ 
@end_doc  @ 
*/
{
}
//
//********************************************************************************
//                    INTERNAL MEMBER_FUNCTIONS
//********************************************************************************
//
int  CAMellipseEntity::getQuadraticRoots(double a, double b, double c, double& r_1, double& r_2)
/*
@begin_doc@
@title    @ getQuadraticRoots(double a, double b, double c, double& r_1, double r_2)
@Purpose  @ 
@end_doc  @ 
*/
//
// Added b== 0 and c==0 code 1/15/98 CRA
//
{
    double discriminant = (b*b - 4.0*a*c);
    if( (discriminant < 0)||
        ((a == 0.0)&&(b == 0))
      ) return 0;

	 if((b == 0)&&(c==0))
	 {
	  r_1 = 0.0;
	  r_2 = 0.0;
	  return 1;
	 }
	 
    if(a == 0.0)
    {
	  r_1 = -c/b;
	  r_2 = -c/b;
	  return 1;
    }

	 double sqrtD;
	 if(discriminant == 0.0)
	 {sqrtD = 0.0;}
	 else
	 {sqrtD  = sqrt(discriminant);}
	 
    if(b >= 0)
    {
        r_1 = (-2.0*c)/(b + sqrtD);
        r_2 = ((-b) - sqrtD)/(2.0*a);
    }
    else
    {
        r_1 = ((-b) + sqrtD)/(2.0*a);
        r_2 = (-2.0*c)/(b - sqrtD);
    }
    return 1;
}

//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//

 
