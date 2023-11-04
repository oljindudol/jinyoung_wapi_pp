#pragma once
#include "CState.h"
class CPlayerMove :
    public CState
{
public:
    CPlayerMove();
    ~CPlayerMove();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CPlayerMove);
};

