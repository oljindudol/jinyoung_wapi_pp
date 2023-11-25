#pragma once
#include "CState.h"
class CGEggHit :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CGEggHit();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CGEggHit();
    CLONE(CGEggHit);
};

