#pragma once
#include "CObj.h"

class CCollider;

class CSkill :
    public CObj
{
    GENERATED_OBJECT(CObj);

protected:
    wstring m_s1;
    wstring m_s2;
    wstring m_s3;
    wstring m_skillname;
    int m_skillnum;
    CCollider* m_Collider;
    CAnimator* m_Animator;
    float duration;
    float m_activedtime;
    float cooltime;
    float m_leftcool;
    float m_att;
    DEBUFF m_debuff;
    bool m_OnActivate;
    LAYER m_skilllayer;


public:
    float GetAtt() { return m_att; }
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    virtual void activate(Vec2 _beginpos,ORIENTATION _ort);
    virtual void begin();


    CLONE_DISABLE(CSkill);
    CSkill();
    CSkill(const CSkill& _Origin);
    ~CSkill();

    friend class CSkillMgr;
};

