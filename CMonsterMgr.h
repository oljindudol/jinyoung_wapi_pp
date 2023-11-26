#pragma once

class CMonster;

class CMonsterMgr
{
	SINGLETON(CMonsterMgr);

private:
	unordered_map<wstring, vector<CMonster*>> m_MonsterMap;


public:
	void init();
	void SpwanMonster(wstring _monstername,
		Vec2 _pos);
	void SpwanRuleMonster(wstring _monstername);

private:
	CMonster* FindAvailableMonster(
		wstring _monstername);

	vector<CMonster*>* FindMonster(
		wstring _monstername);

	void AddMonster(CMonster* _pMonster);

public:
	void DeActivateMonster(CMonster* _pMonster);
	void DeActivateAllMonsters();

	int FindNextMonsterNumber(wstring _monstername);

	void ChangeAllMonsterForcedIdle();
	void ChangeAllMonsterIdle();

public:
	void tick();

	friend class CLevelMgr;
	friend class CMonster;
	friend class CNormalMonDebug;
	friend class CDialogBox;
	friend class CDialogBtn;

};