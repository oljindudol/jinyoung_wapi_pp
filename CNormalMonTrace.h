#pragma once
#include "CState.h"

class CPlayer;

class CNormalMonTrace :
    public CState
{
    GENERATED_OBJECT(CState);
public:
    CNormalMonTrace();
    ~CNormalMonTrace();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    bool m_bigcollider;


    CLONE(CNormalMonTrace);
};

