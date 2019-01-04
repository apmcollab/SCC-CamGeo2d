

#include "cbentity.h"
#include "camcirc.h"
#include "campoly.h"
#include "camxyrct.h"

#include <cstdlib>
#include <cmath>

#include <iostream>
#include <sstream>
using namespace std;

#define   _CAMentityChunkSize_  7
//
//******************************************************************************
//                    CBENTITY.CPP
//******************************************************************************
//
//
//******************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//            Tue Aug 15 19:27:44 1995
//
//******************************************************************************
//
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
//******************************************************************************
//                    CONSTRUCTORS
//******************************************************************************
//
//
//******************************************************************************
//               
//******************************************************************************
//
CAMcombinedEntity::CAMcombinedEntity()
{
	entityListPtr       = new CAMgeometricEntity*[ _CAMentityChunkSize_ ];
	entityNameListPtr   = new char* [ _CAMentityChunkSize_ ];
	entityCount         = 0;
	entityPtrAllocation =  _CAMentityChunkSize_ ;
	entityIndexBase     = 0;

	ceReferenceCount    = 0;
}

CAMcombinedEntity::CAMcombinedEntity( const CAMcombinedEntity& A)
{
	entityPtrAllocation = A.entityPtrAllocation;
	entityListPtr       = new CAMgeometricEntity*[entityPtrAllocation];
	entityNameListPtr   = new char* [entityPtrAllocation];

	entityCount     = A.entityCount;
	entityIndexBase = A.entityIndexBase;
//
//  Copy over entities and names
//
	for(int i = 0; i < entityCount; i++)
	{

	entityListPtr[i]     = (A.entityListPtr[i])->newDuplicateEntity();
	entityListPtr[i]->initializeReferenceCount();

	entityNameListPtr[i] = new char[strlen(A.entityNameListPtr[i]) + 1];
	strcpy(entityNameListPtr[i],A.entityNameListPtr[i]);
	}

    ceReferenceCount    = 0;
}
//
//********************************************************************************
//                    Initialize
//********************************************************************************

void CAMcombinedEntity::initialize()
{
//
//  Remove exisiting data
//
	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	{
	entityListPtr[i]->decrementReferenceCount();
	if(entityListPtr[i]->getReferenceCount() == 0) delete entityListPtr[i];
	}
	}

	if(entityListPtr != 0) delete [] entityListPtr;
	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	delete [] entityNameListPtr[i];
	}
	if(entityNameListPtr != 0) delete [] entityNameListPtr;


	entityListPtr       = new CAMgeometricEntity*[ _CAMentityChunkSize_ ];
	entityNameListPtr   = new char* [ _CAMentityChunkSize_ ];
	entityCount         = 0;
	entityPtrAllocation =  _CAMentityChunkSize_ ;
	entityIndexBase     = 0;

	ceReferenceCount    = 0;
}

void CAMcombinedEntity::initialize( const CAMcombinedEntity& A)
{
//
//  Remove exisiting data
//
	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	{
	entityListPtr[i]->decrementReferenceCount();
	if(entityListPtr[i]->getReferenceCount() == 0) delete entityListPtr[i];
	}
	}

	if(entityListPtr != 0) delete [] entityListPtr;
	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	delete [] entityNameListPtr[i];
	}
	if(entityNameListPtr != 0) delete [] entityNameListPtr;


	entityPtrAllocation = A.entityPtrAllocation;
	entityListPtr       = new CAMgeometricEntity*[entityPtrAllocation];
	entityNameListPtr   = new char* [entityPtrAllocation];

	entityCount     = A.entityCount;
	entityIndexBase = A.entityIndexBase;
//
//  Copy over entities and names
//
	for(int i = 0; i < entityCount; i++)
	{

	entityListPtr[i]     = (A.entityListPtr[i])->newDuplicateEntity();
	entityListPtr[i]->initializeReferenceCount();

	entityNameListPtr[i] = new char[strlen(A.entityNameListPtr[i]) + 1];
	strcpy(entityNameListPtr[i],A.entityNameListPtr[i]);
	}

	ceReferenceCount    = 0;
}
//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
CAMcombinedEntity::~CAMcombinedEntity()
{

	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	{
	entityListPtr[i]->decrementReferenceCount();
	if(entityListPtr[i]->getReferenceCount() == 0) delete entityListPtr[i];
	}
    }

	if(entityListPtr != 0) delete [] entityListPtr;

	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	delete [] entityNameListPtr[i];
	}

	if(entityNameListPtr != 0) delete [] entityNameListPtr;
}
//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//  (The objects in the combined geometric entity are replicated)
//
CAMcombinedEntity&  CAMcombinedEntity::operator =( const CAMcombinedEntity& A)
{
//
//  remove exisiting data
//
	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	{
	entityListPtr[i]->decrementReferenceCount();
	if(entityListPtr[i]->getReferenceCount() == 0) delete entityListPtr[i];
	}
	}

	if(entityListPtr != 0) delete [] entityListPtr;
	if(entityCount != 0)
	{
	for(int i = 0; i < entityCount; i++)
	delete [] entityNameListPtr[i];
	}
	if(entityNameListPtr != 0) delete [] entityNameListPtr;

	if((entityCount == 0)&&(entityIndexBase == 0))
	entityIndexBase = A.entityIndexBase;

//
//  create new data storage and copy
//
	entityPtrAllocation = A.entityPtrAllocation;
	entityListPtr       = new CAMgeometricEntity*[entityPtrAllocation];
	entityNameListPtr   = new char* [entityPtrAllocation];

	entityCount = A.entityCount;
//
//  Copy over entity pointers and names
//
	for(int i = 0; i < entityCount; i++)
	{

	entityListPtr[i]     = (A.entityListPtr[i])->newDuplicateEntity();
	entityListPtr[i]->initializeReferenceCount();

	entityNameListPtr[i] = new char[strlen(A.entityNameListPtr[i]) + 1];
	strcpy(entityNameListPtr[i],A.entityNameListPtr[i]);
	}

    return *this;
}
//
//********************************************************************************
//                    OUTPUT
//********************************************************************************
//
ostream&  operator  <<(ostream& out_stream, const CAMcombinedEntity& A)
{
//
   out_stream << "[BEGIN_ENTITY]" << "\n";
   out_stream << A.getEntityType() << "\n";
   out_stream << "[ENTITY_DATA]" << "\n";
   long i;
	for(i = 0; i < A.entityCount; i++)
	{
   out_stream << A.entityNameListPtr[i] << "\n";
	A.entityListPtr[i]->output(out_stream);
	}
   out_stream << "[END_ENTITY]\n";
	return(out_stream);
}
//
// Operator >> : This routine needs to know about all classes derived
// from CAMgeometricEntity. One could possibly remove this restriction
// with more clever C++ programming; later perhaps...
//
istream&   operator >>(istream& in_stream, CAMcombinedEntity& A)
{
    CAMcircleEntity         C;
    CAMxyRectangleEntity    R;
    CAMpolygonEntity        P;

	char lineInput[256];
    char nameInput[256];


    in_stream  >> lineInput;  // [BEGIN_ENTITY]
    in_stream  >> lineInput;  // CAMcombinedEntity
    in_stream  >> lineInput;  // [ENTITY_DATA]


    in_stream.getline(nameInput,256);   // clear eol
    in_stream.getline(nameInput,256);   // Name of entry
    if(strcmp(nameInput,"[END_ENTITY]")==0) return(in_stream);

    in_stream >> lineInput;
    while(strcmp(lineInput,"[BEGIN_ENTITY]")==0)
    {
    in_stream >> lineInput;  // class name

    if(strcmp(lineInput,"CAMcircleEntity") == 0)
    {
      C.inputData(in_stream);
      A.addEntity(nameInput,C);
    }
    if(strcmp(lineInput,"CAMxyRectangleEntity") == 0)
    {
      R.inputData(in_stream);
      A.addEntity(nameInput,R);
    }
    if(strcmp(lineInput,"CAMpolygonEntity") == 0)
    {
      P.inputData(in_stream);
      A.addEntity(nameInput,P);
    }

    in_stream.getline(nameInput,256);    // clear eol
    in_stream.getline(nameInput,256);
    if(strcmp(nameInput,"[END_ENTITY]")==0) return(in_stream);
	 in_stream >> lineInput;
    }
    
    return(in_stream);
}


//
//********************************************************************************
//                   GRAPHICS
//********************************************************************************
//
//void   CAMcombinedEntity::draw() const
//{
//	for(long i = 0; i < entityCount; i++)
//	{
//	entityListPtr[i]->draw();
//	}
//}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//

void  CAMcombinedEntity::addEntity(const CAMgeometricEntity& E)
{
//
	const char* EtypePtr  = E.getEntityType();
	int   typeCount = 0;
    long  nameSize  = (long)strlen(EtypePtr);
//
//  count the number of entities of the same type
//
	for(long i = 0; i < entityCount; i++)
	if(strncmp(EtypePtr,entityNameListPtr[i],nameSize) == 0) typeCount++;

	typeCount++;
//
//
	long NewEntityCount = entityCount + 1;

	if(NewEntityCount > entityPtrAllocation) expandList();
//
	entityCount++;
	entityListPtr[entityCount - 1] = E.newDuplicateEntity();
	entityListPtr[entityCount - 1]->initializeReferenceCount();
//
//  Create Name which is the type of the entity
//
	/* 
    nameSize   = nameSize  + 6;          // 6 extra => limit of 9999 entities of
							             // identical type
   	char* entityName = new char[nameSize];
    ostringstream(entityName,nameSize) << EtypePtr << " " << typeCount << ends;
    */
    
    //
    // New code : June 29, 2004 using stl sstream
    //
    ostringstream outs;
    outs << EtypePtr << " " << typeCount;
    nameSize         = long((outs.str()).size()) + 1;
	char* entityName = new char[nameSize];
    strcpy(entityName,(outs.str()).c_str());
    //
    //

    entityNameListPtr[entityCount - 1] = entityName;
}

void  CAMcombinedEntity::addEntity(const char* entityName, const CAMgeometricEntity& E)
{
	long NewEntityCount = entityCount + 1;

	if(NewEntityCount > entityPtrAllocation) expandList();

	entityCount++;
//
//
	long nameSize = (long)strlen(entityName);
	nameSize++;
	char* newEntityName = new char[nameSize];
	strcpy(newEntityName,entityName);
//
//
	entityListPtr[entityCount - 1] = E.newDuplicateEntity();
	entityListPtr[entityCount - 1]->initializeReferenceCount();
	entityNameListPtr[entityCount - 1] = newEntityName;
}

CAMgeometricEntity&  CAMcombinedEntity::operator[](CAMcharPtrHandle entityName) const
{
    long i = 0;
    long i_hit = -1;

	while((i < entityCount)&&(i_hit < 0))
	if(strcmp(entityName,entityNameListPtr[i]) != 0)
      { i++;}
    else
      { i_hit = i;}

	if(i>entityCount-1)
	{cerr << "Error : Invalid combinedEntity Index " << endl; exit(1);}

	return *(entityListPtr[i]);
}

CAMgeometricEntity&  CAMcombinedEntity::operator[](long  entityIndex) const
{
	if( ((entityIndex - entityIndexBase) < 0)||
		((entityIndex - entityIndexBase) > entityCount - 1)
	  )
	{cerr << "Error : Invalid combinedEntity Index " << endl; exit(1);}

	return *(entityListPtr[entityIndex - entityIndexBase]);
}

char*  CAMcombinedEntity::getIndexName(long index) const
{
	if( ((index - entityIndexBase) < 0)||
		((index - entityIndexBase) > entityCount - 1)
	  )
	{cerr << "Error : Invalid combinedEntity Index " << endl; exit(1);}

	return entityNameListPtr[index - entityIndexBase];
}

void  CAMcombinedEntity::setIndexName(long index, char* newName)
{
	if( ((index - entityIndexBase) < 0)||
		((index - entityIndexBase) > entityCount - 1)
	  )
	{cerr << "Error : Invalid combinedEntity Index " << endl; exit(1);}

	delete [] entityNameListPtr[index - entityIndexBase];
	entityNameListPtr[index - entityIndexBase] = new char[strlen(newName) + 1];
	strcpy(entityNameListPtr[index - entityIndexBase],newName);
}
void  CAMcombinedEntity::expandList()
{
	entityPtrAllocation +=  _CAMentityChunkSize_ ;

	CAMgeometricEntity** NewEntityListPtr = new CAMgeometricEntity*[entityPtrAllocation];
	char** NewEntityNameListPtr           = new char* [entityPtrAllocation];

	for(int i = 0; i < entityCount; i++)
	{
	NewEntityListPtr[i]     = entityListPtr[i];
	NewEntityNameListPtr[i] = entityNameListPtr[i];
	}

	delete [] entityListPtr;
	delete [] entityNameListPtr;

	entityListPtr     = NewEntityListPtr;
	entityNameListPtr = NewEntityNameListPtr;
}
int  CAMcombinedEntity::operator ==(const CAMcombinedEntity &E) const
{
	if(entityCount != E.entityCount) return 0;

	int flag = 1;
	for(int i = 0; i < entityCount; i++)
	{
	if( *entityListPtr[i] !=  E[i]) flag = 0;
	}
	return flag;
}
int  CAMcombinedEntity::operator !=(const CAMcombinedEntity &E) const
{
	if(entityCount != E.entityCount) return 1;

	int flag = 0;
	for(int i = 0; i < entityCount; i++)
	{
	if( *entityListPtr[i] !=  E[i]) flag = 1;
	}
	return flag;
}


int CAMcombinedEntity::interiorExteriorTest(double xTest, double yTest) const
//
//  Returns +1 if test point is interior to at least one of the elements
//  in the combined entity, -1 if exterior to all elements, 0 if on one
//  of the elements.
//
{
    long k;
    long interiorExteriorFlag = -1;

    if(entityCount == 0) return interiorExteriorFlag;

    else
    {
    interiorExteriorFlag = operator[](0).interiorExteriorTest(xTest,yTest);
    k = 1;
    while((interiorExteriorFlag == -1)&&(k < entityCount))
    {
    interiorExteriorFlag = operator[](k).interiorExteriorTest(xTest,yTest);
    k++;
    }
    }
    
    return interiorExteriorFlag;
}

/*
@begin_doc@
@title    @ getDistanceToBoundary()
@Purpose  @ Returns signed minimal distance to the boundary of the collection of 
entities. This routine is only defined for non-overlapping collections of entities. 
If a point is inside one of the entites, then it returns the (+) distance to it's boundary, 
otherwise it returns (-) the minimum distance to all of the entities. If the test
point is interior to more than one entity, an error message is generated and exit(1) is
called.
@end_doc  @
*/
double CAMcombinedEntity::getDistanceToBoundary(double x, double y) const
{
    long k;
    if(entityCount == 0) return 0.0;

    long interiorCount        =  0;
    long interiorIndex        =  0;
    long interiorExteriorFlag = -1;

    for(k = 0; k < entityCount; k++)
    {
        interiorExteriorFlag = operator[](k).interiorExteriorTest(x,y);
        if(interiorExteriorFlag > 0)
        {
        interiorCount++; 
        interiorIndex = k;
        }
    }


    if(interiorCount > 1) 
    {
    cerr << "Error : combinedEntity contains overlapping entities       " << endl; 
    cerr << "      : getDistanceToBoundary(...) is not implemented for  " << endl; 
    cerr << "      : points inside overlapping entities." << endl; 
    exit(1);
    }


    if(interiorCount == 1)
    {
    return operator[](interiorIndex).getDistanceToBoundary(x,y);
    }

    //
    // point exterior to all entities, so take the -minimum |distance|
    // to the entities.
    //
    double dMin;

    dMin = fabs(operator[](0).getDistanceToBoundary(x,y));
    double dTest;

    for(k = 1; k < entityCount; k++)
    {
    dTest = fabs(operator[](k).getDistanceToBoundary(x,y));
    dMin = (dMin < dTest) ? dMin : dTest;
    }
    
    return -dMin;
}

/*
@begin_doc@
@title    @ getExteriorDistanceToBoundary()
@Purpose  @ For a point exterior to a collection of entities, this routine returns
(-) the minimum distance to all of the entities. For a point interior to one or
more entities this routine returns the value 1.0. This routine is well defined for
overlapping entities.
@end_doc  @
*/
double CAMcombinedEntity::getExteriorDistanceToBoundary(double x, double y) const
{
    long k;
    if(entityCount == 0) return 0.0;

    long interiorCount        =  0;
    long interiorIndex        =  0;
    long interiorExteriorFlag = -1;

    for(k = 0; k < entityCount; k++)
    {
        interiorExteriorFlag = operator[](k).interiorExteriorTest(x,y);
        if(interiorExteriorFlag > 0)
        {
        interiorCount++;
        interiorIndex = k;
        }
    }

    if(interiorCount > 1)
    {
    return 1.0;
    }

    double dMin;
    if(interiorCount == 1)
    {
    dMin = operator[](interiorIndex).getDistanceToBoundary(x,y);
    if(dMin > 0.0){return 1.0; }
    else          {return dMin;}
    }

    //
    // point exterior to all entities, so take the -minimum |distance|
    // to the entities.
    //

    dMin = fabs(operator[](0).getDistanceToBoundary(x,y));
    double dTest;

    for(k = 1; k < entityCount; k++)
    {
    dTest = fabs(operator[](k).getDistanceToBoundary(x,y));
    dMin = (dMin < dTest) ? dMin : dTest;
    }

    return -dMin;
}


void  CAMcombinedEntity::getBoundingBox(double& bMinX, double& bMaxX, 
double& bMinY, double& bMaxY)
{
    long entityCount = getEntityCount();

    if(entityCount == 0) 
    {
    bMinX = 0.0; bMinY = 0.0;
    bMaxX = 0.0; bMaxY = 0.0;
    return;
    }

    long k;

    double minX; double maxX;
    double minY; double maxY;
    
    bMinX = operator[](0).getMinX();
    bMaxX = operator[](0).getMaxX();
    bMinY = operator[](0).getMinY();
    bMaxY = operator[](0).getMaxY();

    for(k = 1; k < entityCount; k++)
    {
    minX = operator[](k).getMinX();
    maxX = operator[](k).getMaxX();
    minY = operator[](k).getMinY();
    maxY = operator[](k).getMaxY();
    bMinX = (bMinX > minX) ? minX : bMinX;
    bMaxX = (bMaxX < maxX) ? maxX : bMaxX;
    bMinY = (bMinY > minY) ? minY : bMinY;
    bMaxY = (bMaxY < maxY) ? maxY : bMaxY;
    }

    return;
}
//
//
//********************************************************************************
//                     CPP File End 
//********************************************************************************
//

 
