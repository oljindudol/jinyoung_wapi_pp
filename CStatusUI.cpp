#include "pch.h"
#include "CStatusUI.h"
#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogMgr.h"

CStatusUI::CStatusUI()
	:RenderDc(nullptr)
	,testhp(100)
	,acctime(0.f)
	,desc(true)
{
	SetScale(Vec2(204.f, 70.f));
	SetPos(Vec2(600.f, 690.f));

	CAssetMgr* asmgr = CAssetMgr::GetInst();

	backtex = asmgr->LoadTexture(L"StatusUIBack", L"texture\\status\\mainBar.status.backgrnd.png");
	hptex = asmgr->LoadTexture(L"StatusUIHp", L"texture\\status\\mainBar.status.gauge.hp.layer.0.png");
	mptex = asmgr->LoadTexture(L"StatusUIMp", L"texture\\status\\mainBar.status.gauge.mp.layer.0.png");
	covertex = asmgr->LoadTexture(L"StatusUICover", L"texture\\status\\status.layer.cover.png");
	lvtex= asmgr->LoadTexture(L"StatusUILv", L"texture\\status\\layer.Lv.png");

	for (int i = 0; i < 10; i++)
	{
		vecgaugetex.push_back(
			asmgr->LoadTexture(L"StatusUINum"+ std::to_wstring(i), L"texture\\status\\gauge.number.frames\\" + std::to_wstring(i) + L".png"  )
		);

		veclvtex.push_back(
			asmgr->LoadTexture(L"StatusUILv" + std::to_wstring(i), L"texture\\status\\lvNumber.frames\\" + std::to_wstring(i) + L".png")
		);
	}
}

CStatusUI::~CStatusUI()
{

}

void SettexturetoDcPartiallyRight (HDC _dc,CTexture* _tex, Vec2 _pos , float _perc)
{

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, _pos.x
		, _pos.y
		, _tex->GetWidth() * _perc
		, _tex->GetHeight()
		, _tex->GetDC()
		, 0, 0
		, _tex->GetWidth() * _perc
		, _tex->GetHeight()
		, blend);
}

void SettexturetoDcPartiallyDown(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, _pos.x
		, _pos.y
		, _tex->GetWidth() 
		, _tex->GetHeight() * _perc
		, _tex->GetDC()
		, 0, 0
		, _tex->GetWidth() 
		, _tex->GetHeight() * _perc
		, blend);

}


void CStatusUI::SetLettertoDc(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset)
{
	wstring strnums = std::to_wstring(_num);

	Vec2 offset = Vec2(_offset, 0.f);

	if (0 != _vecnumtex.size())
	{
		offset += Vec2(
			(int)_vecnumtex[0]->GetWidth()
			, 0
		);
	}

	for (int i = 0; i < strnums.size(); i++)
	{
		int num = strnums[i] - '0';
		SettexturetoDc(_dc, _vecnumtex[num], _pos + (offset*i) );
	}

}

void CStatusUI::SettexturetoDc(HDC _dc, CTexture* _ptexture, Vec2 _pos)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, int(_pos.x)
		, int(_pos.y)
		, _ptexture->GetWidth()
		, _ptexture->GetHeight()
		, _ptexture->GetDC()
		, 0, 0
		, _ptexture->GetWidth()
		, _ptexture->GetHeight()
		, blend);
}


void CStatusUI::tick(float _DT)
{
	acctime += _DT;

	if (acctime > 0.06f)
	{
		if(desc)
		{
			testhp -= 1;
		}
		else
		{
			testhp += 1;
		}

		if (0 == testhp)
			desc = false;

		if (100 == testhp)
			desc = true;

		acctime = 0.f;
	}

	Super::tick(_DT);
}

void CStatusUI::render(HDC _dc)
{
	Vec2 vRenderPos = GetPos();
	Vec2 vScale = GetScale();

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정


	//스테이터스 배경
	SettexturetoDc(_dc, backtex, (vRenderPos + Vec2(3.f, 23.f )));
	
	//체력비율
	SettexturetoDcPartiallyRight(_dc, hptex, (vRenderPos + Vec2(24.f, 28.f)), ((float)testhp / (float)100));

	//마력비율
	SettexturetoDcPartiallyRight(_dc, mptex, (vRenderPos + Vec2(24.f, 44.f)), ((float)testhp / (float)100));

	//스테이터스 커버
	SettexturetoDc(_dc, covertex, (vRenderPos));

	//레벨 표시
	SettexturetoDc(_dc, lvtex, (vRenderPos + Vec2(25.f, 9.f)));
	SetLettertoDc(_dc, 290, veclvtex, (vRenderPos + Vec2(42.f, 9.f)));


	int xoffset = 0.f;
	if (0 != vecgaugetex.size())
	{
		xoffset = vecgaugetex[0]->GetWidth();
	}

	int lakeofhpdigit = 5 - std::to_wstring(testhp).size();
	int lakeofmpdigit = 5 - std::to_wstring(testhp).size();

	//체력 
	SetLettertoDc(_dc, testhp, vecgaugetex, (vRenderPos + Vec2(65.f+ xoffset* lakeofhpdigit, 30.f)));
	SetLettertoDc(_dc, 50000, vecgaugetex, (vRenderPos + Vec2(110.f, 30.f)));

	//MP
	SetLettertoDc(_dc, testhp, vecgaugetex, (vRenderPos + Vec2(65.f + xoffset* lakeofmpdigit, 46.f)));
	SetLettertoDc(_dc, 50000, vecgaugetex, (vRenderPos + Vec2(110.f , 46.f)));



	Super::render(_dc);

}
