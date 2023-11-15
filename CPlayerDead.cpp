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
	//�ִϸ��̼� ���
	CAnimator* pAni = GetAnimator();
	pAni->Play(L"commonpinkbeandead");

	CLevelMgr* pLevelMgr = CLevelMgr::GetInst();

	//����� ���̶��
	if ((UINT)LEVEL_TYPE::PHASE_ZERO == pLevelMgr->GetCurLevelNum())
	{
		//��Ȱ�޼��� ���
		CUIMgr::GetInst()->SetUIVisible(L"ResurrUI1");
		return;
	}

	//����ī��Ʈ ���
	FRule* pRule = pLevelMgr->GetpRule();
	--(pRule->DeathCount);
	
	//��Ȱ�޼��� ���1 : ����ī��Ʈ�� 1�̻��϶�
	if (pRule->DeathCount >= 1)
	{
		CUIMgr::GetInst()->SetUIVisible(L"ResurrUI1");
	}
	//��Ȱ�޼��� ���2 : ����ī��Ʈ�� 1���� ������
	else
	{

	}


}

void CPlayerDead::Exit()
{
}
