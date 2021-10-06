#include "process.h"
#include <QDebug>
Process::Process(QObject *parent):QProcess (parent)
{
    initSignals();
    QString path = QString::fromLocal8Bit(qgetenv("FRP_PATH"));
    QString ini = QString::fromLocal8Bit(qgetenv("FRP_INI"));
    QStringList list;
    list << "-c";
    list << ini;


}

void Process::initSignals()
{
    connect(this, &QProcess::errorOccurred, this, [=](QProcess::ProcessError error){
        if(error == QProcess::FailedToStart)
        {

        }
        else {

        }
        qDebug() << error;
    });

    connect(this, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
          this, [=](int exitCode, QProcess::ExitStatus exitStatus){
        qDebug() << exitCode << exitStatus;
        if(exitStatus == QProcess::NormalExit && exitCode == 0)
        {

        }
        else {

        }
    });

    connect(this, &QProcess::readyReadStandardError, this, [this](){
        m_errorOutput = QString::fromLocal8Bit(readAllStandardError()).trimmed();
        qDebug() << m_errorOutput;
    });

    connect(this, &QProcess::readyReadStandardOutput, this, [this](){
        m_standOutput = QString::fromLocal8Bit(readAllStandardOutput()).trimmed();
        qDebug() << m_standOutput;
        emit setUI(m_standOutput);
    });

    connect(this, &QProcess::started, this, [=](){

    });
}
