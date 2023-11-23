#pragma once
#include "CSkill.h"
class CSecondPowerLeft :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    bool m_used;
    float m_dietime;
public:
    CSecondPowerLeft();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CSecondPowerLeft(const CSecondPowerLeft& _Origin);
    ~CSecondPowerLeft();

    CLONE_DISABLE(CSecondPowerLeft);
};