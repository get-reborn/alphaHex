#ifndef GAMEPOLICY_H
#define GAMEPOLICY_H
#include "inc/game/core.h"
#include "inc/policy/search.h"
#include "inc/policy/eval.h"
#include <Python.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <QObject>
using namespace sear;
using namespace eval;
using namespace std;

class basePolicy//based class
{
public:
    basePolicy();
    virtual int getAiMoveNum(GameCore* core) = 0;
private:
};

class PolicyRandom:public basePolicy
{

public:
    PolicyRandom();
    int getAiMoveNum(GameCore* core);
};


class PolicyMCTS:public basePolicy
{
public:
    PolicyMCTS();
    int getAiMoveNum(GameCore* core);
private:
    //SearchTree tree;
    bool ifInit;
};


class PolicyNet:public basePolicy
{
public:
    PolicyNet();
    ~PolicyNet();
    int getAiMoveNum(GameCore* core);
private:
    PyObject* m_pFunMoveNum;
    PyObject* m_pModel;
};

#endif // GAMEPOLICY_H

