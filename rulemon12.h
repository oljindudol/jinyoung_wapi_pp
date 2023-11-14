#pragma once
#include "CMonster.h"
class rulemon12 :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

public:
    virtual void begin() override;

public:
    virtual void tick(float _DT) override;


public:
    CLONE(CMonster);
    rulemon12();
    rulemon12(const rulemon12& _Origin);
    ~rulemon12();
};

