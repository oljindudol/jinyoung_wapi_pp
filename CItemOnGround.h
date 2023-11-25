#pragma once
#include "CState.h"
class CItem;


class CItemOnGround :
    public CState
{
    GENERATED_OBJECT(CState);
private:
    Vec2 m_initialpos;
    Vec2 m_ItemVel;
    CItem* m_pItem;

public:
    CItemOnGround();
    virtual void finaltick(float _DT);
    virtual void Enter();
    virtual void Exit();
    ~CItemOnGround();

    CLONE(CItemOnGround);
};
