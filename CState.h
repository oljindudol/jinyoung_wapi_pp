#pragma once
#include "CEntity.h"
#include "CStateMachine.h"

#include "CObj.h"
#include "CAnimator.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CMonster.h"
#include "CPlayer.h"
#include "CSkillMgr.h"

class CState :
    public CEntity
{
private:
    CStateMachine* m_pSM;
    UINT            m_StateID;

protected:
    float m_acctime;
    float m_stateduration;
    int m_skillortsign;
    CPlayer* m_pPlayer;




public:
    float Getacctime() { return m_acctime; }
    CStateMachine* GetOwnerSM() { return m_pSM; }
    CObj* GetOwner() { return GetOwnerSM()->GetOwner(); }
    UINT GetStateID() { return m_StateID; }


    void ChangeState(UINT _NextID) { GetOwnerSM()->ChangeState(_NextID); }
    class CAnimator* GetAnimator()
    {
        return GetOwnerSM()->GetAnimatorComponent();
    }

    class CMovement* GetMovement()
    {
        return GetOwnerSM()->GetMoveMentComponent();
    }
    class CCollider* GetCollider()
    {
        return GetOwnerSM()->GetColliderComponent();
    }

public:
    virtual void finaltick(float _DT) = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    virtual CState* Clone() = 0;

public:
    CState();
    ~CState();

    friend class CStateMachine;
};

