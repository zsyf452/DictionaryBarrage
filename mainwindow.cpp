#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化计时器
    this->timer = new QTimer(this);

    Signal_binding();
    readFile("resources/cz.txt");

    timer->setInterval(7000);
    timer->start();


}

void MainWindow::Signal_binding()
{
    connect(this->timer, &QTimer::timeout, this, &MainWindow::Generate_bullet_comments);
}


void MainWindow::Generate_bullet_comments()
{

    srand(QTime::currentTime().msec());
    int subscript = QRandomGenerator::global()->bounded(this->TextDate.size());
    bulletChat *t = new bulletChat(QString::fromStdString(this->TextDate[subscript]),20,20000);
}

bool MainWindow::readFile(std::string path)
{
    std::ifstream ifs(path,std::ios::in);
    if(!ifs.is_open())
        return false;
    std::string temp;
    while(std::getline(ifs,temp))
        this->TextDate.push_back(temp);



    return true;
}

MainWindow::~MainWindow()
{
    delete this->timer;
    delete ui;
}
