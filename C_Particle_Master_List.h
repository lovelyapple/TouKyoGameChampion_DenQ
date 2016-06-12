//-----------------------------------------------------------
//C_PARTICLE_MASTER_LIST
//-----------------------------------------------------------
#ifndef C_PARTICLE_MASTER_LIST
#define C_PARTICLE_MASTER_LIST
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Input.h"
//--------------------------------------
//マスターズインクルード
#include "C_Patricle_Quark.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define MAX_PARTICLE_QUARK	(128)
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
class c_Particle_Master
{
public:
	c_Particle_Master();
	~c_Particle_Master();
	virtual void Init_Particle(LPCSTR FileName);
	virtual void Init_Particle(LPCSTR FileName,int nMaxFrame,int TimePerFrame);
	HRESULT CreateTexBuff_Particle(void);
	virtual void Uninit_Particle(void);
	virtual void Update_Particle(void);
	virtual void Draw_Particle(D3DBLEND Effect);
	virtual void SetVerTexBuff_Particle(void);
	virtual void CreateQuarkSingle(void);

private:
	LPDIRECT3DTEXTURE9		m_pD3DTexture;
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVertexBuffer;
	D3DXVECTOR3				m_vParticlePos;
	LPCSTR					m_lpzFileName;
	c_Quark*				m_pQuark[MAX_PARTICLE_QUARK];
	int						m_nMaxQuark;
	int						m_nMaxQuarkLife;
	int						m_nPatricleMaxFrame;
	int						m_nPatricleTimePerFrame;
	float					m_fPatricleAlpha;
	
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
