#pragma once
#include "CSkill.h"

class CTexture;
class CEndroll :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    wstring m_text;
    wstring owner_name;
    wstring owner_email;
    wstring tobecontinued;
    CTexture* m_veil;
    CTexture* m_veil2;

    CTexture* m_endrolltex;

    int m_alpha1;
    int m_alpha2;
    int m_alpha3;
    int m_digit;

public:
    CEndroll();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void render(HDC _dc) override;
    CEndroll(const CEndroll& _Origin);
    ~CEndroll();

    CLONE_DISABLE(CEndroll);
};