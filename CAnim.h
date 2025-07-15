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
		, vLeftTop(Vec2(0.f, 0.f))
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
	//배속
	float m_multi;
	ORIENTATION m_ort;

	//float m_mag;
	//int m_alpha;

public:
	//void SetMag(float _mag) { m_mag = _mag; }
	//float GetMag() { return m_mag; }
	//void SetAlpha(int _alpha) { m_alpha = _alpha; }
	//int GetAlpha() { return m_alpha; }

	Vec2 GetOffset() { return m_vecFrm[0].vOffset; }

	void Setoffset(Vec2 _offset)
	{
		for (auto& f : m_vecFrm)
		{
			f.vOffset = _offset;
		}
	}

	void finaltick();
	void render(HDC _dc);

public:
	// 일반 애님생성
	//void Create(const wstring& _strName, CTexture* _Atlas
	//    , Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm);

	// 아틀라스x 애님 생성
	void Create(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, Vec2 _vOffset, float _playmul);

	// 한바퀴 회전 애님 생성
	// period : 주기 
	// fpp :frame per period 한바퀴에 몇프레임
	void CreateTurn(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, Vec2 _vOffset, float _playmul, float _period, int _fpp);

	void CreateRotated(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, int _rot, Vec2 _vOffset, float _playmul);




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
	CAnim(const CAnim& other);
	CAnim();
	~CAnim();

	friend class CAnimator;
};

