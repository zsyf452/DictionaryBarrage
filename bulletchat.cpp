#include "bulletchat.h"

bulletChat::bulletChat(QString _txt, int _fontSize, int _duration)
{
    qDebug()<<_txt;
    this->txt = new QLabel(_txt,this);
    this->animation = new QPropertyAnimation(this, "pos");

    //让窗口自适应文本大小
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(this->txt);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->setLayout(layout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);





    // 创建一个字体对象
    QFont font;
    font.setPointSize(_fontSize);
    txt->setFont(font);

    // 获取 QFontMetrics 对象
    QFontMetrics fontMetrics(font);
    int textWidth = fontMetrics.horizontalAdvance(txt->text());

    //获取屏幕信息
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenheight = screenGeometry.height();

    srand(QTime::currentTime().msec());
    int high = QRandomGenerator::global()->bounded(screenheight/2);
    qDebug()<<high;



    animation->setDuration(_duration); // 持续时间，根据需要调整
    animation->setStartValue(QPoint(screenWidth, high)); // 起始位置
    animation->setEndValue(QPoint(this->pos().x()-textWidth,high)); // 结束位置
    animation->start();

    style();
    bnding_signal();
    this->show();
}

void bulletChat::style()
{
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);
    // 设置窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    // 设置窗口为透明，鼠标事件可以穿透窗口
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);


}

void bulletChat::bnding_signal()
{
    connect(this->animation, &QPropertyAnimation::finished,this,&bulletChat::animation_end);
}


void bulletChat::animation_end()
{
    qDebug("弹幕销毁");
    delete this;
}

bulletChat::~bulletChat()
{
    delete animation;
}
