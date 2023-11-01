#include "pch.h"
#include "CSkill.h"
#include "components.h"

void CSkill::begin()
{

}

void CSkill::render(HDC _dc)
{
}

void CSkill::tick(float _DT)
{
}

void CSkill::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}

void CSkill::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	// activatedtime 초기화
	m_activedtime = 0.f;
	
	

	// ort 설정
	ort = _ort;

	// 애니메이션 play
	m_Animator->Play(m_skillname);

	//레벨 참여 비긴으로해도되나 ? 태스크한테 넘겨야하나?
	begin();
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
{
}

CSkill::CSkill(const CSkill& _Origin)
	: m_skillname(L"")
	, m_Collider(nullptr)
	, m_Animator(_Origin.m_Animator)
	, duration(_Origin.duration)
	, m_activedtime(0)
	, cooltime(_Origin.cooltime)
	, m_leftcool(0)
	, m_debuff(DEBUFF::NONE)
{
}

CSkill::~CSkill()
{
}
