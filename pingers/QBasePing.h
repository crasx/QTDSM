#ifndef QBASEPING_H
#define QBASEPING_H

#include <QObject>


class QBasePing  : public QObject
{
    Q_OBJECT
public:
    QBasePing();
    ~QBasePing();

    virtual QString* ToString() ;
    virtual float getAveragePing();

    int getPingTimeoutMs() const;
    void setPingTimeoutMs(int value);

   protected:
    int pingTimeoutMs;
};

#endif // QBASEPING_H
