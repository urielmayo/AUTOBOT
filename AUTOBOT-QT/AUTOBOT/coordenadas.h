#ifndef COORDENADAS_H
#define COORDENADAS_H

#include <QDialog>
#include <QPoint>
#include <server.h>
namespace Ui {
class Coordenadas;
}

class Coordenadas : public QDialog
{
    Q_OBJECT
friend bool connectionStatus(Coordenadas);
public:
    explicit Coordenadas(QWidget *parent = nullptr);
    ~Coordenadas();
    QPoint getPoint() const;
    void setRange(int xRange,int yRange);
    bool retValue();
private slots:
    void on_xSpinBox_valueChanged(int arg1);
    void on_ySpinBox_valueChanged(int arg1);
    void on_buttonBox_accepted();

private:

    enum{
        COORDS,
        CONNECTION,
        WAITING,
    };
    Ui::Coordenadas *ui;
    int xRange, yRange;
    QPoint point;
    bool returned;
};

#endif // COORDENADAS_H
