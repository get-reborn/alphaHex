
from numpy.random import choice
import numpy as np
from Hex_game import chess,HexGame
from sys import stdin
def Normalize(data):
   num = sum(data) * np.ones(data.shape())
   return np.true_divide(data,num)

class RandomPlayer:
    """Player that selects a random legal move."""
    def __init__(self, *args):
        self.name = "Random"

    def getMove(self, game,competitive=False, debug=False):
        game_data = []
        if (game.turn == chess.red):
            board = game.board.reshape((1,1,game.size,game.size ))
        else:
            board = (-game.board).T.reshape((1,1,game.size, game.size))
        probs =  np.ones((game.size , game.size)) * float(1/game.size/game.size)
        value = 0
        game_data.append((board, probs, value))

        probs = probs.reshape((game.size*game.size))
        move_idx = choice(len(probs),1,p = probs)
        move = [move_idx[0] // game.size,move_idx[0] % game.size]
        #print(move)
        while(game.isLegal(move) == False):
            move_idx = choice(len(probs),1,p = probs)
            move = [move_idx[0] // game.size, move_idx[0] % game.size]
        return game_data, move

''' nomal_player test
game = HexGame(3)
player = RandomPlayer(game)
for i in range(9):
    data,move = player.getMove(game)
    game.move(move)
    print(game)
'''