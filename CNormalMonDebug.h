#pragma once
#include "CState.h"
class CNormalMonDebug :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CNormalMonDebug();
    ~CNormalMonDebug();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    bool chased;
    bool stomped;
    bool up;
    CMonster* m_other;

    CLONE(CNormalMonDebug);
};
