#include "pch.h"
#include "QuickSlotUI.h"

#include "CSkill.h"
#include "CSkillMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"
#include "CLogMgr.h"
#include "CLevelMgr.h"
#include "CPlayer.h"
#include "CEngine.h"
#include "CTimeManager.h"





QuickSlotUI::QuickSlotUI()
	:backtex(nullptr)
	, col(0)
	, row(2)
{
	m_uiname = L"QuickSlotUI";

	CAssetMgr* asmgr = CAssetMgr::GetInst();
	CSkillMgr* skmgr = CSkillMgr::GetInst();
	auto res = CEngine::GetInst()->GetResolution();

	backtex = asmgr->LoadTexture(m_uiname + L"Back", L"texture\\quickslot\\100_200.png");

	wstring icon = L"_icon";
	wstring grayicon = L"_grayicon";
	wstring shortcuticon = L"_shortcut_icon";


	// ��ũ : ' 
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonpinkbeanphantomblow"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"blink" + icon, L"texture\\quickslot\\icon\\151001004.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"blink" + grayicon, L"texture\\quickslot\\icon\\151001004.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"`" + shortcuticon, L"texture\\quickslot\\shortcuticon\\`.png"));

	// �Ŀ������� : ctrl 
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonpinkbeanphantomblow"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"powerelixir" + icon, L"texture\\quickslot\\icon\\02000019.info.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"powerelixir" + grayicon, L"texture\\quickslot\\icon\\02000019.info.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"ctrl" + shortcuticon, L"texture\\quickslot\\shortcuticon\\ctrl.png"));

	// �罽���� : 4 
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonpinkbeanphantomblow"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"chainhell" + icon, L"texture\\quickslot\\icon\\4331006.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"chainhell" + grayicon, L"texture\\quickslot\\icon\\4331006.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"4" + shortcuticon, L"texture\\quickslot\\shortcuticon\\4.png"));

	// ��ũ����Ʈ : R
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonpinkbeanphantomblow"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"darksite" + icon, L"texture\\quickslot\\icon\\4001003.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"darksite" + grayicon, L"texture\\quickslot\\icon\\4001003.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"R" + shortcuticon, L"texture\\quickslot\\shortcuticon\\r.png"));

	// ���������� : f3
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonreadytodieuse"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"readytodie" + icon, L"texture\\quickslot\\icon\\400041032.icon2.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"readytodie" + grayicon, L"texture\\quickslot\\icon\\400041032.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"F3" + shortcuticon, L"texture\\quickslot\\shortcuticon\\f3.png"));

	// ���̵� ����̵� : G
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonbladetornadouse"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"bladetornado" + icon, L"texture\\quickslot\\icon\\400041042.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"bladetornado" + grayicon, L"texture\\quickslot\\icon\\400041042.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"G" + shortcuticon, L"texture\\quickslot\\shortcuticon\\g.png"));

	// ���������� : f4
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonsoulcontractuse"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"soulcontract" + icon, L"texture\\quickslot\\icon\\60011219.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"soulcontract" + grayicon, L"texture\\quickslot\\icon\\60011219.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"F4" + shortcuticon, L"texture\\quickslot\\shortcuticon\\f4.png"));

	// ī����ǻ�� : E
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonkarmafuryuse"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"karmafury" + icon, L"texture\\quickslot\\icon\\400041021.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"karmafury" + grayicon, L"texture\\quickslot\\icon\\400041021.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"E" + shortcuticon, L"texture\\quickslot\\shortcuticon\\e.png"));


	// �����ٳ�� : f5
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonerdanovause"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"erdanova" + icon, L"texture\\quickslot\\icon\\400001008.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"erdanova" + grayicon, L"texture\\quickslot\\icon\\400001008.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"f5" + shortcuticon, L"texture\\quickslot\\shortcuticon\\f5.png"));

	// ���̵� ���� : F
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonbladestormuse"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"bladestorm" + icon, L"texture\\quickslot\\icon\\400040006.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"bladestorm" + grayicon, L"texture\\quickslot\\icon\\400040006.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"F" + shortcuticon, L"texture\\quickslot\\shortcuticon\\f.png"));

	// ī���� ���̵� : Home
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonpinkbeanphantomblow"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"karmablade" + icon, L"texture\\quickslot\\icon\\4361500.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"karmablade" + grayicon, L"texture\\quickslot\\icon\\4361500.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"home" + shortcuticon, L"texture\\quickslot\\shortcuticon\\hm.png"));

	// ����Ʈ����Ʈ�� : pdn
	m_VecSkill.push_back(skmgr->FindAvailableSkill(L"commonrestraintringroop"));
	m_VecIcon.push_back(asmgr->LoadTexture(L"restraintring" + icon, L"texture\\quickslot\\icon\\80001455.icon.png"));
	m_VecGrayIcon.push_back(asmgr->LoadTexture(L"restraintring" + grayicon, L"texture\\quickslot\\icon\\80001455.iconDisabled.png"));
	m_VecShortCutKey.push_back(asmgr->LoadTexture(L"pdn" + shortcuticon, L"texture\\quickslot\\shortcuticon\\pdn.png"));

	for (int i = 0; i < 10; i++)
	{
		m_VecCoolDownNum.push_back(
			asmgr->LoadTexture(L"CooltimeNumber" + std::to_wstring(i), L"texture\\quickslot\\SkillCooldownNumber.2.frames\\" + std::to_wstring(i) + L".png")
		);
	}

	for (int i = 0; i < 4; i++)
	{
		m_VecCoolAlertTex.push_back(
			asmgr->LoadTexture(L"CoolAlertTex" + std::to_wstring(i), L"texture\\quickslot\\CooltimeEndAlarmInventory.effect.frames\\" + std::to_wstring(i) + L".png")
		);
	}
	mag = 0.8f;

	tilesize = Vec2(68, 64) * mag;
	col = (int)ceil((float)m_VecSkill.size() / (float)row);
	SetScale(Vec2(tilesize.x * col, tilesize.y * row));
	SetPos(Vec2(res.x - GetScale().x
		, res.y
		//����ġ��
		- 10.f
		- GetScale().y));
}



void QuickSlotUI::tick(float _DT)
{
	int i = 0;
	for (auto pSkill : m_VecSkill)
	{
		//���� ��Ÿ���� 0�� �ƴѰͿ��� �۾�
		float& tcool = pSkill->m_leftcool;
		if (0.f != tcool)
		{
			//������Ÿ���� ���ش�.
			tcool -= _DT;
			if (tcool <= 0.f)
			{
				//0���ϰ��Ǹ� 0���� �����ϰ� �˸����
				tcool = 0.f;
				SetAlert(m_VecIcon[i]);
			}
		}
		++i;
	}
}

void QuickSlotUI::render(HDC _dc)
{
	Vec2 renderpos = GetPos();
	for (int i = 0; i < col * row; ++i)
	{
		int c = i / 2;
		int r = i % 2;
		//��
		SettexturetoDcWithMagnification(_dc, backtex, renderpos + Vec2(tilesize.x * c, tilesize.y * r), mag);

		//�׷��� ������ ������ ����
		SettexturetoDc(_dc, m_VecGrayIcon[i], renderpos + Vec2(tilesize.x * c, tilesize.y * r) + Vec2(5, 4));

		if (0.f == m_VecSkill[i]->m_leftcool)
		{
			SettexturetoDc(_dc, m_VecIcon[i], renderpos + Vec2(tilesize.x * c, tilesize.y * r) + Vec2(5, 4));
		}
		else
		{
			//��ų������ ������Ÿ�� % ����ϱ�
			float perc = 1 - m_VecSkill[i]->m_leftcool / m_VecSkill[i]->cooltime;
			SettexturetoDcPartiallyDown(_dc, m_VecIcon[i], renderpos + Vec2(tilesize.x * c, tilesize.y * r) + Vec2(5, 4), perc);


			//���� ��Ÿ�� ���� ����ϱ�
			int digit = (int)std::to_wstring((int)m_VecSkill[i]->m_leftcool).size();
			int digitoffset = 0;
			switch (digit)
			{
			case 1:
				digitoffset = 10;
				break;
			case 2:
				digitoffset = 5;
				break;
			}
			SetNumberTextureToDc(_dc, (int)m_VecSkill[i]->m_leftcool, m_VecCoolDownNum, renderpos + Vec2(tilesize.x * c, tilesize.y * r) + Vec2(11, 17) + Vec2(digitoffset, 0));
		}

		//��Ʈ��Ű
		SettexturetoDcWithMagnification(_dc, m_VecShortCutKey[i], renderpos + Vec2(tilesize.x * c, tilesize.y * r) + Vec2(8, 8), 0.8f * mag);
	}

	//��Ÿ�� �˸��� ó��

	if (m_AlertList.empty())
	{
		return;
	}

	// �˶��� �����Ѵٸ�
	auto iter = m_AlertList.begin();

	int i = 0;
	while (m_AlertList.end() != iter)
	{
		if (false == (*iter).isstarted)
		{
			CAssetMgr::GetInst()->LoadSound(L"cooldownend", L"sound\\CooldownEndAlarm.wav")->Play();
			(*iter).isstarted = true;
		}
		//�����ð��� ���ӽð��� �Ѿ�� ����
		(*iter).acctime += DT;
		if ((*iter).duration <= (*iter).acctime)
		{
			iter = m_AlertList.erase(iter);
			continue;
		}
		//���ӽð��� ���� ������ ����
		else
		{
			float& acc = (*iter).acctime;
			if (.9f < acc) { AlertRender1(_dc, Vec2(1180, 598 - 56 * i), 3); }
			else if (.9f >= acc
				&& 0.18f <= acc) {
				AlertRender2(_dc, Vec2(1180, 598 - 56 * i), (*iter).tex);
			}
			else if (0.18f > acc
				&& 0.09f < acc) {
				AlertRender1(_dc, Vec2(1180, 598 - 56 * i), 1);
			}
			else { AlertRender1(_dc, Vec2(1180, 598 - 56 * i), 0); }
			iter++;
			++i;
		}
	}
}


void QuickSlotUI::AlertRender1(HDC _dc, Vec2 _pos, int _num)
{
	SettexturetoDc(_dc, m_VecCoolAlertTex[_num], _pos);
	int i = 0;
}

void QuickSlotUI::AlertRender2(HDC _dc, Vec2 _pos, CTexture* _icon)
{
	SettexturetoDc(_dc, m_VecCoolAlertTex[2], _pos);
	SettexturetoDcWithMagnification(_dc, _icon, _pos + Vec2(11, 11), mag);
	int i = 0;
}



bool QuickSlotUI::IsCoolTime(wstring _skillname)
{
	for (auto pSkill : m_VecSkill)
	{
		if (_skillname == pSkill->m_skillname)
		{
			if (0.f == pSkill->m_leftcool)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

void QuickSlotUI::SetAlert(CTexture* _pTex)
{
	FCoolAlert CA = {};

	CA.isstarted = false;
	CA.duration = .99f;
	CA.acctime = 0.f;
	CA.tex = _pTex;

	m_AlertList.push_front(CA);
}

QuickSlotUI::~QuickSlotUI()
{

}