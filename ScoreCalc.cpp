#include "ScoreCalc.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

ScoreCalc::ScoreCalc()
{
    highestScore = -9999999, lowestScore = 9999999, bestInterval = 0, worstInterval = 0, highestInWeek = -9999999,
    lowestInWeek = 9999999, highestInMonth = -9999999, lowestInMonth = 9999999;
}


//////////////////////////////////////////* Start of Setters *////////////////////////////////////////

void ScoreCalc::setHighestScore(int highestScore) {
        this->highestScore = highestScore;
}

void ScoreCalc::setLowestScore(int lowestScore) {
        this->lowestScore = lowestScore;
}

void ScoreCalc::setBestInterval(int bestInterval) {
        this->bestInterval = bestInterval;
}

void ScoreCalc::setWorstInterval(int worstInterval) {
        this->worstInterval = worstInterval;
}

void ScoreCalc::setHighestInWeek(int highestInWeek) {
        this->highestInWeek = highestInWeek;
}

void ScoreCalc::setLowestInWeek(int lowestInWeek) {
        this->lowestInWeek = lowestInWeek;
}

void ScoreCalc::setHighestInMonth (int highestInMonth) {
        this->highestInMonth = highestInMonth;
}

void ScoreCalc::setLowestInMonth(int lowestInMonth) {
        this->lowestInMonth = lowestInMonth;
}

void ScoreCalc::setLastScanDate(string lastScanDate) {
        this->lastScanDate = lastScanDate;
}

void ScoreCalc::setCurrentScore(int currentScore) {
    this->currentScore = currentScore;
}
///////////////////////////////////* End of Setters *////////////////////////////////////////////////

///////////////////////////////////* Start of Getters *///////////////////////////////////////////////

int ScoreCalc::getLowestInMonth() {
    return lowestInMonth;
}

int ScoreCalc::getHighestInMonth() {
    return highestInMonth;
}

int ScoreCalc::getLowestInWeek() {
    return lowestInWeek;
}

int ScoreCalc::getHighestInWeek() {
    return highestInWeek;
}

int ScoreCalc::getWorstInterval() {
    return worstInterval;
}

int ScoreCalc::getBestInterval() {
    return bestInterval;
}

int ScoreCalc::getLowestScore() {
    return lowestScore;
}

int ScoreCalc::getHighestScore() {
    return highestScore;
}

string ScoreCalc::getLastScanDate() {
    return lastScanDate;
}

int ScoreCalc::getCurrentScore() {
    return currentScore;
}

//////////////////////////////////////////////* End of Getters */////////////////////////////////////////////
/*
*   This function returns a true if the file is not empty and the stack contains some scores values
*   else it returns false
*/
bool ScoreCalc::logToScore(string habitFile) {
    bool notEmptyFile = false;
    string fileName = "logs\\" + habitFile, line;
    cout << "Checking file : " << fileName << endl;
    ifstream f(fileName.c_str());
    bool doing = false;
    int score = 0,  doingInterval = 0, nondoingInterval = 0;
    stack<int> allScores;
int xxx = 0 ;
    while(getline(f,line)) {
        notEmptyFile = true;
        if (line[9] == 'd') {
            doing = true;
            doingInterval += 1;
            score +=10;
        }
       else if(line[9] == 'u') {
            doing = false;
            nondoingInterval += 1;
            score -= 7;
       }
       // Setting bestInterval
       if(!doing) {
            if(doingInterval > getBestInterval())
                    setBestInterval(doingInterval);
            doingInterval = 0;
       }
       // Setting worstInterval
       else {
            if(nondoingInterval > getWorstInterval())
                    setWorstInterval(nondoingInterval);
            nondoingInterval = 0;
       }
       // Adding score to the scores stack
       allScores.push(score);
       // Setting highestScore
       if(score > getHighestScore())
                setHighestScore(score);
       // Setting lowestScore
       if(score < getLowestScore())
                setLowestScore(score);

    }
    // Setting currentScore
    setCurrentScore(score);
    cout << "the stack now contains " << allScores.size() << " Elems "<<endl;
    if(!allScores.empty()) {
        cout << "Passed allScores Empty test " << endl;
        if(allScores.size() >= 30) {
            vector<int> lastMonthScores, lastWeekScores;
            int j = 0;
            for(int i = 0; i < 30; i++) {
                int xscore = allScores.top();
                lastMonthScores.push_back(xscore);
                monthScores.push_back(xscore);
                if(j < 7) {
                    lastWeekScores.push_back(xscore);
                    weekScores.push_back(xscore);
                    j++;
                }
                allScores.pop();
            }
            //Sorting scores in ascending order
            sort(lastMonthScores.begin(),lastMonthScores.end());
            sort(lastWeekScores.begin(),lastWeekScores.end());

            setHighestInMonth(*lastMonthScores.rbegin());
            setLowestInMonth(*lastMonthScores.begin());
            setHighestInWeek(*lastWeekScores.rbegin());
            setLowestInWeek(*lastWeekScores.begin());
        }
        else {
            vector<int> lastWeekScores;
            int scoresNumber = allScores.size();
            for(int i = 0; i < scoresNumber; i++) {
                int xscore = allScores.top();
                lastWeekScores.push_back(xscore);
                weekScores.push_back(xscore);
                allScores.pop();
            }
            sort(lastWeekScores.begin(),lastWeekScores.end());
            setLowestInMonth(*lastWeekScores.begin());
            setHighestInMonth(*lastWeekScores.rbegin());
            setLowestInWeek(*lastWeekScores.begin());
            setHighestInWeek(*lastWeekScores.rbegin());
        }
    }

    return notEmptyFile;
}

vector<pair<int,int> > ScoreCalc::getPlottingData(string habitFile, int duration) {

}
