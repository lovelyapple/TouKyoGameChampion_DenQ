//-----------------------------------------------------------
//�G�f�B�^�[���[�hMGR.h
//-----------------------------------------------------------
#ifndef _C_MGR_TITLE_H_
#define _C_MGR_TITLE_H_
//�V�X�e���C���N���[�h
#include "Sys_Input.h"
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Task_List.h"
#include "C_Mgr_Title_Mode.h"
#include "C_Game_Camera.h"
#include "C_Master_Mgr.h"
#include "C_Title_logo.h"
//--------------------------------------

class  c_Mgr_Title : c_Master_Mgr
{
	
public:
	c_Mgr_Title();
//�v���g�^�C�v�錾
void C_Mgr_Init(void);
void C_Mgr_Uninit(void);
void C_Mgr_Update(void);
void C_Mgr_Draw(void);

c_Game_camera*	m_pTitle_Camera;
c_Logo*			m_pTitle_Logo;
//private:

//protected:
};
#endif