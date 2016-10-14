#include "../include/user.h"
#include "../include/tweet.h"
#include "../include/datetime.h"
#include "../include/AList.h"


#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<sstream>

using namespace std;

int main(int argc, char* argv[])
{
  // check command line
  if(argc<2) {
    cerr<<"Usage: ./twitter twitter.dat"<<endl;
    return 1;
  }

  // create iFile
  ifstream iFile(argv[1]);

  if( iFile.fail() ){
    cout<<"cannot open the file"<<endl;
    return 1;
  }

  // read in number of user
  int numUser;

  if(iFile>>numUser) {
  
  string buf;
  getline(iFile, buf);

  // dynamically allocate users pointer array
  User* allUser[numUser];

  // dynamically allocate user's name array
  // this userName array is used to initialize allUser
  string* userName=new string[numUser];

  // this "followingList" is used to store all following's name for every user
  AList<string>* followingList=new AList<string>[numUser];


  // read user's information line by line
  for(int i=0;i<numUser;i++) {

    // userLine: user information line
    string userLine="";
    getline(iFile, userLine);

    stringstream ss(userLine);

    // store user's name
    ss>>userName[i];

    // allUser[i] is a pointer to user: initialize user object
    allUser[i]= new User(userName[i]);

    // store all following user
    string followingName="";

    // add all following user
    while( ss>>followingName ){
      
      // add every following name to the back of followingList
      followingList[i].insert(followingList[i].size(), followingName);
    }

  }

  // this is to add every user's all following
    for(int i=0;i<numUser;i++) {
      for(int j=0;j<followingList[i].size();j++) {

	// find which user allUser[k] is the following of allUser[i]
	int k=0;
	while(allUser[k]->name()!=followingList[i].get(j))
	  k++;

	// add allUser[k] as one of allUser[i]'s following
	allUser[i]->addFollowing( allUser[k] );

      }
    }



    /* Now read in tweets
       as long as don't reach the end of file */

    /******************************************************************
     * Why this is wrong?
     * while(!iFile.fail()) {
     *string theLine;
     *getline(iFile, theLine);
     * ......
     * always show one more line of datetime, same as the last datetime
     ******************************************************************/

    string theLine="";
    
    while(getline(iFile, theLine)){

      stringstream ss(theLine);

      // get the timestamp
      int theYear, theMonth, theDay, theHour, theMinute, theSecond;
      ss>>theYear;
      ss.ignore(1);
      ss>>theMonth;
      ss.ignore(1);
      ss>>theDay;
      ss.ignore(1);
      ss>>theHour;
      ss.ignore(1);
      ss>>theMinute;
      ss.ignore(1);
      ss>>theSecond;
      ss.ignore(1);

      // create datetime object
      DateTime dt(theHour, theMinute, theSecond, theYear, theMonth, theDay);

      // readin who post this tweet
      string theUserName="";
      ss>>theUserName;
      ss.ignore(1);


      // this part is to get the user* who post this tweet
      int whichUser;
      for(whichUser=0;whichUser<numUser;whichUser++) {
	if( theUserName==allUser[whichUser]->name() ) {
	  break;
	}
      }


      // this part is to get the pure content of the tweet
      string tweetText="";
      string word;    
      while(ss>>word){
	tweetText+=word;
	tweetText+=" ";
      }

      /**
       * So far, we got user*, pure tweetText and datetime
       * use these three parts to create a new tweet 
       */
      Tweet* newTweet = new Tweet(allUser[whichUser], dt, tweetText);
 
      // add the tweet to the corresponding user
      allUser[whichUser]->addTweet(newTweet);

    }

    // close the readin file
    iFile.close();

    // Here I have already add all the tweets into corresponding user
    // it's time to output the tweets

    for(int i=0;i<numUser;i++) {
      // get the list of tweets that are going to output
      AList<Tweet*> outTweet = allUser[i]->getFeed();

      // create the file name
      string fileName=allUser[i]->name()+".feed";
      ofstream oFile(fileName);

      // output the user name in the first line of the output file
      oFile<<allUser[i]->name()<<endl;

      // output all the tweets of user and the following
      for(int j=0;j<outTweet.size();j++) {
	oFile<<*(outTweet.get(j))<<endl;
      }

      // close the file
      oFile.close();
    }

    delete[] userName;
  }
  else {
    cerr<<"Not a valid number of user"<<endl;
  }
}

