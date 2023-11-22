#pragma once
#include "CSkill.h"
class CEyeofRuin_L :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    Vec2 m_Vel;
    float m_usetime, m_dietime;
public:
    CEyeofRuin_L();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CEyeofRuin_L(const CEyeofRuin_L& _Origin);
    ~CEyeofRuin_L();

    CLONE_DISABLE(CEyeofRuin_L);
};