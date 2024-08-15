#ifndef TRAY_H
#define TRAY_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QMainWindow>

class Tray:public QObject
{
    Q_OBJECT
private:
    QMainWindow *myWindow;
    //托盘
    QSystemTrayIcon *trayIcon;
    //退出选项
    QAction *quitAction;
public:
    Tray(QMainWindow *myW);
    void signal_binding();
    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // TRAY_H
