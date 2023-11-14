#pragma once
#include "CMonster.h"
class rulemon11 :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

public:
    virtual void begin() override;

public:
    virtual void tick(float _DT) override;


public:
    CLONE(CMonster);
    rulemon11();
    rulemon11(const rulemon11& _Origin);
    ~rulemon11();
};
