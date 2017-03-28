#ifndef EDITHABIT_H
#define EDITHABIT_H
#include <iostream>
#include <QWidget>
#include "Habit.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
using namespace std;

namespace Ui {
class editHabit;
}

class editHabit : public QWidget
{
    Q_OBJECT
    
public:
    explicit editHabit(QMainWindow *mw,string selectedHabitName, QWidget *parent = 0);
    ~editHabit();
    
private slots:
    void on_applyB_clicked();

    void on_cancelB_clicked();

    void on_closeB_clicked();

private:
    Ui::editHabit *ui;
    string selectedHabitName;
    Habit h;
    QMainWindow *mwd;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint mpos;
};

#endif // EDITHABIT_H
