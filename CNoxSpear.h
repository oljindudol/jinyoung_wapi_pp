#pragma once
#include "CSkill.h"
class CNoxSpear :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

public:
    CNoxSpear();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CNoxSpear(const CNoxSpear& _Origin);
    ~CNoxSpear();

    CLONE_DISABLE(CNoxSpear);
};
