#include "pch.h"
#include "CTexture.h"

#include "CEngine.h"

HBITMAP FlipBitmapHorizontally(HBITMAP hbm);

CTexture::CTexture()
	: m_hBit(nullptr)
	, m_hDC(nullptr)
	, m_Info{}
{
}

CTexture::~CTexture()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}



//-----------------------------------------------------------------------------
// Name : GetRotatedBitmap()
// Desc : 비트맵 회전
//    인자들 : 윈도우DC, 비트맵 핸들, 회전각(라디안), 공백 컬러
//-----------------------------------------------------------------------------
HBITMAP GetRotatedBitmap(HDC hdc, HBITMAP hBitmap, float radians)// COLORREF clrBack)
{
	// Create a memory DC compatible with the display
	HDC sourceDC, destDC;
	BITMAP bm;

	HBITMAP hbmResult;
	HBITMAP hbmOldSource;
	HBITMAP hbmOldDest;
	HBRUSH hbrBack;
	HBRUSH hbrOld;

	XFORM xform;

	float cosine, sine;
	int x1, y1, x2, y2, x3, y3, minx, miny, maxx, maxy, w, h;


	sourceDC = CreateCompatibleDC(hdc);
	destDC = CreateCompatibleDC(hdc);



	// Get logical coordinates
	GetObject(hBitmap, sizeof(bm), &bm);

	cosine = cos(radians);
	sine = sin(radians);



	//회전된 이미지의 영역을 구한다.
	// Compute dimensions of the resulting bitmap
	// First get the coordinates of the 3 corners other than origin
	x1 = (int)(bm.bmHeight * sine);
	y1 = (int)(bm.bmHeight * cosine);
	x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
	y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);
	x3 = (int)(bm.bmWidth * cosine);
	y3 = (int)(-bm.bmWidth * sine);

	minx = min(0, min(x1, min(x2, x3)));
	miny = min(0, min(y1, min(y2, y3)));
	maxx = max(0, max(x1, max(x2, x3)));
	maxy = max(0, max(y1, max(y2, y3)));

	w = maxx - minx;
	h = maxy - miny;

	// Create a bitmap to hold the result
	hbmResult = CreateCompatibleBitmap(hdc, w, h);

	hbmOldSource = (HBITMAP)SelectObject(sourceDC, hBitmap);
	hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);

	// Draw the background color before we change mapping mode
	SELECT_BRUSH(destDC,(HBRUSH)GetStockObject(HOLLOW_BRUSH));
	PatBlt(destDC, 0, 0, w, h, PATCOPY);

	// We will use world transform to rotate the bitmap
	SetGraphicsMode(destDC, GM_ADVANCED);
	xform.eM11 = cosine;
	xform.eM12 = -sine;
	xform.eM21 = sine;
	xform.eM22 = cosine;
	xform.eDx = (float)-minx;
	xform.eDy = (float)-miny;

	SetWorldTransform(destDC, &xform);

	// Now do the actual rotating - a pixel at a time
	BitBlt(destDC, 0, 0, bm.bmWidth, bm.bmHeight, sourceDC, 0, 0, SRCCOPY);

	// Restore DCs
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);

	DeleteDC(sourceDC);
	DeleteDC(destDC);

	return hbmResult;

}

bool CTexture::Load_rotated(const wstring& _strFilePath,  float _rad)
{
	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);


	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// 플레이어가 사용할 이미지 비트맵 로딩
		m_hBit = GetRotatedBitmap(CEngine::GetInst()->GetMainDC(), m_hBit, _rad);
		if (nullptr == m_hBit)
		{
			return false;
		}
	}

	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupInput = {};
		GdiplusStartup(&gdiplusToken, &gidstartupInput, nullptr);
		Image* pImg = Image::FromFile(_strFilePath.c_str(), false);

		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Status stat = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

		if (Status::Ok != stat)
			return false;
	}

	m_hBit = GetRotatedBitmap(CEngine::GetInst()->GetMainDC(), m_hBit, _rad);
	//m_hBit = FlipBitmapHorizontally(_origin->GetBitmap());
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	//디버그용
	//BitBlt(CEngine::GetInst()->GetMainDC()
	//	, 0, 0
	//	, CEngine::GetInst()->GetResolution().x, CEngine::GetInst()->GetResolution().y
	//	, m_hDC
	//	, 0, 0, SRCCOPY);

	return true;
}


HBITMAP FlipBitmapHorizontally(HBITMAP hbm) {
	BITMAP bm;
	GetObject(hbm, sizeof(BITMAP), &bm);
	int wd = bm.bmWidth;
	int hgt = bm.bmHeight;

	HDC hdcScr = GetDC(NULL);
	HDC hdcFlipped = CreateCompatibleDC(hdcScr);
	HBITMAP hbmFlipped = CreateCompatibleBitmap(hdcScr, wd, hgt);
	HGDIOBJ oldFlipped = SelectObject(hdcFlipped, hbmFlipped);
	HDC hdcSrc = CreateCompatibleDC(hdcScr);
	HGDIOBJ oldSrc = SelectObject(hdcSrc, hbm);

	StretchBlt(hdcFlipped, wd, 0, -wd, hgt, hdcSrc, 0, 0, wd, hgt, SRCCOPY);

	SelectObject(hdcSrc, oldSrc);
	DeleteDC(hdcSrc);
	SelectObject(hdcFlipped, oldFlipped);
	DeleteDC(hdcFlipped);
	ReleaseDC(NULL, hdcScr);

	return hbmFlipped;
}

bool CTexture::Load_r(const wstring& _strFilePath)
{

	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// 플레이어가 사용할 이미지 비트맵 로딩
		m_hBit = FlipBitmapHorizontally((HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
		if (nullptr == m_hBit)
		{
			return false;
		}
	}

	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupInput = {};
		GdiplusStartup(&gdiplusToken, &gidstartupInput, nullptr);
		Image* pImg = Image::FromFile(_strFilePath.c_str(), false);

		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Status stat = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

		if (Status::Ok != stat)
			return false;
	}



	m_hBit = FlipBitmapHorizontally(m_hBit);
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);


	return true;
}


bool CTexture::Load(const wstring& _strFilePath)
{

	wchar_t szExt[20] = {};
	_wsplitpath_s(_strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 20);

	if (!wcscmp(szExt, L".bmp") || !wcscmp(szExt, L".BMP"))
	{
		// 플레이어가 사용할 이미지 비트맵 로딩
		m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		if (nullptr == m_hBit)
		{
			return false;
		}
	}

	else if (!wcscmp(szExt, L".png") || !wcscmp(szExt, L".PNG"))
	{
		ULONG_PTR gdiplusToken = 0;
		GdiplusStartupInput gidstartupInput = {};
		GdiplusStartup(&gdiplusToken, &gidstartupInput, nullptr);
		Image* pImg = Image::FromFile(_strFilePath.c_str(), false);

		Bitmap* pBitmap = (Bitmap*)pImg->Clone();
		Status stat = pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_hBit);

		if (Status::Ok != stat)
			return false;
	}


	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);

	return true;
}


void CTexture::Create(UINT _Width, UINT Height)
{
	m_hBit = CreateCompatibleBitmap(CEngine::GetInst()->GetMainDC(), _Width, Height);
	m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());

	//m_hDC = CreateCompatibleDC(CEngine::GetInst()->GetMainDC());
	DeleteObject(SelectObject(m_hDC, m_hBit));
	GetObject(m_hBit, sizeof(BITMAP), &m_Info);
}

