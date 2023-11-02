#include "pch.h"
#include "CSkill.h"
#include "components.h"
#include "CTaskMgr.h"



void CSkill::tick(float _DT)
{
	Super::tick(_DT);
}

void CSkill::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CSkill::activate(Vec2 _beginpos, ORIENTATION _ort)
{

	// activatedtime 초기화
	m_activedtime = 0.f;
	
	//스킬 위치설정
	SetPos(_beginpos);

	// 좌우 설정
	ort = _ort;

	m_OnActivate = true;

	// 레벨에참여
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)m_skilllayer, (UINT_PTR)this });

	// 애니메이션 play
	m_Animator->Play(m_skillname);

}




CSkill::CSkill()
	: m_skillname(L"")
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, duration(0)
	, m_activedtime(0)
	, cooltime(0)
	, m_leftcool(0)
	, m_debuff(DEBUFF::NONE)
	, m_att(0)
	, m_OnActivate(false)
	, m_skilllayer(LAYER::DEFAULT)
{
}

CSkill::CSkill(const CSkill& _Origin)
	: m_skillname(L"")
	, m_Collider(nullptr)
	, m_Animator(nullptr)
	, duration(0)
	, m_activedtime(0)
	, cooltime(0)
	, m_leftcool(0)
	, m_debuff(DEBUFF::NONE)
	, m_att(0)
	, m_OnActivate(false)
	, m_skilllayer(LAYER::DEFAULT)
{
}

CSkill::~CSkill()
{
}
