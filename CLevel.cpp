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

class CEntity;
class CLayer;


CLevel::CLevel()
	: m_TileRow(0)
	, m_TileCol(0)
	, m_BackGround(nullptr)
	, m_BackOn(false)
	, pPlayer(nullptr)
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

	// Enter 키가 눌리면 StartLevel 로 변환
	if (KEY_TAP(KEY::_1))
	{
		float perc = (float)rand() / (float)32767;


		CMonsterMgr::GetInst()->SpwanMonster(L"firstion", Vec2((1600.f * perc), 200.f));
	}


	//디버그 로그
	if (!DEBUG_RENDER)
		return;

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

//level->exit때만(게임실행중) 호출
void CLevel::DeleteAllObjects()
{
	CSkillMgr::GetInst()->DeActivateAllSkills();
	//CSkillMgr::GetInst()->DeActivatedAllMonster();
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
