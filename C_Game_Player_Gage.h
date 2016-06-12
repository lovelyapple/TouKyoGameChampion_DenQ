//-----------------------------------------------------------
//プレイヤーのヒートケージ
//-----------------------------------------------------------
#ifndef	_C_PLAYER_CAGE_H_
#define _C_PLAYER_CAGE_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Primitive.h"
#include "C_Game_Player.h"
#include "C_Game_Camera.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define FILE_NAME_HEAT_BG		("data/Texture/Gage_BG.png")
#define FILE_NAME_HEAT_ENTITY	("data/Texture/Gage_Entity.png")
#define FILE_NAME_HEAT_FACE		("data/Texture/Gage_Mark.png")
#define FILE_NAME_HEAT_MARKBG	("data/Texture/Player_MarkBG.png")
typedef enum
{
	HEAT_LEVEL_LOW = 0,
	HEAT_LEVEL_NORMAL,
	HEAT_LEVEL_HIGH,
	HEAT_LEVEL_MAX,
}PLAYER_HEAT_LEVEL;
typedef enum
{
	MARK_MODE_KEEP = 0,
	MARK_MODE_CHANGE,
	MARK_MODE_SHINING,
	MARK_MODE_MAX,
}MARK_MODE;
#define HEAT_TEX_COLOR_LEVEL	(30)
#define PLAYER_HEAT_SIZE_X		(5.0f)
#define PLAYER_HEAT_SIZE_Y		(0.1f)
#define MARK_CHANGE_TIME		(0.5f * 60)
#define TEXSIZE_PER_HEAT		(PLAYER_HEAT_SIZE_X / PLAYER_MAX_HEAT)
const int	g_nHeatLevel[2]	= {PLAYER_MAX_HEAT * 0.2,PLAYER_MAX_HEAT*0.8};

const D3DXVECTOR3 HeatCageOblique	= D3DXVECTOR3(0.5f,0.0f,0.0f);
const D3DXVECTOR3 HeatBGSize		= D3DXVECTOR3(PLAYER_HEAT_SIZE_X,PLAYER_HEAT_SIZE_Y,0.0f);
const D3DXVECTOR3 HeatBGPos			= D3DXVECTOR3(-6.5f,3.5f,7.0f);
const D3DXVECTOR3 HeatEntitySIze	= D3DXVECTOR3(PLAYER_HEAT_SIZE_X * 0.95f,PLAYER_HEAT_SIZE_Y * 0.9f,0.0f);
const D3DXVECTOR3 HeatEntityPos		= HeatBGPos;
const D3DXVECTOR3 HeatFaceSize		= D3DXVECTOR3(0.6f,0.6f,0.0f);
const D3DXVECTOR3 HeatFacePos		= D3DXVECTOR3(HeatBGPos.x - HeatFaceSize.x,HeatBGPos.y,HeatBGPos.z);
const D3DXVECTOR3 HeatFaceBGPos		= HeatFacePos;
const D3DXVECTOR3 HeatFaceBGSize	= HeatFaceSize * 1.4f;	
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Player_heat
{
public:
	c_Player_heat();
	void InitPlayerHeat(c_Game_camera* Camera,c_Player* player);
	void UpdatePlayerHeat(void);
	void UninitPlayerHeat(void);
	void DrawPlayerHeat(void);
	int  GetPlayerHeat(void);
	void SetPlayerHeat(int ChaneValue);

private:
	c_Master_Primitive*				m_pHeatBG;
	c_Master_Primitive*				m_pHeatEntity;
	c_Master_Primitive*				m_pHeatMark;
	c_Master_Primitive*				m_pHeatMarkBG;

	D3DXVECTOR3						m_HeatPos;
	c_Game_camera*					m_pCamera;
	int								m_nRecHeat;

	c_Player*						m_pPlayer;
	float							m_fAlpha;

	int								m_nChangeTime;
	int								m_nBeforeLevel;
	int								m_nRecLevel;
	int								m_nMarkMode;


};

//--------------------------------------
//オブジェクトグローバル変数宣言
//--------------------------------------
//係数グローバル変数宣言
//--------------------------------------
//プロトタイプ宣言
//--------------------------------------
//初期化処理
//--------------------------------------
//終了処理
//--------------------------------------
//更新処理
//--------------------------------------
//描画処理
#endif