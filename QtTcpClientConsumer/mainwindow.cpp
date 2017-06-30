#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    tcpConnect();

    connect(O_bruxo_do_tempo,
            SIGNAL(timeout()),
            this,
            SLOT(getData()));

    connect(ui->ConnectButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpConnect()));

    connect(ui->DisconnectButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(tcpDisconnect()));

    connect(ui->HS_Timing,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(soltar_bruxo()));

    connect(ui->StartButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(soltar_bruxo()));

    connect(ui->StopButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(parar_bruxo()));

    connect(ui->UpdateButton,
            SIGNAL(clicked(bool)),
            this,
            SLOT(update()));

    connect(ui->listWidget,
            SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,
            SLOT(selecIP(QListWidgetItem*)));

    connect(ui->HS_Timing,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(setIntervalo()));

    connect(ui->HS_Timing,
            SIGNAL(valueChanged(int)),
            ui->widgetPlotter,
            SLOT(setVelocidade(int)));

    connect(ui->actionDefcor,
            SIGNAL(triggered(bool)),
            this,
            SLOT(defcor()));

ui->label_2->setNum(ui->HS_Timing->value());
ui->listWidget->addItem("127.0.0.1");
}
void MainWindow::tcpConnect(){
  socket->connectToHost(ui->IP_Line->text(),1234);
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
    O_bruxo_do_tempo->stop();
}

void MainWindow::getData(){
  QString str;
  QByteArray array;
  QStringList list;
  QDateTime datetime;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write("get 127.0.0.1\r\n");
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          datetime.fromString(list.at(0),Qt::ISODate);
          str = list.at(1);
          qDebug() << datetime << ": " << str;
          O_bruxo_do_tempo->start();
          y = list.at(1).toInt();
          repaint();
        }
      }
    }
  }
}

void MainWindow::soltar_bruxo()
{
    O_bruxo_do_tempo->start(ui->HS_Timing->value()*1000);
}

void MainWindow::parar_bruxo()
{
    O_bruxo_do_tempo->stop();
}

void MainWindow::update()
{
    ui->listWidget->addItem(ui->IP_Line->text());
}

void MainWindow::setIntervalo()
{
    O_bruxo_do_tempo->setInterval(ui->HS_Timing->value()*1000);
}

void MainWindow::selecIP(QListWidgetItem* item)
{
    ui->IP_Line->setText(item->text());
}

void MainWindow::defcor()
{
    int r, g, b;
    QColorDialog colordialog;
    colordialog.exec();

    r = colordialog.selectedColor().red();
    g = colordialog.selectedColor().green();
    b = colordialog.selectedColor().blue();
    ui->widgetPlotter->setFundo(r, g, b);
}

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
    delete O_bruxo_do_tempo;
}
