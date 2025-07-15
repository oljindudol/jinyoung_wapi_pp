#include "pch.h"
#include "CAssetMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CSound.h"


CAssetMgr::CAssetMgr()
	:m_transtex(nullptr)
{
	POINT vResol = CEngine::GetInst()->GetResolution();
	m_transtex = CreateTexture(L"TransTex", vResol.x, vResol.y);

	HDC transdc = m_transtex->GetDC();

	SetBkMode(transdc, TRANSPARENT);

	SELECT_BRUSH(transdc, (HBRUSH)GetStockObject(WHITE_BRUSH));

	Rectangle(transdc, -1, -1, vResol.x + 1, vResol.y + 1);

}

CAssetMgr::~CAssetMgr()
{
	for (const auto& pair : m_mapTex)
	{
		delete pair.second;
	}

	for (const auto& pair : m_mapSound)
	{
		delete pair.second;
	}

	ShutdownGDIPlus();
}


CTexture* CAssetMgr::LoadTexture_r(const wstring& _strKey, const wstring& _strRelativePath)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	CTexture* pTexture = FindTexture(_strKey);
	if (pTexture != nullptr)
		return pTexture;

	pTexture = new CTexture;
	if (!pTexture->Load_r(CPathMgr::GetContentPath() + _strRelativePath))
	{
		delete pTexture;
		return nullptr;
	}

	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;
	m_mapTex[_strKey] = pTexture;

	return pTexture;
}

CTexture* CAssetMgr::LoadRotatedTexture(const wstring& _strKey, const wstring& _strRelativePath, int _rot)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	CTexture* pTexture = FindTexture(_strKey);
	if (pTexture != nullptr)
		return pTexture;

	pTexture = new CTexture;
	float rad = static_cast<float>(_rot) * 0.0174533f;
	if (!pTexture->Load_rotated(CPathMgr::GetContentPath() + _strRelativePath, rad))
	{
		delete pTexture;
		return nullptr;
	}

	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = L""; // ȸ���� �ؽ�ó�� ��� ��� X
	m_mapTex[_strKey] = pTexture;

	return pTexture;
}


HBITMAP CAssetMgr::GetTransHBITMAP()
{
	return m_transtex->GetBitmap();
}



#include "CProfileMgr.h"
CTexture* CAssetMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	PROFILE_SCOPE("LoadTexture");

	std::lock_guard<std::mutex> lock(m_mutex);

	//  1. �� �ȿ����� 1ȸ Ȯ��
	CTexture* pTexture = FindTexture(_strKey);
	if (pTexture != nullptr)
		return pTexture;

	//  2. ���� �� �ε�
	pTexture = new CTexture;
	if (!pTexture->Load(CPathMgr::GetContentPath() + _strRelativePath))
	{
		delete pTexture;
		return nullptr;
	}

	//  3. ��� �� ��ȯ
	pTexture->m_strKey = _strKey;
	pTexture->m_strRelativePath = _strRelativePath;
	m_mapTex[_strKey] = pTexture;
	return pTexture;
}

CTexture* CAssetMgr::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
	// �Էµ� Ű�� �ش��ϴ� �ؽ��İ� �ִ��� Ȯ���Ѵ�.
	CTexture* pTexture = FindTexture(_strKey);
	if (nullptr != pTexture)
	{
		// �̹� �ִ� �ؽ��ĸ� ã���� ��ȯ���ش�.
		return pTexture;
	}

	pTexture = new CTexture;
	pTexture->Create(_width, _height);

	// Asset �� Ű���� ��ΰ��� �˷��ش�.
	pTexture->m_strKey = _strKey;
	m_mapTex.insert(make_pair(_strKey, pTexture));
	return pTexture;
}


CTexture* CAssetMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);

	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}


CSound* CAssetMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �Էµ� Ű�� �ش��ϴ� �ؽ��İ� �ִ��� Ȯ���Ѵ�.
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		// �̹� �ִ� �ؽ��ĸ� ã���� ��ȯ���ش�.
		return pSound;
	}

	// �Էµ� Ű�� �ش��ϴ� �ؽ��İ� ������ �ε��ؼ� ��ȯ���ش�.
	wstring strContentPath = CPathMgr::GetContentPath();
	wstring strFilePath = strContentPath + _strRelativePath;

	pSound = new CSound;

	if (!pSound->Load(strFilePath))
	{
		// �ؽ��� �ε尡 ������ ���(��� ���� ���..)
		delete pSound;
		return nullptr;
	}

	// Asset �� Ű���� ��ΰ��� �˷��ش�.
	pSound->m_strKey = _strKey;
	pSound->m_strRelativePath = _strRelativePath;

	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;

}

CSound* CAssetMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAssetMgr::PrintAllTextures()
{
	printf("\n=== [��ü �ε�� �ؽ�ó ���] ===\n");
	for (const auto& pair : m_mapTex)
	{
		const wstring& key = pair.first;
		CTexture* pTex = pair.second;

		wprintf(L"Key: %s | Size: %d x %d\n",
			key.c_str(),
			pTex->GetWidth(),
			pTex->GetHeight());
	}
	printf("�� �ؽ�ó ��: %zu��\n", m_mapTex.size());
}

void CAssetMgr::PrintTextureMemoryUsage()
{
	size_t totalBytes = 0;

	for (const auto& pair : m_mapTex)
	{
		CTexture* pTex = pair.second;
		int width = pTex->GetWidth();
		int height = pTex->GetHeight();
		int bpp = 4; // ��: RGBA8888 ����

		totalBytes += static_cast<size_t>(width) * height * bpp;
	}

	printf("���� �� �ؽ�ó �޸� ��뷮: %.2f MB\n", totalBytes / (1024.0 * 1024.0));
}

ULONG_PTR g_gdiplusToken = 0;
void CAssetMgr::InitGDIPlus()
{
	GdiplusStartupInput gdiStartupInput;
	GdiplusStartup(&g_gdiplusToken, &gdiStartupInput, nullptr);
}

void CAssetMgr::ShutdownGDIPlus()
{
	GdiplusShutdown(g_gdiplusToken);
}


CTexture* CAssetMgr::CreateTextureFromImageData(const ImageData& img)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (CTexture* tex = FindTexture(img.key))
		return tex;

	CTexture* tex = new CTexture;

	HDC hdc = GetDC(NULL);

	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = img.width;
	bmi.bmiHeader.biHeight = -img.height; // top-down
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* bits = nullptr;
	HBITMAP hBmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
	if (!hBmp || !bits)
	{
		delete tex;
		ReleaseDC(NULL, hdc);
		return nullptr;
	}

	memcpy(bits, img.pixels.data(), img.pixels.size());

	tex->m_hDC = CreateCompatibleDC(hdc);
	DeleteObject(SelectObject(tex->m_hDC, hBmp));

	tex->m_hBit = hBmp;
	GetObject(hBmp, sizeof(BITMAP), &tex->m_Info);
	tex->m_strKey = img.key;
	tex->m_strRelativePath = img.relativePath;

	m_mapTex[img.key] = tex;

	ReleaseDC(NULL, hdc);
	return tex;
}
CTexture* CAssetMgr::CreateTextureFromImageData(const std::vector<unsigned char>& pixels, int width, int height, const std::wstring& key)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (CTexture* tex = FindTexture(key))
		return tex;

	CTexture* tex = new CTexture;

	HDC hdc = GetDC(NULL);

	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // top-down
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* bits = nullptr;
	HBITMAP hBmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
	if (!hBmp || !bits)
	{
		delete tex;
		ReleaseDC(NULL, hdc);
		return nullptr;
	}

	memcpy(bits, pixels.data(), pixels.size());

	tex->m_hDC = CreateCompatibleDC(hdc);
	DeleteObject(SelectObject(tex->m_hDC, hBmp));

	tex->m_hBit = hBmp;
	GetObject(hBmp, sizeof(BITMAP), &tex->m_Info);
	tex->m_strKey = key;
	tex->m_strRelativePath = L""; // �ʿ�� ���ڷ� ���� �� ����

	m_mapTex[key] = tex;

	ReleaseDC(NULL, hdc);
	return tex;
}

void CAssetMgr::init()
{
	InitGDIPlus();
}


