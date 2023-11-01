#pragma once
#include "CObj.h"

class CCollider;

class CSkill :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    wstring m_skillname;
    CCollider* m_Collider;
    CAnimator* m_Animator;
    float duration;
    float m_activedtime;
    float cooltime;
    float m_leftcool;
    float att;
    DEBUFF m_debuff;


public:
    virtual void begin() override;
    virtual void render(HDC _dc) override;
    virtual void tick(float _DT) override;
    virtual void BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol) override;
    void activate(Vec2 _beginpos,ORIENTATION _ort);



    CLONE(CSkill);
    CSkill();
    CSkill(const CSkill& _Origin);
    ~CSkill();

    friend class CSkillMgr;
};

