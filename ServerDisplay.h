#ifndef SERVERDISPLAY_H
#define SERVERDISPLAY_H

#include <QWidget>

namespace Ui {
class ServerDisplay;
}

class ServerDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ServerDisplay(QWidget *parent = 0);
    ~ServerDisplay();

private:
    Ui::ServerDisplay *ui;
};

#endif // SERVERDISPLAY_H
