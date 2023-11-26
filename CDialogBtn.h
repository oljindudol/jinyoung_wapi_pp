#pragma once
#include "CBtnUI.h"

class CPlayer;
class CAmon;

class CDialogBtn :
    public CBtnUI
{
    GENERATED_OBJECT(CBtnUI);
public:
    CPlayer* m_player;
    CAmon* m_amon;

    CDialogBtn();
    virtual void begin() override;
    virtual void LBtnClicked(Vec2 _vMousePos)  override;
    ~CDialogBtn();

public:
    CLONE(CDialogBtn);
};
