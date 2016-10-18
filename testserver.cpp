#include "testserver.h"

TestServer::TestServer(int nPort)
{

    m_ptcpSever = new QTcpServer(this);
        if (!m_ptcpSever->listen(QHostAddress::Any, nPort)) {
            printf("Server Error. Unable to start the server:");
            m_ptcpSever->close();
            return;
        }
        connect(m_ptcpSever, SIGNAL(newConnection()),
                this,         SLOT(slotNewConnection())
               );
}

void TestServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpSever->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
           );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );

    sendToClient(pClientSocket, " Server Response: Connected!\n");
}


QDataStream &operator >> (QDataStream &stream, package  &packet)
{
  stream >> packet.package_start;
  stream >> packet.satellite_number;
  stream >> packet.quantity_billing;
  stream >> packet.quantity_PI;
  stream >> packet.quantity_servinfo;
  stream >> packet.quantity_transit;
  return stream;
}

void TestServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_2);
    package packet;
    in >> packet;

    printf("slotReadClient()\n");


}

void TestServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  message;
    QDataStream out(&message, QIODevice::WriteOnly);
    out << str;

    pSocket->write(message);
}
