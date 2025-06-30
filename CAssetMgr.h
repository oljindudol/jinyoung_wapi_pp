#pragma once

#include "CSound.h"

class CTexture;
class CSound;

class CAssetMgr
{
	SINGLETON(CAssetMgr);
private:
	map<wstring, CTexture*>	m_mapTex;
	map<wstring, CSound*>	m_mapSound;
	CTexture* m_transtex;
	mutex m_mutex;

public:
	HBITMAP GetTransHBITMAP();
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* LoadTexture_r(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* LoadRotatedTexture(const wstring& _strKey, const wstring& _strRelativePath, int _rot);
	CTexture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	CTexture* FindTexture(const wstring& _strKey);

	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath);
	CSound* FindSound(const wstring& _strKey);
	bool IsPlaying(CSound* _pSound) { return _pSound->m_bPlay; }

	void PrintAllTextures();
	void PrintTextureMemoryUsage();
	void init();
	void InitGDIPlus();
	void ShutdownGDIPlus();

};