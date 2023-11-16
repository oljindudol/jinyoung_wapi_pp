#pragma once
#include "CUI.h"

class CTexture;
class CMonster;

class CUpperBar :
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    vector<CTexture*>   vecbossthumbs;
    CTexture*           hptex;
    CTexture*           hpbarcovertex;
    CTexture*           percenttex;
    CTexture*           percentback;

    CTexture*           dethcountbacktex;
    vector<CTexture*>   vecdeathcnttex;

    CTexture*           timerbacktex;
    vector<CTexture*>   vectimetex;

    vector<CTexture*>   vecbindtex;
    float               m_hpbuffer;

    CMonster* CurLevelMon;
    int CurLevelNum;
    FRule* pRule;


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;
    virtual void begin() override;

public:
    CLONE(CUpperBar);
    CUpperBar();
    ~CUpperBar();
};