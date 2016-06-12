//============================================================================
//C_MGR_LIGHTR.h
//============================================================================
#ifndef _CLASS_LIGHT_MGR_H
#define _CLASS_LIGHT_MGR_H
//-----------------------------------
//�V�X�e���C���N���[�h
#include"Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
#include "C_Master_Light.h"
#include "C_Master_Mgr.h"
//-----------------------------------
//�}�N����`
#define MAX_LIGHT	(64)
const int g_Num_Light_Sun		= 1;
const int g_Num_Light_Player	= 2;
const int g_Num_Light_PlayerSub	= 3;
//-----------------------------------
//�N���X�錾
class c_Mgr_Light :public c_Master_Mgr
{
public:
	c_Mgr_Light();
	~c_Mgr_Light();
	void C_Mgr_Init(void);
	int	 GetLightNumber(void);
	void ClearAllLight(void);
	void UpdateLight(void);
	c_Light*	m_pCLight[MAX_LIGHT];

};

#endif