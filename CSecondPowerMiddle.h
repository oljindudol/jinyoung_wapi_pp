#pragma once
#include "CSkill.h"
class CSecondPowerMiddle :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    CCollider* m_col2;
    bool m_colon;
    bool m_used[3];
    float m_dietime;
public:
    CSecondPowerMiddle();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CSecondPowerMiddle(const CSecondPowerMiddle& _Origin);
    ~CSecondPowerMiddle();

    CLONE_DISABLE(CSecondPowerMiddle);
};

