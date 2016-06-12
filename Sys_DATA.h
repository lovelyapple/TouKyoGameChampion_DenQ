//============================================================================
//_CRAFT_HUD_.h
//============================================================================
#ifndef _SYS_DATA_H_
#define _SYS_DATA_H_
//-----------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"

//-----------------------------------
//マスターズインクルード
//-----------------------------------
//インスタンスインクルード
//-----------------------------------
//マクロ意義
#define FILE_NAME_BLOCK_DATA	("../data/Sys_Data/Data_Block.scv")
//-----------------------------------
//プロトタイプ宣言
void	Init_Data(void);
HRESULT	LoadSys_Data(void);
void SetBlockStats(c_Block* Block);

#endif