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
	LPDIRECTSOUND8	m_pSound;	// ���� ���� �Ŵ��� ��ü, ���� ī�� ��Ʈ��
	CSound* m_pBGM;		// ���� �߿��� BGM Sound �� ����Ű�� ������

	//����Ǯ ����
public:
	void LoadMultipleSound(wstring _key,wstring _relpath,int _cnt);
private:
	unordered_map<wstring ,vector<CSound*>> m_SoundMap;
	CSound* GetPlayableSound(wstring _key);

	//���� �÷��̾� ����
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
	//�����÷��̾ ���� �̺�Ʈ�� ����ϴ� �Լ�
	void PlayMultipleSound(wstring _key, int _cnt, float _delay);

};

