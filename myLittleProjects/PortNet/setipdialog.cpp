#include "setipdialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

setIPDialog::setIPDialog(QWidget *parent):QDialog (parent)
{
    this->setWindowTitle("添加规则");
    QLabel *label_1 = new QLabel("本地IP");
    QLabel *label_2 = new QLabel("本地端口");
    QLabel *label_3 = new QLabel("公网IP");
    QLabel *label_4 = new QLabel("公网server端口");
    QLabel *label_5 = new QLabel("远程访问端口");
    QLabel *label_6 = new QLabel("type");
    box = new QComboBox(this);
    QStringList boxlist;
    boxlist << "tcp" << "udp" << "http" << "https";
    box->addItems(boxlist);

    QPushButton *ok_button = new QPushButton("确定");
    QPushButton *cancel_button = new QPushButton("取消");
    this->connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(slot_accepttok()));
    this->connect(cancel_button,SIGNAL(clicked(bool)),this,SLOT(close()));

    line1 = new QLineEdit("127.0.0.1",this);
    line2 = new QLineEdit("10086",this);
    line3 = new QLineEdit(this);
    line4 = new QLineEdit("7000",this);
    line5 = new QLineEdit("6666",this);
    glayout = new QGridLayout(this);

    glayout->addWidget(label_1,0,0);
    glayout->addWidget(line1,0,1);
    glayout->addWidget(label_2,1,0);
    glayout->addWidget(line2,1,1);

    glayout->addWidget(label_3,2,0);
    glayout->addWidget(line3,2,1);
    glayout->addWidget(label_4,3,0);
    glayout->addWidget(line4,3,1);

    glayout->addWidget(label_5,4,0);
    glayout->addWidget(line5,4,1);

    glayout->addWidget(label_6,5,0);
    glayout->addWidget(box,5,1);

    glayout->addWidget(ok_button,6,0);
    glayout->addWidget(cancel_button,6,1);
}

void setIPDialog::slot_accepttok()
{
    emit sendIPport(line1->text(),line2->text(),line3->text(),line4->text(),line5->text(),box->currentText());
    this->close();
}
