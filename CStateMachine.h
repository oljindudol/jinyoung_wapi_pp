#pragma once
#include "CComponent.h"
#include "CLogMgr.h"


class CState;
class CAnimator;
class CMovement;
class CCollider;


// FSM, Finite State Machine(유한 상태 기계)
class CStateMachine :
    public CComponent
{
private:
    map<UINT, CState*>  m_mapState;
    CState* m_pCurState;
    map<wstring, void*> m_mapBlackboard;
    CAnimator* m_pAnimator;
    CMovement* m_pMovement;
    CCollider* m_pCollider;
    bool m_forcedidle;

public:
    float GetCurstateAcctime();


    CState* GetCurState()
    {
        return m_pCurState;
    }


    UINT GetCurStateNum()
    {
        for (auto p : m_mapState)
        {
            if (p.second == m_pCurState)
                return p.first;
        }
        return 999;
    }


    CState* AddState(UINT _id, CState* _State);
    CState* FindState(UINT _id);
    void ChangeState(UINT _NextID);

    template<typename T>
    void AddDataToBlackboard(const wstring& _strKey, const T& _Data);

    void* GetDataFromBlackboard(const wstring _strKey);

    CAnimator* GetAnimatorComponent();

    CMovement* GetMoveMentComponent();
    CCollider* GetColliderComponent();
    bool GetForcedIdle(){ return m_forcedidle; }


public:
    virtual void finaltick(float _DT) override;


public:
    CLONE(CStateMachine);

    CStateMachine(CObj* _Owner);
    CStateMachine(const CStateMachine& _Origin);
    ~CStateMachine();

    friend class CMonsterMgr;
    friend class CNormalMonDebug;
};

template<typename T>
inline void CStateMachine::AddDataToBlackboard(const wstring& _strKey, const T& _Data)
{
    map<wstring, void*>::iterator iter = m_mapBlackboard.find(_strKey);
    if (iter != m_mapBlackboard.end())
    {
        LOG(LOG_LEVEL::ERR, L"!!블랙보드에 해당 데이터 키 이미 있음!!");
        return;
    }

    T* pData = new T;
    *pData = _Data;
    m_mapBlackboard.insert(make_pair(_strKey, pData));

}
