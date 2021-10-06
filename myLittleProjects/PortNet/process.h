#ifndef qPROCESS_H
#define qPROCESS_H

#include <QProcess>

class Process:public QProcess
{
    Q_OBJECT
    enum ADB_EXE_RESULE {
        SECCESS_START,
        ERROR_START,
        SECCESS_EXE,
        ERROR_EXE,
        ERROR_MISSING_BINARY,
    };
public:
    Process(QObject *parent = nullptr);
    void initSignals();
    QString m_errorOutput; //标准错误
    QString m_standOutput; //标准输出

signals:
    void setUI(QString);
};

#endif



