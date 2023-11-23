#pragma once
#include "CSkill.h"
class CSecondPowerRight :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    bool m_colon;
    bool m_used[3];
    float m_dietime;
public:
    CSecondPowerRight();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CSecondPowerRight(const CSecondPowerRight& _Origin);
    ~CSecondPowerRight();

    CLONE_DISABLE(CSecondPowerRight);
};