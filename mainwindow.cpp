#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addhabit.h"
#include <QtWidgets/QWidget>
#include <QtCore>
#include <QString>
#include <fstream>
#include <iostream>
#include <sstream>
#include "HabitOp.h"
#include "Habit.h"
#include "LogOp.h"
#include <viewhabit.h>
#include "edithabit.h"
#include <QMessageBox>
#include "statistics.h"
#include <stdio.h>
#include <direct.h>
#include <QList>
#include <QMouseEvent>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    loadList();
    ui->list->item(0)->setSelected(true);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addButton_clicked() {
     noItemSelected();
    addHabit *ahb;
    ahb = new addHabit(this);
    connect(ahb,SIGNAL(on_addButton_clicked()),this,SLOT(loadTheListAgain()));
    ahb->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ahb->show();
    noItemSelected();
}

void MainWindow::loadList() {
    ui->list->clear();
    try{
    fstream f;
    f.open("dict", ios::in);
    string line = "",lo="";
    while(getline(f,line)){
        stringstream ss(line);
        getline(ss,lo,'*');
        QString l = QString::fromStdString(lo);
        ui->list->addItem(l);
    }
    }catch(EXCEPINFO){}
}


void MainWindow::on_modifyButton_clicked()
{
    if(noItemSelected() || noListItems());
    else{
        editHabit *eh;
        eh = new editHabit(this,ui->list->selectedItems().at(0)->text().toStdString(),this);
        eh->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        eh->show();
    }
}


void MainWindow::addListItem(QString itemName) {
    ui->list->addItem(itemName);
}

void MainWindow::on_viewButton_clicked()
{
    if(noItemSelected() || noListItems());
    else{
        ViewHabit *vh;
        vh = new ViewHabit(ui->list->selectedItems().at(0)->text().toStdString());
        vh->show();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    if(noItemSelected() || noListItems());
    else{
        string delHabit = ui->list->selectedItems().at(0)->text().toStdString();
        string msgTxt = "Are you Sure to delete the habit \"";
        msgTxt += delHabit + "\" ?";
        QString msgFinalTxt = QString::fromStdString(msgTxt);
         QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Attention", msgFinalTxt,
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
            qDebug() << "Yes was clicked";
            HabitOp ho;
            Habit nothing;
            ho.updateHabitFile(delHabit,nothing,1);
            string command = "logs\\";
            command += delHabit;
            remove(command.c_str());
            loadList();
          } else {
            qDebug() << "Yes was *not* clicked";
          }
      }
}

void MainWindow::on_closeB_clicked()
{
    this->close();
}

void MainWindow::on_minimizeB_clicked()
{
    this->setWindowState(Qt::WindowMinimized);
}

void MainWindow::on_statisticsB_clicked()
{
    if(noItemSelected() || noListItems());
    else{
        string habitName = ui->list->selectedItems().at(0)->text().toStdString();
        LogOp lo;
        if(lo.hasEmptyLog(habitName)) {
            string msgString = "Habit " + habitName + " has no statistics yet . ";
            QMessageBox::information(this,"Info", msgString.c_str());
        }else {
            Statistics *st;
            st = new Statistics(habitName);
            st->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
            st->show();
        }
    }

}

bool MainWindow::noItemSelected() {
    QList<QListWidgetItem *> ql = ui->list->selectedItems();
    if(ql.empty()) {
        QMessageBox::critical(this,"Error","No Habit Selected !");
        return true;
      }
    else
        return false;
}

bool MainWindow::noListItems() {
    if (ui->list->count() <= 0) {
        QMessageBox::information(this,"Attention", "Your Habit list is empty, add habits first .");
        return true;
    }
    else
        return false;
}

//////////////////////////////////////* Animation *////////////////////////////////////

void MainWindow::on_addButton_pressed()
{
    buttonPressedAnimation(ui->addButton);
}

void MainWindow::on_addButton_released()
{
    buttonReleasedAnimation(ui->addButton);
}

void MainWindow::on_modifyButton_pressed()
{
    buttonPressedAnimation(ui->modifyButton);
}

void MainWindow::on_modifyButton_released()
{
    buttonReleasedAnimation(ui->modifyButton);
}

void MainWindow::on_deleteButton_pressed()
{
    buttonPressedAnimation(ui->deleteButton);
}

void MainWindow::on_deleteButton_released()
{
    buttonReleasedAnimation(ui->deleteButton);
}

void MainWindow::buttonPressedAnimation (QPushButton *b) {
    int width, height, x, y;
    width = b->geometry().width();
    height = b->geometry().height();
    x = b->geometry().x();
    y = b->geometry().y();
    b->setGeometry(x,y-5,width+20,height);
    QSize oldSize = b->iconSize();
    QSize newSize(oldSize.width() + 10,oldSize.height() + 10);
    b->setIconSize(newSize);
}

void MainWindow::buttonReleasedAnimation (QPushButton *b) {
    int width, height, x, y;
    width = b->geometry().width();
    height = b->geometry().height();
    x = b->geometry().x();
    y = b->geometry().y();
    b->setGeometry(x,y+5,width-20,height);
    QSize oldSize = b->iconSize();
    QSize newSize(oldSize.width() - 10,oldSize.height() - 10);
    b->setIconSize(newSize);
}

//////////////////////////////* Moving the window */////////////////////////////

void MainWindow::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void MainWindow::on_aboutB_clicked() {

}
