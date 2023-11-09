#pragma once
#include "CEntity.h"

class CTexture;

struct FFrame
{
    CTexture* m_Atlas;
    CTexture* m_Atlas_r;
    Vec2 vLeftTop;  // 아틀라스 내에서 잘라낼 좌상단 위치
    Vec2 vCutSize;  // 잘라낼 크기
    Vec2 vOffset;   // 오브젝트 중심에서 이동 값
    float Duration; // 해당 프레임 노출 시간

    FFrame()
        :m_Atlas(nullptr)
        , m_Atlas_r(nullptr)
        , vLeftTop(Vec2(0.f,0.f))
        , vCutSize(Vec2(0.f, 0.f))
        , vOffset(Vec2(0.f, 0.f))
        , Duration(0.f)
    {

    }
};


class CAnimator;

class CAnim :
    public CEntity
{
private:
    CAnimator* m_pAnimator;

    vector<FFrame>  m_vecFrm;
    CTexture* m_Atlas;
    int             m_iCurFrm;

    // 누적 시간
    float           m_AccTime;

    // animation 재생 완료 체크
    bool            m_bFinish;
    // -1 루프안함, 루프할 프레임
    int            m_iRoop;
    ORIENTATION m_ort;


public:
    void finaltick();
    void render(HDC _dc);

public:
    void Create(const wstring& _strName, CTexture* _Atlas
        , Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm);

    // 아틀라스x 애님 생성
    void Create(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, Vec2 _vOffset , float _playmul );

    bool IsFinish() { return m_bFinish; }

    void Reset()
    {
        m_AccTime = 0.f;
        m_iCurFrm = m_iRoop;
        m_bFinish = false;
    }

    bool Save(const wstring& _FilePath);
    bool Load(const wstring& _FilePath);

public:
    CLONE(CAnim);

    CAnim();
    ~CAnim();

    friend class CAnimator;
};

