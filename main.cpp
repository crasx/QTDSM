#include <QCoreApplication>
#include "QHLPing.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString *ip = new QString("216.52.148.113");
    QHLPing *test = new QHLPing(ip, 27015);

    test->testPing();


    return a.exec();
}
