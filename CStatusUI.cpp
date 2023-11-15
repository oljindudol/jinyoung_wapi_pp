#include "pch.h"
#include "CStatusUI.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"

CStatusUI::CStatusUI()
	:RenderDc(nullptr)
	, m_hpbuffer(0.f)
	, m_mpbuffer(0.f)
	,m_acctime(0.f)
	,slash(L"/")
	,charname(L"듀블")
	,nametex(nullptr)
{
	m_uiname = L"StatusUI";
	SetScale(Vec2(204.f, 70.f));
	SetPos(Vec2(600.f, 690.f));

	CAssetMgr* asmgr = CAssetMgr::GetInst();

	backtex = asmgr->LoadTexture(L"StatusUIBack", L"texture\\status\\mainBar.status.backgrnd.png");
	hptex = asmgr->LoadTexture(L"StatusUIHp", L"texture\\status\\mainBar.status.gauge.hp.layer.0.png");
	mptex = asmgr->LoadTexture(L"StatusUIMp", L"texture\\status\\mainBar.status.gauge.mp.layer.0.png");
	covertex = asmgr->LoadTexture(L"StatusUICover", L"texture\\status\\status.layer.cover.png");
	lvtex= asmgr->LoadTexture(L"StatusUILv", L"texture\\status\\layer.Lv.png");

	exptex = asmgr->LoadTexture(L"StatusUIExp", L"texture\\status\\1366.layer.back.png");
	expcovertex = asmgr->LoadTexture(L"StatusUIExpCover", L"texture\\status\\1366.layer.cover.png");

	for (int i = 0; i < 10; i++)
	{
		vecgaugetex.push_back(
			asmgr->LoadTexture(L"StatusUINum"+ std::to_wstring(i), L"texture\\status\\gauge.number.frames\\" + std::to_wstring(i) + L".png"  )
		);

		veclvtex.push_back(
			asmgr->LoadTexture(L"StatusUILv" + std::to_wstring(i), L"texture\\status\\lvNumber.frames\\" + std::to_wstring(i) + L".png")
		);
	}

	CPlayer* cPlayer = CLevelMgr::GetInst()->GetPlayer();
}

CStatusUI::~CStatusUI()
{

}






void CStatusUI::tick(float _DT)
{
	m_acctime += _DT;

	CPlayer* cPlayer = CLevelMgr::GetInst()->GetPlayer();

	m_hpbuffer = m_hpbuffer + ((float)cPlayer->hp - m_hpbuffer) * _DT* 5.f;
	m_mpbuffer = m_mpbuffer + ((float)cPlayer->mp - m_mpbuffer) * _DT * 5.f;

	Super::tick(_DT);
}

void CStatusUI::render(HDC _dc)
{

	CPlayer* cPlayer =CLevelMgr::GetInst()->GetPlayer();

	Vec2 vRenderPos = GetPos();
	Vec2 vScale = GetScale();

	//BLENDFUNCTION blend = {};
	//blend.BlendOp = AC_SRC_OVER;
	//blend.BlendFlags = 0; // 0이여야합니다

	//blend.SourceConstantAlpha = 255; // 0 ~ 255
	//blend.AlphaFormat = AC_SRC_ALPHA; // 고정


	//스테이터스 배경
	SettexturetoDc(_dc, backtex, (vRenderPos + Vec2(3.f, 23.f )));
	
	//체력비율(빨간색바)
	SettexturetoDcPartiallyRight(_dc, hptex, (vRenderPos + Vec2(24.f, 28.f)), ((float)m_hpbuffer / (float)cPlayer->maxhp));


	//마력비율(파란색바)
	SettexturetoDcPartiallyRight(_dc, mptex, (vRenderPos + Vec2(24.f, 44.f)), ((float)m_mpbuffer / (float)cPlayer->maxmp));

	//스테이터스 커버
	SettexturetoDc(_dc, covertex, (vRenderPos));

	//레벨 표시
	SettexturetoDc(_dc, lvtex, (vRenderPos + Vec2(25.f, 9.f)));
	SetLettertoDc(_dc, 290, veclvtex, (vRenderPos + Vec2(42.f, 9.f)));


	int xoffset = 0;
	if (0 != vecgaugetex.size())
	{
		xoffset = vecgaugetex[0]->GetWidth();
	}

	int lakeofhpdigit = 5 - (int)std::to_wstring(cPlayer->hp).size();
	int lakeofmpdigit = 5 - (int)std::to_wstring(cPlayer->mp).size();

	//체력 
	SetLettertoDc(_dc, cPlayer->hp , vecgaugetex, (vRenderPos + Vec2(65.f+ xoffset* lakeofhpdigit, 30.f)));

	SetBkMode(_dc, TRANSPARENT);
	SELECT_FONT(_dc, FONT_TYPE::STATUS_BAR_POINT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, (int)(vRenderPos.x + 104.f), (int)(vRenderPos.y+29.f), slash.c_str(), (int)slash.length());

	SetLettertoDc(_dc, cPlayer->maxhp, vecgaugetex, (vRenderPos + Vec2(110.f, 30.f)));


	//MP
	SetLettertoDc(_dc, cPlayer->mp, vecgaugetex, (vRenderPos + Vec2(65.f + xoffset* lakeofmpdigit, 46.f)));
	TextOut(_dc, (int)(vRenderPos.x + 104.f), (int)(vRenderPos.y + 45.f), slash.c_str(), (int)slash.length());
	SetLettertoDc(_dc, cPlayer->maxmp, vecgaugetex, (vRenderPos + Vec2(110.f , 46.f)));



	//캐릭터이름
	SELECT_FONT2(_dc, FONT_TYPE::STATUS_BAR_NAME);
	TextOut(_dc, (int)(vRenderPos.x + 98.f), (int)(vRenderPos.y + 8.f), charname.c_str(), (int)charname.length());


	SettexturetoDc(_dc, exptex, (Vec2(0.f, 758.f)));
	SettexturetoDc(_dc, expcovertex, (Vec2(142.f, 759.f)));


	Super::render(_dc);

}
