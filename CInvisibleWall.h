#pragma once
#include "CObj.h"
class CInvisibleWall :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:

public:
    CInvisibleWall();
    virtual void tick(float _DT) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void begin() override;
    CInvisibleWall(const CInvisibleWall& _Origin);
    ~CInvisibleWall();

public:
    CLONE(CInvisibleWall);
};
