#include "pch.h"
#include "CDamageSkinRed.h"
#include "CSkillMgr.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"


CDamageSkinRed::CDamageSkinRed()
	:m_temp_printdamage(L"")
{
	m_s1 = L"common";
	m_s2 = L"pinkbean";
	m_s3 = L"damageskin_red";

	m_skillname = m_s1 + m_s2 + m_s3;

	//몇번째 스킬인지
	m_skillnum = CSkillMgr::GetInst()->FindNextSkillNumber(m_skillname);

	SetName(m_skillname + L"_" + std::to_wstring(m_skillnum));


	m_skilllayer = LAYER::PLAYER_SKILL;
	duration = 1.f;
	cooltime = 0.f;
	m_att = 5.f;
	m_debuff = DEBUFF::NONE;


	for (int i = 0; i < 10; ++i)
	{
		m_DamageSkinNumbers.push_back(
			CAssetMgr::GetInst()->LoadTexture(L"RedDamageNum_" + std::to_wstring(i)
				, L"texture\\damageskin\\208.NoCri1.frames\\" + std::to_wstring(i) + L".png")
		);
	}

	m_DamageSkinUnits.push_back
	(CAssetMgr::GetInst()->LoadTexture(L"RedDamageOk"
		, L"texture\\damageskin\\208.NoCri1.frames\\ok.png"));

	m_DamageSkinUnits.push_back
	(CAssetMgr::GetInst()->LoadTexture(L"RedDamageMan"
		, L"texture\\damageskin\\208.NoCri1.frames\\man.png"));




}

CDamageSkinRed::CDamageSkinRed(const CDamageSkinRed& _Origin)
{
}

CDamageSkinRed::~CDamageSkinRed()
{
}

void CDamageSkinRed::PrintDamage(Vec2 _beginpos, long long _damage ,int _th)
{

	// activatedtime 초기화
	m_activedtime = 0.f;

	// 좌우 설정
	ort = ORT_LEFT;

	m_OnActivate = true;

	m_temp_delay = 0.1f * _th;
	m_temp_ready = false;

	SetLive();

	// 레벨에참여
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)m_skilllayer, (UINT_PTR)this });


	m_temp_printdamage = L"";
	m_temp_randomoffset.clear();
	m_temp_pos = _beginpos;

	wstring strnums = std::to_wstring(_damage);

	//길이를 보고 유닛을 끼워넣는처리
	int numssize = (int)strnums.size();
	if (numssize > 8)
	{
		strnums = strnums.insert(numssize - 8 , L"억");
		++numssize;
	}
	if (numssize > 4)
	{
		strnums = strnums.insert(numssize - 4, L"만");
		++numssize;
	}

	m_temp_printdamage = strnums;

	float xoffset = -12.f;

	int numberwidth = 0;
	int numberheight = 0;

	int unitwidth = 0;
	int unitheight = 0;

	if (0 != m_DamageSkinNumbers.size())
	{
		numberwidth = (int)m_DamageSkinNumbers[0]->GetWidth();
		numberheight = (int)m_DamageSkinNumbers[0]->GetHeight();
	}

	if (0 != m_DamageSkinUnits.size())
	{
		unitwidth = (int)m_DamageSkinUnits[0]->GetWidth();
		unitheight = (int)m_DamageSkinUnits[0]->GetHeight();
	}

	float maxf = 32767.f;
	float randoffpercent = 0.1f;

	float accoffset = 0.f;

	for (int i = 0; i < m_temp_printdamage.size(); ++i)
	{
		
		m_temp_randomoffset.push_back
		(
			Vec2
			(
				accoffset + numberwidth * (rand() / maxf - 0.5f) * randoffpercent,
				numberheight * (rand() / maxf - 0.5f) * randoffpercent
			)
		);
		if ('억' == m_temp_printdamage[i]
			|| '만' == m_temp_printdamage[i])
		{
			accoffset += unitwidth;
		}
		else
		{
			accoffset += (numberwidth + xoffset);
		}
	}
}

void CDamageSkinRed::begin()
{

}

void CDamageSkinRed::render(HDC _dc)
{
	if (false == m_temp_ready)
		return;

	float durationperc = m_activedtime / duration;
	int alpha = 255 - (int)(110.f * durationperc);
	Vec2 yoffset = Vec2(0.f, -20.f * durationperc);

	int numssize = (int)m_temp_printdamage.size();



	for (int i = 0; i < numssize; i++)
	{
		wchar_t tmpchar =  m_temp_printdamage[i];

		if (L'억' == tmpchar)
		{
			SettexturetoDcWithAlpha(_dc,
				m_DamageSkinUnits[0], m_temp_pos
				+ m_temp_randomoffset[i] + yoffset
				, alpha);
		}
		else if (L'만' == tmpchar)
		{
			SettexturetoDcWithAlpha(_dc,
				m_DamageSkinUnits[1], m_temp_pos
				+ m_temp_randomoffset[i] + yoffset
				, alpha);
		}
		//숫자일때,
		else
		{
			int num = tmpchar - '0';
			SettexturetoDcWithAlpha(_dc,
				m_DamageSkinNumbers[num], m_temp_pos
				+ m_temp_randomoffset[i] + yoffset
				, alpha);
		}
	}
}

void CDamageSkinRed::tick(float _DT)
{
	Super::tick(_DT);
	if ((false == m_temp_ready) &&
		(m_activedtime > m_temp_delay) )
	{
		m_activedtime = 0.f;
		m_temp_ready = true;
	}
}

void CDamageSkinRed::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}





