#pragma once
#include "CSkill.h"
class CSound;


class CBladeTornado :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    CSound* m_sound;
    wstring m_strhitsound;
    bool m_hitboxoff[5];
    bool m_animon;
    int m_tmp_ortsign;

public:
    CBladeTornado();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

    ~CBladeTornado();
    CLONE_DISABLE(CBladeTornado);

};