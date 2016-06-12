//-----------------------------------------------------------
//ゲーム内のブロック
//-----------------------------------------------------------
#ifndef _C_BLOCK_H_
#define _C_BLOCK_H_
//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//マスターズインクルード
#include "C_Master_Model.h"
//--------------------------------------
//インスタンスインクルード
//--------------------------------------
//マクロ定義
#define BLOCK_SIZE			(1.0f)
//--------------------------------------
//構造体宣言
typedef struct 
{
	int		nType;
}S_BLOCK;
typedef enum
{
	BLOCK_TYPE_NOMAL_ELE = 0,
	BLOCK_TYPE_HEIGH_ELE,
	BLOCK_TYPE_MAX,
}BLOCK_TYPE;
//--------------------------------------
//クラス宣言
class C_FIELDPLACE
{
public:
	C_FIELDPLACE();
	C_FIELDPLACE(int inputx,int inputy);
	int x,y;
};
class c_Block :public c_Model
{
public:	
	c_Block();						//コンストラクタ
	c_Block(int,C_FIELDPLACE*);		//コンストラクタオーバーロード
	~c_Block();						//デストラクタ
	HRESULT	SetModel(void);			//
	void UpdateBlock(void);
	void FieldCheck(void);		//フィールドの範囲チェック(選択ブロック用)
	void DrawBlock(void);	

	C_FIELDPLACE	m_uPlace;		//フィールド座標
	S_BLOCK			m_uBlock;		//ブロック構造体
	void UpdateModel(void);
	void DrawModel(void);	



private:
protected:

};
//----------------------------------------
//その他の機能関数
void SetPosFromFeildPlace(C_FIELDPLACE*,D3DXVECTOR3*);
#endif
