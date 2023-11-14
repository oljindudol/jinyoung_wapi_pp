#include "pch.h"
#include "rulemon11.h"

#include "CMonsterMgr.h"

#include "CRuleMon11Idle.h"
#include "CRuleMon11Attack.h"

#include "CTimeManager.h"
#include "CLogMgr.h"


rulemon11::rulemon11()
{
	ort = ORT_RIGHT;
	m_s1 = L"first";
	m_s2 = L"rulemon11";

	m_monstername = m_s1 + m_s2;

	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	SetName(m_monstername);

	SetScale(Vec2(200.f, 600.f));


	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CRuleMon11Idle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK1, new CRuleMon11Attack);

}


rulemon11::rulemon11(const rulemon11& _Origin)
{
	m_AI = GetComponent<CStateMachine>();
	

}


void rulemon11::begin()
{
}


void rulemon11::tick(float _DT)
{
	Super::tick(_DT);
}





rulemon11::~rulemon11()
{

}
