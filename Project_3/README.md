##CSCI 104 Project Repository

###Student Information
  + Name: Woye Lin
  + USC Email: woyelin@usc.edu
  + USC ID: 5131642330

###Project Description

* Step 1: implement Heap Sort

  * The answer to this question is in file ```hsort.h```

* Step 2: Project

  1 The twitter GUI program is in repository  ```twitter``` . I add the hashtag functionality into this part of project.

  * To check all the hashtags, click the  ```Trend Topic``` button at the very bottom of the main window, it will pop out a new window.

   * To check hashtags and corresponding tweets for all time, first check the  ```All time```  radiobutton, and then click  ```refresh``` button. Up to 10 hash tags (and its occurence) will be displayed in the combobox in the order from most occurence to least (I use my merge sort as my O(nlogn) sort approach). To see the tweets containing certain hashtag, first check that hashtag in the combobox, then all the tweets containing that hashtag will automatcally show up in the scroll area below in the order from most recent to least recent.

   * To check hashtags in the past 24 hours, just check the  ```Past 24 hours```  radiobutton, and everything else is the same.


###Compile & Run Instructions


##### To test heapSort:

1 run the following command to enter the repository

```
$ cd proj_woyelin
```

2 Add the following line to the head of your test code:

```
#include 'hsort.h'
```

3 to compile the code, run the following command:

``` 
$ g++ -Wall -g -std=c++11 -o test yourTestFileName
```

4 To execute the test program, run the following command:

```
$ ./test
```


##### To test Twitter project

First, run the following command to enter twitter repository:

```
$ cd proj_woyelin
$ cd twitter
```

To compile the code, run the following command: 

```
$ make
```

To execute the program, run the following command:

```
$ ./twitter twitter.dat
```
