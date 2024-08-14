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
#include "bulletchat.h"

#define RESOURCES_PATH "resources/"
#define OPTION_PATH "option/"
#define SELECT_DATE_NAME OPTION_PATH "SelectDateName.txt"

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

protected:
    void Signal_binding();


public:
    MainWindow(QWidget *parent = nullptr);
    void show();
    //生成弹幕
    void Generate_bullet_comments();
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
