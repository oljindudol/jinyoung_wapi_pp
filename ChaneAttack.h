#pragma once
#include "CSkill.h"
class ChaneAttack :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


    CLONE_DISABLE(ChaneAttack);
    ChaneAttack();
    ChaneAttack(const ChaneAttack& _Origin);
    ~ChaneAttack();

};

