#pragma once
#include "CState.h"
class CMorningStarFallDie :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CMorningStarFallDie();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    ~CMorningStarFallDie();

    CLONE(CMorningStarFallDie);
};
