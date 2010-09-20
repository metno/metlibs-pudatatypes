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

#ifndef _tsData_h
#define _tsData_h

// template class to hold a timeserie of one parameter.
// JS/PU 9/99

#include <map>
#include <set>
#include <vector>

#include <puTools/miTime.h>
#include <puTools/miString.h>

namespace puData {

template<class V> struct progVal {

  V value;
  int prog;

  progVal() :
    prog(0)
  {
  }
  progVal(V val) :
    value(val), prog(0)
  {
  }
  progVal(V val, int pr) :
    value(val), prog(pr)
  {
  }
  friend progVal<V> operator+(const progVal<V>& lhs, const progVal<V>& rhs)
  {
    return progVal((rhs.value + lhs.value), rhs.prog);
  }
  friend progVal<V> operator-(const progVal<V>& lhs, const progVal<V>& rhs)
  {
    return progVal((rhs.value - lhs.value), rhs.prog);
  }
  friend progVal<V> operator*(const progVal<V>& lhs, const progVal<V>& rhs)
  {
    return progVal((rhs.value * lhs.value), rhs.prog);
  }
  friend progVal<V> operator/(const progVal<V>& lhs, const progVal<V>& rhs)
  {
    return progVal((rhs.value / lhs.value), rhs.prog);
  }
  bool is_older_than(const progVal& rhs)
  {
    return rhs.prog < prog;
  }
  void set(const V& val, const int& pr)
  {
    value = val;
    prog = pr;
  }

};

struct datasource {
  miutil::miString name;
  miutil::miString tag;
};

typedef std::set<miutil::miTime> timeline;

template<class T> class tsData {
private:
  //  parameter p;
  datasource src;
  std::map<miutil::miTime, progVal<T> > data;
public:
  tsData<T> ()
  {
  }
  tsData<T> (const tsData<T>& tsIn)
  {
    copyMembers(tsIn);
  }
  tsData<T> (const int & p, const int& s) :
    pindex(p), sindex(s)
  {
  }

  // standart stuff. Get the data in and out again...

  int pindex, sindex;
  bool empty()
  {
    return data.empty();
  }
  void clean()
  {
    data.clear();
  }
  void push(const miutil::miTime t, const T val, const int& pr = 0)
  {
    data[t] = progVal<T> (val, pr);
  }

  void setTs(std::map<miutil::miTime, progVal<T> > ts)
  {
    data = ts;
  }

  T value(miutil::miTime tim)
  {
    return data[tim].value;
  }
  int prog(miutil::miTime tim)
  {
    return data[tim].prog;
  }
  std::map<miutil::miTime, progVal<T> > series() const
  {
    return data;
  }
  timeline times()
  {
    return times(data);
  }

  tsData<T>& operator=(const tsData<T>& rhs)
  {
    copyMembers(rhs);
    return *this;
  }

  progVal<T> operator[](miutil::miTime req)
  {
    progVal<T> a;
    return ((data.count(req) > 0) ? data[req] : a);
  }

  void copyMembers(const tsData<T>& rhs)
  {
    src = rhs.src;
    data = rhs.data;
    pindex = rhs.pindex;
    sindex = rhs.sindex;

    // p = rhs.p;
  }
  // just for the test fun:

  friend std::ostream& operator<<(std::ostream& out, const tsData<T>& tsd)
  {
    std::map<miutil::miTime, progVal<T> > ts = tsd.series();

    typedef typename std::map<miutil::miTime, progVal<T> >::iterator
        osTProgvalItr;

    osTProgvalItr itr = ts.begin();
    std::cout << "valid time           prog   value" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    for (; itr != ts.end(); itr++)
      out << itr->first << "  " << itr->second.prog
          << (itr->second.prog >= 100 ? "    " : "     ") << itr->second.value
          << std::endl;
    return out;
  }

};

}
;

#endif

