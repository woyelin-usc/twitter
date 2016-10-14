#ifndef HSORT_H
#define HSORT_H

#include <vector>

template <class T>
void swap(T& a, T& b)
{
  T temp = a;
  a = b;
  b = temp;
}


template <class T, class Comparator>
  void heapify(std::vector<T>& mylist, int parentIndex, unsigned int endIndex, Comparator comp)
{
  unsigned int leftChildIndex = parentIndex*2;
  unsigned int rightChildIndex = parentIndex*2+1;

  // base case: no left child
  if(leftChildIndex>endIndex)
    return;

  // base case: left child exists, but no right child
  // only compare parent and left child, swap if CHILD is LARGE (max-heap)
  else if(leftChildIndex==endIndex) {
    if( comp(mylist[ parentIndex ], mylist[ leftChildIndex] ) )
      swap( mylist[ leftChildIndex ] , mylist[ parentIndex ] );
  }

 // recursive case
  else {
    // get the large node index
    int largeIndex;
    // if left child node is larger, assign leftChildIndex to largeIndex
    if( comp( mylist[rightChildIndex], mylist[leftChildIndex] ) )
      largeIndex = leftChildIndex;
    // otherwise, assign rightChildIndex to largeIndex
    else
      largeIndex = rightChildIndex;

    // if parent node is smaller than large child node, then swap parent with the large child (max-heap)
    if( comp(mylist[ parentIndex ], mylist[ largeIndex ]))
      swap( mylist[ parentIndex ], mylist[ largeIndex ] );

    // recursive call on largeIndex node
    heapify(mylist, largeIndex, endIndex, comp);

  }

}


// this function convert array into a valid heap
template <class T, class Comparator>
  void makeValidHeap(std::vector<T>& mylist, int parentIndex, Comparator comp)
{
  // base case: already rearrange all needed parent node
  if(parentIndex==0)
    return;

  // rearrange current parent node
  heapify(mylist, parentIndex, mylist.size()-1, comp);

  // recursively rearrange next (literally last) parent node
  makeValidHeap(mylist, parentIndex-1, comp);

}


// dest: pop parent node to "dest" location in the array
template <class T, class Comparator>
  void hSort(std::vector<T>& mylist, int dest, Comparator comp)
{
  // base case: finish all pop ( from 1 to mylist.size() )
  if(dest==1)
    return;

  // swap it with the last val in the array
  swap(mylist[1], mylist[dest] );

  // call heapify to rearrange the heap
  heapify(mylist, 1, dest-1, comp);

  // recursive call
  hSort(mylist, dest-1, comp);

}



// this function is what the outside user calls in the main()
template <class T, class Comparator>
  void heapSort(std::vector<T>& mylist, Comparator comp)
{

  int size = mylist.size();
  
  // if empty vector, or only 1 item, done!
  if(size==0 || size ==1)
    return;

  // add a more item at the front of the vector
  // just make the empty item equals to current first item in the vector
  T empty = mylist[0];
  mylist.insert(mylist.begin(), empty);


  // first make it a valid max-heap, starting from first non leaf node
  makeValidHeap(mylist, (mylist.size()-1)/2 , comp);

  // then call top(), pop() n times
  hSort(mylist, mylist.size()-1, comp);

  // finally, remove the added first item
  mylist.erase(mylist.begin());

}

#endif
