//-----------------------------------------------------------
//�}�l�[�W���[�}�X�^�[�Y�N���X
//-----------------------------------------------------------
#ifndef _C_MASTER_MGR_H_
#define _C_MASTER_MGR_H_
//--------------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
//--------------------------------------
//�N���X�錾
class c_Master_Mgr
{
public:
	c_Master_Mgr();
	~c_Master_Mgr();
	virtual void C_Mgr_Init(void);
	virtual void C_Mgr_Uninit(void);
	virtual void C_Mgr_Update(void);
	virtual void C_Mgr_Draw(void);
private:
};
#endif