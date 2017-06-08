#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTcpSocket"
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void timerEvent(QTimerEvent *e);

public slots:
    void putData();
    void tcpConnect();
    void tcpDisconnect();
    void startTime();
    void stopTime();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QTimer *t = new QTimer(this);
};

#endif // MAINWINDOW_H
