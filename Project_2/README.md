##CSCI 104 Project Repository

###Student Information
  + Name: Woye Lin
  + USC Email: woyelin@usc.edu
  + USC ID: 5131642330

###Project Description
This program will read in a file that contains all the information about users and tweets in a single place, and shows up a Qt front window. In this window, user can:

1 check each user's main feed and mention feed

* first select the user from the user list at the very top of the window
* then click ```main feed``` or ```@ feed``` button to check this user's main feed or mention feed 

2 follow other user

* The user list at the very top of the window is the user you are currently in
* The user list at the next line is the user you want to follow

3 enter a new tweet for a certain user

* The user list at the very top of the window is the user you are currently in
* when you finish inputting the tweet, click ```enter``` button

4 save all current information into a new database file.

* enter the output file name in the textbox
* after that, click ```save``` button


###Compile & Run Instructions
To compile the code, run the following command: 

```
$ qmake -project
$ qmake
$ make
```

To execute the program, run the following command:

```
$ ./proj_woyelin twitter.dat
```