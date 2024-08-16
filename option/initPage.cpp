#include "option/option.h"
#include "ui_option.h"

void option::init_onePage()
{
    BarrageSettings t;
    this->read_barrage_configuration_information(&t);

    this->ui->isAutoBarrageEnabled->setChecked(t.return_isAutoBarrageEnabled_value());
    this->ui->BulletChat_FontSizeLineEdit->setText(QString::number(t.return_BulletChat_FontSize_value()));
    this->ui->BulletChat_retentionTimeLineEdit->setText(QString::number(t.return_BulletChat_retentionTime_value()));
    this->ui->FontStrokeWidthLineEdit->setText(QString::number(t.return_FontStrokeWidth_value()));
}
