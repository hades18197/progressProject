#ifndef HABIT_H
#define HABIT_H
#include <iostream>
#include <stdlib.h>
using namespace std;
class Habit
{
private:
    string name,question,description, startDate;
    int grace;
   // int daysUndone


public:
    Habit();
    void setName(string name);
    void setQuestion(string question);
    void setDescription(string description);
    void setGrace(int grace);
    void setStartDate(string startDate);
    string getName();
    string getDescription();
    string getQuestion();
    int getGrace();
    string getStartDate();
    //void setDaysUndone(int daysUndone);
    //int getDaysUndone();
};

#endif // HABIT_H
