#include "plano.h"
#include "ui_plano.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

Plano::Plano(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plano)
{
    ui->setupUi(this);
    this->adjustSize();
    connect(this,SIGNAL(destroyed()),this,SLOT(sendWarning()));
}

Plano::~Plano()
{
    delete ui;
}

void Plano::on_finalizarButton_clicked()
{
    if(inProcess){
       crearArchivo();
       inProcess = false;
    }

    ui->renderArea->reset();
    ui->renderArea->repaint();
    QMessageBox::information(this,"FINALIZADO","Su recorrido fue guardado exitosamente");
    emit planoClosed();
}


void Plano::on_cleanButton_clicked()
{
    ui->renderArea->reset();
    ui->renderArea->repaint();
    inProcess = false;
}

void Plano::on_rmvCheckPoint_clicked()
{
    int cantPuntos = ui->renderArea->getNPoints();
    bool retVal;
    if(cantPuntos == 0){
        QMessageBox::information(this,"No hay checkpoints","El mapa esta vacio");
        return;
    }

    int removedPoint = QInputDialog::getInt(this,
                                            "Eliminar Checkpoint",
                                            "Seleccionar:",
                                            1,1,cantPuntos,1,&retVal);

    if(retVal == true){
        inProcess = true;
        ui->renderArea->removePoint(removedPoint);
        ui->renderArea->repaint();
    }
}

void Plano::on_addCheckPoint_clicked()
{
    Coordenadas* ventana = new Coordenadas;
    ventana->setRange(vAncho,vAlto);
    ventana->exec();
    if(ventana->retValue() == true){
        punto = ventana->getPoint();
        ui->renderArea->setPoint(punto);
        ui->renderArea->repaint();
        inProcess = true;
    }
    delete  ventana;
}

void Plano::sendWarning()
{
    emit planoClosed();
}

void Plano::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    if(inProcess){
        QMessageBox* msg = new QMessageBox(this);
        msg->setText("Hay un archivo en proceso");
        msg->setInformativeText("¿Estas seguro de que quiere salir?");
        msg->setStandardButtons(QMessageBox::Cancel|QMessageBox::Save|QMessageBox::Discard);
        int res = msg->exec();

        switch (res) {
        case QMessageBox::Save:

            QMessageBox::information(this,"","Archivo Guardado!");
            delete  msg;
            crearArchivo();
            emit planoClosed();
            this->close();

            break;
        case QMessageBox::Discard:
            emit planoClosed();
            this->close();
            break;

        case QMessageBox::Cancel:
            break;

        default: break;
        }
    }
    else{
        emit planoClosed();
        this->close();
    }

}

void Plano::crearArchivo()
{
    QDir dir(TRACK_DIR);
    fileName.append(".txt");

    QFile file(dir.absoluteFilePath(fileName));

    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        return;
    }
    int cantPoints = ui->renderArea->getNPoints();
    qDebug() << "en crearArchivo(): cantPuntos = "<<cantPoints;
    QPoint points[cantPoints];
    ui->renderArea->completarArchivo(points);
    qDebug() <<"venis bien";

    QTextStream writer(&file);
    writer << vAncho <<";"<<vAlto << "\n";
    for(int i = 0; i < cantPoints; i++)
    {
        qDebug() << points[i].x() << ";" << points[i].y();
        writer << points[i].x() << ";" << points[i].y() << "\n";
    }
    file.close();
}

void Plano::setPlano(int vAncho, int vAlto, QString fileName)
{
    this->vAncho = vAncho;
    this->vAlto = vAlto;
    this->fileName = fileName;

    this->ui->renderArea->setFixedSize(vAncho,vAlto);
    this->setWindowTitle(fileName);
}

void Plano::editarPlano(const QString fileName)
{
    ui->renderArea->abrirPlano(fileName);
    ui->renderArea->getSize(vAncho,vAlto);

    setPlano(vAncho,vAlto,fileName);
    this->ui->mainLayout->setSizeConstraint(QLayout::SetMaximumSize);
}

