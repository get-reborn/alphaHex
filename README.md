# AlphaHex （hex chess game,keras framework!)
## May 2019, University of Science and Technology Beijing
## By: @get-reborn,@my,@auto-man

-English
    Based on the deformation of AlphaGo Zero paper, the realization of self-game reinforcement learning realized for Hex chess. It's highly specific, and it's easy to change the evaluation function and the rules of the game to change the project to a model of the game where other information is completely countered, for the easy-to-use Keras framework.
-中文
    基于AlphaGo Zero论文的变形，针对海克斯棋而实现的自我博弈强化学习的实现。其具有高度的专一性，并且可以通过简易的更改评估函数和游戏规则将项目更改为其他信息完全对抗的游戏的模型，适用于简易上手的Keras框架。
###Module
-English
*py_train_model
     Self-game deep learning framework realized by keras framework
*cpp_evaluate
     C++ implementation of the hex chess evaluation function, providing an interface to py_train_model
*py_use_model
     Use the model to provide the next sub-policy to provide an interface to qt_alphaHex
*qt_alphaHex
     Gui game window implemented by qt
-中文
*py_train_model
    利用keras框架实现的自我博弈深度学习框架
*cpp_evaluate
    c++实现的hex棋的评估函数，向py_train_model提供接口
*py_use_model
    使用模型提供下子策略，向qt_alphaHex提供接口
*qt_alphaHex
    利用qt实现的gui博弈窗口
###Installation
-English
    If you want to run the core part of the project (enhanced learning), installing the keras framework is essential. We have already enumerated the dependencies that Python needs. You can implement a one-click dependency by executing 'bash install_pyenv.sh'. installation. However, if you need to use the training and prediction of the nvidia gpu acceleration model, installing cuda is essential <https://developer.nvidia.com/cuda-downloads>. But if you just execute the Queen Bee Tree Search section, these are not required.
-中文
    如果想运行该项目的核心部分（强化学习），安装keras框架是必不可少的，我们已经将python需要的依赖包列举了出来，你可以通过执行'bash install_pyenv.sh'实现依赖项的一键安装。但是如果需要使用nvidia gpu加速模型的训练、预测,安装cuda是必不可少的<https://developer.nvidia.com/cuda-downloads>。但是如果只是执行女王蜂树搜索部分，这些并不是必须的。
###Play
-English
    You can run the qt project directly in the '''./qt_alphaHex''' folder and use qt's good gui to visualize the confrontation.
-中文
    你可以直接在'''./qt_alphaHex'''文件夹中运行该qt项目，并且利用qt良好的gui从而实现对抗的可视化。
###Experiments
-English
    We trained an 11x11 keras model ('''./py_train_model/keras_model/hex11.h5'''), which only achieved 100 iterations due to limited computing power. The model used by default is this model, you can replace it with your trained model for better results.
-中文
    我们训练了一个5x5的keras模型（'''./py_train_model/keras_model/hex11.h5'''）,由于算力有限只实现了100次迭代。默认使用的模型是该模型，你可以将你训练的模型替换它，以得到更好的效果
###Document
-Mastering_Chess_and_Shogi_by_Self-Play_with_a_General_Reinforcement_Learning_Algorithm
-Mastering_the_Game_of_Go_without_Human_Knowledge