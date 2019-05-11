#ifndef GAMETIME_H
#define GAMETIME_H
#include <QLCDNumber>
#include <QTimer>
#include "inc/game/hexChess.h"
#include "inc/gui/widget/strhtml.h"
class WidgetLcd : public QLCDNumber
{
    Q_OBJECT
public:
    explicit WidgetLcd(QWidget *parent = nullptr);
    void initLcd(HexGame* game,int lcdType);
protected:
    void resizeEvent(QResizeEvent* event);
public slots:
    void slots_on_resetTime(HexGame* game);//timeLimit:min
    void slots_on_updateTime();
    void slots_on_timeMode(GameCore* core);
signals:
    void signals_on_timeOver(int chessType);
private:
    bool m_stopKey;
    int m_lcdColorType;
    int m_excessTime;//10 ms
    QTimer* m_timer;
    QString getTimeStr();
};

#endif // GAMETIME_H
