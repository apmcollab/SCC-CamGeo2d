//
//******************************************************************************
//                    CAMCIRC.H
//******************************************************************************
//
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 05 15:22:34 1995
//
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
#include "entity.h"
#include "camgeoimpexp.h"

#ifndef CAM_CIRCLE_ENTITY__
#define CAM_CIRCLE_ENTITY__

class __IMPEXP__ CAMcircleEntity : public CAMgeometricEntity
{

private :

//
//  internal representation data
//
    double  center_x;
    double  center_y;
    double  radius;
    double  start_theta;
    int  orientation;
    double  line_tolerance;

public :

    CAMcircleEntity();
    CAMcircleEntity( const CAMcircleEntity& A);
    CAMcircleEntity(double x_center, double y_center, double r);
//
//  Destructor 
//
    ~CAMcircleEntity();
//
//  Assignment 
//
    CAMcircleEntity& operator = ( const CAMcircleEntity& A);
//
//  output/input  functions
//
    __IMPEXP__ friend std::ostream&  operator <<(std::ostream& out_stream, const CAMcircleEntity& A);
    void  output(std::ostream& out_stream) const;

    __IMPEXP__ friend std::istream&  operator >>(std::istream& in_stream, CAMcircleEntity& A);
    void input(std::istream&);
    void inputData(std::istream&);

    const char*  getEntityType() const {return "CAMcircleEntity";};

    int	     interiorExteriorTest(double xTest, double yTest) const;
    int	     boundaryTest(double xTest, double yTest) const;
    int	     boundaryTest(double s1, double s2, double xTest, double yTest) const;
    void	     scaleBy(double alpha);
    void	     rotateBy(double theta);
    void	     translateBy(double x, double y);
    void  	  translateTo(double x, double y);
    double	  getMinX() const;
    double	  getMaxX() const;
    double	  getMinY() const;
    double	  getMaxY() const;
    double    getTotalArcLength() const;
    int	     getParametricCoordinate(double& s, double x, double y) const;
    int	     getParametricCoordinate(double& s, double s1, double s2, double x, double y) const;
    double	  getXcoordinate(double s) const;
    double	  getYcoordinate(double s) const;
    int       getInteriorPoint(double& x, double& y) const;
    int  	  getSegmentIntersection(double& intersectPoint, double x_a,
			      double y_a, double x_b, double y_b) const;
    int  	  getSegmentIntersection(double& intersectPoint, double s_1,
			      double s_2, double x_a, double y_a, double x_b, double y_b) const;
    void      getUnitNormal(double s, double& n_x, double& n_y) const;
    void      getUnitTangent(double s, double& t_x, double& t_y) const;

	double    getDistanceToBoundary(double x, double y) const;
//
//  Initialization
//
    void  initialize();
    void  initialize(const CAMcircleEntity& A);
    void  initialize(double x_center, double y_center, double r);
//
//  Creation
//
    CAMgeometricEntity*  newDuplicateEntity() const;
//
//  Equality/Inequality
//
    int   operator ==(const CAMgeometricEntity &A) const;
    int   operator !=(const CAMgeometricEntity &A) const;
    void  getConstructorData(double* D, long* L, char* C) const;
    int   compareConstructorData(double* D, long* L, char* C )const;
//
//  Access
//
	 double  getRadius()        const {return radius;};
    double  getXcenter()       const {return center_x;};
    double  getYcenter()       const {return center_y;};
    double  getStartingTheta() const {return start_theta;};
    int     getOrientation()   const {return orientation;};
//
//  Internal Helper Functions
//
    static int  getQuadraticRoots(double a, double b, double c, double& r_1, double& r_2);

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//

 
