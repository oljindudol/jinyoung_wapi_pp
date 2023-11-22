#pragma once
#include "CState.h"
class CSecondBMPowerMiddle :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMPowerMiddle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMPowerMiddle();
    CLONE(CSecondBMPowerMiddle);
};

