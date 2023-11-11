#pragma once
#include "CObj.h"
class CPortal :
    public CObj
{
    GENERATED_OBJECT(CObj);
private:
    LEVEL_TYPE m_togo;
    CAnimator* m_animator;
    CCollider* m_collider;


    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CPortal);
    CPortal();
    CPortal(const CPortal& _Origin);
    ~CPortal();
};

