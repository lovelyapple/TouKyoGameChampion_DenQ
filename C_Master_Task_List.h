//-----------------------------------------------------------
//�^�X�N���X�gh
//-----------------------------------------------------------
#ifndef _TASK_LIST_H
#define _TASK_LIST_H
//-----------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Task.h"

class c_TaskList
{
public:
	c_TaskList();
	~c_TaskList();
	void	InitTaskList(void);
	void	UninitTaskList(void);
	void	RunActiveList(void);
	void	RunRecycleList(void);
	void	DrawTaskList(void);
	c_Task	m_pActive;
	c_Task	m_pRecycle;
private:

};

#endif