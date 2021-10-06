#ifndef SCSHOT_H
#define SCSHOT_H


#include "hotkey.h"
#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>
#include <QShortcut>
#include <QDateTime>
#include <QScreen>
#include <windows.h>
#include <QSettings>
#include <QDebug>
#include <QTextCursor>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>
#include <QTcpServer>//监听套接字

QT_BEGIN_NAMESPACE
namespace Ui { class ScShot; }
QT_END_NAMESPACE

class ScShot : public QWidget
{
    Q_OBJECT

public:
    ScShot(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override;
    ~ScShot();

private slots:
    void onActivated();//system tray
    void onLogChanged();//ui->textEdit_log
    void on_push_button_sent_clicked();//todo
    void on_push_button_select_socket_1_clicked();//1
    void on_push_button_select_socket_2_clicked();//1
    void on_push_button_select_socket_3_clicked();//1
    void on_push_button_lock_all_clicked();//1
    void on_push_button_startFrpAndListen_clicked();//1
    void serverHasNewConnect();//1
    void fileSocketConnected();//1
    void fileSocketHostFound();//1
    void initTCP();//1
    void connectServer();
    void disconnectServer();
    void sendFile();
    void updateFileProgress(qint64);
    void updateFileProgress();
    void displayError(QAbstractSocket::SocketError socketErrot);

private:
    Ui::ScShot *ui;
    //QKeySequence keySequence;
    MyGlobalShortCut *shortcut;
    QMenu *pContextMenu;
    QSystemTrayIcon *systemTray;
    QAction *quitAct;
    //socket
    QTcpServer *tcpServer;
    QTcpSocket *fileSocket;
    QFile *localFile;
    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytestoWrite;
    qint64 filenameSize;
    qint64 bytesReceived;
    qint64 perDataSize;
    QString filename;
    //buffer
    QByteArray inBlock;
    QByteArray outBlock;
    //system date
    QDateTime current_date_time;
    QString str_date_time;
    //
    QTimer timer;
    bool isStart;
    Process *pro;


protected:
    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void showWindow();
};
#endif // SCSHOT_H
