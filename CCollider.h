#pragma once

#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2    m_vScale;      // Owner �κ��� �߰� ����

    Vec2    m_vFinalPos;   // �浹ü�� ���� ��ġ

    Vec2	m_PrevFinalPos; //�浹ü ���� ������ġ : �÷����浹�� ���

    int     m_iCollisionCount;

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    void SetOffsetPos(Vec2 _vOffsetPos) { m_vOffsetPos = _vOffsetPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    Vec2 GetPos() { return m_vFinalPos; }
    Vec2 GetPrevPos() { return m_PrevFinalPos; }

    void InitColCnt() { m_iCollisionCount = 0; }


    Vec2 GetOffsetPos() { return m_vOffsetPos; }
    Vec2 GetScale() { return m_vScale; }

    void BeginOverlap(CCollider* _OtherCol);
    void Overlap(CCollider* _OtherCol);
    void EndOverlap(CCollider* _OtherCol);

public:
    virtual CCollider* Clone() { return new CCollider(*this); }
    Vec2    m_vOffsetPos;  // Owner �κ��� ������ �Ÿ�

public:
    CCollider(CObj* _Owner);
    CCollider(const CCollider& _Origin);
    ~CCollider();

};

