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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "miCoordinates.h"
#include <sstream>


using namespace std;
using namespace miutil;

// --- constructor stuff ---


const double rEarth = 6370;

/*
  ===================================================
                 coor
  ===================================================
*/

coor::coor(const int& i)
{
  deg = i/10000;
  cmin = i - (deg * 10000 );
  deg%=360;
}


coor::coor( const float& f )
{
  float fdeg = f;
  deg = int(fdeg);
  fdeg-=deg;
  deg%=360;
  fdeg*=6000;
  cmin = int(fdeg);
}

void coor::addCmin( const int& rhs)
{
  int toDeg = 0;
  cmin += rhs;

   if(cmin >= 6000 ){
    toDeg = cmin/6000;
    cmin  = cmin%6000;
  }
   if(cmin < 0 ){
    toDeg = -(cmin/6000)-1;
    cmin-= 6000*toDeg;
   }
   deg+=toDeg;
}

bool coor::round(int r, bool best)
{
  if( r<10 )
    return false;


  if( r>6000 ) {
    deg+= ((cmin > 3000)==best ? 1 : 0 );
    cmin=0;
  } else {

    int   pre =       r/2;
    float fpre=(float(r)/2)-pre+1;

    int front=cmin/r;
    int tail=cmin%r;

    if((float(tail)/float(r) > 0.5 )==best )
      front++;

    cmin=front*r;
  }
  return true;
}


bool operator==(const coor& rhs,const coor& lhs)
{
  return ( rhs.fCoor() == lhs.fCoor() );
}

bool operator!=(const coor& rhs,const coor& lhs)
{
  return !( rhs == lhs );
}

bool operator>(const coor& rhs,const coor& lhs)
{
  return ( rhs.fCoor() > lhs.fCoor() );
}

bool operator<(const coor& rhs,const coor& lhs)
{
  return lhs > rhs ;
}

bool operator>=(const coor& rhs,const coor& lhs)
{
  return ( rhs.fCoor() >= lhs.fCoor() );
}

bool operator<=(const coor& rhs,const coor& lhs)
{
  return ( rhs.fCoor() <= lhs.fCoor() );
}


/*
  ===================================================
                 miCoordinates
  ===================================================
*/


miCoordinates::miCoordinates( const int& lon, const int& lat,int rnd )
{
  lon_ = coor(lon);
  lat_ = coor(lat);

  if(rnd) round(rnd);
}

miCoordinates::miCoordinates( const float& lon, const float& lat,int rnd )
{
  lon_ = coor(lon);
  lat_ = coor(lat);
  if(rnd) round(rnd);
}

miCoordinates::miCoordinates( const coor& lon, const coor& lat,int rnd )
 : lon_(lon), lat_(lat)
{
  if(rnd) round(rnd);
}

// --- transformations ---

float miCoordinates::fCoor( const coor& l ) const
{
  return (float(l.cmin)/6000 ) + float(l.deg);
}

int miCoordinates::iCoor( const coor& l) const
{
  return (l.deg*10000) + l.cmin;
}

coor miCoordinates::invert(const coor& outc ) const
{
  coor tmp = outc;
  tmp.deg*=(-1);
  tmp.cmin*=(-1);
  return tmp;
}

double miCoordinates::toRad( const coor& c ) const
{
  double rad;
  rad  =   float(c.deg)/ 180 ;
  rad += ( float(c.cmin)/ (180*6000) );
  rad *=M_PI;
  return rad;
}


void miCoordinates::round(int r)
{
  if(lon_.round(r)) lat_.round(r);
}

vector<miCoordinates> miCoordinates::roundedGrid(int r)
{
  vector<miCoordinates> p;

  coor latr=lat_;
  coor lonr=lon_;
  coor lati=lat_;
  coor loni=lon_;

  if(!latr.round(r,true  )) return p;
  if(!lonr.round(r,true  )) return p;
  if(!lati.round(r,false )) return p;
  if(!loni.round(r,false )) return p;

  p.push_back(miCoordinates(lonr,latr));
  p.push_back(miCoordinates(loni,latr));
  p.push_back(miCoordinates(lonr,lati));
  p.push_back(miCoordinates(loni,lati));
  return p;
}




int miCoordinates::km2deg( int distkm , bool isLon ) const
{
  coor zero;
  int result,tmpInt;

  if(isLon)
    zero = lat_;

  result =int(float(distkm)/(1.852 * cos( toRad( zero ) ) )*100);

  if(result >= 6000 ){
    tmpInt = result/6000;
    tmpInt*= 10000;
    result = result%6000;
    result+=tmpInt;
  }
  return result;
}

// --- checks ---

bool miCoordinates::isInRect(const miCoordinates& nw,
			     const miCoordinates& se ) const
{
  if ( nw.lat_ < lat_ || nw.lon_ > lon_ )
    return false;
  if ( se.lat_ > lat_ || se.lon_ < lon_ )
    return false;
  return true;
}

// --- operators ---

miCoordinates operator+(const miCoordinates& lhs,const miCoordinates&  rhs)
{
  miCoordinates tmp = lhs;
  tmp.addLon(rhs.lon_);
  tmp.addLat(rhs.lat_);
  return tmp;
}

miCoordinates operator-(const miCoordinates& lhs,const miCoordinates&  rhs)
{
  miCoordinates tmp  = lhs;
  miCoordinates tmp2 = rhs;
  tmp.addLon( tmp2.invert( tmp2.lon_ ));
  tmp.addLat( tmp2.invert( tmp2.lat_ ));
  return tmp;
}


miCoordinates operator/(miCoordinates lhs,float rhs)
{
  float flon= lhs.dLon()/rhs;
  float flat= lhs.dLat()/rhs;
  return miCoordinates(flon,flat);
};



bool operator==( const miCoordinates& lhs, const miCoordinates& rhs)
{
  if (lhs.iLon() != rhs.iLon() )
    return false;
  if (lhs.iLat() != rhs.iLat() )
    return false;

  return true;
}

bool operator!=( const miCoordinates& lhs, const miCoordinates& rhs)
{
  return !(lhs == rhs );
}

bool operator>( const miCoordinates& lhs, const miCoordinates& rhs)
{
  int a = lhs.iLon()*100 + lhs.iLat();
  int b = rhs.iLon()*100 + rhs.iLat();
  return a>b ;
}

bool operator<( const miCoordinates& lhs, const miCoordinates& rhs)
{
  return rhs > lhs ;
}

// --- add coordinates ---

void miCoordinates::addLon(coor rhs)
{

  rhs.deg%=360;

  lon_.addCmin(rhs.cmin);

  lon_.deg += rhs.deg;

  float fc = fCoor(lon_ );

  if(fc >= 180 )
    lon_.deg -= 360;

  if(lon_.deg <= -180 )
    lon_.deg += 360;

}

void miCoordinates::addLat(coor rhs)
{
  coor turn(float(180.0));

  rhs.deg %= 360;

  lat_.deg += rhs.deg;

  lat_.addCmin(rhs.cmin);

  lat_.deg%=360;

  float fc = fCoor( lat_ );

  if ( fc >= 270  )
    fc-=360;
  if ( fc <= -270 )
    fc+= 360;

  if ( fc >= 90 ){
    fc = 180 - lat_.deg;
    addLon( turn );
  }

  if (fc <= - 90 ){
    fc+=180;
    fc*=(-1);
    addLon( turn );
  }
  lat_ = coor(fc);

}



// --- ostream ---


miString miCoordinates::str()
{
  ostringstream out;
  out << sLon() << " : " << sLat();
  return out.str();
}

miString miCoordinates::encode()
{
  ostringstream out;
  out << lon_.deg << ":" << lon_.cmin << ":"
      << lat_.deg << ":" << lat_.cmin;
  return out.str();
}

bool miCoordinates::decode(const miString& str)
{
  vector<miString> vstr = str.split(":");
  if( vstr.size() == 4){
    lon_.deg = atoi(vstr[0].cStr());
    lon_.cmin= atoi(vstr[1].cStr());
    lat_.deg = atoi(vstr[2].cStr());
    lat_.cmin= atoi(vstr[3].cStr());
    return true;
  }
  return false;
}

miString miCoordinates::sLon()
{
 ostringstream out;
 char lonp = ((iLon() < 0) ? 'W': 'E');
 out << abs(lon_.deg) << "° "
     << fabs(float(lon_.cmin)/100)
     << "\'" << lonp;
 return out.str();
}


miString miCoordinates::sLat()
{
 ostringstream out;
 char latp = ((iLat() < 0) ? 'S': 'N');
 out << abs(lat_.deg) << "° "
     << fabs(float(lat_.cmin)/100)
     << "\'" << latp;
 return out.str();
}

ostream& operator<<(ostream& out, const miCoordinates& rhs)
{
  miCoordinates tmp = rhs;
  out << tmp.str();
  return out;
}


double miCoordinates::sekant(double ang) const
{
  double res,hal;

  hal = ( M_PI - ang ) / 2;
  res = sin(ang) / sin(hal);
  return res;
}

// --- distance to somewhere (in km)

int miCoordinates::distance( const miCoordinates& in) const
{
  double angle_c;
  double a,b,c,dist;
  double alpha;
  double rlo,rla;

  angle_c = cos(in.rLat()) * cos(rLat());

  miCoordinates diff = *this - in ;

  rlo = fabs(diff.rLon() );
  rla = fabs(diff.rLat() );

  if ( rlo< 0.000000001 )
    alpha = rla;

  else if ( rla < 0.000000001)
    alpha = sqrt( angle_c ) * rlo;

  else {

    a = sekant(rlo );
    b = sekant(rla );

    c = sqrt( a*a*angle_c + b*b );

    alpha = 2 * asin( c / 2 );
  }

  if ( alpha > M_PI )
    alpha = 2 * M_PI - alpha;

  dist = rEarth * alpha;

  return static_cast<int>(rint(dist));
}

double miCoordinates::cross(const miCoordinates& c) const
{
  double cro  = ( dLon() * c.dLat() ) - ( dLat() *  c.dLon() );
  return cro;
}

bool miCoordinates::isCloserThan(const miCoordinates& lhs, int tolerance)
{
  if(tolerance==0)
    return ( lhs == *this );

  return ( distance(lhs) <= tolerance );

}
