#include "server.h"
#include <QTextStream>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractSocket>
Server::Server(QObject *parent) : QTcpServer(parent)
{
    serverSocket = nullptr;
    connect(this,&Server::newConnection,[&](){serverSocket = nextPendingConnection();});

}

void Server::enviar(const QString &msj)
{
    if(serverSocket){
        sendMsg.append("$");
        sendMsg.append(msj);
        sendMsg.append("#");
        QTextStream T(serverSocket);
        T << sendMsg;
        serverSocket->flush();
        sendMsg.clear();
    }
    sendMsg.clear();
}

bool Server::estaConectado()const
{
    return (serverSocket != nullptr);
}

QString Server::getMsg()
{
    if(newMsg == true){
        newMsg = false;
        return recivedMessage;
    }
    else return "";
}

QTcpSocket * Server::getSocket() const
{
    return this->serverSocket;
}

void Server::setSocket()
{
    connect(serverSocket,SIGNAL(readyRead()),this,SLOT(sockRcv()));
    connect(serverSocket,SIGNAL(disconnected()),this,SLOT(socketDisconnected()));
}

void Server::disconnectSocket()
{
    serverSocket->close();
    serverSocket = nullptr;
}

void Server::socketDisconnected()
{
    serverSocket->close();
    serverSocket = nullptr;
}

void Server::sockRcv()
{
    QTextStream Ts(serverSocket);
    recivedMessage = (QString)Ts.readLine();
    if(recivedMessage == "\0"){
        recivedMessage = "";
    }
    serverSocket->flush();
    newMsg = true;
}
