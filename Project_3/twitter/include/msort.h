#ifndef MSORT_H
#define MSORT_H

#include <vector>

// this function merge two sorted array together
template <class T, class Comparator>
  void merge(std::vector<T>& sArray, std::vector<T>& myArray,
	     int start, int mid, int end, Comparator& comp)
{

  // l: first index of the left half array
  int l = start;
  // r: first index of the right half array
  int r = mid;
  // index: first index of the big merge array
  int index = start;


  // compare two arrays one by one, always push back the samller one
  while(l<mid && r<end) {

    if( comp(sArray[l], sArray[r]) ) 
      myArray[index++] = sArray[l++];
    
    else 
      myArray[index++]= sArray[r++];
  }
    
    
  // if left half array has remaining, push back all remaining
  while(l<mid)
    myArray[index++]=sArray[l++];

  // if right half array has remaining, push back all remaining
  while(r<end)
    myArray[index++]=sArray[r++];

    
  // make sArray sorted too
  for(int i=start;i<end;i++)
    sArray[i]=myArray[i];

  
}


/*
 * this is the helper function to mainly divided array
 * start: inclusive   
 * end: exclusive
 */
template <class T, class Comparator>
  void mSort(std::vector<T>& sArray, std::vector<T>& myArray, 
	     int start, int end, Comparator& comp)
{
  // keep dividing the array until there is only one item
  if(start<end-1) {
    int mid = (start+end)/2;
    mSort(sArray, myArray, start, mid, comp);
    mSort(sArray, myArray, mid, end, comp);
    merge(sArray, myArray, start, mid, end, comp);
  }
}



template <class T, class Comparator>
  void mergeSort(std::vector<T>& myArray, Comparator& comp)
{

  int size = myArray.size();

  // make a copy array: sArray
  std::vector<T> sArray;
  for(int i=0; i<size;i++)
    sArray.push_back(myArray[i]);

  // call helper function to devide
  // start index: 0 (inclusive)
  // end index: size (exclusive)
  mSort(sArray, myArray, 0, size, comp);
}
 
#endif
