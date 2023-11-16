#pragma once
#include "CSkill.h"

class CTexture;

class CDamageSkin :
    public CSkill
{
    GENERATED_OBJECT(CSkill);
public:
    vector<CTexture*> m_DamageSkinNumbers;
    vector<CTexture*> m_DamageSkinUnits;

    wstring m_temp_printdamage;
    vector<Vec2> m_temp_randomoffset;
    Vec2 m_temp_pos;

    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    void PrintDamage(Vec2 _beginpos, int _damage);
    virtual void render(HDC _dc) override;

    virtual void begin() override;

    CLONE_DISABLE(CDamageSkin);
    CDamageSkin();
    CDamageSkin(const CDamageSkin& _Origin);
    ~CDamageSkin();
};

