#include <QCoreApplication>
#include <testserver.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestServer server(2323);
    return a.exec();
}
