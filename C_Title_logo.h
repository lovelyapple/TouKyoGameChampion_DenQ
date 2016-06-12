//=============================================================================
//
// タイトル画面処理
//
//=============================================================================
#ifndef _C_TITLE_H_
#define _C_TITLE_H_

//--------------------------------------
//システムインクルード
#include "Sys_Include.h"
#include "Sys_Macro.h"
//--------------------------------------
//マスターズインクルード
//-------------------------------------
#include "C_Master_Primitive.h"
#include "Sys_C_Physic.h"
//--------------------------------------
//マクロ定義
//-------------------------------------
#define TEXTURE_HEIGHT (1)
#define TEXTURE_WIDTH (1)
#define TEXTURE_TITLE ("data/Texture/denkyu.png")
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class  c_Logo : public c_Master_Primitive
{
public:
	c_Logo();
	HRESULT	Init(void);
	void	Update(void);	
	void	SetVerTxBuff(void);	

private:
protected:
};

#endif