//============================================================================
//_CRAFT_HUD_.h
//============================================================================
#ifndef _SYS_DATA_H_
#define _SYS_DATA_H_
//-----------------------------------
//�V�X�e���C���N���[�h
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"

//-----------------------------------
//�}�X�^�[�Y�C���N���[�h
//-----------------------------------
//�C���X�^���X�C���N���[�h
//-----------------------------------
//�}�N���Ӌ`
#define FILE_NAME_BLOCK_DATA	("../data/Sys_Data/Data_Block.scv")
//-----------------------------------
//�v���g�^�C�v�錾
void	Init_Data(void);
HRESULT	LoadSys_Data(void);
void SetBlockStats(c_Block* Block);

#endif