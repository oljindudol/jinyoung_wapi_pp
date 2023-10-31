#include "pch.h"
#include "CEntity.h"


UINT_PTR CEntity::g_NextID = 0;

CEntity::CEntity()
	:m_ID(g_NextID++)
	, m_bDead(false)
{
}

CEntity::CEntity(const CEntity& _other)
	:m_ID(g_NextID++)
	, m_bDead(false)
{

}

//const붙은 ID는 애초에 복사하지않는다.
//CEntity& CEntity::operator=(const CEntity& _other)
//{
//	
//}




CEntity::~CEntity()
{
}
