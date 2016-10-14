#ifndef SET_H
#define SET_H

#include<cstdlib>
#include<set>

template <class T>
class Set : public std::set<T>
{ 
 public: 

  Set<T> setIntersection (const Set<T> & other) const;
  /* Returns the intersection of the current set with other.
     That is, returns the set of all items that are both in this
     and in other. */

  Set<T> setUnion (const Set<T> & other) const;
  /* Returns the union of the current set with other.
     That is, returns the set of all items that are in this set
     or in other (or both). */

};


// setIntersection() implementation
template <class T>
Set<T> Set<T>::setIntersection (const Set<T> & other) const
{
  Set<T> temp;

  // add all items that exist in both set
  for(typename std::set<T>::iterator it=this->begin();
      it!=this->end();
      ++it) {
    for(typename std::set<T>::iterator iter=other.begin();
	  iter!=other.end();
	++iter) {
      if( *it==*iter ) 
	temp.insert(*it);
    }
  }
  return temp;
}



// setUnion() implementation
template <class T>
Set<T> Set<T>::setUnion (const Set<T> & other) const
{
  // create a empty set
  Set<T> temp;

  // copy every element in "this" set
  for(typename std::set<T>::iterator it = this->begin();
      it!=this->end();
      ++it) {
    temp.insert(*it);
  }


  // after that, ,add all non-duplicate items into temp
  for(typename std::set<T>::iterator it = other.begin();
      it!=other.end();
      ++it) {

    // first check duplicate items, then add
    if(this->find(*it)!=this->end()) 
      temp.insert(*it);
  }

  return temp;

};

#endif
