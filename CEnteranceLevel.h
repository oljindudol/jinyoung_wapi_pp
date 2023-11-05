#pragma once
#include "CLevel.h"
class CEnteranceLevel :
    public CLevel
{
public:
    //디버그용 나중에 몬스터매니저에 이관
    class CMonster* m_tmpmon;

    ~CEnteranceLevel();
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

