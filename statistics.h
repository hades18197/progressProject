#ifndef STATISTICS_H
#define STATISTICS_H
#include <iostream>
#include <QWidget>
#include <QMouseEvent>
#include "ScoreCalc.h"
#include <QPoint>
using namespace std;

namespace Ui {
class Statistics;
}

class Statistics : public QWidget
{
    Q_OBJECT
    
public:
    explicit Statistics(string habitName,QWidget *parent = 0);
    ~Statistics();
    
private slots:
    void on_closeB_clicked();

    void on_scope_currentIndexChanged(int index);

private:
    Ui::Statistics *ui;
    QPoint mpos;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void plottingFunction(int scope, ScoreCalc* sc);
    void setupMonthScope(ScoreCalc *sc);
    void setupWeekScope(ScoreCalc *sc);
    QVector<double> xVec, yVec;
    bool setValues = true;
    ScoreCalc sc;
};

#endif // STATISTICS_H
