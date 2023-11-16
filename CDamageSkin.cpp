#include "pch.h"
#include "CDamageSkin.h"
#include "CSkillMgr.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"




CDamageSkin::CDamageSkin()
	:m_temp_printdamage(L"")
{
	m_s1 = L"common";
	m_s2 = L"pinkbean";
	m_s3 = L"damageskin_violet";

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
			CAssetMgr::GetInst()->LoadTexture(L"VioletDamageNum_" + std::to_wstring(i)
				, L"texture\\damageskin\\NoViolet1.frames\\" + std::to_wstring(i) + L".png")
		);
	}
}

CDamageSkin::CDamageSkin(const CDamageSkin& _Origin)
{

}

void CDamageSkin::PrintDamage(Vec2 _beginpos, int _damage)
{
	// activatedtime 초기화
	m_activedtime = 0.f;

	// 좌우 설정
	ort = ORT_LEFT;

	m_OnActivate = true;

	SetLive();

	// 레벨에참여
	CTaskMgr::GetInst()->AddTask(FTask{ CREATE_OBJECT, (UINT_PTR)m_skilllayer, (UINT_PTR)this });


	m_temp_printdamage = L"";
	m_temp_randomoffset.clear();
	m_temp_pos = _beginpos;

	wstring strnums = std::to_wstring(_damage);

	//길이를 보고 유닛을 끼워넣는처리
	int numssize = (int)strnums.size();
	m_temp_printdamage = strnums;

	float xoffset = -12.f;

	int numberwidth = 0;
	int numberheight = 0;

	if (0 != m_DamageSkinNumbers.size())
	{
		numberwidth = (int)m_DamageSkinNumbers[0]->GetWidth();
		numberheight = (int)m_DamageSkinNumbers[0]->GetHeight();
	}

	float maxf = 32767.f;
	float randoffpercent = 0.1f;

	float accoffset =0.f;

	for (int i = 0; i<m_temp_printdamage.size(); ++i)
	{
		//만일때
		//if (false)
		//{
		//	continue;
		//}
		//억일때
		//if (false)
		//{
		//	continue;
		//}
		//숫자일때,
		m_temp_randomoffset.push_back
		(
			Vec2
			(
				accoffset + numberwidth * (rand() / maxf - 0.5f) * randoffpercent,
				numberheight * (rand() / maxf - 0.5f) * randoffpercent
			)
		);
		accoffset += (numberwidth + xoffset);
	}
}

void CDamageSkin::render(HDC _dc)
{
	float durationperc = m_activedtime / duration;
	int alpha = 255 -(int)(110.f * durationperc);
	Vec2 yoffset = Vec2(0.f, -20.f * durationperc);

	int numssize = (int)m_temp_printdamage.size();



	for (int i = 0; i < numssize; i++)
	{

		//숫자일때,
		int num = m_temp_printdamage[i] - '0';
		SettexturetoDcWithAlpha(_dc,
			m_DamageSkinNumbers[num], m_temp_pos
			+ m_temp_randomoffset[i] + yoffset
			, alpha);


	}
}



void CDamageSkin::begin()
{


}




void CDamageSkin::tick(float _DT)
{
	Super::tick(_DT);


}

void CDamageSkin::BeginOverlap(CCollider* _OwnCol, CObj* _OtherObj, CCollider* _OtherCol)
{
}







CDamageSkin::~CDamageSkin()
{
}
