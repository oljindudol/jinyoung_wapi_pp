#pragma once
#include "CMonster.h"
class CGenesisEgg :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

public:
    CGenesisEgg();
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CGenesisEgg(const CGenesisEgg& _Origin);
    ~CGenesisEgg();

public:
    CLONE(CMonster);

};