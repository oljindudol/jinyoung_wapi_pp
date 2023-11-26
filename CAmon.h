#pragma once
#include "CMonster.h"

class CUI;

class CAmon :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

private:
    CUI*        m_dialogbox;
    CAnimator*  m_pAnimator2;
    ENPC_STATE  m_npcstate;

public:
    CAmon();
    virtual void tick(float _DT) override;
    virtual void begin() override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CAmon(const CAmon& _Origin);
    ~CAmon();

    CLONE_DISABLE(CAmon);


    friend class CDialogBox;
    friend class CDialogBtn;
};