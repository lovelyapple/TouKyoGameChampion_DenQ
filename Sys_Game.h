//=======================================================================================
//game cpp
//=======================================================================================
#ifndef _SYS_GAME_H_
#define _SYS_GAME_H_
#include "Sys_Include.h"
//-------------------------------------------------------
//�\���̐錾
typedef enum
{
	GAME_MODE_TITLE = 0,
	GAME_MODE_EDITOR,
	GAME_MODE_PLAY,
	GAME_MODE_CHANGING,
	GAME_MODE_MAX,
}GAME_MODE;
//-------------------------------------------------------
//�v���ƃ^�C�v�錾
//-------------------------------------------------------
HRESULT Initgame(void);
void Updategame(void);
void Uninitgame(void);
void Drawgame(void);
#endif
