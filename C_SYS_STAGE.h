//-----------------------------------------------------------
//�X�e�[�W�N���X
//-----------------------------------------------------------
#ifndef _C_STAGE_H_
#define _C_STAGE_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//--------------------------------------
//�C���X�^���X�C���N���[�h
#include "C_Game_Block.h"
#include "C_Master_Task_List.h"
//--------------------------------------
//�}�N����`
#ifndef _FIELD_SIZE_			//���Ԃ�SysMacro�̒��ɐݒ肵�Ă���

#define MAX_FIELD_WIDTH		(50)
#define MAX_FIELD_HEIGHT	(20)

#endif
#define DEFAULT_FILE_NAME_STAGE		("data/Sys_Data/DefaultStage.csv")
#define MAX_STAGE		(3)

//--------------------------------------
//�N���X�錾
class c_Stage
{
public:
	c_Stage(c_TaskList* List,C_FIELDPLACE player);		//�R���X�g���N�^
	~c_Stage();											//�f�X�g���N�^
	void CreatBlockSingle(C_FIELDPLACE Place,int nType);//�u���b�N�̐���
	void ClearBlockSingle(C_FIELDPLACE Place);			//�P�̂̃u���b�N�폜
	HRESULT SaveStage(void);							//�X�e�[�W�̕ۑ�
	HRESULT LoadStage(void);							//�X�e�[�W�̃��[�h
	void	SetStageName(LPCSTR Name);					//�X�e�[�W���̐ݒ�
	void	ClearAllBlock(void);						//�O�u���b�N�N���A
	void	InitAllBlock(void);
	c_Block*		m_uBlock[MAX_FIELD_HEIGHT][MAX_FIELD_WIDTH];
private:
	
	c_TaskList*		m_uTaskList;
	LPCSTR			m_lpzStageName;
	C_FIELDPLACE	m_uPlayerPlace;
protected:
	

};
#endif