#pragma once

#include <unordered_map>
#include "CSkill.h"
using namespace std;

class CSkillMgr
{
	SINGLETON(CSkillMgr);

public:
	void init();
	void ActivateSkill(
		wstring _aname1,
		wstring _aname2,
		wstring _aname3,
		Vec2 _pos,
		ORIENTATION _ort);

	CSkill* FindSkill(
		wstring _aname1,
		wstring _aname2,
		wstring _aname3);

	float GetCoolTime(
		wstring _aname1,
		wstring _aname2,
		wstring _aname3);
		
private: 
	unordered_map<wstring, CSkill*> m_skillmap;
	void CreateSkill(
		  Vec2 _colbox
		, wstring _aname1
		, wstring _aname2
		, wstring _aname3
		, Vec2 _animOffset = Vec2()
		, float _animPlaymul = 1.f
		, int _roop =0
		, ORIENTATION _ort = ORT_LEFT
		, float _duration = 0.f
		, float _cooltime = 0.f
		, float _att = 0.f
		, DEBUFF _debuff = DEBUFF::NONE
		//Vec2 _colOffset = Vec2()
		//Vec2 _posOffset = Vec2()
	);
};

