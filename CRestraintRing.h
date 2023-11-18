#pragma once
#include "CSkill.h"

class CRestraintRing :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    bool m_roop;
    bool m_end;
    class CSound* m_sound;

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort) override;


    CLONE_DISABLE(CRestraintRing);
    CRestraintRing();
    CRestraintRing(const CRestraintRing& _Origin);
    ~CRestraintRing();

};
