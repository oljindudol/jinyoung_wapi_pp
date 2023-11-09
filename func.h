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
void SettexturetoDcPartiallyDown(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc);
void SetLettertoDc(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset = 0.f);
void SettexturetoDc(HDC _dc, CTexture* _ptexture, Vec2 _pos);