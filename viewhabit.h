#ifndef VIEWHABIT_H
#define VIEWHABIT_H
#include <string>
#include <iostream>
#include <QWidget>
#include <QDateTime>
using namespace std;

namespace Ui {
class ViewHabit;
}

class ViewHabit : public QWidget
{
    Q_OBJECT
    
public:
    explicit ViewHabit(string selectedHabit,QWidget *parent = 0);
    ~ViewHabit();
    
private slots:
    void on_yesB_clicked();

    void on_noB_clicked();

private:
    Ui::ViewHabit *ui;
    string habitFileName, date, dateString;
    QDateTime qdtime;
};

#endif // VIEWHABIT_H
