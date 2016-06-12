//============================================================================
//Ship.h
//============================================================================
#ifndef _CLASS_MASTER_PRIMITIVE_H_
#define _CLASS_MASTER_PRIMITIVE_H_
//-----------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Global_Variable.h"
#include "Sys_Macro.h"
//-----------------------------------
//マスターズインクルード
//-----------------------------------
//インスタンスインクルード
//-----------------------------------
//マクロ定義
#define FILE_NAME_DEAULT_PRIMITIVE		("data/Texture/denkyu.png")
//-----------------------------------
//構造体宣言
#ifndef DVERTEX_PRIMITIVE_3D
#define DVERTEX_PRIMITIVE_3D
typedef struct  
{	
	float		x, y, z;		// 頂点
	float		nx, ny, nz;		// 法線ベクトル
	D3DCOLOR	color;			// ディフューズカラー
	float		tu, tv;			// テクスチャ座標
}DVERTEX_PRIMITIVE;
#endif
//-----------------------------------
//クラス宣言
class c_Master_Primitive
{
public:
	c_Master_Primitive();
	c_Master_Primitive(LPCSTR fzName);	// コンストラクタ
	~c_Master_Primitive();				// デストラクタ
	void	SetFileName(LPCSTR fzName);
	void	ResetPrimitive(void);
	virtual HRESULT Init(void);			// 初期化
	virtual	void	Uninit(void);		// 終了処理
	virtual void	Release(void);		// 開放

	virtual void	SetPos(D3DXVECTOR3 Pos);				// Posの変更
	virtual void	SetSize(D3DXVECTOR3 size);
	virtual void	SetRot(D3DXVECTOR3 Ros);				// Rotの変更
	virtual void	SetVerTexBuff(void);					// バッファ変更
	virtual void	SetVerTexBuffUV(void);					//
			void	SetVerTexBuffAlpha(float Alpha);		// 	
	virtual	void	UpdatePrimitive(void);					// 更新
	virtual void	UpdateCageStyle(void);					// ケージスタイル型更新
	virtual void	SetVerTexBuffCageStylePos(void);		// ケージスタイル描画設定
			void	SetOblique(D3DXVECTOR3* input);			//斜め度合の設定
			void	SetTexUV(D3DXVECTOR3 UV);				//UVサイズの設定
			void	SetTexRecUVFrame(int nFrameX,int nFrameY);	//UVフレームの設定
	void			SetWatchCamera(bool input);				//カメラ注視設定
	virtual void	DrawPrimitive();						// 描画
			void	DrawAntialiasing(void);//アンチエリアシング描画
			void	DrawPrimitiveOtherTexture(LPDIRECT3DTEXTURE9 pD3DTexture);

	D3DXMATRIX		GetMatrix(void);
	D3DXVECTOR3		GetPos(void);
	D3DXVECTOR3		GetSize(void);
protected:
	D3DXVECTOR3						m_vPos;			// 
	D3DXVECTOR3						m_vRot;			//
	D3DXMATRIX						m_mMatrix;		//
	LPDIRECT3DVERTEXBUFFER9			m_pD3DVertexBuffer;
	LPDIRECT3DTEXTURE9				m_pD3DTexture;

	bool							m_bWatchCamera;	//プリ道v部
	LPCSTR							m_pszFName;

	D3DXVECTOR3						m_vSize;
	D3DXVECTOR3						m_vOblique[2];	//傾斜の度合

	D3DXVECTOR3						m_vSizeUV;		//UVの座標
	int								m_nMaxUVFrame;	//最大UVFrame
	int								m_nRecUVFrameX; //現在UV_Xのフレーム数
	int								m_nRecUVFrameY;	//現在UV_Yのフレーム数

	
};


#endif