#pragma once
#include "CState.h"
class CDarkFallingDie :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CDarkFallingDie();
    ~CDarkFallingDie();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    CLONE(CDarkFallingDie);

};

