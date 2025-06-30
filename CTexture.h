#pragma once
#include "CAsset.h"


class CTexture :
	public CAsset
{
private:
	HBITMAP     m_hBit;
	HDC         m_hDC;
	BITMAP      m_Info;

public:
	HDC GetDC() { return m_hDC; }
	HBITMAP GetBitmap() { return m_hBit; }
	UINT GetWidth() { return m_Info.bmWidth; }
	UINT GetHeight() { return m_Info.bmHeight; }
	CTexture();
	~CTexture();

private:
	virtual bool Load(const wstring& _strFilePath) override;
	virtual bool Load_r(const wstring& _strFilePath);
	virtual bool Load_rotated(const wstring& _strFilePath, float _rad);

	void Create(UINT _Width, UINT Height);

private:

	friend class CAssetMgr;
};

