#include "../include/user.h"
#include "../include/tweet.h"
#include "../include/datetime.h"
#include<iostream>
#include<string>
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
  // // delete every pointer in tweets AList
  // for(int i=0;i<_tweets.size();i++)
  //   delete tweets.get(i);

  // /* how to destruct _followers and _following since they are Set and 
  // don't have get() function?*/
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


AList<Tweet*> User::tweets()
{
  return _tweet;
}


void User::addFollower(User* u)
{
  _follower.add(u);
}


void User::addFollowing(User* u)
{
  _following.add(u);
}

/*
  add new tweet to the back*/
void User::addTweet(Tweet* t)
{
  _tweet.insert( _tweet.size(),t);
}


AList<Tweet*> User::getFeed()
{


  AList<Tweet*> temp;

  // first add all tweets to the temp, and then sort them from smallest to largest

  // add all user's own tweets to the back of temp
  for(int i=0;i<_tweet.size();i++) {
    temp.insert(temp.size(),_tweet.get(i));
  }

  // then add all this user's  following's tweets to the back of the temp
  for(User** followingPtr=_following.first();
      followingPtr!=NULL;
      followingPtr=_following.next() ) {

    for(int i=0;i< ((*followingPtr)->_tweet).size();i++) {
      temp.insert(temp.size(), ((*followingPtr)->_tweet).get(i));
    }
  }

  // after add all tweets, now sort them based on the datetime (smallest->largest)
  for(int i=temp.size();i>1;i--) {

    for(int j=0;j<i-1;j++) {
      if( *(temp.get(j)) >  *(temp.get(j+1))) {
  	Tweet* tempTweet=temp.get(j);
  	temp.get(j)=temp.get(j+1);
  	temp.get(j+1)=tempTweet;

      }
    }
  }
   
  
    // // add first pointer to the back
    // temp.insert(0,_tweet.get(0));
  
    // // insert all user's own tweets except the first one (already inserted)
    // for(int i=1;i<_tweet.size();i++) {
    //   int j=0;
    
    //   while(  ( (*( temp.get(j) ))<*( ( _tweet.get(i) )))  &&  ( j<temp.size() )  ) 
    // 	j++;
    
    //   // insert at the position j
    //   temp.insert( j, _tweet.get(i) );
    // }

    // // then insert all following's tweets
    // // use the sub-optimal iterator to go over each follower
    // for(User** followingPtr=_following.first();
    // 	followingPtr!=NULL; 
    // 	followingPtr=_following.next() )  {
    
    //   // go over each tweet of certain following
    //   for(int i=0;i<(  (*followingPtr)->_tweet).size();i++) {

    // 	// this while loop is used to find the right place to insert a followingPtr's tweet
    // 	while( ( ( *(temp.get(j)) ) < *( (  (*followingPtr)->_tweet).get(i)) ) && (j<temp.size()))
    // 	  j++;

    // 	temp.insert(j,  ((*followingPtr)->_tweet).get(i) );

    //   }

    // }
  

  return temp;
}







    




