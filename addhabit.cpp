#include "addhabit.h"
#include "ui_addhabit.h"
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include "habit.h"
#include <HabitOp.h>
#include <QDateTime>
#include <mainwindow.h>
#include "lav.h"
#include <QMouseEvent>
#include <QPoint>
using namespace std;


addHabit::addHabit(QMainWindow *mw,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::addHabit)
{
    ui->setupUi(this);
    mwd = mw;

}

addHabit::~addHabit()
{
    delete ui;
}

void addHabit::on_addButton_clicked()
{
    //checking the input minimum requirement
    LAV lav;
    if(lav.hasMinReq(ui->nameIn->text(),ui->questionIn->text(),this)) {
    // Setting habit attrs //
    Habit h;
    h.setDescription(ui->descriptionIn->text().toStdString());
    h.setGrace(ui->graceSpinner->text().toInt(0,10));
    h.setQuestion(ui->questionIn->text().toStdString());
    h.setName(ui->nameIn->text().toStdString());
    QDateTime qdt;
    QString qs = qdt.currentDateTime().toString("ddMMyyyy");
    h.setStartDate(qs.toStdString());
    h = lav.forceCorrectInput(h);

    //adding the habit
    HabitOp ho;
    ho.addHabit(h);

   //refresh the list
    MainWindow *m = (MainWindow*) mwd;
    m->loadList();
    //close the window
    this->close();
    }
}

void addHabit::on_cancelButton_clicked()
{
    this->close();
}

void addHabit::on_closeB_clicked()
{
    this->close();
}

//////////////////////////////* Moving the window */////////////////////////////

void addHabit::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void addHabit::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}
