#ifndef OPTION_H
#define OPTION_H

#include <QTabWidget>
#include <QSettings>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "barragesettings.h"


#define RESOURCES_PATH "resources/"
#define OPTION_PATH "option/"
#define SELECT_DATE_NAME OPTION_PATH "SelectDateName.txt"
#define BARRAGE_CONFIGURATION_FILE OPTION_PATH "BarrageConfigurationFile"

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

public:
    explicit option(QWidget *parent = nullptr);

    void write_barrage_configuration_information();
    void read_barrage_configuration_information(BarrageSettings *BS);

    ~option();
public:
    void init_onePage();


};

#endif // OPTION_H
