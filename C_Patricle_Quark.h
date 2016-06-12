//-----------------------------------------------------------
//C_PARTICLE_QUARK_H
//-----------------------------------------------------------
#ifndef C_PARTICLE_QUARK_H
#define C_PARTICLE_QUARK_H
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define VALUE_PATRICLE_MAX_LIFE (4 * 60)
//--------------------------------------
//構造体宣言
typedef enum
{
	QUARK_MOVE_MODE_KEEP_ORIGIN = 0,
	QUARK_MOVE_MODE_MOVE_A,
	QUARK_MOVE_MODE_KEEP_A,
	QUARK_MOVE_MODE_MOVE_B,
	QUARK_MOVE_MODE_KEEP_B,
	QUARK_MOVE_MODE_MOVE_RETURN,
	QUARK_MOVE_MODE_MAX,
}QUARK_MOVE_MODE;
typedef enum
{
	QUARK_STATS_POS = 0,
	QUARK_STATS_ROT,
	QUARK_STATS_SIZE,
	QUARK_STATS_SPEED,
	QUARK_STATS_MAX,

	QUARK_STATS_MAX_TIME,
	QUARK_STATS_STOP_TIME,
	QUARK_STATS_FRAMETIME,
	QUARK_STATS_MAX_FRAME,
	QUARK_STATS_MOVE_MODE,

	QUARK_STATS_USE,
	QUARK_STATS_RECYCLE,
	QUARK_STATS_WATCH,

	QUARK_STATS_ALPHA,
	QUARK_STATS_USIZE,
}QUARK_STATS;
//--------------------------------------
//クラス宣言
class c_Quark
{
public:
	c_Quark();
	~c_Quark();
	void	InitQuarkStatus(void);
	HRESULT CreateQuarkTexBuff(void);
	void	UninitQuark(void);
	void	UpdateQuark(void);
	void	UpdateQuarkMatrix(void);

	void	Set_Quark_Stats(QUARK_STATS,D3DXVECTOR3 vInput);
	void	Set_Quark_Stats(QUARK_STATS,int vInput);
	void	Set_Quark_Stats(QUARK_STATS,bool bInput);
	void	Set_Quark_Stats(QUARK_STATS,float fInput);
	D3DXVECTOR3		m_vPos;			//
	D3DXVECTOR3		m_vOriginPos;	//最初のPOS
	D3DXVECTOR3		m_vRot;			//
	D3DXVECTOR3		m_vSize;		//
	D3DXVECTOR3		m_vSpeed;
	D3DXMATRIX		m_mMatrix;		//
	bool			m_bUse;
	bool			m_bWatchCamera;	//
	bool			m_bRecycle;		//アクティブタイプ(自動か手動
	float			m_fAlpha;
	float			m_fVerTexUSize;
	int				m_nVerTexFrame;
	int				m_nLife;
	int				m_nRecTime;		//現在時間
	int				m_nMaxTime;		//最大時間
	int				m_nStopTime;	//停止時間
	int				m_nTimePerFrame;//TimeFrame Per AnimationFrame
	int				m_nMaxFrame;	//MAX Frame
	int				m_nRecFrame;	//Recent Frame
	int				m_nMoveMode;	//移動中のモード
	
	int				m_nMoveStep[QUARK_STATS_MAX];
	D3DXVECTOR3		m_vDestPosAndSpeed[QUARK_STATS_MAX];		//目標Pos
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