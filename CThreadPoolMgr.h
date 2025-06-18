#pragma once

#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

using namespace std;

class CThreadPoolMgr
{
private:
	CThreadPoolMgr(const CThreadPoolMgr&) = delete;
	CThreadPoolMgr& operator=(const CThreadPoolMgr&) = delete;
	CThreadPoolMgr() {};
	~CThreadPoolMgr() {
		Shutdown();
	}

	//������ Ǯ
	vector<thread> m_Workers;
	//������ ����¿�
	condition_variable m_Condition;
	//�۾�ť
	queue<function<void()>> m_Tasks;
	//�۾�ť���ؽ�
	mutex m_QueueMutex;
	//
	atomic<bool> m_Stop = false;
	atomic<int> m_TaskCount = 0;
public:
	static CThreadPoolMgr* GetInst() {
		static CThreadPoolMgr instance;
		return &instance;
	}
	void init();
	void Shutdown();
	void WaitAll();

	template <typename F>
	void Enqueue(F&& f) {
		{
			unique_lock<mutex> lock(m_QueueMutex);
			m_Tasks.emplace(forward<F>(f));
			++m_TaskCount;
		}
		m_Condition.notify_one();
	}
};