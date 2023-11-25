#pragma once
#include "CObj.h"

class CTexture;
class CCollider;

class CItem :
    public CObj
{
    GENERATED_OBJECT(CObj);
    wstring m_s1;
    int m_itemnum;

    //CMovement* m_Movement;
    CAnimator* m_Animator;
    CCollider* m_Collider;
    CStateMachine* m_SM;

public:
    CItem() = delete;
    CItem(wstring _name, int _number);

    virtual void begin() override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void render(HDC _dc);

    wstring GetItemName() { return m_s1; }
    int GetItemNumber() { return m_itemnum; }
    //CMovement* GetMovement() { return m_Movement; }
    CAnimator* GetAnimator() { return m_Animator; }
    CCollider* GetCollider() { return m_Collider; }
    CStateMachine* GetStateMachine() { return m_SM; }

    ~CItem();

public:


public:
    CLONE_DISABLE(CItem);


};

