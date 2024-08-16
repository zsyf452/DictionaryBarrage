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
    connect(this, &QTabWidget::currentChanged, this, &option::onTabChanged);

    //确定
    connect(this->ui->bulletChatOptionCertainButton,&QPushButton::clicked,this,&option::write_barrage_configuration_information);
    connect(this->ui->ShortcutKeysCertainButton,&QPushButton::clicked,this,&option::write_Shortcut_keys);


    //字体颜色和边框颜色
    connect(this->ui->choice_StrokeColorPushButton,&QPushButton::clicked,this,[this](){

        choiceColor(this,this->ui->StrokeColor);
    });
    connect(this->ui->choice_FontColorPushButton,&QPushButton::clicked,this,[this](){

        choiceColor(this,this->ui->FontColor);
    });
}

void option::onTabChanged(int index)
{
    if(index == 0)
        this->init_onePage();
    else if(index == 1)
        this->init_twoPage();
}

void option::write_barrage_configuration_information()
{
    emit this->updateBarragesSettings();
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

    //描边颜色
    setting.setValue(this->ui->StrokeColor->objectName()
                     ,this->ui->StrokeColor->palette().color(QPalette::Window).name());
    //字体颜色
    setting.setValue(this->ui->FontColor->objectName()
                     ,this->ui->FontColor->palette().color(QPalette::Window).name());
}

void option::read_barrage_configuration_information(BarrageSettings *BS)
{

    QSettings setting(BARRAGE_CONFIGURATION_FILE ,QSettings::IniFormat);

    QString isAutoBarrageEnabled_key = this->ui->isAutoBarrageEnabled->objectName();
    QString BulletChat_FontSize_key =  this->ui->BulletChat_FontSize->objectName();
    QString FontStrokeWidth_key =  this->ui->FontStrokeWidth->objectName();
    QString BulletChat_retentionTime_key = this->ui->BulletChat_retentionTime->objectName();
    QString FontColor_key = this->ui->FontColor->objectName();
    QString StrokeColor_key = this->ui->StrokeColor->objectName();

    if (setting.contains(isAutoBarrageEnabled_key))
        BS->set_isAutoBarrageEnabled(setting.value(isAutoBarrageEnabled_key).toBool());

    if(setting.contains(BulletChat_FontSize_key))
        BS->set_BulletChat_FontSize(setting.value(BulletChat_FontSize_key).toInt());


    if(setting.contains(FontStrokeWidth_key))
        BS->set_FontStrokeWidth(setting.value(FontStrokeWidth_key).toDouble());

    if(setting.contains(BulletChat_retentionTime_key))
        BS->set_BulletChat_retentionTime(setting.value(BulletChat_retentionTime_key).toInt());

    if(setting.contains(FontColor_key))
        BS->set_fontColor(setting.value(FontColor_key).toString());

    if(setting.contains(StrokeColor_key))
        BS->set_StrokeColor(setting.value(StrokeColor_key).toString());
}


void option::write_Shortcut_keys()
{
    emit updateShortcutKeysSettings();
    QSettings setting(SHORTCUT_KEYS_FILE,QSettings::IniFormat);
    //开/关弹幕
    setting.setValue(this->ui->enableBarrage->objectName()
                    ,this->ui->enableBarrageKeySquenceEdit->keySequence());
}
void option::read_Shortcut_keys(ShortcutKeysSettings *SK)
{
    QSettings setting(SHORTCUT_KEYS_FILE,QSettings::IniFormat);

    QString enableBarrage_key = this->ui->enableBarrage->objectName();

    if(setting.contains(enableBarrage_key))
    {
        SK->set_enableBarrage(setting.value(enableBarrage_key).toString());
    }

}



void option::choiceColor(QWidget *parent,QLabel *l,QColor defaultColor)
{
    QColor color = QColorDialog::getColor(defaultColor, parent, "选择颜色");
    // 确保用户选择了颜色
    if (color.isValid())
        LabelDyeing(l, color);
}

void option::LabelDyeing(QLabel *l,QColor c)
{
    QPalette palette = l->palette();
    palette.setColor(QPalette::Window, c);
    l->setAutoFillBackground(true);  // 启用背景填充
    l->setPalette(palette);
}

option::~option()
{
    delete ui;
}
