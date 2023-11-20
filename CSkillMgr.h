#pragma once
class CSkill;

struct FEffectEvent
{
	CSkill*		pSkill;
	Vec2		vPos;
	bool		activated;
	ORIENTATION ort;
	float		AccTime;
	float		Duration;
};



class CSkillMgr
{
	SINGLETON(CSkillMgr);

private:
	unordered_map<wstring, vector<CSkill*>> m_skillmap;


public:
	void init();
	CSkill* ActivateSkill(wstring _skillname,
		Vec2 _pos,
		ORIENTATION _ort);

private:
	CSkill* FindAvailableSkill(
		wstring _skillname);

	vector<CSkill*>* FindSkill(
		wstring _skillname);

	void AddSkill(CSkill* _pSkill);
public:
	void AddSkillEff(CSkill* _pSkill
		, wstring _s1, wstring _s2, wstring _s3
		, float _duration , Vec2 _offset = Vec2() ,int _roop=-1);

public:
	void DeActivateAllSkills();
	void DeActivateSkill(CSkill* _skill);
	int FindNextSkillNumber(wstring _skillname);
	void PrintDamageVioletSkin(Vec2 _pos, int _num);
	void PrintDamageRedSkin(Vec2 _pos, long long _num , int _th);
	void tick();

public:
	float GetSkillDuration(wstring _skillname);
	bool IsCoolTime(wstring _skillname);

	

private: 

	//이펙트 플레이어 관련
	class CEffPlayer
	{
	private:
		list<FEffectEvent> m_EventList;
		bool m_isplaying;
		void tick();
		void SetEffEvent(CSkill* _pSkillEff, float _delay,Vec2 _pos ,ORIENTATION _ort);

		CEffPlayer() :m_isplaying(false) {}
		friend class CSkillMgr;
	};

	vector<CEffPlayer*> m_VecEffPlayer;

public:
	//사운드플레이어에 사운드 이벤트를 등록하는 함수
	void PlayMultipleEff(wstring _key, int _cnt, float _delay ,Vec2 _pos ,ORIENTATION _ort);

	friend class QuickSlotUI;
};

