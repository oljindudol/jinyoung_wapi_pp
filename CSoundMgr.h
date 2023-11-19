#pragma once
class CSound;


struct FSoundEvent
{
	bool stop;
	CSound* pSound;
	bool		played;
	float		AccTime;
	float		Duration;
};

class CSoundMgr
{
	SINGLETON(CSoundMgr);
private:
	LPDIRECTSOUND8	m_pSound;	// 사운드 관련 매니저 객체, 사운드 카드 컨트롤
	CSound* m_pBGM;		// 사운드 중에서 BGM Sound 를 가리키는 포인터

	//사운드풀 관련
public:
	void LoadMultipleSound(wstring _key,wstring _relpath,int _cnt);
private:
	unordered_map<wstring ,vector<CSound*>> m_SoundMap;
	CSound* GetPlayableSound(wstring _key);

	//사운드 플레이어 관련
	class CSoundPlayer
	{
	private:
		list<FSoundEvent> m_EventList;
		bool m_isplaying;
		void tick();
		void SetSoundEvent(CSound* _pSound, float _delay);

		CSoundPlayer() :m_isplaying(false) {}
		friend class CSoundMgr;
	};

	vector<CSoundPlayer*> m_VecSoundplayer;



public:
	int init();
	void tick();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
	//사운드플레이어에 사운드 이벤트를 등록하는 함수
	void PlayMultipleSound(wstring _key, int _cnt, float _delay);

};

