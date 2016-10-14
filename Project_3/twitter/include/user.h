#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Set.h"


/* Forward Declaration to avoid #include dependencies */
class Tweet;

class User {
 public:

  /*
   * Default Constructor
   */
  User();


  /**
   * Constructor 
   */
  User(std::string name);

  /**
   * Destructor
   */
  ~User();

  /**
   * Gets the name of the user 
   * 
   * @return name of the user 
   */
  std::string name();

  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  Set<User*> followers();

  /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
  Set<User*> following();

  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  std::vector<Tweet*> tweets();


  /**
   * Gets all the "mentioned this user" tweet
   *
   * @return List of "mentioned this user" tweet
   */
  std::vector<Tweet*> mentionTweets();


  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  void addFollower(User* u);

  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  void addFollowing(User* u);

  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
  void addTweet(Tweet* t);


  /**
   * if a tweet @ this user, add as a mention tweet
   */
  void addMentionTweet(Tweet* t);


  /**
   * return whether two users follow each other
   */
  bool followEachOther(User*);


  /**
   * sorted a tweet list
   */
  void sortTweet(std::vector<Tweet*>& t);


  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  std::vector<Tweet*> getFeed();


  /**
   * Produces the list of SORTED Tweets that @ this user
   */
  std::vector<Tweet*> getMentionFeed();

 private:

  // user's name
  std::string _name;

  // who follow this user
  Set<User*> _follower;

  // who is this user following
  Set<User*> _following;

  // the tweets that this user post
  std::vector<Tweet*> _tweet;

  // the tweets that mention this user
  std::vector<Tweet*> _mentionTweet;

};

#endif
