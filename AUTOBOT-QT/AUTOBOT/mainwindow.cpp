#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <coordenadas.h>
#include <QComboBox>
#include <QInputDialog>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QPoint>
#include <QHostAddress>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , appSize(APP_WIDTH,APP_HEIGTH)
    , server()
{
    setMinimumSize(QSize(appSize));
    setMaximumSize(QSize(appSize));
    ui->setupUi(this);
    goToTab(HOME);

    updateHome();

    ui->textoPlano2D->setReadOnly(true);
    ui->textoManual->setReadOnly(true);
    ui->spinAncho->setRange(0,APP_WIDTH);
    ui->spinAncho->setSingleStep(5);

    ui->spinLargo->setRange(0,APP_HEIGTH);
    ui->spinLargo->setSingleStep(5);

    ui->actiondesconectar->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToTab(int tab)
{
    ui->stackedWidget->setCurrentIndex(tab);
}

bool MainWindow::newConnection()
{
    isConnected = server.estaConectado();
    if(isConnected){
        server.setSocket();
        qDebug() <<" se conecto alguien";
        server.enviar(MSG_CONNECTED);
    }
    estado = WAITING;
    return isConnected;
}

void MainWindow::connectionStatus()
{
    isConnected = server.estaConectado();
    if(!isConnected){
        QMessageBox::warning(this,"Usuario desconectado","Se perdio la conexion con el dispositivo");
        estado = DISCONNECTED;
        this->updateHome();
        this->updateWorkPage();
        this->updateManualPage();
        goToTab(HOME);
        ui->actiondesconectar->setDisabled(true);
    }
    else{
      procesarTrama();
    }

}

void MainWindow::btnSalida()
{
    if (estado == RIDE){
        int retVal = QMessageBox::warning(this,"EL AUTO ESTA CORRIENDO",
                             "desea salir de manera forzosa?",
                             QMessageBox::Cancel,QMessageBox::Close);
       if(retVal == QMessageBox::Close){

           if(mode == MODE_PLANO){
               ui->renderArea->reset();
               ui->cantTramosLabel->clear();
               disconnect(ui->renderArea,SIGNAL(valueChanged(int)),this,SLOT(actualizarTramo(int)));
           }
           else{
               updateManualPage();
           }
           server.enviar(MSG_EXIT);
       }
    }
    estado = MENU;
    goToTab(WORK);
}

void MainWindow::timerEvent(QTimerEvent * e)
{
    Q_UNUSED(e);

    if(!isConnected){
        newConnection();
    }
    else{
        ui->actiondesconectar->setDisabled(false);
        connectionStatus();
    }
}




