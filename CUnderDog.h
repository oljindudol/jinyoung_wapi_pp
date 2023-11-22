#pragma once
#include "CSkill.h"
class CUnderDog :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    float m_MetWallTime;
public:
    CUnderDog();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CUnderDog(const CUnderDog& _Origin);
    ~CUnderDog();

    CLONE_DISABLE(CUnderDog);
};