#pragma once
#include "CLevel.h"
class CPhaseSecond :
    public CLevel
{
public:

    ~CPhaseSecond();
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};
