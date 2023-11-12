#pragma once
#include "CSkill.h"
class ChainAttack :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


    CLONE_DISABLE(ChainAttack);
    ChainAttack();
    ChainAttack(const ChainAttack& _Origin);
    ~ChainAttack();

};

