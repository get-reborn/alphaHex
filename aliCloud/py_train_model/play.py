#! /usr/bin/env python3
# -*- coding:utf-8 -*-
#########################################################
# May 2019, University of Science and Technology Beijing
#########################################################

from alphaHex_model import *
from nomal_player import RandomPlayer
from deepNet_player import DeepLearningPlayer
from bee_player import BeePlayer
from keras import  models

if __name__ == "__main__":
    #train new model
    beat_key = False
    beat_num = 0
    game_size = 8
    for i in range(5000):
        print('|game times: ' + str(i))
        if (i == 0):
            king_player = BeePlayer('./bee_dll/libpymcts.so')
            lower_player = create_player(king_player,game_size = game_size,total_times=100,reTrain= True,train_scale= 9)
        else:
            if(beat_num == 1):
                lower_player = create_player(king_player,king_player, game_size = game_size,
                                             train_only_win = False, total_times=100,reTrain= False)
            else:
                lower_player = create_player(king_player,lower_player,game_size = game_size,
                                             train_only_win = False,total_times=100,reTrain= False,train_scale= 9)
        king_player,beat_key = evaluate_player(king_player,lower_player,game_size= game_size,
                                               each_times= 50,thresh_num= 0.55,competitive=False)
        if(beat_key == True):
            beat_num += 1
            beat_key = False
            print('|victory_times: '+ str(beat_num))
            save_str = './keras_model/model_beat_' + str(beat_num) + '.h5'
            models.save_model(king_player.model,save_str)
        if(beat_num >= 25):
            break

        if(i % 200 ==0):
            save_str = './keras_model/model_time_' + str(i) + '.h5'
            models.save_model(lower_player.model, save_str)

    models.save_model(king_player.model,'./keras_model/model.h5')
    '''
    #test between two player
    model = models.load_model('/home/reget/project/AlphaHex/model_0502.h5')
    net = HexNetwork()
    net.load('/home/reget/project/AlphaHex/azalea.policy.pth')
    player1 = DeepLearningPlayer(model)
    player2 = azalea_Player(net)
    player3 = RandomPlayer()
    evaluate_player(player2, player1, game_size=11,each_times=10, thresh_num=0.22)
    game = HexGame(11)
    for i in range(121):
        # game.legalBoard()
        if (game._complet == True):
            print(game)
            print(game._winner)
            break
        data, move = player2.getMove(game, competitive=True)
        game.move(move)
        print(game)
        data, move = player2.getMove(game, competitive=True)
        game.move(move)
        print(game)
    '''