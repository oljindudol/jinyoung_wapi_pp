#pragma once


class CSkill;

class CSkillMgr
{
	SINGLETON(CSkillMgr);

public:
	void init();
	void ActivateSkill(wstring _skillname,
		Vec2 _pos,
		ORIENTATION _ort);

	vector<CSkill*>* FindSkill(
		wstring _skillname);

	float GetCoolTime(
		wstring _skillname);

	CSkill* FindAvailableSkill(
		wstring _skillname);

	//bool IsActive(
	//	wstring _aname1,
	//	wstring _aname2,
	//	wstring _aname3);

	unordered_map<wstring, vector<CSkill*>> m_skillmap;
		
private: 
	void AddSkill(CSkill* _pSkill);

	//void CreateSkill(
	//	  Vec2 _colbox
	//	, wstring _aname1
	//	, wstring _aname2
	//	, wstring _aname3
	//	, Vec2 _animOffset = Vec2()
	//	, float _animPlaymul = 1.f
	//	, int _roop =0
	//	, ORIENTATION _ort = ORT_LEFT
	//	, float _duration = 0.f
	//	, float _cooltime = 0.f
	//	, float _att = 0.f
	//	, DEBUFF _debuff = DEBUFF::NONE
	//);

};

