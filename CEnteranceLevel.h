#pragma once
#include "CLevel.h"
class CEnteranceLevel :
    public CLevel
{
public:
    //����׿�
    class CMonster* m_tmpmon;

    ~CEnteranceLevel();
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

