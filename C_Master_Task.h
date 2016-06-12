//-----------------------------------------------------------
//�^�X�N�V�X�e���}�X�^h
//-----------------------------------------------------------
#ifndef _TASK_H_
#define _TASK_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
class c_Task
{
public:	
	c_Task();
	c_Task(c_Task& pStart,c_Task& pRecycle);		//�R���X�g���N�^
	~c_Task();										//�f�X�g���N�^
	//void SetList(c_TaskList* List);
	void SetList(c_Task& pStart,c_Task& pRecycle);	//���X�g���Z�b�g����
	void InitArray(void);	//�|�C���^������������
	void AddTask(void);		//�^�X�N���A�N�e�B�u���X�g�ɑ}��
	void CleanArray(void);	//�����̎w���A�h���X���N���A����
	void MoveOutFromActive(void);//�A�N�e�B�u���X�g���獪�P��
	void MoveOut(void);		//�A�N�e�B�u���X�g���烊�T�C�N�����X�g�ֈړ�

	virtual void UpdateTask();
	virtual void DrawTask();	
	virtual void UninitTask();	


	c_Task* m_pPrev;		//�O�̃N���X�ւ̃|�C���^
	c_Task* m_pNext;		//��̃N���X�ւ̃|�C���^
	c_Task* m_pStart;		//�A�N�e�B�u�ւ̃|�C���^
	c_Task* m_pRecycle;		//���T�C�N���ւ̃|�C���^

private:
protected:
};
#endif

