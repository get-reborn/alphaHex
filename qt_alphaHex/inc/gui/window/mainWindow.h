#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include "inc/game/hexChess.h"
#include "inc/gui/window/consoleWindow.h"
#include "inc/policy/aiPolicy.h"

//#define STATE_OVER 0
//#define STATE_RUN 1

//#define POLICY_HUMAN 0
//#define POLICY_RANDOM    1
//#define POLICY_MCTS  1

//#define COLOR_BOARD QColor{191, 191, 191}
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SettingWindow* m_setWidget;
protected:
    //void closeEvent(QCloseEvent* event);
private slots:
    void on_resetButton_clicked();
    void on_regretButton_clicked();
    void slots_on_newGame();
    void slots_on_exitGame();
private:
    Ui::MainWindow* ui;

    HexGame*        m_game;
    //QTimer* m_timer;
};

#endif // MAINWINDOW_H
