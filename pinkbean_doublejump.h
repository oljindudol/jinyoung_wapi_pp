#pragma once
#include "CSkill.h"

class pinkbean_doublejump :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


    CLONE_DISABLE(pinkbean_doublejump);
    pinkbean_doublejump();
    pinkbean_doublejump(const pinkbean_doublejump& _Origin);
    ~pinkbean_doublejump();

};

