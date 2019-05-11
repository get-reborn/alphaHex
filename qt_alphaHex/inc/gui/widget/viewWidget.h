#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>
#include <QBitmap>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include "inc/game/hexChess.h"

const int TYPE_BOARD = 0;
const int TYPE_RED = 1;
const int TYPE_BLUE = 2;

const int GAME_OVER = 0;
const int GAME_RUN = 1;


class WidgetView:public QWidget
{
    Q_OBJECT
public:
    explicit WidgetView(QWidget * parent);
    ~WidgetView();
    void initView(GameCore* core,int viewType);
    void setType(int type);
    void drawBorder(QPainter*,int lineWidth);
protected:
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent* event);
private slots:
    void slots_on_setView(HexGame* game);
signals:
    //void boardUpdate();
    void signals_on_clickMove(int moveNum);
private:
    GameCore* m_game;
    int m_widgetType;
    double  m_height;
    double  m_width;
    QPointF m_points[HEX_MAXSIZE][HEX_MAXSIZE];
    QPolygonF m_contours[HEX_MAXSIZE][HEX_MAXSIZE];
    bool viewPoints();
    QPolygonF getPolygons(QPointF pt,QWidget* window,double width,double height);
};

#endif // GAMEWINDOW_H
