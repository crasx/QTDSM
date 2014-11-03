#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QList>

#include "pingers/includeAll.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    private slots:
    void updateServerTable();
    void on_addServerButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *updateTimer;

    QList<QBasePing *> servers;

    void addServer();


};

#endif // MAINWINDOW_H
