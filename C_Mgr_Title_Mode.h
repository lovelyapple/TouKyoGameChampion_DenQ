//-----------------------------------------------------------
//エディターモードMGR.h
//-----------------------------------------------------------
#ifndef _C_MGR_TITLE_H_
#define _C_MGR_TITLE_H_
//システムインクルード
#include "Sys_Input.h"
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//マスターズインクルード
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
//プロトタイプ宣言
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