#ifndef PLANO_H
#define PLANO_H

#include <QWidget>
#include "coordenadas.h"
namespace Ui {
class Plano;
}

class Plano : public QWidget
{
    Q_OBJECT

public:
    explicit Plano(QWidget *parent = nullptr);
    ~Plano();

private slots:
    void on_finalizarButton_clicked();
    void on_cleanButton_clicked();
    void on_rmvCheckPoint_clicked();
    void on_addCheckPoint_clicked();

    void sendWarning();

private: // atributos
    void closeEvent(QCloseEvent * event);
    Ui::Plano *ui;
    Coordenadas * ventana;
    int vAncho, vAlto;
    QPoint punto;
    bool inProcess;
    QString fileName;

        //metodos
    void crearArchivo();

public:
    void setPlano(int vAncho, int vAlto,QString fileName);
    void editarPlano(const QString fileName);

signals:
    void planoClosed();
};

#endif // PLANO_H
