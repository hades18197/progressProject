#ifndef LogOp_H
#define LogOp_H
#include <iostream>
#include <map>

using namespace std;

class LogOp
{
    public:
        LogOp();
        void addLog(string habitFile,string date,int state);
        void modifyLog(string habitFile,string date, int newState);
        pair<int,string> findLog(string habitFile,string date);
        void displayLogs(string habitFile);
        struct line {
            char date[9];
            char state[7];
        };
        pair<int,int> allDaysCount (string habitFile);
        string getLastDay(string habitFile);
        string getLastDayState(string habitFile);
        bool hasEmptyLog(string habitFile);

    protected:
    private:
};

#endif // LogOp_H
