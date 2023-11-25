#pragma once
#include "CState.h"

class CItem;
class CAnim;

class CItemAbsorbing :
    public CState
{
    GENERATED_OBJECT(CState);
private:
    Vec2 m_ItemVel;
    CItem* m_pItem;
    CAnim* m_pAnim;

public:
    CItemAbsorbing();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    ~CItemAbsorbing();

    CLONE(CItemAbsorbing);
};
