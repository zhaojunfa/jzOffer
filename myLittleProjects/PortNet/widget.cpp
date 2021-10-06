#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QDebug>
#include <QSettings>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("端口映射");
    this->setWindowIcon(QIcon(":/pic/frp/title.png"));
    ui->pushButton->setEnabled(0);
    ui->pushButton_2->setEnabled(0);
    setFixedSize(this->width(),this->height());
    model = new QStandardItemModel(this);
    model->setColumnCount(6);
    model->setHeaderData(0,Qt::Horizontal, "本地IP");
    model->setHeaderData(1,Qt::Horizontal, "本地端口");
    model->setHeaderData(2,Qt::Horizontal, "公网IP");
    model->setHeaderData(3,Qt::Horizontal, "公网server端口");
    model->setHeaderData(4,Qt::Horizontal, "远程访问端口");
    model->setHeaderData(5,Qt::Horizontal, "type");
    model->setRowCount(0);

    theSelection = new QItemSelectionModel(model);//Item选择模型
   // theSelection->setModel(model);
    connect(theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));

    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(theSelection);//设置选择模型
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //tabelview中选取一整行
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    pro = new Process(this);
    connect(pro,&Process::setUI,this,[=](QString Uitext){
        ui->textEdit->setTextColor(Qt::yellow);
        ui->textEdit->append(Uitext);

    });

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_3_clicked()
{
    dialog = new setIPDialog();
    connect(dialog,&setIPDialog::sendIPport,this,[=](QString ip,QString port,QString netIP,QString netport,QString remoteport,QString type){
          QList<QStandardItem*> list;

          list << new QStandardItem(ip)<< new QStandardItem(port) << new QStandardItem(netIP)
               <<new QStandardItem(netport) << new QStandardItem(remoteport) << new QStandardItem(type);

          for(int i = 0;i < list.count();i++)
          {
              list.at(i)->setTextAlignment(Qt::AlignCenter);
             // list.at(i)->setTextAlignment()
          }
          model->insertRow(0,list);


    });
    dialog->exec();
}

void Widget::on_pushButton_clicked()
{
    ui->pushButton_2->setEnabled(1);
    QSettings settings("..\\PortNet\\frp\\frpc.ini", QSettings::IniFormat); // 当前目录的INI文件
    QStringList lsit = settings.allKeys();
//        //GPS setting
    settings.beginGroup("common");
    settings.setValue("server_addr", list1.at(2)->text());
    settings.setValue("server_port", list1.at(3)->text());
    settings.endGroup();

    settings.beginGroup("ssh");
    settings.setValue("type", list1.at(5)->text());
    settings.setValue("local_ip", list1.at(0)->text());
    settings.setValue("local_port", list1.at(1)->text());
    settings.setValue("remote_port", list1.at(4)->text());
    settings.endGroup();
    //list1.clear();

    QString path = QString::fromLocal8Bit(qgetenv("FRP_PATH"));
    QString ini = QString::fromLocal8Bit(qgetenv("FRP_INI"));
    QStringList list;
    list << "-c";
    list << ini;
    pro->start(path,list);
    ui->pushButton->setEnabled(0);
}



void Widget::on_pushButton_2_clicked()
{
    pro->close();
    ui->textEdit->setTextColor(Qt::red);
    ui->textEdit->append("=============服务停止=============");
  //  list1.clear();
    ui->pushButton->setEnabled(1);
}

void Widget::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    list1.clear();
    if (current.isValid() && list1.count() == 0) //当前模型索引有效
    {
        for (int column = 0; column < model->columnCount(); column++) {
              QStandardItem *item = model->item(current.row(), column);
              list1 << item;
          }
    }
    ui->pushButton->setEnabled(1);

}
