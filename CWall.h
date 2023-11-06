#pragma once
#include "CObj.h"
class CWall :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    class CCollider* m_Collider;


public:
    virtual void tick(float _DT) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CWall);
    CWall();
    CWall(const CWall& _Origin);
    ~CWall();
};


