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

class bulletChat:public QDialog
{
     Q_OBJECT
private:
    QLabel *txt;
    QPropertyAnimation *animation;

public:
    bulletChat(QString _txt, int _fontSize, int _duration);
    void style();
    void bnding_signal();
    void animation_end();
    ~bulletChat();
};

#endif // BULLETCHAT_H
