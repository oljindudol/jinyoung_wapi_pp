#pragma once
#include "CState.h"
class CGEggIdle :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CGEggIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CGEggIdle();
    CLONE(CGEggIdle);
};

