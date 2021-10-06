#ifndef HOTKEY_H
#define HOTKEY_H

#include <windows.h>
#include <QAbstractNativeEventFilter>
#include <QKeySequence>
#include <QApplication>
#include <QObject>
#include <QProcess>
#include <QDebug>

class MyWinEventFilter;
class Process;

class MyGlobalShortCut :public QObject
{
    Q_OBJECT
public:

    MyGlobalShortCut(QKeySequence key);
    ~MyGlobalShortCut();
    void activateShortcut();
    bool registerHotKey();
    bool unregisterHotKey();
    QHash<QPair<quint32, quint32>, MyGlobalShortCut*> shortcuts;

private:
    QApplication *m_app;
    MyWinEventFilter *m_filter;
    QKeySequence m_key;
    Qt::Key key;
    Qt::KeyboardModifiers mods;
    static quint32 nativeKeycode(Qt::Key keycode);
    static quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);

signals:

    void activated();

};


class MyWinEventFilter :public QAbstractNativeEventFilter
{
public:

    MyWinEventFilter(MyGlobalShortCut *shortcut);
    ~MyWinEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long*);

private:

    MyGlobalShortCut *m_shortcut;

};

//class Process:
class Process:public QProcess
{
    Q_OBJECT
    enum ADB_EXE_RESULE {
        SECCESS_START,
        ERROR_START,
        SECCESS_EXE,
        ERROR_EXE,
        ERROR_MISSING_BINARY,
    };
public:
    Process(QObject *parent = nullptr);
    void initSignals();
    QString m_errorOutput; //标准错误
    QString m_standOutput; //标准输出

signals:
    void setUI(QString);
};



#endif // HOTKEY_H
