#ifndef HABITOP_H
#define HABITOP_H
#include <map>
#include <iostream>
#include "Habit.h"
#include <vector>
using namespace std;

class HabitOp
{
    public:
        HabitOp();
        const string dict= "dict";
        void addHabit(Habit h);
        pair<int,Habit> searchAndGetHabit(string habitName);
        void updateHabitFile(string habitName, Habit newObject, int option);
        void addHabitLine(Habit h, fstream f);
        vector<string> loadHabitNames();
        bool dictIsEmpty();
    protected:
    private:
};

#endif // HABITOP_H
