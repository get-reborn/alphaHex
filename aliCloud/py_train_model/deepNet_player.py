# coding: utf-8

# imports
import numpy as np
from numpy.random import choice
from keras import  models
from Hex_game import HexGame,chess
#from bee_player import BeePlayer
"""
class: DeepLearningPlayer
Params:
    model: keras model
"""
class DeepLearningPlayer:

    def __init__(self, model):
        self.name = 'Dnn'
        self.model = model
    """
    introduction： use keras model calculate the advantage in each place\
                    and get the legal move
    params:
        game: the game play
        competitive: if choose the best choice
        debug: if display game process
    returns:
        game_data: game play data for train
        move: the right move number
    """
    def getMove(self, game, competitive=False, debug=False):
        game_data = []
        if (game.turn == chess.red):
            board = game.board.reshape((1, 1,game.size, game.size))
        else:
            board = (-game.board).T.reshape((1, 1,game.size, game.size))
        probs, value = self.model.predict(board)
        probs = probs.reshape((game.size,game.size))
        value = value[0][0]
        game_data.append((board, probs, value))
        #probs = probs.reshape((1,1,game.size,game.size))
        if (game.turn == chess.blue):
            probs = probs.T
        if (debug == True):
            print(game)
        probs = self.formatPros(game,probs)
        move = self.moveLegal(game, probs, competitive)
        #if (game.turn == chess.blue):
        #    move = [move[1],move[0]]
        return game_data, move

    """
    introduction： find the seemly move 
    params:
        game: the game play
        probs: the price of each place
        competitive: if choose the best place
    returns:
        the seemly move
    """
    def moveLegal(self, game, probs, competitive=False):
        probs_list = probs.reshape((game.size * game.size))
        if (competitive == True):
            moveNum = np.argmax(probs_list)
            move = [moveNum // game.size,moveNum % game.size]
            return move
        else:
            move = choice(len(probs_list),1 , p=probs_list)
            move = [move[0] // game.size, move[0] % game.size]
            return move

    """
    introduction： format the probability numpy
    params:
        game: the game play
        probs: the price of each place
        legal_moves: where
    returns:
        the seemly move
    """
    def formatPros(self,game,probs):
        probs_format = probs * game.legalBoard()
        probs_format = probs_format / np.sum(probs_format)
        return probs_format




'''deepNet_player test
model1 = models.load_model('./keras_model/model.h5')
#model2 = models.load_model('./keras_model/model.h5')
player1 = DeepLearningPlayer(model1)
player2 = BeePlayer('./bee_dll/libpymcts.so')
for j in range(20):
    game = HexGame(5)
    for i in range(64):
        # game.legalBoard()
        if (game._complet == True):
            print(game)
            print(game._winner)
            break
        data, move = player1.getMove(game, competitive=False)
        game.move(move)
        #print(game)
        if (game._complet == True):
            print(game)
            print(game._winner)
            break
        data, move = player2.getMove(game, competitive=False)
        game.move(move)
        #print(game)
'''