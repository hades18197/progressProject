#include "statistics.h"
#include "ui_statistics.h"
#include "ScoreCalc.h"
#include <iostream>
#include "Habit.h"
#include "HabitOp.h"
#include <QVector>
#include <QMouseEvent>
#include <algorithm>

using namespace std;

Statistics::Statistics(string habitName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Statistics)
{
    ui->setupUi(this);

    //////////////////////////////////* All You what want begins here */////////////////////////////
    if(sc.logToScore(habitName)) {
        cout << "hoss : log to score returned true" << endl;
    }
    ui->scope->setCurrentIndex(0);
    setupWeekScope(&sc);
    setValues = false;

    ////////////////////*Setting Labels with stats*///////////////////////////////////////////
    ui->bestIntervalLbl->setText(QString::number(sc.getBestInterval()));
    ui->worstInterval->setText(QString::number(sc.getWorstInterval()));
    ui->highestInMonthLbl->setText(QString::number(sc.getHighestInMonth()));
    ui->highestInWeekLbl->setText(QString::number(sc.getHighestInWeek()));
    ui->lowestInMonthLbl->setText(QString::number(sc.getLowestInMonth()));
    ui->lowestInWeekLbl->setText(QString::number(sc.getLowestInWeek()));
    ui->currentScoreLbl->setText(QString::number(sc.getCurrentScore()));
    ui->bestScoreLbl->setText(QString::number(sc.getHighestScore()));
    ui->worstScoreLbl->setText(QString::number(sc.getLowestScore()));
    ui->titleLbl->setText(QString::fromStdString(habitName));
    //////////////////////////////////////////////////////////////////////////////////////////


}

Statistics::~Statistics()
{
    delete ui;
}

void Statistics::on_closeB_clicked()
{
    this->close();
}

void Statistics::plottingFunction(int scope, ScoreCalc *sc) {

    double xMin = 0,xMax = 0,yMin = 0,yMax = 0;
    //xVec.clear();
    //yVec.clear();
    if(scope == 7 && sc->weekScores.size() < 7) {
        scope = sc->weekScores.size();
    }
    QString msg1 = "";

/////////////////////////////////* Adding values to the vectors *//////////////////////////////////
    if(setValues) {
            sort(sc->weekScores.begin(),sc->weekScores.end());
            sort(sc->monthScores.begin(),sc->monthScores.end());

        for(int i = 1; i <= scope; i++) {
            xVec.push_back(i);
            if(scope < 30) {
                yVec.push_back((double)sc->weekScores[i-1]);
                cout << "Scope < 30" << endl;
                cout << "The value added now is : " << sc->weekScores[i-1] << " as " << yVec[i-1] << endl;
                msg1 += QString::number(yVec[i-1]);
                msg1 += " ";

            }
            else if(scope == 30) {
                cout << "Scope == 30" <<endl;
                yVec.push_back((double)sc->monthScores[i-1]);
                cout << "The value added now is : " << sc->monthScores[i-1] << " as " << yVec[i-1] << endl;
            }
        }
    }

///////////////////////////////////////////////////////////////////////////////////////////////////

    ui->plotting->addGraph();
    ui->plotting->graph(0)->setData(xVec, yVec);

    // give the axes some labels:
    ui->plotting->xAxis->setLabel("Day");
    ui->plotting->yAxis->setLabel("Score");
    if (scope == 7) {
        QString msg = "";

        yMin = sc->getLowestInWeek();
        yMax = sc->getHighestInWeek();
        xMin = 1;
        xMax = 7;
    }
    else if (scope == 30) {
        yMin = sc->getLowestInMonth();
        yMax = sc->getHighestInMonth();
        xMin = 1;
        xMax = 30;
    }
    // set axes ranges, so we see all data:
    ui->plotting->xAxis->setRange(xMin, xMax);
    ui->plotting->yAxis->setRange(yMin, yMax);
    ui->plotting->replot();

}


//////////////////////////////* Moving the window */////////////////////////////

void Statistics::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

void Statistics::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

void Statistics::setupWeekScope(ScoreCalc *sc) {
    plottingFunction(7,sc);

    ///////////////////* Showing week values Labels *//////////////////////
    ui->highestIn30->setVisible(false);
    ui->lowestIn30->setVisible(false);
    ui->highestInMonthLbl->setVisible(false);
    ui->lowestInMonthLbl->setVisible(false);
    ui->highestIn7->setVisible(true);
    ui->lowestIn7->setVisible(true);
    ui->lowestInWeekLbl->setVisible(true);
    ui->highestInWeekLbl->setVisible(true);
}

void Statistics::setupMonthScope(ScoreCalc *sc){
    plottingFunction(30,sc);

    ////////////////////* Showing Month values Labels *//////////////////////
    ui->highestIn30->setVisible(true);
    ui->lowestIn30->setVisible(true);
    ui->highestInMonthLbl->setVisible(true);
    ui->lowestInMonthLbl->setVisible(true);
    ui->highestIn7->setVisible(false);
    ui->lowestIn7->setVisible(false);
    ui->lowestInWeekLbl->setVisible(false);
    ui->highestInWeekLbl->setVisible(false);
}

void Statistics::on_scope_currentIndexChanged(int index)
{
    if(index == 0) {
        setupWeekScope(&sc);
    }
    else if(index == 1) {
        setupMonthScope(&sc);
    }
}
