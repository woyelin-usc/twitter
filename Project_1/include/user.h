#ifndef USER_H
#define USER_H
#include "Set.h"
#include <string>


/* Forward Declaration to avoid #include dependencies */
class Tweet;

class User {
 public:

  // default constructor
  User();
  
  //Constructor 
  User(std::string name);

  // destructor
  ~User();

 
  /*Gets the name of the user
    return this user's name*/
  std::string name();


  /* Gets all the followers of this user
     return set of users*/
  Set<User*> followers();

  
  /* Gets all the users whom this user follows
     return set of following*/
  Set<User*> following();


  /* Gets all the tweets this user has posted
     return list of tweets this user this user posted */
  AList<Tweet*> tweets();


  // Adds a follower to this user's set of followers
  void addFollower(User* u);

  
  // Adds a following to this user's following
  void addFollowing(User* u);


  // Adds the given tweet as a post from this user
  void addTweet(Tweet* t);

  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  AList<Tweet*> getFeed();

 private:

  std::string _name;

  Set<User*> _follower;

  Set<User*> _following;

  AList<Tweet*> _tweet;

};

#endif
