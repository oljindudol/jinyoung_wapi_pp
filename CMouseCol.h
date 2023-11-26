#pragma once
#include "CSkill.h"
class CMouseCol :
    public CSkill
{
    GENERATED_OBJECT(CSkill);
public:
    CMouseCol();
    CMouseCol(const CMouseCol& _Origin);
    virtual void begin() override;
    ~CMouseCol();

    CLONE_DISABLE(CMouseCol);
};
