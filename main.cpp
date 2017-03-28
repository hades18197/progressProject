#include "mainwindow.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <string.h>
#include "ScoreCalc.h"
#include "Habit.h"
#include "HabitOp.h"
#include "LogOp.h"
#include "filecontrol.h"
#include <vector>
#include <QColor>
#include "Cons.h"
#include "goal.h"
#include <QDate>
#include <QString>
#include "operations.h"
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
   /* QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    w.show();
    return a.exec();*/
   /* QDate qd;
    FileControl fc;
    fc.checkAndCreate();
    Goal g;
    g.setName("my only goal");
    g.setType(Cons::TYPE_LIMITED());
    g.setId(1);
    g.setColor("125 128 19 255");
    g.setCountOffline(Cons::COUNT_OFFLINE());
    g.setFinalGoal(20);
    g.setLimit(10);
    g.setUnit("rep");
    g.setUnitsPerScope(2);
    g.setScope(Cons::SCOPE_DAY());
    g.setStartDate(qd.currentDate().toString("ddMMyyyy").toStdString());
    Goal c,x;
    c.clone(g);
    x.clone(g);
    c.setName("useless goal");
    x.setName("usefull goal");
    g.add();
    c.add();
    x.add();
    g.update(c,Cons::TYPE_LIMITED(),Cons::OPTION_DELETE());
    */
    Operations op;
//   op.recordDay("usefull goal",Cons::TYPE_LIMITED(),80);
    //pair<int,string> p = op.findLog("useless goal",Cons::TYPE_LIMITED(),"24032017");
   // cout << p.first << endl;
    //op.updateLog("useless goal",Cons::TYPE_LIMITED(),"23032017",1);
   // cout << op.getDayUnits("useless goal",Cons::TYPE_LIMITED(),"24032017") + 1 << endl;
   // QDate mydate = QDate::fromString("01122013","ddMMyyyy");
   //cout << mydate.toString("dd/MM/yyyy").toStdString() << endl;
   // op.syncLogs();
    op.syncLogs();
}
