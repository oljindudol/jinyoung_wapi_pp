#pragma once


class CSkill;

class CSkillMgr
{
	SINGLETON(CSkillMgr);

private:
	unordered_map<wstring, vector<CSkill*>> m_skillmap;


public:
	void init();
	void ActivateSkill(wstring _skillname,
		Vec2 _pos,
		ORIENTATION _ort);

private:
	CSkill* FindAvailableSkill(
		wstring _skillname);

	vector<CSkill*>* FindSkill(
		wstring _skillname);

	void AddSkill(CSkill* _pSkill);

public:
	void DeActivateAllSkills();
	void DeActivateSkill(CSkill* _skill);
	int FindNextSkillNumber(wstring _skillname);
	void PrintDamageVioletSkin(Vec2 _pos, int _num);
	void PrintDamageRedSkin(Vec2 _pos, long long _num , int _th);

public:
	float GetSkillDuration(wstring _skillname);
	float GetCoolTime(wstring _skillname);

private: 


};

