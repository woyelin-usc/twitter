#ifndef TRENDTOPIC_H
#define TRENDTOPIC_H

#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QRadioButton>
#include <QListWidget>

#include "tweet.h"
#include "datetime.h"


class trendTopic: public QWidget
{
  Q_OBJECT

 public:

  // constructor
  trendTopic(std::map<std::string, std::vector<Tweet*> >&, std::vector<Tweet*>&, QWidget* parent = 0);

  // this function convert QDateTime to myDateTime
  DateTime* toMyDateTime(const QDateTime&);


  public slots:
    void addHashList();
    void displayHashTweet(const QString&);

 private:
  std::map< std::string, std::vector<Tweet*> > _hash;
  std::vector<Tweet*> _recentTweet;

  QComboBox* hashList;
  QPushButton* refreshBtn;
  QScrollArea* hashTweetArea;
  QListWidget* hashTweetList;

  QRadioButton* all;
  QRadioButton* day;


};

#endif




// this struct is used to sort the hash based on their occurence
struct hashAndTimes
{
  std::string _hashString;
  int _occurence;

  // constructor with parameters
hashAndTimes(std::string hashString, int occurence):
  _hashString(hashString), _occurence(occurence) {}
};


// define a hash comparator for merge sort on hash
struct hashCmp
{
  bool operator()(const hashAndTimes& a, const hashAndTimes& b) {
    return (a._occurence > b._occurence);
  }
};


// define a tweet comparator for merge sort on tweets
struct tweetCmp
{
  bool operator()(  Tweet* a,   Tweet* b) {
    return *a>*b;
  }
};
