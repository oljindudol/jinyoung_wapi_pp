#include "pch.h"
#include "CAchievement.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAssetMgr.h"

CAchievement::CAchievement()
	:m_pAnim(nullptr)
{
	m_s1 = L"fifth";
	m_s2 = L"achievement";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(245, 245));

	//애니메이션
	m_Animator =
		AddComponent<CAnimator>(GetName() + L"Animator");

	m_pAnim = m_Animator->
		CreateAnimation(m_s1, m_s2, m_s3,
			Vec2(0.f, 0.f), 1.f, -1, ORT_LEFT);

	m_Animator->Play(m_s1 + m_s2 + m_s3);


	m_skilllayer = LAYER::SUPER_UI;
	duration = 3.53f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;

	m_text = L"메이플 월드의 구원자";
}

void CAchievement::tick(float _DT)
{
	Super::tick(_DT);
	SetPos(CCamera::GetInst()->GetLookAt() );

	if (m_activedtime > duration - 0.8f)
	{
		int tmp = (int)(((duration - m_activedtime) / 0.8f) * 255);
		if (0 > tmp) tmp = 0;

		m_pAnim->SetAlpha(tmp);
	}
	
}

void CAchievement::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);

}

void CAchievement::begin()
{
	CAssetMgr::GetInst()->LoadSound(L"업적", L"sound\\AchievmentComplete.wav")->Play();
	m_pAnim->SetAlpha(255);
}

void CAchievement::render(HDC _dc)
{
	Super::render(_dc);

	SetBkMode(_dc, TRANSPARENT);
	SELECT_FONT(_dc, FONT_TYPE::ACHIVEMENT);
	SetTextColor(_dc, RGB(218, 255, 141));
	Vec2 pos = CCamera::GetInst()->GetLookAt();

	TextOut(_dc, 600, 455, m_text.c_str(), (int)m_text.length());

	SetTextColor(_dc, RGB(0, 0, 0));

}

CAchievement::CAchievement(const CAchievement& _Origin)
{
}

CAchievement::~CAchievement()
{
}
