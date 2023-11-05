#pragma once
#include "CLevel.h"
class CEnteranceLevel :
    public CLevel
{
public:

    ~CEnteranceLevel();
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};

