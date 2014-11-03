#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateServerTable()));
    updateTimer->start(1000);
    addServer();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateServerTable()
{

    int row=0;
    Q_FOREACH(QBasePing *server, this->servers) {
    qDebug()<<"UPS";
            //QTableWidgetItem *newItem = new QTableWidgetItem(server->getAveragePing());
           // ui->serverList->setItem(row, 0, newItem);
    }

}

void MainWindow::on_addServerButton_clicked()
{
    addServer();
}

void MainWindow::addServer()
{
    ui->serverList->setRowCount(ui->serverList->rowCount()+1);
    QString *ip = new QString("74.91.124.246");
    QHLPing *server = new QHLPing(ip, 27015);
    this->servers.append(server);

}
