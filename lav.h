#ifndef LAV_H
#define LAV_H
#include <QString>
#include <iostream>
#include <QWidget>
#include <QFrame>
#include "Habit.h"
using namespace std;

class LAV
{
public:
    LAV();
    bool hasMinReq(QString name, QString question, QWidget *parent);
    Habit forceCorrectInput(Habit h);
    void logEvent(string event, int type);
    bool emptyFile(string fileFullPath);
};

#endif // LAV_H
