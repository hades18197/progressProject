#include "LogOp.h"
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
using namespace std;

LogOp::LogOp()
{
    mkdir ("logs");
}

void LogOp::displayLogs(string habitFile) {
    string fileName = "logs\\" + habitFile;
    ifstream f(fileName.c_str());
    line l;
    string str;
    while (getline(f,str)) {
       cout << str << endl;
    }
    f.close();
}

string translateState(int numericalState) {
    if(numericalState == 0) return "undone ";
    else if(numericalState == 1) return "done   ";
    else if (numericalState == 2) return "delayed";
}

void LogOp::addLog(string habitFile,string date,int state) {
    string stateString = translateState(state);
    string fileName = "logs\\" + habitFile;
    line l;
    copy(date.begin(), date.end(),l.date);
    copy(stateString.begin(),stateString.end(),l.state);
    fstream f(fileName.c_str(),ios::app | ios::out);
    f << date << " " << stateString;
    f << endl;
    f.close();
}

/* Searches the log file using date and returns a pair contains the record and it's line number in file
*  wantedLine : a pair contains integer first->(line number ) and string second->(line content)
*  if the line not found the value first from the pair will be -1
*/

pair<int,string> LogOp::findLog(string habitFile, string date) {
    pair<int,string> wantedLine; // a pair contains the line number and the string of the wanted line or -1 if not found
    string fileName = "logs\\" + habitFile;
    ifstream f(fileName.c_str());
    bool found = false; //flag -> true if found
    int lineNum = 0; // line counter
    char c[8];
    copy(date.begin(),date.end(),c);
    line l;
    string tmpline,dateInString;
    while (getline(f,tmpline)) {
        stringstream ss(tmpline);
        ss >> dateInString >> l.state;
        lineNum ++;
        if(dateInString == date){
            string currentLine = dateInString + " ";
            currentLine += l.state;
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

void LogOp::modifyLog(string habitFile, string date, int newState) {
    string fileName = "logs\\" + habitFile;
    fstream f(fileName.c_str(), ios::out | ios::in); //opening file for both reading and writing
    pair<int,string> thatDay = findLog(habitFile,date); //result of searching the wanted file
    date += " ";
    string newStateString = translateState(newState);
    string dateInFile;

    while(getline(f,dateInFile)) {
        string dif = dateInFile.substr(0,9);
        if(date == dif) {
                f.seekp(18 *(thatDay.first -1),ios::beg);
                f << dif << newStateString;
                f << endl;
                break;
        }
    }
    f.close();
}


/*
*   The Function Iterates the log file and counts days
*   returns the pair daysCount with number of done days as first
*   as you guessed :D , the number of undone is the second
*/
pair<int,int> LogOp::allDaysCount (string habitFile) {
    string fileName = "logs\\" + habitFile, line;
    pair<int,int> daysCount;
    daysCount.first = 0;
    daysCount.second = 0;
    ifstream f(fileName.c_str());
    while(getline(f,line)) {
        if (line[9] == 'd')
            daysCount.first ++;
        else if(line[9] == 'u')
            daysCount.second ++;
    }
    return daysCount;
}

string LogOp::getLastDay(string habitFile) {
    string fileName = "logs\\" + habitFile, line;
    ifstream f(fileName.c_str());
    f.seekg(-18,ios::end);
    string lastDate;
    f >> lastDate;
    f.close();
    return lastDate;
}

string LogOp::getLastDayState(string habitFile) {
    string fileName = "logs\\" + habitFile, line;
    ifstream f(fileName.c_str());
    f.seekg(-18,ios::end);
    string lastState;
    f >> lastState >> lastState;
    f.close();
    return lastState;
}

bool LogOp::hasEmptyLog(string habitFile) {
    string fileName = "logs\\" + habitFile;
    ifstream f(fileName.c_str());
    f.seekg(0,ios::end);
    return f.tellg() == 0 ? true:false;
}
