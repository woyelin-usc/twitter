#ifndef FRONT_H
#define FRONT_H

#include "user.h"
#include "tweet.h"

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

class front: public QWidget
{
  Q_OBJECT

    public:

  // constructor
  front(std::map<std::string, User*>&, QWidget* parent = 0);

  // pop out message box
  void sameUserFollowing();
  void alreadyFollowing();
  void successfullyFollowing();
  void successfullyEnter();
  void emptyTweet();
  void successfullySave();
  void emptyFileName();
  void emptyMainFeed();
  void emptyMentionFeed();

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

 private:

  std::map<std::string, User*> _user;
  QComboBox* userList;

  // main/mention feed
  QListWidget* mainTweetList;
  QListWidget* mentionTweetList;
  QScrollArea* mainFeedArea;
  QScrollArea* mentionFeedArea;
  QPushButton* mainFeedBtn;
  QPushButton* mentionFeedBtn;

  // enter a new tweet
  QPushButton* enterNewTweetBtn;
  QLineEdit* newTweetLine;

  // save current information
  QLineEdit* ofileName;
  QPushButton* saveInfoBtn;

  // follow other user
  QComboBox* followingList;;
  QPushButton* followBtn;

};

#endif
