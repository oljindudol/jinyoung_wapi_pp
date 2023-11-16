#include "pch.h"
#include "CSoundMgr.h"

#include "CEngine.h"
#include "CSound.h"
#include "CAssetMgr.h"
#include "CTimeManager.h"

CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
}

int CSoundMgr::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"사운드 디바이스 생성 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// 사운드 협조레벨 설정
	HWND hWnd = CEngine::GetInst()->GetMainWind();
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"사운드 매니저 초기화 실패", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	CAssetMgr::GetInst()->LoadSound(L"팬블use", L"sound\\팬블Use.wav");
	CAssetMgr::GetInst()->LoadSound(L"팬블hit", L"sound\\팬블Hit.wav");




	return true;



}

void CSoundMgr::tick()
{
	// 사운드 이벤트가 없으면 리턴
	if (m_EventList.empty())
		return;

	// 사운드 이벤트가 존재한다면
	FSoundEvent& evnt = m_EventList.front();
	if (false == evnt.played)
	{
		evnt.pSound->Play(false);
		evnt.played = true;
	}
	evnt.AccTime += DT;
	if (evnt.Duration <= evnt.AccTime)
	{
		if (evnt.stop)
			evnt.pSound->Stop(true);
		m_EventList.pop_front();
	}

}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}

void CSoundMgr::SetShortSound(wstring _strsound, float _time)
{
	FSoundEvent evnt = {};
	evnt.pSound = CAssetMgr::GetInst()->LoadSound(_strsound, L"");
	evnt.stop = true;
	evnt.AccTime = 0.f;
	evnt.Duration = _time;
	evnt.played = false;
	m_EventList.push_back(evnt);
}

void CSoundMgr::SetLongSound(wstring _strsound, float _time)
{
	FSoundEvent evnt = {};
	evnt.pSound = CAssetMgr::GetInst()->LoadSound(_strsound, L"");
	evnt.stop = false;
	evnt.AccTime = 0.f;
	evnt.Duration = _time;
	evnt.played = false;
	m_EventList.push_back(evnt);
}
