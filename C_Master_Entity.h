//-----------------------------------------------------------
//エンティティ　マスターズクラスH
//-----------------------------------------------------------
#ifndef C_ENTITY_MASTER_H
#define C_ENTITY_MASTER_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "C_SYS_STAGE.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Primitive.h"
#include "Sys_C_Physic.h"
#include "C_Game_Player.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define ENTITY_DOOR_SPEED		(0.02f)
const	int FinishPointNum	= 0;
//--------------------------------------
//構造体宣言
typedef enum
{
	ENTITY_STATE_USE = 0,			//使用可能か
	ENTITY_STATE_TYPENAME,			//この実体のタイプ名前
	ENTITY_STATE_TRIGGER_TYPE,		//発動タイプ
	ENTITY_STATE_HITBOX,			//ヒットボックス
	ENTITY_STATE_MOVE,				//移動可能か
	ENTITY_STATE_ANIMATED,			//アニメーション
	ENTITY_STATE_TIME,				//現在のフレーム時間
	ENTITY_STATE_PLACE,				//フィールド座標
	ENTITY_STATE_POS,				//D3D座標(Primitive_SetPos同様)
	ENTITY_STATE_SIZE,				//大きさ(Primitive_SetSize同様)
	ENTITY_STATE_SPEED,				//速度の指定(方向込)
	ENTITY_STATE_DIRECTOIN,			//方向
	ENTITY_STATE_DESTPOS,			//最終移動位置(例えばドアの場合、閉まっている状態は最終位置)
	ENTITY_STATE_MOTHER,			//母親のアドレス
	ENTITY_STATE_TARGET,			//子供のアドレス
	ENTITY_STATE_PLAYER_P,			//プレイヤーポインタ
	ENTITY_STATE_MAX,				//制御
}ENTITY_BASE_STATS;
typedef enum
{
	ENTITY_NAME_TRIGGER = 0,
	ENTITY_NAME_FINISH_POINT,
	ENTITY_NAME_DOOR_AUTO_UP,
	ENTITY_NAME_DOOR_AUTO_DOWN,
	ENTITY_NAME_DOOR_TRIGGER_UP,
	ENTITY_NAME_DOOR_TRIGGER_DOWN,
	ENTITY_NAME_MAX,

}ENTITY_TYPE_NAME;
typedef enum
{
	ENTITY_MOVE_MODE_KEEP_A	= 0,
	ENTITY_MOVE_MODE_MOVE_A,
	ENTITY_MOVE_MODE_KEEP_B,
	ENTITY_MOVE_MODE_MOVE_B,
	ENTITY_MOVE_MODE_RESET,
	ENTITY_MOVE_MODE_MAX,
}ENTITY_MOVE_MODE;
typedef enum
{
	TRIGGER_TYPE_AUTO = 0,		//全自動
	TRIGGER_TYPE_SEMI,			//半自動
	TRIGGER_TYPE_MANUAL,		//手動
	TRIGGER_TYPE_MAX,
}TRIGGER_TYPE;
typedef struct
{
	C_FIELDPLACE	s_uPlace;				
}ENTITY_STRUCT;
//--------------------------------------
//クラス宣言
class c_Master_Entity : public c_Master_Primitive ,public  c_Physic
{

public:
	c_Master_Entity();
	~c_Master_Entity();
	void ResetMasterStats(void);
	void UninitEntity(void);
	bool Entity_HitPlayerChecker(void);
	void Entity_PlayerExclusion(void);
	void Entity_Draw(void);
	virtual void UpdateEntity(void);

	void Entity_Move(void);

	void SetEntityBaseState(ENTITY_BASE_STATS, bool bInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, int	 nInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, D3DXVECTOR3 vInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, c_Master_Entity* pInput);
	void SetEntityBaseState(ENTITY_BASE_STATS, c_Player* pPlayer);
	void SetEntityBaseState(ENTITY_BASE_STATS, C_FIELDPLACE place);

	c_Master_Entity* GetThisEntity(void);

protected:

	
	int				m_nTime;
	int				m_nMaxTime;
	int				m_nMoveMode;
	D3DXVECTOR3		m_vSpeed;
	D3DXVECTOR3		m_vDriection;
	D3DXVECTOR3		m_vDestPos;
	//primitive の中に　必要な基本設定 size pos がある
	//アップデーター
	bool			m_bUse;			//使用可能
	TRIGGER_TYPE	m_nTriggerType;		//発動方法
	bool			m_bTriggered;	//誘発フラグ
	bool			m_bHitBox;		//境界ボックス
	bool			m_bMove;		//移動
	bool			m_bAnimated;	//アニメーションあ
	bool			m_bActive;		//発動中
private:
	
	C_FIELDPLACE			m_uPlace;
	ENTITY_TYPE_NAME		m_uTypeName;

	c_Master_Entity*		m_pMum;
	c_Master_Entity*		m_pTargetEntity;
	c_Player*				m_pPlayer;
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