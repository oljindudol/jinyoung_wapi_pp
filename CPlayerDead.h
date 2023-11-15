#pragma once
#include "CState.h"
class CPlayerDead :
    public CState
{

public:
    CPlayerDead();
    ~CPlayerDead();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CPlayerDead);
};

