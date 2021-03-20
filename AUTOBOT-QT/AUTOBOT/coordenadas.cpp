#include "coordenadas.h"
#include "ui_coordenadas.h"
#include <QMessageBox>
#include <QDebug>
#include <QTimer>

Coordenadas::Coordenadas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Coordenadas)
{
    ui->setupUi(this);
    setWindowTitle("INGRESAR COORDENADAS:");
}

Coordenadas::~Coordenadas()
{
    delete ui;
}

void Coordenadas::setRange(int xRange, int yRange)
{
    ui->xSpinBox->setRange(0,xRange);
    ui->ySpinBox->setRange(0,yRange);


    QString xAxis = "[0;", yAxis ="[0;";
    xAxis += QString::number(xRange);
    xAxis += "]";
    yAxis += QString::number(yRange);
    yAxis += "]";
    ui->xValues->setText(xAxis);
    ui->yValues->setText(yAxis);
}

QPoint Coordenadas::getPoint() const{return this->point;}

void Coordenadas::on_xSpinBox_valueChanged(int arg1)
{
    point.setX(arg1);
}

void Coordenadas::on_ySpinBox_valueChanged(int arg1)
{
    point.setY(arg1);
}

bool Coordenadas::retValue()
{
    return returned;
}

void Coordenadas::on_buttonBox_accepted()
{
    returned = true;
}




