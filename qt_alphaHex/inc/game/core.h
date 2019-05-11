#ifndef GAME_CORE_H
#define GAME_CORE_H
#include <iostream>
#include <cstring>
#include <vector>
#include <QPoint>
#include <QObject>
#include <QThread>
using namespace std;

const int HEX_MINSIZE = 3;
const int HEX_MAXSIZE = 25;

const int CHESS_DEFAULT = 0;
const int CHESS_BLUE = 1;
const int CHESS_RED = 2;

const int STATE_RUN = 0;
const int STATE_STOP = 1;

/**
 * @brief The GameCore class:the core rules about the hexchess game
 */
class GameCore:public QObject
{
    Q_OBJECT
public:
    explicit GameCore(QObject* parent = nullptr);
    /**
     * @brief initCore
     * @param size :board size
     */
    void initCore(int size);
    void resetCore();
    /**
     * @brief chessMove :move the chess of now player
     * @param moveNum :move to point(x,y) = moveNum(x*board size + y)
     * @return ture :legal move | flase:inlegal move
     */
    bool chessMove(int moveNum);
    bool chessMove(int x,int y);
    /**
     * @brief checkWin :check someone win this moment
     * @param x :new move x of point
     * @param y :new move y of point
     */
    void checkWin(int x,int y);//time|run
    int getSize();
    int getPlayer();
    int getWinner();
    int getLastMove();
    int m_board[HEX_MAXSIZE][HEX_MAXSIZE];
    //the linked chess
    int m_redLink[HEX_MAXSIZE][HEX_MAXSIZE];
    int m_blueLink[HEX_MAXSIZE][HEX_MAXSIZE];
    vector<int> getLegalMove();
private:
    int m_size;
    int m_player;
    int m_winner;
    int m_state;
    int m_lastMoveNum;
    /**
     * @brief seekLink  find a link about the player
     * @param x,y       move position of player
     * @param type      the color of the player
     */
    void seekLink(int x,int y,int type);
    void seekGrid(vector<QPoint> &linkLine,const int board[HEX_MAXSIZE][HEX_MAXSIZE],
                  int x,int y,int color);

public slots:
    void slots_on_timeOver(int loserType);
    void slots_on_AiMove(int moveNum);
signals:
    void signals_on_gameOver(int winner);
    void signals_on_gameUpdate(GameCore*);

};

#endif // GAME_CORE_H
