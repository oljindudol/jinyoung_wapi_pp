#pragma once
class CEntity
{

private:
	static UINT_PTR g_NextID;
	const UINT_PTR m_ID;
	wstring			m_strName;
	bool			m_bDead;

public:
	__inline UINT_PTR GetID() { return m_ID; }
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() const { return m_strName; };
	virtual CEntity* Clone() = 0;
	bool IsDead() { return m_bDead; }

	CEntity();
	CEntity(const CEntity& _other);
	//CEntity& operator = (const CEntity& _other);
	virtual ~CEntity();

	friend class CTaskMgr;
	friend class CObj;
};

