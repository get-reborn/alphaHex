#ifndef GAMELOG_H
#define GAMELOG_H

#include <QTextBrowser>
#include <QBitmap>
#include <QPainter>
#include <QDateTime>
#include "inc/game/hexChess.h"
#include "inc/gui/widget/strhtml.h"

class WidgetLog : public QTextBrowser
{
    Q_OBJECT

public:
    explicit WidgetLog(QWidget *parent = nullptr);
protected:
    //void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
public slots:
    void slots_on_updateLog(GameCore* core);
    void slots_on_clearLog();
    void slots_on_clearLog(int);
    void slots_on_clearLog(HexGame* game);
signals:
private:
};

#endif // GAMELOG_H
