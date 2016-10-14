#ifndef MAP_H
#define MAP_H
#include"AList.h"
#include<stdexcept>
#include<cstdlib>

// add a new pair struct definition
template <class keyType, class valueType>
struct pair 
{
  keyType k;
  valueType v;
};


template <class keyType, class valueType>
class Map
{

 public:
 
  Map ();  // constructor for a new empty map

  ~Map (); // destructor

  int size () const; // returns the number of key-value pairs

  void add (const keyType & key, const valueType & value); 
  /* Adds a new association between the given key and the given value.*/

  void remove (const keyType & key);
     /* Removes the association for the given key.
        If the key has no association, it should throw an exception */

  valueType const & get (const keyType & key) const;
  /* Returns the value associated with the given key by constant reference.
     If the key has no association, it should throw an exception. */

  valueType& get (const keyType & key);
  /* Returns the value associated with the given key by mutable reference.
        If the key has no association, it should throw an exception. */

  bool contains (const keyType & key) const;
  /* Returns true if the key exists in the map, false, otherwise */

 private:
  AList<  pair<keyType,valueType>*  > internalStorage;
  /* Store all associations inside internalStorage list. 
     every element in the internalStorage is a pointer to 
     corresponding pair in the heap */

  // find() helper function
  int find(const keyType& key) const; 

};


// find(): helper function
template <class keyType, class valueType>
  int Map<keyType,valueType>::find(const keyType& key) const
{
  // if we find the key, return the index
  for(int i=0;i<internalStorage.size();i++){
    if( (internalStorage.get(i))->k ==key) 
      return i;
  }
  // if don't find the key, return -1
  return -1;
}

// constructor implementation
template<class keyType, class valueType>
Map<keyType,valueType>::Map()
{
}

// destructor: delete all pointers to the pair
template<class keyType, class valueType>
  Map<keyType, valueType>::~Map()
{
  for(int i=0;i<internalStorage.size();i++)
    delete internalStorage.get(i);
}

// size() implementation: use AList implementation size()
template<class keyType, class valueType>
  int Map<keyType,valueType>::size() const
{
  return internalStorage.size();
}

// add() implementation
template<class keyType, class valueType>
  void Map<keyType,valueType>::add (const keyType & key, const valueType & value)
{
  int index=find(key);

  // if we don't find the key or an empty list, create a new pair
  if(index==-1) {
    //create a new pair
    pair<keyType, valueType>* newPair = new pair<keyType, valueType>;
    newPair->k=key;
    newPair->v=value;

    // add the new pair to the back
    internalStorage.insert(internalStorage.size(), newPair);
    return;
  }

  /* if we have found the key in the map, replace the value
     replace the value */
  internalStorage.get(index)->v=value;
  return;

}

// remove() implementation
template <class keyType, class valueType>
  void Map<keyType, valueType>::remove(const keyType & key)
{

  // exception: don't find the key or empty map
  if( find(key)==-1 || internalStorage.size()==0 )
    throw std::invalid_argument("No such key");

  int index=find(key);
  delete internalStorage.get(index);
  internalStorage.remove(index);
  return;
}

// get() const implementaion
template <class keyType, class valueType>
  valueType const & Map<keyType, valueType>::get (const keyType & key) const
{
  int index=find(key);

  // if we don't find the key
  if(index==-1)
    throw std::invalid_argument("No such key");

  return internalStorage.get(index)->v;
}
// get() implementation
template <class keyType, class valueType>
  valueType& Map<keyType, valueType>::get (const keyType & key)
{
  int index=find(key);

  if(index==-1)
    throw std::invalid_argument("No such key");
  return internalStorage.get(index)->v;
}

// contains() implementation
template <class keyType, class valueType>
  bool Map<keyType, valueType>::contains (const keyType & key) const
{
  int index=find(key);

  // if find() returns -1, meaning we don't find, return false
  if(index==-1)
    return false;
  //else return true
  return true;
}
 

#endif
