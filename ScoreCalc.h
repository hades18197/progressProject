#ifndef SCORECALC_H
#define SCORECALC_H
#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

class ScoreCalc
{
    public:
        ScoreCalc();

        //Setter Functions
        void setHighestScore(int highestScore);
        void setLowestScore(int lowestScore);
        void setBestInterval(int bestInterval);
        void setWorstInterval(int worstInterval);
        void setHighestInWeek(int highestInWeek);
        void setLowestInWeek(int lowestInWeek);
        void setHighestInMonth (int highestInMonth);
        void setLowestInMonth(int lowestInMonth);
        void setLastScanDate(string lastScanDate);
        void setCurrentScore(int currentScore);

        // Getter Functions
        int getLowestInMonth();
        int getHighestInMonth();
        int getLowestInWeek();
        int getHighestInWeek();
        int getWorstInterval();
        int getBestInterval();
        int getLowestScore();
        int getHighestScore();
        int getCurrentScore();
        string getLastScanDate();

        // Functions
        bool logToScore(string habitFile);
        vector<pair<int,int> > getPlottingData(string habitFile, int duration);
        vector<int> monthScores, weekScores;
    protected:
    private:
        /*
        *   The score struct is added to the score file as one line with the following formula :
        *   Name*highestScore*lowestScore*bestInterval*worstInterval*highestInWeek*lowestInWeek*highestInMonth*lowestInMonth#
        *   And the default values for those numerical values are :
        *   Name*-9999999*9999999*0*0*-9999999*9999999*-9999999*9999999#
        */
         int highestScore, lowestScore, //global : highest and lowest
            bestInterval, worstInterval, //global : most consequence done, most consequence undone
            highestInWeek, lowestInWeek, //In the last week Duration: highest and lowest
            highestInMonth, lowestInMonth, //In the last month Duration : highest and lowest
            currentScore; //It's obvious I think
            vector<pair<int,int> > weekValues;
            vector<pair<int,int> > monthValues;
        string lastScanDate;

        // I can't even remember why I added these

};

#endif // SCORECLAC_H
