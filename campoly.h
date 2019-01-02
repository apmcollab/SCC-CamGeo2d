//
//******************************************************************************
//                    CAMPOLY.H
//******************************************************************************
//

//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 05 15:22:34 1995
//
//
// CRA Modifications 4/10/06  Added getDistanceToBoundary(...)
//********************************************************************************
//

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

#include <cstring>

#include "camgeoimpexp.h"
#include "entity.h"
using namespace std;

#ifndef __CAM_POLYGON_ENTITY__
#define __CAM_POLYGON_ENTITY__

class __IMPEXP__ CAMpolygonEntity : public CAMgeometricEntity
{

private :

//
//  internal representation data
//
    double*        x;        // ordinates of polygon vertices
    double*        y;        // abscissas of polygon vertices
    long           n;        // number of points defining polygon
                             // = number of sides. (Polygon is by
                             // definition "closed")

    double*  arcLengthBase;  //
    int      orientation;    //
    double   line_tolerance; //

    double BBoxXmin;
    double BBoxXmax;
    double BBoxYmin;
    double BBoxYmax;

    double xInterior;
    double yInterior;

public :

    CAMpolygonEntity();
    CAMpolygonEntity(const CAMpolygonEntity& A);
    CAMpolygonEntity(double* xVertex, double* yVertex, long nSides);
//
//  Destructor 
//
    ~CAMpolygonEntity();
//
//  Assignment 
//
    CAMpolygonEntity& operator = ( const CAMpolygonEntity& A);
//
//  input/output functions
//
    __IMPEXP__ friend     ostream&  operator <<(ostream& out_stream, const CAMpolygonEntity& A);
    void       output(ostream& out_stream) const;

    __IMPEXP__ friend istream&  operator >>(istream& in_stream, CAMpolygonEntity& A);
    void input(istream&);
    void inputData(istream&);

    const char*	   getEntityType() const {return "CAMpolygonEntity";};
    int	       interiorExteriorTest(double xTest, double yTest) const;
    int	       boundaryTest(double xTest, double yTest) const;
    int	       boundaryTest(double s1, double s2, double xTest, double yTest) const;
    void	   scaleBy(double alpha);
    void	   rotateBy(double theta);
    void	   translateBy(double x, double y);
    void  	   translateTo(double x, double y);
    double	   getMinX() const;
    double	   getMaxX() const;
    double	   getMinY() const;
    double	   getMaxY() const;
    double     getTotalArcLength() const;
    int	       getParametricCoordinate(double& s, double x, double y) const;
    int	       getParametricCoordinate(double& s, double s1, double s2, double x, double y) const;
    double	   getXcoordinate(double s) const;
    double	   getYcoordinate(double s) const;
    int        getInteriorPoint(double& x, double& y) const;
    int  	   getSegmentIntersection(double& intersectPoint, double x_a,
			   double y_a, double x_b, double y_b) const;
    int  	   getSegmentIntersection(double& intersectPoint, double s_1,
			   double s_2, double x_a, double y_a, double x_b, double y_b) const;
    void       getUnitNormal(double s, double& n_x, double& n_y) const;
    void       getUnitTangent(double s, double& t_x, double& t_y) const;

	double     getDistanceToBoundary(double x, double y) const;
//
//  Initialization
//
    void  initialize();
    void  initialize(const CAMpolygonEntity& A);
    void  initialize(double* xVertex, double* yVertex, long nSides);
//
//  Creation
//
    CAMgeometricEntity*  newDuplicateEntity() const;
//
//  Equality/Inequality
//
    int  operator ==(const CAMgeometricEntity &A) const;
    int  operator !=(const CAMgeometricEntity &A) const;
    void  getConstructorData(double* D, long* L, char* C) const;
    int  compareConstructorData(double* D, long* L, char* C )const;
//
//  Access
//
    double*   getXvertices() const       { return x;};
    double*   getYvertices() const       { return y;};
    long      getSideCount() const       { return n;};
    int       getOrientation() const     { return orientation;};
    void      setOrientation(int orient) { orientation = orient;};
  


//
//  Internal Helper Functions
//
	 public :

    long    getVertexCount() const {return n;};
    double  getVertexCoordinate(long vertexIndex) const;
    void    computeArcLengthBase();
    long    getSegmentIndex(double s) const;
    double  getGlobalParametricCoord(double s, long segIndex) const;
    void    setLineTolerance(double tol);
    void    setBoundingBox();
    void    computeInteriorPoint();
	double  computeSegmentDistance(double x, double y, 
		    double xA, double yA, double xB, double yB) const;
};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//
 
