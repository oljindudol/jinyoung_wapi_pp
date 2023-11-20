#pragma once
#include "CState.h"

class CSkill;

class CPlayerAttSp :
    public CState
{

public:
    CPlayerAttSp();
    ~CPlayerAttSp();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    CSkill* ptmpskill;
    float m_animtime;

    CLONE(CPlayerAttSp);
};
