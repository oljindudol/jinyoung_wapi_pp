#pragma once
#include "CState.h"
class CSecondBMBlindness :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMBlindness();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMBlindness();
    CLONE(CSecondBMBlindness);
};

