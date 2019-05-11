#include "ui_mainwindow.h"
#include "inc/gui/window/mainWindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_setWidget(new SettingWindow(parent)),
    m_game(nullptr)
{
    this->close();
    m_setWidget->show();
    ui->setupUi(this);
    //init game
    m_game = new HexGame;
    m_game->initGame(11,20,POLICY_HUMAN,POLICY_HUMAN);
    ui->centralWidget->setLayout(ui->mainLayout);

    connect(m_game,SIGNAL(signals_on_aiMove()),m_game,SLOT(slots_on_policyMove()));
    //init red lcd
    ui->lcdRedTime->initLcd(m_game,CHESS_BLUE);
    //connect(m_timer,SIGNAL(timeout()),ui->lcdRedTime,SLOT(slots_on_updateTime()));
    connect(m_game->getCore(),SIGNAL(signals_on_gameUpdate(GameCore*)),ui->lcdRedTime,SLOT(slots_on_timeMode(GameCore*)));
    connect(m_game,SIGNAL(signals_on_newGame(HexGame*)),ui->lcdRedTime,SLOT(slots_on_resetTime(HexGame*)));
    connect(ui->lcdRedTime,SIGNAL(signals_on_timeOver(int)),m_game->getCore(),SLOT(slots_on_timeOver(int)));
    //init blue lcd
    ui->lcdBlueTime->initLcd(m_game,CHESS_RED);
    //connect(m_timer,SIGNAL(timeout()),ui->lcdBlueTime,SLOT(slots_on_updateTime()));
    connect(m_game->getCore(),SIGNAL(signals_on_gameUpdate(GameCore*)),ui->lcdBlueTime,SLOT(slots_on_timeMode(GameCore*)));
    connect(m_game,SIGNAL(signals_on_newGame(HexGame*)),ui->lcdBlueTime,SLOT(slots_on_resetTime(HexGame*)));
    connect(ui->lcdBlueTime,SIGNAL(signals_on_timeOver(int)),m_game->getCore(),SLOT(slots_on_timeOver(int)));
    //display frame
    ui->boardShow->initView(m_game->getCore(),TYPE_BOARD);
    ui->redLink->initView(m_game->getCore(),TYPE_RED);
    ui->blueLink->initView(m_game->getCore(),TYPE_BLUE);
    connect(ui->boardShow,SIGNAL(signals_on_clickMove(int)),m_game,SLOT(slots_on_humanMove(int)));
    //connect(ui->redLink,SIGNAL(signals_on_clickMove(int)),m_game->getCore(),SLOT(slots_on_humanMove(int)));
    //connect(ui->blueLink,SIGNAL(signals_on_clickMove(int)),m_game->getCore(),SLOT(slots_on_humanMove(int)));
    connect(m_game->getCore(),SIGNAL(signals_on_gameUpdate(GameCore*)),ui->boardShow,SLOT(update()));
    connect(m_game->getCore(),SIGNAL(signals_on_gameUpdate(GameCore*)),ui->redLink,SLOT(update()));
    connect(m_game->getCore(),SIGNAL(signals_on_gameUpdate(GameCore*)),ui->blueLink,SLOT(update()));
    //log
    connect(m_game->getCore(),SIGNAL(signals_on_gameUpdate(GameCore*)),ui->logShow,SLOT(slots_on_updateLog(GameCore*)));
    connect(m_game->getCore(),SIGNAL(signals_on_gameOver(int)),ui->logShow,SLOT(slots_on_clearLog(int)));
    connect(m_game,SIGNAL(signals_on_newGame(HexGame*)),ui->logShow,SLOT(slots_on_clearLog(HexGame*)));

    //set
    connect(m_game->getCore(),SIGNAL(signals_on_gameOver(int)),m_setWidget,SLOT(slots_on_windows_reOpen(int)));
    connect(m_setWidget,SIGNAL(signals_on_renewGame(int,int,int,int)),m_game,SLOT(slots_on_renewGame(int,int,int,int)));

    //this
    connect(m_setWidget,SIGNAL(signals_on_newGame()),this,SLOT(slots_on_newGame()));
    connect(m_setWidget,SIGNAL(signals_on_reset()),this,SLOT(slots_on_exitGame()));
}

MainWindow::~MainWindow()
{
    delete m_game;
    delete ui;
}

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

void MainWindow::slots_on_newGame()
{
    this->show();
}
void MainWindow::slots_on_exitGame()
{
    m_game->deleteAll();
    this->close();
    //m_setWidget->show();
}
