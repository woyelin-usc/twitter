#include"../include/tweet.h"
#include"../include/datetime.h"
#include"../include/user.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<sstream>
#include<stdexcept>
#include<algorithm>

using namespace std;

// default constructor
Tweet::Tweet()
{
  _user=NULL;
  _text="";
}


// constructor: initialization list
Tweet::Tweet(User* user, DateTime& time, std::string& text):_user(user), _time(time),_text(text)
{
}


// return this temp's time
DateTime const& Tweet::time() const
{
  return _time;
}


// return this temp's text
string const& Tweet::text() const
{
  return _text;
}


bool Tweet::operator<(const Tweet& other){
  return _time < other._time;
}


bool Tweet::operator>(const Tweet& other){
  return _time > other._time;
}


// return this tweet's "time+user+text"
ostream& operator<<(ostream& os, const Tweet& t)
{
  os<<t._time<<" "<<t._user->name()<<" "<<t._text;
  return os;
}


vector<string> Tweet::whoIsReplied()
{
  stringstream ss(_text);
  vector<string> repliedUserName;
  string word="";
  while(ss>>word){

  /* 
   * if we found the first "not @" word , 
   * break the loop and return the function immediately
   */
    if( word[0]!='@')
      break;

    /*
     * if first word is "@",
     * pushback mentioend user's name
     */
    else {
      // delete the '@'
      word.erase(0,1);
      // add mentioned user name
      repliedUserName.push_back(word);
    }
  }
  return repliedUserName;
}


// judge who is mentioned in the tweet
vector<string> Tweet::whoIsMentioned()
{
  vector<string> mentionedUserName;
  string word="";
  stringstream ss(_text);

  /*
   * check the whole sentence of _text
   * if we find a @, 
   * return the mentioned user's name
   */
  while(ss>>word) {
    if(word[0]=='@') {
      // delete the '@'
      word.erase(0,1);
      mentionedUserName.push_back(word);
    }
  }
 
  return mentionedUserName;

}


bool Tweet::firstStringCheck()
{
  stringstream ss(_text);
  string firstWord="";
  ss>>firstWord;

  return (firstWord[0]=='@');
}
