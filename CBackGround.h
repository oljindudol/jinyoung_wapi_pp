#pragma once
#include "CObj.h"

class CTexture;

class CBackGround :
    public CObj
{
    GENERATED_OBJECT(CObj);

private:
    CTexture* m_Texture;

public:
    virtual void begin() override;
    virtual void render(HDC _dc) override;
    virtual void tick(float _DT) override;

    CLONE_DISABLE(CBackGround);
    CBackGround();
    void SetTextre(CTexture* _Texture) { m_Texture = _Texture; }
    CTexture* GetTextre() { return m_Texture; }
    CBackGround(const CBackGround& _Origin) = delete;
    ~CBackGround();
};

