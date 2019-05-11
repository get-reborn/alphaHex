#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QWidget>
#include <QButtonGroup>
#include <QThread>
#include "inc/game/hexChess.h"
#include "inc/gui/widget/strhtml.h"
const int DEFAULT_TIME = 20;
const int DEFAULT_SIZE = 11;
const int DEFAULT_RED_POLICY = POLICY_HUMAN;
const int DEFAULT_BLUE_POLICY = POLICY_HUMAN;

namespace Ui {
class settingwindow;
}
class SettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();
    //void initWidgetGame(HexGame* game);
private:
    void resetBotton();
    void setHexGame();
    Ui::settingwindow* ui;
    QButtonGroup*   m_redButtonGroup;
    QButtonGroup*   m_blueButtonGroup;
    int     m_redPolicyType;
    int     m_bluePolicyType;
    int     m_limitTime;
    int     m_setSize;
private slots:
    void on_okButton_clicked();

    void on_timeSetBox_valueChanged(int arg1);
    void on_sizeSetBox_valueChanged(int arg1);

    void on_pushButton_clicked();
    //void slots_on_gameOver();
    void slots_on_windows_reOpen(int winner);

    void on_blueHumanPolicyButton_pressed();

    void on_blueRandomPolicyButton_pressed();

    void on_blueMctsPolicyButton_pressed();

    void on_redMctsPolicyButton_pressed();

    void on_redRandomPolicyButton_pressed();

    void on_redHumanPolicyButton_pressed();

    void on_blueRandomPolicyButton_clicked();

    void on_blueNetPolicyButton_clicked();

    void on_redNetPolicyButton_clicked();

    void on_redNetPolicyButton_pressed();

    void on_blueNetPolicyButton_pressed();

signals:
    void signals_on_renewGame(int size,int time,int redPolicy,int bluePolicy);
    //void signals_on_gameOver();
    void signals_on_newGame();
    void signals_on_reset();
    void signals_on_exit();
};

#endif // SETTINGWINDOW_H
