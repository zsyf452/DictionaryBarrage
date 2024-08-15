#include "outlinedlabel.h"

OutlinedLabel::OutlinedLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);

    this->outlineColor = new QColor(255,255,255);
    this->fontColor = new QColor(0,0,0);
}

OutlinedLabel::OutlinedLabel(const QString &text,QColor outlineC,QColor fontColor,QWidget *parent):QLabel(text, parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);

    this->outlineColor = new QColor(outlineC);
    this->fontColor = new QColor(fontColor);
}


void OutlinedLabel::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);

    QFontMetrics fm(font());
    int textWidth = fm.horizontalAdvance(text());
    int textHeight = fm.height();

    // 中心位置
    int x = (width() - textWidth) / 2;
    int y = (height() + textHeight) / 2 - fm.descent();

    // 设置描边颜色
    QPen pen(*this->outlineColor);
    pen.setWidth(2 );  // 描边宽度，可以调整大小
    painter.setPen(pen);

    // 绘制描边，通过多个方向的偏移实现粗描边效果
    painter.drawText(x - 1 , y - 1, text());
    painter.drawText(x - 1, y + 1, text());
    painter.drawText(x + 1, y - 1, text());
    painter.drawText(x + 1, y + 1, text());

    // 设置字体颜色
    painter.setPen(*this->fontColor);
    painter.drawText(x, y, text());
}

OutlinedLabel::~OutlinedLabel()
{
    delete this->fontColor;
    delete this->outlineColor;
}
