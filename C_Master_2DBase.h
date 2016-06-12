//============================================================================
//C_2D_Master.h
//============================================================================
#ifndef _C_2D_MASTER_H_
#define _C_2D_MASTER_H_
//-----------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//マクロ定義
#define NUM_VERTEX	(4)					//頂点数
#define NUM_POLYGON	(2)					//ポリゴン数

#define VALUE_BIG_ALPHA		(0.8f)
#define VALUE_LIGHT_ALPHA	(0.4f)

#define ALPHA_PERIOD		(2 * 60)
//----------------------------------
//構造体宣言
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// テクスチャのパースペクティブコレクト用
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;
typedef struct
{
	float x,y;
}TEX_SIZE;//-----------------------------------
//構造体宣言
typedef enum
{
	ALPHA_TYPE_SINWAVE = 0,
	ALPHA_TYPE_BIG,
	ALPHA_TYPE_LIGHT,
	ALPHA_TYPE_MAX,
}ALPHA_TYPE;
//----------------------------------
//クラス宣言
class c_2DMaster
{
public:
	c_2DMaster();
	~c_2DMaster();
	HRESULT MakeVertex(void);		
	void SetpTexture(LPDIRECT3DTEXTURE9 *pTexture);
	virtual void SetVerTex(void);
	virtual void Update(void);
	virtual void Uninit(void);
	virtual void Draw(void);
private:
protected:
	LPDIRECT3DTEXTURE9		m_pTexture;				//テクスチャメモリ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;				//バッファ
	D3DXVECTOR3				m_vPos;					//画面上の絶対座標
	D3DXVECTOR3				m_vMove;				//移動


	bool					m_bAnimation;			//アニメーションであるか
	int						m_nRecFrame;			//現在のフレーム数
	int						m_nMaxFrame;			//マックスフレーム数
	float					m_fFrameSize;			//フレームテクスチャサイズ
	TEX_SIZE				m_fTexSizeNor;			//倍率
	TEX_SIZE				m_fTexSizePro;			//絶対小数点
	int						m_nAlphaTime;			//現在のアルファ時間
	int						m_nAlphaPeriod;			//アルファ周期
	float					m_fAlpha;
};

//------------------------------------
//プロトタイプ宣言

#endif
//============================================================================
//End of  File
//============================================================================