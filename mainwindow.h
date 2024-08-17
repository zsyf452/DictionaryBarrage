#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QString>
#include <qdir.h>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QFileSystemWatcher>
#include <QCloseEvent>
#include <QPushButton>


#include "option/barragesettings.h"
#include "option/shortcutkeyssettings.h"
#include "option/option.h"
#include "tray.h"
#include "bulletchat.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    option *opt;

    //快捷键
    ShortcutKeysSettings *SKS;
    ShortcutKeys *SK;

    //是否开启弹幕
    bool isOpen_BulletChat = true;
    BarrageSettings *BS;

    //系统托盘
    Tray *tray;

    //计时器
    QTimer *timer;

    //选中数据的名称
    QString SelectDataName;

    //资源列表
    QStringList *resourcesList;
    //观察资源文件是否出现变动
    QFileSystemWatcher *watcher;
    //数据
    std::vector<QString> TextDate;
    bool isTextDateEmpty = false;

protected:
    void Signal_binding();
    //绑定热键
    void bindHotkey();
    void closeEvent(QCloseEvent *event) override;


public:
    MainWindow(QWidget *parent = nullptr);

    //窗口样式
    void style();

    //生成弹幕
    void Generate_bullet_comments();
    //设置弹幕状态(开启或关闭)
    void set_BulletChatState();
    //读取资源文件夹里面的文件名称
    bool readResourcesFolder(QStringList *sl);
    //读选中文件的数据
    bool readSelectFileDate(QString path);
    //初始化选中文件
    bool initSelectFile();
    //读取选中的文件名称
    bool readSelectFileName();
    //写入选中的文件名称
    bool wirteSelectFileName(QString name);
    //列出资源
    void list_resources();
    //处理资源文件控件点击事件
    void HandlingClickEvents();
    ~MainWindow();
};
#endif // MAINWINDOW_H
