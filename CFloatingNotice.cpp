#include "pch.h"
#include "CFloatingNotice.h"

#include "CAssetMgr.h"
#include "CTexture.h"
//#include "CLevelMgr.h"
#include "CMonster.h"
#include "CEngine.h"

CFloatingNotice::CFloatingNotice()
	:lefttex(nullptr)
	, midtex(nullptr)
	, righttex(nullptr)
	, m_tmp_duration(0.f)
	, m_tmp_msg(L"")
	, m_acctime(0.f)
	, c_midwidth(8.f)
	, m_tmp_midcnt(0)
{
	m_uiname = L"FloatingNoticeUI";

	CAssetMgr* asmgr = CAssetMgr::GetInst();

	lefttex = asmgr->LoadTexture(L"floatingnoticeleft", L"texture\\floatingnotice\\left.png");
	midtex = asmgr->LoadTexture(L"floatingnoticemid", L"texture\\floatingnotice\\mid.png");
	righttex = asmgr->LoadTexture(L"floatingnoticeright", L"texture\\floatingnotice\\right.png");

	m_leftscale = Vec2(lefttex->GetWidth(), lefttex->GetHeight());

}

void CFloatingNotice::tick(float _DT)
{
	m_acctime += _DT;
	if(m_tmp_duration< m_acctime)
	{
		Destroy();
	}
}

void CFloatingNotice::render(HDC _dc)
{
	Vec2 vRenderPos = GetPos();

	//left
	SettexturetoDc(_dc, lefttex, vRenderPos);

	//mid
	for (int i = 0; i < m_tmp_midcnt; ++i)
	{
		SettexturetoDc(_dc, midtex
			, vRenderPos 
			+ Vec2(m_leftscale.x,0.f)
			+ Vec2(c_midwidth * i, 0.f)
		);
	}

	//right
	SettexturetoDc(_dc, righttex, vRenderPos +Vec2(m_leftscale.x+ c_midwidth* m_tmp_midcnt,0.f) );


	SetBkMode(_dc, TRANSPARENT);
	SELECT_FONT(_dc, FONT_TYPE::LEVEL_ALERT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, (int)(vRenderPos.x + m_leftscale.x), (int)(vRenderPos.y + 50.f), m_tmp_msg.c_str(), (int)m_tmp_msg.length());
}



void CFloatingNotice::FloatNotice(wstring _str, float _duration)
{
	m_tmp_duration = _duration;
	m_tmp_msg = _str;
	m_tmp_midcnt = 0;
	m_acctime = 0.f;

	int space_dot_cnt = 0;

	for (const auto& c : m_tmp_msg)
	{
		if (L' ' == c || L'.' == c)
		{
			++space_dot_cnt;
		}
	}


	m_tmp_midcnt = (int)_str.size() * 2 - (int)((float)space_dot_cnt * 1.333333f);


	SetPos(
		(Vec2(CEngine::GetInst()->GetResolution()) / 2.f)
		- Vec2(m_leftscale.x, m_leftscale.y / 2.f)
		- Vec2(c_midwidth * m_tmp_midcnt/2 , 0.f)
	);
	
	Super::SetUIVisible();
}

void CFloatingNotice::begin()
{
}

CFloatingNotice::~CFloatingNotice()
{
}
