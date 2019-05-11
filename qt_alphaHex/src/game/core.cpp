#include "inc/game/core.h"

GameCore::GameCore(QObject* parent): QObject (parent){
}

void GameCore::initCore(int size){
    memset(m_board,CHESS_DEFAULT,sizeof (m_board));
    memset(m_redLink,0,sizeof(m_redLink));
    memset(m_blueLink,0,sizeof(m_blueLink));
    m_player = CHESS_RED;
    m_winner = CHESS_DEFAULT;
    m_size = size;
    m_lastMoveNum = -1;
    m_state = STATE_RUN;
    if(size > HEX_MAXSIZE)
        m_size = HEX_MAXSIZE;
    else if(size < HEX_MINSIZE)
        m_size = HEX_MINSIZE;
    else
        m_size = size;
}
void GameCore::resetCore(){
    memset(m_board,CHESS_DEFAULT,sizeof (m_board));
    memset(m_redLink,0,sizeof(m_redLink));
    memset(m_blueLink,0,sizeof(m_blueLink));
    m_player = CHESS_BLUE;
    m_winner = CHESS_DEFAULT;
    emit signals_on_gameUpdate(this);
}
bool GameCore::chessMove(int moveNum){
    if(m_state == STATE_RUN){
        int x = moveNum / m_size;
        int y = moveNum % m_size;
        return chessMove(x,y);}
    else return false;
}
bool GameCore::chessMove(int x, int y){
    if(m_state == STATE_RUN){
        if(m_board[x][y] != CHESS_DEFAULT)
            return false;
        else {
            m_board[x][y] = m_player;
            m_lastMoveNum = x*m_size + y;
            //QThread::msleep(200);
            emit signals_on_gameUpdate(this);

            //update first
            checkWin(x,y);
            if(m_winner != CHESS_DEFAULT){
                emit signals_on_gameOver(m_winner);
                m_state = STATE_STOP;
                return true;
            }
            cout<<"winner is: "<<m_winner<<endl;
            m_player = (CHESS_BLUE + CHESS_RED) - m_player;
            return true;
        }}
    else
        return false;
}
void GameCore::checkWin(int x,int y){
    if(m_winner != CHESS_DEFAULT)
        return;
    seekLink(x,y,m_player);
    bool leftLink,rightLink,topLink,bottomLink;
    leftLink = false;
    rightLink = false;
    topLink = false;
    bottomLink = false;
    if(m_player == CHESS_BLUE){
        for (int i=0;i<m_size;++i) {
            if(m_redLink[i][0] == 1)
                leftLink = true;
            if(m_redLink[i][m_size - 1] == 1)
                rightLink = true;
            if(leftLink && rightLink){
                m_winner = CHESS_BLUE;
            }
        }
    }
    else if(m_player == CHESS_RED){
        for (int i=0;i<m_size;++i) {
            if(m_blueLink[0][i] == 1)
                topLink = true;
            if(m_blueLink[m_size - 1][i] == 1)
                bottomLink = true;
            if(topLink && bottomLink){
                m_winner = CHESS_RED;
            }
        }
    }
}
int GameCore::getSize(){
    return m_size;
}

int GameCore::getPlayer(){
    return m_player;
}

int GameCore::getWinner(){
    return m_winner;
}
int GameCore::getLastMove(){
    return m_lastMoveNum;
}
vector<int> GameCore::getLegalMove(){
    vector<int> legalMove;
    for (int i=0;i<m_size;++i) {
        for (int j=0;j<m_size;++j) {
            if(m_board[i][j] == CHESS_DEFAULT)
                legalMove.push_back(i*m_size + j);
        }
    }
    return legalMove;
}
void GameCore::seekLink(int x, int y, int type){
    vector<QPoint> playerPoints;
    seekGrid(playerPoints,m_board,x,y,type);
    if(type == CHESS_BLUE){
        memset(m_redLink,0,sizeof(m_redLink));
        for (size_t i = 0;i < playerPoints.size(); ++i) {
            m_redLink[playerPoints[i].x()][playerPoints[i].y()] = 1;
        }
    }
    else {
        memset(m_blueLink,0,sizeof(m_blueLink));
        for (size_t i = 0;i < playerPoints.size(); ++i) {
            m_blueLink[playerPoints[i].x()][playerPoints[i].y()] = 1;
        }
    }
}
void GameCore::seekGrid(vector<QPoint> &linkLine, const int (*board)[25], int x, int y, int color){
    int copyBoard[HEX_MAXSIZE][HEX_MAXSIZE];
    for (int i = 0;i < HEX_MAXSIZE;++i) {
        for (int j = 0;j < HEX_MAXSIZE;++j) {
            copyBoard[i][j] = board[i][j];
        }
    }
    int minLimit = 0;
    int maxLimit = m_size - 1;

    if (x < minLimit || x > maxLimit || y < minLimit || y > maxLimit)
        return;
    else if (copyBoard[x][y] == color) {
        linkLine.push_back(QPoint(x,y));
        copyBoard[x][y] = 0;
    }

    if ( x - 1 >= minLimit &&  x - 1 <= maxLimit &&  y >= minLimit
         &&  y <= maxLimit && copyBoard[x - 1][y] == color){
        seekGrid(linkLine,copyBoard,x-1,y,color);
    }

    if ( x - 1 >= minLimit &&  x - 1 <= maxLimit &&  y + 1 >= minLimit
         &&  y + 1 <= maxLimit && copyBoard[x - 1][y + 1] == color){
        seekGrid(linkLine,copyBoard,x - 1,y + 1,color);
    }

    if ( x >= minLimit &&  x <= maxLimit &&  y - 1 >= minLimit
         &&  y - 1 <= maxLimit && copyBoard[x][y - 1] == color){
        seekGrid(linkLine,copyBoard,  x,  y - 1,color);
    }

    if ( x >= minLimit &&  x <= maxLimit &&  y + 1 >= minLimit
         &&  y + 1 <= maxLimit && copyBoard[x][y+1] == color) {
        seekGrid(linkLine,copyBoard,  x,  y + 1,color);
    }

    if ( x + 1 >= minLimit &&  x + 1 <= maxLimit &&  y - 1 >= minLimit
         &&  y - 1 <= maxLimit && copyBoard[x + 1][ y - 1] == color){
        seekGrid(linkLine,copyBoard, x + 1,  y - 1,color);
    }

    if ( x + 1 >= minLimit &&  x + 1 <= maxLimit &&  y >= minLimit
         &&  y <= maxLimit && copyBoard[ x + 1] [ y]== color){
        seekGrid(linkLine,copyBoard, x + 1,  y,color);
    }
}

void GameCore::slots_on_timeOver(int loserType){
    m_winner =  (CHESS_BLUE + CHESS_RED) - loserType;
}
void GameCore::slots_on_AiMove(int moveNum){
    chessMove(moveNum);
}
