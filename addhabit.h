#ifndef ADDHABIT_H
#define ADDHABIT_H
#include <mainwindow.h>
#include <QMainWindow>
#include <QFrame>
#include <QMouseEvent>
#include <QPoint>

namespace Ui {
class addHabit;
}

class addHabit : public QFrame
{
    Q_OBJECT
    
public:
    explicit addHabit(QMainWindow *mw,QWidget *parent = 0);
    ~addHabit();

    
private slots:
    void on_addButton_clicked();

    void on_cancelButton_clicked();
    void on_closeB_clicked();

signals:

private:
    Ui::addHabit *ui;
    QMainWindow *mwd;
    QPoint mpos;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // ADDHABIT_H

