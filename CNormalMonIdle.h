#pragma once
#include "CState.h"

class CPlayer;

class CNormalMonIdle :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CNormalMonIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CNormalMonIdle();
    CLONE(CNormalMonIdle);
};

