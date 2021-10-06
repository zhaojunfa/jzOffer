#include "widget.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    qputenv("FRP_PATH","..\\PortNet\\frp\\frpc.exe");
    qputenv("FRP_INI","..\\PortNet\\frp\\frpc.ini");
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
