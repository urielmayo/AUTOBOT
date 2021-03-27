#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

namespace  Trama{
QString Empty = "",
        Start = "start",
        Error = "ERROR",
        NotInLine = "not_line",
        OK = "OK",
        Stop = "stop",
        Continue = "continue",
        End = "end",
        Lost = "lost";
}

void MainWindow::procesarTrama()
{
    QString trama = server.getMsg();

    if(trama == Trama::Empty){
        return;
    }
    else if(trama == Trama::Error){
        QMessageBox::warning(this,"ERROR","El Auto esta teniendo problemas, por favor revisar");
        estado = MENU;
    }
    qDebug() << trama;

    switch (estado){

    case WAITING:
        if(trama == Trama::OK){
            QMessageBox::information(this,"EXITO","CONEXION EXITOSA");
            this->updateWorkPage();
            this->updateHome();
            estado = MENU;
        }
        break;

    case MENU:
        break;

    case PRE_RIDE_PLANO:
        if(trama == Trama::Start){
            connect(ui->renderArea,SIGNAL(valueChanged(int)),this,SLOT(actualizarTramo(int)));
            ui->renderArea->paintCar();
            ui->planoStartButton->setDisabled(true);
            estado = RIDE;
        }
        break;

    case PRE_RIDE_START:
        if(trama == Trama::Start){
            ui->InitRideButton->setDisabled(true);
            estado = RIDE;
        }
        else if(trama == Trama::NotInLine){
            QMessageBox::warning(this,"FUERA DE LINEA","El auto no se encuentra en la linea. por favor coloque el auto con los sensores en la linea e inicie de nuevo");
        }
        break;

    case STOP:
        if(trama == Trama::Stop){
            ui->StopContinueButton->setText("CONTINUAR");
        }
        else if(trama == Trama::Continue){
            ui->StopContinueButton->setText("STOP");
            estado = RIDE;
        }

        break;

    case RIDE:
        if(trama == Trama::End){
            if(mode == MODE_PLANO){
                ui->renderArea->reset();
                disconnect(ui->renderArea,SIGNAL(valueChanged(int)),this,SLOT(actualizarTramo(int)));
                ui->cantTramosLabel->clear();
                ui->renderArea->repaint();
                ui->planoStartButton->setDisabled(false);
                goToTab(WORK);
            }
            else{
                ui->InitRideButton->setDisabled(false);
            }
            QMessageBox::information(this,"TRAYECTO TERMINADO","el auto completo su recorrido");
            estado = MENU;
        }
        else if(trama == Trama::Lost){
            QMessageBox::warning(this,"AUTO PERDIDO","El auto se salio de la linea, porfavor pngalo de nuevo en la linea y toque reanudar");
            ui->StopContinueButton->setText("CONTINUAR");
            estado = STOP;
        }
        break;

    default: break;
    }
}
