#pragma once
#include "CObj.h"

class CMonsterm :
    public CObj
{


private:

public:
    float m_Speed;
    virtual void tick(float _DT) override;
    void render(HDC _dc) override;
    CMonster();
    ~CMonster();
};

