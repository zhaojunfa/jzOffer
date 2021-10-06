#ifndef MINHS_H
#define MINHS_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QCloseEvent>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class minHS; }
QT_END_NAMESPACE

class minHS : public QWidget
{
    Q_OBJECT

public:
    minHS(QWidget *parent = nullptr);
    static void *func(void *);
    static void *auto_start_thread(void *);
    ~minHS();
    void closeEvent(QCloseEvent *event);
    void autoStart();

private slots:


    void on_pushButton_clicked();

    void on_push_button_stop_clicked();

    void on_push_button_start_clicked();

    void on_pushButton_start_clicked();

    void on_push_button_MINIMIZE_Self_clicked();

    void onShortCut();

    void on_push_button_restore_HS_clicked();

public:
    Ui::minHS *ui;
    pthread_t thread,auto_start_pthread_t;
    pthread_attr_t attr;

    QMenu *pContextMenu;
    QSystemTrayIcon *systemTray;
    QAction *minimumAct;
    QAction *maximumAct;
    QAction *restoreAct;
    QAction *quitAct;
    QShortcut *shortCut;

protected:

    void activeTray(QSystemTrayIcon::ActivationReason reason);
    void showWindow();


};
#endif // MINHS_H
