#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QColorDialog>
#include <QString>

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

void MainWindow::getData()
{
  double menorx, maiorx, menory, maiory;
  QVector<double> y;
  QVector<double> x;
  QVector<double> y_temp;
  QString str;
  QByteArray array;
  QStringList list;
  QDateTime datetime;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      socket->write (QString("get " + ui->IP_Line->text() + "\r\n").toStdString().c_str());
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          datetime = QDateTime::fromString(list.at(0),Qt::ISODate);
          str = list.at(1);
          y.append(str.toFloat());
          y_temp.append(str.toFloat());
          x.append(datetime.toTime_t());
          qDebug() << datetime << ": " << str;
          //qDebug() << y << "\n        " << x;
        }
      }
    }
    menorx = x.at(0);
    maiorx = x.at(x.size()-1);

    for(int i = 0; i < x.size(); i++)
    {
        x.replace(i, (x.at(i)-menorx)/(maiorx-menorx));
    }

    qSort(y_temp);

    menory = y_temp.at(0);
    maiory = y_temp.at(y_temp.size()-1);
    for(int i = 0; i < y_temp.size(); i++)
    {
        y.replace(i,(y.at(i)-menory)/(maiory-menory));
    }
    ui->widgetPlotter->DefY(y);
    ui->widgetPlotter->DefX(x);
    ui->widgetPlotter->update();
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

/*void MainWindow::defcor()
{
    int r, g, b;
    QColorDialog colordialog;
    colordialog.exec();

    r = colordialog.selectedColor().red();
    g = colordialog.selectedColor().green();
    b = colordialog.selectedColor().blue();
    ui->widgetPlotter->setFundo(r, g, b);
}*/

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
    delete O_bruxo_do_tempo;
}
