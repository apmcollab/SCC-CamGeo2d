
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "campoly.h"
#include "camlink.h"


#define LINE_TOLERANCE 1.0e-08
//
//******************************************************************************
//                    CAMPOLY.CPP
//******************************************************************************
//
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1997
//
//            Jan. 28, 1997
//
//******************************************************************************
//
// Notes : n is the number of sides of the polygon.
// It is always assumed to be closed -- so the constructor takes
// the n vertices which define the polygon.
//
// Internally I use arrays of size n+1 to store the vertices.
// I do this to avoid having to create
// arrays with wrap-around points for the utility routines
// which are called.
//
// The "external" indexing for the vertices starts at 1
//
// Segment (or side) indexing starts at 1
//
// The polygon is parameterized by arclength
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
//******************************************************************************
//                    CONSTRUCTORS
//******************************************************************************
//
//
//********************************************************************************
//               
//********************************************************************************
//
CAMpolygonEntity::CAMpolygonEntity(): CAMgeometricEntity()
{
    x = 0;
    y = 0;
    n = 0;

	 orientation    = 1;
	 line_tolerance = LINE_TOLERANCE;
    arcLengthBase  = 0;
    
    BBoxXmin       = 0.0;
    BBoxXmax       = 0.0;
    BBoxYmin       = 0.0;
    BBoxYmax       = 0.0;

    xInterior      = 0.0;
    yInterior      = 0.0;
}

CAMpolygonEntity::CAMpolygonEntity( const CAMpolygonEntity& A): CAMgeometricEntity(A)
{
    long i;
    if(A.n != 0)
    {
    n             = A.n;
    x             = new double[n+1];
    y             = new double[n+1];
    arcLengthBase = new double[n+1];
    for(i = 0; i <= n; i++)
    {
    x[i]             = A.x[i];
    y[i]             = A.y[i];
    arcLengthBase[i] = A.arcLengthBase[i];}
    }
    else
    {
    x = 0; y = 0; n = 0; arcLengthBase = 0;
    }

	orientation    = A.orientation;
	line_tolerance = A.line_tolerance;

   BBoxXmin       = A.BBoxXmin;
   BBoxXmax       = A.BBoxXmax;
   BBoxYmin       = A.BBoxYmin;
   BBoxYmax       = A.BBoxYmax;

   xInterior      = A.xInterior;
   yInterior      = A.yInterior;

}

CAMpolygonEntity::CAMpolygonEntity(double* xVertex, double* yVertex, long nSides)
: CAMgeometricEntity()
{
    long i;
    if(nSides != 0)
    {
    n = nSides;
    x             = new double[n+1];
    y             = new double[n+1];
    arcLengthBase = new double[n+1];
    for(i = 0; i < n; i++)
    {x[i] = xVertex[i]; y[i] = yVertex[i];}
    x[n]  = x[0];       y[n] = y[0];
    computeArcLengthBase();
    setBoundingBox();
    }
    else
    {
    x = 0; y = 0; n = 0; arcLengthBase = 0;
    }

	orientation    = 1;
	line_tolerance = LINE_TOLERANCE;

    if(nSides != 0)
    {computeInteriorPoint();}

}
//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMpolygonEntity::~CAMpolygonEntity()
{
	if(x != 0) delete [] x;
    if(y != 0) delete [] y;
    if(arcLengthBase != 0) delete [] arcLengthBase;
}
//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//
CAMpolygonEntity&  CAMpolygonEntity::operator =( const CAMpolygonEntity& A)
{
    long i;
    if((n == 0)&&(A.n != 0))
    {

    n             = A.n;
    x             = new double[n+1];
    y             = new double[n+1];
    arcLengthBase = new double[n+1];
    for(i = 0; i <= n; i++)
    {
    x[i]             = A.x[i];
    y[i]             = A.y[i];
    arcLengthBase[i] = A.arcLengthBase[i];
    }

    }
    else if((x != A.x)&&(y != A.y))
    {
    delete [] x; delete [] y; delete [] arcLengthBase;
    n = A.n;
    x = new double[n+1]; y = new double[n+1]; arcLengthBase = new double[n+1];
    for(i = 0; i <= n; i++)
    {
    x[i]             = A.x[i];
    y[i]             = A.y[i];
    arcLengthBase[i] = A.arcLengthBase[i];
    }

    }

	orientation    = A.orientation;
	line_tolerance = A.line_tolerance;

    BBoxXmin       = A.BBoxXmin;
    BBoxXmax       = A.BBoxXmax;
    BBoxYmin       = A.BBoxYmin;
    BBoxYmax       = A.BBoxYmax;

    xInterior      = A.xInterior;
    yInterior      = A.yInterior;

	return *this;
}
//
//******************************************************************************
//                    INITIALIZATION
//******************************************************************************
//
void  CAMpolygonEntity::initialize()
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize();

    if(x != 0) delete [] x;
    if(y != 0) delete [] y;
    if(arcLengthBase != 0) delete [] arcLengthBase;
    x = 0;
    y = 0;
    n = 0;
    arcLengthBase  = 0;
	 orientation    = 1;
	 line_tolerance = LINE_TOLERANCE;

    BBoxXmin       = 0.0;
    BBoxXmax       = 0.0;
    BBoxYmin       = 0.0;
    BBoxYmax       = 0.0;

    xInterior      = 0.0;
    yInterior      = 0.0;

}
void  CAMpolygonEntity::initialize(const CAMpolygonEntity& A)
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize(A);

    if(x != 0) delete [] x;
    if(y != 0) delete [] y;
    if(arcLengthBase != 0) delete [] arcLengthBase;

    long i;
    if(A.n != 0)
    {
    n = A.n;
    x = new double[n+1]; y = new double[n+1]; arcLengthBase = new double[n+1];
    for(i = 0; i <= n; i++)
    {
    x[i]             = A.x[i];
    y[i]             = A.y[i];
    arcLengthBase[i] = A.arcLengthBase[i];
    }}
    else
    {
    x = 0; y = 0; n = 0; arcLengthBase = 0;
    }

	orientation    = A.orientation;
	line_tolerance = A.line_tolerance;

    BBoxXmin       = A.BBoxXmin;
    BBoxXmax       = A.BBoxXmax;
    BBoxYmin       = A.BBoxYmin;
    BBoxYmax       = A.BBoxYmax;

    xInterior      = A.xInterior;
    yInterior      = A.yInterior;

}

void  CAMpolygonEntity::initialize(double* xVertex, double* yVertex, long nSides)
{
	CAMgeometricEntity* Bptr = (CAMgeometricEntity*)(this);
	Bptr->initialize();

    if(x != 0) delete [] x;
    if(y != 0) delete [] y;
    if(arcLengthBase != 0) delete [] arcLengthBase;

    long i;
    if(nSides != 0)
    {
    n = nSides;
    x = new double[n+1]; y = new double[n+1]; arcLengthBase = new double[n+1];
    for(i = 0; i < n; i++)
    {x[i] = xVertex[i]; y[i] = yVertex[i];}
    x[n] = x[0]; y[n] = y[0];
    computeArcLengthBase();
    setBoundingBox();
    }
    else
    {
    x = 0; y = 0; n = 0; arcLengthBase = 0;
    }

	orientation    = 1;
	line_tolerance = LINE_TOLERANCE;

    if(nSides != 0)
    {computeInteriorPoint();}
}
//
//******************************************************************************
//                    Creation
//******************************************************************************
//
CAMgeometricEntity*  CAMpolygonEntity::newDuplicateEntity() const
{
	CAMpolygonEntity* R = new CAMpolygonEntity(*this);
	return  R;
}
//
//********************************************************************************
//                    Equality/Inequality
//********************************************************************************
//
int  CAMpolygonEntity::operator ==(const CAMgeometricEntity &A) const
{
	if(strcmp(A.getEntityType(),getEntityType()) != 0) return 0;

    CAMpolygonEntity* Aptr = ((CAMpolygonEntity*)&A);
	double* D = new double[2*(Aptr->n)];
	long*   L = new long[2];
	char*   C = 0;
	A.getConstructorData(D,L,C);
	int flag = compareConstructorData(D,L,C);
	delete [] D; delete [] L;

	return flag;
}
int CAMpolygonEntity::operator !=(const CAMgeometricEntity &A) const
{
	if(strcmp(A.getEntityType(),getEntityType()) != 0) return 1;

    CAMpolygonEntity* Aptr = ((CAMpolygonEntity*)&A);
	double* D = new double[2*(Aptr->n)];
	long*   L = new long[2];
	char*   C = 0;
	A.getConstructorData(D,L,C);
	int flag = 1 - compareConstructorData(D,L,C);
	delete [] D; delete [] L;

	return flag;
}
int  CAMpolygonEntity::compareConstructorData(double* D, long* L, char* /* C */) const
{
   int flag = 1;
   if(L[0] != n)           flag = 0;
   if(L[1] != orientation) flag = 0;
   long i;
   if(flag != 0)
   {
     for(i = 0; i < n; i++)
     {
       if(D[i]        != x[i] ) flag = 0;
       if(D[i + n]    != y[i] ) flag = 0;
     }
   }

   return flag;
}
void CAMpolygonEntity::getConstructorData(double* D, long* L, char* /* C */)  const
{
    L[0]     = n;
	 L[1]     = orientation;
    long i;
    for(i = 0; i < n; i++)
    {
    D[i]     = x[i];
    D[i + n] = y[i];
    }
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//
//
//********************************************************************************
//                    OUTPUT
//********************************************************************************
//
void  CAMpolygonEntity::output(ostream& out_stream) const
{
   out_stream << "[BEGIN_ENTITY]\n";
   out_stream << getEntityType() << "\n";
   out_stream << "[ENTITY_DATA]\n";
   out_stream <<  n  <<  '\n';
   int i;
   for(i = 0; i < n; i++)
   {
   out_stream << x[i] <<  "  " << y[i] << '\n';
   }
   out_stream << orientation << "\n";
   out_stream << "[END_ENTITY]\n";
}

ostream&  operator <<(ostream& out_stream, const CAMpolygonEntity& A)
{
	A.output(out_stream);
    return(out_stream);
}

istream&  operator >>(istream& in_stream, CAMpolygonEntity& A)
{
	 A.input(in_stream);
    return(in_stream);
}

void  CAMpolygonEntity::input(istream& in_stream)
{
	 char lineInput[256];
    in_stream >> lineInput;    //  [BEGIN_ENTITY]
    in_stream >> lineInput;    //  CAMpolygonEntity

    inputData(in_stream);      //  data and [END_ENTITY]
}

void  CAMpolygonEntity::inputData(istream& in_stream)
{
	 char lineInput[256];
    long nSides;

    in_stream >> lineInput;
    in_stream >> nSides;

    double* xVertex = new double[nSides];
    double* yVertex = new double[nSides];
    int i;
    for(i = 0; i < nSides; i++)
    {
    in_stream >> xVertex[i];
    in_stream >> yVertex[i];
    }

    initialize(xVertex, yVertex, nSides);

    in_stream >> orientation;
    in_stream >> lineInput;          //   [END_ENTITY]

    line_tolerance = LINE_TOLERANCE;
    
    delete [] xVertex;
    delete [] yVertex;
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//
int  CAMpolygonEntity::boundaryTest(double xTest, double yTest) const
//
// Returns 1 if test point is on the boundary of the
// polygon. Returns 0 otherwise.
//
{
  double s;
  return getParametricCoordinate(s, xTest, yTest);
}

/*
@begin_doc@
@title    @ getDistanceToBoundary()
@Purpose  @ Returns signed distance to the boundary.(+) for interior distances
(-1) for exterior distances;
@end_doc  @
*/
double CAMpolygonEntity::getDistanceToBoundary(double xT, double yT) const
{
//
//  Compute the minimum distance to each of the sides
//
    double dMin; 
    double dTest;

    dMin = computeSegmentDistance(xT, yT, x[0], y[0], x[1], y[1]);

    long i;

    for(i = 1; i <= n-1; i++)
    {
    dTest = computeSegmentDistance(xT, yT, x[i], y[i], x[i+1], y[i+1]);
    dMin  = (dMin < dTest) ? dMin : dTest;
    }

    int intExtTest = interiorExteriorTest(xT,yT);

    if(intExtTest > 0)      return  dMin; // inside
    else if(intExtTest < 0) return -dMin; // outside
   
	return 0.0;
}

int  CAMpolygonEntity::boundaryTest(double s1, double s2, double xTest, double yTest) const
//
// Returns 1 if the test point is on the boundary of the
// circle within the parametric coordinate range [s1, s2].
// Returns 0 otherwise.
//
{
    double s;
    return
    CAMpolygonEntity::getParametricCoordinate(s, s1,s2,xTest,yTest);
}

void CAMpolygonEntity::scaleBy(double alpha)
{
    long i;
  	if(n != 0)
    {
      for(i = 0; i <= n; i++)
      {
       x[i] = alpha*x[i];
       y[i] = alpha*y[i];
      }
      computeArcLengthBase();
      setBoundingBox();
      computeInteriorPoint();
    }

}

void CAMpolygonEntity::rotateBy(double theta)
{
    long i;
    double cTheta = cos(theta);
    double sTheta = sin(theta);
    double xp; double yp;

  	if(n != 0)
    {
      for(i = 0; i <= n; i++)
      {
       xp   = x[i];
       yp   = y[i];
       x[i] =  cTheta*xp + sTheta*yp;
       y[i] = -sTheta*xp + cTheta*yp;
      }
    setBoundingBox();
    computeInteriorPoint();
    }
}
void CAMpolygonEntity::translateBy(double xIncrement, double yIncrement)
{
    long i;
  	if(n != 0)
    {
      for(i = 0; i <= n; i++)
      {
       x[i] += xIncrement;
       y[i] += yIncrement;
      }
    setBoundingBox();
    computeInteriorPoint();
    }
}

void CAMpolygonEntity::translateTo(double xLocation, double yLocation)
{
    long   i;
    double xAvg = 0.0;
    double yAvg = 0.0;
    double xIncrement;
    double yIncrement;
    if(n != 0)
    {
      for(i = 0; i < n; i++)
      {
       xAvg += x[i];
       yAvg += y[i];
      }
      xAvg = xAvg/double(n);
      yAvg = yAvg/double(n);

      xIncrement = xLocation - xAvg;
      yIncrement = yLocation - yAvg;
      translateBy(xIncrement, yIncrement);
    }
}

double CAMpolygonEntity::getMinX() const
{
	return BBoxXmin;
}

double CAMpolygonEntity::getMaxX() const
{
	return BBoxXmax;
}

double CAMpolygonEntity::getMinY() const
{
	return BBoxYmin;
}

double CAMpolygonEntity::getMaxY() const
{
    return BBoxYmax;
}

double CAMpolygonEntity::getTotalArcLength() const
{
	return arcLengthBase[n];
}

int CAMpolygonEntity::getParametricCoordinate
(double& s, double xTest, double yTest) const
//
// This routine gets the parametric coordinate of the
// point (x,y). If the point is not on the curve the routine returns
// 0, otherwise the routine returns a value of 1, and the variable s
// is assigned to the parametric coordinate value.
//
{
  long linkI; double sLocal;
  int hit;

  hit =
  CAMlink::onConnectedLinks(x, y, n,xTest, yTest, line_tolerance,linkI, sLocal);
  if(hit != 0)
  {
  s = getGlobalParametricCoord(sLocal,linkI);
  return 1;}
  return 0;
}

int	  CAMpolygonEntity::getParametricCoordinate(double& s, double s1, double s2,
double xTest, double yTest) const
//
//	This routine gets the parametric coordinate of the
//	point (x,y) when the cooresponding parametric coordinate of
//	the point is between s1 and s2.
//	If the point is not on the curve within the parametric coordinate
//	range [s1,s2] the routine returns
//	0, otherwise the routine returns a value of 1, and the variable s
//	is assigned to the parametric coordinate value.
//
{
    long s1Index = getSegmentIndex(s1);
    long s2Index = getSegmentIndex(s2);
    if((s1Index == 0)||(s2Index == 0)) return 0;

    double* xS = &x[s1Index -1];
    double* yS = &y[s1Index -1];
    long nS    = (s2Index - s1Index) + 1;

    long   linkI;
    double sLocal; double sGlobal;
    int hit;

    hit  = CAMlink::onConnectedLinks
    (xS, yS, nS, xTest, yTest, line_tolerance,linkI, sLocal);
    if(hit !=0)
    {
    sGlobal = getGlobalParametricCoord(sLocal, linkI);
    if((s1 <= sGlobal)&&(sGlobal <= s2)){s = sGlobal; return 1;}
    }

    return 0;
}

double CAMpolygonEntity::getXcoordinate(double s) const
{
    long segIndex = getSegmentIndex(s);
    double darc   = arcLengthBase[segIndex] - arcLengthBase[segIndex-1];
    double sLocal = (s - arcLengthBase[segIndex-1])/darc;
	return (1.0 - sLocal)*x[segIndex-1] + sLocal*x[segIndex];
}

double CAMpolygonEntity::getYcoordinate(double s) const
{
	long segIndex = getSegmentIndex(s);
    double darc   = arcLengthBase[segIndex] - arcLengthBase[segIndex-1];
    double sLocal = (s - arcLengthBase[segIndex-1])/darc;
	return (1.0 - sLocal)*y[segIndex-1] + sLocal*y[segIndex];
}

int CAMpolygonEntity::interiorExteriorTest(double xTest, double yTest) const
//
//  Returns +1 if test point is interior to the polygon and
// -1 if point is exterior to the polygon, otherwise returns 0;
//
{
//
//  Check to see if outside the bounding box
//
    double tol = line_tolerance;
    if( xTest < BBoxXmin - tol) return -1*orientation;
    if( xTest > BBoxXmax + tol) return -1*orientation;
    if( yTest < BBoxYmin - tol) return -1*orientation;
    if( yTest > BBoxYmax + tol) return -1*orientation;
//
//  Check to see if on the boundary
//
    if(boundaryTest(xTest,yTest)==1 ) return 0;

    double xC1; double yC1;
    double xC2; double yC2;
    double theta1; double theta2;
    double solidAngle;

    double pi  = 4.0*atan2(1.0,1.0);
    double pi2 = 2.0*pi;

    xC1    = x[0] - xTest;
    yC1    = y[0] - yTest;
    theta1 = atan2(yC1, xC1);
    if(theta1 < 0) theta1 = pi2 + theta1;

    solidAngle = 0.0;
    long i;
    
    for(i = 0; i < n; i++)
    {
    xC2 = x[i+1] - xTest;
    yC2 = y[i+1] - yTest;
    theta2 = atan2(yC2, xC2);
    if(theta2 < 0) theta2 = pi2 + theta2;

    if((theta1 <= pi)&&(theta2 >= theta1 + pi))
    {
    solidAngle += -(theta1 + (pi2-theta2));
    } 
    else
    if((theta2 <= pi)&&(theta1 >= theta2 + pi))
    {
    solidAngle += (pi2 - theta1) + theta2;
    }
    else
    {
    solidAngle += theta2 - theta1;
    }

    theta1 = theta2;
    }
     
    if((fabs(solidAngle - pi2) < tol)||(fabs(solidAngle + pi2) < tol))
    {return 1*orientation;}
    return -1*orientation;
}

int CAMpolygonEntity::getInteriorPoint(double& xReturn, double& yReturn) const
{
    xReturn = xInterior;
    yReturn = yInterior;
	return 1;
}

int CAMpolygonEntity::getSegmentIntersection(double& intersectPoint, double x_a,
			  double y_a, double x_b, double y_b) const
{
    double tol = line_tolerance;
    if((x_a < BBoxXmin - tol)&&(x_b < BBoxXmin - tol))return 0;
    if((x_a > BBoxXmax + tol)&&(x_b > BBoxXmax + tol))return 0;
    if((y_a < BBoxYmin - tol)&&(y_b < BBoxYmin - tol))return 0;
    if((y_a > BBoxYmax + tol)&&(y_b > BBoxYmax + tol))return 0;


    double Qx [2];
    Qx[0] = x_a;
    Qx[1] = x_b;

    double Qy [2];
    Qy[0] = y_a;
    Qy[1] = y_b;

    double pxQ; double pyQ;
    double localS;  double d;
    double s;

    int linkRet = 0;
    int   i = 0;
    while((linkRet ==0)&&(i <= n-1))
    {
    linkRet =
    CAMlink::linkIntersection(Qx, Qy, &(x[i]),&(y[i]),line_tolerance, s);
    if(linkRet == 1)
    {
    pxQ = (1.0-s)*x_a + s*x_b;
    pyQ = (1.0-s)*y_a + s*y_b;
    CAMlink::onLink(x[i], y[i], x[i+1], y[i+1],pxQ, pyQ, line_tolerance, localS, d);
    intersectPoint = getGlobalParametricCoord(localS, i+1);
    }
    i++;
    }
    if(linkRet == 1) return 1;
	return 0;
}

int CAMpolygonEntity::getSegmentIntersection(double& intersectPoint, double s_1,
			  double s_2, double x_a, double y_a, double x_b, double y_b) const

{
    long i1;
    long i2;
    if(s_1 < s_2)
    {
    i1 = getSegmentIndex(s_1) - 1;
    i2 = getSegmentIndex(s_2) - 1;
    }
    else
    {
    i1 = getSegmentIndex(s_2) - 1;
    i2 = getSegmentIndex(s_1) - 1;
    }

    double tol = line_tolerance;
    if((x_a < BBoxXmin - tol)&&(x_b < BBoxXmin - tol))return 0;
    if((x_a > BBoxXmax + tol)&&(x_b > BBoxXmax + tol))return 0;
    if((y_a < BBoxYmin - tol)&&(y_b < BBoxYmin - tol))return 0;
    if((y_a > BBoxYmax + tol)&&(y_b > BBoxYmax + tol))return 0;

    double Qx [2];
    Qx[0] = x_a;
    Qx[1] = x_b;

    double Qy [2];
    Qy[0] = y_a;
    Qy[1] = y_b;

    double pxQ; double pyQ;
    double localS;  double d;
    double s;

    int linkRet = 0;
    int   i = i1;
    while((linkRet ==0)&&(i <= i2))
    {
    linkRet =
    CAMlink::linkIntersection(Qx, Qy, &(x[i]),&(y[i]),line_tolerance, s);
    if(linkRet == 1)
    {
    pxQ = (1.0-s)*x_a + s*x_b;
    pyQ = (1.0-s)*y_a + s*y_b;
    CAMlink::onLink(x[i], y[i], x[i+1], y[i+1],pxQ, pyQ, line_tolerance, localS, d);
    intersectPoint = getGlobalParametricCoord(localS, i+1);
    }
    i++;
    }

    if(linkRet == 1)
    {
    if(s_1 <= s_2)
    {if((s_1 <= intersectPoint)&&(intersectPoint <= s_2)) return 1;}
    else
    {if((s_2 <= intersectPoint)&&(intersectPoint <= s_1)) return 1;}
    }

    intersectPoint = 0;
	return 0;
}
void  CAMpolygonEntity::getUnitNormal(double s, double& n_x, double& n_y) const
{
//
//   No accounting for corners (yet)
//
	long sIndex = getSegmentIndex(s);
    double tx1 = x[sIndex] - x[sIndex -1];
    double ty1 = y[sIndex] - y[sIndex -1];
    double tnrm = sqrt(tx1*tx1 + ty1*ty1);
	n_x =  double(orientation)*(ty1/tnrm);
	n_y =  double(orientation)*(-tx1/tnrm);
}

void  CAMpolygonEntity::getUnitTangent(double s, double& t_x, double& t_y) const
{
	long sIndex = getSegmentIndex(s);
    double tx1 = x[sIndex] - x[sIndex -1];
    double ty1 = y[sIndex] - y[sIndex -1];
    double tnrm = sqrt(tx1*tx1 + ty1*ty1);
	t_x = tx1/tnrm;
	t_y = ty1/tnrm;
}
//
//********************************************************************************
//                    INTERNAL MEMBER_FUNCTIONS
//********************************************************************************
//
// "External" vertex indexing starts at 1
//
double CAMpolygonEntity::getVertexCoordinate(long vertexIndex) const
{
   return arcLengthBase[vertexIndex-1];
}
//
// arcLengthBase[i] = arcLength from vertex 0 to ith vertex
//

void CAMpolygonEntity::computeArcLengthBase()
{
    int i;
    arcLengthBase[0] = 0.0;
    for(i = 1; i <= n; i++)
    {
     arcLengthBase[i] = arcLengthBase[i-1] +
     sqrt((x[i]-x[i-1])*(x[i]-x[i-1]) +
          (y[i]-y[i-1])*(y[i]-y[i-1]));
    }
}
//
//  Computes the index of  the segement containing
//  the point whose parameteric coordinate is s.
//
long CAMpolygonEntity::getSegmentIndex(double s) const
{
     if((s < 0.0)||(s > arcLengthBase[n])) return 0;
     if(s == arcLengthBase[n])             return n;
     if(s == 0.0)                          return 1;

     long index = 0;
     long     i = 0;
     while( s > arcLengthBase[i] ){index++; i++;}
     return index;
}
//
//  This routine transforms the local parametric coordinate for
//  each side (a value in [0,1]) into the parametric coordinate
//  for the complete polygon
//
double CAMpolygonEntity::getGlobalParametricCoord
(double s, long segIndex)  const
{
    double a_1     =  arcLengthBase[segIndex -1];
    double a_2     =  arcLengthBase[segIndex];
    return a_1 + s*(a_2 - a_1);
}
void CAMpolygonEntity::setLineTolerance(double tol)
{
	line_tolerance = tol;
}

void CAMpolygonEntity::setBoundingBox()
{
    long i;

    BBoxXmin = x[0];
    for(i = 1; i < n; i++) {if(BBoxXmin >= x[i]) BBoxXmin = x[i];}

    BBoxXmax = x[0];
    for(i = 1; i < n; i++) {if(BBoxXmax <= x[i]) BBoxXmax = x[i];}

    BBoxYmin = y[0];
    for(i = 1; i < n; i++) {if(BBoxYmin >= y[i]) BBoxYmin = y[i];}

    BBoxYmax = y[0];
    for(i = 1; i < n; i++) {if(BBoxYmax <= y[i]) BBoxYmax = y[i];}

}
/**
This routine computes the interior point by searching along a line
normal to the first side of the polygon and based at the midpoint
of the side. The distance away from the side is initially taken
to be that .25 of the length of the side; this distance is successively
halved (on both sides) until an interior point is computed.

This routine does not check for anomolies --- such as a polygon in
which the first side and some other side are within the line
tolerance of one another.
*/
void CAMpolygonEntity::computeInteriorPoint()
{
	double xbase = (x[0] + x[1])/2.0;
    double ybase = (y[0] + y[1])/2.0;
    double xdif  = (x[1] - x[0])/4.0;
    double ydif  = (y[1] - y[0])/4.0;

    double xpA = xbase - ydif;
    double ypA = ybase + xdif;
    double xpB = xbase + ydif;
    double ypB = ybase - xdif;

    int flagA; int flagB;
    int iFound = 0;

    double dnrm = sqrt(xdif*xdif + ydif*ydif);

    while((iFound == 0)&&(dnrm >= line_tolerance/2.0))
    {
    flagA = interiorExteriorTest(xpA, ypA);
    if(flagA == 1){xInterior = xpA; yInterior = ypA; iFound = 1;}

    if(iFound != 1)
    {
    flagB = interiorExteriorTest(xpB, ypB);
    if(flagB == 1){xInterior = xpB; yInterior = ypB; iFound = 1;}
    }

    if(iFound != 1)
    {
    xdif *= .5;
    ydif *= .5;
    xpA = xbase - ydif;
    ypA = ybase + xdif;
    xpB = xbase + ydif;
    ypB = ybase - xdif;
    dnrm = sqrt(xdif*xdif + ydif*ydif);
    }
    }
//

}

/**
This routine computes the distance to a segment from (xA,yA) to (xB,yB). 
It does this by minimizing the square of the distance from the 
test point to the line through the two points as a function of the 
parametric coordinate. 

*/
double CAMpolygonEntity::computeSegmentDistance(double x, double y, double xA, double yA,
												double xB, double yB) const
{
//
//	Find s* = value at which the distance between x and 
//  line though segment endpoins is minimum.
//
    double dxAB     = xB - xA;
    double dyAB     = yB - yA;

    double dxAX     = x  - xA;
    double dyAY     = y  - yA;

    double xStar; double yStar;
    double sStar;

    double dA; double dB;

    double dABnorm2 = dxAB*dxAB + dyAB*dyAB;
//
//  If endpoints of segment coincide to line tolerance, then return 
//  distance from (x,y) to (xA,yA).
//
    if(dABnorm2 < line_tolerance*line_tolerance) return sqrt(dxAX*dxAX + dyAY*dyAY);

    sStar  = (dxAX*dxAB + dyAY*dyAB)/dABnorm2;

    if((sStar > 0)&&(sStar < 1.0))
    {
        xStar = xA + sStar*dxAB;
        yStar = yA + sStar*dyAB;
        return sqrt((x-xStar)*(x-xStar) + (y-yStar)*(y-yStar));
    }
    else
    {
        dA = sqrt(dxAX*dxAX + dyAY*dyAY);
        dB = sqrt((x-xB)*(x-xB) + (y-yB)*(y-yB));
        if(dA < dB) return dA;
        return dB;
    }

    return 0.0;
}

//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//

 
