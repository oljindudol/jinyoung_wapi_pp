#include "pch.h"

#include "CSkill.h"
#include "CSkillMgr.h"
#include "skills.h"
#include "CTimeManager.h"
#include "CEngine.h"
#include "CLogMgr.h"
#include "CUIMgr.h"
#include "QuickSlotUI.h"

CSkillMgr::CSkillMgr()
{
}

void CSkillMgr::init()
{
	AddSkill((CSkill*)new pinkbean_doublejump);
	AddSkill((CSkill*)new pinkbean_doublejump);
	AddSkill((CSkill*)new pinkbean_phantomblow);

	for (int i = 0; i < 5; i++)
	{
		AddSkill((CSkill*)new ChainAttack);
	}

	for (int i = 0; i < 10; i++)
	{
		AddSkill((CSkill*)new CDamageSkin);
	}

	//뎀스만들기
	for (int i = 0; i < 500; i++)
	{
		AddSkill((CSkill*)new CDamageSkinRed);
	}

	for (int i = 0; i < 80; i++)
	{
		AddSkillEff(new CSkill
			, L"common", L"pinkbean", L"phantomblow_hit"
			, .48f, Vec2(0.f, 0.f));
	}

	for (int i = 0; i < 50; ++i)
	{
		m_VecEffPlayer.push_back(new CEffPlayer);
	}

	for (int i = 0; i < 2; i++)
	{
		AddSkillEff(new CSkill
			, L"common", L"pinkbean", L"upperjump"
			, .72f, Vec2(0.f, 0.f));
	}

	AddSkill(new CRestraintRing);

	AddSkillEff(new CSkill
		, L"common", L"restraintring", L"eff"
		, .9f, Vec2(0.f, -40.f));


	AddSkill(new CErdaNova);
	AddSkill(new CKarmaFury);
	AddSkill(new CBladeTornado);
	AddSkill(new CBladeStorm);

	//레투다
	AddSkillEff(new CSkill
		, L"common", L"readytodie", L"use"
		, .9f, Vec2(0.f, -150.f));

	FindAvailableSkill(L"commonreadytodieuse")->cooltime = 60.f;

	//엔버링크
	AddSkillEff(new CSkill
		, L"common", L"soulcontract", L"use"
		, .9f, Vec2(0.f, -40.f));
	FindAvailableSkill(L"commonsoulcontractuse")->cooltime = 50.f;


	for (int i = 0; i < 15; i++)
	{
		AddSkill(new CUnderDog);
	}

	AddSkill(new CEyeofRuin_L);
	AddSkill(new CEyeofRuin_R);

	for (int i = 0; i < 5; i++)
	{
		AddSkillEff(new CSkill
			, L"first", L"chainattack", L"hit"
			, .84f, Vec2(0.f, -300.f));
	}

	for (int i = 0; i < 5; i++)
	{
		AddSkillEff(new CSkill
			, L"second", L"eyeofruin", L"hit"
			, .72f, Vec2(0.f, 0.f));
	}

	AddSkill(new CSecondPowerLeft);
	AddSkill(new CSecondPowerRight);
	AddSkill(new CSecondPowerMiddle);



	for (int i = 0; i < 7; i++)
	{
		AddSkill(new CNoxSpear);
	}
	for (int i = 0; i < 5; i++)
	{
		AddSkillEff(new CSkill
			, L"second", L"noxspear", L"hit"
			, .7f, Vec2(0.f, 0.f));
	}

	AddSkill(new CBlindness);
	AddSkill(new CAchievement);
	AddSkill(new CEndroll);

	for (int i = 0; i < 5; i++)
	{
		AddSkill(new CMouseCol);
	}


	AddSkillEff(new CSkill
		, L"zero", L"levelup", L"use"
		, 2.3f, Vec2(0.f, 0.f));

	for (int i = 0; i < 5; ++i)
	{
		AddSkillEff(new CSkill
			, L"common", L"debuff", L"deathbycurse"
			, 0.9f, Vec2(0.f, 0.f), -1, ERenderType::OnCamera);
	}
}


void CSkillMgr::AddSkillEff(CSkill* _pSkill
	, wstring _s1, wstring _s2, wstring _s3
	, float _duration, Vec2 _offset, int _roop, ERenderType _RenderType)
{
	_pSkill->m_s1 = _s1;
	_pSkill->m_s2 = _s2;
	_pSkill->m_s3 = _s3;

	_pSkill->m_skillname =
		_pSkill->m_s1
		+ _pSkill->m_s2
		+ _pSkill->m_s3;

	//몇번째 스킬인지
	_pSkill->m_skillnum = FindNextSkillNumber(_pSkill->m_skillname);

	_pSkill->SetName(_pSkill->m_skillname + L"_" + std::to_wstring(_pSkill->m_skillnum));

	//애니메이션
	_pSkill->m_Animator =
		_pSkill->AddComponent<CAnimator>(_pSkill->GetName() + L"Animator");

	_pSkill->m_Animator->SetRenderType(_RenderType);

	_pSkill->m_Animator->
		CreateAnimation(_pSkill->m_s1, _pSkill->m_s2, _pSkill->m_s3,
			_offset, 1.f, _roop, ORT_LEFT);

	_pSkill->m_Animator->Play(_pSkill->m_s1 + _pSkill->m_s2 + _pSkill->m_s3);

	_pSkill->m_skilllayer = LAYER::PLAYER_SKILL;
	_pSkill->duration = _duration;


	vector<CSkill*>* pSkills;
	wstring skillname = _pSkill->m_skillname;
	pSkills = FindSkill(skillname);

	//없는지 확인하는게 당연한처리기 때문에 못찾아도 로그를 내지않는다.
	if (nullptr == pSkills)
	{
		vector<CSkill*> newskillvec;
		newskillvec.push_back(_pSkill);
		m_skillmap.insert(pair<wstring, vector<CSkill*>>(skillname, newskillvec));
	}
	else
	{
		pSkills->push_back(_pSkill);
	}
}

void CSkillMgr::AddSkill(CSkill* _pSkill)
{
	vector<CSkill*>* pSkills;
	wstring skillname = _pSkill->m_skillname;
	pSkills = FindSkill(skillname);

	//없는지 확인하는게 당연한처리기 때문에 못찾아도 로그를 내지않는다.
	if (nullptr == pSkills)
	{
		vector<CSkill*> newskillvec;
		newskillvec.push_back(_pSkill);
		m_skillmap.insert(pair<wstring, vector<CSkill*>>(skillname, newskillvec));
	}
	else
	{
		pSkills->push_back(_pSkill);
	}
}

CSkillMgr::~CSkillMgr()
{
	for (const auto& pair : m_skillmap)
	{
		for (const auto& p : pair.second)
		{
			delete p;
		}
	}

	for (auto ep : m_VecEffPlayer)
	{
		delete ep;
	}
}

void CSkillMgr::DeActivateAllSkills()
{
	for (const auto& pair : m_skillmap)
	{
		for (const auto& p : pair.second)
		{
			p->m_OnActivate = false;
		}
	}
}

void CSkillMgr::DeActivateSkill(CSkill* _skill)
{
	if (nullptr != _skill) { _skill->m_OnActivate = false; }
}

int CSkillMgr::FindNextSkillNumber(wstring _skillname)
{
	auto iter = m_skillmap.find(_skillname);
	if (m_skillmap.end() == iter)
	{
		return 0;
	}

	return (int)iter->second.size();

}


vector<CSkill*>* CSkillMgr::FindSkill(wstring _skillname)
{
	auto iter = m_skillmap.find(_skillname);

	if (iter == m_skillmap.end())
	{
		return nullptr;
	}
	return &(iter->second);
}


//bool CSkillMgr::IsActive(wstring _aname1, wstring _aname2, wstring _aname3)
//{
//	vector<CSkill*>* pskills = FindSkill(_aname1, _aname2, _aname3);
//	if (nullptr == pskills)
//	{
//		//없는스킬 로그 띄우기
//		return true;
//	}
//	return pskills->m_OnActivate;
//}

CSkill* CSkillMgr::FindAvailableSkill(wstring _skillname)
{
	CSkill* pSkill = nullptr;
	vector< CSkill* >* pSkills = FindSkill(_skillname);

	if (nullptr == pSkills)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다"));
		pSkill = nullptr;
	}
	else
	{
		for (auto p : (*pSkills))
		{
			if (false == (p->m_OnActivate))
			{
				pSkill = p;
				break;
			}
		}
	}
	return pSkill;
}


void CSkillMgr::PrintDamageVioletSkin(Vec2 _pos, int _num)
{
	CSkill* pskill = FindAvailableSkill(L"commonpinkbeandamageskin_violet");
	if (nullptr == pskill)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, L"스킬을 찾을수 없습니다 commonpinkbeandamageskin_violet");
		return;
	}

	CDamageSkin* pDs = dynamic_cast<CDamageSkin*>(pskill);
	if (nullptr != pDs)
		pDs->PrintDamage(_pos, _num);

}

void CSkillMgr::PrintDamageRedSkin(Vec2 _pos, long long _num, int _th)
{
	CSkill* pskill = FindAvailableSkill(L"commonpinkbeandamageskin_red");
	if (nullptr == pskill)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, L"스킬을 찾을수 없습니다 commonpinkbeandamageskin_red");
		return;
	}

	CDamageSkinRed* pDs = dynamic_cast<CDamageSkinRed*>(pskill);
	if (nullptr != pDs)
		pDs->PrintDamage(_pos, _num, _th);
}


CSkill* CSkillMgr::ActivateSkill(wstring _skillname
	, Vec2 _pos
	, ORIENTATION _ort)
{
	CSkill* pskill = FindAvailableSkill(_skillname);
	if (nullptr == pskill)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다" + _skillname).c_str());
		return nullptr;
	}

	pskill->activate(_pos, _ort);
	return pskill;
}



bool CSkillMgr::IsCoolTime(wstring _skillname)
{
	return dynamic_cast<QuickSlotUI*>((*CUIMgr::GetInst()->FindUI(L"QuickSlotUI"))[0])->IsCoolTime(_skillname);
}




float CSkillMgr::GetSkillDuration(wstring _skillname)
{
	vector<CSkill*>* pSkills = FindSkill(_skillname);
	if (nullptr == pSkills)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, (L"스킬을 찾을수 없습니다"));
		return 0.f;
	}

	return (*pSkills)[0]->duration;
}


//void CSkillMgr::CreateSkill(
//	  Vec2 _colbox
//	, wstring _aname1
//	, wstring _aname2
//	, wstring _aname3
//	, Vec2 _animOffset 
//	, float _animPlaymul 
//	, int _roop 
//	, ORIENTATION _ort 
//	, float _duration
//	, float _cooltime 
//	, float _att 
//	, DEBUFF _debuff 
//)
//{
//	if (nullptr != FindSkill(_aname1, _aname2, _aname3))
//	{
//		//이미 있는스킬 로그 띄우기
//		return;
//	}
//
//	CSkill* pNewSkill = new CSkill;
//
//	wstring tmpstr = _aname1 + _aname2 + _aname3;
//
//	pNewSkill->m_skillname = tmpstr; 
//
//	//컬라이더
//	pNewSkill->m_Collider =
//		pNewSkill->AddComponent<CCollider>(tmpstr + L"Collider");
//	pNewSkill->m_Collider->SetScale(_colbox);
//	//pNewSkill -> m_Collider->SetOffsetPos(Vec2(0.f, 0.f));
//
//	//애니메이션
//	pNewSkill->m_Animator = 
//		pNewSkill->AddComponent<CAnimator>(tmpstr +L"Animator");
//
//	pNewSkill->m_Animator->
//		CreateAnimation(_aname1, _aname2, _aname3, 
//			_animOffset,_animPlaymul,_roop,_ort);
//
//	pNewSkill->duration = _duration;
//	pNewSkill->cooltime = _cooltime;
//	pNewSkill->m_att = _att;
//	pNewSkill->m_debuff = _debuff;
//
//
//	m_skillmap.insert(pair<wstring, CSkill*>(_aname1 + _aname2 + _aname3, pNewSkill));
//
//}
//
//
//


void CSkillMgr::tick()
{
	for (auto ep : m_VecEffPlayer)
	{
		if (ep->m_isplaying)
			ep->tick();
	}
}

void CSkillMgr::CEffPlayer::tick()
{

	if (m_EventList.empty())
	{
		m_isplaying = false;
		return;
	}

	// 이펙트 이벤트가 존재한다면
	FEffectEvent& evnt = m_EventList.front();
	if (false == evnt.activated)
	{
		evnt.pSkill->activate(evnt.vPos, evnt.ort);
		evnt.activated = true;
	}
	evnt.AccTime += DT;

	if (evnt.Duration <= evnt.AccTime)
	{
		m_EventList.pop_front();
	}
}

void CSkillMgr::CEffPlayer::SetEffEvent(CSkill* _pSkillEff, float _delay, Vec2 _pos, ORIENTATION _ort)
{
	FEffectEvent evnt = {};
	evnt.pSkill = _pSkillEff;
	evnt.AccTime = 0.f;
	evnt.Duration = _delay;
	evnt.vPos = _pos;
	evnt.activated = false;
	evnt.ort = _ort;

	m_EventList.push_back(evnt);
}

void CSkillMgr::PlayMultipleEff(wstring _key, int _cnt, float _delay, Vec2 _pos, ORIENTATION _ort)
{
	auto iter = m_VecEffPlayer.begin();
	while (m_VecEffPlayer.end() != iter)
	{
		if (false == (*iter)->m_isplaying)
			break;
		++iter;
	}

	if (m_VecEffPlayer.end() == iter)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, L"할당 가능한 이펙트 플레이어 없음")
			return;
	}

	(*iter)->m_isplaying = true;

	for (int i = 0; i < _cnt; ++i)
	{
		auto pEff = FindAvailableSkill(_key);
		//로그는 FindAvailableSkill에서처리
		if (nullptr == pEff)
			return;
		pEff->m_OnActivate = true;

		Vec2 Scale = pEff->m_Animator->GetScale();
		(*iter)->
			SetEffEvent(pEff, _delay, _pos
				+ Vec2(
					(float)(Scale.x * (0.3 * RandomPercentHtH()))
					, (float)(Scale.y * (0.2 * RandomPercentHtH()))
				)
				, _ort);
	}
}

void CSkillMgr::ActivateSkillWithDelay(wstring _key, float _delay, vector<Vec2> _pos, ORIENTATION _ort)
{
	auto iter = m_VecEffPlayer.begin();
	while (m_VecEffPlayer.end() != iter)
	{
		if (false == (*iter)->m_isplaying)
			break;
		++iter;
	}

	if (m_VecEffPlayer.end() == iter)
	{
		if (DEBUG_RENDER)
			LOG(LOG_LEVEL::LOG, L"할당 가능한 이펙트 플레이어 없음")
			return;
	}

	(*iter)->m_isplaying = true;

	for (int i = 0; i < (int)_pos.size(); ++i)
	{
		auto pEff = FindAvailableSkill(_key);
		//로그는 FindAvailableSkill에서처리
		if (nullptr == pEff)
			return;
		pEff->m_OnActivate = true;

		Vec2 Scale = pEff->m_Animator->GetScale();
		(*iter)->
			SetEffEvent(pEff, _delay, _pos[i], _ort);
	}
}
