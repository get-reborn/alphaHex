#include "inc/game/hexChess.h"

HexGame::HexGame(QObject* parent):
    QObject (parent),
    m_pCore(new GameCore())
{
    //emit gameStopSignal();
}
HexGame::~HexGame()
{
    if(m_pRedPolicy != nullptr)
        delete m_pRedPolicy;
    if(m_pBluePolicy != nullptr)
        delete m_pBluePolicy;
    delete m_pCore;
}
GameCore* HexGame::getCore(){
    return m_pCore;
}
void HexGame::initGame(int size, int time, int redPolicy, int bluePolicy)
{
    m_pCore->initCore(size);
    m_limitTime = time;
    m_redPolicyType = bluePolicy;
    m_bluePolicyType = redPolicy;
    switch (m_redPolicyType) {
    case POLICY_HUMAN:m_pRedPolicy = nullptr;break;
    case POLICY_RANDOM:m_pRedPolicy = new PolicyRandom(); break;
    case POLICY_MCTS:m_pRedPolicy = new PolicyMCTS();break;
    case POLICT_NET:m_pRedPolicy = new PolicyNet();break;
    default:cerr<<"redPolicy error: no such policy type!!"<<endl;
    }
    //
    switch (m_bluePolicyType) {
    case POLICY_HUMAN:m_pBluePolicy = nullptr;break;
    case POLICY_RANDOM:m_pBluePolicy = new PolicyRandom(); break;
    case POLICY_MCTS:m_pBluePolicy = new PolicyMCTS();break;
    case POLICT_NET:m_pBluePolicy = new PolicyNet();break;
    default:cerr<<"bluePolicy error: no such policy type!!"<<endl;
    }

    if(m_bluePolicyType != POLICY_HUMAN){
        slots_on_policyMove();
    }
}
void HexGame::reset()
{
    if(m_pRedPolicy != nullptr)
        delete m_pRedPolicy;
    if(m_pBluePolicy != nullptr)
        delete m_pBluePolicy;
    switch (m_redPolicyType) {
    case POLICY_HUMAN:m_pRedPolicy = nullptr;break;
    case POLICY_RANDOM:m_pRedPolicy = new PolicyRandom(); break;
    case POLICY_MCTS:m_pRedPolicy = new PolicyMCTS();break;
    default:cerr<<"redPolicy error: no such policy type!!"<<endl;
    }
    switch (m_bluePolicyType) {
    case POLICY_HUMAN:m_pBluePolicy = nullptr;break;
    case POLICY_RANDOM:m_pBluePolicy = new PolicyRandom(); break;
    case POLICY_MCTS:m_pBluePolicy = new PolicyMCTS();break;
    default:cerr<<"bluePolicy error: no such policy type!!"<<endl;
    }
    m_pCore->resetCore();

}
int HexGame::getLimitTime()
{
    return m_limitTime;
}
void HexGame::deleteAll()
{
    if(m_pRedPolicy != nullptr)
        delete m_pRedPolicy;
    if(m_pBluePolicy != nullptr)
        delete m_pBluePolicy;
}
void HexGame::slots_on_policyMove()
{
    if(m_pCore->getWinner() != CHESS_DEFAULT)
        return;
    int moveNum;
    if(m_pCore->getPlayer() == CHESS_BLUE
            && m_redPolicyType != POLICY_HUMAN)
        moveNum = m_pRedPolicy->getAiMoveNum(m_pCore);
    else if(m_pCore->getPlayer() == CHESS_RED
            && m_bluePolicyType != POLICY_HUMAN)
        moveNum = m_pBluePolicy->getAiMoveNum(m_pCore);
    else
        return;
    //if AI moves, retry this function
    m_pCore->chessMove(moveNum);
    emit signals_on_aiMove();
}
void HexGame::slots_on_humanMove(int moveNum)
{
    if(m_pCore->getWinner() != CHESS_DEFAULT)
        return;
    if((m_pCore->getPlayer() == CHESS_BLUE
            && m_redPolicyType == POLICY_HUMAN)
            ||
        m_pCore->getPlayer() == CHESS_RED
            && m_bluePolicyType == POLICY_HUMAN){
        m_pCore->chessMove(moveNum);
        emit signals_on_aiMove();
    }
}
void HexGame::slots_on_renewGame(int size,int time,int redPolicy,int bluePolicy)
{
    initGame(size,time,redPolicy,bluePolicy);
    emit signals_on_newGame(this);
}
