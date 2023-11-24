#pragma once
#include "CUI.h"

class CBlackMage2;
class CStateDebugUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
public:
    CBlackMage2* m_bm2;
    CTexture* m_UItex;
    CStateDebugUI();
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    ~CStateDebugUI();

public:
    CLONE(CStateDebugUI);
};