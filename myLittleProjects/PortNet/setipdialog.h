#ifndef SETIPDIALOG_H
#define SETIPDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QStandardItemModel>
class setIPDialog:public QDialog
{
    Q_OBJECT
public:
    setIPDialog(QWidget *parent = nullptr);

    QString ip;
    QString port;
    QString netport;

    QList<QStandardItem*> list;

    QLineEdit *line1;
    QLineEdit *line2;
    QLineEdit *line3;
    QLineEdit *line4;
    QLineEdit *line5;
    QComboBox *box;
    QGridLayout *glayout;
signals:
    void sendIPport(QString,QString,QString,QString,QString,QString);

public slots:
    void slot_accepttok();
};

#endif // SETIPDIALOG_H
