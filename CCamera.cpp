#include "pch.h"
#include "CCamera.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeManager.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CLevelMgr.h";
#include "CPlayer.h"


CCamera::CCamera()
	: m_Veil(nullptr)
	, m_Alpha(0.f)
{
	Vec2 vResol = CEngine::GetInst()->GetResolution();
	m_Veil = CAssetMgr::GetInst()->CreateTexture(L"VeilTex", vResol.x, vResol.y);
}

CCamera::~CCamera()
{
}

void CCamera::tick()
{
	// ����Ű�� ī�޶� �ٶ󺸰� �ִ� ��ġ�� ����
	if (KEY_PRESSED(KEY::J))
	{
		m_vLookAt.x -= 200.f * DT;
	}

	if (KEY_PRESSED(KEY::L))
	{
		m_vLookAt.x += 200.f * DT;
	}

	if (KEY_PRESSED(KEY::I))
	{
		m_vLookAt.y -= 200.f * DT;
	}

	if (KEY_PRESSED(KEY::K))
	{
		m_vLookAt.y += 200.f * DT;
	}

	// �÷��̾� ������ ī�޶� ����
	CPlayer* player = CLevelMgr::GetInst()->GetCurLevelPlayer();
	if (nullptr != player)
	{
		Vec2 rangeX = CLevelMgr::GetInst()->GetCurLevelCameraRangeX();
		Vec2 rangeY = CLevelMgr::GetInst()->GetCurLevelCameraRangeY();

		Vec2 playercamerapos = player->GetPos();

		Vec2 cameraoffset = Vec2(0.f, -300.f);
		playercamerapos += cameraoffset;

		Vec2 levelmid = CLevelMgr::GetInst()->GetCurLevelMiddle();


		//�÷��̾ �� �����ʿ��ִ��� ���ʿ��ִ��� (���̸����)
		bool left = playercamerapos.x < levelmid.x;
		//�÷��̾ �� �����ִ��� �Ʒ����ִ��� (���̸� �Ʒ�)
		bool beneath = playercamerapos.y > levelmid.y;

		float diffX = 0.f;
		float diffY = 0.f;

		if (left)
		{
			float limitX = rangeX.x;
			//���� �ȿ� ������� ��.
			if (limitX <= playercamerapos.x)
			{
				diffX = playercamerapos.x - m_vLookAt.x;
			}
			else
			{
			//������ ����� ��� ������ �������� ���̸� ���Ѵ�.
				diffX = limitX - m_vLookAt.x;
			}

		}
		else 
		{
			float limitX = rangeX.y;
			if (limitX >= playercamerapos.x)
			{
				diffX = playercamerapos.x - m_vLookAt.x;
			}
			else
			{
				//������ ����� ��� ������ �������� ���̸� ���Ѵ�.
				diffX = limitX - m_vLookAt.x;
			}
		}

		if (beneath)
		{
			float limitY = rangeY.x + cameraoffset.y;
			if (limitY > playercamerapos.y)
			{
				diffY = playercamerapos.y - m_vLookAt.y;
			}
			else
			{
				//������ ����� ��� ������ �������� ���̸� ���Ѵ�.
				diffY = limitY - m_vLookAt.y;
			}
		}
		else
		{
			float limitY = rangeY.y + cameraoffset.y;
			if (limitY < playercamerapos.y)
			{
				diffY = playercamerapos.y - m_vLookAt.y;
			}
			else
			{
				//������ ����� ��� ������ �������� ���̸� ���Ѵ�.
				diffY = limitY - m_vLookAt.y;
			}
		}

		

		Vec2 posdiff = Vec2(diffX, diffY);


		m_vLookAt = m_vLookAt + posdiff * DT * 1.3f;

	}

	


	//if (posdiff.x <0.001f && posdiff.y < 0.001f)
	//{
	//	m_vLookAt = m_vLookAt + posdiff;
	//}


	// ȭ�� �ػ��� �߽���ġ�� �˾Ƴ���.
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// �ػ� �߽ɰ�, ī�޶� ���� �����ִ� ��ǥ�� ���̰��� ���Ѵ�.
	m_vDiff = m_vLookAt - vCenter;


	// ī�޶� �̺�Ʈ�� ������ ����
	if (m_EventList.empty())
		return;

	// ī�޶� �̺�Ʈ�� �����Ѵٸ�
	FCamEvent& evnt = m_EventList.front();

	if (evnt.Type == CAM_EFFECT::FADE_IN)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_Alpha = 0;
			m_EventList.pop_front();
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = 1.f - fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}

	else if (evnt.Type == CAM_EFFECT::FADE_OUT)
	{
		evnt.AccTime += DT;

		if (evnt.Duration <= evnt.AccTime)
		{
			m_EventList.pop_front();
			m_Alpha = 255;
		}
		else
		{
			float fRatio = evnt.AccTime / evnt.Duration;
			float alpha = fRatio;
			m_Alpha = (UINT)(alpha * 255);
		}
	}
}

void CCamera::render(HDC _dc)
{
	if (0 == m_Alpha)
		return;

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;

	blend.SourceConstantAlpha = m_Alpha; // 0 ~ 255
	blend.AlphaFormat = 0; // 0

	AlphaBlend(_dc
		, 0, 0, m_Veil->GetWidth(), m_Veil->GetHeight()
		, m_Veil->GetDC()
		, 0, 0
		, m_Veil->GetWidth(), m_Veil->GetHeight()
		, blend);
}

void CCamera::SetInitialLookAt(Vec2 _RangeX, Vec2 _RangeY)
{
	m_vLookAt = Vec2(_RangeX.x, _RangeY.y);

}
