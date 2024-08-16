#include "option.h"
#include "ui_option.h"

option::option(QWidget *parent)
    : QTabWidget(parent)
    , ui(new Ui::option)
{
    ui->setupUi(this);
    init_onePage();
    signal_binding();
}

void option::signal_binding()
{
    connect(this->ui->bulletChatOptionCertainButton,&QPushButton::clicked,this,&option::write_barrage_configuration_information);
}

void option::write_barrage_configuration_information()
{
    emit this->updateSettings();
    QSettings setting(BARRAGE_CONFIGURATION_FILE ,QSettings::IniFormat);
    //是否自动开启弹幕
    setting.setValue(this->ui->isAutoBarrageEnabled->objectName()
                  ,this->ui->isAutoBarrageEnabled->isChecked());
    //字体大小
    setting.setValue(this->ui->BulletChat_FontSize->objectName()
                    ,this->ui->BulletChat_FontSizeLineEdit->text());
    //描边宽度
    setting.setValue(this->ui->FontStrokeWidth->objectName()
                    ,this->ui->FontStrokeWidthLineEdit->text());
    //滞留时间
    setting.setValue(this->ui->BulletChat_retentionTime->objectName()
                    ,this->ui->BulletChat_retentionTimeLineEdit->text());

}

void option::read_barrage_configuration_information(BarrageSettings *BS)
{

    QSettings setting(BARRAGE_CONFIGURATION_FILE ,QSettings::IniFormat);

    QString isAutoBarrageEnabled_key = this->ui->isAutoBarrageEnabled->objectName();
    QString BulletChat_FontSize_key =  this->ui->BulletChat_FontSize->objectName();
    QString FontStrokeWidth_key =  this->ui->FontStrokeWidth->objectName();
    QString BulletChat_retentionTime_key = this->ui->BulletChat_retentionTime->objectName();

    if (setting.contains(isAutoBarrageEnabled_key))
        BS->set_isAutoBarrageEnabled(setting.value(isAutoBarrageEnabled_key).toBool());

    if(setting.contains(BulletChat_FontSize_key))
        BS->set_BulletChat_FontSize(setting.value(BulletChat_FontSize_key).toInt());


    if(setting.contains(FontStrokeWidth_key))
        BS->set_FontStrokeWidth(setting.value(FontStrokeWidth_key).toDouble());

    if(setting.contains(BulletChat_retentionTime_key))
        BS->set_BulletChat_retentionTime(setting.value(BulletChat_retentionTime_key).toInt());
}

option::~option()
{
    delete ui;
}
