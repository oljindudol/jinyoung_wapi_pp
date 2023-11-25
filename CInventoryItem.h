#pragma once
#include "CBtnUI.h"

class CItemInfoUI;

class CInventoryItem :
    public CBtnUI
{
    GENERATED_OBJECT(CBtnUI);
public:
    CTexture* m_ItemIcon;
    CTexture* m_Iteminfo;
    CItemInfoUI* m_pCItemInfoUI;

    bool m_itemon;
    bool m_hovered;

    CInventoryItem();
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    virtual void OnUnHovered(Vec2 _vMousePos) override;
    virtual void OnHovered(Vec2 _vMousePos) override;
    virtual void MouseOn(Vec2 _vMousePos) override;
    virtual void LBtnClicked(Vec2 _vMousePos)  override;

    ~CInventoryItem();

public:
    CLONE(CInventoryItem);
};
