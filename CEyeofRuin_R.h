#pragma once
#include "CSkill.h"
class CPlayer;

class CEyeofRuin_R :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    float m_speed;
    CPlayer* pPlayer;
    float m_usetime, m_dietime;


public:
    CEyeofRuin_R();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CEyeofRuin_R(const CEyeofRuin_R& _Origin);
    ~CEyeofRuin_R();

    CLONE_DISABLE(CEyeofRuin_R);
};