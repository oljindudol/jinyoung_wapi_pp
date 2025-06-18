#include "pch.h"
#include "CThreadPoolMgr.h"

void CThreadPoolMgr::init()
{
	// I/O 바운드 작업기준으로 논쓰*2할당
	int threadCount = std::thread::hardware_concurrency() * 2;
	m_Stop = false;
	m_TaskCount = 0;

	for (size_t i = 0; i < threadCount; ++i) {
		//(람다함수) 루프를돌며 큐에있는 작업을 빼서실행
		m_Workers.emplace_back([this]() {
			while (true) {
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(m_QueueMutex);
					// 스탑이거나 작업이있으면 깨움
					m_Condition.wait(lock, [this]() {
						return m_Stop || !m_Tasks.empty();
						});

					//스탑이고 작업이없으면 스레드 종료
					if (m_Stop && m_Tasks.empty()) {
						return;
					}

					//작업있으면 실행
					task = std::move(m_Tasks.front());
					m_Tasks.pop();
				}

				task();
				--m_TaskCount;
			}
			});
	}

}

void CThreadPoolMgr::Shutdown()
{
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);
		m_Stop = true;
	}

	m_Condition.notify_all();
	for (std::thread& worker : m_Workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}

	m_Workers.clear();
}

void CThreadPoolMgr::WaitAll()
{
	while (m_TaskCount > 0) {
		this_thread::yield();
	}
}
