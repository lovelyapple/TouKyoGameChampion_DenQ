//-----------------------------------------------------------
//プレイヤークラス
//-----------------------------------------------------------
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
#include "Sys_Input.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Primitive.h"
#include "C_SYS_STAGE.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//インスタンスインクルード
#include "C_Game_Block.h"
//--------------------------------------
//マクロ定義
#define PLAYER_HEIGHT	(BLOCK_SIZE * 1.5 * 0.5f)
#define PLAYER_WIDTH	(BLOCK_SIZE * 1.0 * 0.5f)
#define FILE_NAME_PLAYER	("data/Texture/DenQ_Animation.png")
#define MAX_FRAME			(12)
#define FRAME_PER_TIME		(6)
#define VALUE_WALK_SPEED			(0.005f)
#define VALUE_WALK_MAX_SPEED		(0.06f)
#define VALUE_SPEED_ATTENUSUION		(0.92f)
#define VALUE_SPPED_RESET			(0.01f)
#define VALUE_DUSH_TIMES			(2)
#define VALUE_DUSH_FRAMETIMES		(6)
#define	VALUE_DUSH_SPEED			(VALUE_WALK_SPEED * VALUE_DUSH_TIMES)
#define VALUE_DUSH_MAX_SPEED		(VALUE_WALK_MAX_SPEED * VALUE_DUSH_TIMES)
#define VALUE_JUMP_MOVE_SPEED	(0.01)
#define VALUE_JUMP_MAX_MOVE_SPEED	(0.1)
#define VALUE_JUMP_SPEED	(0.33f)
#define PLAYER_MAX_HEAT			(100)
#define PLAYER_MAX_HEAT_TIME	(10 * 60)
#define PLAYER_HEAT_PER_TIME	((float)PLAYER_MAX_HEAT / (float)PLAYER_MAX_HEAT_TIME)
#define PLAYER_COOL_PER_TIME	((float)PLAYER_HEAT_PER_TIME * 0.7f)
const int g_FrameDislight[4] = {3,10,14,21};
//--------------------------------------
//構造体宣言
typedef enum
{
	MOVE_TYPE_WALK = 0,
	MOVE_TYPE_JUMP,
	//MOVE_TYPE_DUSH,
	//MOVE_TYPE_SLIDE,
	//MOVE_TYPE_DROPING,
	MOVE_TYPE_MAX,
}MOVE_TYPE;						//プレイヤーの行動状態
typedef struct{
	bool  bRTouch;
	bool  bLTouch;
	float fRDist;  
	float fLDist;
}PLAYER_WALK_STATE;
const PLAYER_WALK_STATE g_WalkState[MAX_FRAME / 2] = {{true, true, 0.2f, 0.2f},// 右側足、左側足、右側足距離、左側足距離
													 {true, true, 0.2f, 0.2f},// （※0～5のアニメーションは左右対象であること）
													 {true, true, 0.2f, 0.2f},
													 {true, true, 0.2f, 0.2f},
													 {true, true, 0.2f, 0.2f},
													 {true, true, 0.2f, 0.2f}};

//--------------------------------------
//クラス宣言
class c_Player : public c_Master_Primitive,public c_Physic
{
typedef struct{
bool  bTouched;
int	  nNearBox_X;
int   nNearBox_Y;
float nNearBoxDist;
}FOOT_STATS;
public:
	c_Player();
	c_Player(C_FIELDPLACE place);
	HRESULT	Init(void);
	void	Reset(void);								// データ初期化
	void	Update(void);								// 更新
	void	GronudTouchedCheck(void);					//
	int		MoveCheck(void);							//
	void	SetMoveTypeFrame(int nType,int MaxFrame);	//
	void	SetVerTxBuff(void);							// バッファ更新
	void	SetStage(c_Stage* pStage);					// 
	bool	GetLightSwitch(void);						// 点滅管理
	int		GetPlayerFrame(void);						// フレーム取得
	int		GetPlayerHeat(void);
	D3DXVECTOR3* GetPlayerSpeed(void);

	void    InitFootState(FOOT_STATS *Foot);
	bool	GetFootRTorF(void);
	bool	GetFootLTorF(void);
	D3DXVECTOR3* GetPlayerPosAdress(void);
private:
	D3DXVECTOR3			m_vAcceleration;	//加速度
	D3DXVECTOR3			m_vRecSpeed;		//現在の速度
	FOOT_STATS			m_uLeftFoot;		//左足タッチ
	FOOT_STATS			m_uRightFoot;		//右足タッチ
	//bool				m_bGravitCheck;		//重力
	bool				m_bDirection;		//左右の判定
	bool				m_bLighted;			//電灯フラグ
	int					m_nMaxFrame[MOVE_TYPE_MAX];
	int					m_nRecFrame;
	int					m_nTimeFrame;
	int					m_uMoveType;		//移動状態
	float				m_fHeat;			//温度
	float				m_vVerTexSizeH;
	float				m_vVerTexSizeW[MOVE_TYPE_MAX];	//プレイヤーフレームサイズ


	c_Stage*			m_pStage;
	bool				m_bAllTouched;		//アルファバージョン状態でのあたり接地判定
};
#endif