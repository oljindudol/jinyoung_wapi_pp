#pragma once
class CUI;

class CUIMgr
{
	SINGLETON(CUIMgr);
private:
	// �ֻ��� �θ� UI �߿��� ��Ŀ�� �Ǿ��ִ� UI
	CUI* m_FocuedUI;	

public:
	void tick();
private:
	CUI* GetPriorityCheck(CUI* _ParentUI);

public:
	// �ֻ��� UI�� ��Ƶа�
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

