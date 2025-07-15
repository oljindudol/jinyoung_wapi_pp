#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>

class CDecodeThreadPool
{
public:
	// 싱글턴 인스턴스 접근
	static CDecodeThreadPool* GetInst();

	void Init(int numThreads = 12 * 3);  // 디코딩 전용 스레드풀
	void Enqueue(std::function<void()> task);
	void WaitAll();
	void Shutdown();

private:
	CDecodeThreadPool() = default;
	~CDecodeThreadPool();

	CDecodeThreadPool(const CDecodeThreadPool&) = delete;
	CDecodeThreadPool& operator=(const CDecodeThreadPool&) = delete;

private:
	std::vector<std::thread> m_Workers;
	std::queue<std::function<void()>> m_Tasks;

	std::mutex m_Mutex;
	std::condition_variable m_CondVar;
	bool m_Stop = false;
	int m_TaskCount = 0;
};

