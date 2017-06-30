#include "plotter.h"
//#include "ui_plotter.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QDebug>

Plotter::Plotter(QWidget *parent) :
    QWidget(parent)
{

}
void Plotter::DefX(QVector<double> x)
{
    eixoX = x;
}

void Plotter::DefY(QVector<double> y)
{
    eixoY = y;
}

/*void Plotter::timerEvent(QTimerEvent *e){
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
}*/

void Plotter::paintEvent(QPaintEvent *e)
{
    QPainter pintor(this);
    QBrush pincel;
    QPen caneta;
    int x1, x2, y1, y2;

    pintor.setRenderHint(QPainter::Antialiasing);

    caneta.setColor(QColor(0,0,35));
    pintor.setPen(caneta);

    pincel.setColor(QColor(255,200,200));
    pincel.setStyle(Qt::SolidPattern);
    pintor.setBrush(pincel);

    pintor.drawRect(0,0,width()-1, height()-1);


    caneta.setColor(QColor(0,0,35));

    caneta.setWidth(3);
    pintor.setPen(caneta);
    if(eixoX.size() > 0)
    {
        x1= eixoX.at(0);
        y1= eixoY.at(0);
        for(int i = 1; i < eixoX.size(); i++)
        {
            x2 = qRound(eixoX.at(i)*width());
            y2 = height() - qRound(eixoY.at(i)*height());
            pintor.drawLine(x1,y1,x2,y2);
            x1 = x2;
            y2 = y2;
        }
    }
}

/*void Plotter::drawgraf(double y1)
{
    int x1, x2;
    double y2;
    x1=0;
    y1 = y1*height();
    for(int i=1; i<width(); i++)
    {
    x2=i;
    y2= y1*height();
    x1 = x2;
    y1 = y2;
    }
    repaint();
}*/

/*Plotter::~Plotter()
{
    delete ui;
}*/
