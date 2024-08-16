#include "outlinedlabel.h"

OutlinedLabel::OutlinedLabel(const QString &text, BarrageSettings _BS, QWidget *parent)
    : QLabel(text, parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);

    this->BS = _BS;
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
    QPen pen(this->BS.return_StrokeColor_value());
    painter.setPen(pen);

    // 绘制描边，通过多个方向的偏移实现粗描边效果
    painter.drawText(x - this->BS.return_FontStrokeWidth_value() , y - this->BS.return_FontStrokeWidth_value(), text());
    painter.drawText(x - this->BS.return_FontStrokeWidth_value(), y + this->BS.return_FontStrokeWidth_value(), text());
    painter.drawText(x + this->BS.return_FontStrokeWidth_value(), y - this->BS.return_FontStrokeWidth_value(), text());
    painter.drawText(x + this->BS.return_FontStrokeWidth_value(), y + this->BS.return_FontStrokeWidth_value(), text());

    // 设置字体颜色
    painter.setPen(this->BS.return_fontColor_value());
    painter.drawText(x, y, text());
}

OutlinedLabel::~OutlinedLabel()
{
}
