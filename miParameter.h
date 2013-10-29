/*
  libpuDatatypes - Diverse datatypes: Regions, coordinates and alike
  
  Copyright (C) 2006-2013 met.no

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


#ifndef _miParameter_h
#define _miParameter_h

#include <set>
#include <string>

#define make_namespace
#include <parameter/parameter.h>

//using namespace c_parameter;

class miParameter {

  struct parcmp_ {
    bool operator()(const parameter& p1, const parameter& p2) const
    {
      std::string s1(p1.alias), s2(p2.alias);
      return (s1<s2);
    }
  };

  static std::set<parameter, parcmp_> parlist_;
  static bool initialised_;
  static std::string pardeffile_;

  void fillParlist_()
  {
    if (initialised_)
      return;

    parameter** plist;
    int npar;

    parsepardefs(pardeffile_.c_str(), &plist, &npar);
    for (int i=0; i<npar; i++) {
      parlist_.insert(*(plist[i]));
      free(plist[i]);
    }
    free(plist);
    initialised_=true;
  }

public:
  miParameter()
  {
    initialised_=false;
  }
  miParameter(const std::string& filename)
  {
    pardeffile_=filename;
    initialised_=false;
    fillParlist_();
  }

  void refill(const std::string& filename)
  {
    pardeffile_=filename;
    initialised_=false;
    parlist_.clear();
    fillParlist_();
  }

  int size() const { return parlist_.size(); }

  parameter aliasToPar(const std::string& alias) const
  {
    parameter p;
    strncpy(p.alias, alias.c_str(), ALIASZ);
    std::set<parameter, parcmp_>::iterator hit=parlist_.find(p);
    if (hit!=parlist_.end())
      return *hit;
    parameter q;
    return q;
  }

  void printNames() const
  {
    int sz=parlist_.size();
    for (set<parameter, parcmp_>::iterator i=parlist_.begin();
	 i!=parlist_.end(); i++)
      cout << (*i).name << endl;
  }

};
  
std::set<parameter, miParameter::parcmp_> miParameter::parlist_=
std::set<parameter, miParameter::parcmp_>();
std::string miParameter::pardeffile_="";
bool miParameter::initialised_=false;

#endif
