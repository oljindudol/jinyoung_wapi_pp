#pragma once
#include "CSkill.h"


class pinkbean_phantomblow :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


    CLONE_DISABLE(pinkbean_phantomblow);
    pinkbean_phantomblow();
    pinkbean_phantomblow(const pinkbean_phantomblow& _Origin);
    ~pinkbean_phantomblow();

};