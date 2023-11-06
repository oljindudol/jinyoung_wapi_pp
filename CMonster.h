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
    wstring m_s1;
    wstring m_s2;
    wstring m_monstername;
    int m_monsternum;

    FMonInfo        m_Info;
    CCollider* m_Collider;
    CStateMachine* m_AI;
    CAnimator* m_Animator;
    CMovement* m_Movement ;
    bool m_OnActivate;

public:
    virtual void begin() override;
    virtual void Spawn(Vec2 _Spawnpos);
    void SetMonsterInfo(const FMonInfo& _Info) { m_Info = _Info; }
    //virtual void render(HDC _dc) override;

public:
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;


public:
    CLONE(CMonster);
    CMonster();
    CMonster(const CMonster& _Origin);
    ~CMonster();


    friend class CMonsterMgr;
};

