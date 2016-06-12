//-----------------------------------------------------------
//PauseMenu
//-----------------------------------------------------------
#ifndef _C_PAUSE_MENU_H
#define _C_PAUSE_MENU_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "C_HUD_SelectionList.h"
#include "C_HUD_Selection.h"

#include "C_Game_Camera.h"
//-------------------------------------
//マクロ定義
typedef enum
{
	PAUSE_RETURN_TO_MENU = 0,
	PAUSE_OPTION,
	PAUSE_RETURN_TO_GAME,
	PAUSE_MAX,
}PAUSE_SELECT;
#define RANGE_FROM_CAMERA	(D3DXVECTOR3(-6.0f,-1.0f,5.0f))
#define DEFAULT_ROT_MENU	(D3DXVECTOR3(0.0f,-0.5f,0.0f))

//--------------------------------------
//クラス宣言
class c_PauseMenu
{
public:
	c_PauseMenu();
	~c_PauseMenu();
	void InitMenu(c_Game_camera* pos);
	void UpdateMenu(void);
	void DrawMenu(void);
	void UninitMenu(void);
	void RefreashPos(void);
	bool GetPause(void);



private:
	c_Game_camera*		g_pGameCamera;
	c_Selection*		m_pCursor;
	c_SelectionList*	m_pPauseList;

	int					m_nRecSelect;
	D3DXVECTOR3			m_vPos;
	bool				m_bPause;				//使用されているかどうか

	
};

#endif