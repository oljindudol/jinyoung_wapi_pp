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
		, (int)(_tex->GetWidth() * _perc)
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

void SettexturetoDcPartiallyDownWithMagnification(HDC _dc, CTexture* _tex, Vec2 _pos, float _perc, float _mag)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, (int)_pos.x
		, (int)_pos.y
		, (int)(_tex->GetWidth() * _mag)
		, (int)(_tex->GetHeight() * _perc * _mag)
		, _tex->GetDC()
		, 0, 0
		, _tex->GetWidth()
		, (int)(_tex->GetHeight() * _perc)
		, blend);
}

void SetNumberTextureToDc(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset)
{
	if (_num < 0)
		return;
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

void SetNumberTextureToDcWithTwoDigitZeroPadding(HDC _dc, int _num, const vector<CTexture*> _vecnumtex, Vec2 _pos, float _offset)
{
	wstring strnums = std::to_wstring(_num);

	if (1 == strnums.size())
	{
		strnums = L'0' + strnums;
	}

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

//void SetNumberTextureToDcWithRandomOffset(HDC _dc, const wstring& _nums
//	,const vector<CTexture*> _vecnumtex 
//	,const vector<Vec2> _randomoffsetpercent, Vec2 _pos, int _alpha)
//{
//
//	Vec2 offset = Vec2(_offset, 0.f);
//	
//	int width = 0;
//	int height= 0;
//
//	if (0 != _vecnumtex.size())
//	{
//		width = (int)_vecnumtex[0]->GetWidth();
//		height = (int)_vecnumtex[0]->GetHeight();
//	}
//
//	offset += Vec2(
//		(int)width
//		, 0
//	);
//	float maxf = 32767.f;
//	float randoffpercent = 0.3f;
//
//	int numssize = _nums.size();
//
//
//	for (int i = 0; i < numssize; i++)
//	{
//		int num = _nums[i] - '0';
//		SettexturetoDcWithAlpha(_dc,
//			_vecnumtex[num], _pos 
//			+ (offset * (float)i) 
//			+ Vec2(_randomoffsetpercent[i].x * width * randoffpercent,
//				_randomoffsetpercent[i].y * height * randoffpercent ) , _alpha);
//	}
//}

//void SetNumberTextureToDcWithRandomOffsetAndUnits(HDC _dc, int _num, const vector<CTexture*> _vecnumtex
//	, const vector<CTexture*> _vecunitstex, Vec2 _pos, int _alpha, float _offset = 0.f)
//{
//
//
//
//}



void SettexturetoDcWithAlpha(HDC _dc, CTexture* _ptexture, Vec2 _pos, int _alpha)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = _alpha; // 0 ~ 255
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

void SettexturetoDcWithAlphaAndMagnification(HDC _dc, CTexture* _ptexture, Vec2 _pos, int _alpha, float _mag)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = _alpha; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, int(_pos.x)
		, int(_pos.y)
		, (int)(_ptexture->GetWidth() * _mag)
		, (int)(_ptexture->GetHeight() * _mag)
		, _ptexture->GetDC()
		, 0, 0
		, _ptexture->GetWidth()
		, _ptexture->GetHeight()
		, blend);
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

void SettexturetoDcWithMagnification(HDC _dc, CTexture* _ptexture, Vec2 _pos, float _mag)
{
	BLENDFUNCTION blend = {};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0; // 0이여야합니다

	blend.SourceConstantAlpha = 255; // 0 ~ 255
	blend.AlphaFormat = AC_SRC_ALPHA; // 고정

	AlphaBlend(_dc
		, int(_pos.x)
		, int(_pos.y)
		, (int)(_ptexture->GetWidth() * _mag)
		, (int)(_ptexture->GetHeight() * _mag)
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

wstring RSpacePad(const wstring& _origin, int _size)
{
	int size = (int)_origin.size();
	if (_size <= size)
	{
		return _origin;
	}
	else
	{
		wstring ret = _origin;
		int cnt = (int)((_size - size));
		for (int i = 0; i < cnt; ++i)
		{
			ret += L"  ";
		}
		return ret;
	}

}

wstring LSpacePad_Number(const wstring& _origin, int _size)
{
	int size = (int)_origin.size();
	if (_size <= size)
	{
		return _origin;
	}
	else
	{
		wstring ret = _origin;
		int cnt = (int)((_size - size));
		for (int i = 0; i < cnt; ++i)
		{
			ret = L" " + ret;
		}
		return ret;
	}
}

void DrawRectToDc(HDC _dc, const Vec2& _UpRight, const Vec2& _UpLeft, const Vec2& _DownLeft, const Vec2& _DownRight)
{

}

float VecDot(const Vec2& _A, const Vec2& _B)
{
	return _A.x * _B.x + _A.y * _B.y;
}

float RandomPercentZtoO()
{
	return ((float)rand()) / 32767.f;
}

float RandomPercentHtH()
{
	return ((float)rand()) / 32767.f - 0.5f;
}


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

string ToUtf8(const std::wstring& wide)
{
	if (wide.empty())
		return std::string();

	int utf8Len = ::WideCharToMultiByte(
		CP_UTF8,            // UTF-8 code page
		0,                  // no special flags
		wide.c_str(),       // source wide string
		-1,                 // null-terminated
		nullptr,            // no output buffer yet
		0,                  // calculate required size
		nullptr, nullptr);  // no default char

	if (utf8Len == 0)
		return std::string(); // conversion failed

	std::string utf8(utf8Len, 0);

	::WideCharToMultiByte(
		CP_UTF8, 0,
		wide.c_str(), -1,
		&utf8[0], utf8Len,
		nullptr, nullptr);

	// Remove null terminator from std::string
	if (!utf8.empty() && utf8.back() == '\0')
		utf8.pop_back();

	return utf8;
}

ImageData LoadImageData(const wstring& _strFilePath)
{
	ImageData img;
	img.key = _strFilePath;
	img.relativePath = _strFilePath;

	std::string utf8Path = ToUtf8(_strFilePath);
	int w, h, c;
	unsigned char* raw = stbi_load(utf8Path.c_str(), &w, &h, &c, 4); // force RGBA

	if (raw)
	{
		img.width = w;
		img.height = h;
		img.channels = 4;
		img.pixels.assign(raw, raw + (w * h * 4));
		stbi_image_free(raw);
	}

	return img;
}

#include "CPathMgr.h"
ImageData LoadImageData(const wstring& _strFilePath, const wstring& _key, int _rot)
{
	ImageData img;
	img.key = _key;
	img.relativePath = _strFilePath;

	// 절대경로 조립
	std::wstring absPath = CPathMgr::GetContentPath() + _strFilePath;
	std::string utf8Path = ToUtf8(absPath);

	int w, h, c;
	unsigned char* raw = stbi_load(utf8Path.c_str(), &w, &h, &c, 4); // force RGBA

	if (!raw)
		return img;

	img.width = w;
	img.height = h;
	img.channels = 4;

	// 회전이 필요 없으면 그대로 복사
	if (_rot == 0)
	{
		img.pixels.assign(raw, raw + (w * h * 4));
		img.flippedPixels = ConvertAndFlipRGBAtoBGRA(raw, w, h);
		stbi_image_free(raw);
		ConvertRGBAtoBGRA(img.pixels);
		//img.flippedPixels = FlipHorizontal(img);
		return img;
	}

	// 회전된 이미지 버퍼 생성
	std::vector<unsigned char> rotated(w * h * 4, 0);

	// 회전 각도(rad)
	float rad = static_cast<float>(_rot) * 0.0174533f;
	float cosA = cosf(rad);
	float sinA = sinf(rad);

	// 중심 기준 회전
	int cx = w / 2;
	int cy = h / 2;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			// 원래 좌표를 중심 기준으로 회전
			int dx = x - cx;
			int dy = y - cy;

			int rx = static_cast<int>(dx * cosA - dy * sinA + cx);
			int ry = static_cast<int>(dx * sinA + dy * cosA + cy);

			if (rx < 0 || rx >= w || ry < 0 || ry >= h)
				continue;

			int srcIdx = (ry * w + rx) * 4;
			int dstIdx = (y * w + x) * 4;

			rotated[dstIdx + 0] = raw[srcIdx + 0]; // R
			rotated[dstIdx + 1] = raw[srcIdx + 1]; // G
			rotated[dstIdx + 2] = raw[srcIdx + 2]; // B
			rotated[dstIdx + 3] = raw[srcIdx + 3]; // A
		}
	}

	stbi_image_free(raw);
	ConvertRGBAtoBGRA(rotated);
	img.pixels = std::move(rotated);

	return img;
}

void ConvertRGBAtoBGRA(std::vector<unsigned char>& pixels)
{
	for (size_t i = 0; i + 3 < pixels.size(); i += 4)
	{
		float alpha = pixels[i + 3] / 255.0f;
		pixels[i + 0] = static_cast<unsigned char>(pixels[i + 0] * alpha); // R
		pixels[i + 1] = static_cast<unsigned char>(pixels[i + 1] * alpha); // G
		pixels[i + 2] = static_cast<unsigned char>(pixels[i + 2] * alpha); // B
	}

	for (size_t i = 0; i + 3 < pixels.size(); i += 4)
	{
		std::swap(pixels[i], pixels[i + 2]); // R ↔ B
	}
}

std::vector<unsigned char> FlipHorizontal(const ImageData& img)
{
	int w = img.width;
	int h = img.height;
	std::vector<unsigned char> flipped(img.pixels.size());

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int src = (y * w + x) * 4;
			int dst = (y * w + (w - 1 - x)) * 4;

			flipped[dst + 0] = img.pixels[src + 0]; // R
			flipped[dst + 1] = img.pixels[src + 1]; // G
			flipped[dst + 2] = img.pixels[src + 2]; // B
			flipped[dst + 3] = img.pixels[src + 3]; // A
		}
	}
	return flipped;
}

std::vector<unsigned char> ConvertAndFlipRGBAtoBGRA(unsigned char* src, int width, int height)
{
	std::vector<unsigned char> flipped(width * height * 4);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int srcIdx = (y * width + x) * 4;
			int dstIdx = (y * width + (width - 1 - x)) * 4;

			float alpha = src[srcIdx + 3] / 255.0f;

			// premultiplied alpha + BGRA 변환
			flipped[dstIdx + 0] = static_cast<unsigned char>(src[srcIdx + 2] * alpha); // B
			flipped[dstIdx + 1] = static_cast<unsigned char>(src[srcIdx + 1] * alpha); // G
			flipped[dstIdx + 2] = static_cast<unsigned char>(src[srcIdx + 0] * alpha); // R
			flipped[dstIdx + 3] = src[srcIdx + 3];                                     // A
		}
	}

	return flipped;
}
