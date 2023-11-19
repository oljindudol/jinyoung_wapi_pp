#pragma once
#include "CState.h"
class CNormalMonBind :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CNormalMonBind();
    ~CNormalMonBind();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CNormalMonBind);
};
