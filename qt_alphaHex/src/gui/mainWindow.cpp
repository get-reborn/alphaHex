#include "inc/gui/mainWindow.h"
#include "ui/mainwindow.ui"
#include "ui/consolewindow.ui"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_setWidget(new SettingWindow(parent)),
    m_game(nullptr)
{
    m_setWidget->show();
    ui->setupUi(this);
    m_game = new HexGame;
    m_game->initGame(4);
    m_game->m_limitTime = 1;
    ui->centralWidget->setLayout(ui->mainLayout);

    m_randomAI = new PolicyRandom;
    m_mctsAI = new PolicyMCTS;

    QTimer* timer = new QTimer(this);
    timer->start(10);
    //red lcd
    ui->lcdRedTime->initType(m_game,RED_CHESS);
    connect(timer,SIGNAL(timeout()),ui->lcdRedTime,SLOT(updateTimeFrame()));
    connect(m_game,SIGNAL(timeRedRunSignal()),ui->lcdRedTime,SLOT(timeRun()));
    connect(m_game,SIGNAL(timeRedStopSignal()),ui->lcdRedTime,SLOT(timeStop()));
    connect(m_game,SIGNAL(timeResetSignal(int)),ui->lcdRedTime,SLOT(resetTimeFrame(int)));
    connect(ui->lcdRedTime,SIGNAL(timeOverSignal(int)),m_game,SLOT(timeOver(int)));
    //blue lcd
    ui->lcdBlueTime->initType(m_game,BLUE_CHESS);
    connect(timer,SIGNAL(timeout()),ui->lcdBlueTime,SLOT(updateTimeFrame()));
    connect(m_game,SIGNAL(timeBlueRunSignal()),ui->lcdBlueTime,SLOT(timeRun()));
    connect(m_game,SIGNAL(timeBlueStopSignal()),ui->lcdBlueTime,SLOT(timeStop()));
    connect(m_game,SIGNAL(timeResetSignal(int)),ui->lcdBlueTime,SLOT(resetTimeFrame(int)));
    connect(ui->lcdBlueTime,SIGNAL(timeOverSignal(int)),m_game,SLOT(timeOver(int)));
    //display frame
    ui->boardShow->initGame(m_game);
    ui->redLink->initGame(m_game);
    ui->blueLink->initGame(m_game);
    ui->boardShow->setType(TYPE_BOARD);
    ui->redLink->setType(TYPE_RED);
    ui->blueLink->setType(TYPE_BLUE);
    connect(m_game,SIGNAL(boardUpdateSignal()),ui->boardShow,SLOT(update()));
    connect(m_game,SIGNAL(boardUpdateSignal()),ui->redLink,SLOT(update()));
    connect(m_game,SIGNAL(boardUpdateSignal()),ui->blueLink,SLOT(update()));
    //log
    connect(m_game,SIGNAL(logUpdateSignal(int,QPoint)),ui->logShow,SLOT(updateGameLog(int,QPoint)));
    connect(m_game,SIGNAL(logClearSignal()),ui->logShow,SLOT(clearGameLog()));


    connect(m_game,SIGNAL(gameOverSignal(int)),m_setWidget,SLOT(reOpenWidget(int)));
    connect(m_setWidget,SIGNAL(resetGame(int,int,int,int)),m_game,SLOT(hexGameReset(int,int,int,int)));

    connect(m_setWidget,SIGNAL(gameStopSignal()),this,SLOT(on_game_stop()));
    connect(m_setWidget,SIGNAL(gameRunSignal()),this,SLOT(on_game_run()));


    connect(m_game,SIGNAL(aiRandomMoveSignal(vector<int>)),m_randomAI,SLOT(getMoveNum(vector<int>)));
    connect(m_randomAI,SIGNAL(randomMove(int)),m_game,SLOT(aiMove(int)));

    connect(m_game,SIGNAL(aiMctsMoveSignal(int,int,int)),m_mctsAI,SLOT(getBefMoveNum(int,int,int)));
    connect(m_mctsAI,SIGNAL(mctsMove(int)),m_game,SLOT(aiMove(int)));
    m_state = STATE_OVER;
    m_gameSize = 11;
    m_firPolicy = POLICY_HUMAN;
    m_secPolicy = POLICY_HUMAN;
}

MainWindow::~MainWindow()
{
    delete m_game;
    delete ui;
}

void MainWindow::initGame()
{
    m_game = new HexGame();
    m_game->initGame(m_gameSize);
}
//void MainWindow::closeEvent(QCloseEvent *event)
//{
//    switch( QMessageBox::information( this, tr("exit tip"), tr("Do you really want exit?"), tr("Yes"), tr("No"), 0, 1 ) )
//       {
//         case 0:
//              event->accept();
//              break;
//         case 1:
//         default:
//             event->ignore();
//             break;
//       }
//}
void MainWindow::resetBoard()
{
    int boardNum = m_game->m_size;
    double width = this->width()/(boardNum*1.50 - 1.50);
    double height = this->height()/(boardNum*0.75 + 1.25);
    for (int i = 0; i < boardNum ; ++i) {
        for (int j = 0; j < boardNum ; ++j) {
            QPointF centerPoint = QPointF( width*0.5 + width*0.5*i + width*j , height*0.5 + height*0.75*i);
            m_points[i][j] = centerPoint;
            QVector<QPointF> points;
            points.push_back(QPointF(centerPoint.x(), centerPoint.y() - height / 2));
            points.push_back(QPointF(centerPoint.x() + width / 2, centerPoint.y() - height / 4));
            points.push_back(QPointF(centerPoint.x() + width / 2, centerPoint.y() + height / 4));
            points.push_back(QPointF(centerPoint.x(), centerPoint.y() + height / 2));
            points.push_back(QPointF(centerPoint.x() - width / 2, centerPoint.y() + height / 4));
            points.push_back(QPointF(centerPoint.x() - width / 2, centerPoint.y() - height / 4));
            QPolygonF contours(points);
            m_contours[i][j] = contours;
        }
    }
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,1));
    painter.setBrush(QBrush(COLOR_BOARD,Qt::SolidPattern));
    for(int i=0;i<m_game->m_size;++i){
        for(int j=0;j<m_game->m_size;++j){
            painter.drawConvexPolygon(m_contours[i][j]);
        }
    }
}
//void MainWindow::resetRedLink()
//{

//}
//void MainWindow::resetBlueLink()
//{

//}

void MainWindow::on_resetButton_clicked()
{
    m_game->reset();
    cout<<"reset succeed"<<endl;
}

void MainWindow::on_regretButton_clicked()
{

    //m_game->regret()
    cout<<"regret failed"<<endl;
}

void MainWindow::on_game_run()
{
    this->show();
}
void MainWindow::on_game_stop()
{
    this->close();
    emit mainWindowClose();
}
