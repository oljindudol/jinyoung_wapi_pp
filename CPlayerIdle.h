#pragma once
#include "CState.h"


class CPlayerIdle :
    public CState
{
public:
    CPlayerIdle();
    ~CPlayerIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CPlayerIdle);
};
