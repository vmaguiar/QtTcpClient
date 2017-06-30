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
    /**
     * @brief tcpConnect conecta o projeto do Producer com o projeto do Server,
     * ou seja, conecta ao servidor
     */
  void tcpConnect();
  /**
   * @brief tcpDisconnect desconecta o Producer do servidor
   */
  void tcpDisconnect();
  void getData();
  /**
   * @brief soltar_bruxo Inicializa o temporizador, nescessario para a ritmar as strings produzidas
   */
  void soltar_bruxo();
  /**
   * @brief parar_bruxo para o temporizador quando acionado
   */
  void parar_bruxo();
  /**
   * @brief update atualiza a lista com IP's
   */
  void update();
  /**
   * @brief selecIP insere o IP na linha propria com click duplo do mouse
   * @param item
   */
  void selecIP(QListWidgetItem* item);
  /**
   * @brief setIntervalo insere o intervalo com que o temporizador e o slider vao funcionar
   */
  void setIntervalo();
  /**
   * @brief defcor define a cor de fundo da tela
   */
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
