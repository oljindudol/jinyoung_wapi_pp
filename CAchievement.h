#pragma once
#include "CSkill.h"

class CAnim;
class CAchievement :
    public CSkill
{
    GENERATED_OBJECT(CSkill);

private:
    wstring m_text;
    CAnim* m_pAnim;
public:
    CAchievement();
    virtual void tick(float _DT) override;
    virtual void activate(Vec2 _beginpos, ORIENTATION _ort);
    virtual void begin() override;
    virtual void render(HDC _dc) override;
    CAchievement(const CAchievement& _Origin);
    ~CAchievement();

    CLONE_DISABLE(CAchievement);
};