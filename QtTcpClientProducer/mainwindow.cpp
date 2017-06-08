#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    tcpConnect();

    connect(ui->ConnectButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

    connect(ui->DisconnectButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));


    connect(ui->StartButton,
            SIGNAL (clicked(bool)),
            this,
            SLOT (startTime()));

    connect(ui->StopButton,
            SIGNAL (clicked(bool)),
            this,
            SLOT (stopTime()));

    connect(t,
            SIGNAL(timeout()),
            this,
            SLOT(putData()));
}

void MainWindow::tcpConnect(){
  socket->connectToHost(ui->IP_line->text(),1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}
void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();
    qDebug() << "Disconnected";
    t->stop();
}

void MainWindow::putData()
{
  QDateTime datetime;
  QString str;
  if(socket->state()== QAbstractSocket::ConnectedState){
      datetime = QDateTime::currentDateTime();
      int minimo = ui->HS_MIN->value();
      int maximo = ui->HS_MAX->value();
      ui->HS_MIN->setRange(0,maximo-1);
      if(minimo>maximo)
      {
          minimo = maximo -1;
      }

      str = "set "+
          datetime.toString(Qt::ISODate)+
          " "+
          QString::number(minimo+qrand()%(maximo-minimo)+1)+"\r\n";

      ui->Producer_txtBox->append(str);

      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}

void MainWindow::startTime()
{
    t->start(ui->HS_Timing->value()*1000);

}

void MainWindow::stopTime()
{
    t->stop();
}

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}
