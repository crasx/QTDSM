#include <QCoreApplication>
#include "QHLPing.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString *ip = new QString("192.168.1.195");
    QHLPing *test = new QHLPing(ip, 27015);
    qDebug() << test->ToString()->toLatin1();

    test->testPing();

    qDebug()<<"OK";

    return a.exec();
}
