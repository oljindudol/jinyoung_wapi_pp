#pragma once
#include "CMonster.h"
class ion :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

    public:
        virtual void begin() override;

    public:
        virtual void tick(float _DT) override;
        virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

    public:
        CLONE(CMonster);
        ion();
        ion(const ion& _Origin);
        ~ion();
};

