#pragma once
#include "CUI.h"


class CPanelUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    Vec2    m_vLbtnDownPos;
public:
    virtual void LBtnDown(Vec2 _MousePos) override;
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CPanelUI);
    CPanelUI();
    ~CPanelUI();
};

