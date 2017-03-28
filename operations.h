#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <iostream>
#include <map>
#include <vector>
#include "lav.h"
using namespace std;

class Operations
{
public:
    Operations();
    vector<pair<string,string> > loadDetails(int type);

    void recordDay(string absName,int type,string date,int value);
    void recordDay(string absName, int type, int value);

    string i2s(int num);
    string i2s(int num, int length);

    int s2i(string str);

    pair<int,string> findLog(string absName, int type, string date);

    void updateLog(string absName, int type, string date, int newValue);

    pair<int,string> getLastDay(string absName, int type);

    string getLastDayDate (string absName, int type);

    int getDayUnits(string absName, int type, string dayDate);
    int getDayUnits(string absName, int type);

    string getLogFilePath(string absName, int type);

    bool hasEmptyLog(string absName, int type);

    void syncLogs();
    // Don't need them at this stage
    //long long s2ll(string str);
    //string ll2NByteS(long long num,int n);
private :
    LAV lav;
};

#endif // OPERATIONS_H
