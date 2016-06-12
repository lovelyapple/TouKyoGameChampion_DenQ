//-----------------------------------------------------------
//メニューマスターズクラス
//-----------------------------------------------------------
#ifndef	_C_SELECTIONLIST_H_
#define _C_SELECTIONLIST_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
//--------------------------------------
//マスターズインクルード
#include "Sys_Input.h"

//--------------------------------------
//インスタンスインクルード
#include "C_HUD_Selection.h"
//--------------------------------------
//マクロ定義
#define CURSOR_SIZE				(D3DXVECTOR3(2.0f,0.5f,0.0f))
#define CURSOR_FILE_NAME		("data/Texture/MenuCursor.png")	
#define MAX_SELECTION			(8)
#define BACK_DEST_POS			(D3DXVECTOR3(-4.0f,0.0f,1.0f))
#define SELECTION_MOVE_TIME		(1*60)
#define	ALPHA_CHANGE_VALUE		(1.0f / SELECTION_MOVE_TIME)
//--------------------------------------
//構造体宣言
typedef enum
{
	SELECTION_TYPE_MOVING = 0,			//移動状態
	SELECTION_TYPE_FRONT,				//フロント停止状態
	SELECTION_TYPE_BACK,				//バック停止状態
	SELECTION_TYPE_MAX,					//制御
}SELECTION_TYPE;
//--------------------------------------
//クラス宣言
class c_SelectionList
{
public:
	c_SelectionList();
	void InitSelectionList(void);			//リストの項目をNULLに初期化
	void RunFadeList(void);					//リストのフロントバック移動
	void UpdateList(void);
	void DrawList(void);					//びょぐあ
	void UninitSelectionList(void);			//リスト項目の開放処理
	void CreatList(LPCSTR FileName[],					//ファイル名列
					int MaxItem,						//最大項目数
					D3DXVECTOR3 ListPos,				//リストのフロント位置
					D3DXVECTOR3 size);					//大きさ
	bool TypeCheck(void);								//移動可能チェック
	void SetListPos(D3DXVECTOR3 pos);					//位置の指定
	void SetListRot(D3DXVECTOR3 rot);					//回転の指定
	void ChangeType(int nType);							//移動前準備

	c_Selection*		m_pSelection[MAX_SELECTION];
private:
	
	LPCSTR*				m_pFileName;
	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vRot;

	D3DXVECTOR3			m_vBackPos;			//バック位置
	D3DXVECTOR3			m_vFrontPos;		//フロント位置
	D3DXVECTOR3			m_vSpeed;			//
	int					m_nRecType;			//現在のType
	int					m_nDesType;			//目標のType
	int					m_nTime;			//移動時間
	float				m_fAlpha;			//現在のアルファ値
	float				m_fHeight;			//太さ



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