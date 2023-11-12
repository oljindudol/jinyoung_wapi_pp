#include "pch.h"
#include "func.h"
#include "struct.h"
#include "CEntity.h"
#include "CTaskMgr.h"
#include "define.h"
#include "CTexture.h"

Vec2 Rotate(Vec2 _vDir, float _angle)
{
	_vDir.Normalize();

	Vec2 vRotateDir = Vec2(cosf(_angle) * _vDir.x - sinf(_angle) * _vDir.y
		, sinf(_angle) * _vDir.x + cosf(_angle) * _vDir.y);

	return vRotateDir;
}

bool GetRotateClock(Vec2 _vDir1, Vec2 _vDir2)
{
	//_vDir1.x; _vDir1.y; 0.f, _vDir1.x; _vDir1.y;
	//_vDir2.x; _vDir2.y; 0.f, _vDir2.x; _vDir2.y;

	if (_vDir1.x * _vDir2.y - _vDir1.y * _vDir2.x > 0.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ChangeLevel(LEVEL_TYPE _type)
{
	FTask task = {};
	task.Type = LEVEL_CHANGE;
	task.Param_1 = (INT_PTR)_type;
	CTaskMgr::GetInst()->AddTask(task);
}

void SaveWString(const wstring& _str, FILE* _File)
{
	size_t iLen = _str.length();
	fwrite(&iLen, sizeof(size_t), 1, _File);
	fwrite(_str.c_str(), sizeof(wchar_t), _str.length(), _File);
}

void LoadWString(wstring& _str, FILE* _File)
{
	size_t iLen = 0;
	wchar_t szBuff[255] = {};

	fread(&iLen, sizeof(size_t), 1, _File);
	fread(szBuff, sizeof(wchar_t), iLen, _File);

	_str = szBuff;
}


void SettexturetoDcPartiallyRight(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc)
{

	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, (int)_pos.x
		, (int)_pos.y
		, (int) (_tex->GetWidth() * _perc)
		, _tex->GetHeight()
		, _tex->GetDC()
		, 0, 0
		, (int)(_tex->GetWidth() * _perc)
		, _tex->GetHeight()
		, blend);
}

void SettexturetoDcPartiallyDown(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, (int)_pos.x
		, (int)_pos.y
		, _tex->GetWidth()
		, (int)(_tex->GetHeight() * _perc)
		, _tex->GetDC()
		, 0, 0
		, _tex->GetWidth()
		, (int)(_tex->GetHeight() * _perc)
		, blend);
}

void SetLettertoDc(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset)
{
	wstring strnums = std::to_wstring(_num);

	Vec2 offset = Vec2(_offset, 0.f);

	if (0 != _vecnumtex.size())
	{
		offset += Vec2(
			(int)_vecnumtex[0]->GetWidth()
			, 0
		);
	}

	for (int i = 0; i < strnums.size(); i++)
	{
		int num = strnums[i] - '0';
		SettexturetoDc(_dc, _vecnumtex[num], _pos + (offset * (float)i));
	}

}

void SettexturetoDc(HDC _dc, CTexture* _ptexture, Vec2 _pos)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, int(_pos.x)
		, int(_pos.y)
		, _ptexture->GetWidth()
		, _ptexture->GetHeight()
		, _ptexture->GetDC()
		, 0, 0
		, _ptexture->GetWidth()
		, _ptexture->GetHeight()
		, blend);
}

Vec2 RotateDot(const Vec2& _Dot, float _rad)
{
	Vec2 vRotateDir = 
		Vec2(cosf(_rad) * _Dot.x 
			- sinf(_rad) * _Dot.y, 
			sinf(_rad) * _Dot.x 
			+ cosf(_rad) * _Dot.y);

	return vRotateDir;
}

void DrawRectToDc(HDC _dc, const Vec2& _UpRight, const Vec2& _UpLeft, const Vec2& _DownLeft, const Vec2& _DownRight)
{


}

float VecDot(const Vec2& _A, const Vec2& _B)
{
	return _A.x * _B.x + _A.y * _B.y;
}

