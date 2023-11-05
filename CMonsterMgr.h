#pragma once

class CMonster;

class CMonsterMgr
{
	SINGLETON(CMonsterMgr);

public:
	unordered_map<wstring, vector<CMonster*>> m_MonsterMap;

	void init();
	void SpwanMonster(wstring _monstername,
		Vec2 _pos);

	CMonster* FindAvailableMonster(
		wstring _monstername);

	vector<CMonster*>& FindMonster(
		wstring _monstername);

	void AddMonster(CMonster* _pMonster);

};