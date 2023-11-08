#pragma once
#include "CUI.h"

class CTexture;

class CStatusUI:
    public CUI
{
    GENERATED_OBJECT(CUI);
private:
    HDC RenderDc;
    CTexture* backtex;
    CTexture* hptex;
    CTexture* mptex;
    CTexture* covertex;
    CTexture* lvtex;
    CTexture* nametex;
    vector<CTexture*> veclvtex;
    vector<CTexture*> vecgaugetex;
    void SetLettertoDc(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos,float _offset=0.f);
    void SettexturetoDc(HDC _dc, CTexture* _ptexture,Vec2 _pos);


    int testhp;
    float acctime;
    bool desc;


public:
    virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CStatusUI);
    CStatusUI();
    ~CStatusUI();
};


