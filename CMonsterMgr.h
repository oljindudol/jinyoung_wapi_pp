#pragma once

class CMonster;

class CMonsterMgr
{
	SINGLETON(CMonsterMgr);

public:
	unordered_map<wstring, vector<CMonster*>> m_MonsterMap;

	void init();

	CMonster* FindAvailableMonster(
		wstring _monstername);

	vector<CMonster*>* FindMonster(
		wstring _monstername);

	void AddMonster(CMonster* _pMonster);

	void DeActivateAllMonsters();

	void DeActivateMonster(CMonster* _pMonster);

	void SpwanMonster(wstring _monstername,
		Vec2 _pos);

};