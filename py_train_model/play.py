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
import datetime
if __name__ == "__main__":
    #train new model

    beat_key = False
    beat_num = 0
    game_size = 4
    for i in range(5000):
        print('|game times: ' + str(i))
        if (i == 0):
            king_player = BeePlayer('./bee_dll/libpymcts.so')
            lower_player = create_player(king_player,game_size = game_size,total_times=400,reTrain= True,train_scale= 9)
        else:
            if(beat_num == 1):
                lower_player = create_player(king_player,king_player, game_size = game_size,
                                             train_only_win = False, total_times=400,reTrain= False)
            else:
                lower_player = create_player(king_player,lower_player,game_size = game_size,
                                             train_only_win = False,total_times=400,reTrain= False,train_scale= 9)
        king_player,beat_key = evaluate_player(king_player,lower_player,game_size= game_size,
                                               each_times= 50,thresh_num= 0.60,competitive=False)
        if(beat_key == True):
            beat_num += 1
            beat_key = False
            print('|victory_times: '+ str(beat_num))
            save_str = './keras_model/model_beat_' + str(beat_num) + '.h5'
            models.save_model(king_player.model,save_str)
        if(beat_num >= 25):
            break

        if(i % 100 ==0):
            save_str = './keras_model/model_time_' + str(i) + '.h5'
            models.save_model(lower_player.model, save_str)

    models.save_model(king_player.model,'./keras_model/model.h5')
    '''
    #test between two player
    #model = models.load_model('./keras_model/model.h5')
    #net = HexNetwork()
    #net.load('/home/reget/project/AlphaHex/azalea.policy.pth')
    #player1 = DeepLearningPlayer(model)
    player2 = BeePlayer('./bee_dll/libpymcts.so')
    player3 = BeePlayer('./bee_dll/libpymcts.so')
    #evaluate_player(player2, player1, game_size=4,each_times=10, thresh_num=0.50)
    for i in range(10000):
        #starttime = datetime.datetime.now()

        game = HexGame(4)
        while(True):
            if (game._complet == True):
                #print(game)
                #print(game._winner)
                endtime = datetime.datetime.now()
                #print(endtime - starttime).seconds
                break
            data, move = player2.getMove(game, competitive=False)
            game.move(move)
            if (game._complet == True):
                #print(game)
                #print(game._winner)
                endtime = datetime.datetime.now()
                #print(endtime - starttime).seconds
                break
            data, move = player2.getMove(game, competitive=False)
            game.move(move)
    '''