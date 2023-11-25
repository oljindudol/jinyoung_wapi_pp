#pragma once
#include "CState.h"
class CItem;

class CItemOnAir:
	public CState
{
    GENERATED_OBJECT(CState);
private:
    Vec2 m_ItemVel;
    CItem* m_pItem;

public:
    CItemOnAir();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    ~CItemOnAir();

    CLONE(CItemOnAir);
};

