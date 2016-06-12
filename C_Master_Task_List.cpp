//============================================================================
//TaskList.h
//============================================================================
//-----------------------------------
//�V�X�e���C���N���[�h
#include "C_Master_Task_List.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
//-----------------------------------
//�C���X�^���X�C���N���[�h
c_TaskList::c_TaskList()
{
	InitTaskList();
}
c_TaskList::~c_TaskList()
{
}
void c_TaskList::InitTaskList(void)
{
	m_pActive.InitArray();
	m_pRecycle.InitArray();
}
void c_TaskList::UninitTaskList(void)
{
	//�c�������̂����ׂă��T�C�N�����X�g�̒��ɓ����
	for(c_Task* pActive	= m_pActive.m_pNext;
		pActive != &m_pActive;)
	{
		c_Task* Backup = pActive->m_pNext;
		pActive->MoveOut();
		pActive = Backup;
	}
	//���T�C�N���������s
	RunRecycleList();

	//���S�J��
	if(&m_pActive)
	{
		m_pActive.CleanArray();
	}
	if(&m_pRecycle)
	{
		m_pRecycle.CleanArray();
	}
}
void c_TaskList::RunActiveList(void)
{
#ifdef _DEBUG
	int nCntTask = 0;
#endif

	for(c_Task* pActive	= m_pActive.m_pNext;
		pActive != &m_pActive;)
	{
		c_Task* Backup = pActive->m_pNext;
		pActive->UpdateTask();
		pActive = Backup;
#ifdef _DEBUG
		 nCntTask++;
#endif
	}
}
void c_TaskList::RunRecycleList(void)
{
#ifdef _DEBUG
	int nCntRecycle = 0;
#endif

	for(c_Task* pActive = m_pRecycle.m_pNext;
		pActive != &m_pRecycle;)
	{

#ifdef _DEBUG
		nCntRecycle++;
#endif
		c_Task* Backup = pActive->m_pNext;
		m_pRecycle.m_pNext = pActive->m_pNext;//���T�C�N�����g�̎w�����C��
		pActive->m_pNext->m_pPrev = &m_pRecycle;

		pActive->CleanArray();
		pActive->UninitTask();
		SAFE_DELETE( pActive);
		pActive = Backup;
	}
}
void c_TaskList::DrawTaskList(void)
{
	for(c_Task* pActive = m_pActive.m_pNext;
		pActive!= &m_pActive;
		pActive	= pActive->m_pNext)
	{
		pActive->DrawTask();
	}
}


