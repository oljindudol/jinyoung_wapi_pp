#pragma once
#include "CState.h"
class CDarkFallingRegen :
    public CState
{

public:
    CDarkFallingRegen();
    ~CDarkFallingRegen();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CDarkFallingRegen);

};
