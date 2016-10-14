#include "../include/user.h"
#include "../include/tweet.h"
#include "../include/datetime.h"

#include<algorithm>
#include <stdexcept>

using namespace std;

// default constructor
User::User()
{
  _name="";
}


// constructor: initialization list
User::User(std::string name):_name(name)
{
}


// destructor 
User::~User()
{
}


std::string User::name()
{
  return _name;
}


Set<User*> User::followers()
{
  return _follower;
}


Set<User*> User::following()
{
  return _following;
}


vector<Tweet*> User::tweets()
{
  return _tweet;
}


vector<Tweet*> User::mentionTweets()
{
  return _mentionTweet;
}


void User::addFollower(User* u)
{
  _follower.insert(u);
}


void User::addFollowing(User* u)
{
  _following.insert(u);
}


void User::addTweet(Tweet* t)
{
  _tweet.push_back(t);
}


/* 
 * if the tweet mention this user, 
 * add as a mentioned tweet
 */
void User::addMentionTweet(Tweet* t)
{
  vector<string> mentionedUser = t->whoIsMentioned();
  for(unsigned int i=0;i<mentionedUser.size();i++) {
    if(mentionedUser[i]==_name) {
      _mentionTweet.push_back(t);
      break;
    }
  }
}



/*
 * sort a tweet list
 */
void User::sortTweet(vector<Tweet*>& t)
{
  // empty exception
  if(t.size()==0)
    throw invalid_argument("Empty size");

  for(unsigned int i=t.size();i>1;i--) {

    for(unsigned int j=0;j<i-1;j++) {
      if( *(t.at(j)) > *(t.at(j+1)) ) {
  	Tweet* tempTweet = t.at(j);
  	t.at(j) = t.at(j+1);
  	t.at(j+1) = tempTweet;
      }
    }
  }
}



/*
 * return a list of tweets
 * containing this user's tweets
 * and all following user's tweets
 */
vector<Tweet*> User::getFeed()
{
  vector<Tweet*> temp;

  // add all this user's own tweet
  for(unsigned int i=0;i<_tweet.size();i++)
    temp.push_back(_tweet.at(i));

  // For all following user's tweets
  for(Set<User*>::iterator it = _following.begin();
      it!=_following.end();
      ++it) {

    /*
     * theTweet is user (*it)'s all tweets
     */
    vector<Tweet*> theTweet = (*it)->_tweet;

    for(unsigned int i=0;i< theTweet.size();i++) {

      vector<string> mentionedUser = theTweet[i]->whoIsMentioned();

      // if a tweet starts with @
      if( theTweet[i]->firstStringCheck()) {

	// get all mentionedUser in this tweet
	vector<string> mentionUser = theTweet[i]->whoIsMentioned();
	// check whether this tweet @ this user
	unsigned int k=0;
	for(;k<mentionUser.size();k++) {
	  if( mentionUser[k]==_name)
	    break;
	}

	// if this tweet @ this user
	if(k<mentionUser.size()) {
	  // if this user and this tweet's poster follow each other,add
	  if( followEachOther(*it)){
  	    temp.push_back(theTweet[i]);
	  }
	}
      }

      // otherwise, add this tweet
      else {
	temp.push_back(theTweet[i]);
      }

    }
  }

  //sort if not empty
  if(!temp.empty())
    sortTweet(temp);

  return temp;

}


vector<Tweet*> User::getMentionFeed()
{
  return _mentionTweet;
}


/* 
 *return true follow each other
 */
bool User::followEachOther(User* u)
{
  Set<User*> uFSet = u->following();

  return (_following.find(u)!=_following.end()) 
    &&
    (uFSet.find(this)!=uFSet.end())
    ;
}




