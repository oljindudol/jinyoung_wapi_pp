#include "pch.h"
#include "CThreadPoolMgr.h"

void CThreadPoolMgr::init()
{
	// I/O �ٿ�� �۾��������� ��*2�Ҵ�
	int threadCount = std::thread::hardware_concurrency() * 2;
	m_Stop = false;
	m_TaskCount = 0;

	for (size_t i = 0; i < threadCount; ++i) {
		//(�����Լ�) ���������� ť���ִ� �۾��� ��������
		m_Workers.emplace_back([this]() {
			while (true) {
				std::function<void()> task;

				{
					std::unique_lock<std::mutex> lock(m_QueueMutex);
					// ��ž�̰ų� �۾��������� ����
					m_Condition.wait(lock, [this]() {
						return m_Stop || !m_Tasks.empty();
						});

					//��ž�̰� �۾��̾����� ������ ����
					if (m_Stop && m_Tasks.empty()) {
						return;
					}

					//�۾������� ����
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
