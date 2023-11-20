#pragma once

class CTexture;

Vec2 Rotate(Vec2 _vDir, float _angle);
bool GetRotateClock(Vec2 _vDir1, Vec2 _vDir2);


template<typename T>
bool IsValid(T*& _Entity)
{
	if (nullptr == _Entity)
	{
		return false;
	}

	if (_Entity->IsDead())
	{
		_Entity = nullptr;
		return false;
	}

	return true;
}
void ChangeLevel(LEVEL_TYPE _type);

void SaveWString(const wstring& _str, FILE* _File);
void LoadWString(wstring& _str, FILE* _File);

void SettexturetoDcPartiallyRight(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc);
void SettexturetoDcPartiallyDown(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc );
void SettexturetoDcPartiallyDownWithMagnification(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc , float _mag);


void SetNumberTextureToDc(HDC _dc, int _num
	, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset = 0.f);
void SetNumberTextureToDcWithTwoDigitZeroPadding(HDC _dc, int _num
	, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset = 0.f);

void SettexturetoDc(HDC _dc, CTexture* _ptexture, Vec2 _pos);
void SettexturetoDcWithMagnification(HDC _dc, CTexture* _ptexture, Vec2 _pos ,float _mag);
void SettexturetoDcWithAlpha(HDC _dc, CTexture* _ptexture, Vec2 _pos,int _alpha);
void SettexturetoDcWithAlphaAndMagnification(HDC _dc, CTexture* _ptexture, Vec2 _pos, int _alpha, float _mag);
Vec2 RotateDot(const Vec2& _Dot, float _rad);

void DrawRectToDc(HDC _dc
	, const Vec2& _UpRight
	, const Vec2& _UpLeft
	, const Vec2& _DownLeft
	, const Vec2& _DownRight);


float VecDot(const Vec2& _A, const Vec2& _B);

//ret : 0.000...f ~ 0.99f
float RandomPercentZtoO();


//ret : -0.49..f ~ +0.49...f
float RandomPercentHtH();