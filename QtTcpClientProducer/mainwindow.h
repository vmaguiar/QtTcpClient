#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTcpSocket"
#include <QDebug>
#include <QTimer>

namespace Ui {
/**
 * @brief The MainWindow class representa a janela criada e seu layout
 */
class MainWindow;
}
/**
 * @brief The MainWindow class que esta herdando da class QMainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void timerEvent(QTimerEvent *e);

public slots:
    /**
     * @brief Cria as strings, com a data e o numero aleatorio gerado,
     * @param as quais o produtor deverar imprimir em sua janela
     */
    void putData();
    /**
     * @brief Conecta o projeto do Producer com o projeto do Server,
     * @param ou seja, conecta ao servidor
     */
    void tcpConnect();
    /**
     * @brief Desconecta o Producer do servidor
     */
    void tcpDisconnect();
    /**
     * @brief Inicializa o temporizador, nescessario para a ritmar as strings produzidas
     */
    void startTime();
    /**
     * @brief para o temporizador quando acionado
     */
    void stopTime();

private:
    Ui::MainWindow *ui;
    /**
     * @brief The QTcpSocket class cria um ponteiro para o encaixe do produtor e o servidor se conectarem
     */
    QTcpSocket *socket;
    /**
     * @brief The QTimer class cria um ponteiro para o temporizador
     */
    QTimer *t = new QTimer(this);
};

#endif // MAINWINDOW_H
