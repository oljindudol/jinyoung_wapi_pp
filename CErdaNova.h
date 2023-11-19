#pragma once
#include "CSkill.h"

class CSound;

class CErdaNova :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    CSound* m_sound;
    wstring m_strhitsound;
    bool m_hitboxon;

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort) override;

    CLONE_DISABLE(CErdaNova);
    CErdaNova();
    ~CErdaNova();

};
