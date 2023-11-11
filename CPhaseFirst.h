#pragma once
#include "CLevel.h"
class CPhaseFirst :
    public CLevel
{
public:

    ~CPhaseFirst();
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};


