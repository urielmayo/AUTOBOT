#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderarea.h"
#include <QFile>
#include <QTextStream>
#include <QPoint>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>

void MainWindow::updateWorkPage()
{
    ui->repetirUltTrayectoButton->setDisabled(!isConnected);
    ui->realizarHistorialButton->setDisabled(!isConnected);
    ui->historial->setDisabled(!isConnected);
    ui->editarButton->setDisabled(!isConnected);
    ui->runManualButton->setDisabled(!isConnected);

    if(isConnected){
        ui->disconectedFlag->clear();
        ui->disconectedFlag_2->clear();
    }

    if(anchoFilled && altoFilled){
        ui->crear2D->setDisabled(false);
        ui->crear2D->setText("crear");
    }
    else{
        ui->crear2D->setDisabled(true);
        ui->crear2D->setText("ingresar alto y ancho");
    }
    ui->historial->clear();
    cargarHistorial();
}

void MainWindow::updateManualPage()
{
    ui->InitRideButton->setDisabled(false);
    ui->StopContinueButton->setText("STOP");
}


void MainWindow::cargarHistorial()
{
    QDir trackDir(TRACK_DIR);
    qDebug() <<trackDir.absolutePath();
    QStringList tracks = trackDir.entryList();
    for(int i = 0; i < tracks.size(); i++)
    {
        if((tracks[i] != "." ) && (tracks[i] != "..")){
            tracks[i].remove(".txt");
            ui->historial->insertItem(i,tracks[i]);
        }
    }
}

QString MainWindow::getHistorialSelectedFile()
{
    return ui->historial->currentItem()->text();
}

//-------------------------------------------------------------------------------------------------
//SLOTS PAGINA TRABAJO-----------------------------------------------------------------------------

//funcion al presionar la flacha para volver al inicio MODIFICAR
void MainWindow::on_workHomeButtoon_clicked()
{
    server.enviar(MSG_MENU);
    goToTab(HOME);
}

//funcion para crear plano 2D
void MainWindow::on_crear2D_clicked()
{
    bool retVal;
    fileName = QInputDialog::getText(this,"Guardado","Nombre: ",QLineEdit::Normal,"",&retVal);

    if(retVal == true){
        if(fileName.isEmpty()){
            QMessageBox::warning(this,"ATENCION","No se ingreso nada, intentar de nuevo.");
        }
        else{
            plano = new Plano;
            plano->setPlano(vAncho,vAlto,fileName);
            plano->show();
            connect(plano,SIGNAL(planoClosed()),this,SLOT(deletePlano()));
        }
    }
}

//funcion para crear el plano manualmente
void MainWindow::on_runManualButton_clicked()
{
    mode = MODE_NORMAL;
    goToTab(MANUAL);
}

void MainWindow::on_spinAncho_valueChanged(int arg1)
{
    anchoFilled = (arg1 != 0);
    vAncho = arg1;
    updateWorkPage();

}

void MainWindow::on_spinLargo_valueChanged(int arg1)
{
    altoFilled = (arg1 != 0);
    vAlto = arg1;
    updateWorkPage();
}

void MainWindow::on_repetirUltTrayectoButton_clicked()
{
    goToTab(CORRIENDO);
    mode = MODE_PLANO;
}


//esta funcion corre el plano seleccionado en la lista de planos
void MainWindow::on_realizarHistorialButton_clicked()
{
    QString fileToOpen;
    fileToOpen = getHistorialSelectedFile();
    fileToOpen.append(".txt");

    ui->renderArea->abrirPlano(fileToOpen);
    goToTab(CORRIENDO);
    estado = MENU;
    mode = MODE_PLANO;
}

//esta funcion manda a editar el plano seleccionado en el historial
void MainWindow::on_editarButton_clicked()
{
    fileName = ui->historial->currentItem()->text();
    fileName.append(".txt");

    plano = new Plano;
    plano->editarPlano(fileName);
    //ui->renderArea->getSize(vAncho,vAlto);
    //ui->labelNombre->setText(fileName);
    //goToTab(PLANO);
}


//este funcion se llama cuando el usuario cambia el trayecto elegido en la lista
void MainWindow::on_historial_currentRowChanged(int currentRow)
{
    this->file_row = currentRow;
    qDebug() << file_row;

    if(file_row != -1){
        ui->realizarHistorialButton->setFlat(false);
        ui->realizarHistorialButton->setDisabled(false);
        ui->editarButton->setFlat(false);
        ui->editarButton->setDisabled(false);
    }
    else{
        ui->realizarHistorialButton->setFlat(true);
        ui->realizarHistorialButton->setDisabled(true);
        ui->editarButton->setFlat(true);
        ui->editarButton->setDisabled(true);
    }
}

//-------------------------------------------------------------------------------------------------
//SLOTS PAGINA MANUAL


void MainWindow::on_InitRideButton_clicked()
{
    server.enviar(MSG_START);
    estado = PRE_RIDE_START;
}

void MainWindow::on_StopContinueButton_clicked()
{
    if(estado == RIDE){
        if(ui->StopContinueButton->text() == "STOP"){
            server.enviar(MSG_STOP);
            qDebug() << "mensaje enviado";
            estado = STOP;
        }
    }

    else if (estado == STOP){
        if(ui->StopContinueButton->text() == "CONTINUAR"){
            qDebug() << "mensaje enviado";
            server.enviar(MSG_CONTINUE);
            estado = STOP;
         }
    }

}

void MainWindow::on_manualHomeButton_clicked()
{
    btnSalida();
}

//-------------------------------------------------------------------------------------------------
//SLOTS PAGINA PLANO

void MainWindow::on_planoStartButton_clicked()
{
    server.enviar(MSG_START);
    estado = PRE_RIDE_PLANO;
}

void MainWindow::on_planoFinishButton_clicked()
{
    server.enviar(MSG_EXIT);
    ui->renderArea->reset();
    goToTab(WORK);
}

void MainWindow::on_pushButton_clicked()
{
    btnSalida();
}

void MainWindow::actualizarTramo(int tramo)
{
    ui->cantTramosLabel->setText(QString::number(tramo));
}
