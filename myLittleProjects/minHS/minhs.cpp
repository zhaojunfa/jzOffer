#include <windows.h>
#include <pthread.h>

#include "minhs.h"
#include "ui_minhs.h"
extern bool flag;
extern pthread_mutex_t mutex;
minHS::minHS(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::minHS)
{
    this->thread=0;
    //setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
    setWindowFlags(windowFlags()&~Qt::WindowStaysOnBottomHint);
    setWindowFlags(windowFlags()&~Qt::WindowCloseButtonHint);
    //w.setWindowFlags(w.windowFlags() &~ Qt::WindowMinMaxButtonsHint);
    setFixedSize(362,400);                     // 禁止拖动窗口大
    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(QIcon(":/joy.ico"));
    systemTray->setToolTip("XG's Tools");
    shortCut = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_N),
                             this);
    //
    minimumAct = new QAction("Minimum Window", this);
    //Note the differences between hide() and showMinimized().
    connect(minimumAct, SIGNAL(triggered()), this, SLOT(hide()));
    maximumAct = new QAction("Maximum Window", this);
    connect(maximumAct, SIGNAL(triggered()), this, SLOT(showMaximized()));
    restoreAct = new QAction("Restore Window", this);
    connect(restoreAct, SIGNAL(triggered()), this, SLOT(showNormal()));
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
    connect(systemTray, &QSystemTrayIcon::activated, this, &minHS::activeTray);//点击托盘，执行相应的动作
    //connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &minHS::showWindow);//点击消息框，显示主窗口

    connect(shortCut,&QShortcut::activated,this,&minHS::onShortCut);
    //this->ui->push_button_stop->setEnabled(false);
    ui->setupUi(this);
}

minHS::~minHS()
{
    delete ui;
    //    systemTray->setVisible(false);

    delete pContextMenu;
    delete systemTray;
    delete minimumAct;
    delete maximumAct;
    delete restoreAct;
    delete quitAct;
    delete shortCut;
}

void minHS::closeEvent(QCloseEvent *event)
{
    if(systemTray->isVisible())
    {
        hide();
        //systemTray->showMessage("233", "The program is running behind.");
        event->ignore();
    }
}

void minHS::autoStart()
{
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,1);

    //    this->ui->lineEdit->setText("Finding Window..");
    //    qApp->processEvents();
    //    //Sleep(1500);
    pthread_create(&auto_start_pthread_t,&attr,minHS::auto_start_thread,(void *)this);
    Sleep(1000);

}

void *minHS::func(void* cur){

    //((minHS*)cur)->ui->push_button_start->setEnabled(false);
    while (::flag) {
        Sleep(1000);
        HWND hwnd_zhanwang = FindWindowW(NULL, L"战网");
        Sleep(1000);
        HWND hwnd_lushi = FindWindowW(NULL, L"炉石传说");
        Sleep(1000);
        HWND hwnd_xd = FindWindowW(NULL, L"Hearthbuddy【TS正式版 v1.7】");
        Sleep(1000);
        HWND hwnd_zhongkong = FindWindowW(NULL,L"HearthbuddyHelper——已启动");
        Sleep(1000);
        HWND hwnd_qq_news = FindWindowW(NULL,L"腾讯网迷你版");
        Sleep(1000);
        if(hwnd_qq_news)
            ShowWindow(hwnd_qq_news,SW_HIDE);
        //DestroyWindow(hwnd);
        int count = 0;
        if(hwnd_zhanwang){
            if(!::flag)
            {
                ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
                qApp->processEvents();
                Sleep(1000);
                return nullptr;
            }
            if(!IsIconic(hwnd_zhanwang)){
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE Battle.net.exe");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                ShowWindow(hwnd_zhanwang, SW_MINIMIZE);
                Sleep(1500);
            }
            else{
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE Battle.net.exe(-1)");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                Sleep(1500);
            }
        }
        if(hwnd_lushi){
            if(!::flag)
            {
                ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
                qApp->processEvents();
                Sleep(1000);
                return nullptr;
            }
            if(!IsIconic(hwnd_lushi)){
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE Hearthstone.exe");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                ShowWindow(hwnd_lushi, SW_MINIMIZE);
                Sleep(1500);
            }
            else{
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE Hearthstone.exe(-1)");//don't minimize this window
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                Sleep(1500);
            }

        }
        if(hwnd_xd){
            if(!::flag)
            {
                ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
                qApp->processEvents();
                Sleep(1000);
                return nullptr;
            }
            if(!IsIconic(hwnd_xd)){
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE HSbuddy.exe");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                ShowWindow(hwnd_xd, SW_MINIMIZE);
                Sleep(1500);
            }
            else{
                //                ShowWindow(hwnd_xd, SW_MINIMIZE);
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE HSbuddy.exe(-1)");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                Sleep(1500);
            }
        }
        if(hwnd_zhongkong){
            if(!::flag)
            {
                ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
                qApp->processEvents();
                Sleep(1000);
                return nullptr;
            }
            if(!IsIconic(hwnd_zhongkong)){
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE HSbuddyHelper.exe");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                ShowWindow(hwnd_zhongkong, SW_MINIMIZE);
                Sleep(1500);
            }
            else{
                //                ShowWindow(hwnd_zhongkong, SW_MINIMIZE);
                ((minHS*)cur)->ui->lineEdit->setText("MINIMIZE HSbuddyHelper.exe(-1)");
                //((minHS*)cur)->ui->lineEdit->repaint();
                qApp->processEvents();
                ++count;
                Sleep(1500);
            }
        }
        if(count == 4){
            int i = 300;
            //ShowWindow(FindWindowW(NULL,L"minHS"),SW_MINIMIZE);
            for(;i>=0;--i){
                if(::flag){
                    ((minHS*)cur)->ui->lineEdit->setText(QString("All Done, Next Try..(%1)").arg(i));
                    qApp->processEvents();
                    Sleep(1000);
                }
                else{
                    ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
                    qApp->processEvents();
                    Sleep(1000);
                    return nullptr;
                }
            }
        }
        else{
            int i = 60;
            for(;i>=0;--i){
                if(!::flag)
                {
                    ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
                    qApp->processEvents();
                    Sleep(1000);
                    return nullptr;
                }

                ((minHS*)cur)->ui->lineEdit->setText(QString("Retrying..(%1)").arg(i));
                qApp->processEvents();
                Sleep(1000);
            }
        }

    }
    ((minHS*)cur)->ui->lineEdit->setText("Stopped.");
    qApp->processEvents();
    Sleep(1000);
    return ((void*)0);
}

void *minHS::auto_start_thread(void *arg)
{
    //    this->ui->lineEdit->setText("Finding Window..");
    //    qApp->processEvents();
    //    //Sleep(1500);
    for(int i=6;i>=0;--i){
        if(!::flag){
            ((minHS*)arg)->ui->lineEdit->setText(QString("Not running.%1").arg(i));
            qApp->processEvents();
        }
        else//running
            break;
        Sleep(1000);
    }
    if(!::flag){
        ((minHS*)arg)->ui->push_button_start->click();
        //        flag = true;
        //        pthread_attr_init(&((minHS*)arg)->attr);
        //        pthread_attr_setdetachstate(&((minHS*)arg)->attr,1);
        //        ((minHS*)arg)->ui->lineEdit->setText("Finding Window..");
        //        qApp->processEvents();
        //       // ((minHS*)arg)->ui->push_button_start->setEnabled(false);//wrong
        //        Sleep(500);
        //        pthread_create(&((minHS*)arg)->thread,&((minHS*)arg)->attr,minHS::func,arg);
        //        Sleep(1000);
    }
    return nullptr;
}

void minHS::on_push_button_stop_clicked()
{
    //ting zhi "yiqidong"

    //
}

void minHS::on_push_button_start_clicked()
{
    //this->ui->push_button_start->setEnabled(false);

    if(this->ui->push_button_start->text().contains("START")){
        flag = true;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,1);
        this->ui->lineEdit->setText("Finding Window..");
        qApp->processEvents();
        //Sleep(1500);
        this->ui->push_button_start->setText("STOP");
        //this->ui->push_button_stop->setEnabled(true);
        pthread_create(&thread,&attr,minHS::func,(void *)this);
        Sleep(1000);
    }
    else{
        flag = false;
        if(thread){
            //pthread_kill(thread,0);
            //pthread_cancel(thread);
            //this->ui->push_button_stop->setEnabled(false);
            this->ui->lineEdit->setText("Stop watching..");
            qApp->processEvents();
            Sleep(1000);
            this->ui->push_button_start->setText("START");
            //this->ui->push_button_start->setEnabled(true);
            //        HWND hd = FindWindowW(NULL,L"minHS");
            //        if(hd){
            //            ShowWindow(hd,SW_MINIMIZE);
            //        }

        }
        else{
            Sleep(500);
        }
    }

}


void minHS::on_pushButton_clicked()//start
{


}

void minHS::on_pushButton_start_clicked()
{


}

void minHS::activeTray(QSystemTrayIcon::ActivationReason reason)
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

void minHS::showWindow()
{
    if(this->isHidden())
        this->show();
    else
        this->hide();
}

void minHS::on_push_button_MINIMIZE_Self_clicked()
{
    this->hide();
}

void minHS::onShortCut()
{
    this->show();
}

void minHS::on_push_button_restore_HS_clicked()
{
    HWND hwnd_lushi = FindWindowW(NULL, L"炉石传说");
    if(this->ui->push_button_restore_HS->text().contains("Restore")){
        ShowWindow(hwnd_lushi,SW_RESTORE);
        this->ui->push_button_restore_HS->setText("Minimize\nHearthstone");
    }
    else{
        ShowWindow(hwnd_lushi,SW_MINIMIZE);
        this->ui->push_button_restore_HS->setText("Restore\nHearthstone");
    }
}
