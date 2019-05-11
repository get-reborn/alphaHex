#ifndef HEXCHESS_H
#define HEXCHESS_H

#include <QMessageBox>
#include "inc/game/core.h"
#include "inc/policy/aiPolicy.h"
const int POLICY_HUMAN = 0;
const int POLICY_RANDOM = 1;
const int POLICY_MCTS = 2;
const int POLICT_NET = 3;
//#define STATE_RUN 0
//#define STATE_STOP 1

const QColor COLOR_BLUE =QColor(66, 133, 244);
const QColor COLOR_RED = QColor(234, 67, 53);
const QColor COLOR_BLACK = QColor(191, 191, 191);
class HexGame:public QObject
{
    Q_OBJECT
public:
    explicit HexGame(QObject *parent = nullptr);
    ~HexGame();
    //QPoint m_lastMove;
    void initGame(int size,int time,int redPolicy,int bluePolicy);
    void reset();
    int getLimitTime();
    void deleteAll();
    GameCore* getCore();
public slots:
    void slots_on_renewGame(int size,int time,int redPolicy,int bluePolicy);
    void slots_on_policyMove();
    void slots_on_humanMove(int moveNum);
signals:
    void signals_on_aiMove();
    void signals_on_newGame(HexGame* game);
private:
    GameCore* m_pCore;
    basePolicy* m_pRedPolicy;
    basePolicy* m_pBluePolicy;
    int m_redPolicyType;
    int m_bluePolicyType;
    int m_limitTime;//secends

};

#endif // GAME_CORE_H
