#pragma once
#include "CState.h"
class CRuleMon11Idle :
    public CState
{

public:
    CRuleMon11Idle();
    ~CRuleMon11Idle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CRuleMon11Idle);

};

