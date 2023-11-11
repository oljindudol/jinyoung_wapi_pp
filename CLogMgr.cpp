#include "pch.h"
#include "CLogMgr.h"

#include "CTimeManager.h"
#include "CKeyMgr.h"

CLogMgr::CLogMgr()
	: m_LogMaxLife(5.f)
{
}

CLogMgr::~CLogMgr()
{
}

void CLogMgr::tick(HDC _dc)
{

	SELECT_FONT(_dc, FONT_TYPE::LOG_TEXT);

	list<FLog>::iterator iter = m_LogList.begin();

	for (; iter != m_LogList.end(); )
	{
		(*iter).AccTime += DT;
		if (m_LogMaxLife < (*iter).AccTime)
		{
			iter = m_LogList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iter = m_LogList.begin();
	POINT LT = { 10, 10 };

	SetBkMode(_dc, OPAQUE);

	int i = 0;
	for (; iter != m_LogList.end(); ++iter, ++i)
	{
		switch ((*iter).Level)
		{
		case LOG:
			SetTextColor(_dc, RGB(0, 0, 0));
			TextOut(_dc, LT.x, LT.y + i * int(10.f * 1.5f), (*iter).Message.c_str(), (int)(*iter).Message.length());
			break;
		case WARNING:
			SetTextColor(_dc, RGB(210, 210, 153));
			break;
		case ERR:
			SetTextColor(_dc, RGB(255, 0, 0));
			break;
		}

		TextOut(_dc, LT.x, LT.y + i * int(10.f * 1.5f), (*iter).Message.c_str(), (int)(*iter).Message.length());
	}





	// 마우스 포지션
	//int x = (int)CKeyMgr::GetInst()->GetMousePos().x;
	//int y = (int)CKeyMgr::GetInst()->GetMousePos().y;// -20;

	//wstring tmousepos = L"x:" + std::to_wstring(x)
	//	+ L"y:" +  std::to_wstring(y);

	//TextOut(_dc, x, y , tmousepos.c_str(), (int)tmousepos.length());


	SetBkMode(_dc, TRANSPARENT);
	auto iter2 = m_CustomLogList.begin();
	while (m_CustomLogList.end() != iter2)
	{
		//좌표
		int x = (int)(*iter2).second.x;
		int y = (int)(*iter2).second.y;

		//메세지
		wstring msg= (*iter2).first;

		TextOut(_dc, x - (int)msg.length()*7 , y, msg.c_str(), (int)msg.length());

		iter2 = m_CustomLogList.erase(iter2);
	}


}
