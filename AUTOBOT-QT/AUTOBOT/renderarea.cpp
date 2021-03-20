#include "renderarea.h"
#include "mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QDir>
#include <QtMath>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
    this->setPen();

}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setBrush(Qt::lightGray);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.drawRect(this->rect());
    painter.setPen(pen);
    for(int i = 0; i <cantPuntos; i++)
    {
        painter.drawPoint(point[i]);
        painter.drawText(point[i],QString::number(i+1) + " (" + QString::number(point[i].x()) + ";" + QString::number(point[i].y()) + ")");
        if(i>0){
            pen.setWidth(5);
            painter.setPen(pen);
            painter.drawLine(point[i-1],point[i]);
            pen.setWidth(10);
            painter.setPen(pen);
        }
    }
    if(startRide){
        pen.setBrush(Qt::red);
        painter.setPen(pen);
        painter.drawPoint(car);
        setPen();
    }

}

void RenderArea::timerEvent(QTimerEvent *)
{
    if(!stopPainting){
        updateCarPos();
        this->repaint();
    }
}

void RenderArea::setPoint(QPoint point)
{
    this->point[cantPuntos] = point;
    cantPuntos++;
}

void RenderArea::setPoint(int x, int y){
    QPoint * newPoint = new QPoint(x,y);
    this->point[cantPuntos] = *newPoint;
    cantPuntos++;
    delete  newPoint;
}

void RenderArea::removePoint(int nroPunto)
{
    if(nroPunto < 20){
        for(int i = nroPunto -1 ; i < 20; i++)
        {
            this->point[i].setX(point[i+1].x());
            this->point[i].setY(point[i+1].y());
        }
        cantPuntos --;
   }
   else cantPuntos--;
}

void RenderArea::setPen()
{
    pen.setBrush(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(10);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
}

void RenderArea::setCarPen()
{
    carPen.setBrush(Qt::red);
    carPen.setStyle(Qt::SolidLine);
    carPen.setWidth(10);
    carPen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
}



void RenderArea::reset()
{
    QPoint def(0,0);
    for(int i = 0; i < cantPuntos; i ++)
    {
        point[i] = def;
    }
    cantPuntos = 0;
    if(startRide){
        startRide = false;
        i = 0;
        cantTramos = 0;
        tramosRecorridos = 0;
        killTimer(carTimerId);
    }
    repaint();

}

void RenderArea::completarArchivo(QPoint* points)
{
    for(int i = 0; i < cantPuntos; i++)
    {
        qDebug() << point[i].x() <<";"<< point[i].y();
        points[i].setX(this->point[i].x());
        points[i].setY(this->point[i].y());
    }
}

void RenderArea::setSize(int ancho, int alto){
    this->ancho = ancho;
    this->alto = alto;
}

void RenderArea::abrirPlano(const QString fileName)
{
    QDir dir(TRACK_DIR);
    QFile file(dir.absoluteFilePath(fileName));

    int i = 0;
    bool isSize = true;
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "archivo no encontrado";
    }
    QTextStream text(&file);
    while (!text.atEnd()) {
        QString line = text.readLine();
        if(isSize){
            ancho = line.section(";",0,0).toInt();
            alto = line.section(";",1,1).toInt();
            isSize = false;
        }
        else{
            setPoint(line.section(";",0,0).toUInt(),line.section(";",1,1).toInt());
            i++;
        }

    }
    file.close();
    cantPuntos = i;
    cantTramos = cantPuntos -1;
    tramosRecorridos = 0;
}

void RenderArea::paintCar()
{
    this->startRide = true;
    tramosRecorridos = 0;
    emit valueChanged(tramosRecorridos);
    i = 0;
    stopPainting = false;

    //P0
    xi = point[tramosRecorridos].x();
    yi = point[tramosRecorridos].y();

    //P1
    xf = point[tramosRecorridos+1].x();
    yf = point[tramosRecorridos+1].y();

    xCar = xi;
    yCar = yi;
    car.setX(xCar);
    car.setY(yCar);

    dist = sqrt(pow(xf-xi,2) + pow(yf-yi,2));
    (xf == xi) ? (pendienteInfinita = true) : (angulo = qAtan((yf-yi) / (xf-xi)));

    carTimerId = startTimer(100);
}

void RenderArea::updateCarPos()
{
    qDebug()<< "tramos recorridos: " << tramosRecorridos<< " dist. recorrida = " << 5*i;
    if((5*i) >= dist){
        tramosRecorridos++;
        emit valueChanged(tramosRecorridos);
        i = 1;
        xi = point[tramosRecorridos].x();
        yi = point[tramosRecorridos].y();
        xf = point[tramosRecorridos+1].x();
        yf = point[tramosRecorridos+1].y();

        dist = sqrt(pow(xf-xi,2) + pow(yf-yi,2));
        (xf == xi) ? (pendienteInfinita = true) : (angulo = qAtan((float)(yf-yi) / (float)(xf-xi)));
        qDebug() << (float)(yf-yi)/(xf - xi);
        xCar = xi;
        yCar = yi;
        car.setX(xCar);
        car.setY(yCar);
        if(tramosRecorridos == cantTramos){
            stopPainting = true;
        }
    }

    else{

        if(pendienteInfinita){
            xCar = xi;
            (yf > yi) ? (yCar+=5) : (yCar -= 5);
            car.setX(xCar);
            car.setY(yCar);
        }
        else{

            xCar = xi + 5 * i * qCos(angulo);
            yCar = yi + 5 * i * qSin(angulo);
            qDebug() <<"i = "<<i << " Car = " << xCar <<";" << yCar;
            car.setX((int)qRound(xCar));
            car.setY((int)qRound(yCar));
        }
        i++;
    }
}

void RenderArea::getSize(int &ancho, int &alto)
{
    ancho = this->ancho;
    alto = this->alto;
}

void RenderArea::startPainting()
{

}
