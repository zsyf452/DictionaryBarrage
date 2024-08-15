#ifndef OUTLINEDLABEL_H
#define OUTLINEDLABEL_H

#include <QLabel>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

class OutlinedLabel:public QLabel
{
    Q_OBJECT
private:
    QColor *outlineColor;
    QColor *fontColor;
    short *outlineWidth;
public:
    OutlinedLabel(const QString &text, QWidget *parent = nullptr);
    OutlinedLabel(const QString &text,QColor outlineC,QColor fontColor,QWidget *parent = nullptr);
    OutlinedLabel(const QString &text,short outlineWidth,QColor outlineC,QColor fontColor,QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    ~OutlinedLabel();
};

#endif // OUTLINEDLABEL_H
