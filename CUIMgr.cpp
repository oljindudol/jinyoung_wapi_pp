#include "pch.h"
#include "CUIMgr.h"

#include "CKeyMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CLogMgr.h"
#include "CAssetMgr.h"

#include "CPlayer.h"

#include "uis.h"

void resurr1();
void resurr2();

CUIMgr::CUIMgr()
	: m_FocuedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{
	for (const auto& pair : m_UIMap)
	{
		for (const auto& p : pair.second)
		{
			delete p;
		}
	}
}

void CUIMgr::init()
{
	AddUI(new CStatusUI);
	AddUI(new CUpperBar);

	// UI 생성
	CPanelUI* pResurr1Pan = new CPanelUI;
	pResurr1Pan->SetScale(Vec2(300.f, 131.f));
	pResurr1Pan->SetPos(Vec2((1366.f - pResurr1Pan->GetScale().x)/2.f, (868.f - pResurr1Pan->GetScale().y) / 2.f));
	pResurr1Pan->SetPannelImg(CAssetMgr::GetInst()->LoadTexture(L"ResurrPan1",L"texture\\resurrectmsg\\Notice.9.png"));
	
	CBtnUI* pResurr1Btn = new CBtnUI;
	pResurr1Btn->SetScale(Vec2(40.f, 16.f));
	pResurr1Btn->SetPos(Vec2(230.f, 100.f));
	pResurr1Btn->SetCallBack(resurr1);
	pResurr1Btn->SetNormalImg(CAssetMgr::GetInst()->LoadTexture(L"ResurrBtn1", L"texture\\resurrectmsg\\Notice.btOK.normal.0.png"));
	pResurr1Btn->SetHoverImg(CAssetMgr::GetInst()->LoadTexture(L"ResurrBtn2", L"texture\\resurrectmsg\\Notice.btOK.normal.0.png"));
	pResurr1Btn->SetPressedImg(CAssetMgr::GetInst()->LoadTexture(L"ResurrBtn3", L"texture\\resurrectmsg\\Notice.btOK.pressed.0.png"));

	pResurr1Pan->AddChildUI(pResurr1Btn);

	vector<CUI*> newresurr1vec;
	newresurr1vec.push_back(pResurr1Pan);
	m_UIMap.insert(pair<wstring, vector<CUI*>>(L"ResurrUI1", newresurr1vec));


	AddUI(new CFloatingNotice);
	AddUI(new QuickSlotUI);
	AddUI(new CStateDebugUI);

	AddUI(new CInventory);
}

void CUIMgr::FloatNotice(wstring _msg, float _duration)
{
	auto pui=FindAvailableUI(L"FloatingNoticeUI");

	if (nullptr == pui)
		return;
	
	auto fui = dynamic_cast<CFloatingNotice*>(pui);

	if (nullptr == fui)
		return;

	fui->FloatNotice(_msg, _duration);
}

void CUIMgr::SetUIVisible(wstring _uiname)
{
	CUI* pUI = FindAvailableUI(_uiname);
	if (nullptr == pUI)
	{
		LOG(LOG_LEVEL::LOG, (L"UI를 찾을수 없습니다"));
		return;
	}
	pUI->SetUIVisible();
}

void CUIMgr::SetUIVisibleSuper(wstring _uiname)
{
	CUI* pUI = FindAvailableUI(_uiname);
	if (nullptr == pUI)
	{
		LOG(LOG_LEVEL::LOG, (L"UI를 찾을수 없습니다"));
		return;
	}
	pUI->SetUIVisibleSuper();
}

void CUIMgr::SetUIOnOffResponsible(wstring _uiname)
{
	auto pp = FindUI(_uiname);

	if (nullptr == pp)
		return;
	
	if (false == (*pp)[0]->m_visible)
	{
		if(_uiname == L"statedebugui")
			(*pp)[0]->SetUIVisibleSuper();
		else
			(*pp)[0]->SetUIVisible();
	}
	else
	{
		(*pp)[0]->m_visible = false;
		(*pp)[0]->Destroy();
	}
}

void CUIMgr::DestroyUI(wstring _uiname)
{
	auto pVecUI = FindUI(_uiname);
	if (nullptr == pVecUI)
	{
		LOG(LOG_LEVEL::LOG, (L"UI를 찾을수 없습니다"));
		return;
	}

	auto pUI = (*pVecUI)[0];

	pUI->m_visible = false;
	pUI->Destroy();
}



CUI* CUIMgr::FindAvailableUI(wstring _uiname)
{
	CUI* pui = nullptr;
	vector< CUI* >* puis = FindUI(_uiname);

	if (nullptr == puis)
	{
		LOG(LOG_LEVEL::LOG, (L"UI를 찾을수 없습니다"));
		pui = nullptr;
	}
	else
	{
		for (auto p : (*puis))
		{
			if (false == (p->m_visible))
			{
				pui = p;
				break;
			}
		}
	}
	return pui;
}

vector<CUI*>* CUIMgr::FindUI(wstring _uiname)
{
	auto iter = m_UIMap.find(_uiname);

	if (iter == m_UIMap.end())
	{
		return nullptr;
	}
	return &(iter->second);
}

void CUIMgr::AddUI(CUI* _pui)
{
	vector<CUI*>* puis;
	wstring uiname = _pui->m_uiname;

	puis = FindUI(uiname);

	//없어도 괜찮기 때문에 로그를 내지않는다.
	if (nullptr == puis)
	{
		vector<CUI*> newmonsvec;
		newmonsvec.push_back(_pui);
		m_UIMap.insert(pair<wstring, vector<CUI*>>(uiname, newmonsvec));
	}
	else
	{
		puis->push_back(_pui);
	}
}

void CUIMgr::SetUIInvisible(CUI* _pui)
{
	if (nullptr != _pui) { _pui->m_visible = false; }
}

void CUIMgr::SetInvisibleAllUI()
{
	for (const auto& pair : m_UIMap)
	{
		for (const auto& p : pair.second)
		{
			p->m_visible = false;
		}
	}
}

int CUIMgr::FindNextUINumber(wstring _uiname)
{
	auto iter = m_UIMap.find(_uiname);

	if (m_UIMap.end() == iter)
	{
		return 0;
	}

	return (int)iter->second.size();
}




void CUIMgr::tick()
{
	Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
	bool bLBtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnReleased = KEY_RELEASED(KEY::LBTN);

	CLevel* pLevel = CLevelMgr::GetInst()->GetCurLevel();
	if (nullptr == pLevel)
		return;

	// UILayer 가져오기
	CLayer* pUILayer = pLevel->GetLayer(LAYER::UI);
	vector<CObj*>& vecUI = pUILayer->m_vecObjects;
	vector<CObj*>::reverse_iterator iter = vecUI.rbegin();


	for (iter; iter != vecUI.rend(); ++iter)
	{
		CUI* pUI = dynamic_cast<CUI*>(*iter);
		if (nullptr == pUI)
		{
			LOG(ERR, L"UI Layer 에 UI 가 아닌 오브젝트가 들어 있음");
			continue;
		}

		if (pUI->m_bMouseOn)
		{
			m_FocuedUI = pUI;

			pUI = GetPriorityCheck(pUI);

			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				pUI->OnHovered(vMousePos);
			}
			else
			{
				pUI->MouseOn(vMousePos);
			}

			if (bLbtnReleased)
			{
				pUI->LBtnUp(vMousePos);

				if (pUI->m_bMouseLBtnDown)
				{
					pUI->LBtnClicked(vMousePos);
				}
			}

			if (bLBtnTap)
			{
				pUI->LBtnDown(vMousePos);
				pUI->m_bMouseLBtnDown = true;

				// reverse iterator 로 vector 내에서 erase 하기
				std::advance(iter, 1);
				vecUI.erase(iter.base());

				vecUI.push_back(m_FocuedUI);
			}

			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}

			break;
		}
		else
		{
			if (pUI->m_bMouseOn_Prev != pUI->m_bMouseOn)
			{
				pUI->OnUnHovered(vMousePos);
			}

			if (bLbtnReleased)
			{
				pUI->m_bMouseLBtnDown = false;
			}
		}
	}
}

CUI* CUIMgr::GetPriorityCheck(CUI* _ParentUI)
{
	CUI* pPriorityUI = nullptr;

	static list<CUI*> queue;
	queue.clear();

	queue.push_back(_ParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}

		if (pUI->m_bMouseOn)
		{
			pPriorityUI = pUI;
		}
	}

	return pPriorityUI;
}

void resurr1()
{
	CUIMgr::GetInst()->DestroyUI(L"ResurrUI1");
	CPlayer* cp = CLevelMgr::GetInst()->GetPlayer();
	
	cp->getStateMachine()->ChangeState((UINT)PLAYER_STATE::IDLE);


	cp->m_invincible_time = 5.f;

	cp->hp = cp->maxhp;
	cp->mp = cp->maxmp;
}

void resurr2()
{
	CUIMgr::GetInst()->DestroyUI(L"ResurrUI1");
	CPlayer* cp = CLevelMgr::GetInst()->GetPlayer();

	cp->getStateMachine()->ChangeState((UINT)PLAYER_STATE::IDLE);

	cp->hp = cp->maxhp;
	cp->mp = cp->maxmp;

	cp->m_invincible_time = 5.f;

	ChangeLevel(LEVEL_TYPE::PHASE_ZERO);
}
