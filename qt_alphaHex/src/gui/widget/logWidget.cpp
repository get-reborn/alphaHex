#include "inc/gui/widget/logWidget.h"

WidgetLog::WidgetLog(QWidget *parent) : QTextBrowser (parent)
{
    //    this->moveCursor(this->textCursor().Start);
    this->clear();
}
void WidgetLog::resizeEvent(QResizeEvent* event)
{
    QTextEdit::resizeEvent(event);
    QFont logFont("微软雅黑",this->height()/8,this->height()/8,false);
    this->setFont(logFont);
}
void WidgetLog::slots_on_clearLog()
{
    this->clear();
    //    this->moveCursor(this->textCursor().Start);
}
void WidgetLog::slots_on_clearLog(int)
{
    slots_on_clearLog();
}
void WidgetLog::slots_on_clearLog(HexGame* game)
{
    slots_on_clearLog();
}
void WidgetLog::slots_on_updateLog(GameCore* core)
{
    int moveNum = core->getLastMove();
    int size = core->getSize();
    int log_x = moveNum / size;
    int log_y = moveNum % size;
    QFont logFont("微软雅黑",this->height()/8,this->height()/8,false);
    this->setFont(logFont);
    QString pointStr = "[" + QString::number(log_x) + "," + QString::number(log_y) + "]\n" ;
    QDateTime time = QDateTime::currentDateTime();
    QString logStr = time.toString("hh:mm:ss");
    if(core->getPlayer() == CHESS_BLUE){
        logStr += "  redPlayer move: " + pointStr;
        strToHtml(logStr,COLOR_BLUE);
    }

    else if(core->getPlayer() == CHESS_RED){
        logStr += "  bluePlayer move: " + pointStr;
        strToHtml(logStr,COLOR_RED);
    }
    this->append(logStr);
    this->moveCursor(this->textCursor().End);
}
