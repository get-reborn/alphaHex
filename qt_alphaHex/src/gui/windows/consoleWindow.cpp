#include "ui_consolewindow.h"
#include "inc/gui/window/consoleWindow.h"
SettingWindow::SettingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new  Ui::settingwindow)
{
    emit signals_on_exit();
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags |= Qt::WindowMinimizeButtonHint;
    this->setWindowFlags(flags);
    this->setFixedSize(600,450);
    this->setLayout(ui->mainLayout);
    m_redButtonGroup = new QButtonGroup(this);
    m_blueButtonGroup = new QButtonGroup(this);

    m_redButtonGroup->addButton(ui->redHumanPolicyButton);
    m_redButtonGroup->addButton(ui->redRandomPolicyButton);
    m_redButtonGroup->addButton(ui->redMctsPolicyButton);
    m_redButtonGroup->addButton(ui->redNetPolicyButton);
    //ui->redHumanPolicyButton->setChecked(true);

    m_blueButtonGroup->addButton(ui->blueHumanPolicyButton);
    m_blueButtonGroup->addButton(ui->blueRandomPolicyButton);
    m_blueButtonGroup->addButton(ui->blueMctsPolicyButton);
    m_blueButtonGroup->addButton(ui->blueNetPolicyButton);
    //ui->blueHumanPolicyButton->setChecked(true);
    emit signals_on_reset();
    resetBotton();
}

SettingWindow::~SettingWindow(){}

void SettingWindow::slots_on_windows_reOpen(int winner)
{
    QString winnerStr;
//    if(winner == RED_CHESS){
//        winnerStr = "RED  WIN";
//        strToHtml(winnerStr,COLOR_RED);
//    }
//    else if(winner == BLUE_CHESS){
//        winnerStr = "BLUE WIN";
//        strToHtml(winnerStr,COLOR_BLUE);
//    }
    if(winner == CHESS_BLUE){
        winnerStr = "BLUE  WIN";
        strToHtml(winnerStr,COLOR_BLUE);
    }
    else if(winner == CHESS_RED){
        winnerStr = "RED WIN";
        strToHtml(winnerStr,COLOR_RED);
    }
    //QThread::sleep(1);
    //print the message of winner
    switch( QMessageBox::information( this, tr("winner tip"), winnerStr,tr("Ok"), 0 ) )
    {
    case 0:emit signals_on_reset();
        break;
    default:emit signals_on_reset();
        break;
    }
    this->show();
}
void SettingWindow::resetBotton()
{
    ui->redHumanPolicyButton->setChecked(true);
    ui->blueHumanPolicyButton->setChecked(true);
    ui->timeSetBox->setValue(DEFAULT_TIME);
    ui->sizeSetBox->setValue(DEFAULT_SIZE);
    m_redPolicyType = DEFAULT_RED_POLICY;
    m_bluePolicyType = DEFAULT_BLUE_POLICY;
    m_limitTime = 20 * 60;
    m_setSize = 11;
}
void SettingWindow::on_okButton_clicked()
{
    this->close();
    emit signals_on_renewGame(m_setSize,m_limitTime,m_redPolicyType,m_bluePolicyType);
    emit signals_on_newGame();
}


void SettingWindow::on_timeSetBox_valueChanged(int arg1)
{
    m_limitTime = arg1 * 60;
}

void SettingWindow::on_sizeSetBox_valueChanged(int arg1)
{
    m_setSize = arg1;
}

void SettingWindow::on_pushButton_clicked()
{
    emit signals_on_exit();
}

void SettingWindow::on_blueHumanPolicyButton_pressed()
{
    m_bluePolicyType = POLICY_HUMAN;
}

void SettingWindow::on_blueRandomPolicyButton_pressed()
{
    m_bluePolicyType = POLICY_RANDOM;
}

void SettingWindow::on_blueMctsPolicyButton_pressed()
{
    m_bluePolicyType = POLICY_MCTS;
}

void SettingWindow::on_redMctsPolicyButton_pressed()
{
    m_redPolicyType = POLICY_MCTS;
}

void SettingWindow::on_redRandomPolicyButton_pressed()
{
    m_redPolicyType = POLICY_RANDOM;
}

void SettingWindow::on_redHumanPolicyButton_pressed()
{
    m_redPolicyType = POLICY_HUMAN;
}

void SettingWindow::on_redNetPolicyButton_pressed()
{
    m_redPolicyType = POLICT_NET;
}

void SettingWindow::on_blueNetPolicyButton_pressed()
{
    m_bluePolicyType = POLICT_NET;
}
