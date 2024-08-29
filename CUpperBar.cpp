#include "pch.h"
#include "CUpperBar.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLevelMgr.h"
#include "CMonster.h"


CUpperBar::CUpperBar()
	:vecbossthumbs()
	, hptex(nullptr)
	, hpbarcovertex(nullptr)
	, percenttex(nullptr)
	, percentback(nullptr)
	, dethcountbacktex(nullptr)
	, vecdeathcnttex()
	, timerbacktex(nullptr)
	, vectimetex()
	, vecbindtex()
	, m_hpbuffer(0)
	, CurLevelMon(nullptr)
	, pRule(nullptr)
	, CurLevelNum(0)
{
	m_uiname = L"UpperBarUI";
	SetScale(Vec2(801.f, 200.f));
	SetPos(Vec2(250.f, 2.f));

	CAssetMgr* asmgr = CAssetMgr::GetInst();

	//���� �����
	for (int i = 0; i < 5; i++)
	{
		vecbossthumbs.push_back(
			asmgr->LoadTexture(L"bossthumb_" + std::to_wstring(i)
				, L"texture\\upperbar\\" + std::to_wstring(i) + L".png")
		);
	}

	//���� ü�¹�
	hptex = asmgr->LoadTexture(L"bosshptex", L"texture\\upperbar\\redbar.png");
	hpbarcovertex = asmgr->LoadTexture(L"bosshpbar", L"texture\\upperbar\\boss_will_hp.backgrnd.png");
	percentback = asmgr->LoadTexture(L"bosshppercentback", L"texture\\upperbar\\MobHPRatioInfo.mob.0.backgrnd.png");
	percenttex = asmgr->LoadTexture(L"bosshppercent", L"texture\\upperbar\\MobHPRatioInfo.num.percent.png");

	//����ī��Ʈ ����
	dethcountbacktex = asmgr->LoadTexture(L"deathcntUI", L"texture\\upperbar\\DeathCountInfo.backgrd.png");
	for (int i = 0; i < 10; i++)
	{
		vecdeathcnttex.push_back(
			asmgr->LoadTexture(L"deathcntnum_" + std::to_wstring(i)
				, L"texture\\upperbar\\DeathCountInfo.number.frames\\" + std::to_wstring(i) + L".png")
		);
	}


	//Ÿ�̸� ����
	timerbacktex = asmgr->LoadTexture(L"timmerUI", L"texture\\upperbar\\timer2.backgrnd.png");
	for (int i = 0; i < 10; i++)
	{
		vectimetex.push_back(
			asmgr->LoadTexture(L"timmer_" + std::to_wstring(i)
				, L"texture\\upperbar\\timer2.fontTime.frames\\" + std::to_wstring(i) + L".png")
		);
	}

	//���ε�UI
	for (int i = 0; i < 1; i++)
	{
		vecbindtex.push_back(
			asmgr->LoadTexture(L"bindtex_" + std::to_wstring(i)
				, L"texture\\upperbar\\bindtex\\" + std::to_wstring(i) + L".png")
		);
	}

}


void CUpperBar::begin()
{

	CurLevelNum = (int)CLevelMgr::GetInst()->GetCurLevelNum();
	CurLevelMon = CLevelMgr::GetInst()->GetCurLevelMon();
	pRule = CLevelMgr::GetInst()->GetpRule();


}

void CUpperBar::tick(float _DT)
{
	if (nullptr == CurLevelMon)
		return;

	m_hpbuffer = m_hpbuffer + ((float)CurLevelMon->GetMonsterHp() - m_hpbuffer) * _DT * 5.f;
	Super::tick(_DT);
}

void CUpperBar::render(HDC _dc)
{
	if (nullptr == CurLevelMon)
		return;

	Vec2 vRenderPos = GetPos();
	Vec2 vScale = GetScale();


	//������ ü��
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0�̿����մϴ�

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // ����

	float perc = m_hpbuffer / CurLevelMon->GetMonsterMaxHp();


	//ü��Ŀ��
	SettexturetoDc(_dc, hpbarcovertex, vRenderPos);

	AlphaBlend(_dc
		, (int)(vRenderPos.x + 40.f)
		, (int)(vRenderPos.y + 5.f)
		, (int)(757 * perc)
		, 10
		, hptex->GetDC()
		, 0, 0
		, 37
		, 17
		, blend);

	//�ۼ�Ʈ ����
	SettexturetoDc(_dc, percentback, vRenderPos + Vec2(0.f, 35.f));

	//�ۼ�Ʈ �ؽ���
	SettexturetoDc(_dc, percenttex, vRenderPos + Vec2(26.f, 40.f));


	float percent = CurLevelMon->GetMonsterHp() * 100 / CurLevelMon->GetMonsterMaxHp();
	wstring a;

	if (100.f == percent)
	{
		a = L"100";
	}
	else
	{
		a = std::to_wstring(percent);
		a = a.substr(0, a.find(L'.') + 2);
	}

	SetBkMode(_dc, TRANSPARENT);
	SELECT_FONT(_dc, FONT_TYPE::STATUS_BAR_NAME);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, (int)(vRenderPos.x + 3.f), (int)(vRenderPos.y + 39.f), a.c_str(), (int)a.length());


	//���� �����
	SettexturetoDc(_dc, vecbossthumbs[(CurLevelNum - 1)], vRenderPos + Vec2(5.f, 5.f));

	//����ī��Ʈ
	SettexturetoDc(_dc, dethcountbacktex, vRenderPos + Vec2(203.f, 50.f));


	int lakeofhpdigit = 0;
	int	digitwitdh = 0;
	if (10 > pRule->DeathCount)
	{
		lakeofhpdigit = 1;
		if (0 != vecdeathcnttex.size())
			digitwitdh = (int)vecdeathcnttex[0]->GetWidth();
	}

	//����ī��Ʈ ����
	SetNumberTextureToDc(_dc, pRule->DeathCount, vecdeathcnttex,
		(vRenderPos + Vec2(203.f + 45.f
			+ 5.f * (1 + lakeofhpdigit)
			+ digitwitdh
			, 79.f)));

	//Ÿ�̸� ����
	SettexturetoDc(_dc, timerbacktex, vRenderPos + Vec2(293.f, 50.f));

	int leftsec = pRule->leftsecond;

	int min = leftsec / 60;
	int sec = leftsec % 60;

	lakeofhpdigit = 0;
	digitwitdh = 0;
	if (10 > min)
	{
		lakeofhpdigit = 1;
		if (0 != vecdeathcnttex.size())
			digitwitdh = (int)vecdeathcnttex[0]->GetWidth();
	}

	//�ð� ��
	SetNumberTextureToDc(_dc, min, vectimetex,
		(vRenderPos + Vec2(293.f + 72.f
			+ 10.f * (1 + lakeofhpdigit)
			+ digitwitdh
			, 50.f + 13.f)), 5.f);


	//�ð� ��
	SetNumberTextureToDcWithTwoDigitZeroPadding(_dc, sec, vectimetex,
		(vRenderPos + Vec2(293.f + 130.f
			+ 20.f
			, 50.f + 13.f)), 5.f);

}



CUpperBar::~CUpperBar()
{

}
