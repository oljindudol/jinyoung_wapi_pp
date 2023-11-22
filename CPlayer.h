#pragma once
#include "CObj.h"


class CPlayer :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    //HBITMAP hLoadBit;
    //HBITMAP m_Image;
    //HDC m_ImageDC;
    //BITMAP      m_BitmapInfo;
    //CCollider* m_Collider;
    //CTexture* m_pTexture;
    //CAnimator* m_Animator;
//    float             m_Speed;
    class CCollider* m_Collider;
    class CAnimator* m_Animator;
    class CMovement* m_Movement;
    class CStateMachine* m_PlayerState;
    float m_acctime;


public:
    int level;
    int maxhp;
    int hp;
    int maxmp;
    int mp;
    int att;
    int def;


    class CMovement* getMovement() { return m_Movement; }
    class CCollider* getCollider() { return m_Collider; }
    class CStateMachine* getStateMachine() { return m_PlayerState; }
    virtual void tick(float _DT) override;
    //더이상 오버라이드하지않고,애님에 이동한다.
    //void render(HDC _dc) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void EndOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void begin() override;
    void GetDamaged(float _percentdmg ,DEBUFF _debuff);

public:
    CLONE(CPlayer);
    CPlayer();
    CPlayer(const CPlayer& _Origin);
    ~CPlayer();

};

