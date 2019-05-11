#include "inc/gui/widget/viewWidget.h"

WidgetView::WidgetView(QWidget * parent):QWidget(parent),m_game(nullptr)
{
}
WidgetView::~WidgetView()
{
}
void WidgetView::initView(GameCore* core,int viewType)
{
    m_game = core;
    m_widgetType = viewType;
    viewPoints();
}
bool WidgetView::viewPoints()
{
    if(m_game != NULL)
    {
        int boardNum = m_game->getSize();
        m_width = this->width()/(boardNum*1.50 + 0.50);
        m_height = this->height()/(boardNum*0.75 + 1.25);
        for (int i = 0; i < boardNum ; ++i) {
            for (int j = 0; j < boardNum ; ++j) {
                QPointF centerPoint = QPointF(m_width/2,m_height/2) + QPointF( m_width*0.5 + m_width*0.5*i + m_width*j , m_height*0.5 + m_height*0.75*i);
                m_points[i][j] = centerPoint;
                QVector<QPointF> points;
                points.push_back(QPointF(centerPoint.x(), centerPoint.y() - m_height / 2));
                points.push_back(QPointF(centerPoint.x() + m_width / 2, centerPoint.y() - m_height / 4));
                points.push_back(QPointF(centerPoint.x() + m_width / 2, centerPoint.y() + m_height / 4));
                points.push_back(QPointF(centerPoint.x(), centerPoint.y() + m_height / 2));
                points.push_back(QPointF(centerPoint.x() - m_width / 2, centerPoint.y() + m_height / 4));
                points.push_back(QPointF(centerPoint.x() - m_width / 2, centerPoint.y() - m_height / 4));
                QPolygonF contours(points);
                m_contours[i][j] = contours;
            }
        }
        return true;
    }
    else
        return false;
}
void WidgetView::setType(int type)
{
    m_widgetType = type;
}
void WidgetView::drawBorder(QPainter* painter,int lineWidth)
{
    QPainterPath topPath,rightPath,buttomPath,leftPath;
    int maxSize = m_game->getSize() - 1;

    topPath.moveTo(m_contours[0][0][5]);
    leftPath.moveTo(m_contours[0][0][5]);
    //
    buttomPath.moveTo(m_contours[maxSize][maxSize][2]);
    rightPath.moveTo(m_contours[maxSize][maxSize][2]);
    for (int i=0;i<m_game->getSize() ;++i) {
        topPath.lineTo(m_contours[0][i][0]);
        topPath.lineTo(m_contours[0][i][1]);

        leftPath.lineTo(m_contours[i][0][4]);
        leftPath.lineTo(m_contours[i][0][3]);

        buttomPath.lineTo(m_contours[maxSize][maxSize - i][3]);
        buttomPath.lineTo(m_contours[maxSize][maxSize - i][4]);

        rightPath.lineTo(m_contours[maxSize - i][maxSize][2]);
        rightPath.lineTo(m_contours[maxSize - i][maxSize][1]);
    }
    //0 1 2 3 4 5
    //0 5 1 4 2 3
    topPath.lineTo((m_contours[0][maxSize][0] + m_contours[0][maxSize][1])/2.f);
    rightPath.lineTo((m_contours[0][maxSize][0] + m_contours[0][maxSize][1])/2.f);

    leftPath.lineTo((m_contours[maxSize][0][4] + m_contours[maxSize][0][3])/2.f);
    buttomPath.lineTo((m_contours[maxSize][0][4] + m_contours[maxSize][0][3])/2.f);
    painter->setPen(QPen(COLOR_BLUE,lineWidth));
    painter->setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    //bordPainter.setBrush(QBrush(COLOR_RED,Qt::SolidPattern));
    painter->drawPath(leftPath);
    painter->drawPath(rightPath);

    painter->setPen(QPen(COLOR_RED,lineWidth));
    painter->drawPath(topPath);
    painter->drawPath(buttomPath);
}
void WidgetView::paintEvent(QPaintEvent *event)
{
    if(!m_game)
        return;
    int board[HEX_MAXSIZE][HEX_MAXSIZE];
    //draw board|link
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    painter.setBrush(QBrush(COLOR_BLACK,Qt::SolidPattern));
    //draw frame
    QBitmap bmp(this->size());
    bmp.fill();
    painter.drawRoundedRect(bmp.rect(),8,8);
    setMask(bmp);

    //draw board

    viewPoints();
    painter.setPen(Qt::black);
    for(int i=0;i<m_game->getSize();++i){
        for(int j=0;j<m_game->getSize();++j){
            switch (m_widgetType) {
            case TYPE_BOARD: painter.drawConvexPolygon(m_contours[i][j]); break;
            case TYPE_RED: painter.drawPoint(m_points[i][j]);break;
            case TYPE_BLUE: painter.drawPoint(m_points[i][j]);break;
            default: painter.setBrush(QBrush(COLOR_BLACK,Qt::SolidPattern));
            }
        }
    }
    if(m_widgetType == TYPE_BOARD)
        drawBorder(&painter,3);
    painter.setPen(Qt::black);
    //draw points
    if(m_widgetType == TYPE_BOARD){
        double r = min(m_height,m_width)*0.4;
        for(int i = 0; i < m_game->getSize();++i){
            for(int j = 0; j < m_game->getSize();++j){
                if(m_game->m_board[i][j] == CHESS_BLUE){
                    painter.setBrush(QBrush(COLOR_BLUE,Qt::SolidPattern));
                    painter.drawEllipse(m_points[i][j],r,r);
                }
                else if(m_game->m_board[i][j] == CHESS_RED){
                    painter.setBrush(QBrush(COLOR_RED,Qt::SolidPattern));
                    painter.drawEllipse(m_points[i][j],r,r);
                }
            }
        }
    }
    else {
        if(m_widgetType == TYPE_RED)
            painter.setBrush(QBrush(COLOR_BLUE,Qt::SolidPattern));
        else if(m_widgetType == TYPE_BLUE)
            painter.setBrush(QBrush(COLOR_RED,Qt::SolidPattern));
        for (int i=0;i<m_game->getSize();++i) {
            for (int j = 0;j<m_game->getSize();++j) {
                if(m_widgetType == TYPE_RED){

                    if(m_game->m_redLink[i][j] == 1)
                        painter.drawConvexPolygon(m_contours[i][j]);
                }
                else if (m_widgetType == TYPE_BLUE) {

                    if(m_game->m_blueLink[i][j] == 1)
                        painter.drawConvexPolygon(m_contours[i][j]);
                }
            }
        }
    }
}
void WidgetView::slots_on_setView(HexGame* game)
{
    viewPoints();
    update();
}
void WidgetView::mouseReleaseEvent(QMouseEvent *event){
    int size = m_game->getSize();
    for (int i = 0;i < size; ++i) {
        for(int j = 0;j< size; ++j){
            if(m_contours[i][j].containsPoint(QPointF(event->x(),event->y()),Qt::WindingFill)){
                cout<<"i: "<<i<<"  j: "<<j<<endl;
                int moveNum = i*size + j;
                emit  signals_on_clickMove(moveNum);
                this->update();
                //emit boardUpdate();
                return;
            }
        }
    }
}
