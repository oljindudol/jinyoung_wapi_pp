#include "pch.h"
#include "CEndroll.h"

#include "CSkillMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAssetMgr.h"

CEndroll::CEndroll()
	:m_veil(nullptr)
	, m_veil2(nullptr)
	, m_alpha1(0)
	, m_alpha2(0)
	, m_alpha3(3)
	, m_digit(0)
{
	m_s1 = L"fifth";
	m_s2 = L"endroll";
	m_s3 = L"use";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));

	SetScale(Vec2(245, 245));



	m_skilllayer = LAYER::SUPER_UI;
	duration = 60.f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;

	m_text = L"검은 마법사를 물리치고 세계를 구하였다.";

	owner_name = L"제작자 : 이진영";
	owner_email = L"lee.jinyoung.k181122@gmail.com";
	tobecontinued = L"to be continued...";

	m_veil = CAssetMgr::GetInst()->LoadTexture(L"endveil1", L"texture\\blacktex.png");
	m_endrolltex = CAssetMgr::GetInst()->LoadTexture(L"Endrolltex", L"texture\\endroll.png");
	m_veil2 = CAssetMgr::GetInst()->LoadTexture(L"endveil2", L"texture\\blacktex.png");


	m_digit= m_text.size();

}


void CEndroll::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);
}

void CEndroll::begin()
{
	CAssetMgr::GetInst()->LoadSound(L"업적", L"sound\\AchievmentComplete.wav")->Play();


}

void CEndroll::tick(float _DT)
{
	Super::tick(_DT);

	if (3.f > m_activedtime )
	{
		int tmp = (int)((( m_activedtime)) / 3.f * 255);
		if (255 < tmp) tmp = 255;

		m_alpha1 = tmp;
	}

	if (5.f <= m_activedtime
		&& 7.f)
	{
		int tmp = (int)(((m_activedtime -5.f)) / 2.f * 255);
		if (255 < tmp) tmp = 255;

		m_alpha2 = tmp;
	}




}


void CEndroll::render(HDC _dc)
{
	Super::render(_dc);

	SettexturetoDcWithAlpha(_dc, m_veil, Vec2(0,0), m_alpha1);
	SettexturetoDcWithAlphaAndMagnification(_dc, m_endrolltex, Vec2(227, 113), m_alpha2 ,1.5f);

	if (7.5f <= m_activedtime
		&& 18.5f >= m_activedtime )
	{
		int tmp = ((m_activedtime - 7.5f) / 4.f) * m_digit;

		if (m_digit < tmp) tmp = m_digit;
		wstring tmptext = m_text.substr(0, tmp);

		SetBkMode(_dc, TRANSPARENT);
		SELECT_FONT(_dc, FONT_TYPE::END_ROLL);
		SetTextColor(_dc, RGB(255, 255, 255));
		TextOut(_dc, 400, 600, tmptext.c_str(), (int)tmptext.length());
	}

	SettexturetoDcWithAlpha(_dc, m_veil2, Vec2(0,0), m_alpha3);




}

CEndroll::CEndroll(const CEndroll& _Origin)
{
}

CEndroll::~CEndroll()
{
}
