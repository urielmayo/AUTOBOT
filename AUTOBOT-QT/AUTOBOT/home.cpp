#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordenadas.h"
#include "server.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

//------- PAGINA UNO ------------------------------------------------------------------------------

//funcion que se activa al presionar el boton Trabajo en el inicio
void MainWindow::on_wrkBotton_clicked()
{
    qDebug() <<isConnected;
    if(!isConnected){
        if(isLoged == false){
            QString mensaje = "usted esta por acceder al programa sin estar conectado al vehiculo,"
                              "por lo que la aplicacion se vera drasticamente limitada";
            QMessageBox::warning(this,"ATENCION",mensaje);
            isLoged = true;
        }

    }
    else{
        server.enviar(MSG_WORK);
    }
    updateWorkPage();
    goToTab(WORK);
    isLoged = true;
}


//funcion al presionar el modo creativo
void MainWindow::on_creativeButton_clicked()
{
    if(isConnected){
        server.enviar(MSG_CREATIVE);
        setGameArea();
        goToTab(CREATIVE);
        if(!isLoged)
        {
            QString msg = "para moverse, utilizar las flechas del teclado";
            QMessageBox::information(this,"¿Primera vez?",msg);
            isLoged = true;
        }
    }
}

void MainWindow::updateHome()
{
    if(isConnected){
        ui->creativeButton->setText("CREATIVO");
    }
    else{
        ui->creativeButton->setText("Se necesita conexion");
    }

    ui->creativeButton->setDisabled(!isConnected);
    repaint();
}
