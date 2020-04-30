//
//******************************************************************************
//                    CAMXYRCT.H
//******************************************************************************
//

//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 05 15:39:32 1995
//
//
// CRA Modifications 4/10/06  Added getDistanceToBoundary(...)
//******************************************************************************
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

#include "camgeoimpexp.h"
#include "entity.h"

#ifndef __CAM_XYRECTANGLE_ENTITY__
#define __CAM_XYRECTANGLE_ENTITY__

class __IMPEXP__ CAMxyRectangleEntity : public CAMgeometricEntity
{

private :

//
//  internal representation data
//
    double  x_a;
    double  y_a;
    double  x_b;
    double  y_b;
    int  orientation;
    double  line_tolerance;

public :

    CAMxyRectangleEntity();
    CAMxyRectangleEntity( const CAMxyRectangleEntity& A);
    CAMxyRectangleEntity(double x_1, double y_1, double x_2, double y_2);
//
//  Destructor 
//
    ~CAMxyRectangleEntity();
//
//  Assignment 
//
    CAMxyRectangleEntity& operator = ( const CAMxyRectangleEntity& A);
//
//  output functions
//
    __IMPEXP__ friend std::ostream&  operator <<(std::ostream& out_stream, const CAMxyRectangleEntity& A);
    void  output(std::ostream& out_stream) const;

    __IMPEXP__ friend std::istream&  operator >>(std::istream& in_stream, CAMxyRectangleEntity& A);
    void input(std::istream&);
    void inputData(std::istream&);

    const char*	  getEntityType() const {return "CAMxyRectangleEntity";};
    int	  interiorExteriorTest(double xTest, double yTest) const;
    int	  boundaryTest(double xTest, double yTest) const;
    int  boundaryTest(double s1, double s2, double xTest, double yTest) const;
    void	  scaleBy(double alpha);
    void	  rotateBy(double theta);
    void	  translateBy(double x, double y);
    void  	  translateTo(double x, double y);
    double	  getMinX() const;
    double	  getMaxX() const;
    double	  getMinY() const;
    double	  getMaxY() const;
    double  getTotalArcLength() const;
    int	  getParametricCoordinate(double& s, double x, double y) const;
    int	  getParametricCoordinate(double& s, double s1, double s2, double x, double y) const;
    double	  getXcoordinate(double s) const;
    double	  getYcoordinate(double s) const;
    int  getVertexCount() const {return 4;};
    double  getVertexCoordinate(long vertexIndex) const;
    int  getInteriorPoint(double& x, double& y) const;
    int  	  getSegmentIntersection(double& intersectPoint, double x_1,
			  double y_1, double x_2, double y_2) const;
    int  	  getSegmentIntersection(double& intersectPoint, double s_1,
			  double s_2, double x_1, double y_1, double x_2, double y_2) const;
    void  getUnitNormal(double s, double& n_x, double& n_y)  const;
    void  getUnitTangent(double s, double& t_x, double& t_y) const;

    double    getDistanceToBoundary(double x, double y) const;
//
//  Initialization
//
    void  initialize();
    void  initialize(const CAMxyRectangleEntity& A);
    void  initialize(double x_1, double y_1, double x_2, double y_2);
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
// Access
//
    double   getLowerLeftXpoint()  const {return x_a;};
    double   getLowerLeftYpoint()  const {return y_a;};
    double   getUpperRightXpoint() const {return x_b;};
    double   getUpperRightYpoint() const {return y_b;};
    int getOrientation() const {return orientation;};

//
//  Internal Helper Functions
//
    static int  intersectSegments(double& s, double X_a, double Y_a,
                double X_b, double Y_b, double& t, double U_a, 
                double V_a, double U_b, double V_b);
    double      computeSegmentDistance(double x, double y, double xA, double yA,
												double xB, double yB) const;

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//

 
