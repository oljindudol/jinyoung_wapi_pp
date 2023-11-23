#include "pch.h"
#include "CSkill.h"
#include "components.h"
#include "CTaskMgr.h"



void CSkill::tick(float _DT)
{
	Super::tick(_DT);


	m_activedtime += _DT;

	if (duration < m_activedtime)
	{
		Destroy();
		//CTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::DELETE_OBJECT, (UINT_PTR)this });
	}


}

void CSkill::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CSkill::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);

}

void CSkill::activate(Vec2 _beginpos, ORIENTATION _ort)
{

	// activatedtime �ʱ�ȭ
	m_activedtime = 0.f;
	
	m_leftcool = cooltime;

	//��ų ��ġ����
	SetPos(_beginpos);

	// �¿� ����
	ort = _ort;

	m_OnActivate = true;

	SetLive();
	
	// ����������
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)m_skilllayer, (UINT_PTR)this });

	// �ִϸ��̼� play
	m_Animator->Play(m_Animator->GetCurAnimName());

}

void CSkill::begin()
{
}



CSkill::CSkill()
	: m_s1(L"")
	, m_s2(L"")
	, m_s3(L"")
	, m_skillname(L"")
	, m_skillnum(0)
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
	: m_s1(L"")
	, m_s2(L"")
	, m_s3(L"")
	, m_skillname(L"")
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
