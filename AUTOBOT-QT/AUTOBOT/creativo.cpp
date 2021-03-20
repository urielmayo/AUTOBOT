#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include <QDebug>
#include <QKeyEvent>
#include <QDir>

enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

enum{
    PRESSED,
    RELEASED,
};

//void moveArrow(int key, int state);

static uint8_t direccion = 0;

bool upArrowPressed = false,
     downArrowPressed = false,
     leftArrowPressed = false,
     rightArrowPressed = false;

bool keyPressedEvent = false,
     keyReleasedEvent = false;

//funcion para setear los valores de velocidad del auto
void MainWindow::setGameArea()
{
    ui->speedSlider->setRange(0,MAX_VELOCITY);
    ui->speedSlider->setValue(0);

    ui->speedDial->setRange(0,MAX_VELOCITY);
    ui->speedDial->setValue(0);
}


void MainWindow::keyPressEvent(QKeyEvent *input)
{
    if(input->key() == Qt::Key_W){
        if(!input->isAutoRepeat()){
            ui->upArrowLabel->move(ui->upArrowLabel->x(),ui->upArrowLabel->y() -5);
            if(!downArrowPressed){
                direccion |= (1 << 3);
                keyPressedEvent = true;
                upArrowPressed = true;
            }
        }
    }
    if(input->key() == Qt::Key_A){

        if(!input->isAutoRepeat()){
            ui->leftArrowLabel->move(ui->leftArrowLabel->x()-5,ui->leftArrowLabel->y());
            if(!rightArrowPressed){
                direccion |= (1 << 0);
                keyPressedEvent = true;
                leftArrowPressed = true;
            }
        }
    }
    if(input->key() == Qt::Key_S){
        if(!input->isAutoRepeat()){
            ui->downArrowLabel->move(ui->downArrowLabel->x(),ui->downArrowLabel->y()+5);
            if(!upArrowPressed){
                direccion |= (1 << 2);
                keyPressedEvent = true;
                downArrowPressed = true;
            }
        }
    }
    if(input->key() == Qt::Key_D){
        if(!input->isAutoRepeat()){
            ui->rightArrowLabel->move(ui->rightArrowLabel->x()+5,ui->rightArrowLabel->y());
            if(!leftArrowPressed){
                direccion |= (1 << 1);
                keyPressedEvent = true;
                rightArrowPressed = true;
            }
        }
    }
    if(keyPressedEvent){
        server.enviar(QString::number(direccion));
        keyPressedEvent = false;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *input)
{
    keyReleasedEvent = false;

    if(input->key() == Qt::Key_W){
        ui->upArrowLabel->move(ui->upArrowLabel->x(),ui->upArrowLabel->y() +5);
        if(!downArrowPressed){
            direccion &= ~(1 << 3);
            upArrowPressed = false;
            keyReleasedEvent = true;
        }
    }
    if(input->key() == Qt::Key_A){
        ui->leftArrowLabel->move(ui->leftArrowLabel->x()+5,ui->leftArrowLabel->y());
        if(!rightArrowPressed){
            direccion &= ~(1 << 0);
            keyReleasedEvent = true;
            leftArrowPressed = false;
        }
    }
    if(input->key() == Qt::Key_S){
        ui->downArrowLabel->move(ui->downArrowLabel->x(),ui->downArrowLabel->y()-5);
        if(!upArrowPressed){
            direccion &= ~(1 << 2);
            downArrowPressed = false;
            keyReleasedEvent = true;
        }
    }
    if(input->key() == Qt::Key_D){
        ui->rightArrowLabel->move(ui->rightArrowLabel->x()-5,ui->rightArrowLabel->y());
        if(!leftArrowPressed){
            direccion &= ~(1 << 1);
            rightArrowPressed = false;
            keyReleasedEvent = true;
        }
    }
    if(keyReleasedEvent){
        server.enviar(QString::number(direccion));
    }
}

//-------------------------------------------------------------------------------------------------
//SLOTS

//funcion para mover el dial y elegir velocidad en creatvio
void MainWindow::on_speedSlider_valueChanged(int value)
{
    QString speed;
    speed +="Velocidad: ";
    speed += QString::number(value);
    speed += " KM/H";
    ui->staticSpeedLabel->setText(speed);
}

void MainWindow::on_speedDial_valueChanged(int value)
{
    QString speed;
    speed += QString::number(value);
    speed += " KM/H";
    ui->speedLabel->setText(speed);
}

void MainWindow::on_creativeExitButton_clicked()
{
    server.enviar(MSG_EXIT);
    estado = MENU;
    goToTab(HOME);
}

void MainWindow::deletePlano()
{
    qDebug() <<"borrando plano";
    delete plano;
    plano = nullptr;
}
