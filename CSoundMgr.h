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
	list<FSoundEvent> m_EventList;

public:
	int init();
	void tick();
	LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
	void RegisterToBGM(CSound* _pSound);
	void SetShortSound(wstring _strsound, float _time);
	void SetLongSound(wstring _strsound, float _time);


};

