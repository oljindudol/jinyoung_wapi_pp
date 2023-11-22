#pragma once
#include "CComponent.h"
#include "CAnim.h"

class CAnim;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    // Animator 가 보유하고 있는 Animation 목록, 탐색을 위해서 Map 으로 
    map<wstring, CAnim*> m_mapAnim;

    // 현재 재생중인 Animation
    CAnim* m_CurAnim;

    // 반복 재생 여부
    bool                 m_bRepeat;

public:
    CAnim* GetCurAnim() { return m_CurAnim;  }
    Vec2 GetScale();
    void Play(const wstring& _strName);//, bool _bRepeat);
    void Stop();
    wstring GetCurAnimName() { return m_CurAnim->GetName(); }

    float GetCurAnimmulti() 
    {
        return m_CurAnim->m_multi;
    }


    // Animation 찾기
    CAnim* FindAnim(const wstring& _strName);

    // 애니메이션 생성
    //void CreateAnimation(const wstring& _strName, CTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize
    //    , Vec2 _vOffset, float _duration, int _MaxFrm);

    // 아틀라스x 애니메이션 생성
    void CreateAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname
        , Vec2 _vOffset = Vec2(),float _playmul = 1.f ,int _roop = 0 ,ORIENTATION _ort = ORT_LEFT);

    // 회전된 애니메이션 생성
    void CreateRotatedAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname
        , int _rot
        , Vec2 _vOffset = Vec2(),float _playmul = 1.f, int _roop = 0, ORIENTATION _ort = ORT_LEFT);

    void SaveAnimations(const wstring& _strRelativePath);
    void LoadAnimation(const wstring& _strRelativePath);

public:
    virtual void finaltick(float _DT) override;
    virtual void render(HDC _dc) override;

public:
    CLONE(CAnimator);
    CAnimator(CObj* _Owner);
    CAnimator(const CAnimator& _Origin);
    ~CAnimator();
};

