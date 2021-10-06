#include "scshot.h"
//#include "hotkey.h"
#include "ui_scshot.h"

ScShot::ScShot(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScShot)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
    setWindowFlags(windowFlags()&~Qt::WindowStaysOnBottomHint);
    //setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint);
    //w.setWindowFlags(w.windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    setFixedSize(362,359);                     // 禁止拖动窗口大
    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(QIcon(":/joy.ico"));
    systemTray->setToolTip("ScreenShot Tool");
    quitAct = new QAction("Quit", this);
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    pContextMenu = new QMenu(this);
    //pContextMenu->addAction(minimumAct);
    //pContextMenu->addAction(maximumAct);
    //pContextMenu->addAction(restoreAct);
    //pContextMenu->addSeparator();
    pContextMenu->addAction(quitAct);
    systemTray->setContextMenu(pContextMenu);
    //
    systemTray->show();
    connect(systemTray, &QSystemTrayIcon::activated, this, &ScShot::activeTray);//点击托盘，执行相应的动作
    //connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &minHS::showWindow);//点击消息框，显示主窗口
    QKeySequence keySequence=QKeySequence("ALT+B");//设置快捷键ALT+B
    this->shortcut = new MyGlobalShortCut(keySequence);
    connect(shortcut,SIGNAL(activated()),this,SLOT(onActivated()));
    connect(ui->lineEdit_log,&QTextEdit::textChanged,this,&ScShot::onLogChanged);

}

void ScShot::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略不结束进程
    this->hide();  // 隐藏界面
}

ScShot::~ScShot()
{
    delete shortcut;
    delete ui;
}


void ScShot::onActivated()
{
    //this->hide();
    this->ui->push_button_sent->click();
    //全局热键被激活之后要做的事

}

void ScShot::onLogChanged()
{
    ui->lineEdit_log->moveCursor(QTextCursor::End);
}

void ScShot::activeTray(QSystemTrayIcon::ActivationReason reason)
{

    switch (reason)
    {
    case QSystemTrayIcon::Context:
        //showMenu();
        break;
    case QSystemTrayIcon::DoubleClick:
        showWindow();
        break;
    case QSystemTrayIcon::Trigger:
        showWindow();
        break;
    case QSystemTrayIcon::MiddleClick:
        showWindow();
        break;
    default:
        showWindow();
    }

}

void ScShot::showWindow()
{

    if(this->isHidden())
        this->show();
    else
        this->hide();

}

void ScShot::on_push_button_sent_clicked()
{
    //take a shot
    this->ui->lineEdit_log->append("Take a screen shot..");
    qApp->processEvents();
    Sleep(1000);
    QScreen *screen = QGuiApplication::primaryScreen();
    QString filePathName = "fullScreen-";
    auto time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");//-zzz
    filePathName += time;
    filePathName += ".bmp";
    if(!screen->grabWindow(0).save(filePathName, "bmp",99))
    {
        this->ui->lineEdit_log->append("Save screen failed.");
        qApp->processEvents();
        Sleep(1000);
    }else
    {
        this->ui->lineEdit_log->append(QString("%1\nsaved.").arg(time+".bmp"));
        qApp->processEvents();
        Sleep(1000);
    }
    //
}

void ScShot::on_push_button_select_socket_1_clicked()
{
    QString str = ui->push_button_select_socket_1->text();
    if(str.contains("ON"))
        ui->push_button_select_socket_1->setText("state:\nOFF");
    else
        ui->push_button_select_socket_1->setText("state:\nON");
}

void ScShot::on_push_button_select_socket_2_clicked()
{
    QString str = ui->push_button_select_socket_2->text();
    if(str.contains("ON"))
        ui->push_button_select_socket_2->setText("state:\nOFF");
    else
        ui->push_button_select_socket_2->setText("state:\nON");
}

void ScShot::on_push_button_select_socket_3_clicked()
{
    QString str = ui->push_button_select_socket_3->text();
    if(str.contains("ON"))
        ui->push_button_select_socket_3->setText("state:\nOFF");
    else
        ui->push_button_select_socket_3->setText("state:\nON");
}

void ScShot::on_push_button_lock_all_clicked()
{
    QString str = ui->push_button_lock_all->text();
    if(str.contains("Unlock")){
        ui->push_button_select_socket_1->setEnabled(1);
        ui->push_button_select_socket_2->setEnabled(1);
        ui->push_button_select_socket_3->setEnabled(1);
        ui->push_button_lock_all->setText("Lock\nButtons");
    }
    else{
        ui->push_button_select_socket_1->setEnabled(0);
        ui->push_button_select_socket_2->setEnabled(0);
        ui->push_button_select_socket_3->setEnabled(0);
        ui->push_button_lock_all->setText("Unlock\nButtons");
    }

}

void ScShot::on_push_button_startFrpAndListen_clicked()
{
    if(ui->push_button_startFrpAndListen->text().contains("STOP")){
        ui->lineEdit_log->append("close frp..");
        qApp->processEvents();
        Sleep(500);
        this->pro->kill();
        //close tcpServer
        ui->lineEdit_log->append("close tcpServer..");
        qApp->processEvents();
        Sleep(500);
        this->tcpServer->close();
        //close fileSocket
        ui->lineEdit_log->append("close fileSocket..");
        qApp->processEvents();
        Sleep(500);
        fileSocket->close();
        //change button's text
        ui->lineEdit_log->append("CLOSED.");
        qApp->processEvents();
        Sleep(500);
        ui->push_button_startFrpAndListen->setText("START");
    }
    else{
        //start tcpServer
        ui->lineEdit_log->append(QString("listen %1:%2..")
                                 .arg(ui->lineEdit_local_ipaddr->text())
                                 .arg(ui->lineEdit_local_port->text()));
        qApp->processEvents();
        Sleep(500);
        QString local_addr = ui->lineEdit_local_ipaddr->text();
        quint16 port = ui->lineEdit_local_port->text().toUInt();
        tcpServer->listen(QHostAddress(local_addr),port);
        //log==> started.
        ui->lineEdit_log->append("TCP server started.");
        qApp->processEvents();
        Sleep(500);
        //log==> read frpc.ini
        ui->lineEdit_log->append("read frp.ini ..");
        qApp->processEvents();
        Sleep(500);
        //
        QSettings settings("..\\scshot\\frp_0.37.0_windows_amd64\\frpc.ini", QSettings::IniFormat); // 当前目录的INI文件
        //QStringList lsit = settings.allKeys();
        settings.beginGroup("common");
        settings.setValue("server_addr", "155.94.228.8");//199689.xyz or 155.94.228.8
        settings.setValue("server_port", "7000");
        settings.setValue("privilege_token","xg6666");
        settings.endGroup();

        settings.beginGroup(QString("TCP_FILE_SERVER_%1").arg(ui->lineEdit_local_port->text()));
        settings.setValue("privilege_mode ","true");
        settings.setValue("type","tcp");
        settings.setValue("local_ip", ui->lineEdit_local_ipaddr->text());//127.0.0.1
        settings.setValue("local_port", ui->lineEdit_local_port->text());//
        settings.setValue("remote_port", ui->lineEdit_local_port->text());
        settings.setValue("custom_domains","www.199689.xyz");
        settings.endGroup();
        //list1.clear();

        QString path = QString::fromLocal8Bit(qgetenv("FRP_PATH"));
        QString ini = QString::fromLocal8Bit(qgetenv("FRP_INI"));
        QStringList list;
        list << "-c";
        list << ini;
        pro->start(path,list);
        ui->lineEdit_log->append("start frpc..");
        qApp->processEvents();
        Sleep(500);
        ui->push_button_startFrpAndListen->setText("STOP");
    }
}

void ScShot::serverHasNewConnect()
{
    bytesWritten = 0;
    //每次发送数据大小为64kb
    perDataSize = 64*1024;
    fileSocket->abort();
    fileSocket = tcpServer->nextPendingConnection();
}

void ScShot::fileSocketConnected()
{
    ui->lineEdit_log->append("Connected.");
    qApp->processEvents();
    Sleep(400);
}

void ScShot::fileSocketHostFound()
{
    ui->lineEdit_log->append("Host found.");
    qApp->processEvents();
    Sleep(400);
}

void ScShot::initTCP()
{
    this->fileSocket = new QTcpSocket(this);
    this->tcpServer = new QTcpServer();
    connect(tcpServer,&QTcpServer::newConnection,this,&ScShot::serverHasNewConnect);
    connect(fileSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateFileProgress(qint64)));
    connect(fileSocket,SIGNAL(readyRead()),this,SLOT(updateFileProgress()));
    connect(fileSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError socketError)));
    connect(fileSocket,SIGNAL(hostFound()),this,SLOT(fileSocketHostFound()));
    connect(fileSocket,SIGNAL(connected()),this,SLOT(fileSocketConnected()));
}

void ScShot::connectServer()
{
    ui->lineEdit_log->append(QString("connect %1:%2..")
                             .arg(ui->lineEdit_remote_ipaddr->text())
                             .arg(ui->lineEdit_remote_port->text()));

    qApp->processEvents();
    Sleep(400);
    fileSocket->abort();
    QString ip = ui->lineEdit_remote_ipaddr->text();
    quint16 port = ui->lineEdit_remote_port->text().toUInt();
    fileSocket->connectToHost(ip,port);//!timeOut???
    auto connected = fileSocket->waitForConnected(1000 * 5);
    if(connected)
        qDebug()<<"connected.";
}
























