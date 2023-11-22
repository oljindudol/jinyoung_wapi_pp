#pragma once
#include "CState.h"
class CSecondBMPowerRight :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMPowerRight();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMPowerRight();
    CLONE(CSecondBMPowerRight);
};

