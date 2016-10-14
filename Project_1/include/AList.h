#include<cstdlib>
#include<stdexcept>
#ifndef ALIST_H
#define ALIST_H
#include<cstdlib>

#include<iostream>

template <class T>
struct Item
{
  T value;
  Item<T> *prev, *next;
};

template <class T>
class AList
{
 public:
  AList ();   // constructor

  ~AList ();  // destructor

  int size() const;  // returns the number of elements in the list

  void insert (int position, const T & val); 
  /* insert value before position */

  void remove (int position);
  /* Removes the item from the given position, shifting all
     later items one position to the left.*/

  void set (int position, const T & val);
  /* Overwrites the given position with the given value.
     Does not affect any other positions.  
     Your function should throw an exception if position is
     outside the legal range. */


  T& get (int position) ;
      /* Returns a non-const reference to the item at the given position.
         Your function should throw an exception if position is
         outside the legal range. */

  T const& get (int position) const;
      /* Returns a const reference to the item at the given position.
         Your function should throw an exception if position is
         outside the legal range. */

  AList (const AList<T> & other);
  // A copy constructor which performs a deep copy.

  AList<T> & operator= (const AList<T> & other);
  // An assignment operators.



 private:

  /* head pointer to the 1st item in your linked list */
  T* head;

  /*indicates how many elements are logically in the list*/
  int _size;

  /*which indicates how large the array is*/
  int capacity;

};


// constructor implementation
template <class T>
AList<T>::AList()
{
  capacity=5;
  _size=0;
  head= new T[capacity];
}

// destructor implementation
template <class T>
AList<T>::~AList()
{
  delete[] head;
}


//size() implementation
template <class T>
int AList<T>::size() const
{
  return _size;
}


// insert() implementation
template <class T>
void AList<T>::insert (int position, const T & val)
{
  if( position<0 || position>size() )
    throw std::out_of_range("error position");

  // the list hasn't been full
  if(_size<capacity){

    // empty list
    if(_size==0) {
      head[_size]=val;
      _size++;
      return;
    }

    int i;
    // shift every element after the position
    for(i=_size;i>position;i--)
      head[i]=head[i-1];

    // insert the value
    head[i]=val;

    // increase the size by 1
    _size++;

    return;

  }

  // the list has already been full
  
  //double the capacity of list
  capacity=2*capacity;

  // oldList pointer points to old list
  T* oldList=head;
   
  // move head points to the new list
  head= new T[capacity];

  // copy from oldList into new list
  int j;
  for(j=0;j<_size;j++)
    head[j]=oldList[j];

  // free oldList arrayList
  delete[] oldList;

  // insert the value
  int k;
  for(k=_size;k>position;k--)
    head[k]=head[k-1];

  head[k]=val;

  _size++;

  return;

}

// remove() implementation
template <class T>
void AList<T>::remove(int position)
{

  // exception
  if(position<0 || position>_size)
    throw std::out_of_range("error position");

  // empty list
  if(_size==0)
    return;

  // remove 
  for(int i=position;i<_size-1;i++)
    head[i]=head[i+1];

  _size--;
}

// set() implementation
template <class T>
void AList<T>::set (int position, const T & val)
{
  // exception
  if( position<0 || position> _size-1 )
    throw std::out_of_range("error position");

  // overwrite
  head[position]=val;
  return;
}

// get() implementation
template <class T>
T& AList<T>::get (int position)
{
  // exception
  if( position<0 || position>_size-1)
    throw std::out_of_range("error position");

  return head[position];
}

// get() const implementation
template <class T>
const T& AList<T>::get (int position) const
{
  // exception
  if( position<0 || position>_size-1)
    throw std::out_of_range("error position");

  return head[position];
}


// copy constructor
template <class T>
AList<T>::AList (const AList<T> & other)
{
  _size=other.size();
  capacity=other.capacity;
  head=new T[other.capacity];

  // copy element
  for(int i=0;i<_size;i++)
    head[i]=other.get(i);
}

// operator assignment
template <class T>
AList<T>& AList<T>::operator=(const AList<T>& other)
{
  // self assignment check
  if(this==&other)
    return *this;

  // initilization check
  if(head) 
    delete[] head;

  _size=other._size;
  capacity=other.capacity;
  head=new T[capacity];

  //element by element copy
  for(int i=0;i<_size;i++)
    head[i]=other.get(i);

  return *this;
}


#endif

