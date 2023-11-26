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
	, m_alpha3(0)
	, m_digit(0)
	, m_musicplayed(false)
	, m_effecsoundplayed(false)
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
	thankyoforwatching = L"시청해주셔서 감사합니다";

	m_veil = CAssetMgr::GetInst()->LoadTexture(L"endveil1", L"texture\\blacktex.png");
	m_endrolltex = CAssetMgr::GetInst()->LoadTexture(L"Endrolltex", L"texture\\endroll.png");
	m_veil2 = CAssetMgr::GetInst()->LoadTexture(L"endveil2", L"texture\\blacktex.png");


	m_digit= (int)m_text.size();
	CAssetMgr::GetInst()->LoadSound(L"타자소리", L"sound\\삼국전기텍스트사운드.wav")->SetVolume(100);
	CAssetMgr::GetInst()->LoadSound(L"엔딩노래", L"sound\\Promise of Heaven_mvver.wav")->SetVolume(100);
}


void CEndroll::activate(Vec2 _beginpos, ORIENTATION _ort)
{
	Super::activate(_beginpos, _ort);
}

void CEndroll::begin()
{
	CAssetMgr::GetInst()->LoadSound(L"업적", L"sound\\AchievmentComplete.wav")->Play();
	m_alpha1 = 0;
	m_alpha2 = 0;
	m_alpha3 = 0;
	m_musicplayed = false;
	m_effecsoundplayed = false;
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
		&& 7.f >= m_activedtime)
	{
		int tmp = (int)(((m_activedtime -5.f)) / 2.f * 255);
		if (255 < tmp) tmp = 255;

		m_alpha2 = tmp;
	}

	if (7.f <= m_activedtime
		&& 8.5f >= m_activedtime)
	{
		int tmp = (int)(((m_activedtime - 7.f) / 1.5f) * 88);

		m_alpha2 = 255 - tmp;
	}


	if (9.f < m_activedtime
		&& m_effecsoundplayed == false)
	{
		CAssetMgr::GetInst()->LoadSound(L"타자소리", L"sound\\삼국전기텍스트사운드.wav")->Play();
		m_effecsoundplayed = true;
	}


	if (16.f < m_activedtime
		&& m_musicplayed == false)
	{
		CAssetMgr::GetInst()->LoadSound(L"엔딩노래", L"sound\\Promise of Heaven_mvver.wav")->Play();
		m_musicplayed = true;
	}

	if (15.5f <= m_activedtime
		&& 18.5f >= m_activedtime)
	{
		int tmp = (int)((m_activedtime - 15.5f) / 3.f * 255);

		if (255 < tmp) tmp = 255;
		m_alpha3 = tmp;
	}

	if (20.5f <= m_activedtime
		&& 21.5f >= m_activedtime)
	{
		int tmp = (int)((21.5f - m_activedtime) / 1.f * 255);

		if (0 > tmp) tmp = 0;
		m_alpha3 = tmp;
	}

	if (m_activedtime > duration- 0.5f)
	{
		CAssetMgr::GetInst()->LoadSound(L"엔딩노래", L"sound\\Promise of Heaven_mvver.wav")->Stop();
	}

}


void CEndroll::render(HDC _dc)
{
	Super::render(_dc);

	SettexturetoDcWithAlpha(_dc, m_veil, Vec2(0,0), m_alpha1);

	if (18.5f > m_activedtime)
	{
		SettexturetoDcWithAlphaAndMagnification(_dc, m_endrolltex, Vec2(227, 113), m_alpha2 ,1.5f);
	}

	SettexturetoDcWithAlpha(_dc, m_veil2, Vec2(0, 0), m_alpha3);

	if (9.0f <= m_activedtime
		&& 18.5f >= m_activedtime )
	{
		int tmp = (int)(((m_activedtime - 9.0f) / 4.f) * m_digit);

		if (m_digit < tmp) tmp = m_digit;
		wstring tmptext = m_text.substr(0, tmp);

		SetBkMode(_dc, TRANSPARENT);
		SELECT_FONT(_dc, FONT_TYPE::END_ROLL);
		SetTextColor(_dc, RGB(255, 255, 255));
		TextOut(_dc, 400, 600, tmptext.c_str(), (int)tmptext.length());
	}


	if (19.5f <= m_activedtime)
	{
		SetBkMode(_dc, TRANSPARENT);
		SELECT_FONT(_dc, FONT_TYPE::END_ROLL);
		SetTextColor(_dc, RGB(255, 255, 255));
		TextOut(_dc, 480, 350, thankyoforwatching.c_str(), (int)thankyoforwatching.length());


		TextOut(_dc, 70, 620, owner_name.c_str(), (int)owner_name.length());
		TextOut(_dc, 70, 650, owner_email.c_str(), (int)owner_email.length());
		TextOut(_dc, 1000, 650, tobecontinued.c_str(), (int)tobecontinued.length());
	}

	SettexturetoDcWithAlpha(_dc, m_veil2, Vec2(0, 0), m_alpha3);

}

CEndroll::CEndroll(const CEndroll& _Origin)
{
}

CEndroll::~CEndroll()
{
}
