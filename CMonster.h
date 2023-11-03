#pragma once
#include "CObj.h"


#include "CPlatform.h"
#include "CSkill.h"
class CTexture;


class CCollider;

class CMonster :
    public CObj
{
    GENERATED_OBJECT(CObj);

protected:
    FMonInfo        m_Info;
    CCollider* m_Collider;
    CStateMachine* m_AI;
    CAnimator* m_Animator;
    CMovement* m_Movement ;

public:
    virtual void begin() override;
    void SetMonsterInfo(const FMonInfo& _Info) { m_Info = _Info; }
    //virtual void render(HDC _dc) override;

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CMonster);
    CMonster();
    CMonster(const CMonster& _Origin);
    ~CMonster();
};

