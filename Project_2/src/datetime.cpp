#include"../include/datetime.h"
#include<iostream>
#include<iomanip>

using namespace std;

// default constructor
DateTime::DateTime()
{
}

// constructor: initialize list
DateTime::DateTime(int hh, int mm, int ss, int year,int month, int day):_hour(hh), _minute(mm), _second(ss),_year(year), _month(month), _day(day)
{
} 

/* 
return true: <
return false: >=
*/
bool DateTime::operator<(const DateTime& other)
{
  // compare from year to second
  if(_year<other._year)
    return true;
  else if(_year==other._year) {
    if(_month<other._month)
      return true;
    else if(_month==other._month) {
      if(_day<other._day)
	return true;
      else if(_day==other._day) {
	if(_hour<other._hour)
	  return true;
	else if(_hour==other._hour){
	  if(_minute<other._minute)
	    return true;
	  else if (_minute==other._minute) {
	    if(_second<other._second)
	      return true;
	  }
	}
      }
    }
  }
  return false;
}



/*
return true: >
return false: <=
 */
bool DateTime::operator>(const DateTime& other)
{
  // compare from year to second
  if(_year>other._year)
    return true;
  else if(_year==other._year) {
    if(_month>other._month)
      return true;
    else if(_month==other._month) {
      if(_day>other._day)
	return true;
      else if(_day==other._day) {
	if(_hour>other._hour)
	  return true;
	else if(_hour==other._hour){
	  if(_minute>other._minute)
	    return true;
	  else if (_minute==other._minute) {
	    if(_second>other._second)
	      return true;
	  }
	}
      }
    }
  }
  return false;
}


// outputs the timestamp based on given format
ostream& operator<<(std::ostream& os, const DateTime& other)
{
  os<<setfill('0')<<setw(4)<<other._year<<"-"
    <<setw(2)<<other._month<<"-"
    <<setw(2)<<other._day<<" "
    <<setw(2)<<other._hour<<":"
    <<setw(2)<<other._minute<<":"
    <<setw(2)<<other._second;
  return os;
}  

