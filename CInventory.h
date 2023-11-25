#pragma once
#include "CUI.h"
class CInventoryItem;

class CInventory :
    public CUI
{
    GENERATED_OBJECT(CUI);
public:
    CTexture* m_UItex;
    CInventoryItem* itemarr[24];
    Vec2    m_vLbtnDownPos;

    CInventory();
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    virtual void LBtnDown(Vec2 _MousePos) override;
    void GetItem();
    ~CInventory();

public:
    CLONE(CInventory);
};
