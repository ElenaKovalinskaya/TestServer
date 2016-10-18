#ifndef TESTSERVER_H
#define TESTSERVER_H
#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <iostream>

struct package{
    quint8 package_start;
    quint8 satellite_number;
    quint64 quantity_billing;
    quint64 quantity_PI;
    quint64 quantity_servinfo;
    quint64 quantity_transit;
};

class TestServer : public QObject{
Q_OBJECT
private:
    QTcpServer* m_ptcpSever;
    quint32     m_nNextBlockSize;
private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    TestServer(int nPort);
public slots:
     virtual void slotNewConnection();
     void slotReadClient();

};

#endif // TESTSERVER_H
