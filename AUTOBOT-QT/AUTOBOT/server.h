#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

//mensajes enviados por el servidor
#define MSG_CONNECTED "CONNECTED"
#define MSG_START "START"
#define MSG_STOP "STOP"
#define MSG_WORK "WORK"
#define MSG_CREATIVE "CREAT"
#define MSG_EXIT "EXIT"
#define MSG_MENU "MENU"
#define MSG_CONTINUE "CONTINUE"
#define MSG_UP "U"
#define MSG_RIGHT "R"
#define MSG_DOWN "D"
#define MSG_LEFT "L"
#define MSG_UP_STOP "!U"
#define MSG_RIGHT_STOP "!R"
#define MSG_DOWN_STOP "!D"
#define MSG_LEFT_STOP "!L"

class QTcpSocket;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void enviar(const QString & msj);
    bool estaConectado() const;
    QString getMsg();
    QTcpSocket *getSocket() const;
    void setSocket();
    void disconnectSocket();


private slots:
    void socketDisconnected();
    void sockRcv();

private:
    QTcpSocket * serverSocket;
    QString recivedMessage, sendMsg;
    bool newMsg;
};

#endif // SERVER_H
