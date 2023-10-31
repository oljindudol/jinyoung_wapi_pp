#pragma once
class CPathMgr
{
private:
	//전방선언의 형태로 되는것이기떄문에 cpp에서 초기화필요!
	static wchar_t g_szContent[255];

public:
	static void init();
	__inline static wchar_t* GetContentPath() { return g_szContent; }
};

