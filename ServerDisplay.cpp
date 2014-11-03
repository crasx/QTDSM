#include "ServerDisplay.h"
#include "ui_ServerDisplay.h"

ServerDisplay::ServerDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerDisplay)
{
    ui->setupUi(this);
}

ServerDisplay::~ServerDisplay()
{
    delete ui;
}
