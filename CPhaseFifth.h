#pragma once
#include "CLevel.h"

class CItem;

class CPhaseFifth :
    public CLevel
{
public:
    void dropitem();
    CItem* m_Itempool[40];

    ~CPhaseFifth();
    virtual void init() override;
    virtual void enter() override;
    virtual void exit() override;

    virtual void tick() override;
};
