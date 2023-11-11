#pragma once
#include "CState.h"
class CPlayer;

class CNormalMonRegen :
    public CState
{

public:
    CNormalMonRegen();
    ~CNormalMonRegen();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CNormalMonRegen);
};

