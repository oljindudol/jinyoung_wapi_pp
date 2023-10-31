#pragma once
#include "CObj.h"
#include "CLevel.h"

class CCollider;

class CProjectile :
    public CObj
{
private:
    CCollider* m_Collider;
    float   m_Speed;
    float   m_Angle;
    float   m_mass;

public:
    void SetAngle(float _theta) { m_Angle = _theta; }
    void SetSpeed(float _Speed) { m_Speed = _Speed; }
    void addforce(float _force , float _DT);
    float GetSpeed() { return m_Speed; }
    float GetAngle() { return m_Angle; };

    CCollider* GetCollider() { return m_Collider; }

public:
    //virtual void tick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CProjectile);
    CProjectile();
    CProjectile(const CProjectile& _Origin);
    ~CProjectile();
};

