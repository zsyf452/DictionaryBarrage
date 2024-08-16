#ifndef SHORTCUTKEYSSETTINGS_H
#define SHORTCUTKEYSSETTINGS_H

#include <QKeySequence>
#include <qhotkey.h>


class ShortcutKeys
{
private:
    QHotkey enableBarrage;

public:
    ShortcutKeys():enableBarrage(NULL){};

    ShortcutKeys(QString QSR_enableBarrage):
        enableBarrage(QSR_enableBarrage,true){};

    QHotkey *return_enableBarrage(){return &this->enableBarrage;};
};

class ShortcutKeysSettings
{
private:
    QKeySequence enableBarrage;
public:
    ShortcutKeysSettings():enableBarrage(NULL){};


    QKeySequence return_enableBarrage(){return this->enableBarrage;}

    void set_enableBarrage(QString QStr_enableBarrage){this->enableBarrage = QStr_enableBarrage;}
    void set_enableBarrage(QKeySequence _enableBarrage){this->enableBarrage = _enableBarrage;}
};

#endif // SHORTCUTKEYSSETTINGS_H
