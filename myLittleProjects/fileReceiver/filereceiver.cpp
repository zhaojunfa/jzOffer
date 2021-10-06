#include "filereceiver.h"
#include "ui_filereceiver.h"


filereceiver::filereceiver(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::filereceiver)
    , totalBytes(0)
    , bytesWritten(0)
    , bytestoWrite(0)
    , filenameSize(0)
    , bytesReceived(0)
    , perDataSize(64 * 1024)
{
    setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
    setWindowFlags(windowFlags()&~Qt::WindowStaysOnBottomHint);
    //setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint);
    //w.setWindowFlags(w.windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    setFixedSize(366,288);
    ui->setupUi(this);
    //this->setWindowTitle("端口映射");
    //this->setWindowIcon(QIcon(":/pic/frp/title.png"));
    pro = new Process(this);
    connect(pro,&Process::setUI,this,[=](QString Uitext){
        //ui->textEdit->setTextColor(Qt::yellow);
        //ui->textEdit->append(Uitext);
        ui->lineEdit_log->append(Uitext);
        //qApp->processEvents();

    });
    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(QIcon(":/dlam.ico"));
    systemTray->setToolTip("file Receiver and Sender");
    quitAct = new QAction("Quit", this);
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    pContextMenu = new QMenu(this);
    //pContextMenu->addAction(minimumAct);
    //pContextMenu->addAction(maximumAct);
    //pContextMenu->addAction(restoreAct);
    //pContextMenu->addSeparator();
    pContextMenu->addAction(quitAct);
    systemTray->setContextMenu(pContextMenu);
    systemTray->show();
    connect(systemTray, &QSystemTrayIcon::activated, this, &filereceiver::activeTray);
    connect(ui->lineEdit_log,&QTextEdit::textChanged,this,&filereceiver::onLogChanged);
    //connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &minHS::showWindow);//点击消息框，显示主窗口
    this->initTCP();
}

void filereceiver::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

filereceiver::~filereceiver()
{
    //todo
    delete pro;
    delete pContextMenu;
    delete systemTray;
    delete quitAct;
    delete ui;
}

void filereceiver::activeTray(QSystemTrayIcon::ActivationReason reason)
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

void filereceiver::showWindow()
{
    if(this->isHidden())
        this->show();
    else
        this->hide();
}

void filereceiver::onLogChanged()
{
    ui->lineEdit_log->moveCursor(QTextCursor::End);
}


void filereceiver::on_push_button_startFrpAndListen_clicked()//'START'
{
    if(ui->push_button_startFrpAndListen->text().contains("STOP")){
        ui->lineEdit_log->append("close frp..");
        qApp->processEvents();
        Sleep(500);
        QString cmd = "TASKKILL /F /IM frpc.exe";
        WinExec(cmd.toLocal8Bit().data(), SW_HIDE);
        //pro->kill();

        //        ui->lineEdit_log->setTextColor(Qt::red);
        ui->lineEdit_log->append("close tcpServer..");
        qApp->processEvents();
        Sleep(500);
        tcpServer->close();
        ui->lineEdit_log->append("close fileSocket..");
        qApp->processEvents();
        Sleep(500);
        if(fileSocket)
            fileSocket->close();
        ui->lineEdit_log->append("CLOSED.");
        qApp->processEvents();
        Sleep(500);
        ui->push_button_startFrpAndListen->setText("START");
    }
    else{
        //start linsten:::
        //
        //tcpServer = new QTcpServer();
        ui->lineEdit_log->append(QString("Listen %1:%2..").arg(ui->lineEdit_local_ipaddr->text()).arg(ui->lineEdit_local_port->text()));
        qApp->processEvents();
        Sleep(400);
        //2 listen 127.0.0.1:port
        quint16 port = ui->lineEdit_local_port->text().toUShort();
        tcpServer->listen(QHostAddress::Any, port);
        //3.

        ui->lineEdit_log->append("TCP server started.");
        qApp->processEvents();
        Sleep(400);
        ui->lineEdit_log->append("read frpc.ini..");
        qApp->processEvents();
        Sleep(400);
        QSettings settings("..\\fileReceiver\\frp_0.37.0_windows_amd64\\frpc.ini", QSettings::IniFormat); // 当前目录的INI文件
        //QStringList lsit = settings.allKeys();
        settings.beginGroup("common");
        settings.setValue("server_addr", "155.94.228.8");//199689.xyz or 155.94.228.8
        settings.setValue("server_port", "7000");
        settings.setValue("privilege_token","xg6666");
        settings.endGroup();

        settings.beginGroup(QString("TCP_FILE_SERVER_%1").arg(ui->lineEdit_local_port->text()));
        settings.setValue("privilege_mode","true");
        settings.setValue("type","tcp");
        settings.setValue("local_ip", ui->lineEdit_local_ipaddr->text());//127.0.0.1
        settings.setValue("local_port", ui->lineEdit_local_port->text());//
        settings.setValue("remote_port", ui->lineEdit_local_port->text());
        settings.setValue("custom_domains","www.199689.xyz");
        settings.endGroup();
        //list1.clear();
//        for(int i=3000;i<=65535;++i){
//            settings.beginGroup(QString("TCP_openwrt_tcp_%1").arg(i));
//            settings.setValue("privilege_mode","true");
//            settings.setValue("type","tcp");
//            settings.setValue("local_ip", ui->lineEdit_local_ipaddr->text());//127.0.0.1
//            settings.setValue("local_port", QString("%1").arg(i));//
//            settings.setValue("remote_port", QString("%1").arg(i));
//            settings.setValue("custom_domains","www.199689.xyz");
//            settings.endGroup();
//            settings.beginGroup(QString("TCP_openwrt_udp_%1").arg(i));
//            settings.setValue("privilege_mode","true");
//            settings.setValue("type","udp");
//            settings.setValue("local_ip", ui->lineEdit_local_ipaddr->text());//127.0.0.1
//            settings.setValue("local_port", QString("%1").arg(i));//
//            settings.setValue("remote_port", QString("%1").arg(i));
//            settings.setValue("custom_domains","www.199689.xyz");
//            settings.endGroup();
//        }



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
        //ui->push_button_startFrpAndListen->setEnabled(0);
        //qDebug()<<"frp started\n";
    }

}

void filereceiver::on_server_New_Connect()
{
    bytesWritten = 0;
    //每次发送数据大小为64kb
    perDataSize = 64*1024;
    fileSocket->abort();
    fileSocket = tcpServer->nextPendingConnection();

}

void filereceiver::on_fileSocket_Connected()
{
    ui->lineEdit_log->append("Connected.");
    qApp->processEvents();
    Sleep(400);
}

void filereceiver::on_fileSocket_hostFound()
{
    ui->lineEdit_log->append("Host found.");
    qApp->processEvents();
    Sleep(400);
}

void filereceiver::initTCP()
{
    this->fileSocket = new QTcpSocket(this);
    this->tcpServer = new QTcpServer();
    connect(tcpServer,&QTcpServer::newConnection,this,&filereceiver::on_server_New_Connect);
    connect(fileSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateFileProgress(qint64)));
    connect(fileSocket,SIGNAL(readyRead()),this,SLOT(updateFileProgress()));
    connect(fileSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError socketError)));
    connect(fileSocket,SIGNAL(hostFound()),this,SLOT(on_fileSocket_hostFound()));//0k
    connect(fileSocket,SIGNAL(connected()),this,SLOT(on_fileSocket_Connected()));//??
}

//1.connect to a server
//2.send file

void filereceiver::connectServer()
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

void filereceiver::disconnectServer()
{
    fileSocket->close();
    ui->lineEdit_log->append("fileSocket closed.");
    qApp->processEvents();
    Sleep(500);
}

void filereceiver::selectFile()
{
    //    fileSocket->abort();
    //    this->fileSocket = new QTcpSocket(this);
    //    QString ip = ui->lineEdit_remote_ipaddr->text();
    //    quint16 port = ui->lineEdit_remote_port->text().toUInt();
    //    fileSocket->connectToHost(ip,port);
    //    connect(fileSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(updateFileProgress(qint64)));
    //    connect(fileSocket,SIGNAL(readyRead()),this,SLOT(updateFileProgress()));

    fileSocket->open(QIODevice::WriteOnly);

    //this->ui.progressBar->setValue(0);
    this->filename = QFileDialog::getOpenFileName(this,"Open a file","/","files (*)");
    ui->lineEdit_filePath_selected_file_path->setText(filename);
}

void filereceiver::sendFile()
{
    bytesWritten = 0;
    this->localFile = new QFile(filename);
    if(!localFile->open(QFile::ReadOnly))
    {
        ui->lineEdit_log->append("Client:open file error,cannot send file..");
        qApp->processEvents();
        Sleep(500);
        return;
    }
    ///获取文件大小
    this->totalBytes = localFile->size();
    QDataStream sendout(&outBlock,QIODevice::WriteOnly);
    sendout.setVersion(QDataStream::Qt_5_9);
    QString currentFileName = filename.right(filename.size()-filename.lastIndexOf('/')-1);
    qDebug()<<sizeof(currentFileName);
    //保留总大小信息空间、文件名大小信息空间、文件名
    sendout<<qint64(0)<<qint64(0)<<currentFileName;
    totalBytes += outBlock.size();
    sendout.device()->seek(0);
    sendout<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));

    bytestoWrite = totalBytes-fileSocket->write(outBlock);
    outBlock.resize(0);
}

void filereceiver::updateFileProgress(qint64 numBytes)//send
{
    // 已经发送的数据大小
    bytesWritten += (int)numBytes;

    //如果已经发送了数据
    if(bytestoWrite > 0)
    {
        outBlock = localFile->read(qMin(bytestoWrite,perDataSize));
        ///发送完一次数据后还剩余数据的大小
        bytestoWrite -= ((int)fileSocket->write(outBlock));
        ///清空发送缓冲区
        outBlock.resize(0);
    }
    else
        localFile->close();

    //更新进度条
    //this->ui.progressBar->setMaximum(totalBytes);
    //this->ui.progressBar->setValue(bytesWritten);
    ui->lineEdit_log->append(QString("sending %1/%2..").arg(bytesWritten*2).arg(totalBytes*2));
    qApp->processEvents();
    //Sleep(500);
    //如果发送完毕
    if(bytesWritten == totalBytes)
    {
        ui->lineEdit_log->append(QString("send succeed."));
        qApp->processEvents();
        Sleep(500);
        localFile->close();
        //fileSocket->close();
    }
}

void filereceiver::updateFileProgress(){
    QDataStream inFile(this->fileSocket);
    inFile.setVersion(QDataStream::Qt_5_9);

    //如果接收到的数据小于16个字节，保存到来的文件头结构
    if(bytesReceived <= sizeof(qint64)*2)
    {
        this->ui->lineEdit_log->append("receive file header..");
        qApp->processEvents();
        Sleep(500);
        if((fileSocket->bytesAvailable()>=(sizeof(qint64))*2) && (filenameSize==0))
        {
            inFile>>totalBytes>>filenameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((fileSocket->bytesAvailable()>=filenameSize) && (filenameSize != 0))
        {
            inFile>>filename;
            bytesReceived += filenameSize;
            QString dir = ui->lineEdit_filePath_to_save->text();
            filename = dir+"/"+filename;//maybe changed
            localFile = new QFile(filename);
            if(!localFile->open(QFile::WriteOnly))
            {
                qDebug()<<"Server::create file error!";
                return;
            }
        }
        else
            return;
    }
    //如果接收的数据小于总数据，则写入文件
    if(bytesReceived < totalBytes)
    {
        bytesReceived += fileSocket->bytesAvailable();
        inBlock = fileSocket->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
        this->ui->lineEdit_log->append(QString("receive file %1/%2..").arg(bytesReceived*2).arg(totalBytes*2));
        qApp->processEvents();
        Sleep(500);
    }

    //数据接收完成时
    if(bytesReceived == totalBytes)
    {
        this->ui->lineEdit_log->append("receive file successfully!");
        qApp->processEvents();
        Sleep(500);
        //todo windows right-down news
        bytesReceived = 0;
        totalBytes = 0;
        filenameSize = 0;
        localFile->close();
        //fileSocket->close();
    }

}

void filereceiver::on_push_button_selectFiletoSend_clicked()
{
    filereceiver::selectFile();
    ui->push_button_SEND->setEnabled(1);
}

void filereceiver::on_push_button_SEND_clicked()
{
    ui->push_button_SEND->setEnabled(0);
    connectServer();
    sendFile();
    ui->push_button_SEND->setEnabled(1);

}


void filereceiver::displayError(QAbstractSocket::SocketError socketError)
{
    QString errInfo = fileSocket->errorString() + QString("==>SocketError num =%1").arg(socketError);
    ui->lineEdit_log->append(errInfo);
    qApp->processEvents();
    Sleep(500);
    qDebug()<<fileSocket->errorString();
    fileSocket->close();
}

void filereceiver::on_push_button_setPathtoSave_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_filePath_to_save->setText(dir);
}
