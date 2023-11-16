#pragma once
#include "CSkill.h"
class CDamageSkinRed :
    public CSkill
{
public:
    GENERATED_OBJECT(CSkill)
    vector<CTexture*> m_DamageSkinNumbers;
    vector<CTexture*> m_DamageSkinUnits;

    wstring m_temp_printdamage;
    vector<Vec2> m_temp_randomoffset;
    Vec2 m_temp_pos;
    float m_temp_delay;
    bool m_temp_ready;

    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    void PrintDamage(Vec2 _beginpos, long long _damage ,int _th);
    virtual void render(HDC _dc) override;

    virtual void begin() override;

    CLONE_DISABLE(CDamageSkinRed);
    CDamageSkinRed();
    CDamageSkinRed(const CDamageSkinRed& _Origin);
    ~CDamageSkinRed();
};


