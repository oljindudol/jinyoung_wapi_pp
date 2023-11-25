#pragma once
#include "CUI.h"
class CItemInfoUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
public:
    CTexture* m_UItex;
    bool m_showtrigger;

    CItemInfoUI();
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    ~CItemInfoUI();

public:
    CLONE(CItemInfoUI);
};

