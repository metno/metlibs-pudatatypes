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


#ifndef _miRegions_h
#define _miRegions_h

#include "miCoordinates.h"
#include "miLine.h"

#include <puTools/miString.h>

#include <vector>
#include <set>

using namespace std; 

/// class containing a region withy corners name etc.
/** The object can be compared to other regions and has functionallity to:
 *  - join and splitt regions 
 *  - check areal 
 *  - check boundary boxes
 *  - and more ..
 *
*/
class miRegions {
  typedef enum BoundaryComp { INTERSECTION, HTANGENT, VTANGENT, PASSANT };
  
  /// Struct to keep a boundary box for a miRegion 
  /** The struct contains a lower left corner and an upper right corner
   *
  */
  typedef struct miBoundaryBox {
    int ll_lon;  ///< lower left  corner
    int ll_lat;  
    int ur_lon;  ///< upper right corner
    int ur_lat;
  
    /// check how two Boundary boxes relate to another
    BoundaryComp compare(miBoundaryBox&);

    /// check if a coordinate is inside the box with a tolerance in centiseconds
    bool         isInside(miCoordinates&, int tolerance=0);
    
    miBoundaryBox() {}
    miBoundaryBox(const miCoordinates& ll, const miCoordinates& ur);

  };

private:
  vector<miCoordinates> corner;
  vector<miLine>        border;
  miString              name_;
  int                   idn;
  set<miCoordinates>    cornerset;

  miCoordinates         orig;
  int                   priority_;
  int                   area_;    // km2

  vector<miRegions>     triangles_;

  miCoordinates         upper_right;
  miCoordinates         lower_left;
  miCoordinates         center_;


  void setBorders();
  bool isPartOfSubregion(const miLine&, const miCoordinates&, miString) const;
  bool cornerCompare( vector<miCoordinates> c) const;

public:
  miRegions() {}
  /// create an empty region with a name, but without coordinates
  miRegions( miString name, int id) : name_(name), idn(id) {}
  /// create a region by joining to others 
  miRegions( miRegions lhs, miRegions rhs, int tolerance=1) { join(lhs,rhs,tolerance); }

  // MODIFY--------------------------------------------------------

  /// join two regions
  /** The result will affect this region directly.
   *  lhs and rhs are not unchanged except that their
   *  area is computed   
   *  tolerance is the tolerance in km to find connecting points...
  */
  bool join( miRegions lhs, miRegions rhs,int tolerance=1);  

  void clear();
  void setId(      int i                         ) { idn      = i; }
  void setPriority(int p                         ) { priority_= p; }
  void setName(    miString n                    ) { name_    = n; }
  void setOrigin(  const miCoordinates & o       ) { orig     = o; }
  void setCorners( const vector<miCoordinates> &c);

  /// set a new corner
  /** Warning! this function calls setBorder to recalculate all Borders etc.
   *  when creating a new region create a vector<miCoordinates> and use    
   *  use setCorners instead
   */
  void addCorner(  miCoordinates    );
  /// calls addCorner(miCoordinates);
  void addCorner(  int lon, int lat );

  // QUESTIONS/INFORMATION --------------------------------------------


  vector<miCoordinates> getCorners() const { return corner; }
  vector<miRegions>     triangles();

  miString regName()    const { return name_;              }
  int      regId()      const { return idn;                }
  int      priority()   const { return priority_;          }
  int      size()       const { return corner.size();      }

  bool     isRegion()   const { return corner.size() >  2; } 
  bool     isTriangle() const { return corner.size() == 3; }
  int      area();



  miRegions::miBoundaryBox getBoundary() const;
  miRegions::miBoundaryBox getFuzzyBoundary(float deg) const;

  vector<miCoordinates>    getBoundaryGrid(int noOfGrids, bool inside=true) const;

  miCoordinates origo()              const { return orig;        }
  miCoordinates upper_right_corner() const { return upper_right; }
  miCoordinates lower_left_corner()  const { return lower_left;  }
  miCoordinates center()             const { return center_;     }


  bool      isIdentical(           miRegions&, int threshold=95  ) const; // treshold in %
  bool      isInside(        const miCoordinates&                ) const;
  bool      isInside(        const miRegions&, int threshold=85  ) const; // treshold in %
  bool      isCloseOrInside( const miCoordinates&                ) const;
  int       no_of_crosses(   const miLine&                       ) const;
 
  miRegions subregion(float c,miString sector, bool& ok,int rnd=0) const; //sector=N|S|W|E

  bool      isCounterClockwise();
  void      turnCounterClockwise();
  bool      isConvex();


  friend    ostream& operator<<(ostream&, const miRegions&);
};

#endif
