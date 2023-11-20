#pragma once
#include "CUI.h"

class CTexture;
class CSkill;

struct FCoolAlert
{
    bool isstarted;
    float duration;
    float acctime;
    CTexture* tex;
};

class QuickSlotUI :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture* backtex;
    vector<CSkill*> m_VecSkill;
    vector<CTexture*> m_VecIcon;
    vector<CTexture*> m_VecGrayIcon;
    vector< CTexture*> m_VecShortCutKey;
    //쿨타임 알리미
    vector<CTexture*> m_VecCoolDownNum;
    vector<CTexture*> m_VecCoolAlertTex;

    list< FCoolAlert> m_AlertList;

    void AlertRender2(HDC _dc, Vec2 _pos, CTexture* _icon);
    void AlertRender1(HDC _dc, Vec2 _pos, int num);


public:
    QuickSlotUI();
    ~QuickSlotUI();
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    bool IsCoolTime(wstring _skillname);
    int col;
    int row;
    Vec2 tilesize;
    float mag;

private:
    void SetAlert(CTexture* _pTex);


public:
    CLONE(QuickSlotUI);
};
