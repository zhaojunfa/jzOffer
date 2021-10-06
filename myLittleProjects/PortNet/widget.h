#ifndef WIDGET_H
#define WIDGET_H
class Process;
#include <QWidget>
#include <QItemSelectionModel>
#include "setipdialog.h"
#include "process.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    Process *pro;
    setIPDialog *dialog;
    QStandardItemModel* model;
    QItemSelectionModel *theSelection;//Item选择模型

    QList<QStandardItem*> list1;
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

public slots:

    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
