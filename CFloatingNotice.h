#pragma once
#include "CUI.h"

class CTexture;

class CFloatingNotice :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture* lefttex;
    CTexture* midtex;
    CTexture* righttex;
    Vec2 m_leftscale;
    const float c_midwidth;

    float m_tmp_duration;
    wstring m_tmp_msg;
    int m_tmp_midcnt;
    float m_acctime;




public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    void FloatNotice(wstring _str, float _duration);

public:
    CLONE(CFloatingNotice);
    CFloatingNotice();
    ~CFloatingNotice();
};
