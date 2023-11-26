#include "pch.h"
#include "CDialogBox.h"

#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CAmon.h"
#include "CAssetMgr.h"
#include "CMonsterMgr.h"
#include "CTexture.h"
#include "CDialogBtn.h"

CDialogBox::CDialogBox()
	:m_player(nullptr)
	,m_amon(nullptr)
{
	m_s1 = L"검은마법사를 저지하고 메이플 월드를 구원해주게.";

	m_s2 = L"검은마법사를 물리쳤군 보상을 주겠네.";

	
	CTexture* tmpt = CAssetMgr::GetInst()->LoadTexture(L"diboximg", L"texture\\anim\\zero\\dibox.png");
	SetPannelImg(tmpt);
	SetScale(Vec2(tmpt->GetWidth(), tmpt->GetHeight()));
	
	m_uiname = L"dialogbox";
	SetPos(Vec2(500, 300));

	AddChildUI(new CDialogBtn);
}

void CDialogBox::begin()
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

	// 자식 UI 들 Begin 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->begin();
	}

}


void CDialogBox::render(HDC _dc)
{
	if (ENPC_STATE::NONE == m_amon->m_npcstate)
	{
		return;
	}

	Super::render(_dc);

	Vec2 pos = GetFinalPos();

	SetBkMode(_dc, TRANSPARENT);
	SELECT_FONT(_dc, FONT_TYPE::QUEST_DIALOG);
	SetTextColor(_dc, RGB(0, 0, 0));

	wstring tmptex;

	if (ENPC_STATE::HAVE_QUEST == m_amon->m_npcstate ||
		 ENPC_STATE::ON_QUEST == m_amon->m_npcstate)
	{
		tmptex = m_s1;
	}
	else
	{
		tmptex = m_s2;
	}

	TextOut(_dc, (int)pos.x +35, (int)pos.y + 50, tmptex.c_str(), (int)tmptex.length());

	SetTextColor(_dc, RGB(255,255,255));
}


CDialogBox::~CDialogBox()
{
}
