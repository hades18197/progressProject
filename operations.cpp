#include "operations.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "goal.h"
#include <vector>
#include "Cons.h"
#include <QDate>
#include "filecontrol.h"
#include "goal.h"
using namespace std;

Operations::Operations()
{
}
///////////////////////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//////////////////////////////////////

/* Attention ! this function is not suitable for Course because the difference in members number
*   returns name and color of the goal
*/
vector<pair<string,string> > Operations::loadDetails(int type) {
    string fullPath;
    if(type == Cons::TYPE_LIMITED()) {
        fullPath = Cons::LGLIST();
    }
    else if(type == Cons::TYPE_UNLIMITED()) {
        fullPath = Cons::UGLIST();
    }
    ifstream f(fullPath.c_str());
    string line;
    vector<pair<string,string> > vec;
    while (getline(f,line)) {
        int counter = 0;
        string theName,part;
        stringstream ss(line);
        for(int i = 0; i < 9; i++) {
            getline(ss,part,'|');
            if(i == 1)
                theName = part;
        }
        getline(ss,part,'#');
        pair<string,string> p;
        p.first = theName;
        p.second = part;
        vec.push_back(p);
    }
    return vec;
}


/*
 *  this function is used to log the daily activity to /data/logs/...
 *  absName is the absolute name of the (goal/course) without the rest of the path
 *  or the extension
*/
void Operations::recordDay(string absName,int type,string date,int value) {

    //forming the full path of the log file
    string fullPath = getLogFilePath(absName,type);

    //opening the file for writing
    fstream f(fullPath.c_str(), ios::app | ios::out);
    QDate qd;
    f << date << " " << i2s(value,9) << endl;
    f.close();
    string ev = "adding day record to \"" + fullPath;
    ev += "\" : Successful";
    lav.logEvent(ev,Cons::EVENT_INFO());
}

void Operations::recordDay(string absName,int type,int value) {
    QDate qd;
    string date = qd.currentDate().toString("ddMMyyyy").toStdString();
    recordDay(absName,type,date,value);
}

// Converts an integer to a string
string Operations::i2s(int num) {
     stringstream ss;
     ss << num;
     return ss.str();
}

// overloading for the function i2s but returns a specific length string
string Operations::i2s(int num, int length) {
    string x = i2s(num);
    while(x.length() < length) {
        x += " ";
    }
    return x;
 }

 // Converts a string to an integer
int Operations::s2i(string str) {
     stringstream ss(str);
     int num;
     ss >> num;
     return num;
}

pair<int,string> Operations::findLog(string absName, int type, string date) {
    pair<int,string> wantedLine; // a pair contains the line number and the string of the wanted line or -1 if not found
    string fullPath = getLogFilePath(absName,type);

    ifstream f(fullPath.c_str());
    bool found = false; //flag -> true if found
    int lineNum = 0; // line counter
    string tmpline,dateString, unitsString;
    while (getline(f,tmpline)) {
        stringstream ss(tmpline);
        ss >> dateString >> unitsString;
        lineNum ++;
        if(dateString == date){
            string currentLine = dateString + " ";
            currentLine += unitsString;
            found = true;
            wantedLine.first = lineNum;
            wantedLine.second = currentLine;
            break;
        }
    }
    f.close();
    if(!found) wantedLine.first = -1;
    return wantedLine;
}

void Operations::updateLog(string absName, int type, string date, int newValue) {
    //getting lineNumber
    pair <int,string> p = findLog(absName,type,date);
    string fullPath = getLogFilePath(absName,type);
    //forming the eventLog string
    string ev = "updating date " + date;
    ev += " in log file \"" + fullPath;

    //checking if the record was found in the log
    if(p.first == -1) {
        ev += "\" : Failed ! reason : no such date found";
        lav.logEvent(ev,Cons::EVENT_ERROR());
    }else {
        int lineNum = p.first;
        string newLine = date + " ";
        newLine += i2s(newValue,9);
        fstream f(fullPath.c_str(),ios::in|ios::out);
        f.seekp((20 * (lineNum-1)),ios::beg);
        f << newLine << endl;
        f.close();
        ev += "\" : Successful";
        lav.logEvent(ev,Cons::EVENT_INFO());
    }
}


//gets dayUnits for a specific date
int Operations::getDayUnits(string absName, int type, string dayDate) {
    string fullPath = getLogFilePath(absName,type);
    pair<int,string> p = findLog(absName,type,dayDate);
    stringstream ss(p.second);
    string unitsString;
    ss >> unitsString >> unitsString;
    return s2i(unitsString);
}

// gets dayUnits for last day only (overloaded)
int Operations::getDayUnits(string absName, int type) {
    pair<int,string> p = getLastDay(absName, type);
    string lastDate = getLastDayDate(absName,type);
    return getDayUnits(absName,type,lastDate);
}


string Operations::getLogFilePath(string absName, int type) {
    //Forming the fullPath for the log
    string fullPath;
    if (type == Cons::TYPE_LIMITED())
            fullPath = Cons::LGLOGS();
    else if (type == Cons::TYPE_UNLIMITED())
            fullPath = Cons::UGLOGS();
    //space for adding Course else if (type == Cons::CLOGS())

    fullPath += "\\";
    fullPath += absName + ".logpf";
    return fullPath;
}

/*
 *  returns a pair contains LastDay lineNumber and the line itself
*/
pair<int,string> Operations::getLastDay(string absName, int type) {
    string fullPath = getLogFilePath(absName,type);
    pair<int,string> p;
    ifstream f(fullPath.c_str());
    int lineCount = 0;
    string line,lastLine;
    while (getline(f,line)) {
        lineCount ++;
        lastLine = line;
    }
    p.first = lineCount;
    p.second = lastLine;
    return p;
}

string Operations::getLastDayDate(string absName, int type) {
    pair<int,string> p = getLastDay(absName,type);
    stringstream ss(p.second);
    string lastDate;
    ss >> lastDate;
    return lastDate;
}

bool Operations::hasEmptyLog(string absName, int type) {
    string fullPath = getLogFilePath(absName,type);
    ifstream f(fullPath.c_str());
    f.seekg(0,ios::end);
    int x = f.tellg();
    f.close();
    return x == 0? true:false;
}

void Operations::syncLogs() {
    vector <pair<string,string> > limitedG = loadDetails(Cons::TYPE_LIMITED());
    vector <pair<string,string> > unlimitedG = loadDetails(Cons::TYPE_UNLIMITED());
    FileControl fc;
    cout << "I'm fucking working" << endl;
    for(int i = 0; i < limitedG.size(); i++) {
        string raw = limitedG[i].first;
        Goal *goal = new Goal();
        goal->searchAndGet(raw,Cons::TYPE_LIMITED());
        if(goal->getCountOffline() == Cons::COUNT_OFFLINE()) {
            cout << "Counting for this one : " << raw << endl;
            //preparing path of the log
            string fullPath = Cons::LGLOGS();
            fullPath += ("\\" + raw )+ ".logpf";
            cout << "Full Path = " << fullPath << endl;
            int x = fullPath.size();
            char s[x];
            copy(fullPath.begin(),fullPath.end(),s);

           if(!fc.fEx(s)) {
                ofstream cf(fullPath.c_str());
                cf.close();
                cout << "Created " << s << endl;
           }
            if(hasEmptyLog(raw,Cons::TYPE_LIMITED())) {
                Goal g;
                g.searchAndGet(raw,Cons::TYPE_LIMITED());
                recordDay(raw,Cons::TYPE_LIMITED(),g.getStartDate(),0);
            }
            QDate wantedDate = QDate::currentDate().addDays(-1);
            QDate logLastDate = QDate::fromString(QString::fromStdString(getLastDayDate(raw,Cons::TYPE_LIMITED())),"ddMMyyyy");
            while (logLastDate < wantedDate) {
                logLastDate = logLastDate.addDays(1);
                recordDay(raw,Cons::TYPE_LIMITED(),logLastDate.toString("ddMMyyyy").toStdString(),0);
            }
        }
        delete goal;
    }

    for(int i = 0; i < unlimitedG.size(); i++) {
        string raw = unlimitedG[i].first;
        Goal *goal = new Goal();
        goal->searchAndGet(raw,Cons::TYPE_UNLIMITED());
        if(goal->getCountOffline() == Cons::COUNT_OFFLINE()) {
            cout << "Counting for this one : " << raw << endl;
            //preparing path of the log
            string fullPath = Cons::UGLOGS();
            fullPath += ("\\" + raw )+ ".logpf";
            cout << "Full Path = " << fullPath << endl;
            int x = fullPath.size();
            char s[x];
            copy(fullPath.begin(),fullPath.end(),s);

           if(!fc.fEx(s)) {
                ofstream cf(fullPath.c_str());
                cf.close();
                cout << "Created " << s << endl;
           }
            if(hasEmptyLog(raw,Cons::TYPE_UNLIMITED())) {
                Goal g;
                g.searchAndGet(raw,Cons::TYPE_UNLIMITED());
                recordDay(raw,Cons::TYPE_UNLIMITED(),g.getStartDate(),0);
            }
            QDate wantedDate = QDate::currentDate().addDays(-1);
            QDate logLastDate = QDate::fromString(QString::fromStdString(getLastDayDate(raw,Cons::TYPE_UNLIMITED())),"ddMMyyyy");
            while (logLastDate < wantedDate) {
                logLastDate = logLastDate.addDays(1);
                recordDay(raw,Cons::TYPE_UNLIMITED(),logLastDate.toString("ddMMyyyy").toStdString(),0);
            }
        }
        delete goal;
}

}



//Don't need them at this stage

// Converts string to long long type (won't matter if string contains spaces at the end)
/*long long Operations::s2ll(string str) {
    stringstream ss(str);
    long long res;
    ss >> res;
    return res;
}
*/
/* Converts long long type to a (N-Bytes long) string
*  num is the long long number, and parameter n is the length of the string returned
*/
/*
string Operations::ll2NByteS(long long num,int n) {
    string theWanted;
    stringstream ss;
    ss << num;
    theWanted = ss.str();
    while(theWanted.length() < n) {
        theWanted += " ";
    }
    return theWanted;
}
*/
