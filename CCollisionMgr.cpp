#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_LayerCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	//CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	for (UINT iRow = 0; iRow < 32; ++iRow)
	{
		for (UINT iCol = iRow; iCol < 32; ++iCol)
		{
			if (!(m_LayerCheck[iRow] & (1 << iCol)))
				continue;

			/*const vector<CObj*>& vecLeft = pCurLevel->GetObjects((LAYER)iRow);
			const vector<CObj*>& vecRight = pCurLevel->GetObjects((LAYER)iCol);*/

			CollisionBtwLayer((LAYER)iRow, (LAYER)iCol);
			//const vector<CCollider*>& vecLeft = pCurLevel->GetLayer((LAYER)iRow)->GetColliders();
			//const vector<CCollider*>& vecRight = pCurLevel->GetLayer((LAYER)iCol)->GetColliders();

		}
	}
}

void CCollisionMgr::CheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0, col = 0;

	if (_Left < _Right)
	{
		row = _Left;
		col = _Right;
	}
	else
	{
		col = _Left;
		row = _Right;
	}

	m_LayerCheck[row] |= (1 << col);
}

void CCollisionMgr::UncheckCollision(LAYER _Left, LAYER _Right)
{
	int row = 0, col = 0;

	if (_Left < _Right)
	{
		row = _Left;
		col = _Right;
	}
	else
	{
		col = _Left;
		row = _Right;
	}

	m_LayerCheck[row] &= ~(1 << col);
}

void CCollisionMgr::init()
{
	CheckCollision(PLATFORM, PLAYER);
	CheckCollision(PLATFORM, MONSTER);
	CheckCollision(PLATFORM, MONSTER_PJ);
	CheckCollision(PLATFORM, FALL_OBJ);

	CheckCollision(PLATFORM_DEBUG, PLAYER);

	CheckCollision(WALL, PLAYER);
	CheckCollision(WALL, MONSTER);
	CheckCollision(WALL, MONSTER_PJ);

	CheckCollision(MONSTER, PLAYER);
	CheckCollision(MONSTER, PLAYER_PJ);

	CheckCollision(PLAYER, PLAYER_SKILL);
	CheckCollision(PLAYER, MONSTER_PJ);
	CheckCollision(PLAYER, PORTAL);
	CheckCollision(PLAYER, FALL_OBJ);

}


void CCollisionMgr::CollisionBtwLayer(LAYER _Left, LAYER _Right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();

	if (nullptr == pCurLevel)
		return;


	const vector<CCollider*>& vecLeft = pCurLevel->GetLayer(_Left)->GetColliders();
	const vector<CCollider*>& vecRight = pCurLevel->GetLayer(_Right)->GetColliders();


	// 서로 다른 레이어끼리 충돌 검사
	if (true)//_Left != _Right)
	{

		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				if (vecLeft[i]->GetID() == vecRight[j]->GetID())
					continue;
				COLLIDER_ID ID(vecLeft[i]->GetID(), vecRight[j]->GetID());

				map<COLLIDER_ID, bool>::iterator iter = m_mapID.find(ID);

				if (iter == m_mapID.end())
				{
					m_mapID.insert(make_pair(ID, false));
					iter = m_mapID.find(ID);
				}


				// 현재 충돌 중이다.
				if (IsCollision(vecLeft[i], vecRight[j]))
				{
					if (false == iter->second)
					{
						// 이전에 충돌한 적이 없다.
						//vecLeft[i]->BeginOverlap(vecRight[j]);
						//vecRight[j]->BeginOverlap(vecLeft[i]);
					//}
					// 둘다 Dead 상태가 아니라면
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							// 이전에 충돌한 적이 없다.
							vecLeft[i]->BeginOverlap(vecRight[j]);
							vecRight[j]->BeginOverlap(vecLeft[i]);
						}
						iter->second = true;
					}
					else
					{
						// 이전에도 충돌 중이었다.
						//vecLeft[i]->Overlap(vecRight[j]);
						//vecRight[j]->Overlap(vecLeft[i]);
						// 둘 중 하나 이상 Dead 상태
						if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
						{
							vecLeft[i]->EndOverlap(vecRight[j]);
							vecRight[j]->EndOverlap(vecLeft[i]);
							iter->second = false;
						}
						else
						{
							vecLeft[i]->Overlap(vecRight[j]);
							vecRight[j]->Overlap(vecLeft[i]);
							iter->second = true;
						}
					}
					//iter->second = true;
				}

				// 현재 충돌하지 않고 있다.
				else
				{
					if (iter->second)
					{
						// 이전에는 충돌하고 있었다.
						vecLeft[i]->EndOverlap(vecRight[j]);
						vecRight[j]->EndOverlap(vecLeft[i]);
					}
					iter->second = false;



				}
			}
		}
	}

	// 같은 레이어 내에서 충돌 검사
	else
	{

	}
}

//true : 임의의 축으로 분리되어 있음(충돌확실히 안함)
//false : 다른곳에서 충돌 할 수 도 있음.(4번비교필요)
bool CheckDivided(const Vec2& _AtoB, const Vec2& _Vertical , CCollider* _Left, CCollider* _Right)
{
	// 축 기준 내적 거리
	float fDistance = abs(VecDot(_Vertical,_AtoB));

	// Box 1
	Vec2 vLColScale = _Left->GetScale();

	// Box 2
	Vec2 vRColScale = _Right->GetScale();

	Vec2 vLColUp = RotateDot(Vec2(0.f, 1.f) , _Left->GetOwner()->GetRotation());
	Vec2 vLColRight = RotateDot(Vec2(1.f, 0.f) , _Left->GetOwner()->GetRotation());

	Vec2 vRColUp = RotateDot(Vec2(0.f, 1.f) , _Right->GetOwner()->GetRotation());
	Vec2 vRColRight = RotateDot(Vec2(1.f, 0.f) , _Right->GetOwner()->GetRotation());

	if (fDistance > abs(VecDot(_Vertical,(vLColUp * vLColScale.y / 2.f)))
		+ abs(VecDot(_Vertical, (vLColRight * vLColScale.x / 2.f)))
		+ abs(VecDot(_Vertical, (vRColUp * vRColScale.y / 2.f)))
		+ abs(VecDot(_Vertical, (vRColRight * vRColScale.x / 2.f))))
	{
		return true;
	}

	return false;
}


bool CCollisionMgr::IsCollision(CCollider* _Left, CCollider* _Right)
{
	float LeftRot = _Left->GetOwner()->GetRotation();
	float RightRot = _Right->GetOwner()->GetRotation();

	//양쪽 컬라이더가 회전이 없으면 일반 충돌 처리
	if (0.f == LeftRot &&
		0.f == RightRot)
	{
		if (fabs(_Left->GetScale().x / 2.f + _Right->GetScale().x / 2.f) >= fabs(_Left->GetPos().x - _Right->GetPos().x)
			&& fabs(_Left->GetScale().y / 2.f + _Right->GetScale().y / 2.f) >= fabs(_Left->GetPos().y - _Right->GetPos().y))
		{
			return true;
		}
	}
	//하나라도 충돌이 있다면 OBB충돌처리
	else
	{
		Vec2 vLColUp = RotateDot(Vec2(0.f, 1.f), _Left->GetOwner()->GetRotation());
		Vec2 vLColRight = RotateDot(Vec2(1.f, 0.f), _Left->GetOwner()->GetRotation());

		Vec2 vRColUp = RotateDot(Vec2(0.f, 1.f), _Right->GetOwner()->GetRotation());
		Vec2 vRColRight = RotateDot(Vec2(1.f, 0.f), _Right->GetOwner()->GetRotation());

		Vec2 vNorVec = _Left->GetPos() - _Right->GetPos();

		// 모든 법선벡터를 한번씩 축으로 검사 진행
		if (CheckDivided(vNorVec, vLColUp, _Left, _Right))
			return false;
		if (CheckDivided(vNorVec, vLColRight, _Left, _Right))
			return false;
		if (CheckDivided(vNorVec, vRColUp, _Left, _Right))
			return false;
		if (CheckDivided(vNorVec, vRColRight, _Left, _Right))
			return false;

		return true;
	}
	return false;
}
