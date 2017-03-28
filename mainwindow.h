#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "addhabit.h"
#include <QMainWindow>
#include <QPushButton>
#include <QPoint>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     void loadList();
     void addListItem(QString itemName);

private slots:
    void on_addButton_clicked();

    void on_modifyButton_clicked();

    void on_viewButton_clicked();

    void on_deleteButton_clicked();

    void on_closeB_clicked();

    void on_minimizeB_clicked();

    void on_statisticsB_clicked();

    void on_addButton_pressed();

    void on_addButton_released();

    void on_modifyButton_pressed();

    void on_modifyButton_released();

    void on_deleteButton_pressed();

    void on_deleteButton_released();

    void on_aboutB_clicked();

private:
    Ui::MainWindow *ui;
    QPoint mpos;
    bool noItemSelected();
    bool noListItems();
    void buttonPressedAnimation (QPushButton *b);
    void buttonReleasedAnimation (QPushButton *b);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool hasMinReq(QString name, QString question);
};

#endif // MAINWINDOW_H
