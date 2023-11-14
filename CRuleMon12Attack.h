#pragma once
#include "CState.h"
class CRuleMon12Attack :
    public CState
{
private:
    int attackcnt;

public:
    CRuleMon12Attack();
    ~CRuleMon12Attack();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CRuleMon12Attack);
};
