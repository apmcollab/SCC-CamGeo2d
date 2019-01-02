//
//******************************************************************************
//                    ENTITY.H
//******************************************************************************
//

//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 05 18:04:19 1995
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
#include <iostream>
using namespace std;


#include "geoexit.h"
#include "camgeoimpexp.h"

#ifndef __CAMGEOENTITY__
#define __CAMGEOENTITY__

class __IMPEXP__ CAMgeometricEntity
{

private :

    long  geoReferenceCount;

public :

//
//  Constructors
//
    CAMgeometricEntity(){geoReferenceCount = 0;};
    CAMgeometricEntity(const CAMgeometricEntity&){geoReferenceCount = 0;};
//
//  Destructor
//
    virtual  ~CAMgeometricEntity(){};
//
//  Reference Counting
//
    void  incrementReferenceCount()
{
	if(geoReferenceCount == 0) CAMgeometricEntity::referenceCountError();
	geoReferenceCount++;
};
    void  decrementReferenceCount(){geoReferenceCount--;};
    int  getReferenceCount() const {return geoReferenceCount;};
    void  initializeReferenceCount(){geoReferenceCount = 1;};
    void  setReferenceCount(int refValue){geoReferenceCount = refValue;};
    static void  referenceCountError()
{
cerr << " Cannot Use Reference Counting on Objects New\'d by the Compiler "
<< endl; CAMgeoExit();
};
//
//  output functions
//
    friend ostream&  operator <<(ostream& out_stream, const CAMgeometricEntity& A)
    {A.output(out_stream);return out_stream;};
    virtual void  output(ostream&) const {};

    friend istream&  operator >>(istream& in_stream, CAMgeometricEntity& A)
    {A.input(in_stream);return in_stream;};
    
    virtual void input(istream&) {};

//
//  Geometric Entity Member Functions
//
    virtual const char*  getEntityType() const {return "Null";};
    virtual int  interiorExteriorTest(double, double) const {return 0;};
    virtual int  boundaryTest(double, double) const {return 0;};
    virtual int  boundaryTest(double, double, double, double) const {return 0;};
    virtual void  scaleBy(double){};
    virtual void  rotateBy(double){};
    virtual void  translateBy(double, double){};
    virtual void  translateTo(double, double){};
    virtual double  getMinX() const {return 0.0;};
    virtual double  getMaxX() const {return 0.0;};
    virtual double  getMinY() const {return 0.0;};
    virtual double  getMaxY() const {return 0.0;};
    virtual double  getTotalArcLength() const {return 0.0;};
    virtual int  getParametricCoordinate(double& coordinate, double, double) const {return 0;};
    virtual int  getParametricCoordinate(double& coordinate, double, double, double, double) const {return 0;};
    virtual double  getXcoordinate(double) const {return 0.0;};
    virtual double  getYcoordinate(double) const {return 0.0;};
    virtual int  getInteriorPoint(double& x, double& y) const {x = 0.0; y = 0.0; return 0;};
    virtual int  getSegmentIntersection(double& intersectPoint, double,
				  double, double, double) const {intersectPoint = 0.0; return 0;};
    virtual int  getSegmentIntersection(double& intersectPoint, double,
				  double, double, double, double, double) const {intersectPoint = 0.0; return 0;};
    virtual void  getUnitNormal(double, double& n_x, double& n_y) const {n_x =0.0; n_y = 0.0;};
    virtual void  getUnitTangent(double, double& t_x, double& t_y) const {t_x =0.0; t_y = 0.0;};

	virtual double  getDistanceToBoundary(double x, double y) const {return 0.0;};
//
//  Initialization
//
    void  initialize(){geoReferenceCount = 0;};
    void  initialize(const CAMgeometricEntity&){geoReferenceCount = 0;};
//
//  Creation
//
    virtual CAMgeometricEntity*  newDuplicateEntity() const {CAMgeometricEntity* A = 0; return A;};
//
//  Equality/Inequality
//
    virtual int  operator ==(const CAMgeometricEntity&)const {return 0;};
    virtual int  operator !=(const CAMgeometricEntity&)const {return 0;};
    virtual void  getConstructorData(double*, long*, char*) const {};
    virtual int  compareConstructorData(double*, long*, char*)const {return 0;};
//
//  Error Handling Functions
//
    static void  parametricCoordinateError()
{
cerr << " Error : getParametricCoordinate arguments not on entity " <<endl;
CAMgeoExit();
};

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//

 
