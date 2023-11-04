#pragma once
#include "CState.h"
class CPlayerDown :
    public CState
{
public:
    CPlayerDown();
    ~CPlayerDown();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CPlayerDown);
};
