#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <QColor>

namespace Ui {
class Plotter;
}

class Plotter : public QWidget
{
    Q_OBJECT

public:
    ~Plotter();
    explicit Plotter(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void setFundo(int r, int g, int b);

private:
    Ui::Plotter *ui;
    float teta, veloc;
    QColor fundo;
    double y;

public slots:
  void setVelocidade(int _velocidade);
};

#endif // PLOTTER_H
