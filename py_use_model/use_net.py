from Hex_game import HexGame, chess
from deepNet_player import DeepLearningPlayer
from keras import models
import numpy as np
import os,sys

class NetUser:
    def __init__(self):
        model_path = str(os.path.dirname(os.path.realpath(__file__)) + '/keras_model/model.h5')
        net = models.load_model(model_path)
        self.player = DeepLearningPlayer(net)
    #turn| red:1   blue:-1
    def getMoveNum(self,t):
        size = 5
        turn = 1
        game = HexGame(size)
        #game.board = np.reshape(board,(size , size),int)
        print(1)
        if(turn == 1):
            game.turn = chess.red
        else:
            game.turn = chess.blue
        #_,move = self.player.getMove(game)
        move = 1
        return  move

class Person:
    def sayHi(self):
        print 'hi'
class Second:
    def invoke(self,obj):
         obj.sayHi()
def sayhi(name):
    print 'hi',name;