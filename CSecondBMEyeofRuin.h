#pragma once
#include "CState.h"
class CSecondBMEyeofRuin :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMEyeofRuin();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMEyeofRuin();
    CLONE(CSecondBMEyeofRuin);
};
