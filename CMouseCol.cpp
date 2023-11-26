#include "pch.h"
#include "CMouseCol.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

CMouseCol::CMouseCol()
{
	m_s1 = L"common";
	m_s2 = L"mouse";
	m_s3 = L"collider";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(0, 0));


	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());
	//m_Collider->m_vOffsetPos = (GetScale() / 2);

	m_skilllayer = LAYER::MOUSE_COL;
	duration = 0.3f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;

}

void CMouseCol::begin()
{
	m_Collider->InitColCnt();
}

CMouseCol::CMouseCol(const CMouseCol& _Origin)
{
}


CMouseCol::~CMouseCol()
{
}
