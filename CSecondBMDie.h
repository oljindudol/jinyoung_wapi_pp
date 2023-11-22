#pragma once
#include "CState.h"
class CSecondBMDie :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMDie();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMDie();
    CLONE(CSecondBMDie);
};

