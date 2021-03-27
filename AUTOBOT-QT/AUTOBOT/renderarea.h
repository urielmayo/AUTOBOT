#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPen>
#include <QFile>
class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);
    void setPoint(QPoint point);
    void setPoint(int x, int y);
    void removePoint(int nroPunto);
    void reset();
    int getNPoints() const {return cantPuntos;}
    void completarArchivo(QPoint* points);
    void setSize(int ancho, int alto);
    void abrirPlano(const QString fileName);
    void paintCar();
    void updateCarPos();
    void getSize(int & ancho, int & alto);
    void startPainting();

protected:
    void paintEvent(QPaintEvent* event = nullptr);
    void timerEvent(QTimerEvent *);

private:
    bool startRide = false;
    void setPen();
    void setCarPen();
    QPen pen, carPen;
    QPoint point[20],car;
    int cantTramos;
    int tramosRecorridos;
    int cantPuntos = 0, ancho, alto;

    //funcion de mover al auto
    int xi ,yi, xf, yf;
    float xCar, yCar;
    int i;
    float dist, angulo;
    bool pendienteInfinita, stopPainting;
    int carTimerId;
signals:
    void valueChanged(int value);
};

#endif // RENDERAREA_H
