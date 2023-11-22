#pragma once
#include "CMonster.h"
class CMorningStarFall :
    public CMonster
{
    GENERATED_OBJECT(CMonster);
private:
    bool m_metfloor;
public:
    bool IsMetFloor() { return m_metfloor; }
    virtual void begin() override;
    CMorningStarFall();
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;

    CMorningStarFall(const CMorningStarFall& _Origin);
    ~CMorningStarFall();

public:
    CLONE(CMonster);
};
