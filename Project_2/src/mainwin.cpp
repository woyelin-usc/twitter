#include "../include/user.h"
#include "../include/tweet.h"
#include "../include/datetime.h"
#include "../include/Set.h"
#include "../include/front.h"

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<QString>

#include <QApplication>

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
  iFile>>numUser;

    string buf;
    getline(iFile, buf);

    // dynamically allocate user map
    map<string,User*> user;

    // dynamically allocate user's name array
    string* userName=new string[numUser];

    // read user's information
    for(int i=0;i<numUser;i++) {

      // userLine: user information line
      string userLine="";
      getline(iFile, userLine);

      stringstream ss(userLine);

      // store user's name
      ss>>userName[i];

      // if the user hasn't been created in the map,create first
      if( user.find(userName[i])==user.end() ){
      	User* newUser = new User(userName[i]);
      	user[userName[i]]=newUser;
      }

      // continue add following user
      string followingUserName="";
      while(ss>>followingUserName) {

	// if the user hasn't been created in the map, create first
	if( user.find(followingUserName)==user.end()) {
	  User* newUser = new User(followingUserName);
	  user[followingUserName]=newUser;
	}

	// add following relationship to this user
	user[ userName[i] ]->addFollowing( user[ followingUserName] );
	user[ followingUserName ]->addFollower( user[ userName[i]] );
      }
    }


    // Now read in tweets
    string tweetLine="";

    while(getline(iFile, tweetLine)) {

      stringstream ss(tweetLine);

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

      // get the pure content of the tweet
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
      Tweet* newTweet = new Tweet(user[theUserName], dt, tweetText);

      // add the tweet to the corresponding user
      user[theUserName]->addTweet(newTweet);

      /*
       * check replied and mention tweet and if is the case
       * add to the corresponding user's corresponding tweet
       */
      for(map<string, User*>::iterator it = user.begin();
	  it!=user.end();
	  ++it) {
	(it->second)->addMentionTweet(newTweet);
      }
    }

    // close the iFile
    iFile.close();


    /**********GUI***********/
    QApplication app(argc,argv);
    front twitterFront(user);

    twitterFront.show();
    return app.exec();

}
