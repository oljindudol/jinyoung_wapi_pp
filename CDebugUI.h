#pragma once
#include "CUI.h"
class CDebugUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
public:
    CTexture* m_UItex;
    CDebugUI();
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    ~CDebugUI();

public:
    CLONE(CDebugUI);
};