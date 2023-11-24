#include "pch.h"
#include "CNoxSpear.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"

CNoxSpear::CNoxSpear()
	:m_Col_On(false)
	, m_Col_Off(false)
{
	m_s1 = L"second";
	m_s2 = L"noxspear";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(250, 700));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(0.f, GetScale().y/-2), 1.f, -1, ORT_LEFT);


	//컬라이더
	m_Collider =
		AddComponent<CCollider>(GetName() + L"Collider");
	m_Collider->SetScale(GetScale());

	m_skilllayer = LAYER::MONSTER_PJB;
	duration = 4.68f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;

}

void CNoxSpear::tick(float _DT)
{
	Super::tick(_DT);

	if (2.88 > m_activedtime)
		return;

	if (false == m_Col_On)
	{
		m_Collider->SetOffsetPos(Vec2(0.f, GetScale().y/-2.f));
		m_Col_On = true;
	}
	if (3.51 > m_activedtime)
		return;

	if (false == m_Col_Off)
	{
		m_Collider->SetOffsetPos(Vec2(0, -2000));
		m_Col_Off = true;
	}

	//if (KEY_TAP(H))
	//{
	//	auto curanim = m_Animator->GetCurAnim();
	//	auto newoffset = curanim->GetOffset() + Vec2(-1, 0);
	//	curanim->Setoffset(newoffset);
	//	wstring log = curanim->GetName() + L":"
	//		+ L"(" + std::to_wstring((int)newoffset.x) + L","
	//		+ std::to_wstring((int)newoffset.y) + L")";

	//	LOG(LOG_LEVEL::LOG, log.c_str());
	//}
	//if (KEY_TAP(K))
	//{
	//	auto curanim = m_Animator->GetCurAnim();
	//	auto newoffset = curanim->GetOffset() + Vec2(1, 0);
	//	curanim->Setoffset(newoffset);
	//	wstring log = curanim->GetName() + L":"
	//		+ L"(" + std::to_wstring((int)newoffset.x) + L","
	//		+ std::to_wstring((int)newoffset.y) + L")";

	//	LOG(LOG_LEVEL::LOG, log.c_str());
	//}
	//if (KEY_TAP(U))
	//{
	//	auto curanim = m_Animator->GetCurAnim();
	//	auto newoffset = curanim->GetOffset() + Vec2(0, -1);
	//	curanim->Setoffset(newoffset);
	//	wstring log = curanim->GetName() + L":"
	//		+ L"(" + std::to_wstring((int)newoffset.x) + L","
	//		+ std::to_wstring((int)newoffset.y) + L")";

	//	LOG(LOG_LEVEL::LOG, log.c_str());
	//}
	//if (KEY_TAP(J))
	//{
	//	auto curanim = m_Animator->GetCurAnim();
	//	auto newoffset = curanim->GetOffset() + Vec2(0, 1);
	//	curanim->Setoffset(newoffset);
	//	wstring log = curanim->GetName() + L":"
	//		+ L"(" + std::to_wstring((int)newoffset.x) + L","
	//		+ std::to_wstring((int)newoffset.y) + L")";

	//	LOG(LOG_LEVEL::LOG, log.c_str());
	//}


}

void CNoxSpear::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	m_Col_On = false;
	m_Col_Off = false;
	m_Collider->SetOffsetPos(Vec2(0, -2000));
	m_Animator->Play(m_s1 + m_s2 + m_s3);
	Super::activate(_beginpos, _ort);
}

void CNoxSpear::begin()
{
	m_Collider->InitColCnt();
}

void CNoxSpear::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	m_collisiontimetoplayer = 0.f;
	if (LAYER::PLAYER == (UINT)_OtherObj->GetLayerIdx())
	{
		CSkillMgr::GetInst()->PlayMultipleEff(L"secondnoxspearhit", 1, 0.f, Vec2(_OtherCol->GetPos().x, _OtherCol->GetPos().y), ORT_LEFT);
		CLevelMgr::GetInst()->GetPlayer()->GetDamaged(0.15f, DEBUFF::DESTUCTION);
	}
}

void CNoxSpear::Overlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
	Super::Overlap(_OwnCol, _OtherObj, _OtherCol);
}

CNoxSpear::CNoxSpear(const CNoxSpear& _Origin)
{
}

CNoxSpear::~CNoxSpear()
{
}
