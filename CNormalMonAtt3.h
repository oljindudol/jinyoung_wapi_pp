#pragma once
#include "CState.h"
class CNormalMonAtt3 :
    public CState
{
public:
    CNormalMonAtt3();
    ~CNormalMonAtt3();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    bool chased;
    bool stomped;

    CLONE(CNormalMonAtt3);
};

