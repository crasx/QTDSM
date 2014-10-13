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


    do {
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
    } while (udpSocket->hasPendingDatagrams());

    //process returned data
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
    int partLength=0;
    int processedBytes=0; //used to prevent string overflow

    char type='\0';
    const char * dataPtr ;

    if(len>5){ // grab header at byte 5, first 4 are 0xff
        type = data[4];
    }

    switch(type){
        case 'I': //info ping

            infoReplyMutex.lock();
            infoReply = new HL_INFO_REPLY;

            if(len>6)
                this->infoReply->protocol = data[5];

            //start copying data over c style
            dataPtr= data+6;

            processPingGrabString(this->infoReply->hostname, &dataPtr, len, &processedBytes);

            processPingGrabString(this->infoReply->map, &dataPtr, len, &processedBytes);

            processPingGrabString(this->infoReply->game_directory, &dataPtr, len, &processedBytes);

            processPingGrabString(this->infoReply->game_description, &dataPtr, len, &processedBytes);


            this->infoReply->app_id = (unsigned short)
                    ((unsigned char)dataPtr[1]) << 8 |
                    ((unsigned char)dataPtr[0]);

            this->infoReply->num_players = dataPtr[2];
            this->infoReply->max_players = dataPtr[3];
            this->infoReply->num_of_bots = dataPtr[4];
            this->infoReply->is_private = dataPtr[5];
            this->infoReply->os = dataPtr[6];
            this->infoReply->password = dataPtr[7];
            this->infoReply->secure = dataPtr[8];

            qDebug()<<this->infoReply->app_id<<this->infoReply->num_players<<this->infoReply->max_players<<this->infoReply->num_of_bots<<this->infoReply->is_private<<this->infoReply->os<<this->infoReply->password<<this->infoReply->secure;

            dataPtr +=9;
            processedBytes+=9;

            if(this->infoReply->game_id == 2400){ // "the ship"
                this->infoReply->ship_mode=dataPtr[0];
                this->infoReply->ship_whitneses=dataPtr[1];
                this->infoReply->ship_duration=dataPtr[2];
                dataPtr+=3;
                processedBytes+=3;
            }

            processPingGrabString(this->infoReply->game_version, &dataPtr, len, &processedBytes);

            this->infoReply->extra_data = dataPtr[0];
            dataPtr++;
            processedBytes++;

            if(this->infoReply->extra_data & 0x80){ //extra data flag  - port
                this->infoReply->port = (unsigned short)
                        ((unsigned char)dataPtr[1]) << 8 |
                        ((unsigned char)dataPtr[0]);
                dataPtr+=2;
                processedBytes+=2;
            }

            if(this->infoReply->extra_data & 0x10){ //extra data flag - steam id - 64 bits
                this->infoReply->steamid = 0;
                for(int i=0;i<8;i++){
                    this->infoReply->steamid = this->infoReply->steamid | (((unsigned char)dataPtr[i]) << 8*i);
                }

                dataPtr+=8;
                processedBytes+=8;

            }

            if(this->infoReply->extra_data & 0x40){ //extra data flag - sourcetv, short and string
                this->infoReply->sourcetv_port = (unsigned short)
                        ((unsigned char)dataPtr[1]) << 8 |
                        ((unsigned char)dataPtr[0]);
                dataPtr+=2;
                processedBytes+=2;

                processPingGrabString(this->infoReply->sourcetv_name, &dataPtr, len, &processedBytes);

            }

            if(this->infoReply->extra_data & 0x20){ //extra data flag - keywords
                processPingGrabString(this->infoReply->keywords, &dataPtr, len, &processedBytes);


            }

            if(this->infoReply->extra_data & 0x01){ //extra data flag - gameid, long long
                this->infoReply->game_id = 0;
                for(int i=0;i<8;i++){
                    this->infoReply->game_id = this->infoReply->game_id | (((unsigned char)dataPtr[i]) << 8*i);
                }

                dataPtr+=8;
                processedBytes+=8;

            }

            infoReplyMutex.unlock();
        break;

    }

}

void QHLPing::processPingGrabString(char *result, const char **dataPtr, int maxLength, int *processedBytes )
{
    if(*processedBytes >= maxLength)
        return;

    int partLength = strlen(*dataPtr);
    result = new char[partLength+1];
    strcpy(result, *dataPtr);
    result[partLength]='\0';
    *dataPtr+=partLength+1;
    processedBytes += partLength+1;
    qDebug()<<result;
}

