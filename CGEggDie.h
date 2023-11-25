#pragma once
#include "CState.h"
class CGEggDie :
    public CState
{
    GENERATED_OBJECT(CState);

private:
    bool m_ItemDroped;
public:
    CGEggDie();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();

    ~CGEggDie();
    CLONE(CGEggDie);
};

