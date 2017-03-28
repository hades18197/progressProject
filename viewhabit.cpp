#include "viewhabit.h"
#include "ui_viewhabit.h"
#include <QDate>
#include <QDateTime>
#include <map>
#include <iostream>
#include "Habit.h"
#include "HabitOp.h"
#include "LogOp.h"
#include "statistics.h"
using namespace std;

ViewHabit::ViewHabit(string selectedHabit,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewHabit)
{
    //setting and declaring variables
    HabitOp ho;
    LogOp lo;
    pair<int,Habit> selectedHabitSearchResult =  ho.searchAndGetHabit(selectedHabit);
    Habit selectedHabitObject = selectedHabitSearchResult.second;
    string rawDate = selectedHabitObject.getStartDate();
    habitFileName = selectedHabit;
    date = rawDate.substr(0,2);
    date += "/" + rawDate.substr(2,2);
    date += "/" + rawDate.substr(4,9);
    QString postfix;


    dateString = qdtime.currentDateTime().toString("ddMMyyyy").toStdString();


    //Setting up Gui Elements
    ui->setupUi(this);
    ui->questionLbl->setWordWrap(true);
    ui->currentDatelbl->setText(qdtime.currentDateTime().toString("dd/MM/yyyy"));
    ui->titleLbl->setText(QString::fromStdString(selectedHabitObject.getName()));
    ui->startDateLbl->setText(QString::fromStdString(date));
    if(selectedHabitObject.getQuestion().at(selectedHabitObject.getQuestion().length()-1) == '?')
        postfix = "";
    else
        postfix = " ?";
    ui->questionLbl->setText(QString::fromStdString(selectedHabitObject.getQuestion())+ postfix);


    //Functionality
    if(!lo.hasEmptyLog(habitFileName)) {
    string lastDateInHabit = lo.getLastDay(habitFileName);

    if (dateString == lastDateInHabit) {
        if(lo.getLastDayState(habitFileName) == "done")
            ui->yesB->setDisabled(true);
        else if (lo.getLastDayState(habitFileName) == "undone")
            ui->noB->setDisabled(true);
    }
    }
}

ViewHabit::~ViewHabit()
{
    delete ui;
}

void ViewHabit::on_yesB_clicked()
{
    LogOp lo;
    // if today is already recorded done
    if(dateString == lo.getLastDay(habitFileName)) {
        lo.modifyLog(habitFileName,dateString,1);
    }else {
         lo.addLog(habitFileName,dateString,1);
    }
    ui->yesB->setDisabled(true);
    ui->noB->setEnabled(true);
}

void ViewHabit::on_noB_clicked()
{
    //if today is already recorded undone
    LogOp lo;
    if(dateString == lo.getLastDay(habitFileName)) {
        lo.modifyLog(habitFileName,dateString,0);
    }else {
         lo.addLog(habitFileName,dateString,0);
    }
    ui->noB->setDisabled(true);
    ui->yesB->setEnabled(true);
}
