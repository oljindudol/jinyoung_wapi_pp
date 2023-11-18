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


	// ���� �ٸ� ���̾�� �浹 �˻�
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


				// ���� �浹 ���̴�.
				if (IsCollision(vecLeft[i], vecRight[j]))
				{
					if (false == iter->second)
					{
						// ������ �浹�� ���� ����.
						//vecLeft[i]->BeginOverlap(vecRight[j]);
						//vecRight[j]->BeginOverlap(vecLeft[i]);
					//}
					// �Ѵ� Dead ���°� �ƴ϶��
						if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
						{
							// ������ �浹�� ���� ����.
							vecLeft[i]->BeginOverlap(vecRight[j]);
							vecRight[j]->BeginOverlap(vecLeft[i]);
						}
						iter->second = true;
					}
					else
					{
						// �������� �浹 ���̾���.
						//vecLeft[i]->Overlap(vecRight[j]);
						//vecRight[j]->Overlap(vecLeft[i]);
						// �� �� �ϳ� �̻� Dead ����
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

				// ���� �浹���� �ʰ� �ִ�.
				else
				{
					if (iter->second)
					{
						// �������� �浹�ϰ� �־���.
						vecLeft[i]->EndOverlap(vecRight[j]);
						vecRight[j]->EndOverlap(vecLeft[i]);
					}
					iter->second = false;



				}
			}
		}
	}

	// ���� ���̾� ������ �浹 �˻�
	else
	{

	}
}

//true : ������ ������ �и��Ǿ� ����(�浹Ȯ���� ����)
//false : �ٸ������� �浹 �� �� �� ����.(4�����ʿ�)
bool CheckDivided(const Vec2& _AtoB, const Vec2& _Vertical , CCollider* _Left, CCollider* _Right)
{
	// �� ���� ���� �Ÿ�
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

	//���� �ö��̴��� ȸ���� ������ �Ϲ� �浹 ó��
	if (0.f == LeftRot &&
		0.f == RightRot)
	{
		if (fabs(_Left->GetScale().x / 2.f + _Right->GetScale().x / 2.f) >= fabs(_Left->GetPos().x - _Right->GetPos().x)
			&& fabs(_Left->GetScale().y / 2.f + _Right->GetScale().y / 2.f) >= fabs(_Left->GetPos().y - _Right->GetPos().y))
		{
			return true;
		}
	}
	//�ϳ��� �浹�� �ִٸ� OBB�浹ó��
	else
	{
		Vec2 vLColUp = RotateDot(Vec2(0.f, 1.f), _Left->GetOwner()->GetRotation());
		Vec2 vLColRight = RotateDot(Vec2(1.f, 0.f), _Left->GetOwner()->GetRotation());

		Vec2 vRColUp = RotateDot(Vec2(0.f, 1.f), _Right->GetOwner()->GetRotation());
		Vec2 vRColRight = RotateDot(Vec2(1.f, 0.f), _Right->GetOwner()->GetRotation());

		Vec2 vNorVec = _Left->GetPos() - _Right->GetPos();

		// ��� �������͸� �ѹ��� ������ �˻� ����
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
