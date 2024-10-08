#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "outlinedlabel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    style();
    this->opt = new option;
    //快捷键
    this->SKS = new ShortcutKeysSettings;
    this->BS = new BarrageSettings;
    this->resourcesList = new QStringList;
    this->watcher = new QFileSystemWatcher;
    // opt->show();

    //初始化计时器
    this->timer = new QTimer(this);
    //初始化观察文件变化的成员变量
    this->watcher->addPath(RESOURCES_PATH);
    //初始化弹幕属性
    opt->read_barrage_configuration_information(this->BS);
    //初始化快捷键
    opt->read_Shortcut_keys(this->SKS);
    this->SK = new ShortcutKeys(SKS->return_enableBarrage().toString());
    //初始化系统托盘
    tray = new Tray(this);
    Signal_binding();

    readSelectFileName();
    qDebug()<<"数据读取"<<readSelectFileDate(RESOURCES_PATH + this->SelectDataName);
    timer->setInterval(7000);

    this->isOpen_BulletChat = this->BS->return_isAutoBarrageEnabled_value();
    set_BulletChatState();


    //初始化选址资源列表
    qDebug()<<"文件夹读取"<<readResourcesFolder(this->resourcesList);
    list_resources();
    initSelectFile();


}

void MainWindow::style()
{
    this->setWindowIcon(QIcon(":/resources/icon/TrayIcon.png"));

    setWindowFlags(windowFlags() &~Qt::WindowMaximizeButtonHint);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    hide(); // 隐藏窗口
    event->ignore(); // 忽略关闭事件
}

void MainWindow::Signal_binding()
{
    connect(this->ui->option,&QPushButton::clicked,this->opt,&option::show);

    connect(this->timer, &QTimer::timeout, this, &MainWindow::Generate_bullet_comments);
    connect(this->watcher,&QFileSystemWatcher::directoryChanged,this,[this](){
        qDebug()<<"文件夹读取"<<this->readResourcesFolder(this->resourcesList);
        this->list_resources();
    });
    connect(this->ui->switchButton,&QPushButton::clicked,this,[this](){
        this->isOpen_BulletChat = !this->isOpen_BulletChat;//取反
        set_BulletChatState();
    });

    //快捷键
    bindHotkey();


    connect(this->opt,&option::updateBarragesSettings,this,[this](){
        qDebug()<<"弹幕数据更新";
        this->opt->read_barrage_configuration_information(this->BS);
    });
    connect(this->opt,&option::updateShortcutKeysSettings,this,[this](){
        qDebug()<<"快捷键数据更新";
        this->opt->read_Shortcut_keys(this->SKS);
        qDebug()<<this->SKS->return_enableBarrage();
        this->SK->return_enableBarrage()->resetShortcut();
        this->SK->return_enableBarrage()->setShortcut(this->SKS->return_enableBarrage(),true);
        // this->SK->return_enableBarrage()->setNativeShortcut()
        // bindHotkey();
    });
}

void MainWindow::bindHotkey()
{
    connect(this->SK->return_enableBarrage(),&QHotkey::activated,this,[this](){
        this->isOpen_BulletChat = !this->isOpen_BulletChat;//取反
        set_BulletChatState();
    });
}


void MainWindow::Generate_bullet_comments()
{
    if(this->isTextDateEmpty == false)
        return;

    srand(QTime::currentTime().msec());
    int subscript = QRandomGenerator::global()->bounded(this->TextDate.size());

    bulletChat *t = new bulletChat(this->TextDate[subscript],*this->BS);
}

void MainWindow::set_BulletChatState()
{
    if(this->isOpen_BulletChat)
    {
        this->ui->switchButton->setText("开");
        this->timer->start();
    }
    else
    {
        this->ui->switchButton->setText("关");
        this->timer->stop();
    }
    qDebug()<<"弹幕:"<<this->ui->switchButton->text();
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
    {
        this->isTextDateEmpty = false;
        return false;
    }



    QTextStream in(&file);
    TextDate.clear();//清空之前的数据
    while (!in.atEnd())
    {
        QString line = in.readLine();
        TextDate.push_back(line);
    }

    file.close();
    this->isTextDateEmpty = true;
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


    // 获取文件信息
    QFileInfo fileInfo(file);
    QDir dir = fileInfo.absoluteDir();

    // 检查目录是否存在，如果不存在则创建
    if (!dir.exists())
    {
        if (!dir.mkpath("."))
        {
            qDebug() << "文件夹不存在" << dir.absolutePath();
            return false;
        }
    }

    // 检查文件是否存在
    if (!file.exists())
    {
        qDebug() << "文件不存在:" << SELECT_DATE_NAME;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() <<"文件打开失败"<< SELECT_DATE_NAME;
        return false;
    }

    QTextStream in(&file);
    in >> this->SelectDataName;
    file.close();
    return true;
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
