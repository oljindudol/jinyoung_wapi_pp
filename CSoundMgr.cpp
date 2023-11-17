#include "pch.h"
#include "CSoundMgr.h"

#include "CEngine.h"
#include "CSound.h"
#include "CAssetMgr.h"
#include "CTimeManager.h"
#include "CLogMgr.h"


CSoundMgr::CSoundMgr()
	: m_pSound(nullptr)
	, m_pBGM(nullptr)
{
}

CSoundMgr::~CSoundMgr()
{
	for (auto sp : m_VecSoundplayer)
	{
		delete sp;
	}
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

	for (int i = 0; i < 50; ++i)
	{
		m_VecSoundplayer.push_back(new CSoundPlayer);
	}

	LoadMultipleSound(L"팬블hit", L"sound\\팬블Hit.wav", 100);


	return true;
}

void CSoundMgr::LoadMultipleSound(wstring _key, wstring _relpath, int _cnt)
{
	CAssetMgr* pasm= CAssetMgr::GetInst();
	vector<CSound*> tmpvec;

	for (int i = 0; i < _cnt; ++i)
	{
		auto snd = pasm->LoadSound(_key + L"_" + std::to_wstring(i), _relpath);
		snd->SetVolume(25);
		tmpvec.push_back(snd);
	}
	//m_SoundMap.insert(pair<wstring, vector<CSound*>>( _key, tmpvec ));
	m_SoundMap.insert({_key, tmpvec});
}

CSound* CSoundMgr::GetPlayableSound(wstring _key)
{
	auto iter1 = m_SoundMap.begin();

	while (m_SoundMap.end() != iter1)
	{
		if (_key == (*iter1).first)
		{
			break;
		}
		++iter1;
	}

	if (m_SoundMap.end() == iter1)
	{
		//LOG :키에 해당하는 사운드벡터를 찾을 수 없음.
		LOG(LOG_LEVEL::LOG, L"키에 해당하는 사운드벡터를 찾을 수 없음")
		return nullptr;
	}

	auto vecsound = (*iter1).second;
	auto iter2 = vecsound.begin();

	while (vecsound.end() != iter2)
	{
		//float a = (*iter2)->GetPosition();

		if (0.f == (*iter2)->GetPosition())
		{
			(*iter2)->SetPosition(0.01f);
			break;
		}
		++iter2;
	}

	if (vecsound.end() == iter2)
	{
		//LOG :플레이 가능한 사운드객체 없음
		LOG(LOG_LEVEL::LOG,L"플레이 가능한 사운드객체 없음")
		return nullptr;
	}

	return (*iter2);

}

void CSoundMgr::PlayMultipleSound(wstring _key, int _cnt ,float _delay)
{
	auto iter = m_VecSoundplayer.begin();
	while (m_VecSoundplayer.end() != iter)
	{
		if (false == (*iter)->m_isplaying)
			break;
		++iter;
	}

	if (m_VecSoundplayer.end() == iter)
	{
		LOG(LOG_LEVEL::LOG, L"할당 가능한 사운드 플레이어 없음")
		return;
	}

	(*iter)->m_isplaying = true;

	for (int i = 0; i < _cnt; ++i)
	{
		auto psound = GetPlayableSound(_key);
		//로그는 GetPlayableSound에서처리
		if (nullptr == psound)
			return;
		(*iter)->SetSoundEvent(psound, _delay);
	}

}

void CSoundMgr::tick()
{
	for (auto sp : m_VecSoundplayer)
	{
		if (sp->m_isplaying)
			sp->tick();
	}
}

void CSoundMgr::RegisterToBGM(CSound* _pSound)
{
	if (m_pBGM != nullptr)
		m_pBGM->Stop(true);

	m_pBGM = _pSound;
}

void CSoundMgr::CSoundPlayer::tick()
{
	if (m_EventList.empty())
	{
		m_isplaying = false;
		return;
	}

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

void CSoundMgr::CSoundPlayer::SetSoundEvent(CSound* _pSound, float _delay)
{
	FSoundEvent evnt = {};
	evnt.pSound = _pSound;
	evnt.stop = false;
	evnt.AccTime = 0.f;
	evnt.Duration = _delay;
	evnt.played = false;
	m_EventList.push_back(evnt);
}
