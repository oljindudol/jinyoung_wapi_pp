#pragma once
#include "CState.h"
class CRuleMon11Attack :
    public CState
{
private:
    int attackmax;
    int attackcnt;

public:
    CRuleMon11Attack();
    ~CRuleMon11Attack();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CRuleMon11Attack);
};

