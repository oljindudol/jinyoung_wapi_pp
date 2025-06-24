#pragma once

#include <string>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include <mutex>

class CProfileMgr {
public:
	static CProfileMgr& GetInst();

	void Start(const std::string& label);
	void End(const std::string& label);
	void Print();
	void Print(const std::string& label);
	void Reset();

private:
	CProfileMgr() = default;

	struct ProfileData {
		double total = 0.0;
		int count = 0;
		std::chrono::high_resolution_clock::time_point start;
	};

	std::unordered_map<std::string, ProfileData> m_Data;
	std::mutex mtx;
};


class CScopedProfile {
public:
	CScopedProfile(const std::string& label);
	~CScopedProfile();

private:
	std::string m_Label;
};

#define PROFILE_SCOPE(name) CScopedProfile scoped_profile_##__LINE__(name)


