#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_VELOCITY 20
#define APP_WIDTH 900
#define APP_HEIGTH 800
#include <QMainWindow>
#include <QTcpSocket>
#include "coordenadas.h"
#include "plano.h"
#include "server.h"
#define PORT 3566
#define WAIT_TIME 100
#define TRACK_DIR "../tracks"
//#define TRACK_DIR "../tracks"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //trabajo.cpp

        //PAGINA TRABAJO
        void on_workHomeButtoon_clicked();
        void on_crear2D_clicked();
        void on_spinAncho_valueChanged(int arg1);
        void on_spinLargo_valueChanged(int arg1);
        void on_repetirUltTrayectoButton_clicked();
        void on_realizarHistorialButton_clicked();
        void on_editarButton_clicked();
        void on_historial_currentRowChanged(int currentRow);
        void on_runManualButton_clicked();

        //pagina PLANO
        void on_planoFinishButton_clicked();
        void on_planoStartButton_clicked();

        //pagina MANUAL
        void on_StopContinueButton_clicked();
        void on_InitRideButton_clicked();
        void on_manualHomeButton_clicked();

    //home.cpp
    void on_wrkBotton_clicked();
    void on_creativeButton_clicked();

    //actions.cpp
    void on_actiondesconectar_triggered();
    void on_actionconectar_triggered();

    //creativo.cpp
    void on_speedSlider_valueChanged(int value);
    void on_speedDial_valueChanged(int value);
    void on_creativeExitButton_clicked();

    void deletePlano();
    void actualizarTramo(int tramo);
    void on_pushButton_clicked();

private://atributos
    Ui::MainWindow *ui;

    bool isConnected = false;
    bool anchoFilled = false, altoFilled = false;
    bool isLoged = false;
    bool inProcess = false;

    QPoint punto;
    QSize appSize;
    QString fileName;

    int vAncho, vAlto;
    int estado = WAITING;
    int mode;
    int timerId;
    int file_row = -1;

    Server server;
    Plano * plano;
    Coordenadas* cord = nullptr;
    QTimer * timer;

protected:
    void timerEvent(QTimerEvent *);
    void keyPressEvent(QKeyEvent *input);
    void keyReleaseEvent(QKeyEvent * input);

private://metodos
    void goToTab(int tab);
    void updateWorkPage();
    void updateManualPage();
    void setGameArea();
    void cargarHistorial();
    void procesarTrama();
    QString getHistorialSelectedFile();
    void updateHome();
    bool newConnection();
    void connectionStatus();
    void btnSalida();

    //PAGINAS DEL WIDGET
    enum{
        HOME=0,
        WORK,
        CREATIVE,
        MANUAL,
        CORRIENDO
    };
    //ESTADOS DE CONEXION
    enum{
        DISCONNECTED = 0,
        WAITING,
        MENU,
        PRE_RIDE_PLANO,
        PRE_RIDE_START,
        RIDE,
        STOP
    };
    //MODOS DE CORRER EL AUTO EN MODO TRABAJO
    enum{
        MODE_PLANO,
        MODE_NORMAL
    };

};
#endif // MAINWINDOW_H
