#pragma once
#include "CComponent.h"
#include "CAnim.h"

class CAnim;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    // Animator �� �����ϰ� �ִ� Animation ���, Ž���� ���ؼ� Map ���� 
    map<wstring, CAnim*> m_mapAnim;

    // ���� ������� Animation
    CAnim* m_CurAnim;

    // �ݺ� ��� ����
    bool                 m_bRepeat;
    int m_alpha;
    float m_mag;

public:
    void SetMag(float _mag) { m_mag = _mag; }
    float GetMag() { return m_mag; }
    void SetAlpha(int _alpha) { m_alpha = _alpha; }
    int GetAlpha() { return m_alpha; }

    CAnim* GetCurAnim() { return m_CurAnim;  }
    Vec2 GetScale();
    CAnim* Play(const wstring& _strName);//, bool _bRepeat);
    void Stop();
    wstring GetCurAnimName() { return m_CurAnim->GetName(); }

    float GetCurAnimmulti() 
    {
        return m_CurAnim->m_multi;
    }


    // Animation ã��
    CAnim* FindAnim(const wstring& _strName);

    // �ִϸ��̼� ����
    //void CreateAnimation(const wstring& _strName, CTexture* _Altas, Vec2 _vLeftTop, Vec2 _vCutSize
    //    , Vec2 _vOffset, float _duration, int _MaxFrm);

    // ��Ʋ��x �ִϸ��̼� ����
    CAnim* CreateAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname
        , Vec2 _vOffset = Vec2(),float _playmul = 1.f ,int _roop = 0 ,ORIENTATION _ort = ORT_LEFT);

    // �ѹ��� ȸ�� �ִϸ��̼� ����
    // period : �ֱ� 
    // fpp :frame per period �ѹ����� ��������
    CAnim* CreateTurnAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, float _period, int _fpp
        , Vec2 _vOffset = Vec2(),  float _playmul = 1.f, int _roop = 0, ORIENTATION _ort = ORT_LEFT);


    // ȸ���� �ִϸ��̼� ����
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

