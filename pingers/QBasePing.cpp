#include "pingers/QBasePing.h"

QBasePing::QBasePing()
{
}

QBasePing::~QBasePing()
{

}

QString *QBasePing::ToString()
{
    return new QString("");
}

float QBasePing::getAveragePing()
{
    return 0.0;
}


int QBasePing::getPingTimeoutMs() const
{
    return pingTimeoutMs;
}

void QBasePing::setPingTimeoutMs(int value)
{
    pingTimeoutMs = value;
}


