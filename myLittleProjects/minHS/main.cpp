#include "minhs.h"
#include <windows.h>
#include <QApplication>


bool flag = false;
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

BOOL CALLBACK findXDHelper_button(HWND hwndChild, LPARAM lParam);



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    minHS w;
    w.autoStart();//if autoStart = true;
    w.show();




    return a.exec();
}


BOOL CALLBACK findXDHelper_button(HWND hwndChild){//LPARAM lParam
    int text_length = GetWindowTextLengthW(hwndChild);
    LPWSTR str = new wchar_t[text_length];
    GetWindowTextW(hwndChild,str,text_length);
    QString Qstr = QString::fromWCharArray(str,text_length);
    if( !Qstr.contains("停止")){
        return true;
    }
    return false;
}
