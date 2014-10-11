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


#include "QHLPing.h"
#define QHLPINGDEBUG 1

QHLPing::QHLPing(QString *ip, quint16 port)
{
    this->ipAddress = ip;
    this->port = port;
    this->constructSocket();
}



QString *QHLPing::ToString()
{
    QString *ret=new QString();

    QTextStream(ret) << ipAddress->toLatin1()<< " " <<port;
    return ret;

}

/**
 * @brief QHLPing::testPing
 * Run a test info ping
 */
void QHLPing::testPing()
{

    QByteArray *datagram = new QByteArray();
    datagram->insert(0, "\xFF\xFF\xFF\xFFTSource Engine Query");
    datagram->append('\0');

    if(QHLPINGDEBUG)
        qDebug()<<"S" << datagram->length()<<datagram->constData();

    udpSocket->writeDatagram(*datagram, *hostAddress, port);

    udpSocket->waitForReadyRead(-1);


}

/**
 * @brief QHLPing::processPendingDatagrams
 * Data recieved callback
 */
void QHLPing::processPendingDatagrams()
{
    QByteArray datagram;

    qDebug()<<"RECV";

    do {
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
    } while (udpSocket->hasPendingDatagrams());


    QString asd(datagram);
    qDebug()<<asd.toLatin1()<<datagram.count();


    processPing(datagram.constData(), datagram.count());



}

/**
 * @brief QHLPing::constructSocket
 * Creates new socket and adds listeners
 */
void QHLPing::constructSocket()
{
    hostAddress = new QHostAddress(*this->ipAddress);

    udpSocket = new QUdpSocket();
    //    udpSocket->connectToHost(*hostAddress, port); //bind to our host

    //add event listener
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));



}

/**
 * @brief QHLPing::processPing
 * Processes ping responses based on spec at https://developer.valvesoftware.com/wiki/Server_queries
 * @param data
 * @param len
 */
void QHLPing::processPing(const char *data, int len)
{
    qDebug()<<"LL";
    int partLength=0;
    char type='\0';
    const char * dataPtr ;

    if(len>5){ // grab header at byte 5, first 4 are 0xff
        type = data[4];
    }

    switch(type){
        case 'I': //info ping
            HL_INFO_REPLY *reply = new HL_INFO_REPLY;

            if(len>6)
                reply->protocol = data[5];

            //start copying data over c style
            dataPtr= data+6;

            partLength = strlen(dataPtr);
            reply->hostname = new char[partLength+1];
            strcpy(reply->hostname, dataPtr);
            reply->hostname[partLength]='\0';
            qDebug() << reply->hostname;

            dataPtr+= partLength+1;

            partLength = strlen(dataPtr);
            reply->map = new char[partLength+1];
            strcpy(reply->map, dataPtr);
            reply->map[partLength]='\0';
            qDebug() << reply->map;

            dataPtr+= partLength+1;

            partLength = strlen(dataPtr);
            reply->game_directory = new char[partLength+1];
            strcpy(reply->game_directory, dataPtr);
            reply->game_directory[partLength]='\0';
            qDebug() << reply->game_directory;

            dataPtr+= partLength+1;

            partLength = strlen(dataPtr);
            reply->game_description= new char[partLength+1];
            strcpy(reply->game_description, dataPtr);
            reply->game_description[partLength]='\0';
            qDebug() << reply->game_description;

            dataPtr+= partLength+1;

            reply->app_id = (unsigned short)
                    ((unsigned char)dataPtr[1]) << 8 |
                    ((unsigned char)dataPtr[0]);

            reply->num_players = dataPtr[2];
            reply->max_players = dataPtr[3];
            reply->num_of_bots = dataPtr[4];
            reply->is_private = dataPtr[5];
            reply->os = dataPtr[6];
            reply->password = dataPtr[7];
            reply->secure = dataPtr[8];

            qDebug()<<reply->app_id<<reply->num_players<<reply->max_players<<reply->num_of_bots<<reply->is_private<<reply->os<<reply->password<<reply->secure;

            dataPtr +=9;

            if(reply->game_id == 2400){ // "the ship"
                reply->ship_mode=dataPtr[0];
                reply->ship_whitneses=dataPtr[1];
                reply->ship_duration=dataPtr[2];
                dataPtr+=3;
            }

            partLength = strlen(dataPtr);
            reply->game_version= new char[partLength+1];
            strcpy(reply->game_version, dataPtr);
            reply->game_version[partLength]='\0';
            qDebug() << reply->game_version;

            dataPtr+= partLength+1;

            reply->extra_data = dataPtr[0];
            dataPtr++;

            if(reply->extra_data & 0x80){ //extra data flag  - port
                reply->port = (unsigned short)
                        ((unsigned char)dataPtr[1]) << 8 |
                        ((unsigned char)dataPtr[0]);
                dataPtr+=2;
            }

            if(reply->extra_data & 0x10){ //extra data flag - steam id - 64 bits
                reply->steamid = 0;
                for(int i=0;i<8;i++){
                    reply->steamid = reply->steamid | (((unsigned char)dataPtr[i]) << 8*i);
                }

                dataPtr+=8;
                qDebug()<<reply->steamid;

            }

            if(reply->extra_data & 0x40){ //extra data flag - sourcetv, short and string
                reply->sourcetv_port = (unsigned short)
                        ((unsigned char)dataPtr[1]) << 8 |
                        ((unsigned char)dataPtr[0]);
                dataPtr+=2;

                partLength = strlen(dataPtr);
                reply->sourcetv_name= new char[partLength+1];
                strcpy(reply->sourcetv_name, dataPtr);
                reply->sourcetv_name[partLength]='\0';
                dataPtr+=partLength+1;

            }

            if(reply->extra_data & 0x20){ //extra data flag - keywords

                partLength = strlen(dataPtr);
                reply->keywords = new char[partLength+1];
                strcpy(reply->keywords, dataPtr);
                reply->keywords[partLength]='\0';
                dataPtr+=partLength+1;
                qDebug()<<reply->keywords;

            }

            if(reply->extra_data & 0x01){ //extra data flag - gameid, long long
                reply->game_id = 0;
                for(int i=0;i<8;i++){
                    reply->game_id = reply->game_id | (((unsigned char)dataPtr[i]) << 8*i);
                }

                dataPtr+=8;
                qDebug()<<reply->game_id;


            }


        break;

    }

}

