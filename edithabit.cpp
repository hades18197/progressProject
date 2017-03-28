#include "edithabit.h"
#include "ui_edithabit.h"
#include "HabitOp.h"
#include <iostream>
#include <map>
#include "Habit.h"
#include <QString>
#include <QMainWindow>
#include "mainwindow.h"
#include "lav.h"
#include <QMouseEvent>
#include <QPoint>
using namespace std;

editHabit::editHabit(QMainWindow *mw,string selectedHabitName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editHabit)
{
    //set and declare vars
    this->selectedHabitName = selectedHabitName;
    HabitOp ho;
    pair<int,Habit> selectedHabitObject = ho.searchAndGetHabit(selectedHabitName);
    h = selectedHabitObject.second;
    mwd = mw;

    //Setting up Gui Elements
    ui->setupUi(this);
    ui->nameIn->setText(QString::fromStdString(h.getName()));
    ui->descriptionIn->setText(QString::fromStdString(h.getDescription()));
    ui->questionIn->setText(QString::fromStdString(h.getQuestion()));
    ui->graceSpinner->setValue(h.getGrace());
}

editHabit::~editHabit()
{
    delete ui;
}

void editHabit::on_applyB_clicked()
{
    LAV lav;
    if(lav.hasMinReq(ui->nameIn->text(),ui->questionIn->text(),this)) {
    h.setName(ui->nameIn->text().toStdString());
    h.setQuestion(ui->questionIn->text().toStdString());
    h.setDescription(ui->descriptionIn->text().toStdString());
    h.setGrace(ui->graceSpinner->value());
    HabitOp ho;
    h = lav.forceCorrectInput(h);
    ho.updateHabitFile(selectedHabitName,h,0);
     //refresh the list
     MainWindow *m = (MainWindow*) mwd;
     m->loadList();
     //close the window
     this->close();
    }
}

void editHabit::on_cancelB_clicked()
{
    this->close();
}

void editHabit::on_closeB_clicked()
{
    this->close();
}
////////////////////////////////* Move Functions *//////////////////////////////////


void editHabit::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void editHabit::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
