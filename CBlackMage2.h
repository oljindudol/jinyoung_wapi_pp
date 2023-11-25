#pragma once
#include "CMonster.h"
class CBlackMage2 :
    public CMonster
{
    GENERATED_OBJECT(CMonster);

public:
    CBlackMage2();
    virtual void begin() override;
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    CBlackMage2(const CBlackMage2& _Origin);
    ~CBlackMage2();

private:
    float m_acctime;
    //스테이트 쿨타임배열
    const float m_cooltime[5];
    //스테이트 남은쿨타임배열
    float m_left_cool[5];
    //스테이트 별명 배열
    const wstring m_state_nick[5];
    //스테이트 매핑배열
    const UINT m_state_numarr[5];

    //스테이트 이름배열

    //스테이트 duration 배열


public:
    CLONE(CMonster);


    friend class CSecondBMIdle;
    friend class CStateDebugUI;
};