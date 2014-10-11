// QTHLM
// Copyright (C) Matthew Ramir. aka "crasx" 2014
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include <QtNetwork/QUdpSocket>
#include <QObject>
#include "QHLPingStructs.h"


#ifndef QHLPING_H
#define QHLPING_H


class QHLPing : public QObject
{
    Q_OBJECT

public:
    QHLPing();
    QHLPing(QString * ip, quint16 port);
    QString* ToString();

    void testPing();

private slots:
    void processPendingDatagrams();


private:
    void constructSocket();
    void processPing(const char *data, int len);


    QHostAddress *hostAddress;
    QUdpSocket* udpSocket;
    QString* ipAddress;
    quint16 port;

};


#endif // QHLPING_H
