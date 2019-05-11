from network import HexNetwork
from Hex_game import HexGame,chess
import numpy as np
from numpy.random import choice
import torch

"""
class: azalea_Player
params:
    net: pytorch net
"""
class Azalea_Player:

    def __init__(self,net):
        self.name = 'azalea'
        self.net = net
    """
    introduction： use pytorch net calculate the advantage in each place\
                    and get the legal move
    params:
        game: the game play
        competitive: if choose the best choice
        debug: if display game process
    returns:
        game_data: game play data for train
        move: the right move number
    """
    def getMove(self,game,competitive = False,debug = False):

        if not (game.size == 11):
            raise Exception('Error: azalea player size must be 11')
        game_data = []

        legal_moves = []
        legalBoard = game.legalBoard()
        if(game.turn == chess.blue):
            legalBoard = legalBoard.T

        for i in range(game.size):
            for j in range(game.size):
                if(legalBoard[i][j] == True):
                    legal_moves.append(i*game.size + j + 1)
        legal_moves = np.reshape(legal_moves,(1,len(legal_moves)))

        #board = game.board.reshape((1, game.size * game.size))
        if(game.turn == chess.red):
            board = game.board.reshape((1,game.size*game.size))
        else:
            board = (-game.board).T.reshape((1,game.size*game.size))
        azaleaBoard = np.zeros(np.shape(board),dtype=int)

        for i in range(game.size * game.size):
            if(board[0][i] == 1):
                azaleaBoard[0][i] = 1
            elif(board[0][i] == 0):
                azaleaBoard[0][i] = 0
            elif(board[0][i] == -1):
                azaleaBoard[0][i] = 2
            else:
                raise Exception('Error: undefined chess type')

        batch = {
            'board': torch.tensor(azaleaBoard, device='cpu', dtype=torch.int32),
            'moves': torch.tensor(legal_moves, device='cpu', dtype=torch.int64)
        }

        output = self.net.run(batch)
        prior_prob = np.exp(output['moves_logprob']
                            .cpu().numpy())
        #prior_prob = self.formatPros(prior_prob)
        value = output['value'].cpu().numpy()
        #print(value)
        probs = self.formatPros(game,prior_prob,legal_moves)
        probs = probs.reshape((game.size, game.size))
        game_data.append((board,probs,value))
        if (game.turn == chess.blue):
            probs = probs.T
        if (debug == True):
            print(game)
        move = self.moveLegal(game, probs, competitive)
        return game_data,move

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
    def formatPros(self,game,probs,legal_moves):
        probs_format = np.zeros((1,game.size * game.size))
        normalize_probs = probs
        for i in range(legal_moves.size):
            probs_format[0][legal_moves[0][i] - 1] = normalize_probs[0][i]
        probs_format = probs_format.reshape((game.size * game.size))
        probs_format = probs_format / np.sum(probs_format)
        return probs_format

'''
#azalea player test
net = HexNetwork()
net.load('/home/reget/project/AlphaHex/azalea.policy.pth')
player = azalea_Player(net)
for i in range(10):
    game = HexGame(11)
    while(game.isComplet() == False):  
        x = int(input())
        y = int(input())
        game.move([x,y])
        print(game)
        data,move = player.getMove(game,competitive= False);
        game.move(move)
    print(game)
'''