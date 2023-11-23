#pragma once
#include "CSkill.h"
class CPlayer;
//class CTexture;

class CBlindness :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    CPlayer* m_pPlayer;
    CTexture* m_pMask;
    Vec2 m_vRes;

public:
    CBlindness();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
     virtual void render(HDC _dc) override;
    CBlindness(const CBlindness& _Origin);
    ~CBlindness();

    CLONE_DISABLE(CBlindness);
};
