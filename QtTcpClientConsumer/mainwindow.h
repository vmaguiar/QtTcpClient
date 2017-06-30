#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QColor>
#include <QListWidget>
#include "plotter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
  void tcpConnect();
  void tcpDisconnect();
  void getData();
  void soltar_bruxo();
  void parar_bruxo();
  void update();
  void selecIP(QListWidgetItem* item);
  void setIntervalo();
  void defcor();

private slots:
  void on_actionDefcor_objectNameChanged(const QString &objectName);

  void on_widgetPlotter_customContextMenuRequested(const QPoint &pos);

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  QTimer *O_bruxo_do_tempo = new QTimer(this);
  double y;
  QColor fundo;
};

#endif // MAINWINDOW_H
