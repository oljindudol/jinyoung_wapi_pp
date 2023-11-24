#pragma once
#include "CState.h"

class CBlackMage2;

class CSecondBMIdle :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    void ActivatePower();

    ~CSecondBMIdle();
    CLONE(CSecondBMIdle);

private:
    CBlackMage2* m_pBlackMage2;
};


