#include "pch.h"
#include "rulemon12.h"
#include "CMonsterMgr.h"

#include "CRuleMon12Idle.h"
#include "CRuleMon12Attack.h"

#include "CKeyMgr.h"

rulemon12::rulemon12()
{
	ort = ORT_RIGHT;
	m_s1 = L"first";
	m_s2 = L"rulemon12";

	m_monstername = m_s1 + m_s2;

	//몇번째 몬스터 인지
	m_monsternum = CMonsterMgr::GetInst()->FindNextMonsterNumber(m_monstername);

	SetName(m_monstername);

	SetScale(Vec2(200.f, 600.f));


	// 상태머신 컴포넌트 추가 및 설정
	m_AI = AddComponent<CStateMachine>(GetName() + L"AI");
	m_AI->AddState((UINT)ENORMAL_MON_STATE::IDLE, new CRuleMon12Idle);
	m_AI->AddState((UINT)ENORMAL_MON_STATE::ATTACK1, new CRuleMon12Attack);

}

rulemon12::rulemon12(const rulemon12& _Origin)
{
	m_AI = GetComponent<CStateMachine>();
}


void rulemon12::begin()
{
}

void rulemon12::tick(float _DT)
{
	Super::tick(_DT);

	if (KEY_TAP(KEY::_0))
	{
		m_AI->ChangeState((UINT)ENORMAL_MON_STATE::ATTACK1);
	}
}



rulemon12::~rulemon12()
{
}
