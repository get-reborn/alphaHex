# coding: utf-8

'''creat a model to solve hexGame'''
from Hex_game import selfPlay, comparePlay, HexGame, chess
from deepNet_player import DeepLearningPlayer
import numpy as np
from keras.engine.topology import Input
from keras.engine.training import Model
from keras.layers.convolutional import Conv2D
from keras.layers.core import Activation, Dense, Flatten
from keras.layers.merge import Add
from keras import optimizers
from keras.layers.normalization import BatchNormalization
from keras.regularizers import l2
from tqdm import  tqdm
from tqdm._tqdm import trange

import matplotlib.pyplot as plt
"""
introduction: train a new model 
params:
    train_data: data for train
    game_size: size of game board
    train_scale: the proportion between train and validation
    verbose: display of train
    plot: if plot the loss
    save: if save the model 
    saveName: the name of model
return
    model: a keras model
"""
def __reTrain_model(train_data, game_size, train_scale=5, verbose=2, plot=False, save=False, saveName=None):
    train_x, train_y, validation_x, validation_y = __format_data(
        train_data, game_size,train_scale)
    model = __build_model(game_size)
    history = model.fit(train_x, train_y, verbose=verbose, validation_data=(validation_x, validation_y),
                         shuffle=True , epochs =10)
    #history = model.fit(train_x, train_y, verbose=verbose,
    #                    shuffle=True, epochs=1, batch_size=32)
    if (plot == True):
        acc = history.history['acc']
        val_acc = history.history['val_acc']
        loss = history.history['loss']
        val_loss = history.history['val_loss']
        epochs = range(1, len(acc) + 1)
        plt.plot(epochs, acc, 'bo', label='Training acc')
        plt.plot(epochs, val_acc, 'b', label='Validation acc')
        plt.title('Training and validation accuracy')
        plt.legend()
        plt.figure()
        plt.plot(epochs, loss, 'bo', label='Training loss')
        plt.plot(epochs, val_loss, 'b', label='Validation loss')
        plt.title('Training and validation loss')

        plt.show()
    if (save == True):
        model.save(saveName)
    return model
"""
introduction: keep on train a model 
params:
    train_data: data for train
    game_size: size of game board
    train_scale: the proportion between train and validation
    verbose: display of train
    plot: if plot the loss
    save: if save the model 
    saveName: the name of model
return
    model: keras model
"""
def __train_model(model, train_data, game_size, train_scale=5, verbose=2, plot=False, save=False, saveName=None):
    train_x, train_y, validation_x, validation_y = __format_data(
        train_data, game_size,train_scale)
    history = model.fit(train_x, train_y, verbose=verbose, validation_data=(validation_x, validation_y),
                        epochs = 10)
    if (plot == True):
        acc = history.history['acc']
        val_acc = history.history['val_acc']
        loss = history.history['loss']
        val_loss = history.history['val_loss']
        epochs = range(1, len(acc) + 1)
        plt.plot(epochs, acc, 'bo', label='Training acc')
        plt.plot(epochs, val_acc, 'b', label='Validation acc')
        plt.title('Training and validation accuracy')
        plt.legend()
        plt.figure()
        plt.plot(epochs, loss, 'bo', label='Training loss')
        plt.plot(epochs, val_loss, 'b', label='Validation loss')
        plt.title('Training and validation loss')

        plt.show()
    if (save == True):
        model.save(saveName)
    return model
"""
introduction: build a new model with keras
params:
    game_size: the size of game board
return
    model: keras model
"""
def __build_model(game_size):

    in_x = x = Input((1, game_size, game_size))
    #cnn_filter_num = game_size*game_size*2
    cnn_filter_num = 128
    n_labels = game_size * game_size
    value_fc_size = game_size * game_size
    cnn_first_filter_size = 2
    cnn_filter_size = 2
    l2_reg = 0.0001
    res_layer_num = 4
    learning_rate = 1
    momentum = 0.9
    # begin layers
    x = Conv2D(filters=cnn_filter_num,
            kernel_size=cnn_first_filter_size,
            padding="same",
            data_format="channels_first",
            use_bias=False,
            kernel_regularizer=l2(l2_reg))(x)

    x = BatchNormalization(axis=1)(x)

    x = Activation("relu")(x)

   # centre residual layers
    for  i in range(res_layer_num):
        temp_x = x
        index = i + 1
        x = Conv2D(filters=cnn_filter_num,
                   kernel_size=cnn_filter_size,
                   padding="same",
                   data_format="channels_first",
                   use_bias=False,
                   kernel_regularizer=l2(l2_reg))(x)
        x = BatchNormalization(axis=1)(x)
        x = Activation("relu")(x)
        x = Conv2D(filters=cnn_filter_num,
                   kernel_size=cnn_filter_size,
                   padding="same",
                   data_format="channels_first",
                   use_bias=False,
                   kernel_regularizer=l2(l2_reg))(x)
        x = BatchNormalization(axis=1)(x)
        x = Add()([temp_x, x])
        x = Activation("relu")(x)

    # end layers
    res_out = x

    # policy_out
    x = Conv2D(filters=2,
               kernel_size=1,
               data_format="channels_first",
               use_bias=False,
               kernel_regularizer=l2(l2_reg))(res_out)

    x = BatchNormalization(axis=1)(x)

    x = Activation("relu")(x)

    x = Flatten()(x)

    policy_out = Dense(n_labels,
                       kernel_regularizer=l2(l2_reg),
                       activation="softmax",
                       name="policy_out")(x)

    # value_out
    x = Conv2D(filters=4,
               kernel_size=1,
               data_format="channels_first",
               use_bias=False,
               kernel_regularizer=l2(l2_reg))(res_out)

    x = BatchNormalization(axis=1)(x)

    x = Activation("relu")(x)

    x = Flatten()(x)

    x = Dense(value_fc_size,
              kernel_regularizer=l2(l2_reg),
              activation="relu")(x)

    value_out = Dense(1,
                      kernel_regularizer=l2(l2_reg),
                      activation="tanh",
                      name="value_out")(x)

    # compile model
    model = Model(in_x,
                  [policy_out, value_out])

    sgd = optimizers.SGD(lr=learning_rate,
                         momentum=momentum)

    losses = ['categorical_crossentropy',
              'mean_squared_error']

    model.compile(loss=losses,
                  optimizer='adam',
                  metrics=['accuracy', 'mae'])

    model.summary()
    return model
"""
introduction: format the train date
params: 
    train_data: the data for train without format
    game_size: the game board size
    train_scale: the proportion between train and validation
"""
def __format_data(train_data,game_size,train_scale):
    x = []
    y_probs = []
    y_values = []
    for (board,pros,value) in train_data:
        x.append(board)
        y_probs.append(pros)
        y_values.append(value)

    data_x = np.array(x).reshape((len(x),1,game_size,game_size))
    data_y_probs = np.array(y_probs).reshape((len(y_probs), game_size * game_size))
    data_y_value = np.array(y_values)

    train_x = data_x[:int(train_scale) * data_x.shape[0] // int(train_scale + 1)]
    validation_x = data_x[int(train_scale) * data_x.shape[0] // int(train_scale + 1):]

    train_y_probs = data_y_probs[:int(train_scale) * data_y_probs.shape[0] // int(train_scale + 1)]
    validation_y_probs = data_y_probs[int(train_scale) * data_y_probs.shape[0] // int(train_scale + 1):]

    train_y_value = data_y_value[:int(train_scale) * data_y_value.shape[0] // int(train_scale + 1)]
    validation_y_value = data_y_value[int(train_scale) * data_y_value.shape[0] // int(train_scale + 1):]

    train_y = {'policy_out': train_y_probs,
               'value_out': train_y_value}

    validation_y = {'policy_out': validation_y_probs,
               'value_out': validation_y_value}

    return train_x,train_y,validation_x,validation_y
"""
introduction： picked the data only win
params:
    train_data: the data used for train
    winner: the game winner about data
return：
    picked_data: the data after picked
"""
def __pickUp_data(train_data , winner):
    picked_data = []
    num = 0
    for (board,pros,value) in train_data:
        if ( (num % 2 == 0 and winner == chess.red) or (num % 2 == 1 and winner == chess.blue) ):
            data = (board,pros,value)
            picked_data.append(data)
        num += 1
    return picked_data

"""
introduction： find best player
params:
    old_player: the player who is best now
    new_player: the player compare with old_player
    game_size: the size of game board
    each_times: each type play times
    thresh_num: the thresh num to decide if the new player is eligibility
    competitive: if play with competitive
return:
    the new player be create
"""
def evaluate_player(old_player,new_player,game_size = 11,each_times = 40,thresh_num = 0.55,competitive = False):
    newPlayerWin = 0
    #let new_player win in competitive
    if(competitive == True):
        game = HexGame(game_size)
        _,winner = comparePlay(new_player,old_player,game,competitive=True)
        if(winner == chess.blue):
            print('|competitive loss')
            return old_player,False
        game = HexGame(game_size)
        _,winner = comparePlay(old_player,new_player,game,competitive=True)
        if(winner == chess.red):
            print('|competitive loss')
            return old_player,False

    print('red evaluate: ')
    for i in trange(int(each_times)):
        game = HexGame(game_size)
        _, winner = comparePlay(new_player,old_player,game)
        if (winner == chess.red):
            newPlayerWin += 1

    print('blue evaluate: ')
    for i in trange(int(each_times)):
        game = HexGame(game_size)
        _,winner = comparePlay(old_player,new_player,game)
        if(winner == chess.blue):
            newPlayerWin += 1

    print('|victory_pros:  ' + str(newPlayerWin/(int(each_times) * 2) * 100) + '%')
    if(newPlayerWin/(int(each_times) * 2) >= thresh_num):
        winPlayer = new_player
        isBeat = True
    else :
        winPlayer = old_player
        isBeat = False

    return winPlayer,isBeat

"""
introduction： create/evolve a player 
params:
    king_player: the player who provide train data
    base_player: the player to evolve
    game_size: the size of game board
    total_times: self play times
    reTrain: if train new model
return:
    the new player be create
"""
def create_player(king_player,base_player = None,game_size = 11,total_times = 1000,reTrain = False,train_only_win = False,plot = False, debug = False,train_scale = 9):
    train_data = []
    train_winner = []

    print("SelfPlay Progress:");
    for i in trange(total_times):
        #tqdm.set_description(f"SelfPlay Progress:")
        #print(i)
        if (debug == True):
            debug_str = 'self play progress : ' + str(i + 1) + '/' + str(total_times)
            print(debug_str)
        game = HexGame(game_size)
        new_data, new_winner= selfPlay(king_player,game)
        train_data += new_data
        train_winner.append(new_winner)

    if (train_only_win == True):
        train_data = __pickUp_data(train_data, new_winner)

    if (reTrain == True):
        new_model = __reTrain_model(train_data , game_size,plot = plot,train_scale = train_scale)
    else:
        new_model = __train_model(base_player.model,train_data,game_size,plot = plot,train_scale = train_scale)
    new_player = DeepLearningPlayer(new_model)
    return new_player