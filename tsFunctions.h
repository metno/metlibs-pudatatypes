/*
  libpuDatatypes - Diverse datatypes: Regions, coordinates and alike
  
  $Id$

  Copyright (C) 2006 met.no

  Contact information:
  Norwegian Meteorological Institute
  Box 43 Blindern
  0313 OSLO
  NORWAY
  email: diana@met.no
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef _tsFunctions_h
#define _tsFunctions_h

#include "tsData.h"

#include <puTools/miTime.h>
#include <puTools/miString.h>

#include <map>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>


using namespace std;

namespace puData {

  // dance the timeseries
  enum maskType {
    AandB,
    AorB,
    AnotB
  };


 
  template<class T> struct  A_plus_B {
    progVal<T> operator()( const progVal<T>& A, const progVal<T>& B)
    { return A+B;}
  };	
  template<class T> struct  A_minus_B {
    progVal<T> operator()( const progVal<T>& A, const progVal<T>& B)
    { return A-B;}
  };
  template<class T> struct  A_B_middle {
    progVal<T> operator()( const progVal<T>& A, const progVal<T>& B)
    { return (A+B)/2;}
  };
  template<class T> struct  prefer_A {
    progVal<T> operator()( const progVal<T>& A, const progVal<T>& B)
    { return A;}
  };			
  
  
  // subscribe one function object (functor): F 
  // prefer_A<T> preferA; -> send in preferA
  // define them yourself if you want to ... just one () operator
  // and we're talking
  // return value has to be progVal<T>

  template<class T, typename F>
  map<miTime,progVal<T> > mask(  map<miTime,progVal<T> > A,
				 map<miTime,progVal<T> > B,
				 F& fun,
				 const maskType & mt = AandB){
    map<miTime,progVal<T> > iSect;
    map<miTime,progVal<T> > AB;

    typedef typename   map<miTime,progVal<T> >::iterator tPItr0;

    tPItr0 itr = A.begin();
    
    

    if(mt == AnotB ){
      for( ; itr != A.end(); itr++)
	if( !bool(B.count( itr->first )) ) 
	  AB[itr->first] = itr->second;
      return AB;
    }
    
    for( ; itr != A.end(); itr++)
      if( bool(B.count( itr->first ))) 
	iSect[itr->first] = fun(itr->second, B[ itr->first ]);
    
    if(mt == AandB )
      return iSect;
    
    AB = B;    
    
    for(itr = A.begin() ; itr != A.end(); itr++)
      AB[itr->first] = ( bool(iSect.count( itr->first )) ? 
			 iSect[itr->first ] : itr->second );    
    return AB;
  };

  // with no given function ( class F - > predef is not allowed !)

  template<class T>
  map<miTime,progVal<T> > mask(  map<miTime,progVal<T> > A, 
				 map<miTime,progVal<T> > B,
				 const maskType & mt = AandB){
    prefer_A<T> fun;
    return mask (A,B,fun,mt);
  };


  // select a specific prog or discard one
  template<class T>
  map<miTime,progVal<T> > mask( const map<miTime,progVal<T> >& data,
				const int& pr, const bool & incl = true  ){

    

    map<miTime,progVal<T> > ts = data;
    typedef typename   map<miTime,progVal<T> >::iterator tPItr1;
    tPItr1 itr = ts.begin();
    for( ; itr != ts.end(); itr++)
      if( (itr->second.prog == pr) == incl   ) 
	ts.erase(itr);
    return ts;
  };

  // getting the timeline
  template<class T>
  timeline times( const map<miTime,progVal<T> > & tsin ){
    timeline t;
    map<miTime,progVal<T> > ts = tsin;

    typedef typename   map<miTime,progVal<T> >::iterator tPItr2;
    tPItr2 itr = ts.begin();
    for(; itr != ts.end(); itr++)
      t.insert( itr->first );
    return t;
  };

};

#endif






