#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


void MainWindow::on_actionconectar_triggered()
{
    if(!isConnected){
        if(!server.isListening()){
            if(server.listen(QHostAddress(QHostAddress::Any),3566) == false){
                QMessageBox::warning(this,"ERROR",server.errorString());
            }
            else{
                qDebug() <<"servidor conectado";
                timerId = startTimer(100);
                ui->actionconectar->setDisabled(false);

            }
        }
    }
    else{
        QMessageBox::warning(this,"ATNECION","ya hay un dispositivo conectado");
    }
}

void MainWindow::on_actiondesconectar_triggered()
{
    if(server.estaConectado()){
        server.disconnectSocket();
        ui->actiondesconectar->setDisabled(true);
    }
}
