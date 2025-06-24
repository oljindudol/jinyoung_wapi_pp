#include "pch.h"
#include "CProfileMgr.h"

#include "CProfileMgr.h"

CProfileMgr& CProfileMgr::GetInst() {
	static CProfileMgr instance;
	return instance;
}

void CProfileMgr::Start(const std::string& label) {
	std::lock_guard<std::mutex> lock(mtx);
	m_Data[label].start = std::chrono::high_resolution_clock::now();
}

void CProfileMgr::End(const std::string& label) {
	auto end = std::chrono::high_resolution_clock::now();
	std::lock_guard<std::mutex> lock(mtx);
	auto& data = m_Data[label];
	std::chrono::duration<double> duration = end - data.start;
	data.total += duration.count();
	++data.count;
}

void CProfileMgr::Print() {
	std::lock_guard<std::mutex> lock(mtx);
	for (const auto& [label, data] : m_Data) {
		double avg = (data.count > 0) ? data.total / data.count : 0.0;
		std::cout << label << " - total: " << data.total << " s, count: " << data.count << ", avg: " << avg << " s\n";
	}
}

void CProfileMgr::Print(const std::string& label) {
	std::lock_guard<std::mutex> lock(mtx);
	auto it = m_Data.find(label);
	if (it != m_Data.end()) {
		const auto& data = it->second;
		double avg = (data.count > 0) ? data.total / data.count : 0.0;
		std::cout << label << " - total: " << data.total << " s, count: " << data.count << ", avg: " << avg << " s\n";
	}
}

void CProfileMgr::Reset() {
	std::lock_guard<std::mutex> lock(mtx);
	m_Data.clear();
}

// CScopedProfile.cpp
CScopedProfile::CScopedProfile(const std::string& label) : m_Label(label) {
	CProfileMgr::GetInst().Start(m_Label);
}

CScopedProfile::~CScopedProfile() {
	CProfileMgr::GetInst().End(m_Label);
}