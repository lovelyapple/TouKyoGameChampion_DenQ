//-----------------------------------------------------------
//�^�X�N�V�X�e���}�X�^cpp
//-----------------------------------------------------------

#include "C_Master_Task.h"
c_Task::c_Task()
{
	m_pPrev		= NULL;
	m_pNext		= NULL;
	m_pStart	= NULL;
	m_pRecycle	= NULL;

	m_pPrev = m_pNext = this;
}

c_Task::c_Task(c_Task& pStart,c_Task& pRecycle)
{
	m_pPrev		= NULL;
	m_pNext		= NULL;
	m_pStart	= NULL;
	m_pRecycle	= NULL;

	m_pPrev = m_pNext = this;

	m_pStart	= &pStart;
	m_pRecycle	= &pRecycle;

}
c_Task::~c_Task()
{
	m_pPrev		= NULL;
	m_pNext		= NULL;
	m_pStart	= NULL;
	m_pRecycle	= NULL;
}
void c_Task::InitArray(void)
{
	m_pPrev = m_pNext = this;
}
//void c_Task::SetList(c_TaskList* List)
//{
//	m_pStart = List->GetActiveHead();
//	m_pRecycle = List->GetRecycleHead();
//	AddTask();
//}

void c_Task::SetList(c_Task& pStart,c_Task& pRecycle)
{
	m_pStart	= &pStart;
	m_pRecycle	= &pRecycle;
}

void c_Task::AddTask(void)
{
		//����������
	m_pNext	= m_pStart->m_pNext;
	m_pPrev	= m_pStart;

	//���X�g�O��̒���
	m_pStart->m_pNext->m_pPrev	= this;
	m_pStart->m_pNext			= this;
}
void c_Task::MoveOutFromActive(void)
{
	//���������X�g������o��
	m_pPrev->m_pNext	= m_pNext;//�O�I�u�W�F�N�g��Next�@�������̎��Ɏw��
	m_pNext->m_pPrev	= m_pPrev;//��I�u�W�F�N�g��Prev�@�������̑O�Ɏw��
}

void c_Task::MoveOut(void)
{
	//���������X�g������o��
	m_pPrev->m_pNext	= m_pNext;//�O�I�u�W�F�N�g��Next�@�������̎��Ɏw��
	m_pNext->m_pPrev	= m_pPrev;//��I�u�W�F�N�g��Prev�@�������̑O�Ɏw��

	//���������T�C�N���̒��ɓ����
	m_pRecycle->m_pNext->m_pPrev = this;
	m_pNext	= m_pRecycle->m_pNext;

	m_pRecycle->m_pNext = this;
	m_pPrev = m_pRecycle;
}
void c_Task::CleanArray(void)
{
	if(m_pPrev)
		m_pPrev = NULL;
	if(m_pNext)
		m_pNext = NULL;
	if(m_pStart)
		m_pStart = NULL;
	if(m_pRecycle)
		m_pRecycle = NULL;
}
void c_Task::UninitTask(void)
{
}
void c_Task::UpdateTask(void)
{
}
void c_Task::DrawTask(void)
{
}
