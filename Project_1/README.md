##CSCI 104 Project Repository

###Student Information
  + Name: Woye Lin
  + USC Email: woyelin@usc.edu
  + USC ID: 5131642330

###Project Description
This program will read in a file that contains all the information about users and tweets in a single place, and then produce one output file per user with the filename ```username.feed```. The feed will list the username on the first line and then all the tweets from the user and any users being followed sorted based on timestamp.


###Compile & Run Instructions
To compile the code, run the following command: 

```
$ make
```

To execute the program, run the following command:

```
$ bin/twitter twitter.dat
```

To clean the file (object file, .feed files) after running th1e program, run the following command: 

```
$ make clean
```
