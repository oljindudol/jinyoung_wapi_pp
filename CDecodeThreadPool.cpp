#include "pch.h"
#include "CDecodeThreadPool.h"

CDecodeThreadPool* CDecodeThreadPool::GetInst()
{
	static CDecodeThreadPool instance;
	return &instance;
}

void CDecodeThreadPool::Init(int numThreads)
{
	m_Stop = false;
	m_TaskCount = 0;

	for (int i = 0; i < numThreads; ++i)
	{
		m_Workers.emplace_back([this]() {
			while (true)
			{
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(m_Mutex);
					m_CondVar.wait(lock, [this]() {
						return m_Stop || !m_Tasks.empty();
						});

					if (m_Stop && m_Tasks.empty())
						return;

					task = std::move(m_Tasks.front());
					m_Tasks.pop();
				}

				task();

				{
					std::lock_guard<std::mutex> lock(m_Mutex);
					--m_TaskCount;
				}
			}
			});
	}
}

void CDecodeThreadPool::Enqueue(std::function<void()> task)
{
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Tasks.push(std::move(task));
		++m_TaskCount;
	}
	m_CondVar.notify_one();
}

void CDecodeThreadPool::WaitAll()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		if (m_TaskCount <= 0 && m_Tasks.empty())
			break;

		lock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void CDecodeThreadPool::Shutdown()
{
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_Stop = true;
	}
	m_CondVar.notify_all();

	for (std::thread& t : m_Workers)
		if (t.joinable())
			t.join();

	m_Workers.clear();
}

CDecodeThreadPool::~CDecodeThreadPool()
{
	Shutdown();
}
