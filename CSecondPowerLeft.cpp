#include "pch.h"
#include "CSecondPowerLeft.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"

CSecondPowerLeft::CSecondPowerLeft()
	:m_used(false)
	,m_dietime(0.f)
{
	m_s1 = L"second";
	m_s2 = L"powerleft";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//���° ��ų����
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(245, 245));

	//�ִϸ��̼�
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"regen",
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT)->SetMag(2.f);


	m_Animator->
		CreateAnimation(m_s1, m_s2, L"use",
			Vec2(0.f, 0.f), 1.f, 0, ORT_LEFT)->SetMag(2.f);

	m_Animator->
		CreateAnimation(m_s1, m_s2, L"die",
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT)->SetMag(2.f);

	//�ö��̴�
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(Vec2(1813.05f, 1813.05f));
	m_Collider->m_vOffsetPos = Vec2(100,-100);

	m_RotatedRad = -0.541052f;
	m_skilllayer = LAYER::MONSTER_POWER;
	duration = 6.8f ;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;
}

void CSecondPowerLeft::tick(float _DT)
{
	Super::tick(_DT);

	//if (KEY_TAP(KEY::J))
	//{
	//	auto panim = m_Animator->FindAnim(m_s1 + m_s2 + m_s3);
	//	panim->SetMag(panim->GetMag() -0.1f);
	//	LOG(LOG_LEVEL::LOG, std::to_wstring(panim->GetMag()).c_str());
	//}
	//if (KEY_TAP(KEY::K))
	//{
	//	auto panim = m_Animator->FindAnim(m_s1 + m_s2 + m_s3);
	//	panim->SetMag(panim->GetMag() + 0.1f);
	//	LOG(LOG_LEVEL::LOG, std::to_wstring(panim->GetMag()).c_str());
	//}


	Super::tick(_DT);

	//�ö��̴� �����
	//m_Collider->m_coltest = true;
	//if (KEY_TAP(KEY::H))
	//{
	//	m_Collider->SetOffsetPos(m_Collider->GetOffsetPos() + Vec2(-100, 0));
	//	LOG(LOG_LEVEL::LOG, (std::to_wstring(m_Collider->GetOffsetPos().x) 
	//		+ L"," +std::to_wstring(m_Collider->GetOffsetPos().y)).c_str());
	//}
	//if (KEY_TAP(KEY::K))
	//{
	//	m_Collider->SetOffsetPos(m_Collider->GetOffsetPos() + Vec2(100, 0));
	//	LOG(LOG_LEVEL::LOG, (std::to_wstring(m_Collider->GetOffsetPos().x)
	//		+ L"," + std::to_wstring(m_Collider->GetOffsetPos().y)).c_str());
	//}

	//if (KEY_TAP(KEY::U))
	//{
	//	m_Collider->SetOffsetPos(m_Collider->GetOffsetPos() + Vec2(0, -100));
	//	LOG(LOG_LEVEL::LOG, (std::to_wstring(m_Collider->GetOffsetPos().x)
	//		+ L"," + std::to_wstring(m_Collider->GetOffsetPos().y)).c_str());
	//}
	//if (KEY_TAP(KEY::J))
	//{
	//	m_Collider->SetOffsetPos(m_Collider->GetOffsetPos() + Vec2(0, 100));
	//	LOG(LOG_LEVEL::LOG, (std::to_wstring(m_Collider->GetOffsetPos().x)
	//		+ L"," + std::to_wstring(m_Collider->GetOffsetPos().y)).c_str());
	//}

	//if (KEY_TAP(KEY::V))
	//{
	//	m_RotatedRad -= 0.0174533f;
	//	LOG(LOG_LEVEL::LOG, std::to_wstring(m_RotatedRad).c_str());
	//}
	//if (KEY_TAP(KEY::B))
	//{
	//	m_RotatedRad += 0.0174533f;
	//	LOG(LOG_LEVEL::LOG, std::to_wstring(m_RotatedRad).c_str());
	//}

	//if (KEY_TAP(KEY::N))
	//{
	//	m_Collider->SetScale(m_Collider->GetScale() / 1.1f);
	//	LOG(LOG_LEVEL::LOG, (std::to_wstring(m_Collider->GetScale().x)
	//		+ L"," + std::to_wstring(m_Collider->GetScale().x)).c_str());
	//}
	//if (KEY_TAP(KEY::M))
	//{
	//	m_Collider->SetScale(m_Collider->GetScale() * 1.1f);
	//	LOG(LOG_LEVEL::LOG, (std::to_wstring(m_Collider->GetScale().x)
	//		+ L"," + std::to_wstring(m_Collider->GetScale().x)).c_str());
	//}

	if (1.08f > m_activedtime)
	{
		return;
	}

	if (false == m_used)
	{
		m_Animator->Play(m_s1 + m_s2 + L"use");
		m_Collider->m_vOffsetPos = Vec2(100, -100);
		m_used = true;
	}

	if (1.08f <= m_activedtime && (duration - 0.9f) > m_activedtime)
	{
		return;
	}

	if (0.f == m_dietime)
	{
		m_Animator->Play(m_s1 + m_s2 + L"die");
		m_Collider->m_vOffsetPos = Vec2(100, -5000);
		m_dietime = m_activedtime;
	}

	if (m_dietime + 0.99f > m_activedtime)
	{
		return;
	}
	if (m_dietime + 0.99f <= m_activedtime)
	{
		Destroy();
	}
}

void CSecondPowerLeft::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	m_Collider->m_vOffsetPos = Vec2(100, -5000);
	m_used = false;
	m_dietime = 0.f;
	m_Animator->Play(m_s1 + m_s2 + L"regen");
	Super::activate(_beginpos, _ort);
}

void CSecondPowerLeft::begin()
{
	m_Collider->InitColCnt();
}

void CSecondPowerLeft::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	m_collisiontimetoplayer = 0.f;
	if (LAYER::PLAYER == (UINT)_OtherObj->GetLayerIdx())
	{
		CSkillMgr::GetInst()->PlayMultipleEff(L"secondeyeofruinhit", 1, 0.f, Vec2(_OtherCol->GetPos().x, _OtherCol->GetPos().y), ORT_LEFT);
		CLevelMgr::GetInst()->GetPlayer()->GetDamaged(0.15f, DEBUFF::DESTUCTION);
	}

}

void CSecondPowerLeft::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);
	if (_OtherObj->GetLayerIdx() == (UINT)LAYER::PLAYER)
		if (.5f < m_collisiontimetoplayer)
		{
			BeginOverlap(_OwnCol, _OtherObj, _OtherCol);
		}
}

CSecondPowerLeft::CSecondPowerLeft(const CSecondPowerLeft& _Origin)
{
}

CSecondPowerLeft::~CSecondPowerLeft()
{
}
