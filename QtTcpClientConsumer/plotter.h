#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QColor>
#include <vector>

namespace Ui {
class Plotter;
}

class Plotter : public QWidget
{
    Q_OBJECT

public:
    //~Plotter();
    explicit Plotter(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    //void timerEvent(QTimerEvent *e);
    //void setFundo(int r, int g, int b);
    //void drawgraf(double y1);
    void DefX(QVector<double> x);
    void DefY(QVector<double> y);

private:
    //QColor fundo;
    //double y1, y2, x1, x2;
    QVector<double> eixoX;
    QVector<double> eixoY;

public slots:
  void setVelocidade(int _velocidade);
};

#endif // PLOTTER_H
