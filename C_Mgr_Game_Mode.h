//-----------------------------------------------------------
//エディターモードMGR.h
//-----------------------------------------------------------
#ifndef _MGR_EDITOR_H_
#define _MGR_EDITOR_H_
//--------------------------------------
//システムインクルード
//--------------------------------------
//マスターズインクルード
#include "C_Master_Mgr.h"
#include "C_Master_Font.h"
#include "C_Master_Entity.h"
#include "C_SYS_STAGE.h"
#include "C_Master_Task_List.h"
#include "Sys_Shader.h"
//--------------------------------------
//インスタンスインクルード
#include "C_Game_Camera.h"
#include "C_Game_Block.h"
#include "C_Game_BackGround.h"
#include "C_Game_Player.h"
#include "C_Game_Player_Effect.h"
#include "C_Game_Player_Gage.h"
//--------------------------------------
//
#include "C_Mgr_Light_Sys.h"
#include "C_Mgr_Field_Item.h"
//--------------------------------------
//マクロ定義
#define MIN_PLAYER_LIGHT_VALUE	(2.0f)
#define MAX_PLAYER_LIGHT_VALUE	(10.0f)
#define PLAYER_LIGHT_CHANGE		(0.05f)
//--------------------------------------
//クラス宣言
class c_Mgr_Game_Mode:public c_Master_Mgr
{
public:
	void C_Mgr_Init(c_Game_camera* camera);
	void C_Mgr_Uninit(void);
	void C_Mgr_Update(void);
	void C_Mgr_Draw(void);
	void SetLightSys(c_Mgr_Light* LightSys);
	int GetIniputBLockMove(void);
	void ShaderSetLight(void);
	void DebugDraw(void);
	void SetGameMode(int mode);

	c_Block*		m_pActiveBlock;
	c_TaskList*		m_pBlockList;
	c_Stage*		m_pStage;
	c_Game_camera*	m_pCamera;
	c_StageBG*		m_pBackGround;
	c_Mgr_Light*	m_pLightMgr;
	c_Player*		m_pPlayer;
	c_PlayerLight*	m_pPlayerEffect;
	c_Player_heat*	m_pPlayerCage;
	c_Font*			m_pFont;
	c_Mgr_Field_Item*	m_pMgr_Item;
private:
	int				m_bGameMode;
	float			m_fLightRange;

};
#endif