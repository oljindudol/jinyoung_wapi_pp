#pragma once
#include "CUI.h"
#include "CStatusUI.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"


class CTexture;

class CStatusUI:
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    CTexture* backtex;
    CTexture* hptex;
    CTexture* mptex;
    CTexture* covertex;
    CTexture* lvtex;
    CTexture* nametex;
    vector<CTexture*> veclvtex;
    vector<CTexture*> vecgaugetex;
    wstring slash;
    wstring charname;
    CTexture* exptex;
    CTexture* expcovertex;

    //void SetLettertoDc(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos,float _offset=0.f);
    //void SettexturetoDc(HDC _dc, CTexture* _ptexture,Vec2 _pos);


    float m_hpbuffer;
    float m_mpbuffer;
    float m_acctime;


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CStatusUI);
    CStatusUI();
    ~CStatusUI();
};


