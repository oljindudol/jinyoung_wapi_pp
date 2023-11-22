#pragma once
#include "CState.h"
class CMorningStarFallIdle :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CMorningStarFallIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    ~CMorningStarFallIdle();

    CLONE(CMorningStarFallIdle);
};
