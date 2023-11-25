#include "pch.h"
#include "CAnimator.h"

#include "CAnim.h"
#include "CPathMgr.h"

#include "CLogMgr.h"

CAnimator::CAnimator(CObj* _Owner)
	: CComponent(_Owner)
	, m_CurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _Origin)
	: CComponent(_Origin)
	, m_CurAnim(nullptr)
	, m_bRepeat(_Origin.m_bRepeat)
{
	for (const auto& pair : _Origin.m_mapAnim)
	{
		CAnim* pAnim = pair.second->Clone();
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(pair.first, pAnim));
	}

	if (nullptr != _Origin.m_CurAnim)
	{
		m_CurAnim = FindAnim(_Origin.m_CurAnim->GetName());
		m_CurAnim->Reset();
	}
}

CAnimator::~CAnimator()
{
	for (const auto& pair : m_mapAnim)
	{
		delete pair.second;
	}
}

void CAnimator::finaltick(float _DT)
{
	if (IsValid(m_CurAnim))
	{
		if ((m_CurAnim->m_iRoop>-1) && m_CurAnim->IsFinish())
		{
			m_CurAnim->Reset();
		}

		m_CurAnim->finaltick();
	}
}

void CAnimator::render(HDC _dc)
{
	if (IsValid(m_CurAnim))
	{
		m_CurAnim->render(_dc);
	}
}

Vec2 CAnimator::GetScale()
{
	if (nullptr != m_CurAnim)
	{
		return m_CurAnim->m_vecFrm[0].vCutSize;
	}
	return Vec2();
}

CAnim* CAnimator::Play(const wstring& _strName)
{
	//m_bRepeat = _bRepeat;

	m_CurAnim = FindAnim(_strName);
	m_CurAnim->m_bFinish = false;
	m_CurAnim->m_iCurFrm = 0;

	return m_CurAnim;
}

void CAnimator::Stop()
{
}

CAnim* CAnimator::FindAnim(const wstring& _strName)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}

//일반 애니메이션 생성
//void CAnimator::CreateAnimation(const wstring& _strName, CTexture* _Altas,
//	Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm)
//{
//	CAnim* pAnim = FindAnim(_strName);
//	if (IsValid(pAnim))
//	{
//		return;
//	}
//
//	pAnim = new CAnim;
//	pAnim->m_pAnimator = this;
//	pAnim->Create(_strName, _Altas, _vLeftTop, _vCutSize, _vOffset, _Duration, _MaxFrm);
//	m_mapAnim.insert(make_pair(_strName, pAnim));
//}


//아틀라스 x 일반애니메이션 
// roop == 0 은 일반루프
// roop == -1 은 루프안함
// roop == 그외숫자는 루프할때 돌아갈 프레임
CAnim* CAnimator::CreateAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, Vec2 _vOffset , float _playmul,int _roop, ORIENTATION _ort)
{
	CAnim* pAnim = FindAnim(_strphase+ _strobj+ _stranimname);
	if (IsValid(pAnim))
	{
		return nullptr;
	}

	pAnim = new CAnim;
	pAnim->m_pAnimator = this;
	pAnim->m_iRoop = _roop;
	pAnim->m_ort = _ort;
	pAnim->Create(_strphase, _strobj, _stranimname,_vOffset,_playmul);
	m_mapAnim.insert(make_pair(_strphase + _strobj + _stranimname, pAnim));

	return pAnim;
}

CAnim* CAnimator::CreateTurnAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, float _period, int _fpp
	, Vec2 _vOffset, float _playmul, int _roop, ORIENTATION _ort)
{
	CAnim* pAnim = FindAnim(_strphase + _strobj + _stranimname);
	if (IsValid(pAnim))
	{
		return nullptr;
	}

	pAnim = new CAnim;
	pAnim->m_pAnimator = this;
	pAnim->m_iRoop = _roop;
	pAnim->m_ort = _ort;

	pAnim->CreateTurn(_strphase, _strobj, _stranimname, _vOffset,_playmul ,_period, _fpp);
	m_mapAnim.insert(make_pair(_strphase + _strobj + _stranimname, pAnim));

	return pAnim;
}



void CAnimator::CreateRotatedAnimation(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, int _rot, Vec2 _vOffset, float _playmul, int _roop, ORIENTATION _ort)
{
	CAnim* pAnim = FindAnim(_strphase + _strobj + _stranimname +L"_"+std::to_wstring(_rot));
	if (IsValid(pAnim))
	{
		return;
	}

	pAnim = new CAnim;
	pAnim->m_pAnimator = this;
	pAnim->m_iRoop = _roop;
	pAnim->m_ort = _ort;
	pAnim->CreateRotated(_strphase, _strobj, _stranimname , _rot, _vOffset, _playmul);
	m_mapAnim.insert(make_pair(_strphase + _strobj + _stranimname + L"_" + std::to_wstring(_rot), pAnim));
}

void CAnimator::SaveAnimations(const wstring& _strRelativePath)
{
	wstring strFolderPath = CPathMgr::GetContentPath();
	strFolderPath += _strRelativePath;

	for (const auto& pair : m_mapAnim)
	{
		wstring strFilePath = strFolderPath + L"\\" + pair.first + L".txt";
		if (!pair.second->Save(strFilePath))
		{
			LOG(ERR, L"Animation Save 실패");
		}
	}
}

void CAnimator::LoadAnimation(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	CAnim* pNewAnim = new CAnim;

	if (!pNewAnim->Load(strFilePath))
	{
		LOG(ERR, L"Animation Load 실패");
		delete pNewAnim;
		return;
	}

	pNewAnim->m_pAnimator = this;
	m_mapAnim.insert(make_pair(pNewAnim->GetName(), pNewAnim));
}
