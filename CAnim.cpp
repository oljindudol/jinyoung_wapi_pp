#include "pch.h"
#include "CAnim.h"

#include "CAnimator.h"
#include "CObj.h"
#include "CCamera.h"
#include "CTexture.h"
#include "CTimeManager.h"
#include "CLogMgr.h"
#include "CAssetMgr.h"
#include "CPathMgr.h"
#include "CEngine.h"

#include <algorithm>
#include <filesystem>

using namespace std;

CAnim::CAnim()
	: m_pAnimator(nullptr)
	, m_Atlas(nullptr)
	, m_iCurFrm(0)
	, m_bFinish(false)
	, m_bRoop(true)
	, m_AccTime(0.f)
	, m_ort(ORT_LEFT)
{
}

CAnim::~CAnim()
{
}

void CAnim::finaltick()
{
	if (m_bFinish)
		return;

	m_AccTime += DT;

	if (m_vecFrm[m_iCurFrm].Duration < m_AccTime)
	{
		m_AccTime = 0.f;

		if (m_vecFrm.size() - 1 <= m_iCurFrm)
		{
			m_bFinish = true;
		}
		else
		{
			++m_iCurFrm;
		}
	}

}



void CAnim::render(HDC _dc)
{
	const FFrame& frm = m_vecFrm[m_iCurFrm];

	CObj* pOwnerObject = m_pAnimator->GetOwner();
	Vec2 vRenderPos = pOwnerObject->GetRenderPos();

	/*TransparentBlt(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
					  , int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
					  , int(frm.vCutSize.x), int(frm.vCutSize.y)
					  , m_Atlas->GetDC()
					  , int(frm.vLeftTop.x), int(frm.vLeftTop.y)
					  , int(frm.vCutSize.x), int(frm.vCutSize.y)
					  , RGB(255, 0, 255));*/

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 0

	HDC tmpdc = frm.m_Atlas->GetDC();;

	if(ORT_RIGHT==m_pAnimator->GetOwner()->ort){
		tmpdc = frm.m_Atlas_r->GetDC();
	}

	
	AlphaBlend(_dc, int(vRenderPos.x - (frm.vCutSize.x / 2.f) + frm.vOffset.x)
		, int(vRenderPos.y - (frm.vCutSize.y / 2.f) + frm.vOffset.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, tmpdc
		, int(frm.vLeftTop.x), int(frm.vLeftTop.y)
		, int(frm.vCutSize.x), int(frm.vCutSize.y)
		, blend);

}



void CAnim::Create(const wstring& _strName, CTexture* _Atlas
	, Vec2 _vLeftTop, Vec2 _vCutSize, Vec2 _vOffset, float _Duration, int _MaxFrm)
{
	SetName(_strName);

	m_Atlas = _Atlas;

	m_vecFrm.reserve(_MaxFrm);

	for (size_t i = 0; i < _MaxFrm; ++i)
	{
		FFrame frm = {};

		frm.vLeftTop = _vLeftTop + Vec2(_vCutSize.x * i, 0.f);
		frm.vCutSize = _vCutSize;
		frm.vOffset = _vOffset;
		frm.Duration = _Duration;

		m_vecFrm.push_back(frm);
	}
}

static bool comparefirst(pair<wstring, wstring> _p1, pair<wstring, wstring> _p2)
{
	return stoi(_p1.first) < stoi(_p2.first);
}

void CAnim::Create(const wstring& _strphase, const wstring& _strobj, const wstring& _stranimname, Vec2 _vOffset ,float _playmul )
{
	SetName(_strphase+ _strobj+_stranimname);



	wstring filePath = CPathMgr::GetContentPath();
	wstring addipath = 
		_strphase + L"\\"
		+ _strobj + L"\\"
		+ _stranimname;

	filePath += L"texture\\anim\\"
		+ addipath;

	vector<pair<wstring,wstring>> tmpvec;
	wstring t;


	for (auto& p : std::filesystem::directory_iterator(filePath))
	{

		t = p.path().filename();
		int idxu = t.find(L"_");
		tmpvec.push_back(
			pair<wstring, wstring>
			(t.substr(0,idxu), t.substr(idxu+1,t.find(L".png")- idxu-1))
		);

	}

	sort(tmpvec.begin(), tmpvec.end(),comparefirst);

	int maxfrm = tmpvec.size();
	m_vecFrm.reserve(maxfrm);

	wstring tmpname;

	for(int i=0;i<maxfrm;i++)
	{
		FFrame frm = {};
		tmpname = addipath +L"\\" + tmpvec[i].first + L"_" + tmpvec[i].second;

		CTexture* pAtlas = CAssetMgr::GetInst()->LoadTexture(tmpname, L"texture\\anim\\" +tmpname+L".png");
		CTexture* pAtlas_r = CAssetMgr::GetInst()->LoadTexture_r(tmpname + L"_r", L"texture\\anim\\" + tmpname + L".png");


		frm.m_Atlas = pAtlas;
		frm.m_Atlas_r = pAtlas_r;
		frm.vOffset = _vOffset;
		frm.Duration = ((stoi(tmpvec[i].second)- stoi(tmpvec[i].first))/1000.f)/_playmul;
		frm.vCutSize = Vec2(pAtlas->GetWidth(), pAtlas->GetHeight());
		m_vecFrm.push_back(frm);
	}


	//for (size_t i = 0; i < _MaxFrm; ++i)
	//{
	//	

	//	frm.vLeftTop = _vLeftTop + Vec2(_vCutSize.x * i, 0.f);
	//	frm.vCutSize = _vCutSize;
	//	frm.vOffset = _vOffset;
	//	frm.Duration = _Duration;

	//	m_vecFrm.push_back(frm);
	//}
}

bool CAnim::Save(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"w");

	if (nullptr == pFile)
	{
		LOG(ERR, L"파일 열기 실패");
		return false;
	}


	// Animation 이름 저장
	fwprintf_s(pFile, L"[ANIM_NAME]\n");

	wstring strName = GetName();
	fwprintf_s(pFile, strName.c_str());
	fwprintf_s(pFile, L"\n\n");
	//int iLen = 0;
	//iLen = strName.length();
	//fwrite(&iLen, sizeof(int), 1, pFile);
	//fwrite(strName.c_str(), sizeof(wchar_t), strName.length(), pFile);


	// 키, 경로
	fwprintf_s(pFile, L"[ATLAS_TEXTURE]\n");
	//bool bExist = m_Atlas;
	//fwrite(&bExist, sizeof(bool), 1, pFile);

	//if (bExist)

	wstring strKey;
	wstring strRelativePath;

	if (IsValid(m_Atlas))
	{
		strKey = m_Atlas->GetKey();
		strRelativePath = m_Atlas->GetRelativePath();
	}

	fwprintf_s(pFile, strKey.c_str());
	fwprintf_s(pFile, L"\n");
	fwprintf_s(pFile, strRelativePath.c_str());
	fwprintf_s(pFile, L"\n\n");

	// 프레임 데이터
	// 프레임 숫자
	fwprintf_s(pFile, L"[FRAME_COUNT]\n");
	fwprintf_s(pFile, L"%d\n\n", (int)m_vecFrm.size());


	for (int i = 0; i < (int)m_vecFrm.size(); ++i)
	{
		fwprintf_s(pFile, L"[FRAME_NUM]\n");
		fwprintf_s(pFile, L"%d\n", i);

		fwprintf_s(pFile, L"[LEFT_TOP]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vLeftTop.x, m_vecFrm[i].vLeftTop.y);

		fwprintf_s(pFile, L"[CUT_SIZE]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vCutSize.x, m_vecFrm[i].vCutSize.y);

		fwprintf_s(pFile, L"[OFFSET]\n");
		fwprintf_s(pFile, L"%f %f\n", m_vecFrm[i].vOffset.x, m_vecFrm[i].vOffset.y);

		fwprintf_s(pFile, L"[DURATION]\n");
		fwprintf_s(pFile, L"%f\n\n", m_vecFrm[i].Duration);
	}

	fclose(pFile);

	return true;
}

bool CAnim::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _FilePath.c_str(), L"r");

	if (nullptr == pFile)
	{
		LOG(ERR, L"파일 열기 실패");
		return false;
	}

	// Animation 이름 로드
	while (true)
	{
		wchar_t szRead[256] = {};
		if (EOF == fwscanf_s(pFile, L"%s", szRead, 256))
		{
			break;
		}

		if (!wcscmp(szRead, L"[ANIM_NAME]"))
		{
			fwscanf_s(pFile, L"%s", szRead, 256);
			SetName(szRead);
		}
		else if (!wcscmp(szRead, L"[ATLAS_TEXTURE]"))
		{
			wstring strKey, strRelativePath;

			fwscanf_s(pFile, L"%s", szRead, 256);
			strKey = szRead;

			fwscanf_s(pFile, L"%s", szRead, 256);
			strRelativePath = szRead;

			m_Atlas = CAssetMgr::GetInst()->LoadTexture(strKey, strRelativePath);
		}
		else if (!wcscmp(szRead, L"[FRAME_COUNT]"))
		{
			int iFrameCount = 0;
			fwscanf_s(pFile, L"%d", &iFrameCount);
			m_vecFrm.resize(iFrameCount);

			int iCurFrame = 0;
			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);

				if (!wcscmp(szRead, L"[FRAME_NUM]"))
				{
					fwscanf_s(pFile, L"%d", &iCurFrame);
				}
				else if (!wcscmp(szRead, L"[LEFT_TOP]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vLeftTop.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vLeftTop.y);
				}
				else if (!wcscmp(szRead, L"[CUT_SIZE]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vCutSize.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vCutSize.y);
				}
				else if (!wcscmp(szRead, L"[OFFSET]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vOffset.x);
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].vOffset.y);
				}
				else if (!wcscmp(szRead, L"[DURATION]"))
				{
					fwscanf_s(pFile, L"%f", &m_vecFrm[iCurFrame].Duration);

					if (iFrameCount - 1 <= iCurFrame)
						break;
				}
			}
		}
	}

	fclose(pFile);
	return true;
}