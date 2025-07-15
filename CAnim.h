#pragma once
#include "CEntity.h"

class CTexture;

struct FFrame
{
	CTexture* m_Atlas;
	CTexture* m_Atlas_r;
	Vec2 vLeftTop;  // ��Ʋ�� ������ �߶� �»�� ��ġ
	Vec2 vCutSize;  // �߶� ũ��
	Vec2 vOffset;   // ������Ʈ �߽ɿ��� �̵� ��
	float Duration; // �ش� ������ ���� �ð�

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

	// ���� �ð�
	float           m_AccTime;

	// animation ��� �Ϸ� üũ
	bool            m_bFinish;
	// -1 ��������, ������ ������
	int            m_iRoop;
	//���
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
	// �Ϲ� �ִԻ���
	//void Create(const wstring& _strName, CTexture* _Atlas
	//    , Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm);

	// ��Ʋ��x �ִ� ����
	void Create(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, Vec2 _vOffset, float _playmul);

	// �ѹ��� ȸ�� �ִ� ����
	// period : �ֱ� 
	// fpp :frame per period �ѹ����� ��������
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

