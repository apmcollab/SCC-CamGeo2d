#include "camcirc.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#ifndef CAM_PI
#define CAM_PI 3.14159265358979323846
#endif


//
//******************************************************************************
//                    CAMCIRC.CPP
//******************************************************************************
//
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Mon Aug 14 12:23:45 1995
//
//******************************************************************************
//
//
//******************************************************************************
//                    CONSTRUCTORS
//******************************************************************************
//
//
//******************************************************************************
//               
//******************************************************************************
/*
#############################################################################
#
# Copyright 1995-2019 Chris Anderson
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
CAMcircleEntity::CAMcircleEntity(): CAMgeometricEntity()
{
	this->center_x = 0.0;
	this->center_y = 0.0;
	this->radius = 0.0;
	this->start_theta = 0.0;
	this->orientation = 1;
	this->line_tolerance = 1.0e-8;
}

CAMcircleEntity::CAMcircleEntity( const CAMcircleEntity& A): CAMgeometricEntity(A)
{
	this->center_x       = A.center_x;
	this->center_y       = A.center_y;
	this->radius         = A.radius;
	this->start_theta    = A.start_theta;
	this->orientation    = A.orientation;
	this->line_tolerance = A.line_tolerance;
}

CAMcircleEntity::CAMcircleEntity(double x_center, double y_center, double r): CAMgeometricEntity()
{
	this->center_x       = x_center;
	this->center_y       = y_center;
	this->radius         = r;
   this->start_theta    = 0.0;
	this->orientation    = 1;
	this->line_tolerance = 1.0e-8;
}


//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMcircleEntity::~CAMcircleEntity()
{
}

//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//
CAMcircleEntity&  CAMcircleEntity::operator =( const CAMcircleEntity& A)
{
    this->center_x = A.center_x;
    this->center_y = A.center_y;
    this->radius = A.radius;
    this->start_theta = A.start_theta;
	 this->orientation = A.orientation;
	 this->line_tolerance = A.line_tolerance;

	 return *this;
}
//
//********************************************************************************
//                    INITIALIZATION
//********************************************************************************
//
void  CAMcircleEntity::initialize()
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize();

	center_x = 0.0;
	center_y = 0.0;
	radius = 0.0;
	start_theta = 0.0;
	orientation = 1;
	line_tolerance = 1.0e-8;

}
void  CAMcircleEntity::initialize(const CAMcircleEntity& A)
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize(A);

	center_x        = A.center_x;
	center_y        = A.center_y;
	radius          = A.radius;
	start_theta     = A.start_theta;
	orientation     = A.orientation;
	line_tolerance  = A.line_tolerance;
}

void  CAMcircleEntity::initialize(double x_center, double y_center, double r)
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize();

	center_x = x_center;
	center_y = y_center;
	radius = r;
	start_theta = 0.0;
	orientation = 1;
	line_tolerance = 1.0e-8;
}
//
//********************************************************************************
//                    Creation
//********************************************************************************
//
CAMgeometricEntity*  CAMcircleEntity::newDuplicateEntity() const
{
	CAMcircleEntity* R = new CAMcircleEntity(*this);
	return  R;
}
//
//********************************************************************************
//                    Equality/Inequality
//********************************************************************************
//
int  CAMcircleEntity::operator ==(const CAMgeometricEntity &A) const
{
	if(strcmp(A.getEntityType(),getEntityType()) != 0) return 0;
	double* D = new double[4];
	long*   L = new long[1];
	char*   C = 0;
	A.getConstructorData(D,L,C);
	int flag = compareConstructorData(D,L,C);
	delete [] D; delete [] L;

	return flag;
}
int CAMcircleEntity::operator !=(const CAMgeometricEntity &A) const
{
	if(strcmp(A.getEntityType(),getEntityType()) != 0) return 1;
	double* D = new double[4];
	long*   L = new long[1];
	char*   C = 0;
	A.getConstructorData(D,L,C);
	int flag = 1 - compareConstructorData(D,L,C);
	delete [] D; delete [] L;

	return flag;
}
int  CAMcircleEntity::compareConstructorData(double* D, long* L, char*) const
{
   int flag = 1;
   if(D[0] != center_x)    flag = 0;
   if(D[1] != center_y)    flag = 0;
   if(D[2] != radius)      flag = 0;
   if(D[3] != start_theta) flag = 0;
   if(L[0] != orientation) flag = 0;
   return flag;
}
void CAMcircleEntity::getConstructorData(double* D, long* L, char*)  const
{
	D[0] = center_x;
	D[1] = center_y;
	D[2] = radius;
	D[3] = start_theta;
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
void  CAMcircleEntity::output(ostream& out_stream) const
{
	out_stream << "[BEGIN_ENTITY]\n";
   out_stream <<  getEntityType() << "\n";
   out_stream << "[ENTITY_DATA]\n";
   out_stream << center_x << "  " << center_y <<  '\n';
   out_stream << radius   <<  '\n';
   out_stream << orientation << '\n';
   out_stream << "[END_ENTITY]\n";
}
ostream&  operator <<(ostream& out_stream, const CAMcircleEntity& A)
{
	 A.output(out_stream);
    return(out_stream);
}

istream&  operator >>(istream& in_stream, CAMcircleEntity& A)
{
	 A.input(in_stream);
    return(in_stream);
}

void  CAMcircleEntity::input(istream& in_stream)
{
	 char lineInput[256];
    in_stream >> lineInput;
    in_stream >> lineInput;
    inputData(in_stream);
}

void  CAMcircleEntity::inputData(istream& in_stream)
{
	 char lineInput[256];
    in_stream >> lineInput;
    in_stream >> center_x;
    in_stream >> center_y;
    in_stream >> radius;
    in_stream >> orientation;
    in_stream >> lineInput;

    line_tolerance = 1.0e-8;
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//

int CAMcircleEntity::interiorExteriorTest(double xTest, double yTest) const
/*
@begin_doc@
@title    @ interiorExteriorTest()
@Purpose  @ Returns +1 if test point is interior to the circle and
-1 if point is exterior to the circle, otherwise returns 0;
@end_doc  @
*/
{
	double rTest;
	double relTolerance;

	relTolerance = line_tolerance*radius;

	rTest   = sqrt((xTest - center_x)*(xTest - center_x) +
			  (yTest - center_y)*(yTest - center_y));

	if(rTest < radius - relTolerance) return   1;
	if(rTest > radius + relTolerance) return  -1;
	return 0;
}
/*
@begin_doc@
@title    @ getDistanceToBoundary()
@Purpose  @ Returns signed distance to the boundary.(+) for interior distances
(-1) for exterior distances;
@end_doc  @
*/
double CAMcircleEntity::getDistanceToBoundary(double x, double y) const
{
	double rTest;

	rTest   = sqrt((x - center_x)*(x - center_x) +
			  (y - center_y)*(y - center_y));
	return radius - rTest;
}

int  CAMcircleEntity::boundaryTest(double xTest, double yTest) const
/*
@begin_doc@
@title    @ boundaryTest(double xTest, double yTest)
@Purpose  @ Returns 1 if test point is on the boundary of the
circle. Returns 0 otherwise.
@end_doc  @ 
*/
{
	double rTest;
	double relTolerance;

	relTolerance = line_tolerance*radius;

	rTest   = sqrt((xTest - center_x)*(xTest - center_x) +
			  (yTest - center_y)*(yTest - center_y));

	if((rTest > radius - relTolerance)&&
	   (rTest < radius + relTolerance)) return 1;

	return 0;
}
int  CAMcircleEntity::boundaryTest(double s1, double s2, double xTest,
double yTest) const
/*
@begin_doc@
@title    @ boundaryTest(double xTest, double yTest)
@Purpose  @ Returns 1 if the test point is on the boundary of the
circle within the parametric coordinate range [s1, s2].
Returns 0 otherwise.
@end_doc  @ 
*/
{
	double rTest;
	double relTolerance;

	relTolerance = line_tolerance*radius;

	rTest   = sqrt((xTest - center_x)*(xTest - center_x) +
			  (yTest - center_y)*(yTest - center_y));

	if((rTest > radius - relTolerance)&&
	   (rTest < radius + relTolerance))
	{
	double s;
	double theta = atan2(yTest - center_y,xTest - center_x);
	if(theta < 0.0) theta += 2.0*CAM_PI;

	if(theta < start_theta)
	{s = radius*(theta + start_theta);}
	else
	{s = radius*(theta - start_theta);}

	if((s1 <= s)&&(s <= s2)) return 1;
	}
	return 0;
}

void   	  CAMcircleEntity::scaleBy(double alpha)
/*
@begin_doc@
@title    @ scaleBy(double alpha)
@Purpose  @ 
@end_doc  @ 
*/
{
	radius = alpha*radius;
}

void   	  CAMcircleEntity::rotateBy(double theta)
/*
@begin_doc@
@title    @ rotateBy(double theta)
@Purpose  @ 
@end_doc  @ 
*/
{
	start_theta = start_theta + theta;
}

void   	  CAMcircleEntity::translateBy(double x, double y)
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

void   	  CAMcircleEntity::translateTo(double x, double y)
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

double 	  CAMcircleEntity::getMinX() const
/*
@begin_doc@
@title    @ getMinX()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_x - radius;
}

double 	  CAMcircleEntity::getMaxX() const
/*
@begin_doc@
@title    @ getMaxX()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_x + radius;
}

double 	  CAMcircleEntity::getMinY() const
/*
@begin_doc@
@title    @ getMinY()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_y - radius;
}

double 	  CAMcircleEntity::getMaxY() const
/*
@begin_doc@
@title    @ getMaxY()
@Purpose  @ 
@end_doc  @ 
*/
{
	return center_y + radius;
}

double	  CAMcircleEntity::getTotalArcLength() const
/*
@begin_doc@
@title    @ getTotalArcLength()
@Purpose  @ 
@end_doc  @ 
*/
{
	return 2.0*CAM_PI*radius;
}

int	  CAMcircleEntity::getParametricCoordinate(double& s, double x, double y) const
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

	double theta = atan2(y - center_y,x - center_x);
	if(theta < 0.0) theta += 2.0*CAM_PI;

	if(theta < start_theta)
	{s = radius*(theta + start_theta);}
	else
	{s = radius*(theta - start_theta);}

	return 1;
}

int	  CAMcircleEntity::getParametricCoordinate(double& s, double s1, double s2, double x, double y) const
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

	double theta = atan2(y - center_y,x - center_x);
	if(theta < 0.0) theta += 2.0*CAM_PI;

	if(theta < start_theta)
	{s = radius*(theta + start_theta);}
	else
	{s = radius*(theta - start_theta);}

	return 1;
}

double	  CAMcircleEntity::getXcoordinate(double s) const
/*
@begin_doc@
@title    @ getXcoordinate(double s)
@Purpose  @ 
@end_doc  @ 
*/
{
	if((s > radius*2.0*CAM_PI)||(s < 0))
	{cerr << "Error : getXCoordinate argument out of range "
		  << endl; exit(1);}
	return center_x + radius*(cos((s/radius) + start_theta));
}

double	  CAMcircleEntity::getYcoordinate(double s) const
/*
@begin_doc@
@title    @ getYcoordinate(double s)
@Purpose  @ 
@end_doc  @ 
*/
{
	if((s > radius*2.0*CAM_PI)||(s < 0))
	{cerr << "Error : getYCoordinate argument out of range "
		  << endl; exit(1);}
	return center_y + radius*(sin((s/radius) + start_theta));
}

int  CAMcircleEntity::getInteriorPoint(double& x, double& y) const
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

int CAMcircleEntity::getSegmentIntersection(double& intersectPoint, double x_a,
			  double y_a, double x_b, double y_b) const
/*
@begin_doc@
@title    @ getSegmentIntersection(double& intersectPoint, double x_1,
			  double y_1, double x_2, double y_2)
@Purpose  @ 
@end_doc  @ 
*/
{
	double x_ba = x_b  - x_a;
	double y_ba = y_b  - y_a;
	double x_ac = x_a  - center_x;
	double y_ac = y_a  - center_y;

	double a = x_ba*x_ba + y_ba*y_ba;
	double b = 2.0*(x_ac*x_ba + y_ac*y_ba);
	double c = x_ac*x_ac + y_ac*y_ac - radius*radius;

	double s_1; double s_2;
	double x_p; double y_p;
	int returnFlag = 0;

	if(getQuadraticRoots(a, b, c, s_1, s_2) == 0) return 0;

	if((s_1 >=0)&&(s_1 <= 1.0))
	{
	x_p = x_a + s_1*(x_b - x_a);
	y_p = y_a + s_1*(y_b - y_a);
	if(getParametricCoordinate(intersectPoint, x_p, y_p) == 0)
	CAMgeometricEntity::parametricCoordinateError();
	returnFlag = 1;
	}

	if((s_2 >=0)&&(s_2 <= 1.0))
	{
	if(returnFlag == 1)
	{
	    if(s_2 < s_1)
		{
		x_p = x_a + s_2*(x_b - x_a);
		y_p = y_a + s_2*(y_b - y_a);
		if(getParametricCoordinate(intersectPoint, x_p, y_p) == 0)
		CAMgeometricEntity::parametricCoordinateError();
		}
	}
	else
	{
	  x_p = x_a + s_2*(x_b - x_a);
	  y_p = y_a + s_2*(y_b - y_a);
	  if(getParametricCoordinate(intersectPoint, x_p, y_p) == 0)
	  CAMgeometricEntity::parametricCoordinateError();
	  returnFlag = 1;
	}
	}

	return returnFlag;
}

int CAMcircleEntity::getSegmentIntersection(double& intersectPoint, double s_1,
			  double s_2, double x_1, double y_1, double x_2, double y_2) const
/*
@begin_doc@
@title    @ getSegmentIntersection(double& intersectPoint, double s_1,
		      double s_2, double x_1, double y_1, double x_2, double y_2)
@Purpose  @ 
@end_doc  @ 
*/
{
	if(getSegmentIntersection(intersectPoint, x_1,y_1, x_2, y_2) == 1)
	{
    if((intersectPoint >= s_1)&&(intersectPoint <= s_2)) return 1;
	}
	return 0;
}

void  CAMcircleEntity::getUnitNormal(double s, double& n_x, double& n_y) const
/*
@begin_doc@
@title    @ getNormal(double s, double& n_x, double& n_y)
@Purpose  @ 
@end_doc  @ 
*/
{
	if((s > radius*2.0*CAM_PI)||(s < 0))
	{cerr << "Error : getUnitNormal parametric argument out of range "
		  << endl; exit(1);}

	n_x = cos((s/radius) + start_theta);
	n_y = sin((s/radius) + start_theta);
}

void  CAMcircleEntity::getUnitTangent(double s, double& t_x, double& t_y) const
/*
@begin_doc@
@title    @ getTangent(double s, double& t_x, double& t_y)
@Purpose  @ 
@end_doc  @ 
*/
{
	if((s > radius*2.0*CAM_PI)||(s < 0))
	{cerr << "Error : getUnitTangent parametric argument out of range "
		  << endl; exit(1);}

	t_x = -sin((s/radius) + start_theta);
	t_y =  cos((s/radius) + start_theta);
}
//
//********************************************************************************
//                    INTERNAL MEMBER_FUNCTIONS
//********************************************************************************
//
int  CAMcircleEntity::getQuadraticRoots(double a, double b, double c, double& r_1, double& r_2)
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

 
