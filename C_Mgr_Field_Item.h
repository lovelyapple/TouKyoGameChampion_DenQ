//-----------------------------------------------------------
//C_MGR_FIELD_ITEM
//-----------------------------------------------------------
#ifndef C_MGR_FIELD_ITEM_H
#define C_MGR_FIELD_ITEM_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Entity.h"
#include "C_Game_Player.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define MAX_ENTITY		(128)
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Mgr_Field_Item
{
public:
	c_Mgr_Field_Item(c_Player* pPlayer);
	void Init_MGR_Entity(void);
	void Uninit_MGR_Entity(void);
	void Update_MGR_Entity(void);
	void Draw_MGR_Entity(void);
	int  CreateEntity(C_FIELDPLACE place, 
							int nType,bool bUserTrigger,long lParam);
	c_Master_Entity*	m_pEntity[MAX_ENTITY];
private:
	c_Player*	m_pPlayer;

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