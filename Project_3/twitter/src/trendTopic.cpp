#include "../include/trendTopic.h"
#include "../include/msort.h"
#include <QGridLayout>
#include <QString>
#include <sstream>
#include <QListWidgetItem>
#include <QDateTime>


using namespace std;


trendTopic::trendTopic(map<string, vector<Tweet*> >& hash, vector<Tweet*>& recentTweet, QWidget* parent): QWidget(parent), _hash(hash), _recentTweet(recentTweet)
{

  hashList = new QComboBox;
  refreshBtn = new QPushButton("refresh");
  hashTweetArea = new QScrollArea;
  hashTweetArea->setWidgetResizable(true);
  hashTweetList = new QListWidget;

  all = new QRadioButton("All time");
  day = new QRadioButton("Past 24 hours");


  hashTweetArea->setWidget(hashTweetList);

  connect(refreshBtn, SIGNAL(clicked()), hashList, SLOT(clear()));
  connect(refreshBtn, SIGNAL(clicked()), this, SLOT(addHashList()));
  connect(hashList, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(displayHashTweet(const QString&)));


  QGridLayout* mainLayout = new QGridLayout;

  mainLayout->addWidget(hashList, 0, 0, 1, 3);
  mainLayout->addWidget(refreshBtn, 0, 3);
  mainLayout->addWidget(all, 1, 0, 1, 2);
  mainLayout->addWidget(day, 1, 2, 1, 2);
  mainLayout->addWidget(hashTweetArea, 2, 0, 2, 4);

  setLayout(mainLayout);

}


// this function is to add all hash strings into hash list
void trendTopic::addHashList()
{

  // create a vector that contains the hashAndTimes struct
  // the struct contains: 1.hash string 2.occurence of that hash
  vector<hashAndTimes> hashCount;

  // situation where user select all time
  if(all->isChecked()) {

    // add all hash tags struct
    for(map<string, vector<Tweet*> >::iterator it = _hash.begin();
	it != _hash.end();
	++it) {
      hashAndTimes oneHashStruct(it->first, (it->second).size() );
      hashCount.push_back(oneHashStruct);
    }

    // then sort the vector based on each hash's occurence
    hashCmp comp;
    mergeSort(hashCount, comp);

    // if it has less than 10 hash strings, list them all
    int size = hashCount.size();

    if(size<10) {
      for(int i=0;i<size;i++) {
	int occur = hashCount[i]._occurence;
	string stringOccur;
	stringstream ss;
	ss<<occur;
	ss>>stringOccur;

	string stdHashOnList = hashCount[i]._hashString +" "+ stringOccur;
	QString hashOnList = QString::fromStdString(stdHashOnList);
	hashList->addItem(hashOnList);
      }
    }

    // if it has more than 10 has strings, only list first 10
    else {
      for(int i=0;i<10;i++) {
	int occur = hashCount[i]._occurence;
	string stringOccur;
	stringstream ss;
	ss<<occur;
	ss>>stringOccur;

	string stdHashOnList = hashCount[i]._hashString + " "+stringOccur;
	QString hashOnList = QString::fromStdString(stdHashOnList);
	hashList->addItem(hashOnList);
      }
    }



  }


  // situation where user select past 24 hours
  if(day->isChecked()) {

    // if recentTweet is empty, do nothing
    if(_recentTweet.size()==0)
      return;

    // create a datetime object
    QDateTime* dt = new QDateTime;


    // startDT: [current date time - 1 day]
    DateTime* startDT = toMyDateTime(dt->currentDateTime().addDays(-1));


    // sort all tweets in _recentTweet vector from most recent to least recent if _recentTweet is not empty
    tweetCmp tweetComp;
    if(_recentTweet.size()) {
      mergeSort(_recentTweet, tweetComp);


      // delete all "old" tweet
      int i=_recentTweet.size()-1;

      while(  (i>=0)  &&  (*startDT>_recentTweet[i]->time()) ) {
	_recentTweet.pop_back();
	i--;
      }


      // get all hashtags from _recentTweet vector    
      for(unsigned int i=0;i<_recentTweet.size();i++) {
	Set<string> thisTweetHash = _recentTweet[i]->getHashTags();
	// for every hash in this tweet
	for(Set<string>::iterator it = thisTweetHash.begin();
	    it != thisTweetHash.end();
	    ++it) { 

	  // first check whether hashCount vector has that hash
	  unsigned int j=0;
	  for(;j<hashCount.size();j++) {
	    if( hashCount[j]._hashString==*it ) {
	      break;
	    }
	  }

	  // if already in the hashCount vector, increase the occurence by 1
	  if(j!=hashCount.size()) 
	    hashCount[j]._occurence +=1;
  
	  // if not in the hashCount vector, create a new struct and push back to hashCount
	  else {
	    hashAndTimes oneHashStruct( *it, 1);
	    hashCount.push_back(oneHashStruct);
	  }
	}
      }
      

      // now sort hashCount
      hashCmp hashComp;
      mergeSort(hashCount, hashComp);


      // if it has less than 10 hash, list them all
      if(hashCount.size()<10) {

	for(unsigned int i=0;i<hashCount.size();i++) {
	  int occur = hashCount[i]._occurence;
	  string stringOccur;
	  stringstream ss;
	  ss<<occur;
	  ss>>stringOccur;
	  
	  string stdHashOnList = hashCount[i]._hashString +" "+ stringOccur;
	  QString hashOnList = QString::fromStdString(stdHashOnList);
	  hashList->addItem(hashOnList);
	  
	}
      }
      
      // if it has more than 10 strings, only list first 10
      else {
	
	for(int i=0;i<10;i++) {
	  
	  int occur = hashCount[i]._occurence;
	  string stringOccur;
	  stringstream ss;
	  ss<<occur;
	  ss>>stringOccur;
	  
	  string stdHashOnList = hashCount[i]._hashString + " "+stringOccur;
	  QString hashOnList = QString::fromStdString(stdHashOnList);
	  hashList->addItem(hashOnList);
	  
	  
	}
      } 
    }
    
    displayHashTweet(hashList->currentText());
  }
}



void trendTopic::displayHashTweet(const QString& text)
{

  // clear scroll area
  hashTweetList->clear();

  string currentHash =text.toStdString();

  // this is for moment when all items in the list removed,(change->display) do nothing
  if(currentHash=="")
    return;

  currentHash.erase(currentHash.size()-2,2);

  if( all->isChecked()) {

    // first sort all tweets of each hash
    tweetCmp comp;
    for(map<string, vector<Tweet*> >::iterator it = _hash.begin();
	it != _hash.end();
	++it) {
      mergeSort( it->second, comp );
    }
   

    for(unsigned int i=0;i<(_hash[currentHash]).size();i++) {
      
      // use stringstream to get a whole tweet (including timestamep)
      stringstream ss;
      ss<<*((_hash[currentHash])[i]);
      string stdTweetTxt="";
      string word;
      while(ss>>word)
	stdTweetTxt+=word+" " ;
    
      // convert std::string to QString
      QString QTweetTxt = QString::fromStdString(stdTweetTxt);
      // create a list item
      QListWidgetItem* tweet = new QListWidgetItem(QTweetTxt);
    
      hashTweetList->addItem(tweet);
    }
  }


  if( day->isChecked() ) {

    // pick all tweets contains currentHash (24hours) into a new vector
    vector<Tweet*> currentHashTweet;

    for(unsigned int i=0;i<_recentTweet.size();i++) { 
      Set<string> thisTweetHash = _recentTweet[i]->getHashTags();

      // if this tweet contains currentHash, add tweet to currentHashTweet
      if( thisTweetHash.find( currentHash ) != thisTweetHash.end() )
  	currentHashTweet.push_back( _recentTweet[i] );
    }

    // sort currentHashTweet
    tweetCmp comp;
    mergeSort( currentHashTweet, comp );


    // output them on the scroll area
    for(unsigned int i=0;i<currentHashTweet.size();i++) {
      // use stringstream to get a whole tweet (including timestamep)
      stringstream ss;
      ss<<*(currentHashTweet[i]);
      string stdTweetTxt="";
      string word;
      while(ss>>word)
  	stdTweetTxt+=word+" " ;
    
      // convert std::string to QString
      QString QTweetTxt = QString::fromStdString(stdTweetTxt);
      // create a list item
      QListWidgetItem* tweet = new QListWidgetItem(QTweetTxt);
    
      hashTweetList->addItem(tweet);
    }
  }

}


DateTime* trendTopic::toMyDateTime(const QDateTime& dt)
{

  QString format = QString::fromStdString("yyyy-MM-dd hh:mm:ss");
  string dateTimeString = (dt.toString(format)).toStdString();

  // parse dateTimeString
  stringstream ss(dateTimeString);
  int theYear, theMonth, theDay, theHour, theMinute, theSecond;
  ss>>theYear; ss.ignore(1); ss>>theMonth; ss.ignore(1); ss>>theDay;ss.ignore(1); 
  ss>>theHour; ss.ignore(1); ss>>theMinute; ss.ignore(1); ss>>theSecond; ss.ignore(1);

      
  // create datetime object
  DateTime* myDateTime = new DateTime(theHour, theMinute, theSecond, theYear, theMonth, theDay);

  return myDateTime;
}
