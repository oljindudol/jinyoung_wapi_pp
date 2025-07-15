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
	// �̱��� �ν��Ͻ� ����
	static CDecodeThreadPool* GetInst();

	void Init(int numThreads = 12 * 3);  // ���ڵ� ���� ������Ǯ
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

