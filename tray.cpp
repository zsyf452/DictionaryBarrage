#include "tray.h"

Tray::Tray(QMainWindow *myW):myWindow(myW)
{
    trayIcon = new QSystemTrayIcon(myWindow);
    trayIcon->setIcon(QIcon(":/icon/TrayIcon.png")); // 设置图标
    // 创建托盘图标的菜单
    QMenu *trayMenu = new QMenu(myWindow);
    quitAction = new QAction("Quit", myWindow);


    trayMenu->addAction(quitAction);

    signal_binding();

    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
}

void Tray::signal_binding()
{
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Tray::onTrayIconActivated);

}

void Tray::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case  QSystemTrayIcon::DoubleClick:
            this->myWindow->show();
            break;
        default:
            break;
    }
}
