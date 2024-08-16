#ifndef BARRAGESETTINGS_H
#define BARRAGESETTINGS_H


#include <QColor>

class BarrageSettings
{
private:
    bool isAutoBarrageEnabled;//是否自动开启弹幕
    int BulletChat_FontSize;//字体大小
    double FontStrokeWidth; //描边宽度
    int BulletChat_retentionTime;//滞留时间
    QColor outlineColor;
    QColor fontColor;
public:
    BarrageSettings(bool _isAutoBarrageEnabled
                    ,int _BulletChat_FontSize
                    ,double _FontStrokeWidth
                    ,int _BulletChat_retentionTime
                    ,QColor _outlineColor
                    ,QColor _fontColor):
        isAutoBarrageEnabled(_isAutoBarrageEnabled)
        ,BulletChat_FontSize(_BulletChat_FontSize)
        ,FontStrokeWidth(_FontStrokeWidth)
        ,BulletChat_retentionTime(_BulletChat_retentionTime)
        ,outlineColor(_outlineColor)
        ,fontColor(_fontColor){};

    BarrageSettings():
        isAutoBarrageEnabled(true)
        ,BulletChat_FontSize(20)
        ,FontStrokeWidth(1)
        ,BulletChat_retentionTime(20000)
        ,outlineColor(255,255,255)
        ,fontColor(0,0,0){};


    bool return_isAutoBarrageEnabled_value(){return this->isAutoBarrageEnabled;}
    int return_BulletChat_FontSize_value(){return this->BulletChat_FontSize;}
    double return_FontStrokeWidth_value(){return this->FontStrokeWidth;}
    int return_BulletChat_retentionTime_value(){return this->BulletChat_retentionTime;}
    QColor return_outlineColor_value(){return this->outlineColor;}
    QColor return_fontColor_value(){return this->fontColor;}

    void set_isAutoBarrageEnabled(const bool _isAutoBarrageEnabled){this->isAutoBarrageEnabled = _isAutoBarrageEnabled;}
    void set_BulletChat_FontSize(const int _BulletChat_FontSize){this->BulletChat_FontSize = _BulletChat_FontSize;}
    void set_FontStrokeWidth(const double _FontStrokeWidth){this->FontStrokeWidth = _FontStrokeWidth;}
    void set_BulletChat_retentionTime(const int _BulletChat_retentionTime){this->BulletChat_retentionTime = _BulletChat_retentionTime;}
    void set_outlineColor(const QColor _outlineColor){this->outlineColor = _outlineColor;}
    void set_fontColor(const QColor _fontColor){this->fontColor = _fontColor;}
};


#endif // BARRAGESETTINGS_H
