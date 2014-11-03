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
#include <QMutex>
#include <QTimer>
#include <QElapsedTimer>
#include "QHLPingStructs.h"
#include "QBasePing.h"

#ifndef QHLPING_H
#define QHLPING_H


class QHLPing : public QBasePing
{
    Q_OBJECT

public:
    QHLPing();
    QHLPing(QString * ip, quint16 port);

    void executeStatusPing();
    void executePlayersPing();

    QString* ToString();
    float getAveragePing();


private slots:
    void processPendingDatagrams();

    void timerCallback();


private:

    void constructSocket();
    void constructPingTimer();

    void processPing(const char *data, int len);

    void pingChallengeCallback(const char *data);

    QMutex playerReplyMutex;


    QMutex infoReplyMutex;

    QMutex pingMutex;
    QElapsedTimer *pingTimer;

    HL_INFO_REPLY *infoReply;
    HL_PLAYER_INFO playerInfo[128];

    QHostAddress *hostAddress;
    QUdpSocket* udpSocket;
    QString* ipAddress;
    QTimer* timer;
    quint16 port;

    quint64 totalPingTime;
    int totalPingCount;
    int lastPingTime;

};


#endif // QHLPING_H
