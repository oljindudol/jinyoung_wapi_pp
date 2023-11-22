#pragma once
#include "CState.h"
class CSecondBMIdle :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMIdle();
    CLONE(CSecondBMIdle);
};


