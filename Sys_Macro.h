#ifndef _SYS_MACRO_
#define _SYS_MACRO_

#include "Sys_Include.h"


//-------- マクロ
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif

#define BACKCOLOR	(D3DCOLOR_XRGB(0,0,0))

#define KEY_CHANGE_DISP	('F')
#define FRAME_RATE		(1000/60)	// フレームレート


#define IDI_ICON1		(101)
#define IDR_MENU1		(102)
#define ID_FILE_EXIT	(40001)	//メニューの命令コード

#define D3DV_INIT(x)	{(x) = D3DXVECTOR3(0.0f,0.0f,0.0f);}
#define D3DM_INIT(x)	{D3DXMatrixIdentity(&x);}

#define SCREEN_WIDTH_WIN	(1280)
#define SCREEN_HEIGHT_WIN	(720)
#define SCREEN_WIDTH_FULL	(1280)
#define SCREEN_HEIGHT_FULL	(800)
#define ASPECT_RATIO_WIN	((float)SCREEN_WIDTH_WIN/SCREEN_HEIGHT_WIN)
#define ASPECT_RATIO_FULL	(SCREEN_WIDTH_FULL/SCREEN_HEIGHT_FULL)
#define FOVY				(60.0f)
#define NEAR_CLIP			1.0f								// 前面クリップ距離
#define FAR_CLIP			10000.0f	

// 頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_2D_PRIM	 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//------------------------------------------------------
//ゲーム設定に関するマクロ定義
#ifndef _FIELD_SIZE_
#define _FIELD_SIZE_
#define MAX_FIELD_WIDTH		(100)
#define MAX_FIELD_HEIGHT	(15)
#endif

#ifndef _INPUT_KEY_
#define _INPUT_KEY_
#define KEY_DIR_LEFT	(DIK_LEFT)
#define KEY_DIR_RIGHT	(DIK_RIGHT)
#define KEY_DIR_UP		(DIK_UP)
#define KEY_DIR_DOWN	(DIK_DOWN)
#define KEY_JUMP		(DIK_SPACE)
#define KEY_DUSH		(DIK_LSHIFT)
#define KEY_ENTER		(DIK_RETURN)
#define KEY_PAUSE		(DIK_P)

typedef enum
{
	MOVE_KEY_X_UP = 0,
	MOVE_KEY_X_DWON,
	MOVE_KEY_Y_UP,
	MOVE_KEY_Y_DOWN,
	MOVE_KEY_Z_UP,
	MOVE_KEY_Z_DOWN,
	MOVE_KEY_JUMP_KEY,
	MOVE_KEY_DUSH,
	MOVE_KEY_MAX,
}MOVE_KEY;
#endif
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
#define DEFAULT_MODEL_FILE	"data/model/base_error.x"
#endif
//-----------------------------------------------------------
//タイトル
//-----------------------------------------------------------
//--------------------------------------
//システムインクルード
//--------------------------------------
//マスターズインクルード
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
//--------------------------------------
//構造体宣言
//--------------------------------------
//クラス宣言
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
