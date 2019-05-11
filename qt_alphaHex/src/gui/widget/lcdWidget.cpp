#include "inc/gui/widget/lcdWidget.h"

WidgetLcd::WidgetLcd(QWidget *parent) : QLCDNumber(parent)
{
    this->setDigitCount(10);
    this->setMode(QLCDNumber::Dec);
    this->setSegmentStyle(QLCDNumber::Flat);
    m_stopKey = true;
    m_excessTime = 0;
    m_timer = new QTimer(this);
    m_timer -> start(10);
    this->display(QString("88:88:88"));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slots_on_updateTime()));
}

void WidgetLcd::initLcd(HexGame* game,int lcdType)
{
    m_excessTime = game->getLimitTime() * 100;
    m_lcdColorType = lcdType;
    m_stopKey = true;
    QPalette lcdpat = this->palette();
    if(m_lcdColorType == CHESS_BLUE)
        lcdpat.setColor(QPalette::Normal,QPalette::WindowText,COLOR_BLUE);
    else if(m_lcdColorType == CHESS_RED)
        lcdpat.setColor(QPalette::Normal,QPalette::WindowText,COLOR_RED);
    this->setPalette(lcdpat);
    this->display(getTimeStr());
}

void WidgetLcd::resizeEvent(QResizeEvent *event)
{
    QLCDNumber::resizeEvent(event);
    QPalette lcdpat = this->palette();
    if(m_lcdColorType == CHESS_BLUE)
        lcdpat.setColor(QPalette::Normal,QPalette::WindowText,COLOR_BLUE);
    else if(m_lcdColorType == CHESS_RED)
        lcdpat.setColor(QPalette::Normal,QPalette::WindowText,COLOR_RED);
    this->setPalette(lcdpat);
    QString str =getTimeStr();
    this->display(str);
}

void WidgetLcd::slots_on_resetTime(HexGame* game)
{
    m_excessTime = game->getLimitTime() * 100;
    m_stopKey = true;
    this->display(getTimeStr());
}
void WidgetLcd::slots_on_updateTime()
{
    if(m_stopKey == false){
        if(m_excessTime > 1){
            QString str =getTimeStr();
            this->display(str);
            m_excessTime -= 1;
            update();
        }
        else {
            emit signals_on_timeOver(m_lcdColorType);
        }
    }
}
void WidgetLcd::slots_on_timeMode(GameCore* core)
{
    //slots_on_updateTime();
    if(m_lcdColorType == core->getPlayer()){
        m_stopKey = true;
    }
    else {
        m_stopKey = false;
    }
}
QString WidgetLcd::getTimeStr()
{
    int m = m_excessTime/(60 * 100);
    int s = m_excessTime%(60 * 100)/(100);
    int ms = m_excessTime%(60 * 100)%(100);
    QString mmStr,ssStr,msStr;
    if(m < 10)
        mmStr = "0" + QString::number(m);
    else
        mmStr = QString::number(m);

    if(s < 10)
        ssStr = "0" + QString::number(s);
    else
        ssStr = QString::number(s);

    if(ms < 10)
        msStr = "0" + QString::number(ms);
    else
        msStr = QString::number(ms);

    QString str =mmStr + ":" + ssStr + ":" + msStr;
    return  str;
}
