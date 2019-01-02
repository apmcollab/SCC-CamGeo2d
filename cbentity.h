//
//******************************************************************************
//                    CBENTITY.H
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 05 17:10:48 1995
//
// CRA Modifications 4/10/06  Added getDistanceToBoundary(...)
//                            Fixed the interiorExteriorTest bug 
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
using namespace std;

#ifndef __CAM_CHAR_PTR_HANDLE__
#define __CAM_CHAR_PTR_HANDLE__


class CAMcharPtrHandle
{
    char*  dataPtr;

public :

    CAMcharPtrHandle(char* A){dataPtr = A;};
      operator char*(){return dataPtr;};

};

#endif


//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Thu Oct 05 17:10:48 1995
//
//********************************************************************************
//

#ifndef __CAM_COMBINED_ENTITY__
#define __CAM_COMBINED_ENTITY__

#include <iostream>
#include <string>
using namespace std;

#include "entity.h"
#include "camgeoimpexp.h"

class __IMPEXP__ CAMcombinedEntity
{

private :

//
//  internal representation data
//
    CAMgeometricEntity**  entityListPtr;
    char **  entityNameListPtr;
    long  entityCount;
    long  entityPtrAllocation;
    int  entityIndexBase;

public :

    CAMcombinedEntity();
    CAMcombinedEntity( const CAMcombinedEntity& A);
//
//  Destructor 
//
    ~CAMcombinedEntity();
//
//  Assignment 
//
    CAMcombinedEntity& operator = ( const CAMcombinedEntity& A);
    void  initialize();
    void  initialize(const CAMcombinedEntity& E);
//
//  Output 
//
    __IMPEXP__ friend ostream&   operator <<(ostream& out_stream, const CAMcombinedEntity& A);
    __IMPEXP__ friend istream&   operator >>(istream& in_stream, CAMcombinedEntity& A);
    
    const char*  getEntityType() const {return "CAMcombinedEntity";};
    
    void  addEntity(const CAMgeometricEntity& E);
    void  addEntity(const char* entityName, const CAMgeometricEntity& E);
    void  addEntity(CAMgeometricEntity* E){addEntity(*E);};
    void  addEntity(const char* entityName, CAMgeometricEntity* E){addEntity(entityName,*E);};
    long  getEntityCount() const {return entityCount;};
    int  getIndexBase() const {return entityIndexBase;};
    void  setIndexBase(int newIndexBase){entityIndexBase = newIndexBase;};
    long  getIndexBound() const {return entityCount + (entityIndexBase - 1);};
    CAMgeometricEntity&  operator[](CAMcharPtrHandle entityName) const;
    CAMgeometricEntity&  operator[](long  entityIndex) const;
    char*  getIndexName(long index) const;
    void  setIndexName(long index, char* newName);
//
//  operations on union of contained entities
//
    void getBoundingBox(double& bMinX, double& bMaxX, 
    double& bMinY, double& bMaxY);


    int interiorExteriorTest(double xTest, double yTest) const;

	double getDistanceToBoundary(double x, double y) const;
	double getExteriorDistanceToBoundary(double x, double y) const;

//
//  Equality/Inequality
//
    int  operator ==(const CAMcombinedEntity &A) const;
    int  operator !=(const CAMcombinedEntity &A) const;
    void  draw() const;
    void  expandList();
//
//  Reference Counting
//

private :

    long  ceReferenceCount;

public :

    void  incrementReferenceCount()
{
	if(ceReferenceCount == 0) CAMcombinedEntity::referenceCountError();
	ceReferenceCount++;
};
    void  decrementReferenceCount(){ceReferenceCount--;};
    long  getReferenceCount() const {return ceReferenceCount;};
    void  initializeReferenceCount(){ceReferenceCount = 1;};
    void  setReferenceCount(long refValue){ceReferenceCount = refValue;};
    static void  referenceCountError()
{
cerr << " Cannot Use Reference Counting on Objects New\'d by the Compiler " << endl;
CAMgeoExit();
};

};

#endif
//
//********************************************************************************
//                     Header File End 
//********************************************************************************
//

 
