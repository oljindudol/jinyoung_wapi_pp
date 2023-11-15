#pragma once
class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
private:
	// 최상위 부모 UI 중에서 포커싱 되어있는 UI
	CUI* m_FocuedUI;	

public:
	void tick();
private:
	CUI* GetPriorityCheck(CUI* _ParentUI);

public:
	// 최상위 UI만 모아둔것
	unordered_map<wstring, vector<CUI*>> m_UIMap;
	void init();
	void SetUIVisible(wstring _uiname);
	void DestroyUI(wstring _uiname);

private:
	CUI* FindAvailableUI(wstring _uiname);

	vector<CUI*>* FindUI(wstring _uiname);

	void AddUI(CUI* _pui);

public:
	void SetUIInvisible(CUI* _pui);
	void SetInvisibleAllUI();

	int FindNextUINumber(wstring _uiname);



};

