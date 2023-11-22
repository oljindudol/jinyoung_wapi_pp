#pragma once
#include "CState.h"
class CSecondBMMorningStarFall :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMMorningStarFall();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMMorningStarFall();
    CLONE(CSecondBMMorningStarFall);
};

