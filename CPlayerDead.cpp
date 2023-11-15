#include "pch.h"
#include "CPlayerDead.h"
#include "CEnteranceLevel.h"
#include "CLevelMgr.h"
#include "CUIMgr.h"

CPlayerDead::CPlayerDead()
{
}

CPlayerDead::~CPlayerDead()
{
}

void CPlayerDead::finaltick(float _DT)
{
}

void CPlayerDead::Enter()
{
	//애니메이션 재생
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeandead");

	CLevelMgr* pLevelMgr = CLevelMgr::GetInst();

	//디버그 맵이라면
	if ((UINT)LEVEL_TYPE::PHASE_ZERO == pLevelMgr->GetCurLevelNum())
	{
		//부활메세지 출력
		CUIMgr::GetInst()->SetUIVisible(L"ResurrUI1");
		return;
	}

	//데스카운트 깍기
	FRule* pRule = pLevelMgr->GetpRule();
	--(pRule->DeathCount);
	
	//부활메세지 출력1 : 데스카운트가 1이상일때
	if (pRule->DeathCount >= 1)
	{
		CUIMgr::GetInst()->SetUIVisible(L"ResurrUI1");
	}
	//부활메세지 출력2 : 데스카운트가 1보다 작을때
	else
	{

	}


}

void CPlayerDead::Exit()
{
}
