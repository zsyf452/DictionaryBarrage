#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    style();

    this->resourcesList = new QStringList;
    this->watcher = new QFileSystemWatcher;
    //初始化计时器
    this->timer = new QTimer(this);
    //初始化观察文件变化的成员变量
    this->watcher->addPath(RESOURCES_PATH);

    //初始化系统托盘
    tray = new Tray(this);
    Signal_binding();
    readSelectFileName();
    qDebug()<<"数据读取"<<readSelectFileDate(RESOURCES_PATH + this->SelectDataName);

    timer->setInterval(7000);
    timer->start();

    //初始化选址资源列表
    qDebug()<<"文件夹读取"<<readResourcesFolder(this->resourcesList);
    list_resources();
    initSelectFile();


}

void MainWindow::style()
{
    setWindowFlags(windowFlags() &~Qt::WindowMaximizeButtonHint);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    hide(); // 隐藏窗口
    event->ignore(); // 忽略关闭事件
}

void MainWindow::Signal_binding()
{
    connect(this->timer, &QTimer::timeout, this, &MainWindow::Generate_bullet_comments);
    connect(this->watcher,&QFileSystemWatcher::directoryChanged,this,[this](){
        qDebug()<<"文件夹读取"<<this->readResourcesFolder(this->resourcesList);
        this->list_resources();
    });
}


void MainWindow::Generate_bullet_comments()
{

    srand(QTime::currentTime().msec());
    int subscript = QRandomGenerator::global()->bounded(this->TextDate.size());
    bulletChat *t = new bulletChat(this->TextDate[subscript],20,20000);
}

bool MainWindow::readResourcesFolder(QStringList *sl)
{
    QDir dir(RESOURCES_PATH);
    if(!dir.exists())
        return false;
    *sl = dir.entryList(QDir::Files);
    return true;
}

bool MainWindow::readSelectFileDate(QString path)
{
    qDebug()<<"当前数据是"<<path;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    TextDate.clear();//清空之前的数据
    while (!in.atEnd()) {
        QString line = in.readLine();
        TextDate.push_back(line);
    }

    file.close();
    return true;

}

bool MainWindow::initSelectFile()
{
    for(int i = 0;i<this->ui->fileDate->count();i++)
    {
        QLayoutItem *item = this->ui->fileDate->itemAt(i);
        QCheckBox *t = qobject_cast<QCheckBox *>(item->widget());
        if(t && this->SelectDataName == t->text())
        {
            t->setChecked(true);
            return true;
        }
    }
    return false;
}


bool MainWindow::readSelectFileName()
{
    QFile file(SELECT_DATE_NAME);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream in(&file);
    in >> this->SelectDataName;
    file.close();
}

bool MainWindow::wirteSelectFileName(QString name)
{
    QFile file(SELECT_DATE_NAME);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out<<name;
    file.close();
    return true;
}

void MainWindow::list_resources()
{
    //删除之前已存在控件
    QLayoutItem *item;
    while ((item = this->ui->fileDate->takeAt(0)))
    {
        if (item->widget())
        {
            delete item->widget(); // 删除控件
        }
        delete item; // 删除布局项
    }

    //更新现在控件
    for(int i=0;i<this->resourcesList->size();i++)
    {
        QCheckBox *date = new QCheckBox;
        date->setText(resourcesList->at(i));
        // date->text()
        this->ui->fileDate->addWidget(date);
        connect(date,&QCheckBox::clicked,this,&MainWindow::HandlingClickEvents);
    }


}

void MainWindow::HandlingClickEvents()
{

    // 获取发出信号的 QCheckBox
    QCheckBox *clickedCheckBox = qobject_cast<QCheckBox *>(sender());

    if (clickedCheckBox)
    {

        QLayoutItem *item;
        for(int i=0;i<this->ui->fileDate->count();i++)
        {
            item = this->ui->fileDate->itemAt(i);
            QCheckBox *t = qobject_cast<QCheckBox *>(item->widget());
            if(t && t != clickedCheckBox)
                t->setChecked(false);
        }
        // 确保点击的 QCheckBox 保持选中状态
        clickedCheckBox->setChecked(true);
        this->SelectDataName = clickedCheckBox->text();
        this->wirteSelectFileName(clickedCheckBox->text());
        qDebug()<<"数据读取"<<readSelectFileDate(RESOURCES_PATH + this->SelectDataName);
    }
}

MainWindow::~MainWindow()
{
    delete tray;
    delete this->timer;
    delete ui;
}
