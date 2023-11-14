#pragma once
#include "CState.h"
class CDarkFallingIdle :
    public CState
{

public:
    CDarkFallingIdle();
    ~CDarkFallingIdle();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CDarkFallingIdle);

};
