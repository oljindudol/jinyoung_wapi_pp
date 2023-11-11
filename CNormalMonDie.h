#pragma once
#include "CState.h"


class CNormalMonDie :
    public CState
{

public:
    CNormalMonDie();
    ~CNormalMonDie();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CNormalMonDie);
};
