#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <vector>
#include <QString>
#include <string>
#include <fstream>
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
    //计时器
    QTimer *timer;

    //数据
    std::vector<std::string> TextDate;

protected:
    void Signal_binding();

public:
    MainWindow(QWidget *parent = nullptr);
    //生成弹幕
    void Generate_bullet_comments();
    bool readFile(std::string path);
    ~MainWindow();
};
#endif // MAINWINDOW_H
