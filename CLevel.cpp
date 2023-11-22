#include "pch.h"
#include "CLevel.h"

#include "CTimeManager.h"
#include "CObj.h"
#include "CTile.h"
#include "CLayer.h"
#include "CSkillMgr.h"
#include "CMonsterMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CLogMgr.h"
#include "CEngine.h"
#include "CUIMgr.h"
#include "CAssetMgr.h"
#include "CSkill.h"
#include "CLevelMgr.h"
#include "CMonster.h"


class CEntity;
class CLayer;



CLevel::CLevel()
	: m_TileRow(0)
	, m_TileCol(0)
	, m_BackGround(nullptr)
	, m_BackOn(false)
	, pPlayer(nullptr)
	, pBgm(nullptr)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i] = new CLayer;
		m_Layer[i]->setLayer((LAYER)i);
	}
}

CLevel::~CLevel()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		if (nullptr != m_Layer[i])
			delete m_Layer[i];
	}
}

CPlayer* CLevel::GetPlayer()
{
	if (nullptr != pPlayer)
	{
		return pPlayer;
	}


	if (nullptr == pPlayer)
	{
		vector<CObj*> objvec= GetObjects(LAYER::PLAYER);
		if(0 != objvec.size())
			return dynamic_cast<CPlayer*>(objvec[0]);

	}

	return nullptr;
}



void CLevel::begin()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->begin();
	}
}

void CLevel::tick()
{
	//float DT = CTimeManager::GetInst()->GetDeltaTime();

	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->clear();
	}


	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->tick(DT);
	}
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->finaltick(DT);
	}

	// 
	if (KEY_TAP(KEY::_1))
	{
		//int a = rand();
		//float perc = ((float)(a % 100)) / 100.f;


		CMonsterMgr::GetInst()->SpwanMonster(L"firstion", Vec2((m_LevelMiddle.x - 400.f), 400.f));
		CMonsterMgr::GetInst()->SpwanMonster(L"firstyalda", Vec2((m_LevelMiddle.x + 400.f), 400.f));
	}

	if (KEY_TAP(KEY::_2))
	{
		CMonsterMgr::GetInst()->ChangeAllMonsterForcedIdle();
	}

	if (KEY_TAP(KEY::_3))
	{
		CMonsterMgr::GetInst()->ChangeAllMonsterIdle();
	}

	if (KEY_TAP(KEY::_4))
	{
		CMonsterMgr::GetInst()->ChangeAllMonsterForcedIdle();
		CLevelMgr::GetInst()->GetCurLevelMon()->GetAI()->ChangeState((UINT)ENORMAL_MON_STATE::DEBUG);
	}

	if (KEY_TAP(KEY::LBTN))
	{
		//
		//CMonsterMgr::GetInst()->SpwanMonster(L"firstdarkfalling",
		//	CCamera::GetInst()->GetRealPos( CKeyMgr::GetInst()->GetMousePos()));
		// 
		//CSkillMgr::GetInst()->ActivateSkill(L"firstrulemonchainattack", CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos()), ORT_LEFT);
	}

	if (KEY_TAP(KEY::_5))
	{
		CUIMgr::GetInst()->FloatNotice(L"아아아아아아아아아아아아아아아아아아아아", 2.f);
		//CUIMgr::GetInst()->FloatNotice(L"아 아 아 아 아 아 아 아 아 아 아 아 ", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"어. 어. 어. 어. 어. 어. 어. 어. 어. 어. 어.", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"파멸의 눈이 적을 쫓는다.", 5.f);
	}

	if (KEY_TAP(KEY::_6))
	{
		//CUIMgr::GetInst()->FloatNotice(L"아아아아아아아아아아아아아아아아아아아아", 5.f);
		CUIMgr::GetInst()->FloatNotice(L"아 아 아 아 아 아 아 아 아 아 아 아 ", 2.f);
		//CUIMgr::GetInst()->FloatNotice(L"어. 어. 어. 어. 어. 어. 어. 어. 어. 어. 어.", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"파멸의 눈이 적을 쫓는다.", 5.f);
	}

	if (KEY_TAP(KEY::_7))
	{
		//CUIMgr::GetInst()->FloatNotice(L"아아아아아아아아아아아아아아아아아아아아", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"아 아 아 아 아 아 아 아 아 아 아 아 ", 5.f);
		CUIMgr::GetInst()->FloatNotice(L"어.어.어.어.어.어.어.어.어.어.어.", 2.f);
		//CUIMgr::GetInst()->FloatNotice(L"파멸의 눈이 적을 쫓는다.", 5.f);
	}

	if (KEY_TAP(KEY::_8))
	{
		//CUIMgr::GetInst()->FloatNotice(L"아아아아아아아아아아아아아아아아아아아아", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"아 아 아 아 아 아 아 아 아 아 아 아 ", 5.f);
		CUIMgr::GetInst()->FloatNotice(L"어. 어. 어. 어. 어. 어. 어. 어. 어. 어. 어.", 2.f);
		//CUIMgr::GetInst()->FloatNotice(L"파멸의 눈이 적을 쫓는다.", 5.f);
	}

	if (KEY_TAP(KEY::_9))
	{
		//CUIMgr::GetInst()->FloatNotice(L"아아아아아아아아아아아아아아아아아아아아", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"아 아 아 아 아 아 아 아 아 아 아 아 ", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"어. 어. 어. 어. 어. 어. 어. 어. 어. 어. 어.", 1.f);
		CUIMgr::GetInst()->FloatNotice(L"파멸의 눈이 적을 쫓는다.", 2.f);
	}



	if (KEY_TAP(KEY::F3))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonreadytodieuse"))
		{

		}
		else 
		{
			CAssetMgr::GetInst()->LoadSound(L"레투다use", L"sound\\레투다use.wav")->Play();
			CSkillMgr::GetInst()->ActivateSkill(L"commonreadytodieuse", GetPlayer()->GetPos(), ORT_LEFT);
		}
	}	
	if (KEY_TAP(KEY::F4))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonsoulcontractuse"))
		{

		}
		else
		{
			CAssetMgr::GetInst()->LoadSound(L"엔버use", L"sound\\엔버use.wav")->Play();
			CSkillMgr::GetInst()->ActivateSkill(L"commonsoulcontractuse", GetPlayer()->GetPos(), ORT_LEFT);
		}
	}	
	if (KEY_TAP(KEY::F5))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonerdanovause"))
		{

		}
		else
		{
			CSkillMgr::GetInst()->ActivateSkill(L"commonerdanovause", GetPlayer()->GetPos(), ORT_LEFT);
		}
	}

	if (KEY_TAP(KEY::E))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonkarmafuryuse"))
		{

		}
		else
		{
			CSkillMgr::GetInst()->ActivateSkill(L"commonkarmafuryuse", GetPlayer()->GetPos(), ORT_LEFT);
		}
	}
	if (KEY_TAP(KEY::G))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonbladetornadouse"))
		{

		}
		else
		{
			CSkillMgr::GetInst()->ActivateSkill(L"commonbladetornadouse", GetPlayer()->GetPos(), pPlayer->ort);
		}
	}
	if (KEY_TAP(KEY::F))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonbladestormuse"))
		{

		}
		else
		{
			GetPlayer()->getStateMachine()->ChangeState((UINT)PLAYER_STATE::ATT_SP);
		}
	}
	//if (KEY_RELEASED(KEY::F))
	//{
	//	if (nullptr != ptmpskill && !ptmpskill->IsDead())
	//	{
	//		ptmpskill->Destroy();
	//	}
	//}

	if (KEY_TAP(KEY::F6))
	{
		//CUIMgr::GetInst()->FloatNotice(L"아아아아아아아아아아아아아아아아아아아아", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"아 아 아 아 아 아 아 아 아 아 아 아 ", 5.f);
		//CUIMgr::GetInst()->FloatNotice(L"어. 어. 어. 어. 어. 어. 어. 어. 어. 어. 어.", 5.f);
		CUIMgr::GetInst()->FloatNotice(L"파멸의 눈이 적을 쫓는다.", 1.f);
	}


	if (KEY_TAP(KEY::PAGE_DOWN))
	{
		if (CSkillMgr::GetInst()->IsCoolTime(L"commonrestraintringroop"))
		{

		}
		else
		{
			CSkillMgr::GetInst()->ActivateSkill(L"commonrestraintringroop", GetPlayer()->GetPos(), ORT_LEFT);
		}

	}

	if (KEY_TAP(KEY::LCTRL))
	{
		CAssetMgr::GetInst()->CAssetMgr::GetInst()->LoadSound(L"potion", L"sound\\포션.wav")->Play();
		pPlayer->hp = pPlayer->maxhp;
	}

	if (KEY_TAP(M))
	{
		CBackGround* pBack = m_BackGround;
		bool bBack = m_BackOn;

		// pback 이 설정되어있고 백그라운드off이라면
		// 켜준다
		if (nullptr != pBack && !bBack)
		{
			CTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::CREATE_OBJECT,(UINT_PTR)LAYER::BACKGROUND ,(UINT_PTR)pBack });
			m_BackOn = true;
		}
		// pback 이 설정되어있고 백그라운드on이라면
		// 꺼준다
		else if (nullptr != pBack && bBack)
		{
			CTaskMgr::GetInst()->AddTask(FTask{ TASK_TYPE::EXPEL_OBJECT, (UINT_PTR)pBack });
			m_BackOn = false;
		}
	}

	//디버그 로그
	if (!DEBUG_RENDER)
		return;

	if (KEY_TAP(Y))
	{

		auto ai = CLevelMgr::GetInst()->GetCurLevelMon()->GetAI();
		auto ainum = ai->GetCurStateNum();
		UINT nextainum = ainum + 1;
		if (ai->FindState(nextainum))
			ai->ChangeState(nextainum);
		else
			ai->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		wstring statename = std::to_wstring(ai->GetCurStateNum());
		LOG(LOG_LEVEL::LOG, statename.c_str());
	}

	if (KEY_TAP(T))
	{

		auto ai = CLevelMgr::GetInst()->GetCurLevelMon()->GetAI();
		auto ainum = ai->GetCurStateNum();
		UINT nextainum = ainum - 1;
		if (ai->FindState(nextainum))
			ai->ChangeState(nextainum);
		else
			ai->ChangeState((UINT)ENORMAL_MON_STATE::IDLE);
		wstring statename = std::to_wstring(ai->GetCurStateNum());
		LOG(LOG_LEVEL::LOG, statename.c_str());
	}


	if (KEY_TAP(H))
	{
		auto ai = CLevelMgr::GetInst()->GetCurLevelMon()->GetAI();
		auto ainum = ai->GetCurStateNum();

		auto curanim = CLevelMgr::GetInst()->GetCurLevelMon()->GetAnimator()->GetCurAnim();
		auto newoffset = curanim->GetOffset() + Vec2(-1, 0);
		curanim->Setoffset(newoffset);
		wstring log = std::to_wstring(ainum) + L":"
			+ L"(" + std::to_wstring((int)newoffset.x) + L","
			+ std::to_wstring((int)newoffset.y) + L")";

		LOG(LOG_LEVEL::LOG, log.c_str());

	}
	if (KEY_TAP(K))
	{
		auto ai = CLevelMgr::GetInst()->GetCurLevelMon()->GetAI();
		auto ainum = ai->GetCurStateNum();

		auto curanim = CLevelMgr::GetInst()->GetCurLevelMon()->GetAnimator()->GetCurAnim();
		auto newoffset = curanim->GetOffset() + Vec2(1, 0);
		curanim->Setoffset(newoffset);
		wstring log = std::to_wstring(ainum) + L":"
			+ L"(" + std::to_wstring((int)newoffset.x) + L","
			+ std::to_wstring((int)newoffset.y) + L")";

		LOG(LOG_LEVEL::LOG, log.c_str());
	}
	if (KEY_TAP(U))
	{
		auto ai = CLevelMgr::GetInst()->GetCurLevelMon()->GetAI();
		auto ainum = ai->GetCurStateNum();

		auto curanim = CLevelMgr::GetInst()->GetCurLevelMon()->GetAnimator()->GetCurAnim();
		auto newoffset = curanim->GetOffset() + Vec2(0, -1);
		curanim->Setoffset(newoffset);
		wstring log = std::to_wstring(ainum) + L":"
			+ L"(" + std::to_wstring((int)newoffset.x) + L","
			+ std::to_wstring((int)newoffset.y) + L")";

		LOG(LOG_LEVEL::LOG, log.c_str());
	}
	if (KEY_TAP(J))
	{
		auto ai = CLevelMgr::GetInst()->GetCurLevelMon()->GetAI();
		auto ainum = ai->GetCurStateNum();

		auto curanim = CLevelMgr::GetInst()->GetCurLevelMon()->GetAnimator()->GetCurAnim();
		auto newoffset = curanim->GetOffset() + Vec2(0, 1);
		curanim->Setoffset(newoffset);
		wstring log = std::to_wstring(ainum) + L":"
			+ L"(" + std::to_wstring((int)newoffset.x) + L","
			+ std::to_wstring((int)newoffset.y) + L")";

		LOG(LOG_LEVEL::LOG, log.c_str());
	}


	// 마우스 포지션
	Vec2 mouspos = CKeyMgr::GetInst()->GetMousePos();
	Vec2 realmous = CCamera::GetInst()->GetRealPos(mouspos);
	int x = (int)realmous.x;
	int y = (int)realmous.y;

	wstring tmousepos = L"x:" + std::to_wstring(x)
		+ L"y:" + std::to_wstring(y);


	CLogMgr::GetInst()->AddCustomLog(tmousepos, mouspos + Vec2(0.f, -20.f));


	// 플레이어 포지션 
	x = (int)GetPlayer()->GetPos().x;
	y = (int)GetPlayer()->GetPos().y;

	wstring tplayerpos = L"player x:" + std::to_wstring(x)
		+ L"y:" + std::to_wstring(y);

	CLogMgr::GetInst()->AddCustomLog(tplayerpos, Vec2(1366.f, 0.f));

}

void CLevel::render(HDC _dc)
{
	//for (size_t i = 0; i < m_vecObjects.size(); ++i)
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->render(_dc);
	}
}


void CLevel::AddObject(LAYER _LayerType, CObj* _Object)
{
	// 레이어에 오브젝트를 집어넣는다.
	m_Layer[_LayerType]->AddObject(_Object);
	// 레이어 인덱스값을 오브젝트에 세팅해준다(오브젝트가 자신이 소속된 레이어 인덱스를 알게 한다)
	_Object->m_iLayerIdx = _LayerType;
}

//level->exit때만(게임실행중) 호출 이관3
void CLevel::DeleteAllObjects()
{
	CMonsterMgr::GetInst()->DeActivateAllMonsters();
	CUIMgr::GetInst()->SetInvisibleAllUI();
	CSkillMgr::GetInst()->DeActivateAllSkills();
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->DeleteAllObjects();
	}
}

void CLevel::DeleteObjectsByLayer(LAYER _Layer)
{
	m_Layer[_Layer]->DeleteAllObjects();
}


void CLevel::CreateTile(UINT _Row, UINT _Col)
{
	DeleteObjectsByLayer(LAYER::TILE);

	m_TileRow = _Row;
	m_TileCol = _Col;

	for (UINT i = 0; i < _Row; ++i)
	{
		for (UINT j = 0; j < _Col; ++j)
		{
			CTile* pTile = new CTile;

			pTile->SetPos(Vec2(TILE_SIZE * j, TILE_SIZE * i));

			AddObject(LAYER::TILE, pTile);
		}
	}
}


CObj* CLevel::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		const vector<CObj*>& vecObjects = m_Layer[i]->GetObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (vecObjects[j]->GetName() == _Name)
			{
				return vecObjects[j];
			}
		}
	}

	return nullptr;
}
