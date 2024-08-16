#ifndef OPTION_H
#define OPTION_H

#include <QTabWidget>
#include <QSettings>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QColorDialog>
#include <QColor>
#include <QPalette>
#include <QLabel>
#include "barragesettings.h"
#include "shortcutkeyssettings.h"


#define RESOURCES_PATH "resources/"
#define OPTION_PATH "option/"
#define SELECT_DATE_NAME OPTION_PATH "SelectDateName.txt"
#define BARRAGE_CONFIGURATION_FILE OPTION_PATH "BarrageConfigurationFile"
#define SHORTCUT_KEYS_FILE OPTION_PATH "ShortcutKeysFile"

namespace Ui {
class option;
}

class option : public QTabWidget
{
    Q_OBJECT
private:
    Ui::option *ui;
    //弹幕

signals:
    void updateSettings();

protected:
    void signal_binding();
    void onTabChanged(int index);

public:
    explicit option(QWidget *parent = nullptr);

    void write_barrage_configuration_information();
    void read_barrage_configuration_information(BarrageSettings *BS);

    void write_Shortcut_keys();
    void read_Shortcut_keys(ShortcutKeysSettings *SK);

    static void choiceColor(QWidget *parent, QLabel *l, QColor defaultColor = QColor(255,255,255));
    static void LabelDyeing(QLabel *l,QColor c);
    ~option();
public:
    void init_onePage();
    void init_twoPage();


};

#endif // OPTION_H
