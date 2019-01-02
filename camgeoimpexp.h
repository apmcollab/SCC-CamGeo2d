//
//  Import/Export Directive for CAMgeo DLL
//
//  Chris Anderson (C) UCLA 1997
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

#undef  __IMPEXP__

#ifdef  __BCPLUSPLUS__
#ifdef  __EXPORT_CAMGEOENTITY__
#define __IMPEXP__  __declspec(dllexport)
#endif
#ifdef  __USEDLL__
#define __IMPEXP__  __declspec(dllimport)
#endif
#endif


#ifdef  _MSC_VER
#ifdef  __EXPORT_CAMGEOENTITY__
#define __IMPEXP__  __declspec(dllexport)
#endif
#ifdef  __USEDLL__
#define __IMPEXP__  __declspec(dllimport)
#endif
#endif


#ifdef   __STATIC__
#undef   __IMPEXP__
#define  __IMPEXP__
#endif

#ifndef __IMPEXP__
#define __IMPEXP__
#endif 
