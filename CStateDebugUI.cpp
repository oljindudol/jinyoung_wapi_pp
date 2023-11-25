#include "pch.h"
#include "CStateDebugUI.h"
#include "CLevelMgr.h"
#include "CBlackMage2.h"
#include "CState.h"
#include "CAssetMgr.h"
#include "CEngine.h"


CStateDebugUI::CStateDebugUI()
	:m_UItex(nullptr)
{
	m_uiname = L"statedebugui";
	SetScale(Vec2(165, 170));
	SetPos(Vec2(250.f, 2.f));

	m_UItex = CAssetMgr::GetInst()->LoadTexture(L"statedebuguitex", L"texture\\statedebugbg.png");
}

void CStateDebugUI::tick(float _DT)
{

}

void CStateDebugUI::render(HDC _dc)
{
	if (!DEBUG_RENDER)
		return;

	Vec2 debug_renpos = m_bm2->GetRenderPos() - m_bm2->GetScale() / 2 - Vec2(165, 0);

	SELECT_BRUSH(_dc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	SELECT_PEN(_dc, WT_PEN);


	SettexturetoDc(_dc, m_UItex, debug_renpos);

	SetBkMode(_dc, TRANSPARENT);

	SetBkColor(_dc, RGB(255, 255, 255));

	auto curstate = m_bm2->m_AI->GetCurState();
	auto curacctime = curstate->GetAcctime();
	auto curdur = curstate->GetDuration();

	int yoffset = 0;
	int yoffsetsize = 18;

	SELECT_FONT2(_dc, FONT_TYPE::STATUS_DEBUG);

	wstring staname = curstate->GetName();

	//현재상태
	if (L"대기상태" == staname)
	{
		SetBkColor(_dc, RGB(255, 255, 255));
		SetTextColor(_dc, RGB(0, 0, 255));

		if (true == m_bm2->m_AI->GetForcedIdle())
		{
			staname = L"강제대기";
		}
	}
	else
	{
		SetBkColor(_dc, RGB(255, 255, 0));
		SetTextColor(_dc, RGB(255, 0, 0));
	}

	wstring curstate_line = L"현재상태:" + staname;
	TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, curstate_line.c_str(), (int)curstate_line.length());
	++yoffset;


	wstring percwstr = std::to_wstring((curacctime / curdur) * 100.f);
	wstring curtimestr = std::to_wstring(curacctime);
	wstring curdurstr = std::to_wstring(curdur);


	SetBkColor(_dc, RGB(255, 255, 255));
	//if (curacctime > curdur)
	//{
	//	SetTextColor(_dc, RGB(0, 0, 255));
	//}

	//상태누적시간
	wstring acctime_line = L"누적시간:" + curtimestr.substr(0, curtimestr.find(L".")) + L"/" + curdurstr.substr(0, curdurstr.find(L"."))
		+ L"(" + percwstr.substr(0, percwstr.find(L".")) + L"%)";
	TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, acctime_line.c_str(), (int)acctime_line.length());
	++yoffset; ++yoffset;

	SetTextColor(_dc, RGB(255, 255, 255));

	//상태별 남은 쿨타임
	wstring statecool_line = L"상태별 남은 쿨타임:";
	TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, statecool_line.c_str(), (int)statecool_line.length());
	++yoffset;

	int size = (int)sizeof(m_bm2->m_left_cool) / sizeof(float);
	for (int i = 0; i < size; ++i)
	{

		if (m_bm2->m_left_cool[i] < 0.f)
		{
			SetBkColor(_dc, RGB(255, 255, 255));
			SetTextColor(_dc, RGB(0, 0, 255));
		}
		else
		{
			SetBkColor(_dc, RGB(255, 255, 255));
			SetTextColor(_dc, RGB(255, 255, 255));
		}
		if (curacctime * 1.1f > m_bm2->m_cooltime[i] - m_bm2->m_left_cool[i] &&
			curacctime * 0.9f < m_bm2->m_cooltime[i] - m_bm2->m_left_cool[i]
			&& 5.f < m_bm2->m_acctime)
		{
			SetBkColor(_dc, RGB(255, 255, 0));
			SetTextColor(_dc, RGB(255, 0, 0));
		}

		wstring leftcool = std::to_wstring(m_bm2->m_left_cool[i]);
		wstring cool = std::to_wstring(m_bm2->m_cooltime[i]);
		wstring tmpmsg = RSpacePad(m_bm2->m_state_nick[i], 4) + L": " + LSpacePad_Number(leftcool.substr(0, leftcool.find(L".")), 2)
			+ L"/"
			+ LSpacePad_Number(cool.substr(0, cool.find(L".")), 2);
		TextOut(_dc, (int)(debug_renpos.x), (int)(debug_renpos.y) + yoffset * yoffsetsize, tmpmsg.c_str(), (int)tmpmsg.length());
		++yoffset;
	}


	SetTextColor(_dc, RGB(255, 255, 255));
}

void CStateDebugUI::begin()
{
	if ((UINT)LEVEL_TYPE::PHASE_SECOND == CLevelMgr::GetInst()->GetCurLevelNum())
	{
		m_bm2 = dynamic_cast<CBlackMage2*>(CLevelMgr::GetInst()->GetCurLevelMon());

		if (nullptr == m_bm2)
		{
			m_visible = false;
			Destroy();
		}
	}
	else
	{
		m_visible = false;
		Destroy();
	}
}

CStateDebugUI::~CStateDebugUI()
{
}
