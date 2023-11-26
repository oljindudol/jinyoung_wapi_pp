#pragma once
#include "CPanelUI.h"

class CPlayer;
class CAmon; 

class CDialogBox :
    public CPanelUI
{
    GENERATED_OBJECT(CPanelUI);
private:
    wstring  m_s1;
    wstring  m_s2;
    CPlayer* m_player;
    CAmon* m_amon;

public:
    CDialogBox();
    virtual void render(HDC _dc) override;
    virtual void begin() override;
    ~CDialogBox();

public:
    CLONE(CDialogBox);
};

