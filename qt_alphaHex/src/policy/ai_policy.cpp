#include "inc/policy/aiPolicy.h"

basePolicy::basePolicy(){}

PolicyRandom::PolicyRandom():basePolicy (){}

int PolicyRandom::getAiMoveNum(GameCore* core){
    cout<<"Random Begin"<<endl;
    vector<int> legalMove = core->getLegalMove();
    int size = legalMove.size();
    srand(time(0));
    int moveNum = legalMove[rand()%size];
    cout<<"Random Over"<<endl;
    return moveNum;
}

PolicyMCTS::PolicyMCTS():basePolicy (){
    cout<<"ok"<<endl;
    //tree = SearchTree();
    //SearchTree tree;
    //ifInit = false;
}

int PolicyMCTS::getAiMoveNum(GameCore *core){
    //RED | WHILE :top to button
    //BLUE| BLACK :left to right
    int treeSize = core->getSize() + 2;

    int* treeBoard = new int[treeSize * treeSize];
    for (int i = 0; i <treeSize * treeSize; ++i) {
        treeBoard[i] = 0;
    }
    for (int i = 1; i < treeSize - 1; ++i) {
        for (int j = 1; j < treeSize - 1; ++j) {
            treeBoard[i*treeSize + j] = core->m_board[i - 1][j - 1];
        }
    }
    /*
    for (size_t i = 0; i < treeSize; ++i)
    {
        for (size_t j = 0; j < treeSize; ++j)
        {
            cout << treeBoard[i * treeSize + j] << " ";
        }
        cout << endl;
    }
    */
    SearchTree tree(treeSize,treeBoard);
    delete []treeBoard;
    double *arr;
    if(core->getPlayer() == CHESS_RED)
        arr = tree.Get_Move_Array(RED);
    else
        arr = tree.Get_Move_Array(BLUE);
    int value = tree.Get_Value();
    //find max
    double max = 0;
    int p_x,p_y;
    p_x = p_y = 0;
    for (int i = 1; i < treeSize - 1; ++i) {
        for (int j = 1; j < treeSize - 1; ++j) {
            //cout<<arr[i *treeSize + j]<<" ";
            if( arr[i *treeSize + j] > max){
                max = arr[i *treeSize + j];
                p_x = i;
                p_y = j;
            }
        }
        //cout<<endl;
    }
    int moveNum = (p_x - 1)*core->getSize() + (p_y - 1);
    cout<<"MCTS Over"<<endl;
    return moveNum;
}

PolicyNet::PolicyNet(){
    Py_SetPythonHome(L"/home/reget/anaconda3/envs/keras");
    Py_Initialize();
    if(!Py_IsInitialized()){
        cerr<<"python model init fail"<<endl;
        exit(0);
    }
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/reget/project/AlphaHex0505/py_use_model')");
    //PyRun_SimpleString("sys.path.append('/home/reget/anaconda3/envs/keras/lib/python3.6/site-packages/')");
    //PyRun_SimpleString("import keras");
    PyObject * pModule = NULL;//声明变量
    pModule = PyImport_ImportModule("net_user");
    if(!pModule){
        cerr<<"can not find module"<<endl;
        exit(0);
    }
    PyObject* pDict = PyModule_GetDict(pModule);
    if(!pDict){
        cerr<<"can not find dict"<<endl;
        exit(0);
    }
    PyObject* pFunCreat = PyDict_GetItemString(pDict, "creat_model");
    m_pModel = PyObject_CallFunction(pFunCreat, "s", "Hex11");
    m_pFunMoveNum = PyDict_GetItemString(pDict, "getMoveNum");

//    PyObject* list = PyList_New(0);
//    PyObject* pArgs = NULL;
//    pArgs = PyTuple_New(1);
//    for(size_t i = 0; i < 121 ; i++){
//        PyList_Append(list,Py_BuildValue("i",0));
//    }
//    PyTuple_SetItem(pArgs,0,list);
//    PyObject* pAns = PyObject_CallFunction(pFunMoveNum, "OOii",pModel,list,11,1);

//    int res = 0;
//    PyArg_Parse(pAns,"i",&res);
//    cout<<res<<endl;
    /*
    if(!pt)
        cout<<"error"<<endl;
    cout<<"func ok"<<endl;
    PyObject* list = PyList_New(0);
    PyObject* pArgs = NULL;
    pArgs = PyTuple_New(1);
    for(size_t i = 0; i < 25 ; i++){
        PyList_Append(list,Py_BuildValue("i",0));
    }
    PyTuple_SetItem(pArgs,0,list);
         cout<<"OK"<<endl;
    PyObject* pAns = PyObject_CallMethod(pInstanceNet,"getMoveNum","O",pArgs);
    if(!pAns){
        cerr<<"call error"<<endl;
        exit(0);
    }
    sleep(1);
    cout<<"OK"<<endl;
    char* charAns= PyBytes_AsString(pAns);
    cout<<"OK"<<endl;
    cout<<charAns<<endl;
*/
    //Py_Finalize();
}
PolicyNet::~PolicyNet(){
    Py_DECREF(m_pFunMoveNum);
    Py_DECREF(m_pModel);
    Py_Finalize();
}
int PolicyNet::getAiMoveNum(GameCore *core){
    int size = core->getSize();
    if(size != 5){
        cerr<<"bad size"<<endl;
        exit(0);
    }
    PyObject* list = PyList_New(0);
    for(size_t i = 0; i < size ; i++){
        for(size_t j = 0; j < size ; j++) {
            int num = 0;
            if(core->m_board[j][i] == CHESS_RED)
                num = 1;
            else if (core->m_board[j][i] == CHESS_BLUE) {
                num = -1;
            }
            else {
                num = 0;
            }
            cout<<num<<" ";
            PyList_Append(list,Py_BuildValue("i",num));
        }
        cout<<endl;
    }
    int turn;
    if(core->getPlayer() == CHESS_RED)
        turn = 1;
    else
        turn = -1;
    //cout<<turn<<endl;

    PyObject* pAns = PyObject_CallFunction(m_pFunMoveNum,"OOii",m_pModel,list,size,turn);
    if(!pAns){
        cerr<<"call error"<<endl;
        exit(0);
    }
    int res = 0;
    PyArg_Parse(pAns,"i",&res);
    //cout<<res<<endl;
    Py_DECREF(list);
    Py_DECREF(pAns);
    return res;
}
