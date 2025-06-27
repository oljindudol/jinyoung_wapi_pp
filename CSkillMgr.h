#pragma once
class CSkill;

struct FEffectEvent
{
	CSkill* pSkill;
	Vec2		vPos;
	bool		activated;
	ORIENTATION ort;
	float		AccTime;
	float		Duration;
};


#include <mutex>
class CSkillMgr
{
	SINGLETON(CSkillMgr);

private:
	mutex m_SMmutex;
	unordered_map<wstring, vector<CSkill*>> m_skillmap;

public:
	void init();
	CSkill* ActivateSkill(wstring _skillname,
		Vec2 _pos,
		ORIENTATION _ort = ORT_LEFT);

private:
	void LoadSkills();
	void MUL_LoadSkill();
	void MUL_LoadSkills();
	template<typename T>
	void CreateAndAddMultipleSkills(int count)
	{
		std::vector<CSkill*> skills;
		skills.reserve(count);  // 메모리 파편화 줄이기

		for (int i = 0; i < count; ++i)
			skills.push_back(new T);

		{
			std::lock_guard<std::mutex> lock(m_SMmutex);
			for (auto skill : skills)
				AddSkill(skill);  // 기존 AddSkill 그대로 사용
		}
	}

	template<typename T>
	void CreateAndAddMultipleSkillEff(
		int count,
		const std::wstring& s1,
		const std::wstring& s2,
		const std::wstring& s3,
		float duration,
		const Vec2& offset = Vec2(0.f, 0.f),
		int roop = -1,
		ERenderType renderType = ERenderType::OnPlayer)
	{
		std::vector<CSkill*> skills;
		skills.reserve(count);

		for (int i = 0; i < count; ++i)
		{
			CSkill* skill = new T;
			skill->m_s1 = s1;
			skill->m_s2 = s2;
			skill->m_s3 = s3;

			skill->m_skillname = s1 + s2 + s3;
			skill->m_skillnum = FindNextSkillNumber(skill->m_skillname);
			skill->SetName(skill->m_skillname + L"_" + std::to_wstring(skill->m_skillnum));

			skill->m_skilllayer = LAYER::PLAYER_SKILL;
			skill->duration = duration;

			skill->m_Animator = skill->AddComponent<CAnimator>(skill->GetName() + L"Animator");
			skill->m_Animator->SetRenderType(renderType);
			skill->m_Animator->CreateAnimation(s1, s2, s3, offset, 1.f, roop, ORT_LEFT);
			skill->m_Animator->Play(s1 + s2 + s3);

			skills.push_back(skill);
		}

		{
			std::lock_guard<std::mutex> lock(m_SMmutex);
			for (auto skill : skills)
			{
				vector<CSkill*>* pSkills = FindSkill(skill->m_skillname);
				if (!pSkills)
				{
					m_skillmap[skill->m_skillname] = { skill };
				}
				else
				{
					pSkills->push_back(skill);
				}
			}
		}
	}

	CSkill* FindAvailableSkill(
		wstring _skillname);

	vector<CSkill*>* FindSkill(
		wstring _skillname);

	void AddSkill(CSkill* _pSkill);
public:
	void AddSkillEff(CSkill* _pSkill
		, wstring _s1, wstring _s2, wstring _s3
		, float _duration, Vec2 _offset = Vec2(), int _roop = -1, ERenderType _RenderType = ERenderType::OnDefault);

public:
	void DeActivateAllSkills();
	void DeActivateSkill(CSkill* _skill);
	int FindNextSkillNumber(wstring _skillname);
	void PrintDamageVioletSkin(Vec2 _pos, int _num);
	void PrintDamageRedSkin(Vec2 _pos, long long _num, int _th);
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
		void SetEffEvent(CSkill* _pSkillEff, float _delay, Vec2 _pos, ORIENTATION _ort);

		CEffPlayer() :m_isplaying(false) {}
		friend class CSkillMgr;
	};

	vector<CEffPlayer*> m_VecEffPlayer;

public:
	//이펙트플레이어에 이펙트 이벤트를 등록하는 함수
	void PlayMultipleEff(wstring _key, int _cnt, float _delay, Vec2 _pos, ORIENTATION _ort);

	//이펙트플레이어에 이펙트 이벤트를 등록하는 함수
	void ActivateSkillWithDelay(wstring _key, float _delay, vector<Vec2> _pos, ORIENTATION _ort);

	friend class QuickSlotUI;
};

