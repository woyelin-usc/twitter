#include<stdexcept>
#include<cstdlib>
#include "AList.h"

template <class T>
class Set {
 
 public: 
  Set ();                     // constructor for an empty set
 
  Set (const Set<T> & other); // copy constructor, making a deep copy
  
  ~Set ();                    // destructor


  void add (const T & item); 
  /* Adds the item to the set. 
     Throws an exception if the set already contains the item. */

  void remove (const T & item);
  /* Removes the item from the set.
     Throws an exception if the set does not contain the item. */

  bool contains (const T & item) const;
  /* Returns true if the set contains the item, and false otherwise. */

  int size () const;
  /* Returns the number of elements in the set. */

  bool isEmpty () const;
  /* Returns true if the set is empty, and false otherwise. */

  Set<T> setIntersection (const Set<T> & other) const;
  /* Returns the intersection of the current set with other.
     That is, returns the set of all items that are both in this
     and in other. */

  Set<T> setUnion (const Set<T> & other) const;
  /* Returns the union of the current set with other.
     That is, returns the set of all items that are in this set
     or in other (or both). */

  T* first ();
  /* Returns the pointer to some element of the set, 
     which you may consider the "first" element.
     Should return NULL if the set is empty. */

  T* next ();
  /* Returns the pointer to an element of the set different from all 
     the ones that "first" and "next" have returned so far. 
     Should return NULL if there are no more element. */

 
 private:
  AList <T> internalStorage;

  int loc;
};


// constructor implementation
template <class T>
Set<T>::Set()
{
  loc=0;
}

// copy constructor
template <class T>
Set<T>::Set (const Set<T> & other)
{
  internalStorage=other.internalStorage;
}

// destructor implementation
template <class T>
Set<T>::~Set()
{
}


// size() implementation
template <class T>
int Set<T>::size() const
{
  return internalStorage.size();
}



// add() implementation
template <class T>
void Set<T>::add(const T & item)
{

  bool status=contains(item);

  if(status)
    throw std::invalid_argument("item already exists");

  // no item already exists, add item to the back
  internalStorage.insert(size(),item);

}


// remove() implementation
template <class T>
void Set<T>::remove(const T& item)
{
  int i;
  for(i=0;i<size();i++) {
    // if we find the item, remove it 
    if(item==internalStorage.get(i)) {
      internalStorage.remove(i);
      return;
    }
  }
  
  // we don't find the item
  throw std::invalid_argument("item doesn't exist");
 
}


// contain() implementation
template <class T>
bool Set<T>::contains(const T & item) const
{
  for(int i=0;i<size();i++){
    if(item==internalStorage.get(i))
      return true;
  }
  return false;
}



// isEmpty() implementation
template <class T>
bool Set<T>::isEmpty() const
{
  // if size>0, not empty
  if(size())
    return false;

  // otherwise, is empty
  return true;
}



template <class T>
Set<T> Set<T>::setIntersection (const Set<T> & other) const
{
  Set<T> temp;

  // add all items that exist in both set
  for(int i=0;i<size();i++) {
    for(int j=0;j<other.size();j++) {
      if( internalStorage.get(i)==other.internalStorage.get(j) )
	temp.add(internalStorage.get(i));
    }
  }
  return temp;
}


// setUnion() implementation
template <class T>
Set<T> Set<T>::setUnion (const Set<T> & other) const
{
  // use copy constructor to assign other to temp
  Set<T> temp(other);

  // after that ,add all non-duplicate items into temp
  for(int i=0;i<size();i++) {

    // first check duplicate items
    /* if( !temp.contains(internalStorage.get(i)) ) */
       temp.add( internalStorage.get(i) );

  }

  return temp;

}


// first() implementation
template <class T>
T* Set<T>:: first ()
{
  loc=0;

  // empty list, return NULL
  if(size()==0)
    return NULL;

  // create temp pointer points to "first" item
  T* temp=& (internalStorage.get(loc));
  return temp;
}


// next() implementation
template <class T>
T* Set<T>:: next()
{
  loc++;

  // no more elements, return NULL
  if(loc==size())
    return NULL;

  // create temp pointer points to "next" item
  T* temp=&( internalStorage.get(loc) );
  return temp;
 
}




