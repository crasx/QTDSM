#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*QString *ip = new QString("74.91.124.246");
    qDebug()<<"K";
    QHLPing *test = new QHLPing(ip, 27015);
    */
    MainWindow w;
    w.show();



    return a.exec();
}
