#include "../include/front.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <sstream>
#include <QDateTime>
#include <fstream>

using namespace std;

DateTime front::toMyDateTime(const QDateTime* dt)
{

  QString format = QString::fromStdString("yyyy-MM-dd hh:mm:ss");
  string dateTimeString = (dt->toString(format)).toStdString();

  // parse dateTimeString
  stringstream ss(dateTimeString);
  int theYear, theMonth, theDay, theHour, theMinute, theSecond;
  ss>>theYear; ss.ignore(1); ss>>theMonth; ss.ignore(1); ss>>theDay;ss.ignore(1); 
  ss>>theHour; ss.ignore(1); ss>>theMinute; ss.ignore(1); ss>>theSecond; ss.ignore(1);
      
  // create datetime object
  DateTime myDateTime(theHour, theMinute, theSecond, theYear, theMonth, theDay);

  return myDateTime;
}



// constructor
front::front(map<string, User*>& user, map<string, vector<Tweet*> >& hash, QWidget* parent): QWidget(parent), _user(user), _hash(hash)
{

  // set two user lists
  userList = new QComboBox;
  followingList = new QComboBox;
  // add all user to the user list
 for(map<string, User*>::iterator it = _user.begin();
	it!=_user.end();
	++it) {
   QString theName = QString::fromStdString(it->first);
   userList->addItem( theName);
   followingList->addItem( theName);
 }


 followBtn = new QPushButton("Follow");

  // main feed
  mainFeedLabel = new QLabel("main feed");
  mainTweetList = new QListWidget;
  mainFeedArea = new QScrollArea;
  mainFeedArea->setWidget(mainTweetList);
  mainFeedArea->setWidgetResizable(true);

  // mention feed
  mentionFeedLabel = new QLabel("@ feed");
  mentionTweetList = new QListWidget;
  mentionFeedArea = new QScrollArea;
  mentionFeedArea->setWidget(mentionTweetList);
  mentionFeedArea->setWidgetResizable(true);

  // enter new tweet
  enterNewTweetBtn = new QPushButton("Enter");
  newTweetLine = new QLineEdit;


  // save current informationto a file
  ofileName = new QLineEdit;
  saveInfoBtn = new QPushButton("Save");


  // user and following user lists: a formlayout
  QFormLayout* userFormLayout = new QFormLayout;
  userFormLayout->addRow("User: ", userList);

  QFormLayout* followFormLayout = new QFormLayout;
  followFormLayout->addRow("Choose to follow: ", followingList);


  QGridLayout* userGLayout = new QGridLayout;
  userGLayout->addLayout(userFormLayout,0,0);
  userGLayout->addLayout(followFormLayout,1,0);
  userGLayout->addWidget(followBtn,1,1);
  

  // main feed and @ feed: a formlayout
  QFormLayout* feedFormLayout = new QFormLayout;
  feedFormLayout->addRow(mainFeedLabel, mainFeedArea);
  feedFormLayout->addRow(mentionFeedLabel, mentionFeedArea);

  // enter new tweet: a hlayout with a formlayout
  QFormLayout* newTweetFormLayout = new QFormLayout;
  newTweetFormLayout->addRow("New tweet:", newTweetLine);
  QHBoxLayout* newTweetHLayout = new QHBoxLayout;
  newTweetHLayout->addLayout(newTweetFormLayout);
  newTweetHLayout->addWidget(enterNewTweetBtn);

  // used to save the file: a hlayout with a formlayout
  QFormLayout* saveFormLayout = new QFormLayout;
  saveFormLayout->addRow("output file name:", ofileName);
  QHBoxLayout* saveHLayout = new QHBoxLayout;
  saveHLayout->addLayout(saveFormLayout);
  saveHLayout->addWidget(saveInfoBtn);


  // set trend topic button
  trendTopicBtn = new QPushButton("Trend Topic");


  // set main layout: a gridlayout
  QGridLayout* gLayout = new QGridLayout;
  gLayout->addLayout(userGLayout,0,0,1,2);
  gLayout->addLayout(feedFormLayout, 1,0,1,2);
  gLayout->addLayout(newTweetHLayout,2,0,1,2);
  gLayout->addLayout(saveHLayout,3,0,1,2);

  gLayout->addWidget(trendTopicBtn,4,0,1,2);

  // set main layout
  setLayout(gLayout);

  // follow btn connect
  connect(followBtn, SIGNAL(clicked()), this, SLOT( followOtherUser()));

  // main/mention feed connect
  connect(userList, SIGNAL(currentIndexChanged(const QString&)),this,SLOT( showMainFeed()));
  connect(userList, SIGNAL(currentIndexChanged(const QString&)), this, SLOT( showMentionFeed()));


  // enter new tweet btn connect
  connect(enterNewTweetBtn, SIGNAL(clicked()), this, SLOT( enterNewTweet()));


  // save current information btn connect
  connect(saveInfoBtn, SIGNAL(clicked()), this, SLOT( saveInformation()));


  // display a trend topic window
  connect(trendTopicBtn, SIGNAL(clicked()), this, SLOT( displayTrendTopic()));


  connect(enterNewTweetBtn, SIGNAL(clicked()), this, SLOT( showMainFeed()));

  connect(enterNewTweetBtn, SIGNAL(clicked()), this, SLOT( showMentionFeed()));



  // create a datetime object
  QDateTime* dt = new QDateTime;
   
  // get current datetime
  *dt = dt->currentDateTime();
  DateTime endDT = toMyDateTime(dt);
    
  // startDT: current date time - 1 day
  *dt = dt->addDays(-1);
  DateTime startDT = toMyDateTime(dt);

  // initialize for _recentTweet vector
 for(map<string, vector<Tweet*> >::iterator it = _hash.begin();
      it != _hash.end();
      ++it) {

    // check whether tweet was posted in the past 24 hours
    vector<Tweet*> thisHashTweet = it->second;
    for(unsigned int i=0;i<thisHashTweet.size();i++) {

      // get this tweet's datetime
      DateTime thisDT = thisHashTweet[i]->time();
      // if this tweet was posted in the past 24 hours, check whether _recentTweet already contains this tweetthen push it into _recentTweet
      if( (thisDT > startDT) && (thisDT < endDT) ) {

	bool find=false;
	for(unsigned int z=0;z<_recentTweet.size();z++) {
	  if(_recentTweet[z] == thisHashTweet[i] ) {
	    find=true;
	    break;
	  }
	}
	if(!find)
	  _recentTweet.push_back( thisHashTweet[i] );
      }
    }
  }


 // initialize the main/mention feed with first user on the userlist
 showMainFeed();
 showMentionFeed();

}


void front::showMainFeed()
{

  // first clear existing tweets
  mainTweetList->clear();

  // get user's name
  string currentUserName = userList->currentText().toStdString();

  // if((_user[currentUserName]->getFeed()).empty())
  //   emptyMainFeed();

  vector<Tweet*> theMainFeed = _user[currentUserName]->getFeed();
  // if( theMainFeed.size()==0)
  //   emptyMainFeed();
  if(! (theMainFeed.empty()) ) {
    vector<Tweet*> theTweet = (_user[currentUserName])->getFeed();

    for(int i=theTweet.size()-1;i>=0;i--) {
      
      // use stringstream to get a whole tweet (including timestamep)
      stringstream ss;
      ss<<*(theTweet[i]);
      string stdTweetTxt="";
      string word;
      while(ss>>word)
      stdTweetTxt+=word+" " ;
      
      // convert std::string to QString
      QString QTweetTxt = QString::fromStdString(stdTweetTxt);
      // create a list item
      QListWidgetItem* item = new QListWidgetItem(QTweetTxt);
      // add that item into the list
      mainTweetList->addItem(item);
    }
  }
}


void front::showMentionFeed()
{
 // first clear existing tweets
  mentionTweetList->clear();

  // get user's name
  string currentUserName = userList->currentText().toStdString();
  
  if( (_user[currentUserName]->mentionTweets()).size()>0 ) {
  
    vector<Tweet*> theTweet = (_user[currentUserName])->mentionTweets();

    for(int i=theTweet.size()-1;i>=0;i--) {

      // use stringstream to get a whole tweet (including timestamep)
      stringstream ss;
      ss<<*(theTweet[i]);
      string stdTweetTxt="";
      string word;
      while(ss>>word)
	stdTweetTxt+=word+" " ;
      
      // convert std::string to QString
      QString QTweetTxt = QString::fromStdString(stdTweetTxt);
      // create a list item
      QListWidgetItem* item = new QListWidgetItem(QTweetTxt);
      // add that item into the list
      mentionTweetList->addItem(item);
    }
  }
}


// enter new tweet
void front::enterNewTweet()
{
  // get the new tweet text
  string tweetTxt = (newTweetLine->text()).toStdString();

  // if not empty tweet
  if(tweetTxt!=""){

    // get user's name
    string currentUserName = userList->currentText().toStdString();
    // create datetime object
    QDateTime* qdt = new QDateTime;
    string stdFormat = "yyyy-MM-dd hh:mm:ss";
    QString format = QString::fromStdString(stdFormat);

    string dateTimeString = ((qdt->currentDateTime()).toString(format)).toStdString();


    // parse dateTimeString
    stringstream ss(dateTimeString);
    int theYear, theMonth, theDay, theHour, theMinute, theSecond;
    ss>>theYear;
    ss.ignore(1);
    ss>>theMonth;
    ss.ignore(1);
    ss>>theDay;
    ss.ignore(1);
    ss>>theHour;
    ss.ignore(1);
    ss>>theMinute;
    ss.ignore(1);
    ss>>theSecond;
    ss.ignore(1);
      
    // create datetime object
    DateTime dt(theHour, theMinute, theSecond, theYear, theMonth, theDay);


    // create a new tweet
    Tweet* createTweet = new Tweet(_user[currentUserName], dt, tweetTxt);

    // add to that user
    (_user[currentUserName])->addTweet(createTweet); 

    newTweetLine->clear();

    // check whether there is any @ in new entered tweet
    vector<string> mentionedUser=createTweet->whoIsMentioned();

    // if new tweet @ any user, add this tweet into user's mention tweet
    for(map<string, User*>::iterator it=_user.begin();
	it!=_user.end();
	++it) {

      for(unsigned int i=0;i<mentionedUser.size();i++)  {
	string mentionedUserName = mentionedUser[i];
	if(mentionedUserName == it->first) {
	  _user[mentionedUserName]->addMentionTweet( createTweet);
	}
      }
    }

    /***************** new feature *********************/
    // first check whether the entered new tweet has a #
    Set<string> theHashSet = createTweet->getHashTags();
    // for all hash this new tweet contains:
    for(Set<string>::iterator it = theHashSet.begin();
	it != theHashSet.end();
	++it) {
      // if this hash already in the _hash map, just insert the tweet
      if( _hash.find(*it)!=_hash.end() )
	_hash[*it].push_back(createTweet);
      // if this has is not in the _hash map, create one and insert tweet
      else {
	vector<Tweet*> newHashTweet;
	newHashTweet.push_back(createTweet);
	_hash[*it] = newHashTweet;

      }
      
      // only push a tweet into _recentTweet when the tweet contains hashtags
      _recentTweet.push_back(createTweet);

    }

  }

}


// save information
void front::saveInformation()
{
  // get the inputted outfile's name
  string fileName = (ofileName->text()).toStdString();
  int theSize = fileName.size();
 
  // if not an empty file, create the file
  if(fileName!="") {

    // convert string filename to char* filename
    // because the qt makefile doesn't have std==c++11    
    char theFileName[theSize+1];

    for(int i=0;i<theSize;i++) 
      theFileName[i]=fileName[i];
    theFileName[theSize]='\0';
  
    ofstream ofile(theFileName);
 
    // output number of user
    ofile<<_user.size()<<endl;

    // output each user and his following user
    for(map<string, User*>::iterator it = _user.begin();
  	it!=_user.end();
  	++it) {
      // output user's name
      ofile<< (*it).first<<" ";
     
      // output all user's following user name
      Set<User*> theFollowing = ((*it).second)->following();
      for(Set<User*>::iterator iter = theFollowing.begin();
  	  iter!=theFollowing.end();
  	  ++iter) {
  	ofile<< (*iter)->name()<<" ";
      }
      ofile<<endl;
    }

    // output every user's tweet
    for(map<string, User*>::iterator it = _user.begin();
  	it!=_user.end();
  	++it) {
      vector<Tweet*> theTweet = (it->second)->tweets();
      for(vector<Tweet*>::iterator itera = theTweet.begin();
  	  itera!=theTweet.end();
  	  ++itera){
  	ofile<< *(*itera)<<endl;
      }
    }

    // close file
    ofile.close();

    ofileName->clear();
  }

}


void front::followOtherUser()
{
  string userName = userList->currentText().toStdString();
  string followingName = followingList->currentText().toStdString();
  Set<User*> theFollowing = (_user[userName])->following();

  // self follow
  if(userName== followingName) {
    sameUserFollowing();
  }

  // already follow
  else if(theFollowing.find(_user[followingName])!=theFollowing.end()) {
    alreadyFollowing();
  }

  else {
    (_user[userName])->addFollowing(_user[followingName]);
    successfullyFollowing();
  }

}					


// display a new trend topic window
void front::displayTrendTopic()
{

  // why doesn't work when user local variable on trendTopic?
  trendTopic* trendTopicWindow = new trendTopic(_hash, _recentTweet);
  trendTopicWindow->show();
}




//followings are  message box function
void front::sameUserFollowing()
{
  QMessageBox::information(this, tr("error"), tr("cannot follow yourself"));
}

void front::alreadyFollowing()
{
  QMessageBox::information(this, tr("error"), tr("already follow this user"));
}

void front::successfullyFollowing()
{
  QMessageBox::information(this, tr(""), tr("successfully following"));
}
