#include "plotter.h"
//#include "ui_plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QDebug>

Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
   // ui(new Ui::Plotter)
{
    //ui->setupUi(this);
    teta = 0.0;
    startTimer(10);
    veloc = 0.0;
    fundo.setRgb(255,255,0);
    setMouseTracking(true);
}

void Plotter::timerEvent(QTimerEvent *e){
  teta = teta + veloc;
  repaint();
}

void Plotter::setFundo(int r, int g, int b){
  fundo.setRgb(r,g,b);
  repaint();
}

void Plotter::setVelocidade(int _velocidade)
{
  veloc = _velocidade/100.0;
  repaint();
}

void Plotter::paintEvent(QPaintEvent *e)
{
    int x1, y1, x2, y2;
    QPainter pintor(this);
    pintor.setRenderHint(QPainter::Antialiasing);
    QPen caneta;
    QBrush pincel;
    caneta.setColor(QColor(0,0,0));
    caneta.setWidth(3);
    pintor.setPen(caneta);
    pincel.setStyle(Qt::SolidPattern);
    pincel.setColor(QColor(0,0,0));
    pintor.setBrush(pincel);

    x1 = 0;
    y1= y*height();
    for(int i=1; i<width(); i++)
    {
    x2=i;
    y2= y*height();
    pintor.drawLine(x1,y1,x2,y1);
    x1 = x2;
    y1 = y2;
    }

}

Plotter::~Plotter()
{
    delete ui;
}
