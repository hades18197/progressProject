#include "lav.h"
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QWidget>
#include <QFrame>
#include "Habit.h"
#include <string>
#include "Cons.h"
#include <QDateTime>
#include <fstream>
using namespace std;

LAV::LAV() {

}

bool LAV::hasMinReq(QString name, QString question, QWidget *parent) {
    bool res = true;
    if(name.isEmpty()) {
        QMessageBox::critical(parent,"Error", "The Field Name is required and can't be left Empty !");
        res = false;
    }
    else if(question.isEmpty()) {
        QMessageBox::critical(parent,"Error", "The Field Question is required and can't be left Empty !");
        res = false;
    }
    return res;
}

Habit LAV::forceCorrectInput(Habit h) {
    string s[3];
    s[0] = h.getName();
    s[1] = h.getQuestion();
    s[2] = h.getQuestion();
    string tmp = "";
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < s[k].length(); i++) {
            if(s[k][i] != '*') {
                tmp += s[k][i];
            }
        }
        if(k == 0)
            h.setName(tmp);
        else if(k == 1)
            h.setQuestion(tmp);
        else if(k == 2)
            h.setDescription(tmp);
        tmp = "";
    }
    return h;
}

void LAV::logEvent(string event, int type) {
    QDateTime qdt;
    string typeString;
    if(type == Cons::EVENT_INFO()) typeString = "Info";
    else if(type == Cons::EVENT_ERROR()) typeString = "Error";
    fstream f(Cons::EXEC_LOG(),ios::app | ios::out);
    f << "[ " << qdt.currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString() << " ] (" << typeString << ") : ";
    f << event << endl;
}

bool LAV::emptyFile(string fileFullPath) {
    bool em = false;
    ifstream f(fileFullPath.c_str());
    f.seekg(0,ios::end);
    if (f.tellg() == 0)
        em = true;
    f.close();
    return em;
}
