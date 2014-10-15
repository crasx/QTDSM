#include <QCoreApplication>
#include "QHLPing.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString *ip = new QString("74.91.113.10");
    QHLPing *test = new QHLPing(ip, 27015);

    test->executeStatusPing();
    test->executePlayersPing();


    return a.exec();
}
