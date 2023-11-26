#include "pch.h"
#include "CDialogBtn.h"

#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CAmon.h"
#include "CAssetMgr.h"
#include "CMonsterMgr.h"
#include "CTexture.h"
#include "CUIMgr.h"
#include "CSkillMgr.h"

CDialogBtn::CDialogBtn()
	: m_player(nullptr)
	, m_amon(nullptr)
{
	auto ticon = CAssetMgr::GetInst()->LoadTexture(L"dialogbtnicon", L"texture\\anim\\zero\\UtilDlgEx.BtOK.normal.0.png");

	SetScale(Vec2(ticon->GetWidth(), ticon->GetHeight()));

	SetPos(Vec2(473, 180));
	SetNormalImg(ticon);
	SetPressedImg(ticon);
	SetHoverImg(ticon);
}



void CDialogBtn::begin()
{
	m_player = CLevelMgr::GetInst()->GetPlayer();
	auto tmpmon = CMonsterMgr::GetInst()->FindMonster(L"zeroamon");
	CAmon* tmpamon = nullptr;

	if (nullptr != tmpmon)
		tmpamon = dynamic_cast<CAmon*>((*tmpmon)[0]);

	if (nullptr != tmpamon)
	{
		m_amon = tmpamon;
	}
	int a = 0;
}

void CDialogBtn::LBtnClicked(Vec2 _vMousePos)
{

	CUIMgr::GetInst()->SetUIOnOffResponsible(L"dialogbox");

	if (ENPC_STATE::HAVE_QUEST == m_amon->m_npcstate ||
		ENPC_STATE::ON_QUEST == m_amon->m_npcstate
		)
	{
		m_amon->m_npcstate = ENPC_STATE::ON_QUEST;
		m_amon->m_pAnimator2->Play(m_amon->m_s1 + m_amon->m_s2 + L"ongoing");
	}

	if (ENPC_STATE::COMPLETE_QUEST == m_amon->m_npcstate)
	{
		CSkillMgr::GetInst()->ActivateSkill(L"zerolevelupuse", m_player->GetPos() + Vec2(0, -200), ORT_LEFT);
		CAssetMgr::GetInst()->LoadSound(L"·¾¾÷", L"sound\\LevelUp.wav")->Play();
		++m_player->level;

		m_amon->m_npcstate = ENPC_STATE::NONE;
		m_amon->m_pAnimator2->Play(m_amon->m_s1 + m_amon->m_s2 + L"none");
	}

}

CDialogBtn::~CDialogBtn()
{
}
