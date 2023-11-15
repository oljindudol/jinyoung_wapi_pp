#pragma once
#include "CState.h"
class CNormalMonAtt1 :
    public CState
{
    GENERATED_OBJECT(CState);
public:

    CNormalMonAtt1();
    ~CNormalMonAtt1();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    bool m_bigcollider;

    CLONE(CNormalMonAtt1);
};


