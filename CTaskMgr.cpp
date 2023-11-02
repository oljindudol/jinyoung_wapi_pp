#include "pch.h"
#include "CTaskMgr.h"


#include "CLevelMgr.h"
#include "CLevel.h"
#include "CObj.h"
#include "CComponent.h"

CTaskMgr::CTaskMgr()
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::tick()
{
	for (size_t i = 0; i < m_vecTask.size(); ++i)
	{
		switch (m_vecTask[i].Type)
		{
		case CREATE_OBJECT:
		{
			LAYER layertype = (LAYER)m_vecTask[i].Param_1;
			CObj* Object = (CObj*)m_vecTask[i].Param_2;

			CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
			pCurLevel->AddObject(layertype, Object);
			Object->begin();
		}
		break;
		case EXPEL_OBJECT:
		{
			CObj* pObj = (CObj*)m_vecTask[i].Param_1;
			LAYER objLayer= (LAYER) pObj->GetLayerIdx();

			CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer((UINT_PTR)objLayer);
			vector<CObj*>& objs = pLayer->m_vecObjects;
			auto iter = objs.begin();

			while (iter != objs.end())
			{
				if (pObj == (*iter))
				{
					(*iter)->m_iLayerIdx = -1;
					(*iter)->SetDead();

					iter = objs.erase(iter);
					break;
				}
				++iter;
			}
		}
		break;
		case DELETE_OBJECT:
		{
			CObj* pDeadObj = (CObj*)m_vecTask[i].Param_1;

			//pDeadObj->m_bDead = true;
			pDeadObj->SetDead();
		}
			break;
		case LEVEL_CHANGE:
			{
			LEVEL_TYPE type = (LEVEL_TYPE)m_vecTask[i].Param_1;
			CLevelMgr::GetInst()->ChangeLevel(type);
			}
			break;
		}
	}

	m_vecTask.clear();
}