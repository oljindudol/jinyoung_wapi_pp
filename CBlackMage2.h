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
    //������Ʈ ��Ÿ�ӹ迭
    const float m_cooltime[5];
    //������Ʈ ������Ÿ�ӹ迭
    float m_left_cool[5];
    //������Ʈ ���� �迭
    const wstring m_state_nick[5];
    //������Ʈ ���ι迭
    const UINT m_state_numarr[5];

    //������Ʈ �̸��迭

    //������Ʈ duration �迭


public:
    CLONE(CMonster);


    friend class CSecondBMIdle;
    friend class CStateDebugUI;
};