#pragma once
#include "CSkill.h"

class CSound;
class CPlayer;

class CBladeStorm :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    CSound* m_sound;
    wstring m_strhitsound;
    bool m_hitboxoff[42];
    CPlayer* m_Player;

public:
    CBladeStorm();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

    ~CBladeStorm();
    CLONE_DISABLE(CBladeStorm);

};