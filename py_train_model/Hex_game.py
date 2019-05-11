# coding: utf-8
'''define the hex game'''

# imports
import numpy as np
from scipy.ndimage import label
from enum import Enum

"""chess types"""
class chess(Enum):
    blue = -1
    empty = 0
    red = 1

BASE_SIZE = 3
BASE_TURN = chess.red

"""define link"""
_link = np.ones([3, 3], int)
_link[0, 0] = 0
_link[2, 2] = 0

"""display board"""
CHAR_RED = u"\033[1;31m"
CHAR_BLUE = u"\033[1;34m"
CHAR_RESET = u"\033[0;0m"
CHAR_CIRCLE = u"\u25CF"

"""disk draw"""
CHAR_RED_DISK = CHAR_RED + CHAR_CIRCLE + CHAR_RESET
CHAR_BLUE_DISK = CHAR_BLUE + CHAR_CIRCLE + CHAR_RESET
CHAR_EMPTY_CELL = u"\u00B7"

"""boarder draw"""
CHAR_RED_BORDER = CHAR_RED + "-" + CHAR_RESET
CHAR_BLUE_BORDER = CHAR_BLUE + "\\" + CHAR_RESET

def print_(i):
    if i < 0:
        return CHAR_BLUE_DISK
    if i > 0:
        return CHAR_RED_DISK
    return CHAR_EMPTY_CELL

"""
class: HexGame
introduction: The base rules of HexGame
params:
    public:
        size: game board size(int)
        turn: next player type(struct: chess)
        board: game board(np.shape(size,size),int)\
                -1 blue | 0 empty | 1 red
    private:
        _complet: if game over(bool)
        _winner: game winner(struct: chess)
        _repr: print string(string)
        _steps: play sum steps(int)   
"""
class HexGame:

    def __init__(self, size=BASE_SIZE):
        self.size = size
        self.turn = BASE_TURN
        self.board = np.zeros([size, size], int)

        self._complet = None
        self._winner = None
        self._repr = None
        self._steps  = 0
    """
        introduction: display the game board
        return: display string
    """
    def __repr__(self):
        self._repr = u'\n' + '=' * ((self.size - 1)) + '[' +str(self._steps) + ' steps' + ']' + '=' * (self.size - 1)  + '\n'
        self._repr +=  (' ' + CHAR_RED_BORDER) * self.size + '\n'                              
        for i in range(self.size):
            self._repr += ' ' * i + CHAR_BLUE_BORDER + ' '
            for j in range(self.size):
                self._repr += print_(self.board[i, j]) + ' '
            self._repr += CHAR_BLUE_BORDER + '\n'
        self._repr += ' ' * self.size + ' ' + (' ' + CHAR_RED_BORDER) * self.size
        return self._repr
    """
        introduction: decide move step if legal
        param:
            move: next chess move(list[int,int])
        return:
            bool: if the move is legal
    """
    def isLegal(self, move):
        if (self.board[move[0]][move[1]] == chess.empty.value):
            return True
        return False
    """
       introduction: validate game if over 
       return: 
            bool: if the game is over
    """
    def isComplet(self):
        if (self.turn == chess.red):
            cBoard = self.board
        elif (self.turn == chess.blue):
            cBoard = self.board.T
        else:
            raise Exception('illegal turn:' + str(self.turn))
        clumps = label(cBoard == self.turn.value, _link)[0]
        #print(clumps)
        spanning_clumps = np.intersect1d(clumps[0], clumps[-1])
        self._complet = np.count_nonzero(spanning_clumps)
        return self._complet
    """
       introduction: check if winner appear 
       return: 
            winner type
    """
    def checkWinner(self):
        if self._winner is not None:
            return self._winner
        if (self.isComplet()):
            self._winner = self.turn
        return self._winner

    """
       introduction: chess move
       param:
            move: chess move number
       return: 
            winner type
    """
    def move(self, move):
        if not (self.isLegal(move)):
            raise Exception('illegal move:' + str(move))
        self.board[move[0]][move[1]] = self.turn.value
        self.checkWinner()
        self.turn = chess(0 - (self.turn.value))
        self._steps += 1
        #print(self)

    """
       introduction: get legal move place
       return: 
            legal move numbers
    """
    def legalBoard(self):
        legalNum = np.array(self.board == np.zeros(self.board.shape));
        return legalNum

"""
    introduction: the competition of two different player
    params:
        redPlayer: player in red way
        bluePlayer: player in blue way
        game: board game(default,game size is 11)
        competitve: true|choose the best choice\
                    false|choose move by probability
    returns:     
        train_data: provide the pros for train
        game_winner: the game winner      
"""
def comparePlay(redPlayer,bluePlayer,game = HexGame(size = 11),competitive = False):
    train_data = []
    while(game._complet != True):
        if (game.turn == chess.red):
            new_data,move = redPlayer.getMove(game,competitive = competitive)
        else:
            new_data,move = bluePlayer.getMove(game,competitive = competitive)
        game.move(move)
    return train_data,game._winner

"""
    introduction: player self play to 
    params:
        redPlayer: player in red way
        bluePlayer: player in blue way
        game: board game(default,game size is 11)
        competitve: true|choose the best choice\
                    false|choose move by probability
    returns:     
        train_data: provide the pros for train
        game_winner: the game winner      
"""
def selfPlay(selfPlayer,game = HexGame(size = 11)):
    train_data = []
    while (game._complet != True): 
        new_data,move = selfPlayer.getMove(game,competitive = False)
        train_data += new_data
        game.move(move)
    return train_data,game._winner
    
'''
#Hex_game test
game = HexGame(2)
print(game)
for i in range(2 * 2):
    x = int(input('input move x: '))
    y = int(input('input move y: '))
    move =[x,y]
    print(move[0], move[1])
    game.move(move)

    print(game)
    if(game._complet == True):
        print(game._winner)
        break
'''
