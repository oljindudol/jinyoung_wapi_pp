#pragma once
#include "CState.h"
class CMorningStarFallRegen :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CMorningStarFallRegen();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    ~CMorningStarFallRegen();

    CLONE(CMorningStarFallRegen);
};
