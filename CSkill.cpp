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
	// activatedtime �ʱ�ȭ
	m_activedtime = 0.f;
	
	

	// ort ����
	ort = _ort;

	// �ִϸ��̼� play
	m_Animator->Play(m_skillname);

	//���� ���� ��������ص��ǳ� ? �½�ũ���� �Ѱܾ��ϳ�?
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
