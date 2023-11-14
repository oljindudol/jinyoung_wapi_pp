#pragma once
#include "CMonster.h"
class CDarkFalling :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

public:
    virtual void begin() override;

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CMonster);
    CDarkFalling();
    CDarkFalling(const CDarkFalling& _Origin);
    ~CDarkFalling();
};

