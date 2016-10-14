#include"../include/tweet.h"
#include"../include/datetime.h"
#include"../include/user.h"
#include<iostream>
#include<string>
#include<cstdlib>

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





