#ifndef FRONT_H
#define FRONT_H

#include "user.h"
#include "tweet.h"
#include "trendTopic.h"

#include <QComboBox>
#include <string>
#include <QString>
#include <QScrollArea>
#include <QListWidget>
#include <QPushButton>
#include <vector>
#include <map>
#include <QLineEdit>
#include <QMessageBox>
#include <QDateTime>
#include <QLabel>

class front: public QWidget
{
  Q_OBJECT

 public:

  // constructor
  front(std::map<std::string, User*>&, 
	std::map<std::string, std::vector<Tweet*> >&,
	QWidget* parent = 0);


  DateTime toMyDateTime(const QDateTime* dt);


  void sameUserFollowing();
  void alreadyFollowing();
  void successfullyFollowing();


  public slots:
  // show main feed function
  void showMainFeed();

  // show mention feed function
  void showMentionFeed();

  // enter new tweet function
  void enterNewTweet();

  // save current information
  void saveInformation();

  // follow other user
  void followOtherUser();

  // display a new window for trend topics
  void displayTrendTopic();

 private:

  std::map<std::string, User*> _user;
  std::map<std::string, std::vector<Tweet*> > _hash;
  std::vector<Tweet*> _recentTweet;

  QComboBox* userList;

  // main/mention feed
  QListWidget* mainTweetList;
  QListWidget* mentionTweetList;
  QScrollArea* mainFeedArea;
  QScrollArea* mentionFeedArea;
  QLabel* mainFeedLabel;
  QLabel* mentionFeedLabel;

  // enter a new tweet
  QPushButton* enterNewTweetBtn;
  QLineEdit* newTweetLine;

  // save current information
  QLineEdit* ofileName;
  QPushButton* saveInfoBtn;

  // follow other user
  QComboBox* followingList;;
  QPushButton* followBtn;


  // trend topic button
  QPushButton* trendTopicBtn;


};

#endif
