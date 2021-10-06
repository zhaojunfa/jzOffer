//#include "hotkey.h"
#include "scshot.h"
#include <QApplication>
#include <QTextCodec>


int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    qputenv("FRP_PATH","..\\fileReceiver\\frp_0.37.0_windows_amd64\\frpc.exe");
    qputenv("FRP_INI","..\\fileReceiver\\frp_0.37.0_windows_amd64\\frpc.ini");
    QApplication a(argc, argv);
    ScShot w;
    w.show();



    return a.exec();
}
