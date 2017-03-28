#ifndef GOAL_H
#define GOAL_H
#include "lav.h"
#include <map>
#include <iostream>
#include "operations.h"
using namespace std;

class Goal
{
public:
    Goal();

    int getId() const;
    void setId(int value);

    int getType() const;
    void setType(int value);

    int getScope() const;
    void setScope(int value);

    int getFinalGoal() const;
    void setFinalGoal(int value);

    int getLimit() const;
    void setLimit(int value);

    int getUnitsPerScope() const;
    void setUnitsPerScope(int value);

    int getCountOffline() const;
    void setCountOffline(int value);

    string getName() const;
    void setName(const string &value);

    string getUnit() const;
    void setUnit(const string &value);

    string getStartDate() const;
    void setStartDate(const string &value);

    string getColor() const;
    void setColor(const string &value);
    bool searchAndGet(string name, int type);
    void add();
    void clone(Goal &g);
    void update(Goal g, int type, int option);

protected:
    //Data Members
    int id, type, scope, finalGoal, limit, unitsPerScope, countOffline;
    string name, unit, startDate, color;
    LAV lav;
    Operations op;

    //Functions
    int loadId(string dict);
    string toString();



};

#endif // GOAL_H
