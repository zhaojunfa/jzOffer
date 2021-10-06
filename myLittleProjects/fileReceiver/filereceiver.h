#ifndef FILERECEIVER_H
#define FILERECEIVER_H

//class Process;
#include "process.h"
#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>
#include <QSettings>
#include <QDebug>
#include <QTextCursor>
#include <windows.h>
#include <QTcpSocket>
#include <QFile>
#include <QTcpServer>
#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class filereceiver; }
QT_END_NAMESPACE

class filereceiver : public QWidget
{
    Q_OBJECT

public:
    filereceiver(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;
    ~filereceiver();

private:
    Ui::filereceiver *ui;
    Process *pro;
    QMenu *pContextMenu;
    QSystemTrayIcon *systemTray;
    QAction *quitAct;
    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;
    bool isStart;
    //tcp server

    QTimer timer;//定时器

protected:

    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void showWindow();
    void onLogChanged();
private slots:
    void on_push_button_startFrpAndListen_clicked();
    void on_server_New_Connect();
    void on_fileSocket_Connected();
    void on_fileSocket_hostFound();
    void initTCP();
    //void newConnect();
    void connectServer();
    void disconnectServer();
    //void sendData();
    void selectFile();
    void sendFile();
    //更新文件发送进度
    void updateFileProgress(qint64);
    //更新文件接收进度
    void updateFileProgress();
    void on_push_button_selectFiletoSend_clicked();
    void on_push_button_SEND_clicked();

    //2
    void displayError(QAbstractSocket::SocketError socketError);

    void on_push_button_setPathtoSave_clicked();

private:
    QTcpServer *tcpServer;
    QTcpSocket *fileSocket;//send
    ///文件传送
    QFile *localFile;
    ///文件大小
    qint64 totalBytes;      //文件总字节数
    qint64 bytesWritten;    //已发送的字节数
    qint64 bytestoWrite;    //尚未发送的字节数
    qint64 filenameSize;    //文件名字的字节数
    qint64 bytesReceived;   //接收的字节数
    ///每次发送数据大小
    qint64 perDataSize;
    QString filename;
    ///数据缓冲区
    QByteArray inBlock;
    QByteArray outBlock;

    //系统时间
    QDateTime current_date_time;
    QString str_date_time;
};
#endif // FILERECEIVER_H

