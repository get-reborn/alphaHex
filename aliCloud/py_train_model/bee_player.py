from Hex_game import HexGame, chess
import ctypes
import numpy as np
from numpy.random import choice
from math import tanh
#from nomal_player import RandomPlayer
class BeePlayer:
    def __init__(self, path_dll):
        so = ctypes.cdll.LoadLibrary
        self.name = 'Bee'
        self.lib = so(path_dll)
        self.lib.getMove.restype = ctypes.c_double

    def getMove(self, game, competitive=False, debug=False):
        game_data = []
        bee_size = game.size
        if (game.turn == chess.red):
            board = game.board.reshape((1, 1, game.size, game.size))
        else:
            board = (-game.board).T.reshape((1, 1, game.size, game.size))
        temp_board = board.reshape((bee_size * bee_size))
        bee_board = (ctypes.c_int * (bee_size * bee_size))()
        bee_pros = (ctypes.c_double * (bee_size * bee_size))()
        for i in range(bee_size * bee_size):
            bee_board[i] = temp_board[i]

        bee_value = self.lib.getMove(bee_board, bee_size, bee_pros)
        probs = np.zeros((bee_size,bee_size))
        for i in range(bee_size * bee_size):
            probs[i // bee_size,i % bee_size] = bee_pros[i]
        value = tanh(bee_value / (bee_size * 100))
        game_data.append((board, probs, value))
        #print('value',value)
        if (game.turn == chess.blue):
            probs = probs.T
        if(debug == True):
            print(game)

        probs = self.formatPros(game, probs)
        move = self.moveLegal(game, probs, competitive)
        return game_data, move

    def moveLegal(self, game, probs, competitive=False):
        probs_list = probs.reshape((game.size * game.size))
        if (competitive == True):
            moveNum = np.argmax(probs_list)
            move = [moveNum // game.size, moveNum % game.size]
            return move
        else:
            move = choice(len(probs_list), 1, p=probs_list)
            move = [move[0] // game.size, move[0] % game.size]
            return move

    def formatPros(self, game, probs):
        probs_format = probs * game.legalBoard()
        probs_format = probs_format / np.sum(probs_format)
        return probs_format

'''
#test
game = HexGame(8)
bee = BeePlayer('./bee_dll/libpymcts.so')
ran = RandomPlayer()
while(1):
    if(game.isComplet() == True):
        print(game)
        break
    data, move = ran.getMove(game)
    game.move(move)
    if(game.isComplet() == True):
        print(game)
        break

    data,move = bee.getMove(game,competitive=True)
    game.move(move)
    print(game)
'''
