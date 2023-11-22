#pragma once
#include "CMonster.h"
class CBlackMage2 :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

public:
    CBlackMage2();
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CBlackMage2(const CBlackMage2& _Origin);
    ~CBlackMage2();


public:
    CLONE(CMonster);
};