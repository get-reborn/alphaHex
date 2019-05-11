from Hex_game import HexGame, chess
from deepNet_player import DeepLearningPlayer
from keras import models
import numpy as np
import os,sys
def  creat_model(name):
    model_path = str(os.path.dirname(os.path.realpath(__file__)) + '/keras_model/hex5.h5')
    model = models.load_model(model_path)
    return model

def  getMoveNum(model,board,size,turn):
    #print(board)
    #print(turn)
    board= np.reshape(board,(size,size),int)
    legalBoard = np.array(board == np.zeros(np.shape(board)))
    print(legalBoard)
    if (turn == 1):
        board = board.reshape((1, 1,size,size))
    else:
        board = (-board).T.reshape((1, 1,size, size))
    print(board)
    probs, _ = model.predict(board)
    probs = probs.reshape((size,size))
    if (turn == -1):
        probs = probs.T
    probs = probs * legalBoard
    print(probs)
    probs_list = probs.reshape((size * size))
    print(probs_list)
    moveNum = np.argmax(probs_list)
    print(moveNum)
    return moveNum