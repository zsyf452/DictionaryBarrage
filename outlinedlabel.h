#ifndef OUTLINEDLABEL_H
#define OUTLINEDLABEL_H

#include <QLabel>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

#include "option/barragesettings.h"

class OutlinedLabel:public QLabel
{
    Q_OBJECT
private:
    BarrageSettings BS;
public:
    OutlinedLabel(const QString &text, BarrageSettings _BS, QWidget *parent = nullptr);


    void paintEvent(QPaintEvent *event) override;

    ~OutlinedLabel();
};

#endif // OUTLINEDLABEL_H
