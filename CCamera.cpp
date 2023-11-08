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
	// 방향키로 카메라가 바라보고 있는 위치를 변경
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

	// 플레이어 쪽으로 카메라 보정
	CPlayer* player = CLevelMgr::GetInst()->GetCurLevelPlayer();
	if (nullptr != player)
	{
		Vec2 rangeX = CLevelMgr::GetInst()->GetCurLevelCameraRangeX();
		Vec2 rangeY = CLevelMgr::GetInst()->GetCurLevelCameraRangeY();

		Vec2 playercamerapos = player->GetPos();

		Vec2 cameraoffset = Vec2(0.f, -300.f);
		playercamerapos += cameraoffset;

		Vec2 levelmid = CLevelMgr::GetInst()->GetCurLevelMiddle();


		//플레이어가 맵 오른쪽에있는지 왼쪽에있는지 (참이면왼쪽)
		bool left = playercamerapos.x < levelmid.x;
		//플레이어가 맵 위에있는지 아래에있는지 (참이면 아래)
		bool beneath = playercamerapos.y > levelmid.y;

		float diffX = 0.f;
		float diffY = 0.f;

		if (left)
		{
			float limitX = rangeX.x;
			//범위 안에 있을경우 참.
			if (limitX <= playercamerapos.x)
			{
				diffX = playercamerapos.x - m_vLookAt.x;
			}
			else
			{
			//범위를 벗어났을 경우 범위를 기준으로 차이를 구한다.
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
				//범위를 벗어났을 경우 범위를 기준으로 차이를 구한다.
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
				//범위를 벗어났을 경우 범위를 기준으로 차이를 구한다.
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
				//범위를 벗어났을 경우 범위를 기준으로 차이를 구한다.
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


	// 화면 해상도의 중심위치를 알아낸다.
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// 해상도 중심과, 카메라가 현재 보고있는 좌표의 차이값을 구한다.
	m_vDiff = m_vLookAt - vCenter;


	// 카메라 이벤트가 없으면 리턴
	if (m_EventList.empty())
		return;

	// 카메라 이벤트가 존재한다면
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
