#pragma once
#include "CState.h"
class CPlayerAttNorm :
    public CState
{

public:
    CPlayerAttNorm();
    ~CPlayerAttNorm();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CPlayerAttNorm);
};

