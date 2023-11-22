#pragma once
#include "CState.h"
class CSecondBMNoxSpear :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CSecondBMNoxSpear();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CSecondBMNoxSpear();
    CLONE(CSecondBMNoxSpear);
};

