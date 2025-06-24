#pragma once


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>


#include <vector>
#include <list>
#include <map>
#include <string>
#include <crtdbg.h>
#include <assert.h>
#include <unordered_map>
#include <queue>


#pragma comment(lib, "Msimg32.lib")

// Png 관련
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

// 사운드
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

// 뮤텍스
#include <mutex>
using std::mutex;

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

using namespace::Gdiplus;
using std::vector;
using std::list;
using std::map;
using std::string;
using std::wstring;
using std::make_pair;
using std::unordered_map;
using std::pair;

//순서 의존성 해결?
#define RGB_BLACK   (RGB(0, 0, 0))
#define RGB_RED		(RGB(255, 0, 0))
#define RGB_GREEN	(RGB(0, 255, 0))
#define RGB_BLUE	(RGB(0, 0, 255))
#define RGB_WHITE	(RGB(255, 255, 255))
#define RGB_YELLOW	(RGB(255, 255, 0))

//enum 선언이유= pen 인덱스 체크용(사람실수)
enum COLOR
{
	BLACK,
	RED,
	GREEN,
	BLUE,
	WHITE,
	YELLOW,
};


#include "global.h"

#include <iostream>

struct Profiler {
	std::string name;
	double total = 0;
	int count = 0;

	Profiler(const std::string& n) : name(n) {}

	void add(double duration) {
		total += duration;
		count++;
	}

	void print() {
		std::cout << name << " - total: " << total
			<< " s, count: " << count
			<< ", avg: " << (total / count) << " s\n";
	}
};

struct ScopedProfiler {
	Profiler& profiler;
	std::chrono::high_resolution_clock::time_point start;

	ScopedProfiler(Profiler& p) : profiler(p), start(std::chrono::high_resolution_clock::now()) {}

	~ScopedProfiler() {
		auto end = std::chrono::high_resolution_clock::now();
		profiler.add(std::chrono::duration<double>(end - start).count());
	}
};



