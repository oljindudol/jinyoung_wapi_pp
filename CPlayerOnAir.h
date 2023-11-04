#pragma once
#include "CState.h"
class CPlayerOnAir :
    public CState
{
public:
    CPlayerOnAir();
    ~CPlayerOnAir();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CPlayerOnAir);
};


