#ifndef BULLETCHAT_H
#define BULLETCHAT_H


#include <QDialog>
#include <QLabel>
#include <QPropertyAnimation>
#include <QString>
#include <QGuiApplication>
#include <QScreen>
#include <ctime>
#include <QTime>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QFontMetrics>
#include "outlinedlabel.h"
#include "option/barragesettings.h"

class bulletChat:public QDialog
{
     Q_OBJECT
private:
    OutlinedLabel *txt;
    BarrageSettings BS;
    QPropertyAnimation *animation;

public:
    bulletChat(QString _txt,BarrageSettings _BS);
    void style();
    void bnding_signal();
    void animation_end();
    ~bulletChat();
};

#endif // BULLETCHAT_H
