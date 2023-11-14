#pragma once
#include "CState.h"
class CRuleMon12Idle :
    public CState
{

public:
    CRuleMon12Idle();
    ~CRuleMon12Idle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CRuleMon12Idle);

};

